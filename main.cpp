#include "TXLib.h"

struct Character
{
    int x;
    int y;
    HDC pic;
    bool visible;
    int v;
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
    int xbullet;
    int ybullet;
    bool singlefire=true;
    bool selectpistol=false;
    bool selectrifle=true;
    bool selectsniper=false;
    bool selectshotgun=false;
    const char* singlefireoninfo = "Режим стрельбы: одиночными.";
    const char* singlefireoffinfo = "Режим стрельбы: очередями.";

    Character bullet[100];
    Character protagonist = {x, y, txLoadImage ("ct.bmp"), true, 0};
    Character enemy = {xenemy, yenemy, txLoadImage ("enemy.bmp"), true, 100};
    HDC background = txLoadImage ("background.bmp");

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
    txBegin();
    txBitBlt (txDC(), 0, 0, 1600, 900, background);

    enemy.x = enemy.x-12;

    if(singlefire)
    {

        txSelectFont("Arial", 25);
        txSetColor(TX_BLACK, 3);
        txSetFillColor(TX_WHITE);
        txCircle(bullet[0].x, bullet[0].y, 5);
        bullet[0].x=bullet[0].x+(bullet[0].v+100);
        txTextOut(protagonist.x+28, protagonist.y-29, singlefireoninfo);
        txSelectFont("Arial", 23);
        txSetColor(TX_WHITE);
        txTextOut(protagonist.x+30, protagonist.y-30, singlefireoninfo);
    }
    else
    {
       for(int i=0; i<rifleburst; i++)
       {
           if(bullet[i].visible)
           {
              txSelectFont("Arial", 25);
              txSetColor(TX_BLACK, 3);
              txSetFillColor(TX_WHITE);
              txCircle(bullet[rifleburst-1].x, bullet[rifleburst-1].y, 5);
              bullet[rifleburst-1].x=bullet[rifleburst-1].x+bullet[rifleburst-1].v+28;
              txTextOut(protagonist.x+28, protagonist.y-29, singlefireoninfo);
              txSelectFont("Arial", 23);
              txSetColor(TX_WHITE);
              txTextOut(protagonist.x+30, protagonist.y-30, singlefireoffinfo);
           }
       }
    }

    if(GetAsyncKeyState(VK_RETURN))
    {
         for(int i=0; i<rifleburst; i++)
         {
             bullet[i] = {protagonist.x+305, protagonist.y+99, 0, true, 10};
         }
    }

    DrawProtagonist(protagonist);
    DrawEnemy(enemy);

    if(GetAsyncKeyState('W'))
    {
    protagonist.y=protagonist.y-35;
    }
    if(GetAsyncKeyState('S'))
    {
    protagonist.y=protagonist.y+35;
    }

    if(bullet[0].x>enemy.x+70 && bullet[0].x<enemy.x+260
        && bullet[0].y>enemy.y && bullet[0].y<enemy.y+150)
    {
    bullet[0].visible=false;
    enemy.visible=false;
    }
    else if(bullet[rifleburst-1].x>enemy.x+50 && bullet[rifleburst-1].x<enemy.x+260
        && bullet[rifleburst-1].y>enemy.y && bullet[rifleburst-1].y<enemy.y+150)
    {
    bullet[rifleburst-1].visible=false;
    enemy.visible=false;
    }

    if(!enemy.visible)
    {
       enemy.y = random(150, 700);
       enemy.x = 1700;
       enemy.visible = true;
    }

    if(GetAsyncKeyState('B'))
    {
    singlefire=false;
    }
    if(GetAsyncKeyState('N'))
    {
    singlefire=true;
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
