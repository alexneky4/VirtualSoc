#include "DOB.h"

DOB::DOB() {
    char* err;
    sqlite3_open("virtualSoc.db",&db);

    int rc = sqlite3_exec(db,"CREATE TABLE IF NOT EXISTS registeredUsers (user varchar2(40), password varchar2(40));",
                          nullptr, nullptr, &err);
    if(rc != SQLITE_OK)
    {
        cerr<<err<<endl;
    }

    rc = sqlite3_exec(db,"CREATE TABLE IF NOT EXISTS userFriends (user varchar2(40), userFriend varchar2(40), status varchar2(20));",
                      nullptr, nullptr, &err);
    if(rc != SQLITE_OK)
    {
        cerr<<err<<endl;
    }

    rc = sqlite3_exec(db,"CREATE TABLE IF NOT EXISTS usersPosts (user varchar2(40), post varchar2(600),status varchar2(40));",
                      nullptr, nullptr, &err);
    if(rc != SQLITE_OK)
    {
        cerr<<err<<endl;
    }

    rc = sqlite3_exec(db,"CREATE TABLE IF NOT EXISTS friendRequests (fromUser varchar2(40), toUser varchar2(40));",
                      nullptr, nullptr, &err);
    if(rc != SQLITE_OK)
    {
        cerr<<err<<endl;
    }

    rc = sqlite3_exec(db,"CREATE TABLE IF NOT EXISTS userChats (sender varchar2(40), receiver varchar2(40), messageText varchar2(200), msgDate text);",
                      nullptr, nullptr, &err);
    if(rc != SQLITE_OK)
    {
        cerr<<err<<endl;
    }
}

bool DOB::existUser(string username,string password)
{
    char *err;
    sqlite3_stmt *stmt;
    int rc;
    string querry = "SELECT * FROM registeredUsers WHERE user = '" +  username + "' AND password = '"+password+"';";
    rc = sqlite3_prepare_v2(db,querry.c_str(),-1,&stmt, nullptr);
    if(rc != SQLITE_OK)
    {
        return false;
    }
    rc = sqlite3_step(stmt);
    if(rc == SQLITE_ROW)
        return true;
    return false;

}

bool DOB::existUsername(string username)
{
    char *err;
    sqlite3_stmt *stmt;
    int rc;
    string querry = "SELECT * FROM registeredUsers WHERE user = '" +  username +"';";
    rc = sqlite3_prepare_v2(db,querry.c_str(),-1,&stmt, nullptr);
    if(rc != SQLITE_OK)
    {
        return false;
    }
    rc = sqlite3_step(stmt);
    if(rc == SQLITE_ROW)
        return true;
    return false;

}

bool DOB::addUser(string username,string password)
{
    char *err;
    if(existUsername(username) == true)
        return false;
    string querry = "INSERT INTO registeredUsers VALUES ( '" + username + "' , '" + password + "' );";
    int rc = sqlite3_exec(db,querry.c_str(), nullptr, nullptr,&err);
    if(rc != SQLITE_OK)
    {
        cerr<<err<<endl;
        return false;
    }
    return true;
}



bool DOB::deleteUser(string username, string password)
{
    char *err;

    string querry = "DELETE FROM registeredUsers WHERE user = '" +  username + "' AND password = '" + password + " ';";
    int rc = sqlite3_exec(db,querry.c_str(), nullptr, nullptr,&err);
    if(rc != SQLITE_OK)
    {
        cerr<<rc<<endl;
        return false;
    }
    return true;
}

bool DOB::existFriendRequest(string fromUser, string toUser)
{
    sqlite3_stmt *stmt;
    int rc;
    printf("%s %s \n", fromUser.c_str(), toUser.c_str());
    string querry = "SELECT * FROM friendRequests WHERE fromUser = '" +  fromUser + "' AND toUser = '" + toUser + " ';";
    sqlite3_prepare_v2(db,querry.c_str(),-1,&stmt, nullptr);
    if((rc = sqlite3_step(stmt)) == SQLITE_ROW)
        return true;
    else if(rc == SQLITE_DONE)
        return false;
    else
    {
        cerr<<"Eroare"<<'\n';
        return false;
    }
}
bool DOB::addFriendRequest(string fromUser, string toUser)
{
    char *err;
    if(existFriendRequest(fromUser,toUser) == true)
        return false;
    string querry = "INSERT INTO friendRequests VALUES ( '" + fromUser + "' , '" + toUser + "' );";
    int rc = sqlite3_exec(db,querry.c_str(), nullptr, nullptr,&err);
    if(rc != SQLITE_OK)
    {
        cerr<<err<<endl;
        return false;
    }
    return true;
}

bool DOB::deleteFriendRequest(string fromUser, string toUser)
{
    char *err;

    string querry = "DELETE FROM friendRequests WHERE fromUser = '" +  fromUser + "' AND toUser = '" + toUser + "';";
    int rc = sqlite3_exec(db,querry.c_str(), nullptr, nullptr,&err);
    if(rc != SQLITE_OK)
    {
        cerr<<rc<<endl;
        return false;
    }
    return true;
}

bool DOB::existFriend(string user, string userFriend)
{
    sqlite3_stmt *stmt;
    int rc;
    string querry = "SELECT * FROM userFriends WHERE user = '" +  user + "' AND userFriend = '" + userFriend + "';";
    sqlite3_prepare_v2(db,querry.c_str(),-1,&stmt, nullptr);
    rc = sqlite3_step(stmt);
    if(rc == SQLITE_ROW)
        return true;
    else if(rc == SQLITE_DONE)
        return false;
    else
    {
        cerr<<"Eroare"<<'\n';
        return false;
    }
}

bool DOB::addFriend(string user, string userFriend, string status)
{
    char *err;
    if(existFriend(user,userFriend) == true)
    {
        return false;
    }

    string querry = "INSERT INTO userFriends VALUES ( '" + user + "' , '" + userFriend + "' , '" + status + "' );";
    int rc = sqlite3_exec(db,querry.c_str(), nullptr, nullptr,&err);
    if(rc != SQLITE_OK)
    {
        cerr<<err<<endl;
        return false;
    }
    return true;
}

bool DOB::deleteFriend(string user, string userFriend)
{
    char *err;

    string querry = "DELETE FROM userFriends WHERE user = '" +  user + "' AND userFriend = '" + userFriend + " ';";
    int rc = sqlite3_exec(db,querry.c_str(), nullptr, nullptr,&err);
    if(rc != SQLITE_OK)
    {
        cerr<<rc<<endl;
        return false;
    }
    return true;
}

vector<string> DOB::getOtherUsers(string username)
{
    char *err;
    int rc;
    sqlite3_stmt *stmt;
    vector<string> allUsers;
    string querry = "SELECT user FROM registeredUsers WHERE user != '" + username + "' AND " +
                    "user NOT IN (SELECT toUser FROM friendRequests WHERE fromUser = '" + username + "') ;";

    sqlite3_prepare_v2(db,querry.c_str(),-1,&stmt, nullptr);
    while((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        string user = reinterpret_cast<const char*>(sqlite3_column_text(stmt,0));
        allUsers.push_back(user);
    }

    return allUsers;
}

vector<string> DOB::getUserFriends(std::string username) {
    char *err;
    int rc;
    sqlite3_stmt *stmt;
    vector<string> userFriends;
    string querry = "SELECT userFriend FROM userFriends WHERE user = '" + username +"';";

    sqlite3_prepare_v2(db,querry.c_str(),-1,&stmt, nullptr);
    while((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        string user = reinterpret_cast<const char*>(sqlite3_column_text(stmt,0));
        userFriends.push_back(user);
    }

    return userFriends;
}

bool DOB::updateFriendStatus(std::string user, std::string userFriend, std::string status) {
    char *err;
    string querry = "UPDATE userFriends SET status = '" + status + "' WHERE user = '" +  user + "' AND userFriend = '" + userFriend + "';";
    cerr<<querry<<'\n';
    int rc = sqlite3_exec(db,querry.c_str(), nullptr, nullptr,&err);
    if(rc != SQLITE_OK)
    {
        return false;
    }
    return true;
}

vector<string> DOB::getFriendRequests(std::string username) {
    char *err;
    int rc;
    sqlite3_stmt *stmt;
    vector<string> friendRequests;
    string querry = "SELECT fromUser FROM friendRequests WHERE toUser = '" + username +  "' ;";

    sqlite3_prepare_v2(db,querry.c_str(),-1,&stmt, nullptr);
    while((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        string user = reinterpret_cast<const char*>(sqlite3_column_text(stmt,0));
        friendRequests.push_back(user);
    }

    return friendRequests;
}

bool DOB::addPost(string user,string postText, string status)
{
    char *err;
    string querry = "INSERT INTO usersPosts VALUES ( '" + user + "' , '" + postText + "' , '" + status + "' );";
    int rc = sqlite3_exec(db,querry.c_str(), nullptr, nullptr,&err);
    if(rc != SQLITE_OK)
    {
        cerr<<err<<endl;
        return false;
    }
    return true;
}

vector<string> DOB::getPublicPosts() {
    char *err;
    int rc;
    sqlite3_stmt *stmt;
    vector<string> publicPosts;
    string querry = "SELECT post FROM usersPosts WHERE status = 'Public' ;";

    sqlite3_prepare_v2(db,querry.c_str(),-1,&stmt, nullptr);
    while((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        string post = reinterpret_cast<const char*>(sqlite3_column_text(stmt,0));
        publicPosts.push_back(post);
    }

    return publicPosts;
}


vector<string> DOB::getAllUserPosts(string user) {
    char *err;
    int rc;
    sqlite3_stmt *stmt;
    vector<string> publicPosts;
    string querry = "SELECT post FROM usersPosts WHERE user in "
                    "(SELECT userFriend FROM userFriends where user = '" + user + "')" +
                    "and status in ('Public','Friends-Only');";

    sqlite3_prepare_v2(db,querry.c_str(),-1,&stmt, nullptr);
    while((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        string post = reinterpret_cast<const char*>(sqlite3_column_text(stmt,0));
        publicPosts.push_back(post);
    }

    return publicPosts;
}

vector<string> DOB::getPrivatePosts(string user) {
    char *err;
    int rc;
    sqlite3_stmt *stmt;
    vector<string> privatePosts;
    string querry = "SELECT post FROM usersPosts WHERE user = '" + user + "' ;";

    sqlite3_prepare_v2(db,querry.c_str(),-1,&stmt, nullptr);
    while((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        string post = reinterpret_cast<const char*>(sqlite3_column_text(stmt,0));
        privatePosts.push_back(post);
    }

    return privatePosts;
}

vector<pair<string,string>> DOB::getUsersChat(std::string sender, std::string receiver) {
    char *err;
    int rc;
    sqlite3_stmt *stmt;
    vector<pair<string,string>> chatMessage;
    string querry = "SELECT sender,messageText FROM userChats WHERE sender IN ('" + sender + "' , '"
                    + receiver + "') AND receiver IN ('" + sender + "' , '"+ receiver + "') ORDER BY msgDate;";
    sqlite3_prepare_v2(db,querry.c_str(),-1,&stmt, nullptr);
    while((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        string user = reinterpret_cast<const char*>(sqlite3_column_text(stmt,0));
        string message = reinterpret_cast<const char*>(sqlite3_column_text(stmt,1));
        chatMessage.push_back(make_pair(user,message));
    }

    return chatMessage;
}

bool DOB::insertMessage(string sender,string receiver,string messageText, string date)
{
    char *err;
    string querry = "INSERT INTO userChats VALUES ( '" + sender + "' , '" + receiver + "' , '" + messageText +
                    "',  DATETIME('" + date + "'));";
    cout<<querry<<endl;
    int rc = sqlite3_exec(db,querry.c_str(), nullptr, nullptr,&err);
    if(rc != SQLITE_OK)
    {
        cerr<<err<<endl;
        return false;
    }
    return true;
}