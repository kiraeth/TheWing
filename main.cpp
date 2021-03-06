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
    int xenemy=2500;
    int yenemy=500;
    int venemy=20;
    int enemynumber=3;
    int xbullet;
    int ybullet;
    int level = 1;
    string page = "??????? ????";
    char scoremassive[100];
    int score = 0;
    int tp = 0;

    Character bullet[100];
    Character protagonist = {x, y, txLoadImage ("ct.bmp"), true, 0};
    Character enemy = {xenemy, yenemy, txLoadImage ("enemy.bmp"), true, 100};

    Character enemies[enemynumber];
    enemies[0] = {3000, 200, enemy.pic, true, 100};
    enemies[1] = {2900, 450, enemy.pic, true, 100};
    enemies[2] = {2950, 700, enemy.pic, true, 100};

    txSelectFont("Impact", 30);
    Text first = {25, 25, "??? ??????:", true};
    Text second = {25, 50, "???? ??????: ?? ?????????? ?????? ? ??????.", true};
    Text third = {25, 75, "??????? Enter, ????? ????????", true};
    Text fourth = {25, 100, "??????? W ??? S, ????? ?????? ????? ??? ????", true};
    Text fifth = {25, 150, "??????? Q, ????? ??????? ??? ????", true};
    Text scoretext = {1500, 25, scoremassive, true};
    Text finalscoretext = {665, 225, scoremassive, true};
    HDC background = txLoadImage ("background.bmp");
    HDC backmainmenu = txLoadImage ("backmainmenu.bmp");
    HDC gameover = txLoadImage ("gameover.bmp");

    for(int i=0; i<rifleburst; i++)
    {
        bullet[i] = {protagonist.x+305, protagonist.y+99, 0, false, 10};
    }

    while(true)
    {
    txBegin();
    txClear();

    if(page=="?????")
    {
    txSelectFont("Impact", 50);
    txSetColor(TX_WHITE, 3);
    txSetFillColor(TX_BLACK);
    txBitBlt(txDC(), 0, 0, 1600, 900, gameover);
    Text gameover = {725, 125, "?? ?????????", true};
    DrawText(gameover);
    sprintf(scoremassive, "??? ????????? ????: %d", score);
    DrawText(finalscoretext);
    txRectangle(700, 500, 900, 550);
    txSelectFont("Impact", 30);
    Text gameoverbutton = {775, 510, "?????", true};
    DrawText(gameoverbutton);
    if(txMouseX() >= 700 && txMouseY() >= 500 &&
    txMouseX() <= 900 && txMouseY() <= 550 &&
    txMouseButtons() == 1)
    {
        return 0;
    }
    }

    if(page=="????")
    {
        txSelectFont("Impact", 50);
        txSetColor(TX_WHITE, 3);
        txBitBlt(txDC(), 0, 0, 1600, 900, backmainmenu);
        txSetFillColor(TX_BLACK);
        txRectangle(700, 400, 900, 450);
        Text menutext1 = {675, 150, "???? ??????????????", true};
        DrawText(menutext1);
        txSelectFont("Impact", 30);
        Text menubutton1 = {755, 410, "???????????", true};
        DrawText(menubutton1);
        if(txMouseX() >= 700 && txMouseY() >= 400 &&
        txMouseX() <= 900 && txMouseY() <= 450 &&
        txMouseButtons() == 1)
        {
            page = "????";
        }

        txRectangle(700, 500, 900, 550);
        Text menubutton2 = {775, 510, "?????", true};
        DrawText(menubutton2);
        if(txMouseX() >= 700 && txMouseY() >= 500 &&
        txMouseX() <= 900 && txMouseY() <= 550 &&
        txMouseButtons() == 1)
        {
            return 0;
        }
    }

        if(page=="??????? ????")
    {
        txSelectFont("Impact", 80);
        txSetColor(TX_WHITE, 3);
        txBitBlt(txDC(), 0, 0, 1600, 900, backmainmenu);
        txSetFillColor(TX_BLACK);
        txRectangle(700, 400, 900, 450);
        Text menutext1 = {735, 150, "?????", true};
        DrawText(menutext1);
        txSelectFont("Impact", 30);
        Text menubutton1 = {755, 410, "?????? ????", true};
        DrawText(menubutton1);
        if(txMouseX() >= 700 && txMouseY() >= 400 &&
        txMouseX() <= 900 && txMouseY() <= 450 &&
        txMouseButtons() == 1)
        {
            page = "????";
        }

        txRectangle(700, 500, 900, 550);
        Text menubutton2 = {775, 510, "?????", true};
        DrawText(menubutton2);
        if(txMouseX() >= 700 && txMouseY() >= 500 &&
        txMouseX() <= 900 && txMouseY() <= 550 &&
        txMouseButtons() == 1)
        {
            return 0;
        }
    }

    if(page=="????")
    {
        if(GetAsyncKeyState(VK_ESCAPE))
        {
            page="????";
        }


    txBitBlt (txDC(), 0, 0, 1600, 900, background);

    enemies[0].x = enemies[0].x-12;
    enemies[1].x = enemies[1].x-10;
    enemies[2].x = enemies[2].x-14;

    DrawProtagonist(protagonist);

    DrawEnemy(enemies[0]);
    DrawEnemy(enemies[1]);
    DrawEnemy(enemies[2]);

    if(enemies[enemynumber].visible)
        {
            for(int i=0; i<enemynumber; i++)
                {
                    DrawEnemy(enemies[i]);
                    enemies[i].x = enemies[i].x-5;
                }
        }

    txSetColor(TX_WHITE);
    DrawText(first);
    DrawText(second);
    DrawText(third);
    DrawText(fourth);
    DrawText(fifth);
    sprintf(scoremassive, "????: %d", score);
    DrawText(scoretext);

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
                    /*
                    enemies[i].visible=false;
                    txSleep(1000);
                    enemies[i].visible=true;
                    txSleep(1000);  */
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
            score = score + 10;
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

    for(int i=0; i<enemynumber; i++)
    {
        if(enemies[i].x<=protagonist.x)
        {
           page="?????";
        }
    }

    txEnd();

    }
    txSleep(25);
    }

    txDeleteDC (background);
    txDeleteDC (protagonist.pic);
    txDeleteDC (enemy.pic);

    return 0;
    }
