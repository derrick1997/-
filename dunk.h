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

//����ϵͳ��
class Dunk
{
public:
    //���캯��
    Dunk(/* args */);

    //�˵�����
    void show_menu();

    //�˳�����
    void existsys();

    //��ʼ����������
    void chushihua();

    //����������6����Ա
    void createplayer();

    //��ʼ���� ��������
    void startdunk();

    //��ǩ
    void dunkdraw();

    //����
    void dunkcontest();

    //��ʾ�÷�
    void showscore();

    //�������
    void savedata();

    //���ؼ�¼
    void loaddata();

    //�ж��ļ��Ƿ�Ϊ��
    bool filesempty;

    //����������ݵ�����
    map<int, vector<string>> m_data;


    //��չ���
    void cleardata();

    //��Ա����
    //�����һ�ֱ�����Ա���
    vector<int> p1;

    //��һ�ֽ�����Ա��ţ����ڶ��ֲ�����Ա���
    vector<int> p2;

    //�ڶ��ֽ�����Ա��ż��ھ���Ա���
    vector<int> pch;

    //��ű���Լ���Ӧ����Ա
    map<int, player> m_player;

    //��ű�������
    int m_total;

    //��������
    ~Dunk();
};
