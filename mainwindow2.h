#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H

#include <QMainWindow>
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include <block.h>
#include <QTimer>
#include <QMessageBox>
#include <qmessagebox.h>
#include <qlabel.h>
#include <QLabel>

//定义常量
#define BLOCK_LENGTH 21
#define BLOCK_HEIGH 21
#define ELENUM_LENGHT 20
#define EXPRESSION_LENGHT 24
#define EXPRESSION_HEIGH 24
#define TTILE_BEGIN 23
#define TITILE_HEIGH  (TTILE_BEGIN+40)
#define PRIMARY_LENGTH  189
#define MIDDLE_LENGTH   336
#define TOP_LENGTH      630

namespace Ui {
class MainWindow2;
}

class MainWindow2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow2(QWidget *parent = 0);
    ~MainWindow2();

private:
    Ui::MainWindow2 *ui;
    QTimer * runtime;

    //---------------------label
    QLabel *playerpoint;
    QLabel *player1_score;
    QLabel *player2_score;
protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
private slots:
    void on_secondadd();

    //-----------rules test
    void showrules();


};
void showblock2(int x,int y);
int iswin2();
void restart2(int row,int col,int boolnum);
void painttitle2(QPainter * painter);
void paintboom2(QPainter * painter);


#endif // MAINWINDOW2_H
