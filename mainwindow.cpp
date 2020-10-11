#include "mainwindow.h"
#include "ui_mainwindow.h"

//定义全局变量
bool start=0;
static int paint_flag = 0;
QPainter * paintmywindow;
MainWindow * app;
//初始化类,现在为初级
int ROW =9;
int COL =9;
int BOOMNUM = 10;
block * mine = new block(ROW,COL,BOOMNUM);
int click_x,click_y,end = 0,timeend=1;
int LENGTH=mine->getcol()*21;   //182
int HEIGHT=mine->getrow()*21 + TITILE_HEIGH;  //245
static bool showimage = 1;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //构建窗口大小
    app = this;
    ui->setupUi(this);
    this->setMinimumSize(LENGTH,HEIGHT);
    this->setMaximumSize(LENGTH,HEIGHT);
    ui->menuBar->hide();
    runtime = new QTimer(this);
    connect(runtime,SIGNAL(timeout()),this,SLOT(on_secondadd()));
    connect(runtime,SIGNAL(timeout()),this,SLOT(update()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
//鼠标事件
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(start==1){


   //用户鼠标点击，判断左右键，确定落点，修改块信息，确定是否结束
     click_x = event->x();
     click_y = event->y();
   //先判断是否点击了笑脸
     if(event->buttons()==(Qt::LeftButton)&&(click_x>(int)LENGTH*100/200-11)&&
             (click_x<(int)LENGTH*100/200+11 +EXPRESSION_LENGHT)&&(click_y>7+TTILE_BEGIN)&&
             (click_y<7+TTILE_BEGIN+EXPRESSION_HEIGH))
    {
     qDebug()<<"点击了笑脸";
     restart(mine->getrow(),mine->getcol(),mine->getboomNum());
     paint_flag = 0;
     end = 0;
     timeend = 1;
     runtime->stop();
     update();
     return;
    }
    else if( click_y<TITILE_HEIGH ) return;

    if(end==1)
    return ;
   //确定落点
    click_x = click_x/BLOCK_LENGTH;
    click_y = (click_y-TITILE_HEIGH)/BLOCK_HEIGH;
    if(event->buttons()==(Qt::LeftButton))
     {
         if(timeend==1)
         {
             runtime->start(1000);
         }
         if(mine->p[click_y][click_x]==99)
         {
            //若点击了炸弹,瞬间爆炸，结束游戏
             paint_flag = 4;
             end = 1;
             timeend=1;
             runtime->stop();
             update();

         }
         else if((mine->p[click_y][click_x]<10))
         {
             //需要递归遍历，更改类中信息
             showblock(click_y,click_x);
             paint_flag = 2;
             if(end = iswin()==1)
             {
                 paint_flag = 5;
                 timeend=1;
                 runtime->stop();
             }
             update();
             if(end)
         {
             if(showimage)
              {
                  QMessageBox message(QMessageBox::NoIcon, "游戏胜利", "恭喜你扫完了所有的雷 ");
                  message.setIconPixmap(QPixmap(":/new/prefix1/IMAGE/win.png"));
                  showimage = !showimage;
                  message.exec();
              }
             else
             {
                  QMessageBox message(QMessageBox::NoIcon, "游戏胜利", " 恭喜你又双叒叕赢得游戏 ");
                  message.setIconPixmap(QPixmap(":/new/prefix1/IMAGE/good.png"));
                  showimage = !showimage;
                  message.exec();
             }

         }
         }
          else return;

     }
    else if(event->buttons()==(Qt::RightButton))
     {
         //如果点击了右键
         if((mine->p[click_y][click_x]<10)||(mine->p[click_y][click_x]==99))
         {
             mine->p[click_y][click_x] = mine->p[click_y][click_x] +50;
             mine->minusredFlagNum();
         }
         else if((mine->p[click_y][click_x]>=50&&mine->p[click_y][click_x]<60)||(mine->p[click_y][click_x]>110))
         {
             mine->p[click_y][click_x] = mine->p[click_y][click_x] -50;
             mine->addredFlagNum();
         }
         paint_flag = 3;
         if(end = iswin()==1)
         {
             paint_flag = 5;
             timeend=1;
             runtime->stop();
         }
         update();
         if(end)
         {
             if(showimage)
              {
                  QMessageBox message(QMessageBox::NoIcon, "you are win", "very good, I really very appreciate you ");
                  message.setIconPixmap(QPixmap("win.png"));
                  showimage = !showimage;
                  message.exec();
              }
             else
             {
                  QMessageBox message(QMessageBox::NoIcon, "you are win", " I will give you a red flower ");
                  message.setIconPixmap(QPixmap("good.png"));
                  showimage = !showimage;
                  message.exec();
             }
         }
    }
}
}
//绘图事件
void MainWindow::paintEvent(QPaintEvent *event)
{
     QPainter painter(this);
     paintmywindow = &painter;
     //加载位图
     QPixmap mine_title(":/new/prefix1/IMAGE/mine_title.bmp");
     QPixmap block_close(":/new/prefix1/IMAGE/button1.png");
     QPixmap block_open(":/new/prefix1/IMAGE/block_open.bmp");
     QPixmap red_flag(":/new/prefix1/IMAGE/redflag.bmp");
     QPixmap keil_boom(":/new/prefix1/IMAGE/keilboom.bmp");
     QPixmap click_boom(":/new/prefix1/IMAGE/clickboom.bmp");
     QPixmap boom(":/new/prefix1/IMAGE/boom.bmp");
     QPixmap qq_smile(":/new/prefix1/IMAGE/smile.bmp");
     QPixmap qq_lose(":/new/prefix1/IMAGE/lose.bmp");
     QPixmap qq_pround(":/new/prefix1/IMAGE/proud.bmp");
     QPixmap ele_0(":/new/prefix1/IMAGE/ele0.bmp");
     QPixmap ele_1(":/new/prefix1/IMAGE/ele1.bmp");
     QPixmap ele_2(":/new/prefix1/IMAGE/ele2.bmp");
     QPixmap ele_3(":/new/prefix1/IMAGE/ele3.bmp");
     QPixmap ele_4(":/new/prefix1/IMAGE/ele4.bmp");
     QPixmap ele_5(":/new/prefix1/IMAGE/ele5.bmp");
     QPixmap ele_6(":/new/prefix1/IMAGE/ele6.bmp");
     QPixmap ele_7(":/new/prefix1/IMAGE/ele7.bmp");
     QPixmap ele_8(":/new/prefix1/IMAGE/ele8.bmp");
     QPixmap ele_9(":/new/prefix1/IMAGE/ele9.bmp");
     QPixmap ele_10(":/new/prefix1/IMAGE/ele10.bmp");
     QPixmap blk_1(":/new/prefix1/IMAGE/blk1.bmp");
     QPixmap blk_2(":/new/prefix1/IMAGE/blk2.bmp");
     QPixmap blk_3(":/new/prefix1/IMAGE/blk3.bmp");
     QPixmap blk_4(":/new/prefix1/IMAGE/blk4.bmp");
     QPixmap blk_5(":/new/prefix1/IMAGE/blk5.bmp");
     QPixmap blk_6(":/new/prefix1/IMAGE/blk6.bmp");
     QPixmap blk_7(":/new/prefix1/IMAGE/blk7.bmp");
     QPixmap blk_8(":/new/prefix1/IMAGE/字符8.bmp");


    //如果是第一次打开，则进行初始化
    if(paint_flag==0)
    {
        painttitle(paintmywindow);
        //绘制雷区
        for(int i = 0;i<mine->getcol()*BLOCK_LENGTH;i=i+BLOCK_LENGTH)
            for(int j =TITILE_HEIGH;j<TITILE_HEIGH+mine->getrow()*BLOCK_HEIGH;j=j+BLOCK_HEIGH)
              painter.drawPixmap(i,j,block_close,0,0,BLOCK_LENGTH,BLOCK_LENGTH);
    }
    //左键点到炸弹绘制
    else if (paint_flag == 4)
    {
        painttitle(paintmywindow);
        //绘制雷区
        for(int i = 0;i<mine->getrow();i++)
        {
            for(int j = 0;j<mine->getcol();j++ )
               {
                if((mine->p[i][j]<10))
                {
                    painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,block_close,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
                }
                else if((mine->p[i][j]==99))
                {
                    painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,boom,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
                }
                else if (mine->p[i][j]>110)
                {
                    painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,red_flag,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
                }
                else if ((mine->p[i][j]<60)&&(mine->p[i][j]>=50))
                {
                    painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,keil_boom,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
                }
                else if ((mine->p[i][j])>99&&(mine->p[i][j]<110))
                {
                   int blk_num = mine->p[i][j] - 100;
                   switch (blk_num)
                   {
                    case 0: painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,block_open,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                    case 1: painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_1,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                    case 2: painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_2,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                    case 3: painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_3,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                    case 4: painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_4,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                    case 5: painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_5,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                    case 6: painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_6,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                    case 7: painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_7,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                    case 8: painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_8,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                   }
                }
               }
            }
        //绘制点击的炸弹
        painter.drawPixmap(click_x*BLOCK_LENGTH,click_y*BLOCK_HEIGH+TITILE_HEIGH,click_boom,0,0,BLOCK_LENGTH,BLOCK_HEIGH);

     }
    //左键点到空白绘制
    else if (paint_flag == 2 )
    {
       //绘制标题
       painttitle(paintmywindow);
       //绘制雷区
       paintboom(paintmywindow);
    }
    //右键点击绘制
    else if(paint_flag ==3)
    {

        painttitle(paintmywindow);
        paintboom(paintmywindow);
    }
    //游戏成功结束
    else if(paint_flag == 5)
    {
        painttitle(paintmywindow);
        paintboom(paintmywindow);
    }
}

//左键遍历递归
void showblock(int x,int y)
{
    for(int blockRow = x - 1; blockRow <=x + 1;blockRow++)
        for(int blockCol = y - 1;blockCol <=y + 1;blockCol++)
        {
            if(blockRow<0||blockCol<0||blockRow>=mine->getrow()||blockCol>=mine->getcol())
               continue;
            if(mine->p[blockRow][blockCol]<10)
            {
                mine->p[blockRow][blockCol] =  mine->p[blockRow][blockCol] + 100;
                if(mine->p[blockRow][blockCol]==100)
                showblock(blockRow,blockCol);
            }
        }
}
//判断是否结束游戏
int iswin()
{
    int cnt = 0;
    for(int row = 0; row <mine->getrow();row++)
        for(int col =0;col<mine->getcol();col++)
        {
            if((mine->p[row][col]>=100)&&(mine->p[row][col]<110))
                cnt++;
        }
    if(cnt>=((mine->getcol()*mine->getrow())-mine->getboomNum()))
        return 1;
    else
        return 0;
}
//重新开始游戏
void restart(int row,int col,int boolnum)
{
    mine = new block (row,col,boolnum);
}
//绘制时间红旗数与标题
void painttitle(QPainter  * painter)
{
    //加载位图
    QPixmap mine_title(":/new/prefix1/IMAGE/mine_title.bmp");
    QPixmap block_close(":/new/prefix1/IMAGE/button1.png");
    QPixmap block_open(":/new/prefix1/IMAGE/block_open.bmp");
    QPixmap red_flag(":/new/prefix1/IMAGE/redflag.bmp");
    QPixmap keil_boom(":/new/prefix1/IMAGE/keilboom.bmp");
    QPixmap click_boom(":/new/prefix1/IMAGE/clickboom.bmp");
    QPixmap boom(":/new/prefix1/IMAGE/boom.bmp");
    QPixmap qq_smile(":/new/prefix1/IMAGE/smile.bmp");
    QPixmap qq_lose(":/new/prefix1/IMAGE/lose.bmp");
    QPixmap qq_pround(":/new/prefix1/IMAGE/proud.bmp");
    QPixmap ele_0(":/new/prefix1/IMAGE/ele0.bmp");
    QPixmap ele_1(":/new/prefix1/IMAGE/ele1.bmp");
    QPixmap ele_2(":/new/prefix1/IMAGE/ele2.bmp");
    QPixmap ele_3(":/new/prefix1/IMAGE/ele3.bmp");
    QPixmap ele_4(":/new/prefix1/IMAGE/ele4.bmp");
    QPixmap ele_5(":/new/prefix1/IMAGE/ele5.bmp");
    QPixmap ele_6(":/new/prefix1/IMAGE/ele6.bmp");
    QPixmap ele_7(":/new/prefix1/IMAGE/ele7.bmp");
    QPixmap ele_8(":/new/prefix1/IMAGE/ele8.bmp");
    QPixmap ele_9(":/new/prefix1/IMAGE/ele9.bmp");
    QPixmap blk_1(":/new/prefix1/IMAGE/blk1.bmp");
    QPixmap blk_2(":/new/prefix1/IMAGE/blk2.bmp");
    QPixmap blk_3(":/new/prefix1/IMAGE/blk3.bmp");
    QPixmap blk_4(":/new/prefix1/IMAGE/blk4.bmp");
    QPixmap blk_5(":/new/prefix1/IMAGE/blk5.bmp");
    QPixmap blk_6(":/new/prefix1/IMAGE/blk6.bmp");
    QPixmap blk_7(":/new/prefix1/IMAGE/blk7.bmp");
    QPixmap blk_8(":/new/prefix1/IMAGE/字符8.bmp");
    QPixmap ele_10(":/new/prefix1/IMAGE/ele10.bmp");

    //调整大小
    mine_title = mine_title.scaled(QSize(LENGTH,40));

    //显示标题部分
    painter->drawPixmap(0,TTILE_BEGIN,mine_title,0,0,1000,1000);
    if(paint_flag == 4)
    painter->drawPixmap((int)LENGTH*100/200-11,7+TTILE_BEGIN,qq_lose,0,0,1000,1000);
    else if (paint_flag == 5)
    painter->drawPixmap((int)LENGTH*100/200-11,7+TTILE_BEGIN,qq_pround,0,0,1000,1000);
    else
    painter->drawPixmap((int)LENGTH*100/200-11,7+TTILE_BEGIN,qq_smile,0,0,1000,1000);

    //显示红旗数量
    int redflagnum = mine->getredFlagNum();
    if(redflagnum<0)
    {
        redflagnum = -redflagnum;
        painter->drawPixmap((int)(LENGTH*40)/200-30,5+TTILE_BEGIN,ele_10,0,0,1000,1000);
    }
    else painter->drawPixmap((int)(LENGTH*40)/200-30,5+TTILE_BEGIN,ele_0,0,0,1000,1000);
    switch(redflagnum/10)
    {
    case 0:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_0,0,0,1000,1000);break;
    case 1:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_1,0,0,1000,1000);break;
    case 2:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_2,0,0,1000,1000);break;
    case 3:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_3,0,0,1000,1000);break;
    case 4:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_4,0,0,1000,1000);break;
    case 5:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_5,0,0,1000,1000);break;
    case 6:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_6,0,0,1000,1000);break;
    case 7:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_7,0,0,1000,1000);break;
    case 8:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_8,0,0,1000,1000);break;
    case 9:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_9,0,0,1000,1000);break;
    }
    switch (redflagnum%10)
    {
    case 0:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_0,0,0,1000,1000);break;
    case 1:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_1,0,0,1000,1000);break;
    case 2:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_2,0,0,1000,1000);break;
    case 3:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_3,0,0,1000,1000);break;
    case 4:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_4,0,0,1000,1000);break;
    case 5:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_5,0,0,1000,1000);break;
    case 6:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_6,0,0,1000,1000);break;
    case 7:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_7,0,0,1000,1000);break;
    case 8:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_8,0,0,1000,1000);break;
    case 9:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_9,0,0,1000,1000);break;
    }

    //显示时间
    int timenum = mine->gettimeNum();
    switch  (timenum/100)
    {
    case 0:  painter->drawPixmap((int)(LENGTH*163)/200-30,5+TTILE_BEGIN,ele_0,0,0,1000,1000);break;
    case 1:  painter->drawPixmap((int)(LENGTH*163)/200-30,5+TTILE_BEGIN,ele_1,0,0,1000,1000);break;
    case 2:  painter->drawPixmap((int)(LENGTH*163)/200-30,5+TTILE_BEGIN,ele_2,0,0,1000,1000);break;
    case 3:  painter->drawPixmap((int)(LENGTH*163)/200-30,5+TTILE_BEGIN,ele_3,0,0,1000,1000);break;
    case 4:  painter->drawPixmap((int)(LENGTH*163)/200-30,5+TTILE_BEGIN,ele_4,0,0,1000,1000);break;
    case 5:  painter->drawPixmap((int)(LENGTH*163)/200-30,5+TTILE_BEGIN,ele_5,0,0,1000,1000);break;
    case 6:  painter->drawPixmap((int)(LENGTH*163)/200-30,5+TTILE_BEGIN,ele_6,0,0,1000,1000);break;
    case 7:  painter->drawPixmap((int)(LENGTH*163)/200-30,5+TTILE_BEGIN,ele_7,0,0,1000,1000);break;
    case 8:  painter->drawPixmap((int)(LENGTH*163)/200-30,5+TTILE_BEGIN,ele_8,0,0,1000,1000);break;
    case 9:  painter->drawPixmap((int)(LENGTH*163)/200-30,5+TTILE_BEGIN,ele_9,0,0,1000,1000);break;
    }
    switch  (timenum/10)
    {
    case 0:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_0,0,0,1000,1000);break;
    case 1:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_1,0,0,1000,1000);break;
    case 2:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_2,0,0,1000,1000);break;
    case 3:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_3,0,0,1000,1000);break;
    case 4:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_4,0,0,1000,1000);break;
    case 5:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_5,0,0,1000,1000);break;
    case 6:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_6,0,0,1000,1000);break;
    case 7:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_7,0,0,1000,1000);break;
    case 8:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_8,0,0,1000,1000);break;
    case 9:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_9,0,0,1000,1000);break;
    }
    switch  (timenum%10)
    {
    case 0:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_0,0,0,1000,1000);break;
    case 1:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_1,0,0,1000,1000);break;
    case 2:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_2,0,0,1000,1000);break;
    case 3:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_3,0,0,1000,1000);break;
    case 4:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_4,0,0,1000,1000);break;
    case 5:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_5,0,0,1000,1000);break;
    case 6:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_6,0,0,1000,1000);break;
    case 7:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_7,0,0,1000,1000);break;
    case 8:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_8,0,0,1000,1000);break;
    case 9:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_9,0,0,1000,1000);break;
    }

}
//绘制正常鼠标点击事件与结束的雷区
void paintboom(QPainter * painter)
{
    //加载位图
    QPixmap mine_title(":/new/prefix1/IMAGE/mine_title.bmp");
    QPixmap block_close(":/new/prefix1/IMAGE/button1.png");
    QPixmap block_open(":/new/prefix1/IMAGE/block_open.bmp");
    QPixmap red_flag(":/new/prefix1/IMAGE/redflag.bmp");
    QPixmap keil_boom(":/new/prefix1/IMAGE/keilboom.bmp");
    QPixmap click_boom(":/new/prefix1/IMAGE/clickboom.bmp");
    QPixmap boom(":/new/prefix1/IMAGE/boom.bmp");
    QPixmap qq_smile(":/new/prefix1/IMAGE/smile.bmp");
    QPixmap qq_lose(":/new/prefix1/IMAGE/lose.bmp");
    QPixmap qq_pround(":/new/prefix1/IMAGE/proud.bmp");
    QPixmap ele_0(":/new/prefix1/IMAGE/ele0.bmp");
    QPixmap ele_1(":/new/prefix1/IMAGE/ele1.bmp");
    QPixmap ele_2(":/new/prefix1/IMAGE/ele2.bmp");
    QPixmap ele_3(":/new/prefix1/IMAGE/ele3.bmp");
    QPixmap ele_4(":/new/prefix1/IMAGE/ele4.bmp");
    QPixmap ele_5(":/new/prefix1/IMAGE/ele5.bmp");
    QPixmap ele_6(":/new/prefix1/IMAGE/ele6.bmp");
    QPixmap ele_7(":/new/prefix1/IMAGE/ele7.bmp");
    QPixmap ele_8(":/new/prefix1/IMAGE/ele8.bmp");
    QPixmap ele_9(":/new/prefix1/IMAGE/ele9.bmp");
    QPixmap blk_1(":/new/prefix1/IMAGE/blk1.bmp");
    QPixmap blk_2(":/new/prefix1/IMAGE/blk2.bmp");
    QPixmap blk_3(":/new/prefix1/IMAGE/blk3.bmp");
    QPixmap blk_4(":/new/prefix1/IMAGE/blk4.bmp");
    QPixmap blk_5(":/new/prefix1/IMAGE/blk5.bmp");
    QPixmap blk_6(":/new/prefix1/IMAGE/blk6.bmp");
    QPixmap blk_7(":/new/prefix1/IMAGE/blk7.bmp");
    QPixmap blk_8(":/new/prefix1/IMAGE/字符8.bmp");
    QPixmap ele_10(":/new/prefix1/IMAGE/ele10.bmp");


    for(int i = 0;i<mine->getrow();i++)
    {
        for(int j = 0;j<mine->getcol();j++ )
           {

            if((mine->p[i][j]<10)||(mine->p[i][j]==99))
            {
                painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,block_close,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
            }
            else if (((mine->p[i][j]<60)&&(mine->p[i][j]>=50))||(mine->p[i][j]>120))
            {
                painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,red_flag,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
            }
            else if ((mine->p[i][j]>99)&&(mine->p[i][j]<110))
            {
               int blk_num = mine->p[i][j] - 100;
               switch (blk_num)
               {
                case 0: painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,block_open,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                case 1: painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_1,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                case 2: painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_2,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                case 3: painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_3,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                case 4: painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_4,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                case 5: painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_5,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                case 6: painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_6,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                case 7: painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_7,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                case 8: painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_8,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
               }
            }
           }
     }
}
//计时器槽函数
void MainWindow::on_secondadd()   //点击开始计算秒数
{
    mine->addtimeNum();
}

void MainWindow::on_actionPrimary_triggered()   //9*9，10颗雷，低等难度
{
    end =0;
    timeend =1;
    mine = new block(9,9,10);
    LENGTH=mine->getcol()*21;
    HEIGHT=mine->getrow()*21 + TITILE_HEIGH;
    this->setMinimumSize(LENGTH,HEIGHT);
    this->setMaximumSize(LENGTH,HEIGHT);
}

void MainWindow::on_actionMiddle_triggered()    //16*16，40颗雷，中等难度
{
    end =0;
    timeend =1;
    mine = new block(16,16,40);
    LENGTH=mine->getcol()*21;
    HEIGHT=mine->getrow()*21 + TITILE_HEIGH;
    this->setMinimumSize(LENGTH,HEIGHT);
    this->setMaximumSize(LENGTH,HEIGHT);
}

void MainWindow::on_actionSenior_triggered()  //16*30，99颗雷，最高难度
{
    end =0;
    timeend =1;
    mine = new block(16,30,99);
    LENGTH=mine->getcol()*21;
    HEIGHT=mine->getrow()*21 + TITILE_HEIGH;
    this->setMinimumSize(LENGTH,HEIGHT);
    this->setMaximumSize(LENGTH,HEIGHT);
}

void MainWindow::on_actionQuit_triggered() //退出游戏
{
    QApplication::quit();
}

void MainWindow::on_actionUser_defined_triggered()   //弹出dialog自定义大小
{
    useDefineWindows = new Dialog(this);
    useDefineWindows->show();

}
void createinterface()//自定义的大小
{
    end =0;
    timeend =1;
    mine = new block(ROW,COL,BOOMNUM);
    LENGTH=mine->getcol()*21;
    HEIGHT=mine->getrow()*21 + TITILE_HEIGH;
    app->setMinimumSize(LENGTH,HEIGHT);
    app->setMaximumSize(LENGTH,HEIGHT);
}

void MainWindow::on_actionHelp_triggered()
{
    QMessageBox message(QMessageBox::NoIcon, "NO HELP", "随缘点就可以了 ");
    message.setIconPixmap(QPixmap(":/new/prefix1/IMAGE/unknow.png"));
    message.exec();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox message(QMessageBox::NoIcon, "居然真的有人好奇作者", "此时一位靓仔留下了背影转身离去");
    message.setIconPixmap(QPixmap(":/new/prefix1/IMAGE/agree.png"));
    message.exec();
}

void MainWindow::on_actionHow_to_play_triggered()
{
    QMessageBox message(QMessageBox::NoIcon, "so easy", "");
    message.setIconPixmap(QPixmap(":/new/prefix1/IMAGE/baidu.png"));
    message.exec();
}
void MainWindow::on_action2p_triggered()
{  this->hide();
   w2.show();
   w2.setWindowTitle("扫雷双人模式");
}


void MainWindow::on_pushButton_clicked()
{
    ui->widget->hide();
    ui->menuBar->show();
    start=1;
}

void MainWindow::on_pushButton_2_clicked()
{
    this->close();
}
