#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include <vector>

using namespace std;

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QMainWindow
{
    Q_OBJECT
private:
    vector<QString> chat;
    int numberOfMessages=0;

public:
    explicit ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow();
    Ui::ChatWindow* getUi();
    void resetChatBox();
    void addChatMessage(QString message,char align);
private:
    Ui::ChatWindow *ui;
};

#endif // CHATWINDOW_H
