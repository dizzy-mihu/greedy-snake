#include <easyx.h>
//#include <stdio.h>
#include <conio.h>
#include <time.h>

#define NUM 100		//�����ߵĳ���
#define SIZE 15		//�ߵ����

#define HEIGHT 40*SIZE   //�߶�Ϊ20������λ
#define WIDTH 40*SIZE	//���Ϊ20������λ

//���巽λ
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77


struct Location		//��������ṹ��
{
	int x;
	int y;
};

struct Snake		//�����ߵĽṹ��
{
	int len;				//����
	int direc;				//����
	Location locat[NUM];	//λ��
}snake;

struct Food
{
	bool eat;			//״̬
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

	//��ʼ����ͷ
	snake.locat[0].x = WIDTH/2;
	snake.locat[0].y = HEIGHT/2;

	//��ʼ�����������
	snake.locat[1].x = snake.locat[0].x-SIZE;
	snake.locat[1].y = 100 ;
	snake.locat[2].x = snake.locat[0].x -2*SIZE;
	snake.locat[2].y = 100 ;

	food.eat = true; //��ʼ��ʳ��Ϊ����״̬����Ҫ��������
	CreateFood();

}
void GameDraw()
{
	cleardevice();		//����

	for (int i=0; i < snake.len; i++)		//��������
	{
		if (i == 0)		//��ͷ
		{
			setfillcolor(RED);
			fillrectangle(snake.locat[i].x, snake.locat[i].y, snake.locat[i].x + SIZE, snake.locat[i].y + SIZE);
			//������������ x ���꣬�����ϲ� y ���꣬�����Ҳ� x ���꣬�����²� y ���꣩
		}
		else		//����
		{
			rectangle(snake.locat[i].x, snake.locat[i].y, snake.locat[i].x + SIZE, snake.locat[i].y + SIZE);
		}
	}
	setfillcolor(GREEN);
	fillrectangle(food.x, food.y, food.x + SIZE, food.y + SIZE);

}
void Move_Snake()
{
	
	if (_kbhit())		//�ж��Ƿ��м�ֵ����
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

	for (int i = snake.len-1; i >0; i--)		//����β��ʼ��ǰ��������
	{
		snake.locat[i].x = snake.locat[i - 1].x;
		snake.locat[i].y = snake.locat[i - 1].y;
	}

	switch (snake.direc)		//�ƶ���ͷ
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
	if (snake.locat[0].x < 0 || snake.locat[0].x > WIDTH-SIZE || snake.locat[0].y < 0 || snake.locat[0].y > HEIGHT-SIZE) //ײǽ�ж�
	{
		return true;
	}
	for (int i = 1; i < snake.len; i++)
	{
		if (snake.locat[i].x == snake.locat[0].x && snake.locat[i].y == snake.locat[0].y)		//�Գ��ж�
			return true;
	}
	return false;
}
void Restart(bool flag)
{
	if (flag)
	{
		int select = MessageBox(GetHWnd(), L"��ô�����أ�����һ����", L"��", MB_OKCANCEL);
		if (select == IDOK)	//����һ��
		{
			//���³�ʼ��
			GameInit();
		}
		else  //�˳�
		{
			exit(0);
		}
	}
}
int main()
{
	initgraph(WIDTH, HEIGHT,0);			//��������
	setbkcolor(RGB(255,148,206));	//��ɫ����
	cleardevice();					//����ɫ����

	GameInit();						//��Ϸ��ʼ��
	while(1)
	{
		CreateFood();		//����ʳ��
		EatFood();			//�ж��Ƿ񱻳�
		Move_Snake();		//���ƶ�
		GameDraw();			//���ƽ���
		Restart(GameOver());	//�ж��Ƿ����
		Sleep(100);	
	}
	closegraph();
	return 0;
}
