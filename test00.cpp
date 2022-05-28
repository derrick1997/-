#include "dunk.h"

//���캯��
Dunk::Dunk()
{
    //��ʼ������
    this->chushihua();

    //����6����Ա
    this->createplayer();

    //������������
    this->loaddata();
}

//�˵�����
void Dunk::show_menu()
{
    cout << "********************************" << endl;
    cout << "*******��ӭ�μӿ�������**********" << endl;
    cout << "********1.��ʼ��������***********" << endl;
    cout << "********2.�鿴�����¼***********" << endl;
    cout << "********3.��ձ�����¼***********" << endl;
    cout << "********0.�˳���������***********" << endl;
    cout << "********************************" << endl;
    cout << endl;
}

//������Ա
void Dunk::createplayer()
{
    string nameseed[6] = {"����", "����", "�ǵ�", "���", "������", "С��˹"};
    for (int i = 0; i < 6; i++)
    {
        string name = "��Ա";
        name += nameseed[i];

        //������Ա�����÷�
        player dp;
        dp.m_name = name;

        for (int j = 0; j < 2; j++)
        {
            dp.M_score[j] = 0;
        }

        //������Ա���
        this->p1.push_back(i + 100);

        //��Ա����Լ���Ӧ����Ա����map
        this->m_player.insert(make_pair(i + 100, dp));
    }
}

//��ʼ���� ��������
void Dunk::startdunk()
{
    //��һ�ֿ�ʼ����

    // 1.��ǩ
    this->dunkdraw();

    // 2.����
    this->dunkcontest();

    // 3.��ʾ�������
    this->showscore();

    //�ڶ��ֱ���
    this->m_total++;

    // 1.��ǩ
    this->dunkdraw();

    // 2.����
    this->dunkcontest();

    // 3.��ʾ�ھ�����
    this->showscore();

    // 4.����������ļ���
    this->savedata();

    cout << "�������ȫ������" << endl;
    system("pause");
    system("cls");
}

//��ǩ
void Dunk::dunkdraw()
{
    cout << "�ڡ�" << this->m_total << "���ֱ�����ǩ������" << endl;
    cout << "---------------------------" << endl;
    cout << "��ǩ���˳����:" << endl;
    if (this->m_total == 1)
    {
        //��һ��
        random_shuffle(p1.begin(), p1.end());
        for (vector<int>::iterator it = p1.begin(); it != p1.end(); it++)
        {
            cout << *it << " ";
        }
        cout << endl;
    }
    else
    {
        //�ڶ���
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

//����
void Dunk::dunkcontest()
{
    cout << "�ڡ�" << this->m_total << "���ֱ�����ʽ��ʼ" << endl;

    //׼����ʱ���� ���С��
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

    //����������Ա
    for (vector<int>::iterator it = p_src.begin(); it != p_src.end(); it++)
    {
        fenzu++;
        //��ί���
        deque<int> d;
        for (int i = 0; i < 5; i++) // 5����ί���
        {
            int score = rand() % 4 + 7; //��������Ϊ7�ֵ�10��
            // cout <<score << " ";//���Դ���Ƿ���ȷ
            d.push_back(score);
        }
        cout << endl;
        sort(d.begin(), d.end(), greater<int>());    //��������
        int sum = accumulate(d.begin(), d.end(), 0); //�ܷ�

        //��ӡ�ܷ�
        cout << "���:" << *it << "| ������" << this->m_player[*it].m_name << "| �ܵ÷֣�" << sum << endl;

        //���ַܷ���map����
        this->m_player[*it].M_score[this->m_total - 1] = sum;

        //��������ݷ��뵽��ʱС��������
        groupscore.insert(make_pair(sum, *it)); //��ֵkey���ܵ÷֣�value����Ա���

        //���ǰ����
        if (fenzu % 6 == 0 && this->m_total == 1) //ÿ6���˽�����
        {
            cout << endl;
            cout << "---------------------------" << endl;
            cout << "|-��Ա��" << this->m_total << "�۵÷��������£�-|" << endl;
            cout << "---------------------------" << endl;
            for (multimap<int, int, greater<int>>::iterator it = groupscore.begin(); it != groupscore.end(); it++)
            {
                cout << "��ţ�" << it->second << "| ������" << this->m_player[it->second].m_name << "| �ܵ÷֣�"
                     << this->m_player[it->second].M_score[this->m_total - 1] << endl;
            }

            //ǰ��������
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
            cout << "|-��Ա��" << this->m_total << "�۵÷��������£�-|" << endl;
            cout << "---------------------------" << endl;
            for (multimap<int, int, greater<int>>::iterator it = groupscore.begin(); it != groupscore.end(); it++)
            {
                cout << "��ţ�" << it->second << "| ������" << this->m_player[it->second].m_name << "| �ܵ÷֣�"
                     << this->m_player[it->second].M_score[this->m_total - 2] << endl;
            }

            //�ھ�����
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
    cout << "------�ڡ�" << this->m_total << "���ֱ�������!------" << endl;
    system("pause");
}

//��ʾ�÷�
void Dunk::showscore()
{
    vector<int> p;
    if (this->m_total == 1)
    {
        cout << "-----�ڡ�" << this->m_total << "���ֽ�����Ա��Ϣ����:-----" << endl;
        p = p2;
        for (vector<int>::iterator it = p.begin(); it != p.end(); it++)
        {
            cout << "��ţ�" << *it << "| ������ " << this->m_player[*it].m_name << "| �÷֣�"
                 << this->m_player[*it].M_score[this->m_total - 1] << endl;
        }
    }
    else
    {
        cout << "-----�ڡ�" << this->m_total << "���ֹھ���Ա��Ϣ����:-----" << endl;
        p = pch;
        for (vector<int>::iterator it = p.begin(); it != p.end(); it++)
        {
            cout << "��ţ�" << *it << "| ������ " << this->m_player[*it].m_name << "| �÷֣�"
                 << this->m_player[*it].M_score[this->m_total - 2] << endl;
        }
    }
    cout << endl;

    system("pause");
    system("cls");
    this->show_menu();
}

//�������
void Dunk::savedata()
{
    ofstream ofs;
    ofs.open("dunk.csv", ios::out | ios::app); // app��ʾ׷���ļ�,csv��ʽkeyiyongexcel���߼��±���

    if (!ofs)
    {
        cerr << "�򿪴���!" << endl;
        exit(1);
    }

    //��ÿ����Աд���ļ�
    for (vector<int>::iterator it = pch.begin(); it != pch.end(); it++)
    {
        /* ofs << "��ţ�" << *it << ","
            << "�÷֣�" << this->m_player[*it].M_score[1] << ","; */
        ofs << *it << ","
            << this->m_player[*it].M_score[1] << ",";
    }
    ofs << endl;

    ofs.close();
    cout << "���ݼ�¼���" << endl;
}

//���ؼ�¼
void Dunk::loaddata()
{
    ifstream ifs("dunk.csv", ios::in); //���ļ�

    //�ļ������ڵ����
    if (!ifs.is_open())
    {
        this->filesempty = true;
        cout << "�ļ������ڣ�" << endl;
        ifs.close();
        return;
    }

    //�ļ���յ����
    char ch;
    ifs >> ch;
    if (ifs.eof())
    {
        cout << "�ļ�Ϊ��" << endl;
        this->filesempty = true;
        ifs.close();
        return;
    }

    //�ļ���Ϊ��
    this->filesempty = false;

    ifs.putback(ch); //�������ȡ�ĵ����ַ�ȡ��

    string data;
    int index = 1; //��1��
    while (ifs >> data)
    {
        cout << "��" << index << "��ھ���Ϣ��" << data << endl;

        vector<string> v; //����ַ���

        index++;
    }

    ifs.close();
}


//��չ���
void Dunk::cleardata()
{
    cout << "�Ƿ��������?" << endl;
    cout << "1.��" << endl;
    cout << "2.��" << endl;

    int sel = 0;
    cin >> sel;

    if (sel == 1)
    {
        //ȷ�����
        ofstream ofs("dunk.csv", ios::trunc); //���
        ofs.close();

        //��ʼ������
        this->chushihua();

        //����6����Ա
        this->createplayer();

        //������������
        this->loaddata();
        cout << "��ճɹ�!" << endl;
    }
    system("pause");
    system("cls");
}

//�˳�����
void Dunk::existsys()
{
    cout << "��ϲ��������Բ������!" << endl;
    system("pause");
    exit(0);
}

//������ʼ��
void Dunk::chushihua()
{
    //�������
    this->p1.clear();
    this->p2.clear();
    this->pch.clear();
    this->m_player.clear();

    //��ʼ����������
    this->m_total = 1;
}

//��������,����������п��п��ޣ���Ϊû�ж�������
Dunk::~Dunk()
{
}