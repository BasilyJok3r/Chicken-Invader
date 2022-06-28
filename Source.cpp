#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include "CC212VSGL.h"
#define pFramesLeft 4
#define G CC212VSGL ::
#define LEFT 75
#define pFramesMiddle 2
#define FramesPerSec 10
#define RIGHT 77
#define UP 72
#define DOWN 80
#define BGFrames 302
#define SPACE 32
#define pProj 7
#define chick 4
#define makeThingsBigger 1.5
#define ENTER 13
#define BACKSPACE 8

#pragma comment(lib, "CC212VSGL.lib")

int *pframes;
int *pframes1;
int *pframes2;
int *pBG;
int *pPFrames;
int *eNFrames;
int *eRFrames;
int *eOFrames;
int *eYFrames;
int *eGFrames;
int *ePFrames;
int *ePFrame;
int *hFrame;
int *lGFrame;
int *bossFrames;
int z3[9] = {0};
int score=0;
int round=1;
int speed[3] = { 15,25,35 };
int powerUp = 1;
int cou;
int *hitFrame;
int *BEFrame;
int LifeFrame;
int *PEFrame;
int SIFrame;
int ForkFrame;
char p[20];
char pNew[20]; 
int *MFrame;
int MLFrame;
bool cheat[3] = {false};
int scr;
int catLogoFrame;

class player
{
	public:
		int life=3;
		int pStatus=0;
		bool dead = false;
		int x;
		int y;
		float LcurrentFrame = 3;
		float RcurrentFrame = 0;
		float OLcurrentFrame = 1;
		float ORcurrentFrame = 2;
		float McurrentFrame = 0;
		bool doneL=false;
		bool doneR = false;
		bool enemy = false;
		bool pActive=true;

		player(int px, int py)
		{
			x = px;
			y = py;
		}
		void renderUp()
		{
			if (y >= 10)
			{
				G drawImage(pframes1[(int)McurrentFrame], x, y = y - 50, 0);
				if (McurrentFrame == 0)
					McurrentFrame = 1;
				else
					McurrentFrame = 0;
			}
			else
			{
				G drawImage(pframes1[(int)McurrentFrame], x, y = y, 0);
				if (McurrentFrame == 0)
					McurrentFrame = 1;
				else
					McurrentFrame = 0;
			}
		}
		void renderDown()
		{
			if (y <= G getWindowHeight()-100*makeThingsBigger)
			{
				G drawImage(pframes1[(int)McurrentFrame], x, y = y + 50, 0);
				if (McurrentFrame == 0)
					McurrentFrame = 1;
				else
					McurrentFrame = 0;
			}
			else
			{
				G drawImage(pframes1[(int)McurrentFrame], x, y = y, 0);
				if (McurrentFrame == 0)
					McurrentFrame = 1;
				else
					McurrentFrame = 0;
			}
		}
		void renderLeft()
		{
			if (x >= 0)
			{
				G drawImage(pframes[(int)LcurrentFrame], x = x - 50, y, 0);
				if (LcurrentFrame == 0)
				{
					doneL = true;
				}
				else
					LcurrentFrame -= 1;
			}
			else
			{
				G drawImage(pframes[(int)LcurrentFrame], x, y, 0);
				if (LcurrentFrame == 0)
					doneL = true;
				else
					LcurrentFrame -= 1;
			}
		}
		void renderOLeft()
		{
				G drawImage(pframes[(int)OLcurrentFrame], x, y, 0);
				if (OLcurrentFrame == 3)
				{
					LcurrentFrame = 3;
					OLcurrentFrame = 1;
					doneL = false;
				}
				else
					OLcurrentFrame += 1;
		}
		void renderMiddle()
		{
			G drawImage(pframes1[(int)McurrentFrame], x, y, 0);
			if (McurrentFrame == 0)
			{
				McurrentFrame += 1;
			}
			else
			{
				McurrentFrame = 0;
			}
		}
		void renderRight()
		{
			if (x <= G getWindowWidth()-95*makeThingsBigger)
			{
				G drawImage(pframes2[(int)RcurrentFrame], x = x + 50, y, 0);
				if (RcurrentFrame == 3)
				{
					doneR = true;
				}
				else
					RcurrentFrame += 1;
			}
			else
			{
				G drawImage(pframes2[(int)RcurrentFrame], x, y, 0);
				if (RcurrentFrame == 3)
					doneR = true;
				else
					RcurrentFrame += 1;
			}
		}
		void renderORight()
		{
			G drawImage(pframes2[(int)ORcurrentFrame], x, y, 0);
			if (ORcurrentFrame == 0)
			{
				RcurrentFrame = 0;
				ORcurrentFrame = 2;
				doneR = false;
			}
			else
				ORcurrentFrame -= 1;
		}
};
class enemy
{
	public:
		int life = 100;
		int x = 0, y = 0, dir = rand()%2,currentFrame, count = 0, dirx = 1,diry=1,attack=0,active=0,color=rand()%6;
		bool dead = false;
		void renderEnemy()
		{
			if (color==0)
			G drawImage(eNFrames[currentFrame], x, y, 0);
			else if (color==1)
				G drawImage(eRFrames[currentFrame], x, y, 0);
			else if (color==2)
				G drawImage(eOFrames[currentFrame], x, y, 0);
			else if (color==3)
				G drawImage(eYFrames[currentFrame], x, y, 0);
			else if (color==4)
				G drawImage(eGFrames[currentFrame], x, y, 0);
			else if (color==5)
				G drawImage(eNFrames[currentFrame], x, y, 0);
			count++;
			if (currentFrame == 3 && dir == 1 && count==2)
			{
				currentFrame = 2;
				dir = 0;
				count = 0;
			}
			else if (currentFrame == 0 && dir == 0 && count==2)
			{
				currentFrame = 1;
				dir = 1;
				count = 0;
			}
			else if (dir == 1 && count==2)
			{
				currentFrame += 1;
				count = 0;
			}
			else if (dir == 0 && count==2)
			{
				count = 0;
				currentFrame -= 1;
			}
		}
		int currentHitFrame = 0;
		int hitDone = true;
		int xSp, ySp;
		void renderHitSparks()
		{
			if (hitDone == false)
			{
				G drawImage(hitFrame[currentHitFrame], xSp, ySp, 0);
				if (currentHitFrame == 4)
					hitDone = true;
				else
					currentHitFrame++;
			}
		}
};
void updateLocation(enemy *e)
{
	int done = 0;
	for (int i = 0; i < 9; i++)
	{
		if (e[i].x >= G getWindowWidth() - 102 * makeThingsBigger && e[i].dirx == 1 && e[i].diry == 1 && e[i].dead==false)
		{
			for (i = 0; i < 9; i++)
			{
					e[i].x -= 10;
					e[i].y += 82;
					e[i].dirx = -1;
					e[i].diry = -1;
			}
			done = 1;
			break;
		}
		else if (e[i].x <= 0 && e[i].dirx == -1 && e[i].diry == -1 && e[i].dead==false)
		{
			for (i = 0; i < 9; i++)
			{
					e[i].x += 10;
					e[i].y += 82;
					e[i].dirx = 1;
					e[i].diry = 1;
			}
			done = 1;
			break;
		}
	}
	if (done != 1)
	{
		for (int i = 0; i < 9; i++)
		{
			if (e[i].x < G getWindowWidth() - 102 * makeThingsBigger && e[i].dirx == 1 && e[i].diry == 1)
			{
				for (i = 0; i < 9; i++)
					e[i].x += 10;
				break;
			}
			else if (e[i].x > 0 && e[i].dirx == -1 && e[i].diry == -1)
			{
				for (i = 0; i < 9; i++)
					e[i].x -= 10;
				break;
			}
		}
	}
}
class projectile
{
	public:
		int px, py;
		int ex, ey,damage=100;
		int bx, by;
		float currentPFrame=rand()%7;
		float currentEFrame = 0;
		int count = 0;
		bool pActive = false;
		bool eActive = false;
		bool release = false;
		bool bActive = false;
		int bShoot;
		int bSpeed = 25;
		int i;
		int count1 = 0;
		void renderpProjectile(bool enemy)
		{
				if (release)
				{
					pActive = true;
					G drawImage(pPFrames[(int)currentPFrame], px, py -= 50, 0);
					count += 1;
				}
				if (count > 10 && currentPFrame >= 6)
				{
					currentPFrame = 0;
					count = 0;
				}
				else if (count > 10 && currentPFrame <= 6)
				{
					currentPFrame += 1;
					count = 0;
				}
				if (py <= 0)
				{
					release = false;
				}
				if (release == false)
					pActive = false;
		}
		void rendereProjectile()
		{
			if (eActive)
			{
				G drawImage(ePFrame[(int)currentEFrame], ex, ey += speed[i], 0);
			}
			if (ey >= G getWindowHeight() - 15)
				eActive = false;
		}
		void renderbProjectile()
		{
			if (bShoot == 1)
				bActive=true;
			if (bActive)
			{
				G drawImage(ePFrame[(int)currentEFrame], bx, by += bSpeed, 0);
			}
			if (by >= G getWindowHeight() - 15)
				bActive = false;
		}
};
void check(projectile *eP, enemy *e, int num)
{
	if (e[num].dead == false)
	{
		e[num].attack = rand() % 2;
		if (e[num].attack == 1)
		{
			eP[num].eActive = true;
			eP[num].ex = (e[num].x) + 102 / 2 * makeThingsBigger;
			eP[num].ey = e[num].y;
		}
	}
}
void initializeNew(int xL, int yL,projectile *pP, int loc)
{
	if (powerUp == 1)
	{
		pP[loc].px = xL + 95 * makeThingsBigger / 2;
		pP[loc].py = yL;
	}
	else if (powerUp == 2)
	{
		if (cou == 0)
		{
			pP[loc].px = xL + 95 * makeThingsBigger / 3;
			pP[loc].py = yL;
			cou++;
		}
		else if (cou == 1)
		{
			pP[loc].px = xL + 95 * makeThingsBigger*2 / 3;
			pP[loc].py = yL;
			cou = 0;
		}
	}
	else if (powerUp == 3)
	{
		if (cou == 0)
		{
			pP[loc].px = xL + 95 * makeThingsBigger / 3;
			pP[loc].py = yL;
			cou++;
		}
		else if (cou == 2)
		{
			pP[loc].px = xL + 95 * makeThingsBigger * 2 / 3;
			pP[loc].py = yL;
			cou = 0;
		}
		else if (cou == 1)
		{
			pP[loc].px = xL + 95 * makeThingsBigger /2;
			pP[loc].py = yL-10;
			cou++;
		}
	}
}
void enemiesLocatiion(enemy *e, int num)
{
	int calcy = 0;
	int calc = (G getWindowWidth() * 3 / 4) / 3;
	int c = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (j == 0)
			{
				e[c].currentFrame = rand() % 4;
				e[c].x = 0;
				e[c].y = calcy;
				e[c].attack = rand() % 2;
				c++;
			}
			else
			{
				e[c].currentFrame = rand() % 4;
				e[c].x = calc * j;
				e[c].y = calcy;
				e[c].attack = rand() % 2;
				c++;
			}
		}
		calcy = calcy + makeThingsBigger*1.5 +125;
	}
}
void newEnemiesLocatiion(enemy *e, int num)
{
	int calcy = 0;
	int calc = (G getWindowWidth() * 3 / 4) / 3;
	int c = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (j == 0)
			{
				e[c].dead = false;
				c++;
			}
			else
			{
				e[c].dead = false;
				c++;
			}
		}
		calcy = calcy + makeThingsBigger * 1.5 + 125;
	}
}
class gift
{
	public:
		int active = 0,loc,x,y,currentFrame=0;
		bool lost=true;
		bool done = false;
		int  lucky = 0;
		void check()
		{
			active = rand() % 2;
		}
		void check1()
		{
			if (active == 1)
			{
				lucky = rand() % 2;
				loc = rand() % 9;
			}
		}
		void renderGift()
		{
			if (lost==false)
			if (y >= G getWindowHeight())
				lost = true;
			if (lost==false)
			G drawImage(lGFrame[currentFrame], x, y += 30, 0);
			if (currentFrame == 3)
				currentFrame = 0;
			else
				currentFrame++;
		}
		void intializeGift( enemy *e)
		{
			if (lost==true && done ==false)
				if (e[loc].dead == true)
				{
					x = e[loc].x;
					y = e[loc].y;
					lost = false;
					done = true;
				}
		}
};
class boss
{
	public:
		int x=rand()% 458, y=0,life=1000;
		int timeForBoss = 10;
		int xDir;
		int yDir;
		int time = 0;
		int lol;
		int xSp, ySp;
		int speed=10;
		int currentFrame1=rand()%5;
		int dir= rand() % 2 - 1;
		bool dead=false;
	 	int count=0;
		int hitDone;
		int currentHitFrame=0;
		void loadBossLevel()
		{
			if (dead == false)
			{
				if (y <= 0)
				{
					lol = 1;
					xDir = rand() % 3 - 1;
					yDir = rand() % 2;
					if (currentFrame1 == 4)
					{
						dir = -1;
						if (xDir == 1 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x = x + speed, y += speed, 0);
						else if (xDir == 1 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x += speed, y, 0);
						else if (xDir == 0 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x, y += speed, 0);
						else if (xDir == 0 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x, y, 0);
						else if (xDir == -1 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x -= speed, y, 0);
						else if (xDir == -1 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x -= speed, y += speed, 0);
						if (dir == 1)
							currentFrame1++;
						else
							currentFrame1--;
					}
					else if (currentFrame1 == 0)
					{
						dir = 1;
						if (xDir == 1 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x = x + speed, y += speed, 0);
						else if (xDir == 1 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x += speed, y, 0);
						else if (xDir == 0 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x, y += speed, 0);
						else if (xDir == 0 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x, y, 0);
						else if (xDir == -1 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x -= speed, y, 0);
						else if (xDir == -1 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x -= speed, y += speed, 0);
						if (dir == 1)
							currentFrame1++;
						else
							currentFrame1--;
					}
					else if (dir == 1)
					{
						if (xDir == 1 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x = x + speed, y += speed, 0);
						else if (xDir == 1 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x += speed, y, 0);
						else if (xDir == 0 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x, y += speed, 0);
						else if (xDir == 0 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x, y, 0);
						else if (xDir == -1 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x -= speed, y, 0);
						else if (xDir == -1 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x -= speed, y += speed, 0);
						currentFrame1++;
					}
					else
					{
						if (xDir == 1 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x = x + speed, y += speed, 0);
						else if (xDir == 1 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x += speed, y, 0);
						else if (xDir == 0 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x, y += speed, 0);
						else if (xDir == 0 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x, y, 0);
						else if (xDir == -1 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x -= speed, y, 0);
						else if (xDir == -1 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x -= speed, y += speed, 0);
						currentFrame1--;
					}
				}
				else if (x <= 0)
				{
					lol = 2;
					xDir = rand() % 2;
					yDir = rand() % 3 - 1;
					if (currentFrame1 == 4)
					{
						dir = -1;
						if (xDir == 1 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x = x + speed, y += speed, 0);
						else if (xDir == 1 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x += speed, y, 0);
						else if (xDir == 0 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x, y += speed, 0);
						else if (xDir == 0 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x, y, 0);
						else if (xDir == 0 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x, y -= speed, 0);
						else if (xDir == 1 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x = x + speed, y -= speed, 0);
						if (dir == 1)
							currentFrame1++;
						else
							currentFrame1--;
					}
					else if (currentFrame1 == 0)
					{
						dir = 1;
						if (xDir == 1 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x = x + speed, y += speed, 0);
						else if (xDir == 1 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x += speed, y, 0);
						else if (xDir == 0 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x, y += speed, 0);
						else if (xDir == 0 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x, y, 0);
						else if (xDir == 0 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x, y -= speed, 0);
						else if (xDir == 1 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x = x + speed, y -= speed, 0);
						if (dir == 1)
							currentFrame1++;
						else
							currentFrame1--;
					}
					else if (dir == 1)
					{
						if (xDir == 1 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x = x + speed, y += speed, 0);
						else if (xDir == 1 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x += speed, y, 0);
						else if (xDir == 0 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x, y += speed, 0);
						else if (xDir == 0 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x, y, 0);
						else if (xDir == 0 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x, y -= speed, 0);
						else if (xDir == 1 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x = x + speed, y -= speed, 0);
						currentFrame1++;
					}
					else
					{
						if (xDir == 1 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x = x + speed, y += speed, 0);
						else if (xDir == 1 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x += speed, y, 0);
						else if (xDir == 0 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x, y += speed, 0);
						else if (xDir == 0 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x, y, 0);
						else if (xDir == 0 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x, y -= speed, 0);
						else if (xDir == 1 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x = x + speed, y -= speed, 0);
						currentFrame1--;
					}
				}
				else if (x >= G getWindowWidth() - 393)
				{
					lol = 3;
					xDir = rand() % 2 - 1;
					yDir = rand() % 3 - 1;
					if (currentFrame1 == 4)
					{
						dir = -1;
						if (xDir == 0 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x, y += speed, 0);
						else if (xDir == 0 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x, y, 0);
						else if (xDir == -1 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x = x - speed, y -= speed, 0);
						else if (xDir == -1 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x -= speed, y, 0);
						else if (xDir == 0 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x, y -= speed, 0);
						else if (xDir == -1 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x -= speed, y += speed, 0);
						if (dir == 1)
							currentFrame1++;
						else
							currentFrame1--;
					}
					else if (currentFrame1 == 0)
					{
						dir = 1;
						if (xDir == 0 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x, y += speed, 0);
						else if (xDir == 0 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x, y, 0);
						else if (xDir == -1 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x = x - speed, y -= speed, 0);
						else if (xDir == -1 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x -= speed, y, 0);
						else if (xDir == 0 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x, y -= speed, 0);
						else if (xDir == -1 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x -= speed, y += speed, 0);
						if (dir == 1)
							currentFrame1++;
						else
							currentFrame1--;
					}
					else if (dir == 1)
					{
						if (xDir == 0 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x, y += speed, 0);
						else if (xDir == 0 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x, y, 0);
						else if (xDir == -1 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x = x - speed, y -= speed, 0);
						else if (xDir == -1 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x -= speed, y, 0);
						else if (xDir == 0 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x, y -= speed, 0);
						else if (xDir == -1 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x -= speed, y += speed, 0);
						currentFrame1++;
					}
					else
					{
						if (xDir == 0 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x, y += speed, 0);
						else if (xDir == 0 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x, y, 0);
						else if (xDir == -1 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x = x - speed, y -= speed, 0);
						else if (xDir == -1 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x -= speed, y, 0);
						else if (xDir == 0 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x, y -= speed, 0);
						else if (xDir == -1 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x -= speed, y += speed, 0);
						currentFrame1--;
					}
				}
				else if (y >= G getWindowHeight() - 239)
				{
					lol = 4;
					xDir = rand() % 3 - 1;
					yDir = rand() % 2 - 1;
					if (currentFrame1 == 4)
					{
						dir = -1;
						if (xDir == 1 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x += speed, y, 0);
						else if (xDir == 0 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x, y, 0);
						else if (xDir == -1 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x = x - speed, y -= speed, 0);
						else if (xDir == -1 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x -= speed, y, 0);
						else if (xDir == 0 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x, y -= speed, 0);
						else if (xDir == 1 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x = x + speed, y -= speed, 0);
						if (dir == 1)
							currentFrame1++;
						else
							currentFrame1--;
					}
					else if (currentFrame1 == 0)
					{
						dir = 1;
						if (xDir == 1 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x += speed, y, 0);
						else if (xDir == 0 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x, y, 0);
						else if (xDir == -1 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x = x - speed, y -= speed, 0);
						else if (xDir == -1 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x -= speed, y, 0);
						else if (xDir == 0 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x, y -= speed, 0);
						else if (xDir == 1 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x = x + speed, y -= speed, 0);
						if (dir == 1)
							currentFrame1++;
						else
							currentFrame1--;
					}
					else if (dir == 1)
					{
						if (xDir == 1 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x += speed, y, 0);
						else if (xDir == 0 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x, y, 0);
						else if (xDir == -1 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x = x - speed, y -= speed, 0);
						else if (xDir == -1 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x -= speed, y, 0);
						else if (xDir == 0 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x, y -= speed, 0);
						else if (xDir == 1 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x = x + speed, y -= speed, 0);
						currentFrame1++;
					}
					else
					{
						if (xDir == 1 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x += speed, y, 0);
						else if (xDir == 0 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x, y, 0);
						else if (xDir == -1 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x = x - speed, y -= speed, 0);
						else if (xDir == -1 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x -= speed, y, 0);
						else if (xDir == 0 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x, y -= speed, 0);
						else if (xDir == 1 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x = x + speed, y -= speed, 0);
						currentFrame1--;
					}
				}
				else
				{
					if (lol == 1 && time == 50)
					{
						xDir = rand() % 3 - 1;
						yDir = rand() % 2;
						time = 0;
					}
					else if (lol == 2 && time == 50)
					{
						xDir = rand() % 2;
						yDir = rand() % 3 - 1;
						time = 0;
					}
					else if (lol == 3 && time == 50)
					{
						xDir = rand() % 2 - 1;
						yDir = rand() % 3 - 1;
						time = 0;
					}
					else if (lol == 4 && time == 50)
					{
						xDir = rand() % 3 - 1;
						yDir = rand() % 2 - 1;
						time = 0;
					}
					else if (time == 50)
					{
						xDir = rand() % 2;
						yDir = rand() % 2 - 1;
						time = 0;
					}
					time++;
					if (currentFrame1 == 4)
					{
						dir = -1;
						if (xDir == 1 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x = x + speed, y += speed, 0);
						else if (xDir == 1 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x += speed, y, 0);
						else if (xDir == 0 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x, y += speed, 0);
						else if (xDir == 0 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x, y, 0);
						else if (xDir == -1 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x = x - speed, y -= speed, 0);
						else if (xDir == -1 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x -= speed, y, 0);
						else if (xDir == 0 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x, y -= speed, 0);
						else if (xDir == 1 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x = x + speed, y -= speed, 0);
						else if (xDir == -1 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x -= speed, y += speed, 0);
						if (dir == 1)
							currentFrame1++;
						else
							currentFrame1--;
					}
					else if (currentFrame1 == 0)
					{
						dir =1;
						if (xDir == 1 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x = x + speed, y += speed, 0);
						else if (xDir == 1 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x += speed, y, 0);
						else if (xDir == 0 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x, y += speed, 0);
						else if (xDir == 0 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x, y, 0);
						else if (xDir == -1 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x = x - speed, y -= speed, 0);
						else if (xDir == -1 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x -= speed, y, 0);
						else if (xDir == 0 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x, y -= speed, 0);
						else if (xDir == 1 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x = x + speed, y -= speed, 0);
						else if (xDir == -1 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x -= speed, y += speed, 0);
						if (dir == 1)
							currentFrame1++;
						else
							currentFrame1--;
					}
					else if (dir == 1)
					{
						if (xDir == 1 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x = x + speed, y += speed, 0);
						else if (xDir == 1 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x += speed, y, 0);
						else if (xDir == 0 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x, y += speed, 0);
						else if (xDir == 0 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x, y, 0);
						else if (xDir == -1 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x = x - speed, y -= speed, 0);
						else if (xDir == -1 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x -= speed, y, 0);
						else if (xDir == 0 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x, y -= speed, 0);
						else if (xDir == 1 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x = x + speed, y -= speed, 0);
						else if (xDir == -1 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x -= speed, y += speed, 0);
						currentFrame1++;
					}
					else
					{
						if (xDir == 1 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x = x + speed, y += speed, 0);
						else if (xDir == 1 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x += speed, y, 0);
						else if (xDir == 0 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x, y += speed, 0);
						else if (xDir == 0 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x, y, 0);
						else if (xDir == -1 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x = x - speed, y -= speed, 0);
						else if (xDir == -1 && yDir == 0)
							G drawImage(bossFrames[currentFrame1], x -= speed, y, 0);
						else if (xDir == 0 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x, y -= speed, 0);
						else if (xDir == 1 && yDir == -1)
							G drawImage(bossFrames[currentFrame1], x = x + speed, y -= speed, 0);
						else if (xDir == -1 && yDir == 1)
							G drawImage(bossFrames[currentFrame1], x -= speed, y += speed, 0);
						currentFrame1--;
					}
				}
			}
		}
			void renderHitSparks()
			{
				if (hitDone == false)
				{
					G drawImage(hitFrame[currentHitFrame], xSp, ySp, 0);
					if (currentHitFrame == 4)
						hitDone = true;
					else
						currentHitFrame++;
				}
			}
		bool checkIfBossDead( projectile *pP, int D)
		{
		if (life - pP[D].damage <= 0)
			{
				life = life - pP[D].damage;
				return true;
			}
			life = life - pP[D].damage;
			return false;
		}
		void checkBossHit(projectile *pP)
		{
			for (int j = 0; j < 420; j++)
				if ((y + 239  >= pP[j].py) && (x + 393 >= pP[j].px) && (y <= pP[j].py) && (x <= pP[j].px) && (dead == false) && (pP[j].pActive == true))
				{
					hitDone = false;
					xSp = pP[j].px - 43 / 2;
					ySp = pP[j].py - 36 / 2;
					currentHitFrame = 0;
					if (checkIfBossDead(pP, j) == true)
					{
						dead = true;
						score++;
					}
					pP[j].release = false;
					pP[j].pActive = false;
				}
		}
};
struct mis
{
	int num = 0;
	bool active = false;
};
int currentFrame = 0;
void renderBossExplosion(bool &render,int x,int y,bool player)
{ 
	if (player==true)
	G drawImage(PEFrame[currentFrame], x, y,0);
	else
	G drawImage(BEFrame[currentFrame], x, y, 0);
	if (currentFrame == 8)
	{
		render = true;
		currentFrame = 0;
	}
	else
		render = false;
		currentFrame++;
}

void pLoadBackground()
{
	pBG = new int [224];
	char str[30];
	float z;
	for (int i = 0; i < 224; i++)
	{
		z = i / 226.0 * 700.0;
		pBG[i] = G loadImage(str);
		G beginDraw();
		G setDrawingThickness(5);
		G setDrawingColor(RGB(0, 0, 255));
		G drawSolidRectangle(G getWindowWidth() / 2 - 720 / 2, G getWindowHeight() / 2 - 120 / 2, 720, 120);
		G setDrawingThickness(3);
		G setDrawingColor(RGB(255, 255, 255));
		G drawSolidRectangle(G getWindowWidth() / 2 - 700 / 2, G getWindowHeight() / 2 - 100 / 2,z, 100);
		sprintf(str, "images\\space\\Frame%d.png", i);
		pBG[i] = G loadImage(str);
		G resizeImage(pBG[i], G getWindowWidth(), G getWindowHeight());
		G endDraw();
	}
}
void loadChickenBoss()
{
	bossFrames = new int [5];
	bossFrames[0] = G loadImage("images\\chickBoss\\Frame0.png");
	bossFrames[1] = G loadImage("images\\chickBoss\\Frame1.png");
	bossFrames[2] = G loadImage("images\\chickBoss\\Frame2.png");
	bossFrames[3] = G loadImage("images\\chickBoss\\Frame3.png");
	bossFrames[4] = G loadImage("images\\chickBoss\\Frame4.png");
}
int currentBGFrame = 0;
void renderBG()
{
	 G drawImage(pBG[currentBGFrame], 0, 0, 0);
	 if (currentBGFrame == 223)
		 currentBGFrame = 0;
	 else
		 currentBGFrame ++;
}
void pLoadFramesLeft()
{
	pframes = new int[pFramesLeft];
		pframes[0] = G loadImage("images\\sLeft\\frame 1.png");
		pframes[1] = G loadImage("images\\sLeft\\frame 2.png");
		pframes[2] = G loadImage("images\\sLeft\\frame 3.png");
		pframes[3] = G loadImage("images\\sLeft\\frame 4.png");
		for (int i = 0; i < pFramesLeft; i++)
			G resizeImage(pframes[i], 85 * makeThingsBigger, 96 * makeThingsBigger);
}

void pLoadFramesMiddle()
{
	pframes1 = new int[pFramesMiddle];
	pframes1[0] = G loadImage("images\\sMiddle\\frame 5.png");
	pframes1[1] = G loadImage("images\\sMiddle\\frame 6.png");
	for (int i = 0; i < pFramesMiddle; i++)
		G resizeImage(pframes1[i], 85 *makeThingsBigger, 96 * makeThingsBigger);
}
void pLoadFramesRight()
{
	pframes2 = new int[pFramesLeft];
		pframes2[0] = G loadImage("images\\sRight\\frame 7.png");
		pframes2[1] = G loadImage("images\\sRight\\frame 8.png");
		pframes2[2] = G loadImage("images\\sRight\\frame 9.png");
		pframes2[3] = G loadImage("images\\sRight\\frame 10.png");
		for (int i = 0; i < pFramesLeft; i++)
			G resizeImage(pframes2[i], 85 * makeThingsBigger, 96 * makeThingsBigger);
}
void pLoadFramesProjectile()
{
	pPFrames = new int[pProj];
	pPFrames[0] = G loadImage("images\\projectiles\\pFrame1.png");
	pPFrames[1] = G loadImage("images\\projectiles\\pFrame2.png");
	pPFrames[2] = G loadImage("images\\projectiles\\pFrame3.png");
	pPFrames[3] = G loadImage("images\\projectiles\\pFrame4.png");
	pPFrames[4] = G loadImage("images\\projectiles\\pFrame5.png");
	pPFrames[5] = G loadImage("images\\projectiles\\pFrame6.png");
	pPFrames[6] = G loadImage("images\\projectiles\\pFrame7.png");
	for (int i = 0; i < pProj; i++)
		G resizeImage(pPFrames[i],  4* makeThingsBigger,  16* makeThingsBigger);
}
void eNLoad()
{
	eNFrames = new int[chick];
	eNFrames[0] = G loadImage("images\\chicken\\ChickNorm\\Frame1.png");
	eNFrames[1] = G loadImage("images\\chicken\\ChickNorm\\Frame2.png");
	eNFrames[2] = G loadImage("images\\chicken\\ChickNorm\\Frame3.png");
	eNFrames[3] = G loadImage("images\\chicken\\ChickNorm\\Frame4.png");
	for (int i = 0; i < chick ; i++)
		G resizeImage(eNFrames[i], 102*makeThingsBigger, 82*makeThingsBigger);
}
void eRLoad()
{
	eRFrames = new int[chick];
	eRFrames[0] = G loadImage("images\\chicken\\ChickRed\\Frame1.png");
	eRFrames[1] = G loadImage("images\\chicken\\ChickRed\\Frame2.png");
	eRFrames[2] = G loadImage("images\\chicken\\ChickRed\\Frame3.png");
	eRFrames[3] = G loadImage("images\\chicken\\ChickRed\\Frame4.png");
	for (int i = 0; i < chick; i++)
		G resizeImage(eRFrames[i], 102 * makeThingsBigger, 82 * makeThingsBigger);
}
void eOLoad()
{
	eOFrames = new int[chick];
	eOFrames[0] = G loadImage("images\\chicken\\ChickOrange\\Frame1.png");
	eOFrames[1] = G loadImage("images\\chicken\\ChickOrange\\Frame2.png");
	eOFrames[2] = G loadImage("images\\chicken\\ChickOrange\\Frame3.png");
	eOFrames[3] = G loadImage("images\\chicken\\ChickOrange\\Frame4.png");
	for (int i = 0; i < chick; i++)
		G resizeImage(eOFrames[i], 102 * makeThingsBigger, 82 * makeThingsBigger);
}
void eYLoad()
{
	eYFrames = new int[chick];
	eYFrames[0] = G loadImage("images\\chicken\\ChickYellow\\Frame1.png");
	eYFrames[1] = G loadImage("images\\chicken\\ChickYellow\\Frame2.png");
	eYFrames[2] = G loadImage("images\\chicken\\ChickYellow\\Frame3.png");
	eYFrames[3] = G loadImage("images\\chicken\\ChickYellow\\Frame4.png");
	for (int i = 0; i < chick; i++)
		G resizeImage(eYFrames[i], 102 * makeThingsBigger, 82 * makeThingsBigger);
}
void eGLoad()
{
	eGFrames = new int[chick];
	eGFrames[0] = G loadImage("images\\chicken\\ChickGreen\\Frame1.png");
	eGFrames[1] = G loadImage("images\\chicken\\ChickGreen\\Frame2.png");
	eGFrames[2] = G loadImage("images\\chicken\\ChickGreen\\Frame3.png");
	eGFrames[3] = G loadImage("images\\chicken\\ChickGreen\\Frame4.png");
	for (int i = 0; i < chick; i++)
		G resizeImage(eGFrames[i], 102 * makeThingsBigger, 82 * makeThingsBigger);
}
void ePLoad()
{
	ePFrames = new int[chick];
	ePFrames[0] = G loadImage("images\\chicken\\ChickPurple\\Frame1.png");
	ePFrames[1] = G loadImage("images\\chicken\\ChickPurple\\Frame2.png");
	ePFrames[2] = G loadImage("images\\chicken\\ChickPurple\\Frame3.png");
	ePFrames[3] = G loadImage("images\\chicken\\ChickPurple\\Frame4.png");
	for (int i = 0; i < chick; i++)
		G resizeImage(ePFrames[i], 102 * makeThingsBigger, 82 * makeThingsBigger);
}
void eLoadProjectile()
{
	ePFrame = new int[1];
	ePFrame[0] = G loadImage("images\\projectiles\\ePFrame1.png");
	G resizeImage(ePFrame[0], 12 * makeThingsBigger, 15 * makeThingsBigger);
}
void loadHit()
{
	hFrame = new int[8];
	hFrame[0] = G loadImage("images\\explosion\\Frame1.png");
	hFrame[1] = G loadImage("images\\explosion\\Frame2.png");
	hFrame[2] = G loadImage("images\\explosion\\Frame3.png");
	hFrame[3] = G loadImage("images\\explosion\\Frame4.png");
	hFrame[4] = G loadImage("images\\explosion\\Frame5.png");
	hFrame[5] = G loadImage("images\\explosion\\Frame6.png");
	hFrame[6] = G loadImage("images\\explosion\\Frame7.png");
	hFrame[7] = G loadImage("images\\explosion\\Frame8.png");
}
void loadGiftFrames()
{
	lGFrame = new int[4];
	lGFrame[0] = G loadImage("images\\gift\\frame0.png");
	lGFrame[1] = G loadImage("images\\gift\\frame1.png");
	lGFrame[2] = G loadImage("images\\gift\\frame2.png");
	lGFrame[3] = G loadImage("images\\gift\\frame3.png");
}
void loadHitSparks()
{
	hitFrame = new int[5];
	hitFrame[0] = G loadImage("images\\hitSparks\\Frame5.png");
	hitFrame[1] = G loadImage("images\\hitSparks\\Frame4.png");
	hitFrame[2] = G loadImage("images\\hitSparks\\Frame3.png");
	hitFrame[3] = G loadImage("images\\hitSparks\\Frame2.png");
	hitFrame[4] = G loadImage("images\\hitSparks\\Frame1.png");
}
void loadBigExplosion()
{
	BEFrame = new int[9];
	BEFrame[0] = G loadImage("images\\bossExplosion\\BEFrame1.png");
	BEFrame[1] = G loadImage("images\\bossExplosion\\BEFrame2.png");
	BEFrame[2] = G loadImage("images\\bossExplosion\\BEFrame3.png");
	BEFrame[3] = G loadImage("images\\bossExplosion\\BEFrame4.png");
	BEFrame[4] = G loadImage("images\\bossExplosion\\BEFrame5.png");
	BEFrame[5] = G loadImage("images\\bossExplosion\\BEFrame6.png");
	BEFrame[6] = G loadImage("images\\bossExplosion\\BEFrame7.png");
	BEFrame[7] = G loadImage("images\\bossExplosion\\BEFrame8.png");
	BEFrame[8] = G loadImage("images\\bossExplosion\\BEFrame9.png");
}
void loadPlayerExplosion()
{
	PEFrame = new int[9];
	PEFrame[0] = G loadImage("images\\bossExplosion\\BEFrame1.png");
	PEFrame[1] = G loadImage("images\\bossExplosion\\BEFrame2.png");
	PEFrame[2] = G loadImage("images\\bossExplosion\\BEFrame3.png");
	PEFrame[3] = G loadImage("images\\bossExplosion\\BEFrame4.png");
	PEFrame[4] = G loadImage("images\\bossExplosion\\BEFrame5.png");
	PEFrame[5] = G loadImage("images\\bossExplosion\\BEFrame6.png");
	PEFrame[6] = G loadImage("images\\bossExplosion\\BEFrame7.png");
	PEFrame[7] = G loadImage("images\\bossExplosion\\BEFrame8.png");
	PEFrame[8] = G loadImage("mages\\bossExplosion\\BEFrame9.png");
	for (int i = 0; i< 9; i++)
		G resizeImage(PEFrame[i], 869 / 4, 658 / 4);
} 
void loadMis()
{
	MFrame = new int[4];
	MFrame[0] = G loadImage("images\\missile\\Frame1.png");
	MFrame[1] = G loadImage("images\\missile\\Frame2.png");
	MFrame[2] = G loadImage("images\\missile\\Frame3.png");
	MFrame[3] = G loadImage("images\\missile\\Frame4.png");
}
void loadCatLogo()
{
	catLogoFrame = G loadImage("images\\CatLogo\\cat.jpg");
	G resizeImage(catLogoFrame, G getWindowWidth(), G getWindowHeight());
}
void renderCat()
{
	G beginDraw();
	G drawImage(catLogoFrame,0,0,0);
	G endDraw();
	Sleep(3000);
}
void loadMisLogo()
{
	MLFrame = G loadImage("images\\MisLogo\\Frame1.png");
}
void loadfork()
{
	ForkFrame=G loadImage("images\\Fork\\ForkFrame.png");
}
void loadStartIntro()
{
	SIFrame = G loadImage("images\\StartIntro\\SIFrame1.png");
	G resizeImage(SIFrame, 235 * makeThingsBigger, 121 * makeThingsBigger);
}
void LoadLife()
{
	LifeFrame = G loadImage("images\\life\\life.png");
	G resizeImage(LifeFrame, 11 * makeThingsBigger*2, 12 * makeThingsBigger*2);
}
void Pcheck(projectile *pP, int num)
{
	for (int i = 0; i <= num; i++)
		pP[i].release = false;
}
int check1(projectile *pP)
{
	for (int i = 0; i < 9; i++)
		if (pP[i].eActive == true)
			return 0;
	return 1;
}
void RenderLife(int x,int y)
{
	G drawImage(LifeFrame, x, y, 0);
}
int checkBoss(projectile *bP)
{
	for (int i = 0; i < 9; i++)
		if (bP[i].bActive == true)
			return 0;
	return 1;
}
bool checkIfDead(enemy *e, projectile *pP, int L, int D)
{
	if (e[L].life - pP[D].damage <= 0)
	{
		e[L].life = e[L].life - pP[D].damage;
		return true;
	}
	e[L].life = e[L].life - pP[D].damage;
	return false;
}
int checkGiftGrabbed(player pSpace, gift gif,mis &misle)
{
	if ((pSpace.y + 96 * makeThingsBigger >= gif.y) && (pSpace.x + 85 * makeThingsBigger >= gif.x) && (pSpace.x<=gif.x+58*makeThingsBigger) && (pSpace.y<=gif.y+55*makeThingsBigger)&& gif.lost==false)
	{
		if (gif.lucky == 0 && powerUp < 3)
			powerUp++;
		else if (gif.lucky == 1)
			misle.num++;
		return 1;
	}
	return 0;
}
void checkHit(enemy *e, projectile *pP)
{
	for (int i = 0; i < 9; i++)
		for(int j=0;j<420;j++)
			if ((e[i].y + 82 * makeThingsBigger >= pP[j].py) && (e[i].x + 102 * makeThingsBigger >= pP[j].px) && (e[i].y <= pP[j].py) && (e[i].x <= pP[j].px) && (e[i].dead==false) && (pP[j].pActive==true))
			{
				e[i].hitDone = false;
				e[i].xSp = pP[j].px - 43 / 2;
				e[i].ySp = pP[j].py - 36 / 2;
				e[i].currentHitFrame = 0;
				if (checkIfDead(e,pP,i,j) == true)
				{
					e[i].dead = true;
					score++;
				}
				pP[j].release = false;
				pP[j].pActive = false;
			}
}
void checkBossHit(boss bos, projectile *pP)
{
		for (int j = 0; j < 420; j++)
			if ((bos.y + 239 * makeThingsBigger >= pP[j].py) && (bos.x + 393 * makeThingsBigger >= pP[j].px) && (bos.y <= pP[j].py) && (bos.x <= pP[j].px) && (bos.dead == false) && (pP[j].pActive == true))
			{
				if (bos.checkIfBossDead(pP, j) == true)
				{
					bos.dead = true;
					score++;
				}
				pP[j].release = false;
				pP[j].pActive = false;
			}
}
int CheckPlayerHit(projectile *eP,player &pSpace,int num)
{
	if (pSpace.pActive == true)
	{
		for (int j = 0; j <= num; j++)
			if ((pSpace.y + 96 * makeThingsBigger >= eP[j].ey) && (pSpace.x + 85 * makeThingsBigger >= eP[j].ex) && (pSpace.y <= eP[j].ey) && (pSpace.x <= eP[j].ex) && (pSpace.dead == false) && (eP[j].eActive == true))
			{
				pSpace.life -= 1;
				eP[j].release = false;
				eP[j].eActive = false;
				return 1;
			}
	}
	return 0;
}
int CheckPlayerBossHit(projectile *eP, player &pSpace, int num)
{
	if (pSpace.pActive == true)
	{
		for (int j = 0; j <= num; j++)
			if ((pSpace.y + 96 * makeThingsBigger >= eP[j].by) && (pSpace.x + 85 * makeThingsBigger >= eP[j].bx) && (pSpace.y <= eP[j].by) && (pSpace.x <= eP[j].bx) && (pSpace.dead == false) && (eP[j].bActive == true))
			{
				pSpace.life -= 1;
				eP[j].release = false;
				eP[j].bActive = false;
				return 1;
			}
	}
	return 0;
}
int CheckPlayerChickHit(enemy *e, player &pSpace, int num)
{
	if (pSpace.pActive == true)
	{
		for (int j = 0; j <= num; j++)
			if ((pSpace.y + 96 * makeThingsBigger >= e[j].y) && (pSpace.x + 85 * makeThingsBigger >= e[j].x) && (pSpace.y <= e[j].y+82 * makeThingsBigger) && (pSpace.x <= e[j].x+ 102 * makeThingsBigger) && (pSpace.dead == false) && (e[j].dead == false))
			{
				pSpace.life -= 1;
				return 1;
			}
	}
	return 0;
}
int CheckPlayerBHit(boss bos, player &pSpace)
{
	if (pSpace.pActive == true)
	{
			if ((pSpace.y + 96 * makeThingsBigger >= bos.y) && (pSpace.x + 85 * makeThingsBigger >= bos.x) && (pSpace.y <= bos.y + 239) && (pSpace.x <= bos.x + 393) && (pSpace.dead == false) && (bos.dead == false))
			{
				pSpace.life -= 1;
				return 1;
			}
	}
	return 0;
}
void renderEHit(enemy *e)
{
	for (int i = 0; i < 9; i++)
	{
		int currentFrame = 0;
		if (e[i].dead == true && e[i].active==0)
		{
			if (z3[i] <= 1)
			{
				G drawImage(e[i].currentFrame += 1, e[i].x, e[i].y, 0);
				G drawImage(hFrame[z3[i]], e[i].x + (51 - 19)*makeThingsBigger, e[i].y + (41 - 19.5)*makeThingsBigger, 0);
				z3[i]++;
			}
			else if (z3[i] == 7)
			{
				G drawImage(hFrame[7], e[i].x + (51 - 19)*makeThingsBigger, e[i].y + (41 - 19.5)*makeThingsBigger, 0);
				e[i].active = 1;
			}
			else
			{
				G drawImage(hFrame[z3[i]], e[i].x + (51 - 19)*makeThingsBigger, e[i].y + (41 - 19.5)*makeThingsBigger, 0);
				z3[i]++;
			} 
		}
	}
}
bool checkEnemies(enemy *e)
{
	for (int i = 0; i < 9; i++)
		if (e[i].dead == false)
			return false;
	return true;
}
int currentTime = 0;
int z1 = 7;
int thick=1;
int rad=190;
int dir = 1;
void renderspawn(player &pSpace,bool &spawn)
{
	G setDrawingColor(BLUE);
	if (currentTime == z1)
	{
		dir = dir * -1;
		z1 += 7;
		G setDrawingThickness(thick);
		G drawCircle(pSpace.x - (rad / 2 - 85 * makeThingsBigger / 2), pSpace.y - (rad / 2 - 96 * makeThingsBigger / 2), rad);
	}
	else if (dir == -1)
	{
		G setDrawingThickness(thick);
		G drawCircle(pSpace.x - (rad / 2 - 85 * makeThingsBigger / 2), pSpace.y - (rad / 2 - 96 * makeThingsBigger / 2), rad);
		rad += 2;
		thick--;
	}
	else if (dir==1)
	{
		G setDrawingThickness(thick);
		G drawCircle(pSpace.x - (rad / 2 - 85 * makeThingsBigger / 2), pSpace.y - (rad/ 2 - 96 * makeThingsBigger / 2), rad);
		rad-=2;
		thick++;
	}
	if (currentTime == 30)
	{
		spawn = false;
		currentTime = 0;
		pSpace.pActive = true;
		z1 = 0;
	}
	else
		currentTime++;
}
FILE *InFile;
void getInfo(int &score,bool &getInfoDone,int ch3)
{
		renderBG();
		int loc = G getWindowWidth() / 2;
		InFile = fopen("save file\\sav.txt", "r");
			fscanf(InFile, "NickName=%s\nHighestScore=%d", &p, &scr);
		fclose(InFile);
		if (ch3 == 0)
		{
			printf("plz enter you name: ");
			gets_s(pNew);
			InFile = fopen("save file\\sav.txt", "w");
			fprintf(InFile, "NickName=%s\nHighestScore=%d", pNew, scr);
			fclose(InFile);
		}
		getInfoDone = true;
}
int currentFrame2 = 0;
int currenty = 0;
int currentx = 0;
bool renderlol=true;
void rendermisle(mis &misle,enemy *e,boss &bos)
{
	G drawImage(MFrame[currentFrame2], currentx,currenty-=10 , 0);
	if (currenty <= G getWindowHeight()/2)
	{
		for (int i = 0; i < 10; i++)
			e[i].dead = true;
		if (bos.timeForBoss==round)
		bos.dead = true;
		renderlol = false;
		misle.active = false;
	}
	if (currentFrame2 == 3)
		currentFrame2 = 0;
	else
		currentFrame2++;
}
unsigned char ch1;
int loc=0;
void startIntro(bool &StartIntro, int &ch3)
{
	int locy = G getWindowHeight() / 2 - 100 / 2 - 100;
	while (true)
	{
		G beginDraw();
		renderBG();
		if (kbhit())
		{
			ch1 = getch();
			if (ch1 == ' ' && loc==0)
			{
				StartIntro = false;
				ch3 = loc;
				break;
			}
			else if (ch1==' ' && loc==1)
			{
				StartIntro = false;
				ch3 = loc;
				break;
			}
			if (ch1 == 224)
			{
				ch1 = getch();
				if (ch1 == DOWN)
				{
					if (loc == 0)
					{
						locy = G getWindowHeight() / 2 - 100 / 2 + 100;
						loc++;
					}
				}
				else if (ch1 == UP)
				{
					if (loc == 1)
					{
						locy = G getWindowHeight() / 2 - 100 / 2 - 100;
						loc--;
					}
				}
			}
		}
		G drawImage(SIFrame, G getWindowWidth() / 2 - 235 * makeThingsBigger / 2, 30 * makeThingsBigger, 0);
		G setDrawingColor(RGB(0, 0, 85));
		G drawSolidEllipse(G getWindowWidth() / 2 - 300 / 2, G getWindowHeight() / 2 - 100 / 2 - 100, 300, 100);
		G setDrawingColor(RGB(0, 0, 85));
		G drawSolidEllipse(G getWindowWidth() / 2 - 300 / 2, G getWindowHeight() / 2 - 100 / 2 + 100, 300, 100);
		if (loc==0)
			G setDrawingColor(RGB(0, 0, 255));
		else
		G setDrawingColor(RGB(0, 0, 128));
		G setDrawingThickness(5);
		G drawEllipse(G getWindowWidth() / 2 - 300 / 2, G getWindowHeight() / 2 - 100 / 2 - 100, 305, 105);
		if (loc==1)
			G setDrawingColor(RGB(0, 0, 255));
		else
		G setDrawingColor(RGB(0, 0, 128));
		G drawEllipse(G getWindowWidth() / 2 - 300 / 2, G getWindowHeight() / 2 - 100 / 2 + 100, 305, 105);
		G setFontSizeAndBoldness(50, 50);
		G setDrawingColor(RGB(255, 255, 255));
		G drawText(G getWindowWidth() / 2 - 300 / 2 + 35, G getWindowHeight() / 2 - 100 / 2 - 100 + 25, "NEW GAME");
		G drawImage(ForkFrame, G getWindowWidth() / 2 - 300 / 2 - 70, locy, 0);
		G setFontSizeAndBoldness(50, 50);
		G setDrawingColor(RGB(255, 255, 255));
		G drawText(G getWindowWidth() / 2 - 300 / 2 + 35, G getWindowHeight() / 2 - 100 / 2 + 100 + 25, "CONTINUE");
		G setFontSizeAndBoldness(20, 50);
		G setDrawingColor(RGB(255, 255, 255));
		G drawText(0, G getWindowHeight() - 80, "arrow keys for movement");
		G drawText(0, G getWindowHeight() - 60, "space key for selection and firing");
		G drawText(0, G getWindowHeight() - 40, "e key to exit");
		G drawText(0, G getWindowHeight() - 20, "s keys to launch missile");
		G endDraw();
	}
}
void waitForTime(int start)
{
	while (1)
	{
		float  t = (clock() / (float)CLOCKS_PER_SEC * 1000.0f - start / (float)CLOCKS_PER_SEC * 1000.0f);
		if (t > 1.0f / FramesPerSec * 1000.0f)
			break;
	}
}
int main()
{
	G setup();
	G setFullScreenMode();
	G hideCursor();
	int frameRateLimit = 0;
	int spaceCount = 0,IL;
	int current = 0, cou = 0, z = 0;
	int ch3;
	bool z1, done = false;
	bool doneBoss=true;
	bool render;
	bool renderP=true;
	int timeLimit = 0;
	bool spawn = false;
	bool StartIntro = true;
	int GodCount = 0;
	bool getInfoDone = false;
	char str3[50];
	int rol = 0;
	enemy e[9];
	player pSpace(G getWindowWidth() / 2, G getWindowHeight() - 96 * makeThingsBigger);
	gift gif;
	boss bos;
	mis misle;
	pLoadBackground();
	loadCatLogo();
	pLoadFramesLeft();
	pLoadFramesMiddle();
	pLoadFramesRight();
	pLoadFramesProjectile();
	eNLoad();
	eRLoad();
	eOLoad();
	eYLoad();
	eGLoad();
	ePLoad();
	enemiesLocatiion(e, 9);
	eLoadProjectile();
	loadChickenBoss();
	loadHit();
	loadGiftFrames();
	loadHitSparks();
	loadBigExplosion();
	LoadLife();
	loadPlayerExplosion();
	loadStartIntro();
	loadfork();
	loadMis();
	loadMisLogo();
	renderCat();
	projectile pP[420], eP[9],bP[10];
	char str_R[20];
	while (1)
	{
		frameRateLimit = clock();
		srand(clock());
		G beginDraw();
		renderBG();
		if (StartIntro == true)
		{
			startIntro(StartIntro,ch3);
		}
		else if (getInfoDone==false)
			{
				int score;
				getInfo(score,getInfoDone,ch3);
			}
		else
		{
			if (cou <= 30 && doneBoss == true)
				done = false;
			if (cou == 31)
			{
				cou = 0;
				round++;
				done = true;
			}
			if (doneBoss == false)
			{
				if (bos.dead == false)
				{
					if (checkBoss(bP) == 1)
					{
						for (int j = 0; j < 10; j++)
							bP[j].bShoot = rand() % 2;
					}
					for (int i = 0; i < 10; i++)
					{
						if (bP[i].bActive == false)
						{
							bP[i].bx = bos.x + 394 / 3 + rand() % (394 / 3);
							bP[i].by = bos.y + rand() % 240;
						}
						bP[i].renderbProjectile();
					}
				}
			}
			if (bos.timeForBoss == round)
			{
				if (rol == 0)
				bos.dead = false;
				rol = 1;
				bos.loadBossLevel();
				bos.checkBossHit(pP);
				if (bos.dead == true)
				{
					renderBossExplosion(render, bos.x - (869 / 2 - 393 / 2), bos.y - (658 / 2 - 239 / 2), false);
					if (render == done)
					{
						doneBoss = true;
						round++;
					}
				}
				else
					doneBoss = false;
				if (doneBoss == true)
				{
					bos.timeForBoss += 10;
					bos.speed += 10;
					for (int i = 0; i < 10; i++)
						bP[i].bSpeed += 10;
					render = false;
					rol = 0;
					if (bos.life < 10000)
						bos.life = round * 100;
					for (int i = 0; i < 10; i++)
					{
						bP[i].bx = -100;
						bP[i].by = -100;
						bP[i].bActive = false;
					}
				}
			}
			z1 = checkEnemies(e);
			if (z1 == true && done == true && doneBoss == true)
			{
				newEnemiesLocatiion(e, 9);
				enemiesLocatiion(e, 9);
				for (int i = 0; i < 9; i++)
				{
					e[i].life = 10 * (round);
					e[i].active = 0;
					z3[i] = 0;
				}
				for (int i = 0; i < 3; i++)
					speed[i] = speed[i] + 1;
				for (int i = 0; i < 10; i++)
					eP[i].eActive = false;
				for (int i = 0; i < 420; i++)
				{
					pP[i].release = false;
					pP[i].pActive = false;
				}
				for (int i = 0; i < 10; i++)
					e[i].color = rand() % 6;
				spaceCount = 0;
				gif.check();
				if (gif.active == 1)
				{
					gif.check1();
					gif.lost = true;
					gif.done = false;
				}
			}
			else if ((z1 == true || round == 1) && cou < 31 && doneBoss == true)
			{
				sprintf(str_R, "WAVE %d", round);
				G setDrawingColor(RGB(255, 255, 255));
				G setFontSizeAndBoldness(100, 500);
				G drawText((G getWindowWidth() - 500) / 2, (G getWindowHeight() - 100) / 2, str_R);
				cou++;
			}
			if (kbhit())
			{
				unsigned char ch = getch();
				if (ch == 'e')
					return 0;
				else if (ch == ' ')
				{
					if (spaceCount == 420 && pP[spaceCount - 1].release == false)
					{
						if (pSpace.dead == false)
							pSpace.renderMiddle();
						Pcheck(pP, spaceCount - 1);
						pP[spaceCount - 1].release = false;
						spaceCount = 0;
						if (powerUp == 1)
						{
							spaceCount++;
							initializeNew(pSpace.x, pSpace.y, pP, spaceCount - 1);
						}
						else if (powerUp == 2)
						{
							spaceCount += 2;
							initializeNew(pSpace.x, pSpace.y, pP, spaceCount - 1);
							initializeNew(pSpace.x, pSpace.y, pP, spaceCount - 2);
						}
						else if (powerUp == 3)
						{
							spaceCount += 3;
							initializeNew(pSpace.x, pSpace.y, pP, spaceCount - 1);
							initializeNew(pSpace.x, pSpace.y, pP, spaceCount - 2);
							initializeNew(pSpace.x, pSpace.y, pP, spaceCount - 3);
						}
					}
					else if (spaceCount < 420)
					{
						if (pSpace.dead == false)
							pSpace.renderMiddle();
						if (powerUp == 1)
						{
							spaceCount++;
							initializeNew(pSpace.x, pSpace.y, pP, spaceCount - 1);
							pP[spaceCount - 1].release = true;
						}
						else if (powerUp == 2)
						{
							spaceCount += 2;
							initializeNew(pSpace.x, pSpace.y, pP, spaceCount - 1);
							initializeNew(pSpace.x, pSpace.y, pP, spaceCount - 2);
							pP[spaceCount - 1].release = true;
							pP[spaceCount - 2].release = true;
						}
						else if (powerUp == 3)
						{
							spaceCount += 3;
							initializeNew(pSpace.x, pSpace.y, pP, spaceCount - 1);
							initializeNew(pSpace.x, pSpace.y, pP, spaceCount - 2);
							initializeNew(pSpace.x, pSpace.y, pP, spaceCount - 3);
							pP[spaceCount - 1].release = true;
							pP[spaceCount - 2].release = true;
							pP[spaceCount - 3].release = true;
						}
					}
				}
				else if (ch == 's')
				{
					if (misle.num > 0)
					{
						currenty = pSpace.y;
						currentx = pSpace.x;
						misle.num--;
						misle.active = true;
					}
				}
				else if (ch == '=')
					cheat[0] = true;
				else if (ch == '-')
					cheat[1] = true;
				else if (ch == ENTER)
					cheat[2] = true;
				if (ch == 224)
				{
					char ch = getch();
					if (ch == LEFT)
					{
						if (pSpace.dead == false)
							pSpace.renderLeft();
					}
					else if (ch == RIGHT)
					{
						if (pSpace.dead == false)
							pSpace.renderRight();
					}
					else if (ch == UP)
					{
						if (pSpace.dead == false)
							pSpace.renderUp();
					}
					else if (ch == DOWN)
					{
						if (pSpace.dead == false)
							pSpace.renderDown();
					}
				}
			}
			else if (pSpace.doneL)
			{
				if (pP[spaceCount - 1].release == false)
				{
					Pcheck(pP, spaceCount - 1);
					pP[spaceCount - 1].release = false;
					spaceCount = 0;
				}
				if (pSpace.dead == false)
					pSpace.renderOLeft();
			}
			else if (pSpace.doneR)
			{
				if (pP[spaceCount - 1].release == false)
				{
					Pcheck(pP, spaceCount - 1);
					pP[spaceCount - 1].release = false;
					spaceCount = 0;
				}
				if (pSpace.dead == false)
					pSpace.renderORight();
			}
			else {
				if (pP[spaceCount - 1].release == false)
				{
					Pcheck(pP, spaceCount - 1);
					pP[spaceCount - 1].release = false;
					spaceCount = 0;
				}
				if (pSpace.dead == false)
					pSpace.renderMiddle();
			}
			checkHit(e, pP);
			for (int i = 0; i < 9; i++)
				e[i].renderHitSparks();
			bos.renderHitSparks();
			if (gif.active == 1)
			{
				gif.intializeGift(e);
				if (checkGiftGrabbed(pSpace, gif,misle) == 1)
					gif.lost = true;
				gif.renderGift();
			}
			if (misle.active == true)
				rendermisle(misle,e,bos);
			else if (renderlol==false)
				renderBossExplosion(renderlol, currentx - 869 / 8, currenty - 869 / 8, true);
			if (spaceCount > 0)
			{
				for (int i = 0; i <= spaceCount - 1; i++)
					if (pSpace.dead==false)
					pP[i].renderpProjectile(false);
			}
			z = check1(eP);
			if (z == 1)
			{
				for (int i = 0; i < 9; i++)
					eP[i].i = rand() % 3;
				for (int i = 0; i < 9; i++)
					check(eP, e, i);
			}
			for (int i = 0; i < 9; i++)
			{
				eP[i].rendereProjectile();
			}
			updateLocation(e);
			for (int i = 0; i < 9; i++)
			{
				if (e[i].dead == false)
					e[i].renderEnemy();
			}
			if (e[0].y >= G getWindowHeight())
				enemiesLocatiion(e, 9);
			if (cheat[0] == false)
			{
				if (CheckPlayerHit(eP, pSpace, 9) == 1 || renderP == false)
				{
					renderP = false;
					pSpace.dead = true;
					renderBossExplosion(renderP, pSpace.x - (869 / 8 - 85 * makeThingsBigger / 2), pSpace.y - (658 / 8 - 96 * makeThingsBigger / 2), true);
				}
				else if (CheckPlayerBossHit(bP, pSpace, 10) == 1 || renderP == false)
				{
					renderP = false;
					pSpace.dead = true;
					renderBossExplosion(renderP, pSpace.x - (869 / 8 - 85 * makeThingsBigger / 2), pSpace.y - (658 / 8 - 96 * makeThingsBigger / 2), true);
				}
				else if (CheckPlayerChickHit(e, pSpace, 9) == 1 || renderP == false)
				{
					renderP = false;
					pSpace.dead = true;
					renderBossExplosion(renderP, pSpace.x - (869 / 8 - 85 * makeThingsBigger / 2), pSpace.y - (658 / 8 - 96 * makeThingsBigger / 2), true);
				}
				else if (CheckPlayerBHit(bos, pSpace) == 1 || renderP == false)
				{
					renderP = false;
					pSpace.dead = true;
					renderBossExplosion(renderP, pSpace.x - (869 / 8 - 85 * makeThingsBigger / 2), pSpace.y - (658 / 8 - 96 * makeThingsBigger / 2), true);
				}
				else if (renderP == true && pSpace.dead == true)
				{
					if (timeLimit == 50)
					{
						timeLimit = 0;
						if (pSpace.life != 0)
							pSpace.dead = false;
						renderP = true;
						spawn = true;
						pSpace.pActive = false;
					}
					else
						timeLimit++;
				}
			}
			if (cheat[0] == true)
			{
				if (GodCount <= 50)
				{
					G setDrawingColor(RGB(255, 255, 255));
					G setFontSizeAndBoldness(20, 10);
					G drawText(G getWindowWidth()/2, G getWindowHeight()/2, "GOD MODE ENABLED");
					GodCount++;
				}
			}
			if (cheat[1] == true)
			{
				pSpace.life++;
				cheat[1] = false;
			}
			if (cheat[2] == true)
			{
				misle.num++;
				cheat[2] = false;
			}
			if (spawn == true && renderP == true && pSpace.life != 0)
				renderspawn(pSpace, spawn);
			int x = G getWindowWidth() - 11 * makeThingsBigger * 2;
			int y = 0;
			for (int i = 1; i <= pSpace.life; i++)
			{
				RenderLife(x, y);
				x -= 13 * makeThingsBigger * 2;
			}
			x = G getWindowWidth() - 31 * makeThingsBigger;
			y = G getWindowHeight() - 49* makeThingsBigger;
			for (int i = 1; i <= misle.num; i++)
			{
				G drawImage(MLFrame, x, y, 0);
				x -= 31 * makeThingsBigger;
			}
			renderEHit(e);
			G setDrawingColor(RGB(255, 255, 255));
			G setFontSizeAndBoldness(30, 10);
			sprintf(str3, "YOUR HIGHEST PREVIOUS SCORE: %d", scr);
			G drawText(G getWindowWidth()/2-30/2, 0, str3);
			char str[20];
			sprintf(str, "Score: %d", score);
			G setDrawingColor(RGB(255, 255, 255));
			G setFontSizeAndBoldness(50, 30);
			G drawText(0, 0, str);
			if (pSpace.life == 0)
			{
				G setDrawingColor(RGB(255, 255, 255));
				G setFontSizeAndBoldness(100, 500);
				G drawText((G getWindowWidth() - 500) / 2, (G getWindowHeight() - 100) / 2, "GAME OVER!!!");
				if (score > scr)
				{
					InFile = fopen("save file\\sav.txt", "w");
					fprintf(InFile, "NickName= %s\n", pNew);
					fprintf(InFile, "HighestScore= %d\n", score);
					fclose(InFile);
				}
			}
		}
		G endDraw();
		waitForTime(frameRateLimit);
	}
		getch();
		return(0);
}