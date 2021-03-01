// 贪吃蛇4.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<mmsyscom.h>
#pragma comment(lib,"winmm.lib")
#define win_width 640
#define win_height 480
#define SNAKESIZE 100
#define obnum1 24
struct
{
	int speed;
	int len;
	int dir;
	int score;
	int Checkpoint;
	int size;
	POINT coor[SNAKESIZE];
}snake;
enum DIR {
	UP,DOWN,LEFT,RIGHT,
};
struct
{
	POINT foodxy;
	int flag;
	DWORD color;
}food;
struct
{
	POINT obstructionxy1[obnum1];
	int flag;
	DWORD color;
}obstruction;
void Gameinit()//定义

{
	snake.len = 3;
	snake.dir = RIGHT;
	snake.score = 0;
	snake.size = 10;
	/*snake.speed = 300;*/
	snake.coor[2].x = 0;
	snake.coor[2].y = 250;
	snake.coor[1].x = snake.size;
	snake.coor[1].y = 250;
	snake.coor[0].x = 2*snake.size;
	snake.coor[0].y = 250;
	snake.Checkpoint = 0;
	srand((unsigned)time(NULL));
	food.foodxy.x = rand() % (win_width/10)*10;
	food.foodxy.y = rand() % (win_height/10)*10;
	food.flag = 1;
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
}
void GameDraw()//界面和食物和开始的蛇
{
	setbkcolor(RGB(105,160,141));
	fillroundrect(snake.coor[0].x, snake.coor[0].y, snake.coor[0].x + snake.size, snake.coor[0].y + snake.size,100,100);
	for (int i = 1; i < snake.len; i++)
	{
		setlinecolor(WHITE);//边框
		setfillcolor(BLUE);//填充色
		fillellipse(snake.coor[i].x, snake.coor[i].y, snake.coor[i].x + snake.size, snake.coor[i].y + snake.size);
		/*printf("%d%d\n", snake.coor[i].x, snake.coor[i].y);*/
	}
	if (food.flag ==1)
	{
		setfillcolor(food.color);
		fillellipse/*椭圆*/(food.foodxy.x, food.foodxy.y, food.foodxy.x + snake.size, food.foodxy.y + snake.size);
	}
	if (obstruction.flag == 1)
		for (int i = 0; i < obnum1; i++) {
			{
				setfillcolor(obstruction.color);
				fillrectangle/*矩形*/(obstruction.obstructionxy1[i].x, obstruction.obstructionxy1[i].y, obstruction.obstructionxy1[i].x + snake.size, obstruction.obstructionxy1[i].y + snake.size);
			}
		}
	char temp[20]="";
	sprintf(temp, "分数：%d", snake.score);
	setbkmode(TRANSPARENT);//透明色
	outtextxy(20, 20, temp);
	char name[20] = "";
	sprintf(name, "作者：文强");
	setbkmode(TRANSPARENT);
	outtextxy(20, 40, name);
	char gk[20] = "";
	sprintf(gk, "关卡：%d", snake.Checkpoint);
	setbkmode(TRANSPARENT);
	outtextxy(20, 60, gk);
}
void Snakemove()//动
{
	for (int i = snake.len - 1; i > 0; i--)
	{
		snake.coor[i].x = snake.coor[i - 1].x;
		snake.coor[i].y = snake.coor[i - 1].y;
	}
	switch (snake.dir)
	{
	case UP:
		snake.coor[0].y -= snake.size;
		break;
	case DOWN:
		snake.coor[0].y += snake.size;
		break;
	case LEFT:
		snake.coor[0].x -= snake.size;
		break;
	case RIGHT:
		snake.coor[0].x += snake.size;
		break;
	}
}
void Keycontrol()//控制
{
	if (GetAsyncKeyState(VK_UP) && snake.dir != DOWN)
	{
		snake.dir = UP;
	}
	if (GetAsyncKeyState(VK_DOWN) && snake.dir != UP)
	{
		snake.dir = DOWN;
	}
	if (GetAsyncKeyState(VK_LEFT) && snake.dir != RIGHT)
	{
		snake.dir = LEFT;
	}
	if (GetAsyncKeyState(VK_RIGHT) && snake.dir != LEFT)
	{
		snake.dir = RIGHT;
	}
}
void Eatfood()//吃食物
{
	if (snake.coor[0].x == food.foodxy.x && snake.coor[0].y == food.foodxy.y && food.flag == 1)
	{
		snake.len++;
		snake.score += 20;
		food.flag = 0;
		snake.speed -= 10;
		snake.Checkpoint = (snake.score / 40);
	}
	if (food.flag == 0)
	{
		srand((unsigned)time(NULL));
		food.foodxy.x = rand() % (win_width / 10) * 10;
		food.foodxy.y = rand() % (win_height / 10) * 10;
		food.flag = 1;
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	}
}
void Eatslfe()//咬到自己
{
	for (int i = 4; i < snake.len; i++)
	{
		if (snake.coor[0].x == snake.coor[i].x && snake.coor[0].y == snake.coor[i].y)
		{
			outtextxy(250, 200, "咬到蛇身，游戏结束");
			_getch();
			exit(666);
		}
	}
}
void getobstruction()//障碍物生成
{
	for (int i = 0; i < 2; i++)
	{
		obstruction.obstructionxy1[i].x = 100 + 10 * i;
		obstruction.obstructionxy1[i].y = 50;
		obstruction.flag = 1;
		obstruction.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	}
	for (int i = 2; i < 4; i++)
	{
		obstruction.obstructionxy1[i].x = 100 + 10 * i;
		obstruction.obstructionxy1[i].y = 60;
		obstruction.flag = 1;
		obstruction.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	}
	for (int i = 4; i < 6; i++)
	{
		obstruction.obstructionxy1[i].x = 100 + 10 * i;
		obstruction.obstructionxy1[i].y = 350;
		obstruction.flag = 1;
		obstruction.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	}
	for (int i = 6; i < 8; i++)
	{
		obstruction.obstructionxy1[i].x = 100 + 10 * i;
		obstruction.obstructionxy1[i].y = 360;
		obstruction.flag = 1;
		obstruction.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	}
	for (int i = 8; i < 10; i++)
	{
		obstruction.obstructionxy1[i].x = 400 + 10 * i;
		obstruction.obstructionxy1[i].y = 50;
		obstruction.flag = 1;
		obstruction.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	}
	for (int i = 10; i < 12; i++)
	{
		obstruction.obstructionxy1[i].x = 400 + 10 * i;
		obstruction.obstructionxy1[i].y = 60;
		obstruction.flag = 1;
		obstruction.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	}
	for (int i = 12; i < 14; i++)
	{
		obstruction.obstructionxy1[i].x = 400 + 10 * i;
		obstruction.obstructionxy1[i].y = 350;
		obstruction.flag = 1;
		obstruction.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	}
	for (int i = 14; i < 16; i++)
	{
		obstruction.obstructionxy1[i].x = 400 + 10 * i;
		obstruction.obstructionxy1[i].y = 360;
		obstruction.flag = 1;
		obstruction.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	}
}
void pause()//暂停
{
	int k;
		if (_kbhit())
		{
			k = _getch();
			if (k ==32)
			{
				outtextxy(250, 200, "游戏暂停,空格继续");
				while (1)
				if (_kbhit() && _getch() == 32)
				break;
			}

		}
}
void snakeStatus()//碰到边缘
{
	if (snake.coor[0].y < 0 || snake.coor[0].y == win_height)
	{
		outtextxy(250, 200, "撞墙死亡，游戏结束");
		getch();
		exit(666);
	}
	if (snake.coor[0].x < 0 || snake.coor[0].x == win_width)
	{
		outtextxy(250, 200, "撞墙死亡，游戏结束");
		getch();
		exit(666);
	}
	for (int i = 0; i < 24; i++) 
	{
	if (snake.coor[0].x == obstruction.obstructionxy1[i].x && snake.coor[0].y == obstruction.obstructionxy1[i].y)
	{
		outtextxy(250, 200, "撞墙死亡，游戏结束");
		getch();
		exit(666);
	}
	}
}
void Gamebegie()//游戏开始难度选择,地图变化
{
	outtextxy(250, 200, "开始游戏");
	outtextxy(250, 220, "普通难度按1");
	outtextxy(250, 240, "一般难度按2");
	outtextxy(250, 260, "困难难度按3");
	outtextxy(150, 280, "游戏说明，空格表示暂停，触碰墙壁和障碍会死亡，");
	outtextxy(200, 300, "吃掉一个食物20分，40一个关卡");
	while (1)
	{
			if (_kbhit() && _getch() == '1')
			{
				snake.speed = 300;
				getobstruction();
				break;
			}

			if (_kbhit() && _getch() == '2')
			{
				snake.speed = 250;
				getobstruction();
				for (int i = 16; i < 20; i++)
				{
					obstruction.obstructionxy1[i].x = 120 + 10 * i;
					obstruction.obstructionxy1[i].y = 180;
					obstruction.flag = 1;
					obstruction.color = RGB(rand() % 256, rand() % 256, rand() % 256);
				}
				break;
			}

			if (_kbhit() && _getch() == '3')
			{
				snake.speed = 200;
				getobstruction();
				for (int i = 16; i < 20; i++)
				{
					obstruction.obstructionxy1[i].x = 120 + 10 * i;
					obstruction.obstructionxy1[i].y = 120;
					obstruction.flag = 1;
					obstruction.color = RGB(rand() % 256, rand() % 256, rand() % 256);
				}
				for (int i = 20; i < 24; i++)
				{
					obstruction.obstructionxy1[i].x = 120 + 10 * i;
					obstruction.obstructionxy1[i].y = 240;
					obstruction.flag = 1;
					obstruction.color = RGB(rand() % 256, rand() % 256, rand() % 256);
				}
				break;
			}
	}
}
void palybgm()//背景音乐
{
	mciSendString("open bgm.wma alias a", 0, 0, 0);
	mciSendString("play a repeat", 0, 0, 0);
}
void backgroud()
{
	IMAGE img;
	loadimage(&img, "C:\\Users\\God of war\\Pictures\\Camera Roll\\webp.webp(1).jpg");
	putimage(0, 0, &img);
}
int main()8
{
	initgraph(win_width, win_height, SHOWCONSOLE);//运行框
	backgroud();
	Gameinit();
	palybgm(); 
	Gamebegie();
	while (1)
	{
		cleardevice();//刷新
		Snakemove();
		GameDraw();
		Eatfood();
		Keycontrol();
		snakeStatus();
		Eatslfe();
		pause();
		Sleep(snake.speed);
	}
	getchar();
	closegraph();
	return 0;
}