#include "User.h"
#include <iterator>
using namespace std;
User::User()
{
    id = -1;
    username = "";
    password = "";
    socketDescriptor = -1;
}

User::User(string username,string password)
{
    id = -1;
    this->username = username;
    this->password = password;
    socketDescriptor = -1;
}

User::User(unsigned int id, std::string username, std::string password)
{
    this->id = id;
    this->username = username;
    this->password = password;
    socketDescriptor = -1;
}

User::User(unsigned int id, std::string username, std::string password, int socketDescriptor)
{
    this->id = id;
    this->username = username;
    this->password = password;
    this->socketDescriptor = socketDescriptor;
}

unsigned int User::getId() const {
    return id;
}

void User::setId(unsigned int id) {
    User::id = id;
}

const string &User::getUsername() const {
    return username;
}

void User::setUsername(const string &username) {
    User::username = username;
}

const string &User::getPassword() const {
    return password;
}

void User::setPassword(const string &password) {
    User::password = password;
}

int User::getSocketDescriptor() const {
    return socketDescriptor;
}

void User::setSocketDescriptor(int socketDescriptor) {
    User::socketDescriptor = socketDescriptor;
}

const vector<User> &User::getFriendList() const {
    return friendList;
}

void User::setFriendList(const vector<User> &friendList) {
    User::friendList = friendList;
}

void User::addFriend(User newFriend)
{
    friendList.push_back(newFriend);
}

void User::eliminateFriend(User noFriend)
{
    for(auto it = friendList.begin(); it != friendList.end(); it++)
    {
        if(it->username == noFriend.username && it->password == noFriend.password)
        {
            friendList.erase(it);
            break;
        }
    }
}


