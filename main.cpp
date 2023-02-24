#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <sys/signal.h>
#include <sys/wait.h>
#include <map>
#include <thread>
#include <utility>
#include "DOB/DOB.h"
#include "Users/User.h"

using namespace std;

extern int errno;

#define PORT 2048

int clientCounter = 0;
map<string,int> activeUsers;
map<int,int> communication;
vector<int> activeFd;
DOB db;
//TODO: Crapa la show posts : de lucrat si aflat de ce
void sendMessage(string message, int fd)
{
    cerr<<message<<'\n';
    int length = message.length();
    int nrBytes;
    if(find(activeFd.begin(), activeFd.end(), fd) != activeFd.end())
        nrBytes = send(fd,&length,sizeof(int),MSG_NOSIGNAL);
    if(nrBytes < 0)
    {
        perror("[server]Error when sending message\n");
        if(errno == EPIPE)
        {
            if(find(activeFd.begin(), activeFd.end(), fd) != activeFd.end())
                activeFd.erase(find(activeFd.begin(), activeFd.end(), fd));
            close(fd);
            return;
        }
    }
    if(find(activeFd.begin(), activeFd.end(), fd) != activeFd.end())
        nrBytes = send(fd,message.c_str(),length,MSG_NOSIGNAL);
    if(nrBytes < 0)
    {
        perror("[server]Error when sending message\n");
        if(errno == EPIPE)
        {
            if(find(activeFd.begin(), activeFd.end(), fd) != activeFd.end())
                activeFd.erase(find(activeFd.begin(), activeFd.end(), fd));
            close(fd);
            return;
        }
    }
}

void receiveMessage(string &message,int fd)
{
    int length;
    int nrBytes;
    if(find(activeFd.begin(), activeFd.end(), fd) != activeFd.end())
        nrBytes = recv(fd,&length,sizeof(int),MSG_NOSIGNAL);
    if(nrBytes < 0)
    {
        perror("[server]Error when receiving message\n");

    }
    else
    {
        if(nrBytes == 0)
        {
            if(errno == EPIPE)
            {
                if(find(activeFd.begin(), activeFd.end(), fd) != activeFd.end())
                    activeFd.erase(find(activeFd.begin(), activeFd.end(), fd));
                close(fd);
                return;
            }

        }

    }
    char *receiver = new char[length + 1]{};
    if(find(activeFd.begin(), activeFd.end(), fd) != activeFd.end())
        nrBytes = recv(fd,receiver,length,MSG_NOSIGNAL);
    if(nrBytes < 0)
    {
        perror("[server]Error when receiving message\n");
    }
    else
    {
        if(nrBytes == 0)
        {
            if(errno == EPIPE)
            {
                if(find(activeFd.begin(), activeFd.end(), fd) != activeFd.end())
                    activeFd.erase(find(activeFd.begin(), activeFd.end(), fd));
                close(fd);
                return;
            }
        }
    }
    message = receiver;
    delete[] receiver;
    cerr<<message<<'\n';

}

bool loginUser(User user)
{
    string response;
    if(db.existUser(user.getUsername(),user.getPassword()) == true)
    {
        response = "IN";
        sendMessage(response,user.getSocketDescriptor());
        return true;
    }
    else
    {
        response = "OUT";
        sendMessage(response,user.getSocketDescriptor());
        return false;
    }

}
bool registerUser(User user)
{
    string response;
    if(db.addUser(user.getUsername(),user.getPassword()) == true)
    {
        response = "IN";
        sendMessage(response,user.getSocketDescriptor());
        return true;
    }
    else
    {
        response = "OUT";
        sendMessage(response,user.getSocketDescriptor());
        return false;
    }
}
bool sendOtherUsers(User user)
{
    vector<string> otherUsers = db.getOtherUsers(user.getUsername());
    int size = otherUsers.size();
    send(user.getSocketDescriptor(),&size,sizeof(int),MSG_NOSIGNAL);
    for(auto other : otherUsers)
    {
        sendMessage(other,user.getSocketDescriptor());
    }
    return true;

}
bool addUserRequest(User user,string username)
{
    string success;
    if(db.addFriendRequest(user.getUsername(), std::move(username)) == true)
    {
        success = "success";
        sendMessage(success,user.getSocketDescriptor());
        return true;
    }
    else
    {
        success = "failed";
        sendMessage(success,user.getSocketDescriptor());
        return false;
    }
}

bool sendFriendList(User user)
{
    vector<string> usernames = db.getUserFriends(user.getUsername());
    int size = usernames.size();
    send(user.getSocketDescriptor(),&size,sizeof(int),MSG_NOSIGNAL);
    for(auto userFriend : usernames)
    {
        sendMessage(userFriend,user.getSocketDescriptor());
    }
    return true;
}

bool updateFriendStatus(User user, string username, string status)
{
    if(db.updateFriendStatus(user.getUsername(),username,status) == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool sendFriendRequests(User user)
{
    vector<string> usernames = db.getFriendRequests(user.getUsername());
    int size = usernames.size();
    send(user.getSocketDescriptor(),&size,sizeof(int),MSG_NOSIGNAL);
    for(auto userFriend : usernames)
    {
        sendMessage(userFriend,user.getSocketDescriptor());
    }
    return true;
}
bool deleteUserRequest(User user, string username)
{
    if(db.deleteFriendRequest(username,user.getUsername()) == true)
        return true;
    else
        return false;
}
bool addUserFriend(User user, string username)
{
    bool val = db.addFriend(user.getUsername(),username,"Friend") && db.addFriend(username,user.getUsername(),"Friend");
    if(val)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool addUserPost(User user,string postText, string status)
{
    if(db.addPost(user.getUsername(), std::move(postText), std::move(status)))
        return true;
    else
        return false;
}
bool getAllPublicPosts(int client)
{
    vector<string> publicPosts = db.getPublicPosts();
    int size = publicPosts.size();
    send(client,&size,sizeof(int),MSG_NOSIGNAL);
    for(string post : publicPosts)
    {
        sendMessage(post,client);
    }
    return true;
}

bool sendAllUserPosts(User user)
{
    vector<string> allPosts = db.getAllUserPosts(user.getUsername());
    vector<string> privatePosts = db.getPrivatePosts(user.getUsername());
    allPosts.insert(allPosts.end(),privatePosts.begin(),privatePosts.end());
    int size = allPosts.size();
    send(user.getSocketDescriptor(),&size,sizeof(int),MSG_NOSIGNAL);
    for(string post : allPosts)
    {
        sendMessage(post,user.getSocketDescriptor());
    }
    return true;
}

bool sendExistingMessages(User user, string username)
{
    vector<pair<string,string>> existingMessages = db.getUsersChat(user.getUsername(),username);
    int size = existingMessages.size();
    send(user.getSocketDescriptor(),&size,sizeof(int),MSG_NOSIGNAL);
    for(auto msgPair : existingMessages)
    {
        string sender = msgPair.first;
        string message = msgPair.second;
        sendMessage(sender,user.getSocketDescriptor());
        sendMessage(message,user.getSocketDescriptor());
    }
    return true;
}

bool sendChatMessage(User user)
{
    string message = "";
    fd_set readfds;
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    while(message != "DONE_CHAT")
    {
        string username;
        receiveMessage(username,user.getSocketDescriptor());
        sendExistingMessages(user,username);
        if (activeUsers.find(username) != activeUsers.end()) {
            int otherUsersd = activeUsers[username];
            communication[user.getSocketDescriptor()] = otherUsersd;
        }
        do {
            FD_ZERO(&readfds);
            FD_SET(user.getSocketDescriptor(), &readfds);
            select (user.getSocketDescriptor()+1, &readfds, NULL, NULL, &tv);
            if(FD_ISSET(user.getSocketDescriptor(),&readfds) == true)
            {
                time_t curr_time;
                tm * curr_tm;
                string time_string;
                char timeChar[20];
                time(&curr_time);
                curr_tm = localtime(&curr_time);

                strftime(timeChar, 20, "%Y-%m-%d %H:%M:%S", curr_tm);
                time_string = timeChar;
                receiveMessage(message,user.getSocketDescriptor());
                if(message != "CHANGE_CHAT" && message != "DONE_CHAT") {
                    db.insertMessage(user.getUsername(), username, message, time_string);
                    if (activeUsers.find(username) != activeUsers.end()) {
                        int otherUsersd = activeUsers[username];
                        communication[user.getSocketDescriptor()] = otherUsersd;
                        if (communication[otherUsersd] == user.getSocketDescriptor()) {
                            sendMessage(message, otherUsersd);
                        }
                    }
                }
            }
        }while(message != "CHANGE_CHAT" && message != "DONE_CHAT");
        communication[user.getSocketDescriptor()] = -1;
    }

    return true;
}

void response(int client)
{
    int option = 12;
    int nrBytes;
    User user;
    user.setId(clientCounter++);
    user.setSocketDescriptor(client);
    bool logged = false;
    do{
        if(find(activeFd.begin(), activeFd.end(), client) != activeFd.end())
            option = 12;
        if(find(activeFd.begin(), activeFd.end(), client) != activeFd.end())
            nrBytes = recv(client,&option,sizeof(int),MSG_NOSIGNAL);
        if(nrBytes == 0)
        {
            if(find(activeFd.begin(), activeFd.end(), client) != activeFd.end())
                activeFd.erase(find(activeFd.begin(), activeFd.end(), client));
            close(client);
            return;
        }
        switch(option)
        {
            case 0 :
            {
                if(logged == false)
                {
                    getAllPublicPosts(client);
                }
                else
                {
                    sendAllUserPosts(user);
                }
                break;
            }
            case 1:
            {
                string username;
                string password;
                receiveMessage(username,client);
                receiveMessage(password,client);
                user.setUsername(username);
                user.setPassword(password);
                if(loginUser(user) == true)
                {
                    logged = true;
                    activeUsers[user.getUsername()] = user.getSocketDescriptor();
                }
                else
                {
                    user.setUsername("");
                    user.setPassword("");
                }
                break;
            }
            case 2:
            {
                string username;
                string password;
                receiveMessage(username,client);
                receiveMessage(password,client);
                user.setUsername(username);
                user.setPassword(password);
                if(registerUser(user) == false)
                {
                    user.setUsername("");
                    user.setPassword("");
                }
                break;
            }
            case 3:
            {
                if(logged == true)
                {
                    sendFriendList(user);
                }
                break;
            }
            case 4: {
                if(logged == true)
                {
                    string status;
                    string username;
                    receiveMessage(username,client);
                    receiveMessage(status,client);
                    updateFriendStatus(user,username,status);
                }
                break;
            }
            case 5:
            {
                if(logged == true)
                {
                    sendFriendRequests(user);
                }
                break;
            }
            case 6:
            {
                if(logged == true)
                {
                    string response;
                    string username;
                    //receiveMessage(username,client);
                    receiveMessage(response,client);
                    if(response == "IN")
                    {
                        receiveMessage(username,client);
                        deleteUserRequest(user,username);
                        addUserFriend(user,username);
                    }
                    else if(response == "OUT")
                    {
                        receiveMessage(username,client);
                        deleteUserRequest(user,username);
                    }
                }
                break;
            }
            case 7:
            {
                if(logged == true)
                {
                    sendMessage(user.getUsername(),client);
                    sendOtherUsers(user);
                }
                break;
            }
            case 8:
            {
                if(logged == true)
                {
                    string response;
                    receiveMessage(response,client);
                    if(response == "IN")
                    {
                        string username;
                        receiveMessage(username,client);
                        addUserRequest(user,username);
                    }
                }
                break;
            }
            case 9:
            {
                if(logged == true)
                {
                    string postText;
                    string status;
                    receiveMessage(postText,client);
                    receiveMessage(status,client);
                    addUserPost(user,postText,status);
                }
                break;
            }
            case 10:
            {
                if(logged == true)
                {
                    sendFriendList(user);
                }
                break;
            }
            case 11:
            {
                sendChatMessage(user);
                break;
            }
        }
    }while(option != 12);

    if(find(activeFd.begin(), activeFd.end(), client) != activeFd.end())
        activeFd.erase(find(activeFd.begin(), activeFd.end(), client));
    close(client);
    activeUsers.erase(user.getUsername());
}
int main()
{
    struct sockaddr_in server;
    struct sockaddr_in from;
    int optval = 1;
    int sd;
    if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("[server]Error when creating server socket.\n");
        return errno;
    }
    setsockopt(sd, SOL_SOCKET, SO_REUSEADDR,&optval,sizeof(optval));
    bzero (&server, sizeof (server));
    bzero (&from, sizeof (from));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT);

    if (bind (sd, (struct sockaddr *) &server, sizeof (struct sockaddr)) == -1)
    {
        perror ("[server]Error at binding the socket to the server.\n");
        return errno;
    }

    if (listen (sd, 10) == -1)
    {
        perror ("[server]Error at listen().\n");
        return errno;
    }

    int index = 0;
    while(1) {
        int client;
        socklen_t length = sizeof(from);
        while ((client = accept(sd, (struct sockaddr *) &from, &length)) > 0) {
            activeFd.push_back(client);
            thread t(response, client);
            t.detach();
        }
    }
    return 0;
}
