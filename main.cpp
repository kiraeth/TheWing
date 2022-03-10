#include "TXLib.h"

struct Character
{
    int x;
    int y;
    HDC pic;
    bool visible;
    int v;
};

struct Text
{
    int x;
    int y;
    const char* text;
    bool visible;
};

void DrawProtagonist(Character protagonist)
{
    if(protagonist.visible)
    {
        Win32::TransparentBlt (txDC(), protagonist.x, protagonist.y, 300, 134, protagonist.pic, 0, 0, 579, 258, RGB (44, 128, 43));
    }
}

void DrawEnemy(Character enemy)
{
    if(enemy.visible)
    {
        Win32::TransparentBlt (txDC(), enemy.x, enemy.y, 260, 150, enemy.pic, 0, 0, 422, 243, RGB (44, 128, 43));
    }
}

void DrawText(Text text)
{
    if(text.visible)
    {
        txTextOut(text.x, text.y, text.text);
    }
}

int main()
{
    txCreateWindow (1600, 900);
    txDisableAutoPause();
    int x=325;
    int y=500;
    int rifleburst=3;
    int snipersingle=1;
    int shotgunsingle=6;
    int pistolsingle=1;
    int xenemy=1700;
    int yenemy=500;
    int venemy=20;
    int enemynumber=3;
    int xbullet;
    int ybullet;
    bool selectpistol=false;
    bool selectrifle=true;
    bool selectsniper=false;
    bool selectshotgun=false;

    Character bullet[100];

    Character protagonist = {x, y, txLoadImage ("ct.bmp"), true, 0};
    Character enemy = {xenemy, yenemy, txLoadImage ("enemy.bmp"), true, 100};

    Character enemies[enemynumber];
    enemies[0] = {1700, 200, enemy.pic, true, 100};
    enemies[1] = {1650, 450, enemy.pic, true, 100};
    enemies[2] = {1750, 700, enemy.pic, true, 100};

    txSelectFont("Impact", 30);
    Text first = {25, 25, "��� ������:", true};
    Text second = {25, 50, "������� Enter, ����� ��������", true};
    Text third = {25, 75, "������� W ��� S, ����� ������ ����� ��� ����", true};
    Text fourth = {25, 100, "������� G, ����� ������� ������� �����������", true};
    Text fifth = {25, 125, "������� Q, ����� ������� ��� ����", true};
    HDC background = txLoadImage ("background.bmp");

    for(int i=0; i<rifleburst; i++)
    {
        bullet[i] = {protagonist.x+305, protagonist.y+99, 0, false, 10};
    }

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
    txBegin();
    txBitBlt (txDC(), 0, 0, 1600, 900, background);

    enemy.x = enemy.x-12;

    DrawProtagonist(protagonist);

       if(enemies[enemynumber].visible)
        {
          for(int i=0; i<enemynumber; i++)
            {
                DrawEnemy(enemies[i]);
                enemies[i].x = enemies[i].x-12;
            }
        }

    txSetColor(TX_WHITE);
    DrawText(first);
    DrawText(second);
    DrawText(third);
    DrawText(fourth);
    DrawText(fifth);

    if(GetAsyncKeyState('W'))
    {
    protagonist.y=protagonist.y-35;
    }
    if(GetAsyncKeyState('S'))
    {
    protagonist.y=protagonist.y+35;
    }

    if(GetAsyncKeyState('Q'))
    {
        first.visible=false;
        second.visible=false;
        third.visible=false;
        fourth.visible=false;
        fifth.visible=false;
    }


    if(GetAsyncKeyState(VK_RETURN))
    {
         for(int i=0; i<rifleburst; i++)
         {
             bullet[i] = {protagonist.x+305, protagonist.y+99, 0, true, 10};
             bullet[i].visible = true;
         }
    }

    if(bullet[0].visible)
        {
        for(int i=0; i<rifleburst; i++)
                {
                if(bullet[i].visible)
                    {
                        txSetColor(TX_BLACK, 3);
                        txSetFillColor(TX_WHITE);
                        txCircle(bullet[rifleburst-1].x, bullet[rifleburst-1].y, 5);
                        bullet[rifleburst-1].x=bullet[rifleburst-1].x+bullet[rifleburst-1].v+28;
                    }
                }
        }

    for(int i=0; i<enemynumber; i++)
        {
        if(bullet[rifleburst-1].x>enemies[i].x+50 && bullet[rifleburst-1].x<enemies[i].x+260
        && bullet[rifleburst-1].y>enemies[i].y && bullet[rifleburst-1].y<enemies[i].y+150)
            {
                bullet[rifleburst-1].visible=false;
                enemies[i].visible=false;
            }
        }

    for(int i=0; i<enemynumber; i++)
    {
        if(!enemies[i].visible)
        {
            enemies[i].y = random(150, 700);
            enemies[i].x = random(1700, 1850);
            enemies[i].visible = true;
        }
    }

    if(protagonist.x<=325)
    {
    protagonist.x=325;
    }
    if(protagonist.y<=150)
    {
    protagonist.y=150;
    }
    if(protagonist.y>=700)
    {
    protagonist.y=700-20;
    }
    txSleep(25);
    txEnd();
    }

    txDeleteDC (background);
    txDeleteDC (protagonist.pic);
    txDeleteDC (enemy.pic);

    return 0;
    }
