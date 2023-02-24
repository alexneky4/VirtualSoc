#include "createpost.h"
#include "./ui_createpost.h"

CreatePost::CreatePost(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreatePost)
{
    ui->setupUi(this);
}

CreatePost::~CreatePost()
{
    delete ui;
}

Ui::CreatePost* CreatePost::getUi()
{
    return ui;
}
