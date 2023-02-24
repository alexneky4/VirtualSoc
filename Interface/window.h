#ifndef WINDOW_H
#define WINDOW_H
#include "chatwindow.h"
#include "createpost.h"
#include "mainwindow.h"
#include "loginwindow.h"
#include "friendlist.h"
#include <thread>
#include <QObject>
#include <errno.h>
#include <sys/socket.h>
#include <QSocketNotifier>
class Window : public QObject
{
    Q_OBJECT
public:
    MainWindow main;
    LoginWindow login;
    FriendList friends;
    CreatePost post;
    ChatWindow chat;
    QSocketNotifier *notifier = new QSocketNotifier(QSocketNotifier::Read);
    int socketDescriptor;
    bool loggedIn = false;
    bool startChat = false;
    Window();
public slots:
    void showLogin();
    void showRegister();
    void showFriends();
    void showFriendRequests();
    void showOtherUsers();
    void showCreatePost();
    void showChat();
    void backFunction();
    void connectUser();
    void popAcceptRequest(QListWidgetItem* widget);
    void popSendRequest(QListWidgetItem* widget);
    void changeStatus(QListWidgetItem* widget);
    void addUserPost();
    void displayPosts();
    void activateChat(QListWidgetItem* widget);
    void sendChatMessage();
    void backFromChat();
private:
    void receiveChatMessages();
    void resetInformations();
    void sendMessage(string message);
    void receiveMessage(string &message);
public:
    void setSocketDescriptor(int fd);

};

#endif // WINDOW_H
