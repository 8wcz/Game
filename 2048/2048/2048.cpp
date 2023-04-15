#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<graphics.h>
#include<conio.h>
//�������ڣ�ÿ��4������

#define MAX_GRID 4 //ÿ�и�����
#define GRID_WIDTH 100 //���ӿ��
#define INTERVAL 15 //���
//ö��ÿ�������Լ���������ɫ
enum Color 
{
	zero = RGB(205, 193, 180), //�հ�
	twoTo1 = RGB(238, 228, 218), //2
	twoTo2 = RGB(237, 224, 200), //4
	twoTo3 = RGB(242, 177, 121), //8
	twoTo4 = RGB(245, 149, 99), //16
	twoTo5 = RGB(246, 124, 95), //32
	twoTo6 = RGB(246, 94, 59), //64
	twoTo7 = RGB(242, 177, 121), //128
	twoTo8 = RGB(237, 204, 97), //256
	twoTo9 = RGB(255, 0, 128), //512
	twoTo10 = RGB(145, 0, 72), //1024
	twoTo11 = RGB(242, 17, 158), //2048
	back = RGB(187, 173, 160), //����
};
Color arr[13] = {zero, twoTo1, twoTo2, twoTo3, twoTo4, twoTo5, twoTo6, twoTo7, twoTo8, twoTo9, twoTo10, twoTo11, back };
int num[12] = {0, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1048, 2048};
int map[MAX_GRID][MAX_GRID];
POINT pos[MAX_GRID][MAX_GRID];//�洢��������,����ʹ��
bool flag = false;
//���庯�����������2����4
int twoOrFour()
{
	if (rand() % 10 == 1)
	{
		return 4;
	}
	else
	{
		return 2;
	}
};
//����������λ�ò����������ŵ�������
void CreateNumber()
{
	while (1)
	{
		int x = rand() % MAX_GRID;
		int y = rand() % MAX_GRID;
		if (map[x][y] == 0)
		{
			map[x][y] = twoOrFour();
			break;
		}
		
	}
}
void GameInit()
{
	//�������������
	srand(GetTickCount());
	//�����������
	for (int i = 0; i < MAX_GRID; i++)
	{
		for (int k = 0; k < MAX_GRID; k++)
		{
			pos[i][k].x = k * GRID_WIDTH + (k + 1) * INTERVAL;
			pos[i][k].y = i * GRID_WIDTH + (i + 1) * INTERVAL;
		};
	};
	//��ʼ�����������������
	CreateNumber();
	CreateNumber();
	
};
void GameDraw()
{
	setbkcolor(back);//������ɫ
	cleardevice(); //ˢ��
	for (int i = 0; i < MAX_GRID; i++) 
	{
		for (int k = 0; k < MAX_GRID; k++) 
		{
			for (int q = 0; q < 12; q++)
			{
				if (map[i][k] == num[q])
				{
					setfillcolor(arr[q]);
					solidrectangle(pos[i][k].x, pos[i][k].y, pos[i][k].x + GRID_WIDTH, pos[i][k].y + GRID_WIDTH);
					if (map[i][k] != 0)
					{
						char number[5] = " ";
						settextstyle(50, 0, "����");
						setbkmode(TRANSPARENT); //����ģʽ��͸��
						sprintf(number, "%d", map[i][k]);
						//���־��У��ø��ӵ�һ���ȥ�ַ�����һ��
						int tempx = GRID_WIDTH / 2 - textwidth(number)/2;
						int tempy = GRID_WIDTH / 2 - textheight(number) / 2;
						outtextxy(pos[i][k].x+tempx, pos[i][k].y+tempy,number);
					}
				}
			}
		}
	}
};
//����
void moveup()
{
	for (int i = 0; i < MAX_GRID; i++)
	{
		int temp = 0;
		for (int begin = 1; begin < MAX_GRID; begin++)
		{
			if (map[begin][i] != 0)
			{
				if (map[temp][i] == 0)
				{
					map[temp][i] = map[begin][i];
					map[begin][i] = 0;
				}
				else if(map[temp][i] == map[begin][i])
				{
					map[temp][i] += map[begin][i];
					map[begin][i] = 0;
				}
				else
				{
					map[temp+1][i] = map[begin][i];
					if (temp + 1 != begin)
					{
						map[begin][i] = 0;
					}
				}
				temp++;
				flag = true;
			}
		}
	}
	printf("up\n");
}
// ����
void movedown()
{
	for (int i = 0; i < MAX_GRID; i++)
	{
		int temp = MAX_GRID-1;
		for (int begin = MAX_GRID-2; begin >=0; begin--)
		{
			if (map[begin][i] != 0)
			{
				if (map[temp][i] == 0)
				{
					map[temp][i] = map[begin][i];
					map[begin][i] = 0;
				}
				else if (map[temp][i] == map[begin][i])
				{
					map[temp][i] += map[begin][i];
					map[begin][i] = 0;
				}
				else
				{
					map[temp - 1][i] = map[begin][i];
					if (temp - 1 != begin)
					{
						map[begin][i] = 0;
					}
				}
				temp--;
				flag = true;
			}
		}
	}
	printf("down\n");
}
// ����
void moveleft()
{
	for (int i = 0; i < MAX_GRID; i++)
	{
		int temp = 0;
		for (int begin = 1; begin < MAX_GRID; begin++)
		{
			if (map[i][begin] != 0)
			{
				if (map[i][temp] == 0)
				{
					map[i][temp] = map[i][begin];
					map[i][begin] = 0;
				}
				else if (map[i][temp] == map[i][begin])
				{
					map[i][temp] += map[i][begin];
					map[i][begin] = 0;
				}
				else
				{
					map[i][temp+1] = map[i][begin];
					if (temp + 1 != begin)
					{
						map[i][begin] = 0;
					}
				}
				temp++;
				flag = true;
			}
		}
	}
	printf("left\n");
}
// ����
void moveright()
{
	for (int i = 0; i < MAX_GRID; i++)
	{
		int temp = MAX_GRID -1;
		for (int begin = MAX_GRID - 2; begin >= 0; begin--)
		{
			if (map[i][begin] != 0)
			{
				if (map[i][temp] == 0)
				{
					map[i][temp] = map[i][begin];
					map[i][begin] = 0;
				}
				else if (map[i][temp] == map[i][begin])
				{
					map[i][temp] += map[i][begin];
					map[i][begin] = 0;
				}
				else
				{
					map[i][temp - 1] = map[i][begin];
					if (temp - 1 != begin)
					{
						map[i][begin] = 0;
					}
				}
				temp--;
				flag = true;
			}
		}
	}
	printf("right\n");
}
void GameJude()
{
	if (flag)
	{
		CreateNumber();
		flag = false;
	}
}
//���̿��������ƶ�
void GameContor()
{
	//��ȡ�������룺_getch()
	char key = _getch();
	switch (key)
	{
		case 'w':
		case 'W':
		case 72:
			moveup();
			break;
		case 's':
		case 'S':
		case 80:
			movedown();
			break;
		case 'a':
		case 'A':
		case 75: 
			moveleft();
			break;
		case 'd':
		case 'D':
		case 77:
			moveright();
			break;

	}
}
int main() 
{
	//����
	initgraph(MAX_GRID * GRID_WIDTH + 5 * INTERVAL, MAX_GRID * GRID_WIDTH + 5 * INTERVAL,1);
	GameInit();
	while (1)
	{
		GameDraw();
		GameContor();
		GameJude();
	}
	
	getchar();
	return 0;
}
