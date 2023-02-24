/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QWidget *centralwidget;
    QLabel *LoginLabel;
    QLabel *usernameLabel;
    QLabel *passwordLabel;
    QLineEdit *usernameInsert;
    QLineEdit *passwordInsert;
    QPushButton *submitButton;
    QPushButton *backButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName("LoginWindow");
        LoginWindow->resize(829, 395);
        centralwidget = new QWidget(LoginWindow);
        centralwidget->setObjectName("centralwidget");
        LoginLabel = new QLabel(centralwidget);
        LoginLabel->setObjectName("LoginLabel");
        LoginLabel->setGeometry(QRect(320, 10, 231, 51));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        LoginLabel->setFont(font);
        LoginLabel->setScaledContents(false);
        LoginLabel->setAlignment(Qt::AlignCenter);
        LoginLabel->setWordWrap(false);
        LoginLabel->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
        usernameLabel = new QLabel(centralwidget);
        usernameLabel->setObjectName("usernameLabel");
        usernameLabel->setGeometry(QRect(230, 100, 111, 41));
        passwordLabel = new QLabel(centralwidget);
        passwordLabel->setObjectName("passwordLabel");
        passwordLabel->setGeometry(QRect(230, 160, 91, 31));
        usernameInsert = new QLineEdit(centralwidget);
        usernameInsert->setObjectName("usernameInsert");
        usernameInsert->setGeometry(QRect(320, 110, 171, 22));
        passwordInsert = new QLineEdit(centralwidget);
        passwordInsert->setObjectName("passwordInsert");
        passwordInsert->setGeometry(QRect(320, 170, 171, 22));
        passwordInsert->setEchoMode(QLineEdit::Password);
        submitButton = new QPushButton(centralwidget);
        submitButton->setObjectName("submitButton");
        submitButton->setGeometry(QRect(360, 230, 101, 31));
        backButton = new QPushButton(centralwidget);
        backButton->setObjectName("backButton");
        backButton->setGeometry(QRect(10, 10, 80, 23));
        QFont font1;
        font1.setBold(true);
        backButton->setFont(font1);
        LoginWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(LoginWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 829, 20));
        LoginWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(LoginWindow);
        statusbar->setObjectName("statusbar");
        LoginWindow->setStatusBar(statusbar);

        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QMainWindow *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "MainWindow", nullptr));
        LoginLabel->setText(QCoreApplication::translate("LoginWindow", "LOGIN", nullptr));
        usernameLabel->setText(QCoreApplication::translate("LoginWindow", "Username", nullptr));
        passwordLabel->setText(QCoreApplication::translate("LoginWindow", "Password", nullptr));
        passwordInsert->setText(QString());
        submitButton->setText(QCoreApplication::translate("LoginWindow", "Submit", nullptr));
        backButton->setText(QCoreApplication::translate("LoginWindow", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
