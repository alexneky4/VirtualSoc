/********************************************************************************
** Form generated from reading UI file 'friendlist.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRIENDLIST_H
#define UI_FRIENDLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FriendList
{
public:
    QWidget *centralwidget;
    QLabel *friendsLabel;
    QListWidget *friendsList;
    QPushButton *backButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *FriendList)
    {
        if (FriendList->objectName().isEmpty())
            FriendList->setObjectName("FriendList");
        FriendList->resize(820, 377);
        centralwidget = new QWidget(FriendList);
        centralwidget->setObjectName("centralwidget");
        friendsLabel = new QLabel(centralwidget);
        friendsLabel->setObjectName("friendsLabel");
        friendsLabel->setGeometry(QRect(210, 10, 381, 61));
        QFont font;
        font.setPointSize(24);
        font.setBold(true);
        friendsLabel->setFont(font);
        friendsLabel->setAlignment(Qt::AlignCenter);
        friendsList = new QListWidget(centralwidget);
        friendsList->setObjectName("friendsList");
        friendsList->setGeometry(QRect(140, 70, 541, 231));
        backButton = new QPushButton(centralwidget);
        backButton->setObjectName("backButton");
        backButton->setGeometry(QRect(10, 10, 80, 23));
        QFont font1;
        font1.setBold(true);
        backButton->setFont(font1);
        FriendList->setCentralWidget(centralwidget);
        menubar = new QMenuBar(FriendList);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 820, 20));
        FriendList->setMenuBar(menubar);
        statusbar = new QStatusBar(FriendList);
        statusbar->setObjectName("statusbar");
        FriendList->setStatusBar(statusbar);

        retranslateUi(FriendList);

        friendsList->setCurrentRow(-1);


        QMetaObject::connectSlotsByName(FriendList);
    } // setupUi

    void retranslateUi(QMainWindow *FriendList)
    {
        FriendList->setWindowTitle(QCoreApplication::translate("FriendList", "MainWindow", nullptr));
        friendsLabel->setText(QCoreApplication::translate("FriendList", "FRIENDS", nullptr));
        backButton->setText(QCoreApplication::translate("FriendList", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FriendList: public Ui_FriendList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRIENDLIST_H
