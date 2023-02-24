#ifndef FRIENDLIST_H
#define FRIENDLIST_H

#include <QMainWindow>
#include <iostream>
#include <vector>
#include <QListWidgetItem>

using namespace std;
namespace Ui {
class FriendList;
}

class FriendList : public QMainWindow
{
    Q_OBJECT

public:
    explicit FriendList(QWidget *parent = nullptr);
    ~FriendList();

    Ui::FriendList* getUi();
    void showFriendList(vector<QString> friends);
    void changeFriendsLabel(QString newText);
    QListWidget* getFriendRequests();
    void resetList();
private:
    Ui::FriendList *ui;
};

#endif // FRIENDLIST_H
