/*--------------------------------------
project�� ˫��С��Ϸ
anthor��   LLz
����    �ƶ�    �桢˳ʱ����ת   �����ӵ�
���1   4568    7 9 			      0
���2   adws 	  q e 			      �ո�
--------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#define High 20  // ��Ϸ����ߴ�
#define Width 100        
// ȫ�ֱ���
int position_x, position_y, p_x, p_y, turn_a, turn_b, num_a, num_b, num_max, life_a = 10, life_b = 10; // �ɻ�λ��
int canvas[High][Width] = { 0 }; // ��ά����洢��Ϸ�����ж�Ӧ��Ԫ��
// 0Ϊ�ո�1Ϊ�ɻ�*��2Ϊ�ӵ�|��3Ϊ�л�@
int next[8][2] = { {0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1} }; //����  ����  ��  ���� 
int bullet_a[21][4];
int bullet_b[21][4];   //a b����ӵ�20����            
void gotoxy(int x, int y)  //����ƶ���(x,y)λ��
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}
void startup() // ���ݳ�ʼ��
{
	num_a = 0;
	num_b = 0;
	turn_a = 0;
	turn_b = 0;
	p_x = High / 2;
	p_y = Width * 4 / 5;
	canvas[p_x][p_y] = 5;
	position_x = High / 2;
	position_y = Width / 5;
	canvas[position_x][position_y] = 1;
}
void show()  // ��ʾ����
{
	gotoxy(0, 0);  // ����ƶ���ԭ��λ�ã������ػ�����
	int i, j;
	for (i = 0; i < High; i++)
	{
		for (j = 0; j < Width; j++)
		{
			if (i == 0 || i == High - 1 || j == 0 || j == Width - 1) {
				canvas[i][j] = 4;
				printf("0");
				continue;
			}
			if (canvas[i][j] == 0)
				printf(" ");   //   ����ո�
			else if (canvas[i][j] == 1)
				printf("N");   //   ����ɻ�a
			else if (canvas[i][j] == 2)
				printf("@");   //   ����ɻ�B
			else if (canvas[i][j] == 3)
				printf("o");   //  ����ӵ�o 
			else if (canvas[i][j] == 4)
				printf("o");   //	����ɻ�aָ�� 
			else if (canvas[i][j] == 5)
				printf("o");   //	����ɻ�bָ��  
		}
		printf("\n");
	}
	printf("A��");
	for (i = 1; i <= 10; i++)
		if (i <= life_a)
			printf("��");
		else printf(" ");
	printf("\nB: ");
	for (i = 1; i <= 10; i++)
		if (i <= life_b)
			printf("��");
		else printf(" ");
}
void updateWithoutInput()  // ���û������޹صĸ���
{
	int i, j, k;
	num_max = num_a > num_b ? num_a : num_b;
	for (i = 1; i <= num_max; i++) {
		if (bullet_a[i][2] == 0 || bullet_a[i][2] == High - 1) {
			bullet_a[i][0] = -bullet_a[i][0];
		}
		else if (bullet_a[i][3] == 0 || bullet_a[i][3] == Width - 1) {
			bullet_a[i][1] = -bullet_a[i][1];
		}
		if (bullet_b[i][2] == 0 || bullet_b[i][2] == High - 1) {
			bullet_b[i][0] = -bullet_b[i][0];
		}
		else if (bullet_b[i][3] == 0 || bullet_b[i][3] == Width - 1) {
			bullet_b[i][1] = -bullet_b[i][1];
		}
		canvas[bullet_a[i][2]][bullet_a[i][3]] = 0;
		canvas[bullet_b[i][2]][bullet_b[i][3]] = 0;
		bullet_a[i][2] += bullet_a[i][0];
		bullet_a[i][3] += bullet_a[i][1];
		bullet_b[i][2] += bullet_b[i][0];
		bullet_b[i][3] += bullet_b[i][1];
		canvas[bullet_a[i][2]][bullet_a[i][3]] = 3;
		canvas[bullet_b[i][2]][bullet_b[i][3]] = 3;
	}
	for (k = 1; k <= num_max; k++)
	{
		if (((position_x == bullet_a[k][2]) && (position_y == bullet_a[k][3])) || ((position_x == bullet_b[k][2]) && (position_y == bullet_b[k][3])))  // �л�ײ���һ�
		{
			life_a--;
			if (life_a <= 0) {
				printf("A ���ʧ�ܣ�\n");
				Sleep(3000);
				system("pause");
				exit(0);
			}
		}
		if (((p_x == bullet_a[k][2]) && (p_y == bullet_a[k][3])) || ((p_x == bullet_b[k][2]) && (p_y == bullet_b[k][3])))  // �л�ײ���һ�
		{
			life_b--;
			if (life_b <= 0) {
				printf("B ���ʧ�ܣ�\n");
				Sleep(3000);
				system("pause");
				exit(0);
			}
		}
	}
}
void updateWithInput()  // ���û������йصĸ���
{
	char input;
	if (_kbhit())  // �ж��Ƿ�������
	{
		input = _getch();  // �����û��Ĳ�ͬ�������ƶ�����������س�
		if (input == 'a' && position_y > 1)
		{
			canvas[position_x + next[turn_a][0]][position_y + next[turn_a][1]] = 0;
			canvas[position_x][position_y] = 0;
			position_y--;  // λ������
			canvas[position_x][position_y] = 1;
			canvas[position_x + next[turn_a][0]][position_y + next[turn_a][1]] = 4;
		}
		else if (input == 'd' && position_y < Width - 2)
		{
			canvas[position_x + next[turn_a][0]][position_y + next[turn_a][1]] = 0;
			canvas[position_x][position_y] = 0;
			position_y++;  // λ������
			canvas[position_x][position_y] = 1;
			canvas[position_x + next[turn_a][0]][position_y + next[turn_a][1]] = 4;
		}
		else if (input == 'w' && position_x > 1)
		{
			canvas[position_x + next[turn_a][0]][position_y + next[turn_a][1]] = 0;
			canvas[position_x][position_y] = 0;
			position_x--;  // λ������
			canvas[position_x][position_y] = 1;
			canvas[position_x + next[turn_a][0]][position_y + next[turn_a][1]] = 4;
		}
		else if (input == 's' && position_x < High - 2)
		{
			canvas[position_x + next[turn_a][0]][position_y + next[turn_a][1]] = 0;
			canvas[position_x][position_y] = 0;
			position_x++;  // λ������
			canvas[position_x][position_y] = 1;
			canvas[position_x + next[turn_a][0]][position_y + next[turn_a][1]] = 4;
		}
		else if (input == ' ' && num_a <= 20)  // �����ӵ�
		{
			num_a++;
			bullet_a[num_a][0] = next[turn_a][0];
			bullet_a[num_a][1] = next[turn_a][1];
			bullet_a[num_a][2] = position_x + bullet_a[num_a][0];
			bullet_a[num_a][3] = position_y + bullet_a[num_a][1];
			canvas[bullet_a[num_a][2]][bullet_a[num_a][3]] = 3;
		}
		else if (input == 'q')  // �ڵ������� 
		{
			canvas[position_x + next[turn_a][0]][position_y + next[turn_a][1]] = 0;
			turn_a--;
			if (turn_a < 0)
				turn_a = 7;
			canvas[position_x + next[turn_a][0]][position_y + next[turn_a][1]] = 4;
		}
		else if (input == 'e')  //  �ڵ������� 
		{
			canvas[position_x + next[turn_a][0]][position_y + next[turn_a][1]] = 0;
			turn_a++;
			if (turn_a > 7)
				turn_a = 0;
			canvas[position_x + next[turn_a][0]][position_y + next[turn_a][1]] = 4;
		}
		else if (input == '4' && position_y > 1)
		{
			canvas[p_x + next[turn_b][0]][p_y + next[turn_b][1]] = 0;
			canvas[p_x][p_y] = 0;
			p_y--;  // λ������
			canvas[p_x][p_y] = 2;
			canvas[p_x + next[turn_b][0]][p_y + next[turn_b][1]] = 5;
		}
		else if (input == '6' && p_y < Width - 2)
		{
			canvas[p_x + next[turn_b][0]][p_y + next[turn_b][1]] = 0;
			canvas[p_x][p_y] = 0;
			p_y++;  // λ������
			canvas[p_x][p_y] = 2;
			canvas[p_x + next[turn_b][0]][p_y + next[turn_b][1]] = 5;
		}
		else if (input == '8' && p_x > 1)
		{
			canvas[p_x + next[turn_b][0]][p_y + next[turn_b][1]] = 0;
			canvas[p_x][p_y] = 0;
			p_x--;  // λ������
			canvas[p_x][p_y] = 2;
			canvas[p_x + next[turn_b][0]][p_y + next[turn_b][1]] = 5;
		}
		else if (input == '5' && p_x < High - 2)
		{
			canvas[p_x + next[turn_b][0]][p_y + next[turn_b][1]] = 0;
			canvas[p_x][p_y] = 0;
			p_x++;  // λ������
			canvas[p_x][p_y] = 2;
			canvas[p_x + next[turn_b][0]][p_y + next[turn_b][1]] = 5;
		}
		else if (input == '0' && num_b <= 20)  // �����ӵ�
		{
			num_b++;
			bullet_b[num_b][0] = next[turn_b][0];
			bullet_b[num_b][1] = next[turn_b][1];
			bullet_b[num_b][2] = p_x + bullet_b[num_b][0];
			bullet_b[num_b][3] = p_y + bullet_b[num_b][1];
			canvas[bullet_b[num_b][2]][bullet_b[num_b][3]] = 3;
		}
		else if (input == '7')  // �ڵ������� 
		{
			canvas[p_x + next[turn_b][0]][p_y + next[turn_b][1]] = 0;
			turn_b--;
			if (turn_b < 0)
				turn_b = 7;
			canvas[p_x + next[turn_b][0]][p_y + next[turn_b][1]] = 5;
		}
		else if (input == '9')  //  �ڵ������� 
		{
			canvas[p_x + next[turn_b][0]][p_y + next[turn_b][1]] = 0;
			turn_b++;
			if (turn_b > 7)
				turn_b = 0;
			canvas[p_x + next[turn_b][0]][p_y + next[turn_b][1]] = 5;
		}
	}
}
int main()
{
	startup();  // ���ݳ�ʼ��
	system("color 30");
	while (1)  // ��Ϸѭ��ִ��
	{
		show();  // ��ʾ����
		updateWithoutInput();  // ���û������޹صĸ���
		updateWithInput();  // ���û������йصĸ���
	}
	return 0;
}
