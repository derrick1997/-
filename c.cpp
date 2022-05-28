#include <iostream>
#include "dunk.h"
#include <string>
#include <ctime>

using namespace std;

int main()
{
	// 0 随机种子
	srand((unsigned int)time(NULL)); //利用系统时间实现真随机

	Dunk play;

	int choice = 0; //用户输入选择
	while (true)
	{
		play.show_menu();
		cout << "请输入您的选择：" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1: // 1.开始扣篮大赛
			play.startdunk();
			break;
		case 2: // 2.查看往届记录
			play.loaddata();
			// play.showdata();
			break;
		case 3: // 3.清空比赛记录
			play.cleardata();
			break;
		case 0: //退出
			play.existsys();
			break;
		default:
			system("cls"); //清屏
			break;
		}
	}

	system("pause");
	return 0;
}
