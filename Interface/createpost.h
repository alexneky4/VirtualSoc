#ifndef CREATEPOST_H
#define CREATEPOST_H

#include <QMainWindow>

namespace Ui {
class CreatePost;
}

class CreatePost : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreatePost(QWidget *parent = nullptr);
    ~CreatePost();
    Ui::CreatePost* getUi();

private:
    Ui::CreatePost *ui;
};

#endif // CREATEPOST_H
