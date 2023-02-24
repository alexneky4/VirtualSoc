#include "loginwindow.h"
#include "./ui_loginwindow.h"
#include <string>
#include <QDialog>
#include <QVBoxLayout>

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::changeLoginLabelText(QString newText)
{
    ui->LoginLabel->setText(newText);
}

Ui::LoginWindow* LoginWindow::getUi()
{
    return ui;
}

