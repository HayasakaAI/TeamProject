#ifndef BLOCK_H
#define BLOCK_H

#include "iostream"
#include "ctime"
#include "stdlib.h"
#include <QDebug>


class block
{
public:
    block(int row ,int col,int boomNum);
    ~block();
    int getcol();
    int getrow();
    int getboomNum();
    int getredFlagNum();
    int gettimeNum();
    void minusredFlagNum();//减红旗数
    void addredFlagNum();//加红旗数
    void addtimeNum();
    int **p;
private:
    int row,col,boomNum;
    int timeNum,redFlagNum;

};

#endif // BLOCK_H
