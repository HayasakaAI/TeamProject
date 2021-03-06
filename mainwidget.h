#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

namespace Ui {
class mainwidget;
}

class mainwidget : public QWidget
{
    Q_OBJECT

public:
    explicit mainwidget(QWidget *parent = 0);
    ~mainwidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::mainwidget *ui;
};

#endif // MAINWIDGET_H
