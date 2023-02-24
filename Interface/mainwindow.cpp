#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->nextPostButton->hide();
    ui->previousPostButton->hide();
    ui->postText->hide();
    connect(ui->nextPostButton,&QPushButton::clicked,this,&MainWindow::nextButton);
    connect(ui->previousPostButton,&QPushButton::clicked,this,&MainWindow::previousButton);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_MainWindow_iconSizeChanged(const QSize &iconSize)
{

}


Ui::MainWindow* MainWindow::getUi()
{
    return ui;
}

void MainWindow::displayPostText()
{
    QString currPostText = allPostsText[indexPost];
    if(indexPost == 0)
    {
        ui->previousPostButton->hide();
    }
    else
    {
         ui->previousPostButton->show();
    }
    if(indexPost == allPostsText.size() - 1)
    {
        ui->nextPostButton->hide();
    }
    else
    {
         ui->nextPostButton->show();
    }
    ui->postText->setText(currPostText);
}

void MainWindow::nextButton()
{

        indexPost++;
        displayPostText();
}

void MainWindow::previousButton()
{

        indexPost--;
        displayPostText();

}
void MainWindow::addPost(QString newPostText)
{
    allPostsText.push_back(newPostText);
}

void MainWindow::deletePostsAfter(int index) {
    allPostsText.erase(allPostsText.begin() + index - 1,allPostsText.end());
}
void MainWindow::clearPosts()
{
    allPostsText.clear();
}
void MainWindow::setCurrentText()
{
    if(allPostsText.size() == 0)
    {
        addPost("Hello");
        displayPostText();
    }
    else
    {
        displayPostText();
    }

}

