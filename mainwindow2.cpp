#include "mainwindow2.h"
#include "ui_mainwindow2.h"
//定义全局变量
static int paint_flag = 0;
QPainter * paintmywindow2;
MainWindow2 * app2;
//初始化类,现在为初级
int ROW2 =9;
int COL2 =9;
int BOOMNUM2 = 10;
block * mine2 = new block(ROW2,COL2,BOOMNUM2);
int click_x2,click_y2,end2 = 0,timeend2=1;
int LENGTH2=mine2->getcol()*21;
int HEIGHT2=mine2->getrow()*21 + TITILE_HEIGH+50;
static bool showimage = 1;
int p1point=0;
int p2point=0;
bool player=0;

MainWindow2::MainWindow2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow2)
{

    //构建窗口大小
    app2 = this;
    ui->setupUi(this);
    this->setMinimumSize(LENGTH2,HEIGHT2+50);
    this->setMaximumSize(LENGTH2,HEIGHT2+50);
    runtime = new QTimer(this);
    connect(runtime,SIGNAL(timeout()),this,SLOT(on_secondadd()));
    connect(runtime,SIGNAL(timeout()),this,SLOT(update()));

    //-------------------------------------------设定label标签
    playerpoint=new QLabel("p1点击");
    playerpoint->setGeometry(LENGTH2/2-10,HEIGHT2-50,100,30);
    playerpoint->setParent(this);
    player1_score=new QLabel("p1玩家分数：");
    player1_score->setGeometry((LENGTH2*40)/200-30,HEIGHT2-35,100,30);
    player1_score->setParent(this);
    player2_score=new QLabel("p2玩家分数：");
    player2_score->setGeometry((LENGTH2*163)/200-30-ELENUM_LENGHT,HEIGHT2-35,100,30);
    player2_score->setParent(this);

    connect(ui->Ui_MainWindow2::action,SIGNAL(triggered(bool)),this,SLOT(showrules()));

}

//-------------------------游戏规则
void MainWindow2::showrules(){
    QMessageBox message(QMessageBox::NoIcon, "帮助文档", "双人扫雷游戏规则：\n两名玩家按照p1p2的顺序轮流通过鼠标对同一游戏区域进行扫雷，点击鼠标即轮换对手回合。玩家可以通过左键打开安全的格或右键插旗排雷获得分数，最终得分最高者获胜。\n具体得分规则：若玩家A点击普通格子，则获得1分；若点击炸弹，直接判定对手胜利；\n双方均可使用红旗进行排雷操作，但总旗数固定，每轮仅可使用一次，且可拔除场上已有的旗。\n若玩家A在雷区正确插旗，则获得2分，若在普通格子插旗则判定排雷失败，对手加1分；\n若玩家A拔除区域内排雷失败的旗子，则获得1分；但若拔除正确排雷的旗子则对手加2分；");
    //message.setIconPixmap(QPixmap(":/new/prefix1/IMAGE/unknow.png"));
    //message.resize(1920,1080);
    message.exec();
}


MainWindow2::~MainWindow2()
{
    delete ui;
}
//鼠标事件
void MainWindow2::mousePressEvent(QMouseEvent *event)
{


   //用户鼠标点击，判断左右键，确定落点，修改块信息，确定是否结束
     click_x2 = event->x();
     click_y2 = event->y();
   //先判断是否点击了笑脸
     if(event->buttons()==(Qt::LeftButton)&&(click_x2>(int)LENGTH2*100/200-11)&&
             (click_x2<(int)LENGTH2*100/200+11 +EXPRESSION_LENGHT)&&(click_y2>7+TTILE_BEGIN)&&  //笑脸所在区域
             (click_y2<7+TTILE_BEGIN+EXPRESSION_HEIGH))
    {
     qDebug()<<"点击了笑脸";
     restart2(mine2->getrow(),mine2->getcol(),mine2->getboomNum());
     paint_flag = 0;
     end2 = 0;
     timeend2 = 1;
     p1point=0;
     p2point=0;
     player=0;
     playerpoint->setText("p1点击");
     runtime->stop();
     update();
     return;
    }
    else if( click_y2<TITILE_HEIGH||click_y2>HEIGHT2-50 ) return;

    if(end2==1)
    return ;
   //确定落点
    click_x2 = click_x2/BLOCK_LENGTH;  //第x行
    click_y2 = (click_y2-TITILE_HEIGH)/BLOCK_HEIGH; //第y列
    if(event->buttons()==(Qt::LeftButton))  //左键点击
     {
         if(timeend2==1)
         {
             runtime->start(1000);
         }
         if(mine2->p[click_y2][click_x2]==99)
         {
            //若点击了炸弹,瞬间爆炸，结束游戏
             paint_flag = 4;
             end2 = 1;
             timeend2=1;
             runtime->stop();
             update();
             if(player==1){
                 QMessageBox message(QMessageBox::NoIcon, "p2踩雷", "p1胜利 ");
                 message.setIconPixmap(QPixmap(":/new/prefix1/IMAGE/lose.bmp"));

                 message.exec();
             }
            else if(player==0){
                 QMessageBox message(QMessageBox::NoIcon, "p1踩雷", "p2胜利 ");
                 message.setIconPixmap(QPixmap(":/new/prefix1/IMAGE/lose.bmp"));

                 message.exec();
             }
         }
         else if((mine2->p[click_y2][click_x2]<10))
         {
             //需要递归遍历，更改类中信息
             showblock2(click_y2,click_x2);
             paint_flag = 2;
             if(player==0){p1point=p1point+1;}
             if(player==1){p2point=p2point+1;}
             if(end2 = iswin2()==1)
             {
                 paint_flag = 5;
                 timeend2=1;
                 runtime->stop();

             }
             update();
             if(end2)
         {
             if(p1point>p2point)
              {
                  QMessageBox message(QMessageBox::NoIcon, "游戏胜利", "p1胜利 ");
                  message.setIconPixmap(QPixmap(":/new/prefix1/IMAGE/win.png"));

                  message.exec();
              }
             if(p1point<p2point)
             {
                  QMessageBox message(QMessageBox::NoIcon, "游戏胜利", " p2胜利 ");
                  message.setIconPixmap(QPixmap(":/new/prefix1/IMAGE/good.png"));

                  message.exec();
             }
             if(p1point==p2point)
             {
                  QMessageBox message(QMessageBox::NoIcon, "游戏胜利", " 和局 ");
                  message.setIconPixmap(QPixmap(":/new/prefix1/IMAGE/good.png"));

                  message.exec();
             }



         }
         }
          else return;

     }
    else if(event->buttons()==(Qt::RightButton))
     {

        //如果点击了右键
        if(mine2->p[click_y2][click_x2]<10)
        {
            mine2->p[click_y2][click_x2] = mine2->p[click_y2][click_x2] +50;
            mine2->minusredFlagNum();
            if(player==0) {p2point=p2point+1;}
                         if(player==1) {p1point=p1point+1;}
        }
        else if(mine2->p[click_y2][click_x2]==99){

            mine2->p[click_y2][click_x2] = mine2->p[click_y2][click_x2] +50;
            mine2->minusredFlagNum();
            if(player==0) {p1point=p1point+2;}
                        if(player==1) {p2point=p2point+2;}
        }
        else if(mine2->p[click_y2][click_x2]>=50&&mine2->p[click_y2][click_x2]<60)
        {mine2->p[click_y2][click_x2] = mine2->p[click_y2][click_x2] -50;//移除红旗
            mine2->addredFlagNum();//红旗加1
            if(player==0) {p1point=p1point+1;}
            if(player==1) {p2point=p2point+1;}
        }
        else if(mine2->p[click_y2][click_x2]>110){
            mine2->p[click_y2][click_x2] = mine2->p[click_y2][click_x2] -50;//移除红旗
                         mine2->addredFlagNum();//红旗加1
                         if(player==0) {p2point=p2point+2;}
                         if(player==1) {p1point=p1point+2;}

        }
        paint_flag = 3;
        if(end2 = iswin2()==1)
        {
            paint_flag = 5;
            timeend2=1;
            runtime->stop();
        }
        update();
        if(end2)
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


    player=!player;
    if(player==1){
        playerpoint->setText("p2点击");
    }
    if(player==0){
        playerpoint->setText("p1点击");
    }
}
//绘图事件
void MainWindow2::paintEvent(QPaintEvent *event)
{
     QPainter painter(this);
     paintmywindow2 = &painter;
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
        painttitle2(paintmywindow2);
        //绘制雷区
        for(int i = 0;i<mine2->getcol()*BLOCK_LENGTH;i=i+BLOCK_LENGTH)
            for(int j =TITILE_HEIGH;j<TITILE_HEIGH+mine2->getrow()*BLOCK_HEIGH;j=j+BLOCK_HEIGH)
              painter.drawPixmap(i,j,block_close,0,0,BLOCK_LENGTH,BLOCK_LENGTH);
    }
    //左键点到炸弹绘制
    else if (paint_flag == 4)
    {
        painttitle2(paintmywindow2);
        //绘制雷区
        for(int i = 0;i<mine2->getrow();i++)
        {
            for(int j = 0;j<mine2->getcol();j++ )
               {
                if((mine2->p[i][j]<10)) //没被翻开的数字
                {
                    painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,block_close,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
                }
                else if((mine2->p[i][j]==99)) //没被翻开的炸弹
                {
                    painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,boom,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
                }
                else if (mine2->p[i][j]>110)  //炸弹被插旗
                {
                    painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,red_flag,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
                }
                else if ((mine2->p[i][j]<60)&&(mine2->p[i][j]>=50))  //数字被插旗
                {
                    painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,keil_boom,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
                }
                else if ((mine2->p[i][j])>99&&(mine2->p[i][j]<110))  //数字被点开
                {
                   int blk_num = mine2->p[i][j] - 100;
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
        painter.drawPixmap(click_x2*BLOCK_LENGTH,click_y2*BLOCK_HEIGH+TITILE_HEIGH,click_boom,0,0,BLOCK_LENGTH,BLOCK_HEIGH);

     }
    //左键点到空白绘制
    else if (paint_flag == 2 )
    {
       //绘制标题
       painttitle2(paintmywindow2);
       //绘制雷区
       paintboom2(paintmywindow2);
    }
    //右键点击绘制
    else if(paint_flag ==3)
    {

        painttitle2(paintmywindow2);
        paintboom2(paintmywindow2);
    }
    //游戏成功结束
    else if(paint_flag == 5)
    {
        painttitle2(paintmywindow2);
        paintboom2(paintmywindow2);
    }


}

//左键遍历递归（每个格子周围8个的情况）
void showblock2(int x,int y)
{
    for(int blockRow = x - 1; blockRow <=x + 1;blockRow++)
        for(int blockCol = y - 1;blockCol <=y + 1;blockCol++)
        {
            if(blockRow<0||blockCol<0||blockRow>=mine2->getrow()||blockCol>=mine2->getcol()) //特殊位置处理
               continue;
            if(mine2->p[blockRow][blockCol]<10)
            {
                mine2->p[blockRow][blockCol] =  mine2->p[blockRow][blockCol] + 100;  //翻开的格子数值+100
                if(mine2->p[blockRow][blockCol]==100)
                showblock2(blockRow,blockCol);   //如果此格周围都无炸弹自动翻开此格
            }
        }
}
//判断是否结束游戏
int iswin2()
{
    int cnt = 0;
    for(int row = 0; row <mine2->getrow();row++)
        for(int col =0;col<mine2->getcol();col++)
        {
            if((mine2->p[row][col]>=100)&&(mine2->p[row][col]<110))
                cnt++;
        }
    if(cnt>=((mine2->getcol()*mine2->getrow())-mine2->getboomNum()))  //翻开的格子等于（总数-炸弹数）游戏结束
        return 1;
    else
        return 0;
}


//重新开始游戏
void restart2(int row,int col,int boolnum)
{
    mine2 = new block (row,col,boolnum);
}



//绘制时间红旗数与标题
void painttitle2(QPainter  * painter)
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
    mine_title = mine_title.scaled(QSize(LENGTH2,40));

    //显示标题部分
    painter->drawPixmap(0,TTILE_BEGIN,mine_title,0,0,1000,1000);
    if(paint_flag == 4)
    painter->drawPixmap((int)LENGTH2*100/200-11,7+TTILE_BEGIN,qq_lose,0,0,1000,1000);
    else if (paint_flag == 5)
    painter->drawPixmap((int)LENGTH2*100/200-11,7+TTILE_BEGIN,qq_pround,0,0,1000,1000);
    else
    painter->drawPixmap((int)LENGTH2*100/200-11,7+TTILE_BEGIN,qq_smile,0,0,1000,1000);

    //显示红旗数量
    int redflagnum = mine2->getredFlagNum();
    if(redflagnum<0)
    {
        redflagnum = -redflagnum;
        painter->drawPixmap((int)(LENGTH2*40)/200-30,5+TTILE_BEGIN,ele_10,0,0,1000,1000);//百位数画分号
    }
    else painter->drawPixmap((int)(LENGTH2*40)/200-30,5+TTILE_BEGIN,ele_0,0,0,1000,1000);
    switch(redflagnum/10)
    {
    case 0:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_0,0,0,1000,1000);break;
    case 1:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_1,0,0,1000,1000);break;
    case 2:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_2,0,0,1000,1000);break;
    case 3:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_3,0,0,1000,1000);break;
    case 4:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_4,0,0,1000,1000);break;
    case 5:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_5,0,0,1000,1000);break;
    case 6:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_6,0,0,1000,1000);break;
    case 7:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_7,0,0,1000,1000);break;
    case 8:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_8,0,0,1000,1000);break;
    case 9:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_9,0,0,1000,1000);break;
    }
    switch (redflagnum%10)
    {
    case 0:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_0,0,0,1000,1000);break;
    case 1:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_1,0,0,1000,1000);break;
    case 2:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_2,0,0,1000,1000);break;
    case 3:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_3,0,0,1000,1000);break;
    case 4:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_4,0,0,1000,1000);break;
    case 5:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_5,0,0,1000,1000);break;
    case 6:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_6,0,0,1000,1000);break;
    case 7:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_7,0,0,1000,1000);break;
    case 8:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_8,0,0,1000,1000);break;
    case 9:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_9,0,0,1000,1000);break;
    }
    //显示P1分数

    switch(p1point/10)
    {
    case 0:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT,HEIGHT2-10,ele_0,0,0,1000,1000);break;
    case 1:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT,HEIGHT2-10,ele_1,0,0,1000,1000);break;
    case 2:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT,HEIGHT2-10,ele_2,0,0,1000,1000);break;
    case 3:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT,HEIGHT2-10,ele_3,0,0,1000,1000);break;
    case 4:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT,HEIGHT2-10,ele_4,0,0,1000,1000);break;
    case 5:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT,HEIGHT2-10,ele_5,0,0,1000,1000);break;
    case 6:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT,HEIGHT2-10,ele_6,0,0,1000,1000);break;
    case 7:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT,HEIGHT2-10,ele_7,0,0,1000,1000);break;
    case 8:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT,HEIGHT2-10,ele_8,0,0,1000,1000);break;
    case 9:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT,HEIGHT2-10,ele_9,0,0,1000,1000);break;
    }
    switch (p1point%10)
    {
    case 0:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,HEIGHT2-10,ele_0,0,0,1000,1000);break;
    case 1:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,HEIGHT2-10,ele_1,0,0,1000,1000);break;
    case 2:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,HEIGHT2-10,ele_2,0,0,1000,1000);break;
    case 3:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,HEIGHT2-10,ele_3,0,0,1000,1000);break;
    case 4:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,HEIGHT2-10,ele_4,0,0,1000,1000);break;
    case 5:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,HEIGHT2-10,ele_5,0,0,1000,1000);break;
    case 6:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,HEIGHT2-10,ele_6,0,0,1000,1000);break;
    case 7:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,HEIGHT2-10,ele_7,0,0,1000,1000);break;
    case 8:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,HEIGHT2-10,ele_8,0,0,1000,1000);break;
    case 9:  painter->drawPixmap((int)(LENGTH2*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,HEIGHT2-10,ele_9,0,0,1000,1000);break;
    }
    //显示P2分数

    switch(p2point/10)
    {
    case 0:  painter->drawPixmap((int)(LENGTH2*163)/200-30,HEIGHT2-10,ele_0,0,0,1000,1000);break;
    case 1:  painter->drawPixmap((int)(LENGTH2*163)/200-30,HEIGHT2-10,ele_1,0,0,1000,1000);break;
    case 2:  painter->drawPixmap((int)(LENGTH2*163)/200-30,HEIGHT2-10,ele_2,0,0,1000,1000);break;
    case 3:  painter->drawPixmap((int)(LENGTH2*163)/200-30,HEIGHT2-10,ele_3,0,0,1000,1000);break;
    case 4:  painter->drawPixmap((int)(LENGTH2*163)/200-30,HEIGHT2-10,ele_4,0,0,1000,1000);break;
    case 5:  painter->drawPixmap((int)(LENGTH2*163)/200-30,HEIGHT2-10,ele_5,0,0,1000,1000);break;
    case 6:  painter->drawPixmap((int)(LENGTH2*163)/200-30,HEIGHT2-10,ele_6,0,0,1000,1000);break;
    case 7:  painter->drawPixmap((int)(LENGTH2*163)/200-30,HEIGHT2-10,ele_7,0,0,1000,1000);break;
    case 8:  painter->drawPixmap((int)(LENGTH2*163)/200-30,HEIGHT2-10,ele_8,0,0,1000,1000);break;
    case 9:  painter->drawPixmap((int)(LENGTH2*163)/200-30,HEIGHT2-10,ele_9,0,0,1000,1000);break;
    }
    switch (p2point%10)
    {
    case 0:  painter->drawPixmap((int)(LENGTH2*163)/200-30+ELENUM_LENGHT,HEIGHT2-10,ele_0,0,0,1000,1000);break;
    case 1:  painter->drawPixmap((int)(LENGTH2*163)/200-30+ELENUM_LENGHT,HEIGHT2-10,ele_1,0,0,1000,1000);break;
    case 2:  painter->drawPixmap((int)(LENGTH2*163)/200-30+ELENUM_LENGHT,HEIGHT2-10,ele_2,0,0,1000,1000);break;
    case 3:  painter->drawPixmap((int)(LENGTH2*163)/200-30+ELENUM_LENGHT,HEIGHT2-10,ele_3,0,0,1000,1000);break;
    case 4:  painter->drawPixmap((int)(LENGTH2*163)/200-30+ELENUM_LENGHT,HEIGHT2-10,ele_4,0,0,1000,1000);break;
    case 5:  painter->drawPixmap((int)(LENGTH2*163)/200-30+ELENUM_LENGHT,HEIGHT2-10,ele_5,0,0,1000,1000);break;
    case 6:  painter->drawPixmap((int)(LENGTH2*163)/200-30+ELENUM_LENGHT,HEIGHT2-10,ele_6,0,0,1000,1000);break;
    case 7:  painter->drawPixmap((int)(LENGTH2*163)/200-30+ELENUM_LENGHT,HEIGHT2-10,ele_7,0,0,1000,1000);break;
    case 8:  painter->drawPixmap((int)(LENGTH2*163)/200-30+ELENUM_LENGHT,HEIGHT2-10,ele_8,0,0,1000,1000);break;
    case 9:  painter->drawPixmap((int)(LENGTH2*163)/200-30+ELENUM_LENGHT,HEIGHT2-10,ele_9,0,0,1000,1000);break;
    }


    //显示时间
    int timenum = mine2->gettimeNum();
    switch  (timenum/100)
    {
    case 0:  painter->drawPixmap((int)(LENGTH2*163)/200-30,5+TTILE_BEGIN,ele_0,0,0,1000,1000);break;
    case 1:  painter->drawPixmap((int)(LENGTH2*163)/200-30,5+TTILE_BEGIN,ele_1,0,0,1000,1000);break;
    case 2:  painter->drawPixmap((int)(LENGTH2*163)/200-30,5+TTILE_BEGIN,ele_2,0,0,1000,1000);break;
    case 3:  painter->drawPixmap((int)(LENGTH2*163)/200-30,5+TTILE_BEGIN,ele_3,0,0,1000,1000);break;
    case 4:  painter->drawPixmap((int)(LENGTH2*163)/200-30,5+TTILE_BEGIN,ele_4,0,0,1000,1000);break;
    case 5:  painter->drawPixmap((int)(LENGTH2*163)/200-30,5+TTILE_BEGIN,ele_5,0,0,1000,1000);break;
    case 6:  painter->drawPixmap((int)(LENGTH2*163)/200-30,5+TTILE_BEGIN,ele_6,0,0,1000,1000);break;
    case 7:  painter->drawPixmap((int)(LENGTH2*163)/200-30,5+TTILE_BEGIN,ele_7,0,0,1000,1000);break;
    case 8:  painter->drawPixmap((int)(LENGTH2*163)/200-30,5+TTILE_BEGIN,ele_8,0,0,1000,1000);break;
    case 9:  painter->drawPixmap((int)(LENGTH2*163)/200-30,5+TTILE_BEGIN,ele_9,0,0,1000,1000);break;
    }
    switch  (timenum/10)
    {
    case 0:  painter->drawPixmap((int)(LENGTH2*163)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_0,0,0,1000,1000);break;
    case 1:  painter->drawPixmap((int)(LENGTH2*163)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_1,0,0,1000,1000);break;
    case 2:  painter->drawPixmap((int)(LENGTH2*163)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_2,0,0,1000,1000);break;
    case 3:  painter->drawPixmap((int)(LENGTH2*163)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_3,0,0,1000,1000);break;
    case 4:  painter->drawPixmap((int)(LENGTH2*163)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_4,0,0,1000,1000);break;
    case 5:  painter->drawPixmap((int)(LENGTH2*163)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_5,0,0,1000,1000);break;
    case 6:  painter->drawPixmap((int)(LENGTH2*163)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_6,0,0,1000,1000);break;
    case 7:  painter->drawPixmap((int)(LENGTH2*163)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_7,0,0,1000,1000);break;
    case 8:  painter->drawPixmap((int)(LENGTH2*163)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_8,0,0,1000,1000);break;
    case 9:  painter->drawPixmap((int)(LENGTH2*163)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_9,0,0,1000,1000);break;
    }
    switch  (timenum%10)
    {
    case 0:  painter->drawPixmap((int)(LENGTH2*163)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_0,0,0,1000,1000);break;
    case 1:  painter->drawPixmap((int)(LENGTH2*163)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_1,0,0,1000,1000);break;
    case 2:  painter->drawPixmap((int)(LENGTH2*163)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_2,0,0,1000,1000);break;
    case 3:  painter->drawPixmap((int)(LENGTH2*163)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_3,0,0,1000,1000);break;
    case 4:  painter->drawPixmap((int)(LENGTH2*163)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_4,0,0,1000,1000);break;
    case 5:  painter->drawPixmap((int)(LENGTH2*163)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_5,0,0,1000,1000);break;
    case 6:  painter->drawPixmap((int)(LENGTH2*163)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_6,0,0,1000,1000);break;
    case 7:  painter->drawPixmap((int)(LENGTH2*163)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_7,0,0,1000,1000);break;
    case 8:  painter->drawPixmap((int)(LENGTH2*163)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_8,0,0,1000,1000);break;
    case 9:  painter->drawPixmap((int)(LENGTH2*163)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_9,0,0,1000,1000);break;
    }

}




//绘制正常鼠标点击事件与结束的雷区
void paintboom2(QPainter * painter)
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


    for(int i = 0;i<mine2->getrow();i++)
    {
        for(int j = 0;j<mine2->getcol();j++ )
           {

            if((mine2->p[i][j]<10)||(mine2->p[i][j]==99))
            {
                painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,block_close,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
            }
            else if (((mine2->p[i][j]<60)&&(mine2->p[i][j]>=50))||(mine2->p[i][j]>120))
            {
                painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,red_flag,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
            }
            else if ((mine2->p[i][j]>99)&&(mine2->p[i][j]<110))
            {
               int blk_num = mine2->p[i][j] - 100;
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
void MainWindow2::on_secondadd()   //点击开始计算秒数
{
    mine2->addtimeNum();
}
