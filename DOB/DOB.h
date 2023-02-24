#include "sqlite3.h"
#include <string>
#include <iostream>
#include <vector>
#ifndef VIRTUALSOC_DOB_H
#define VIRTUALSOC_DOB_H

using namespace std;

class DOB {
    sqlite3 *db;
public:
    DOB();
    bool existUser(string username,string password);
    bool addUser(string username,string password);
    bool deleteUser(string username, string password);
    bool existUsername(string usenrame);
    vector<string> getOtherUsers(string username);
    bool existFriendRequest(string fromUser, string toUser);
    bool addFriendRequest(string fromUser, string toUser);
    bool deleteFriendRequest(string fromUser, string toUser);
    bool existFriend(string user, string userFriend);
    bool addFriend(string user, string userFriend, string status);
    bool deleteFriend(string user, string userFriend);
    vector<string> getUserFriends(string username);
    bool updateFriendStatus(string user,string userFriend,string status);
    vector<string> getFriendRequests(string username);
    bool addPost(string user, string PostText, string status);
    vector<string> getPublicPosts();
    vector<string> getAllUserPosts(string user);
    vector<string> getPrivatePosts(string user);
    vector<pair<string,string>> getUsersChat(string sender, string receiver);
    bool insertMessage(string sender,string receiver,string messageText, string date);
};


#endif //VIRTUALSOC_DOB_H
