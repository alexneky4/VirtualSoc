/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *loginButton;
    QPushButton *registerButton;
    QPushButton *friendsButton;
    QPushButton *friendsRequestButton;
    QPushButton *createPostButton;
    QPushButton *chatButton;
    QPushButton *previousPostButton;
    QPushButton *nextPostButton;
    QLabel *postText;
    QPushButton *otherUsersButton;
    QPushButton *showPostsButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(936, 369);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        loginButton = new QPushButton(centralwidget);
        loginButton->setObjectName("loginButton");
        loginButton->setGeometry(QRect(620, 10, 121, 51));
        registerButton = new QPushButton(centralwidget);
        registerButton->setObjectName("registerButton");
        registerButton->setGeometry(QRect(770, 10, 131, 51));
        friendsButton = new QPushButton(centralwidget);
        friendsButton->setObjectName("friendsButton");
        friendsButton->setGeometry(QRect(20, 30, 121, 51));
        friendsRequestButton = new QPushButton(centralwidget);
        friendsRequestButton->setObjectName("friendsRequestButton");
        friendsRequestButton->setGeometry(QRect(20, 90, 121, 51));
        createPostButton = new QPushButton(centralwidget);
        createPostButton->setObjectName("createPostButton");
        createPostButton->setGeometry(QRect(20, 210, 121, 51));
        chatButton = new QPushButton(centralwidget);
        chatButton->setObjectName("chatButton");
        chatButton->setGeometry(QRect(20, 270, 121, 51));
        previousPostButton = new QPushButton(centralwidget);
        previousPostButton->setObjectName("previousPostButton");
        previousPostButton->setGeometry(QRect(210, 220, 101, 41));
        nextPostButton = new QPushButton(centralwidget);
        nextPostButton->setObjectName("nextPostButton");
        nextPostButton->setGeometry(QRect(700, 220, 111, 41));
        postText = new QLabel(centralwidget);
        postText->setObjectName("postText");
        postText->setGeometry(QRect(220, 70, 601, 131));
        QPalette palette;
        QBrush brush(QColor(198, 70, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Link, brush);
        QBrush brush1(QColor(0, 0, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Inactive, QPalette::Link, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Link, brush1);
        postText->setPalette(palette);
        otherUsersButton = new QPushButton(centralwidget);
        otherUsersButton->setObjectName("otherUsersButton");
        otherUsersButton->setGeometry(QRect(20, 150, 121, 51));
        showPostsButton = new QPushButton(centralwidget);
        showPostsButton->setObjectName("showPostsButton");
        showPostsButton->setGeometry(QRect(440, 270, 91, 31));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 936, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        loginButton->setText(QCoreApplication::translate("MainWindow", "Login", nullptr));
        registerButton->setText(QCoreApplication::translate("MainWindow", "Register", nullptr));
        friendsButton->setText(QCoreApplication::translate("MainWindow", "Friends", nullptr));
        friendsRequestButton->setText(QCoreApplication::translate("MainWindow", "Friends Requests", nullptr));
        createPostButton->setText(QCoreApplication::translate("MainWindow", "Create Post", nullptr));
        chatButton->setText(QCoreApplication::translate("MainWindow", "Chat", nullptr));
        previousPostButton->setText(QCoreApplication::translate("MainWindow", "Previous", nullptr));
        nextPostButton->setText(QCoreApplication::translate("MainWindow", "Next", nullptr));
        postText->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        otherUsersButton->setText(QCoreApplication::translate("MainWindow", "Other Users", nullptr));
        showPostsButton->setText(QCoreApplication::translate("MainWindow", "Show Posts", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
