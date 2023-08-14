#include <easyx.h>
//#include <stdio.h>
#include <conio.h>
#include <time.h>

#define NUM 100		//定义蛇的长度
#define SIZE 15		//蛇的身宽

#define HEIGHT 40*SIZE   //高度为20个蛇身位
#define WIDTH 40*SIZE	//宽度为20个蛇身位

//定义方位
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77


struct Location		//定义坐标结构体
{
	int x;
	int y;
};

struct Snake		//定义蛇的结构体
{
	int len;				//长度
	int direc;				//朝向
	Location locat[NUM];	//位置
}snake;

struct Food
{
	bool eat;			//状态
	int x;
	int y;		
}food;
void CreateFood()
{
	if (food.eat)
	{
		food.x = rand() % (WIDTH / SIZE) * SIZE;
		food.y = rand() % (HEIGHT / SIZE) * SIZE;
	}
	food.eat = false;
}

void GameInit()
{
	snake.len = 3;
	snake.direc = RIGHT;

	//初始化蛇头
	snake.locat[0].x = WIDTH/2;
	snake.locat[0].y = HEIGHT/2;

	//初始化蛇身的坐标
	snake.locat[1].x = snake.locat[0].x-SIZE;
	snake.locat[1].y = 100 ;
	snake.locat[2].x = snake.locat[0].x -2*SIZE;
	snake.locat[2].y = 100 ;

	food.eat = true; //初始化食物为被吃状态，需要重新生成
	CreateFood();

}
void GameDraw()
{
	cleardevice();		//清屏

	for (int i=0; i < snake.len; i++)		//绘制蛇形
	{
		if (i == 0)		//蛇头
		{
			setfillcolor(RED);
			fillrectangle(snake.locat[i].x, snake.locat[i].y, snake.locat[i].x + SIZE, snake.locat[i].y + SIZE);
			//参数（矩形左部 x 坐标，矩形上部 y 坐标，矩形右部 x 坐标，矩形下部 y 坐标）
		}
		else		//蛇身
		{
			rectangle(snake.locat[i].x, snake.locat[i].y, snake.locat[i].x + SIZE, snake.locat[i].y + SIZE);
		}
	}
	setfillcolor(GREEN);
	fillrectangle(food.x, food.y, food.x + SIZE, food.y + SIZE);

}
void Move_Snake()
{
	
	if (_kbhit())		//判断是否有键值输入
	{
		//char temp_getch();
		int c = _getch();
		switch (c)
		{
		case UP:
		case 'w':
		case 'W':
			if(snake.direc!=DOWN)
				snake.direc = UP; 
			break;
		case DOWN:
		case 's':
		case 'S':
			if (snake.direc != UP)
				snake.direc = DOWN;
			break;
		case LEFT:
		case 'a':
		case 'A':
			if (snake.direc != RIGHT)
				snake.direc = LEFT;
			break;
		case RIGHT:
		case 'd':
		case 'D':
			if (snake.direc != LEFT)
				snake.direc = RIGHT;
		}
		//printf("%d\n", c);
	}

	for (int i = snake.len-1; i >0; i--)		//从蛇尾开始向前拷贝坐标
	{
		snake.locat[i].x = snake.locat[i - 1].x;
		snake.locat[i].y = snake.locat[i - 1].y;
	}

	switch (snake.direc)		//移动蛇头
	{
	case UP:
		snake.locat[0].y -= SIZE; break;
	case DOWN:
		snake.locat[0].y += SIZE; break;
	case LEFT:
		snake.locat[0].x -= SIZE; break;
	case RIGHT:
		snake.locat[0].x += SIZE;
	}
}
void EatFood()
{
	if (snake.locat[0].x == food.x && snake.locat[0].y == food.y)
	{
	food.eat = true;
	snake.len++;
	}
		
}
bool GameOver()
{
	if (snake.locat[0].x < 0 || snake.locat[0].x > WIDTH-SIZE || snake.locat[0].y < 0 || snake.locat[0].y > HEIGHT-SIZE) //撞墙判断
	{
		return true;
	}
	for (int i = 1; i < snake.len; i++)
	{
		if (snake.locat[i].x == snake.locat[0].x && snake.locat[i].y == snake.locat[0].y)		//自吃判断
			return true;
	}
	return false;
}
void Restart(bool flag)
{
	if (flag)
	{
		int select = MessageBox(GetHWnd(), L"怎么寄了呢？再来一把吗？", L"寄", MB_OKCANCEL);
		if (select == IDOK)	//再来一把
		{
			//重新初始化
			GameInit();
		}
		else  //退出
		{
			exit(0);
		}
	}
}
int main()
{
	initgraph(WIDTH, HEIGHT,0);			//创建窗口
	setbkcolor(RGB(255,148,206));	//粉色背景
	cleardevice();					//背景色清屏

	GameInit();						//游戏初始化
	while(1)
	{
		CreateFood();		//创建食物
		EatFood();			//判断是否被吃
		Move_Snake();		//蛇移动
		GameDraw();			//绘制界面
		Restart(GameOver());	//判断是否结束
		Sleep(100);	
	}
	closegraph();
	return 0;
}
