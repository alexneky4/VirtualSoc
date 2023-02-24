/********************************************************************************
** Form generated from reading UI file 'createpost.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEPOST_H
#define UI_CREATEPOST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CreatePost
{
public:
    QWidget *centralwidget;
    QLabel *createPostLabel;
    QTextEdit *postTextEdit;
    QGroupBox *postStatus;
    QRadioButton *publicStatus;
    QRadioButton *privateStatus;
    QRadioButton *friendsOnlyStatus;
    QPushButton *submitButton;
    QPushButton *backButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CreatePost)
    {
        if (CreatePost->objectName().isEmpty())
            CreatePost->setObjectName("CreatePost");
        CreatePost->resize(836, 400);
        centralwidget = new QWidget(CreatePost);
        centralwidget->setObjectName("centralwidget");
        createPostLabel = new QLabel(centralwidget);
        createPostLabel->setObjectName("createPostLabel");
        createPostLabel->setGeometry(QRect(230, 20, 331, 61));
        QFont font;
        font.setPointSize(24);
        font.setBold(true);
        createPostLabel->setFont(font);
        createPostLabel->setAlignment(Qt::AlignCenter);
        postTextEdit = new QTextEdit(centralwidget);
        postTextEdit->setObjectName("postTextEdit");
        postTextEdit->setGeometry(QRect(90, 90, 651, 81));
        postStatus = new QGroupBox(centralwidget);
        postStatus->setObjectName("postStatus");
        postStatus->setGeometry(QRect(190, 190, 501, 61));
        publicStatus = new QRadioButton(postStatus);
        publicStatus->setObjectName("publicStatus");
        publicStatus->setGeometry(QRect(20, 30, 100, 21));
        privateStatus = new QRadioButton(postStatus);
        privateStatus->setObjectName("privateStatus");
        privateStatus->setGeometry(QRect(290, 30, 100, 21));
        friendsOnlyStatus = new QRadioButton(postStatus);
        friendsOnlyStatus->setObjectName("friendsOnlyStatus");
        friendsOnlyStatus->setGeometry(QRect(150, 30, 100, 21));
        submitButton = new QPushButton(centralwidget);
        submitButton->setObjectName("submitButton");
        submitButton->setGeometry(QRect(360, 270, 121, 31));
        backButton = new QPushButton(centralwidget);
        backButton->setObjectName("backButton");
        backButton->setGeometry(QRect(10, 10, 80, 23));
        QFont font1;
        font1.setBold(true);
        backButton->setFont(font1);
        CreatePost->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CreatePost);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 836, 20));
        CreatePost->setMenuBar(menubar);
        statusbar = new QStatusBar(CreatePost);
        statusbar->setObjectName("statusbar");
        CreatePost->setStatusBar(statusbar);

        retranslateUi(CreatePost);

        QMetaObject::connectSlotsByName(CreatePost);
    } // setupUi

    void retranslateUi(QMainWindow *CreatePost)
    {
        CreatePost->setWindowTitle(QCoreApplication::translate("CreatePost", "MainWindow", nullptr));
        createPostLabel->setText(QCoreApplication::translate("CreatePost", "CREATE POST", nullptr));
        postTextEdit->setHtml(QCoreApplication::translate("CreatePost", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        postStatus->setTitle(QCoreApplication::translate("CreatePost", "Status", nullptr));
        publicStatus->setText(QCoreApplication::translate("CreatePost", "Public", nullptr));
        privateStatus->setText(QCoreApplication::translate("CreatePost", "Private", nullptr));
        friendsOnlyStatus->setText(QCoreApplication::translate("CreatePost", "Friends-Only", nullptr));
        submitButton->setText(QCoreApplication::translate("CreatePost", "Submit", nullptr));
        backButton->setText(QCoreApplication::translate("CreatePost", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreatePost: public Ui_CreatePost {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEPOST_H
