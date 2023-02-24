#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow* getUi();
    void addPost(QString newPostText);
    void deletePostsAfter(int index);
    void setCurrentText();
    void clearPosts();
private:
    void displayPostText();

private slots:
    void on_MainWindow_iconSizeChanged(const QSize &iconSize);
    void nextButton();
    void previousButton();

private:
    Ui::MainWindow *ui;
    vector<QString> allPostsText;
    int indexPost;
};
#endif // MAINWINDOW_H
