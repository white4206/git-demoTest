#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#define W 78  //��Ϸ���ؿ� 
#define H 26  //��Ϸ���ظ� 
int dir = 3;    //�����������ֵ3��ʾ���� 
int Flag = 0;   //����ʳ��ı�־��1��0�� 
int score = 0;  //��ҵ÷� 
struct food {
    int x;  //ʳ���x���� 
    int y;  //ʳ���y���� 
}fod;  //�ṹ��food��������Ա 
struct snake {
    int len;      //���� 
    int speed;  //�ƶ��ٶ� 
    int x[100];  //����ĳ��x���� 
    int y[100];  //����ĳ��y���� 
}snk;   //�ṹ��snk��4����Ա 
void gtxy(int x, int y)  //���ƹ���ƶ��ĺ��� 
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void gtxy(int x, int y);  //��������Ҫ�õ��ļ����Աຯ�� 
void csh();  //��ʼ������ 
void keymove(); //���������ƶ��� 
void putFod();  //Ͷ��ʳ�� 
int  Over();   //��Ϸ������1��0�� 
void Color(int a);  //�趨��ʾ��ɫ�ĺ��� 
int main()   //������ 
{
    csh();
    while (1)
    {
        Sleep(snk.speed);
        keymove();
        putFod();
        if (Over())
        {
            system("cls");
            gtxy(W / 2 + 1, H / 2); printf("��Ϸ����!T__T");
            gtxy(W / 2 + 1, H / 2 + 2); printf("����ܷ֣�%d��", score);
            _getch();
            break;
        }
    }
    return 0;
}
void csh()   //��ʼ���� 
{
    int i;
    gtxy(0, 0);
    CONSOLE_CURSOR_INFO cursor_info = { 1,0 };  //�������������ع������� 
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
    for (i = 0; i <= W; i = i + 2)  //������ҪΪż������Ϊ���Ҫ��ӡ���ַ�ռ����λ�� 
    {
        Color(2);   //���ô�ӡ��ɫΪ��ɫ 
        gtxy(i, 0);  printf("��");  //��ӡ�ϱ߿� 
        gtxy(i, H); printf("��");  //��ӡ�±߿� 
    }
    for (i = 1; i < H; i++)
    {
        gtxy(0, i); printf("��");  //��ӡ��߿� 
        gtxy(W, i); printf("��");  //��ӡ�ұ߿� 
    }
    while (1)
    {
        srand((unsigned)time(NULL));  //��ʼ�������������srand( )
        fod.x = rand() % (W - 4) + 2;  //�������rand( )����һ����0���ȣ�W-4��С1�����ټ�2 
        fod.y = rand() % (H - 2) + 1;  //�������rand( )����һ����0���ȣ�H-2��С1�����ټ�1 
        if (fod.x % 2 == 0) break;  //fod.x��ʳ��ĺ����꣬Ҫ��2�ı�����Ϊż���� 
    }
    Color(12);   //�趨��ӡ��ɫΪ���� 
    gtxy(fod.x, fod.y); printf("��");  //��ʳ�����괦��ӡ��ʼʳ�� 
    snk.len = 3;      //������ֵΪ3�� 
    snk.speed = 350;  //ˢ���ߵ�ʱ�䣬���ƶ��ٶȳ�ֵΪ350���맒
    snk.x[0] = W / 2 + 1;  //��ͷ������ҪΪż������ΪW/2=39�� 
    snk.y[0] = H / 2;    //��ͷ������ 
    Color(9);   //�趨��ӡ��ɫΪ���� 
    gtxy(snk.x[0], snk.y[0]);  printf("��");   //��ӡ��ͷ 
    for (i = 1; i < snk.len; i++)
    {
        snk.x[i] = snk.x[i - 1] + 2;  snk.y[i] = snk.y[i - 1];
        gtxy(snk.x[i], snk.y[i]);  printf("��");   //��ӡ���� 
    }
    Color(7);   //�ָ�Ĭ�ϵİ��ֺڵ� 
    return;
}
void keymove()  //���������ƶ��� 
{
    int key;
    if (_kbhit())    //���а��������ִ��������� 
    {
        key = _getch();
        if (key == 224)  //ֵΪ224��ʾ�����˷����������Ҫ�ٴλ�ȡ��ֵ 
        {
            key = _getch();
            if (key == 72 && dir != 2)dir = 1;  //72��ʾ���������Ϸ���� 
            if (key == 80 && dir != 1)dir = 2;  //80Ϊ���� 
            if (key == 75 && dir != 4)dir = 3;  //75Ϊ���� 
            if (key == 77 && dir != 3)dir = 4;  //77Ϊ���� 
        }
        if (key == 32)
        {
            while (1) if ((key = _getch()) == 32) break;
        }  //32Ϊ�ո�������������ͣ 
    }
    if (Flag == 0)   //���û��ʳ���ִ���������������β 
    {
        gtxy(snk.x[snk.len - 1], snk.y[snk.len - 1]);  printf("  ");
    }
    int i;
    for (i = snk.len - 1; i > 0; i--)  //����β��ÿ�ڴ洢ǰһ������ֵ����ͷ���⣩ 
    {
        snk.x[i] = snk.x[i - 1];  snk.y[i] = snk.y[i - 1];
    }
    switch (dir)  //�ж���ͷ�����ĸ������ƶ�������ȡ��������ֵ 
    {
    case 1: snk.y[0]--; break;   //dir=1Ҫ�����ƶ� 
    case 2: snk.y[0]++; break;  //dir=2Ҫ�����ƶ� 
    case 3: snk.x[0] -= 2; break;  //dir=3Ҫ�����ƶ� 
    case 4: snk.x[0] += 2; break;  //dir=4Ҫ�����ƶ� 
    }
    Color(9);
    gtxy(snk.x[0], snk.y[0]); printf("��");   //��ӡ��ͷ 
    if (snk.x[0] == fod.x && snk.y[0] == fod.y)   //��Ե�ʳ����ִ�����²��� 
    {
        printf("\7"); snk.len++; score += 100; snk.speed -= 5; Flag = 1;
    } //7������ 
    else Flag = 0;   //û�Ե�ʳ��flag��ֵΪ0 
    if (snk.speed < 150) snk.speed = snk.speed + 5;   //�����룬�����ٶ����޼ӿ� 
}
void putFod()  //Ͷ��ʳ�� 
{
    if (Flag == 1)  //��Ե�ʳ���ִ�����²�����������һ��ʳ�� 
    {
        while (1)
        {
            int i, n = 1;
            srand((unsigned)time(NULL));  //��ʼ�������������srand( )
            fod.x = rand() % (W - 4) + 2;  //��������Ϸ��Χ�ڵ�һ��x����ֵ 
            fod.y = rand() % (H - 2) + 1;  //��������Ϸ��Χ�ڵ�һ��y����ֵ 
            for (i = 0; i < snk.len; i++)   //������ɵ�ʳ�ﲻ�����ߵ����� 
            {
                if (fod.x == snk.x[i] && fod.y == snk.y[i]) { n = 0; break; }
            }
            if (n && fod.x % 2 == 0) break;  //n����Ϊ0�Һ�����Ϊż������ʳ������ȡֵ�ɹ� 
        }
        Color(12);  //�趨�ַ�Ϊ��ɫ 
        gtxy(fod.x, fod.y);  printf("��");   //��굽ȡ�õ����괦��ӡʳ�� 
    }
    return;
}
int Over()  //�ж���Ϸ�Ƿ�����ĺ��� 
{
    int  i;
    Color(7);
    gtxy(2, H + 1); printf("��ͣ��space.");  //���´�ӡһЩ������Ϣ 
    gtxy(2, H + 2); printf("��Ϸ�÷֣�%d", score);
    if (snk.x[0] == 0 || snk.x[0] == W) return 1;  //��ͷ�������ұ߽� 
    if (snk.y[0] == 0 || snk.y[0] == H) return 1;  //��ͷ�������±߽� 
    for (i = 1; i < snk.len; i++)
    {
        if (snk.x[0] == snk.x[i] && snk.y[0] == snk.y[i]) return 1;
    }  //��ͷ�������� 
    return 0;    //û���߽缰����ͷ���0 
}
void Color(int a)   //�趨��ɫ�ĺ��� 
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
}