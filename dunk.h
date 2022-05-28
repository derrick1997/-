#pragma once

#include <iostream>
#include <vector>
#include <map>
#include "player.h"
#include <algorithm>
#include <deque>
#include <functional>
#include <numeric>
#include <string>
#include <fstream>

using namespace std;

//扣篮系统类
class Dunk
{
public:
    //构造函数
    Dunk(/* args */);

    //菜单函数
    void show_menu();

    //退出函数
    void existsys();

    //初始化所有容器
    void chushihua();

    //创建参赛的6名球员
    void createplayer();

    //开始比赛 比赛流程
    void startdunk();

    //抽签
    void dunkdraw();

    //比赛
    void dunkcontest();

    //显示得分
    void showscore();

    //保存分数
    void savedata();

    //加载记录
    void loaddata();

    //判断文件是否为空
    bool filesempty;

    //存放往届数据的容器
    map<int, vector<string>> m_data;


    //清空功能
    void cleardata();

    //成员属性
    //保存第一轮比赛球员编号
    vector<int> p1;

    //第一轮晋级球员编号，即第二轮参赛球员编号
    vector<int> p2;

    //第二轮晋级球员编号即冠军球员编号
    vector<int> pch;

    //存放编号以及对应的球员
    map<int, player> m_player;

    //存放比赛轮数
    int m_total;

    //析构函数
    ~Dunk();
};
