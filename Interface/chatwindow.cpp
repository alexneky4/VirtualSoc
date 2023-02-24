#include "chatwindow.h"
#include "./ui_chatwindow.h"
#include <QLabel>

ChatWindow::ChatWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

Ui::ChatWindow* ChatWindow::getUi()
{
    return ui;
}

void ChatWindow::addChatMessage(QString message,char align)
{
    if(numberOfMessages < 5)
    {
        chat.push_back(message);
        QListWidgetItem* item = new QListWidgetItem(ui->chatBox);
        item->setText(message);
        ui->chatBox->addItem(item);
        if(align == 'l')
        {
            item->setTextAlignment(Qt::AlignLeft);
        }
        else if(align == 'r')
        {
            item->setTextAlignment(Qt::AlignRight);
        }
        numberOfMessages++;
    }
    else
    {
        chat.erase(chat.begin());
        QListWidgetItem* deleteItem = ui->chatBox->takeItem(0);
        delete deleteItem;
        chat.push_back(message);
        QListWidgetItem* item = new QListWidgetItem(ui->chatBox);
        item->setText(message);
        ui->chatBox->addItem(item);
        if(align == 'l')
        {
            item->setTextAlignment(Qt::AlignLeft);
        }
        else if(align == 'r')
        {
            item->setTextAlignment(Qt::AlignRight);
        }
    }
}

void ChatWindow::resetChatBox()
{
    numberOfMessages = 0;
    ui->chatBox->clear();
}
