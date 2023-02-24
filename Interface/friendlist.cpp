#include "friendlist.h"
#include "./ui_friendlist.h"
#include <QDialog>
#include <QPushButton>
#include <QHBoxLayout>

FriendList::FriendList(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FriendList)
{
    ui->setupUi(this);

}

FriendList::~FriendList()
{
    delete ui;
}

Ui::FriendList* FriendList::getUi()
{
    return ui;
}
void FriendList::showFriendList(vector<QString> friends)
{
    for(QString friendUser : friends)
    {
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(friendUser);
        ui->friendsList->addItem(item);
    }
}

void FriendList::changeFriendsLabel(QString newText)
{
    ui->friendsLabel->setText(newText);
}

QListWidget* FriendList::getFriendRequests()
{
    return ui->friendsList;
}

void FriendList::resetList() {
    ui->friendsList->clear();
}