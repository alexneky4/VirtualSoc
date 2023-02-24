#include "window.h"
#include "ui_chatwindow.h"
#include "ui_createpost.h"
#include "ui_friendlist.h"
#include "ui_loginwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QVBoxLayout>
#include <QMessageBox>

Window::Window()
{
    notifier->setEnabled(false);
    main.show();
    login.hide();
    friends.hide();
    post.hide();
    chat.hide();
    QObject::connect(main.getUi()->loginButton,&QPushButton::clicked,this,&Window::showLogin);
    QObject::connect(main.getUi()->registerButton,&QPushButton::clicked,this,&Window::showRegister);
    QObject::connect(main.getUi()->friendsButton,&QPushButton::clicked,this,&Window::showFriends);
    QObject::connect(main.getUi()->friendsRequestButton,&QPushButton::clicked,this,&Window::showFriendRequests);
    QObject::connect(main.getUi()->otherUsersButton,&QPushButton::clicked,this,&Window::showOtherUsers);
    QObject::connect(main.getUi()->createPostButton,&QPushButton::clicked,this,&Window::showCreatePost);
    QObject::connect(main.getUi()->chatButton,&QPushButton::clicked,this,&Window::showChat);
    QObject::connect(main.getUi()->showPostsButton,&QPushButton::clicked,this,&Window::displayPosts);
    QObject::connect(login.getUi()->backButton,&QPushButton::clicked,this,&Window::backFunction);
    QObject::connect(friends.getUi()->backButton,&QPushButton::clicked,this,&Window::backFunction);
    QObject::connect(post.getUi()->backButton,&QPushButton::clicked,this,&Window::backFunction);
    QObject::connect(chat.getUi()->backButton,&QPushButton::clicked,this,&Window::backFromChat);
    QObject::connect(login.getUi()->submitButton,&QPushButton::clicked,this,&Window::connectUser);
    QObject::connect(post.getUi()->submitButton,&QPushButton::clicked, this, &Window::addUserPost);
    QObject::connect(chat.getUi()->chatLists,&QListWidget::itemClicked,this,&Window::activateChat);
    QObject::connect(chat.getUi()->sendButton,&QPushButton::clicked,this,&Window::sendChatMessage);
    QObject::connect(notifier, &QSocketNotifier::activated, this, &Window::receiveChatMessages);
}
void Window::showLogin()
{
    login.show();
    main.hide();
    friends.hide();
    post.hide();
    chat.hide();
}
void Window::showRegister()
{
    login.changeLoginLabelText("REGISTER");
    showLogin();
}

void Window::displayPosts() {
    int option = 0;
    int nrBytes = send(socketDescriptor,&option,sizeof(int),MSG_NOSIGNAL);
    if(nrBytes < 0)
    {
        close(socketDescriptor);
        return;
    }
    main.clearPosts();
    if(loggedIn == false)
    {
        int nrPosts;
        nrBytes = recv(socketDescriptor,&nrPosts,sizeof(int),MSG_NOSIGNAL);
        if(nrBytes < 0)
        {
            cerr<<"Eroare";
        }
        if(nrPosts == 0)
            main.getUi()->postText->text() = "There is no public posts. Please log in";
        else
        {
            for(int i = 1; i <= nrPosts; i++)
            {
                string post;
                receiveMessage(post);
                main.addPost(QString::fromStdString(post));
            }
        }
    }
    else
    {
        //main.deletePostsAfter(nrPublicPost);

        int size;
        nrBytes = recv(socketDescriptor,&size,sizeof(int),MSG_NOSIGNAL);
        if(nrBytes < 0)
        {
            close(socketDescriptor);
            return;
        }
        for(int i = 1; i <= size; i++)
        {
            string postText;
            receiveMessage(postText);
            main.addPost(QString::fromStdString(postText));
        }
    }

    main.setCurrentText();
    main.getUi()->postText->show();
    main.getUi()->showPostsButton->hide();
}
void Window::connectUser()
{
    int option = 9;
    string username = login.getUi()->usernameInsert->text().toStdString();
    string password = login.getUi()->passwordInsert->text().toStdString();
    if(username == "" || password == "")
    {
        QMessageBox::information(login.getUi()->submitButton,"Field(s) Blank","Insert both the username and password");
    }
    else
    {
        if(login.getUi()->LoginLabel->text() == "LOGIN")
        {
            option = 1;
            int nrBytes = send(socketDescriptor,&option,sizeof(int),MSG_NOSIGNAL);
            if(nrBytes < 0)
            {
                close(socketDescriptor);
                return;
            }
            sendMessage(username);
            sendMessage(password);
            string response;
            receiveMessage(response);
            if(response == "IN")
            {

                QMessageBox::information(login.getUi()->submitButton,"Login Successful","You are logged in");
                loggedIn = true;
            }
            else if(response == "OUT")
            {
                QMessageBox::information(login.getUi()->submitButton,"Login Failed","Invalid username and/or password");
                loggedIn = false;
            }

        }
        else if(login.getUi()->LoginLabel->text() == "REGISTER")
        {
            option = 2;
            int nrBytes = send(socketDescriptor,&option,sizeof(int),MSG_NOSIGNAL);
            if(nrBytes < 0)
            {
                close(socketDescriptor);
                return;
            }
            sendMessage(username);
            sendMessage(password);
            string response;
            receiveMessage(response);
            if(response == "IN")
            {
                QMessageBox::information(login.getUi()->submitButton,"Registered Successful","You registered successfully");
            }
            else if(response == "OUT")
            {
                QMessageBox::information(login.getUi()->submitButton,"Registered Failed","Username already in use");
            }
            loggedIn = false;
        }
    }
    backFunction();
}

void Window::showFriends()
{
    if(loggedIn == true)
    {
        QObject::disconnect(friends.getUi()->friendsList,&QListWidget::itemClicked,this,&Window::popSendRequest);
        QObject::disconnect(friends.getUi()->friendsList,&QListWidget::itemClicked,this,&Window::popAcceptRequest);
        int option = 3;
        int nrBytes = send(socketDescriptor,&option,sizeof(int),MSG_NOSIGNAL);
        if(nrBytes < 0)
        {
            close(socketDescriptor);
            return;
        }
        vector<QString> friendList;
        int numberOfFriends;
        nrBytes = recv(socketDescriptor,&numberOfFriends,sizeof(int),MSG_NOSIGNAL);
        if(nrBytes < 0)
        {
            close(socketDescriptor);
            return;
        }
        for(int i = 1; i <= numberOfFriends; i++)
        {
            string userFriend;
            receiveMessage(userFriend);
            friendList.push_back(QString::fromStdString(userFriend));
        }
        friends.showFriendList(friendList);
        friends.show();
        main.hide();
        login.hide();
        post.hide();
        chat.hide();
        connect(friends.getUi()->friendsList,&QListWidget::itemClicked,this,&Window::changeStatus);
    }
    else
    {
        QMessageBox::warning(main.getUi()->friendsButton,"Warning","You are not logged in!");
    }

}
void Window::changeStatus(QListWidgetItem *widget) {

    int option = 4;
    int nrBytes = send(socketDescriptor,&option,sizeof(int),MSG_NOSIGNAL);
    if(nrBytes < 0)
    {
        close(socketDescriptor);
        return;
    }
    QDialog *dialog = new QDialog;
    dialog->setWindowTitle("Change Status");
    QGroupBox* box = new QGroupBox;
    QRadioButton* friendStatus = new QRadioButton;
    friendStatus->setText("Friend");
    QRadioButton* closeFriendStatus = new QRadioButton;
    closeFriendStatus->setText("Close Friend");
    QRadioButton* familyStatus = new QRadioButton;
    familyStatus->setText("Family");
    QHBoxLayout* boxLayout = new QHBoxLayout;

    boxLayout->addWidget(friendStatus);
    boxLayout->addWidget(familyStatus);
    boxLayout->addWidget(closeFriendStatus);
    box->setLayout(boxLayout);

    QHBoxLayout* layout = new QHBoxLayout;
    QPushButton* submit = new QPushButton;
    submit->setText("Submit");
    layout->addWidget(box);
    layout->addWidget(submit);

    dialog->setLayout(layout);
    connect(submit,&QPushButton::clicked,dialog,&QDialog::accept);
    dialog->exec();
    string status;
    if(dialog->result() == QDialog::Accepted)
    {
        if(friendStatus->isChecked() == true)
        {
            status = "Friend";
        }
        else if(familyStatus->isChecked() == true)
        {
            status = "Family";
        }
        else if(closeFriendStatus->isChecked() == true)
        {
            status = "Close Friend";
        }
        string username = widget->text().toStdString();
        sendMessage(username);
        sendMessage(status);
    }
}

void Window::showFriendRequests()
{
    if(loggedIn == true) {
        QObject::disconnect(friends.getUi()->friendsList,&QListWidget::itemClicked,this,&Window::popSendRequest);
        QObject::disconnect(friends.getUi()->friendsList,&QListWidget::itemClicked,this,&Window::changeStatus);
        int option = 5;
        int nrBytes = send(socketDescriptor, &option, sizeof(int), MSG_NOSIGNAL);
        if (nrBytes < 0) {
            close(socketDescriptor);
            return;
        }
        vector<QString> friendList;
        int numberOfFriends;
        nrBytes = recv(socketDescriptor, &numberOfFriends, sizeof(int), MSG_NOSIGNAL);
        if (nrBytes < 0) {
            close(socketDescriptor);
            return;
        }
        for (int i = 1; i <= numberOfFriends; i++) {
            string userFriend;
            receiveMessage(userFriend);
            friendList.push_back(QString::fromStdString(userFriend));
        }
        friends.changeFriendsLabel("FRIEND REQUESTS");
        friends.showFriendList(friendList);
        friends.show();
        main.hide();
        login.hide();
        post.hide();
        chat.hide();
        connect(friends.getUi()->friendsList,&QListWidget::itemClicked,this,&Window::popAcceptRequest);

    }
    else
    {
        QMessageBox::warning(main.getUi()->friendsButton,"Warning","You are not logged in!");
    }
}
void Window::popAcceptRequest(QListWidgetItem *widget)
{
    int option = 6;
    int nrBytes = send(socketDescriptor,&option,sizeof(int),MSG_NOSIGNAL);
    string username = widget->text().toStdString();
    if(nrBytes < 0)
    {
        close(socketDescriptor);
        return;
    }
    QDialog *dialog = new QDialog;
    dialog->setWindowTitle("Accept Friend Request");
    QPushButton* accept = new QPushButton("Accept");
    QPushButton* reject = new QPushButton("Reject");
    QHBoxLayout* layout = new QHBoxLayout;

    layout->addWidget(accept);
    layout->addWidget(reject);

    dialog->setLayout(layout);
    connect(accept,&QPushButton::clicked,dialog,&QDialog::accept);
    connect(reject,&QPushButton::clicked,dialog,&QDialog::reject);
    dialog->exec();
    string response;
    if(dialog->result() == QDialog::Accepted)
    {
        response = "IN";
        sendMessage(response);
        sendMessage(username);
        delete widget;
    }
    else if(dialog->result() == QDialog::Rejected)
    {
        response = "OUT";
        sendMessage(response);
        sendMessage(username);
        delete widget;
    }

}

void Window::showOtherUsers()
{
    if(loggedIn == true)
    {
        QObject::disconnect(friends.getUi()->friendsList,&QListWidget::itemClicked,this,&Window::popAcceptRequest);
        QObject::disconnect(friends.getUi()->friendsList,&QListWidget::itemClicked,this,&Window::changeStatus);
        int option = 7;
        int nrBytes = send(socketDescriptor,&option,sizeof(int),MSG_NOSIGNAL);
        if(nrBytes < 0)
        {
            close(socketDescriptor);
            return;
        }
        string username;
        receiveMessage(username);
        int numberOfUsers;
        nrBytes = recv(socketDescriptor,&numberOfUsers,sizeof(int),MSG_NOSIGNAL);
        if(nrBytes < 0)
        {
            close(socketDescriptor);
            return;
        }
        vector<QString> otherUsersList;
        for(int i = 1; i <= numberOfUsers; i++)
        {
            string otherUser;
            receiveMessage(otherUser);
            otherUsersList.push_back(QString::fromStdString(otherUser));
        }
        friends.showFriendList(otherUsersList);
        friends.changeFriendsLabel("OTHER USERS");
        friends.show();
        main.hide();
        login.hide();
        post.hide();
        chat.hide();
        connect(friends.getUi()->friendsList,&QListWidget::itemClicked,this,&Window::popSendRequest);
    }
    else
    {
        QMessageBox::warning(main.getUi()->friendsButton,"Warning","You are not logged in!");
    }
}
void Window::popSendRequest(QListWidgetItem *widget)
{
    int option = 8;
    int nrBytes = send(socketDescriptor,&option,sizeof(int),MSG_NOSIGNAL);
    if(nrBytes < 0)
    {
        close(socketDescriptor);
        return;
    }
    QDialog *dialog = new QDialog;
    dialog->setWindowTitle("Send Friend Request");
    QPushButton* send = new QPushButton;

    QHBoxLayout* layout = new QHBoxLayout;
    send->setText("Submit");
    layout->addWidget(send);

    dialog->setLayout(layout);
    connect(send,&QPushButton::clicked,dialog,&QDialog::accept);
    dialog->exec();
    string result;
    if(dialog->result() == QDialog::Accepted)
    {
        result = "IN";
        sendMessage(result);
        string name = widget->text().toStdString();
        sendMessage(name);
        string status;
        string success;
        receiveMessage(success);
        if(success == "success")
            delete widget;
        else
        {
            QMessageBox::warning(friends.getUi()->friendsList,"Error","Could not accept this friend request");
        }
        delete dialog;
    }
    else if(dialog->result() == QDialog::Rejected)
    {
        result = "OUT";
        sendMessage(result);
        delete dialog;
    }

}

void Window::showCreatePost()
{
    if(loggedIn == true)
    {
        post.show();
        main.hide();
        login.hide();
        friends.hide();
        chat.hide();
    }
    else
    {
        QMessageBox::warning(main.getUi()->friendsButton,"Warning","You are not logged in!");
    }
}
void Window::showChat()
{
    if(loggedIn == true)
    {
        chat.getUi()->chatLists->clear();
        int option = 10;
        int nrBytes = send(socketDescriptor,&option,sizeof(int),MSG_NOSIGNAL);
        if(nrBytes < 0)
        {
            close(socketDescriptor);
            return;
        }
        int numberOfFriends;
        nrBytes = recv(socketDescriptor,&numberOfFriends,sizeof(int),MSG_NOSIGNAL);
        if(nrBytes < 0)
        {
            close(socketDescriptor);
            return;
        }
        for(int i = 1; i <= numberOfFriends; i++)
        {
            string userFriend;
            receiveMessage(userFriend);
            QListWidgetItem *item = new QListWidgetItem;
            item->setText(QString::fromStdString(userFriend));
            chat.getUi()->chatLists->addItem(item);
        }
        chat.show();
        main.hide();
        login.hide();
        friends.hide();
        post.hide();
    }
    else
    {
        QMessageBox::warning(main.getUi()->friendsButton,"Warning","You are not logged in!");
    }
}
void Window::activateChat(QListWidgetItem *widget) {
    if(notifier->isEnabled() == true)
        notifier->setEnabled(false);
    chat.resetChatBox();
    if(startChat == false) {
        startChat = true;
        int option = 11;
        int nrBytes = send(socketDescriptor, &option, sizeof(int), MSG_NOSIGNAL);
        if (nrBytes < 0) {
            close(socketDescriptor);
            return;
        }
    }
    else
    {
        chat.getUi()->chatBox->clear();
        string change = "CHANGE_CHAT";
        sendMessage(change);
    }
    string username = widget->text().toStdString();
    sendMessage(username);
    int numberOfMessages;
    int nrBytes = recv(socketDescriptor,&numberOfMessages,sizeof(int),MSG_NOSIGNAL);
    if(nrBytes < 0)
    {
        close(socketDescriptor);
        return;
    }
    for(int i = 1; i <= numberOfMessages; i++)
    {
        string sender;
        receiveMessage(sender);
        string messageText;
        receiveMessage(messageText);
        if(sender == username)
            chat.addChatMessage(QString::fromStdString(messageText),'l');
        else
            chat.addChatMessage(QString::fromStdString(messageText),'r');
    }
    notifier->setEnabled(true);
}

void Window::receiveChatMessages()
{
    cerr<<"AFFAFFAF\n";
    string message;
    receiveMessage(message);
    chat.addChatMessage(QString::fromStdString(message),'l');

}
void Window::sendChatMessage()
{
    string text;
    text = chat.getUi()->messageText->toPlainText().toStdString();
    if(text != "")
    {
        chat.getUi()->messageText->clear();
        chat.addChatMessage(QString::fromStdString(text),'r');
        sendMessage(text);
    }

}
void Window::addUserPost() {
    string postText = post.getUi()->postTextEdit->toPlainText().toStdString();
    string status;
    if(postText.length() >= 600)
    {
        QMessageBox::warning(post.getUi()->postStatus,"Post too long","The post has to be less than 600 characters.");
    }
    else if(postText.length() == 0)
    {
        QMessageBox::warning(post.getUi()->postStatus,"Empty post","The post has to contain at least one character.");
    }
    else
    {
        int option = 9;
        int nrBytes = send(socketDescriptor,&option,sizeof(int),MSG_NOSIGNAL);
        if(nrBytes < 0)
        {
            close(socketDescriptor);
            return;
        }
        if(post.getUi()->publicStatus->isChecked() == true)
        {
            status = "Public";
        }
        else if(post.getUi()->friendsOnlyStatus->isChecked() == true)
        {
            status = "Friends-Only";
        }
        else if(post.getUi()->privateStatus->isChecked() == true)
        {
            status = "Private";
        }
        sendMessage(postText);
        sendMessage(status);
        post.getUi()->postTextEdit->clear();
        QMessageBox::warning(post.getUi()->postStatus,"Success","The post was created successfully");
        backFunction();
    }
}


void Window::sendMessage(std::string message) {
    cerr<<message<<'\n';
    int length = message.length();
    int nrBytes;
    nrBytes = send(socketDescriptor,&length,sizeof(int),MSG_NOSIGNAL);
    if(nrBytes < 0)
    {
        perror("[server]Error when sending message\n");
        return;

    }
    nrBytes = send(socketDescriptor,message.c_str(),length,MSG_NOSIGNAL);
    if(nrBytes < 0)
    {
        perror("[server]Error when sending message\n");
        return;
    }
}
void Window::receiveMessage(std::string &message) {
    int length;
    int nrBytes;
    nrBytes = recv(socketDescriptor,&length,sizeof(int),MSG_NOSIGNAL);
    if(nrBytes < 0)
    {
        perror("[server]Error when receiving message\n");
        return;
    }
    char *receiver = new char[length + 1]{};
    nrBytes = recv(socketDescriptor,receiver,length,MSG_NOSIGNAL);
    if(nrBytes < 0)
    {
        delete[] receiver;
        perror("[server]Error when receiving message\n");
        return;
    }
    message = receiver;
    delete[] receiver;
}

void Window::resetInformations() {
    if(notifier->isEnabled() == true)
        notifier->setEnabled(false);
    login.changeLoginLabelText("LOGIN");
    friends.changeFriendsLabel("FRIENDS");
    login.getUi()->usernameInsert->setText("");
    login.getUi()->passwordInsert->setText("");
    main.getUi()->nextPostButton->hide();
    main.getUi()->previousPostButton->hide();
    main.getUi()->postText->hide();
    main.getUi()->showPostsButton->show();
    chat.resetChatBox();
}
void Window::backFromChat()
{
    startChat = false;
    if(notifier->isEnabled() == true)
    {
        string done = "DONE_CHAT";
        sendMessage(done);
    }

    backFunction();
}
void Window::backFunction()
{
    resetInformations();
    main.show();
    login.hide();
    friends.resetList();
    friends.hide();
    post.hide();
    chat.hide();
}
void Window::setSocketDescriptor(int fd) {
    socketDescriptor = fd;
    notifier->setSocket(fd);
}
/*
void Window::chatFunctions()
{
    trimit_optiune ca dau chat
    primesc mesajele deja existente in baza de date
    creez un thread pt a primi toate mesajele care sunt trimise in momentul de fata
    //creez un thread ca sa trimit mesaje catre server
    while(true) -> update la fereastra de mesaje
}

void receiveFrom server
{
    while(true)
{
        select;
        update la string de mesaje cu mutex
}
};
*/