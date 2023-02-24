#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#ifndef VIRTUALSOC_USER_H
#define VIRTUALSOC_USER_H
using namespace std;


class User {
private:
    unsigned int id;
    string username;
    string password;
    int socketDescriptor;
    vector<User> friendList;
public:
    User();
    User(string username,string password);
    User(unsigned int id, string username,string password);
    User(unsigned int id, string username, string password, int socketDescriptor);

    unsigned int getId() const;
    void setId(unsigned int id);

    const string &
    getUsername() const;
    void setUsername(const string &username);

    const string &getPassword() const;
    void setPassword(const string &password);

    int getSocketDescriptor() const;
    void setSocketDescriptor(int socketDescriptor);

    const vector<User> &getFriendList() const;
    void setFriendList(const vector<User> &friendList);

    void addFriend(User newFriend);
    void eliminateFriend(User noFriend);
    void sendChatMessage(User recipient, string message);
    void seeAllMessages();
    void seeFriendRequests();
    void acceptFriendRequest(User acceptRequest);
};


#endif //VIRTUALSOC_USER_H
