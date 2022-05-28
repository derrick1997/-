#include "dunk.h"

//构造函数
Dunk::Dunk()
{
    //初始化属性
    this->chushihua();

    //创建6名球员
    this->createplayer();

    //加载往届数据
    this->loaddata();
}

//菜单函数
void Dunk::show_menu()
{
    cout << "********************************" << endl;
    cout << "*******欢迎参加扣篮大赛**********" << endl;
    cout << "********1.开始扣篮大赛***********" << endl;
    cout << "********2.查看往届记录***********" << endl;
    cout << "********3.清空比赛记录***********" << endl;
    cout << "********0.退出比赛进程***********" << endl;
    cout << "********************************" << endl;
    cout << endl;
}

//创建球员
void Dunk::createplayer()
{
    string nameseed[6] = {"拉文", "卡特", "乔丹", "戈登", "霍华德", "小琼斯"};
    for (int i = 0; i < 6; i++)
    {
        string name = "球员";
        name += nameseed[i];

        //创建球员姓名得分
        player dp;
        dp.m_name = name;

        for (int j = 0; j < 2; j++)
        {
            dp.M_score[j] = 0;
        }

        //创建球员编号
        this->p1.push_back(i + 100);

        //球员编号以及对应的球员放入map
        this->m_player.insert(make_pair(i + 100, dp));
    }
}

//开始比赛 比赛流程
void Dunk::startdunk()
{
    //第一轮开始比赛

    // 1.抽签
    this->dunkdraw();

    // 2.比赛
    this->dunkcontest();

    // 3.显示晋级结果
    this->showscore();

    //第二轮比赛
    this->m_total++;

    // 1.抽签
    this->dunkdraw();

    // 2.比赛
    this->dunkcontest();

    // 3.显示冠军归属
    this->showscore();

    // 4.保存分数到文件中
    this->savedata();

    cout << "本届比赛全部结束" << endl;
    system("pause");
    system("cls");
}

//抽签
void Dunk::dunkdraw()
{
    cout << "第《" << this->m_total << "》轮比赛抽签进行中" << endl;
    cout << "---------------------------" << endl;
    cout << "抽签后的顺序是:" << endl;
    if (this->m_total == 1)
    {
        //第一轮
        random_shuffle(p1.begin(), p1.end());
        for (vector<int>::iterator it = p1.begin(); it != p1.end(); it++)
        {
            cout << *it << " ";
        }
        cout << endl;
    }
    else
    {
        //第二轮
        random_shuffle(p2.begin(), p2.end());
        for (vector<int>::iterator it = p2.begin(); it != p2.end(); it++)
        {
            cout << *it << " ";
        }
        cout << endl;
    }
    cout << "---------------------------" << endl;
    cout << "|*************************|" << endl;
    cout << "---------------------------" << endl;
    system("pause");
    cout << endl;
}

//比赛
void Dunk::dunkcontest()
{
    cout << "第《" << this->m_total << "》轮比赛正式开始" << endl;

    //准备临时容器 存放小组
    multimap<int, int, greater<int>> groupscore;

    int fenzu = 0;

    vector<int> p_src;
    if (this->m_total == 1)
    {
        p_src = p1;
    }
    else
    {
        p_src = p2;
    }

    //遍历所有球员
    for (vector<int>::iterator it = p_src.begin(); it != p_src.end(); it++)
    {
        fenzu++;
        //评委打分
        deque<int> d;
        for (int i = 0; i < 5; i++) // 5个评委打分
        {
            int score = rand() % 4 + 7; //分数区间为7分到10分
            // cout <<score << " ";//测试打分是否正确
            d.push_back(score);
        }
        cout << endl;
        sort(d.begin(), d.end(), greater<int>());    //进行排序
        int sum = accumulate(d.begin(), d.end(), 0); //总分

        //打印总分
        cout << "编号:" << *it << "| 姓名：" << this->m_player[*it].m_name << "| 总得分：" << sum << endl;

        //将总分放入map容器
        this->m_player[*it].M_score[this->m_total - 1] = sum;

        //将打分数据放入到临时小组容器中
        groupscore.insert(make_pair(sum, *it)); //键值key是总得分，value是球员编号

        //获得前三名
        if (fenzu % 6 == 0 && this->m_total == 1) //每6个人进三个
        {
            cout << endl;
            cout << "---------------------------" << endl;
            cout << "|-球员第" << this->m_total << "扣得分排名如下：-|" << endl;
            cout << "---------------------------" << endl;
            for (multimap<int, int, greater<int>>::iterator it = groupscore.begin(); it != groupscore.end(); it++)
            {
                cout << "编号：" << it->second << "| 姓名：" << this->m_player[it->second].m_name << "| 总得分："
                     << this->m_player[it->second].M_score[this->m_total - 1] << endl;
            }

            //前三名晋级
            int count = 0;

            for (multimap<int, int, greater<int>>::iterator it = groupscore.begin(); it != groupscore.end() && count < 3; it++, count++)
            {
                if (this->m_total == 1)
                {
                    p2.push_back(it->second);
                }
                else
                {
                    pch.push_back(it->second);
                }
            }
            groupscore.clear();
        }
        else if (fenzu % 3 == 0 && this->m_total == 2)
        {
            cout << endl;
            cout << "---------------------------" << endl;
            cout << "|-球员第" << this->m_total << "扣得分排名如下：-|" << endl;
            cout << "---------------------------" << endl;
            for (multimap<int, int, greater<int>>::iterator it = groupscore.begin(); it != groupscore.end(); it++)
            {
                cout << "编号：" << it->second << "| 姓名：" << this->m_player[it->second].m_name << "| 总得分："
                     << this->m_player[it->second].M_score[this->m_total - 2] << endl;
            }

            //冠军诞生
            int count = 0;
            for (multimap<int, int, greater<int>>::iterator it = groupscore.begin(); it != groupscore.end() && count < 1; it++, count++)
            {
                if (this->m_total == 1)
                {
                    p2.push_back(it->second);
                }
                else
                {
                    pch.push_back(it->second);
                }
            }
            groupscore.clear();
        }
    }
    cout << "------第《" << this->m_total << "》轮比赛结束!------" << endl;
    system("pause");
}

//显示得分
void Dunk::showscore()
{
    vector<int> p;
    if (this->m_total == 1)
    {
        cout << "-----第《" << this->m_total << "》轮晋级球员信息如下:-----" << endl;
        p = p2;
        for (vector<int>::iterator it = p.begin(); it != p.end(); it++)
        {
            cout << "编号：" << *it << "| 姓名： " << this->m_player[*it].m_name << "| 得分："
                 << this->m_player[*it].M_score[this->m_total - 1] << endl;
        }
    }
    else
    {
        cout << "-----第《" << this->m_total << "》轮冠军球员信息如下:-----" << endl;
        p = pch;
        for (vector<int>::iterator it = p.begin(); it != p.end(); it++)
        {
            cout << "编号：" << *it << "| 姓名： " << this->m_player[*it].m_name << "| 得分："
                 << this->m_player[*it].M_score[this->m_total - 2] << endl;
        }
    }
    cout << endl;

    system("pause");
    system("cls");
    this->show_menu();
}

//保存分数
void Dunk::savedata()
{
    ofstream ofs;
    ofs.open("dunk.csv", ios::out | ios::app); // app表示追加文件,csv格式keyiyongexcel或者记事本打开

    if (!ofs)
    {
        cerr << "打开错误!" << endl;
        exit(1);
    }

    //将每个球员写入文件
    for (vector<int>::iterator it = pch.begin(); it != pch.end(); it++)
    {
        /* ofs << "编号：" << *it << ","
            << "得分：" << this->m_player[*it].M_score[1] << ","; */
        ofs << *it << ","
            << this->m_player[*it].M_score[1] << ",";
    }
    ofs << endl;

    ofs.close();
    cout << "数据记录完成" << endl;
}

//加载记录
void Dunk::loaddata()
{
    ifstream ifs("dunk.csv", ios::in); //读文件

    //文件不存在的情况
    if (!ifs.is_open())
    {
        this->filesempty = true;
        cout << "文件不存在！" << endl;
        ifs.close();
        return;
    }

    //文件清空的情况
    char ch;
    ifs >> ch;
    if (ifs.eof())
    {
        cout << "文件为空" << endl;
        this->filesempty = true;
        ifs.close();
        return;
    }

    //文件不为空
    this->filesempty = false;

    ifs.putback(ch); //将上面读取的单个字符取回

    string data;
    int index = 1; //第1届
    while (ifs >> data)
    {
        cout << "第" << index << "届冠军信息：" << data << endl;

        vector<string> v; //存放字符串

        index++;
    }

    ifs.close();
}


//清空功能
void Dunk::cleardata()
{
    cout << "是否清空数据?" << endl;
    cout << "1.是" << endl;
    cout << "2.否" << endl;

    int sel = 0;
    cin >> sel;

    if (sel == 1)
    {
        //确认清空
        ofstream ofs("dunk.csv", ios::trunc); //清空
        ofs.close();

        //初始化属性
        this->chushihua();

        //创建6名球员
        this->createplayer();

        //加载往届数据
        this->loaddata();
        cout << "清空成功!" << endl;
    }
    system("pause");
    system("cls");
}

//退出函数
void Dunk::existsys()
{
    cout << "恭喜扣篮大赛圆满结束!" << endl;
    system("pause");
    exit(0);
}

//容器初始化
void Dunk::chushihua()
{
    //容器清空
    this->p1.clear();
    this->p2.clear();
    this->pch.clear();
    this->m_player.clear();

    //初始化比赛轮数
    this->m_total = 1;
}

//析构函数,在这个程序中可有可无，因为没有堆区数据
Dunk::~Dunk()
{
}