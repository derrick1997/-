#include <iostream>
#include "dunk.h"
#include <string>
#include <ctime>

using namespace std;

int main()
{
	// 0 �������
	srand((unsigned int)time(NULL)); //����ϵͳʱ��ʵ�������

	Dunk play;

	int choice = 0; //�û�����ѡ��
	while (true)
	{
		play.show_menu();
		cout << "����������ѡ��" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1: // 1.��ʼ��������
			play.startdunk();
			break;
		case 2: // 2.�鿴�����¼
			play.loaddata();
			// play.showdata();
			break;
		case 3: // 3.��ձ�����¼
			play.cleardata();
			break;
		case 0: //�˳�
			play.existsys();
			break;
		default:
			system("cls"); //����
			break;
		}
	}

	system("pause");
	return 0;
}
