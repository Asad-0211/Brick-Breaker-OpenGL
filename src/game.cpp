/*
Muhammad Asad Akbar
23i-0120
2A
Department of Artificial Intelligence
*/

#ifndef CENTIPEDE_CPP_
#define CENTIPEDE_CPP_
#include "util.h"
#include <iostream>
#include<string>
#include<cmath> 
#include<fstream>
using namespace std;

void Timer(int );

class Coordinates
{
	protected:
	
	int color;
	float x;
	float y;
	
	public:
	
	float getXCoordinate()
	{
		return x;
	}
	
	float getYCoordinate()
	{
		return y;
	}
	
	int getColor()
	{
		return color;
	}
	
	void setXCoordinate(float cx)
	{
		x = cx;
	}
	
	void setYCoordinate(float cy)
	{
		y = cy;
	}
	
	void setColor(int c)
	{
		color = c;
	}
};

class Brick: public Coordinates
{
	int health;
	int color;
	int rows;
	int colomns;
	const int width;
	const int height;
	
	public:
	
	Brick(int r = 6, int col = 8, int bx = 572, int by = 430, int c = 1): width(67), height(30)
	{
		rows = r, colomns = col, x = bx, y = by, health = 1, color = c;
	}
	
	int getRows() const
	{
		return rows;
	}	
	
	int getColomns() const
	{
		return colomns;
	}	
	
	int getHeight() const
	{
		return height;
	}
	
	int getWidth() const
	{
		return width;
	}	
	
	int getHealth()
	{
		return health;
	}
	
	int getColor()
	{
		return color;
	}
	
	void setRows(int r)
	{
		rows = r;
	}
	
	void setColomns(int c)
	{
		colomns = c;
	}			 
	
	void setHealth(int h)
	{
		health = h;
		if(h == 4)
		{
			health = 3;
		}
		else if(h == 5)
		{
			health = 2;
		}	
	}
	
	void setColor(int c)
	{
		color = c;
		setHealth(c);
	}
	
	void drawBrick()
	{
		char ch = '0' + health;
		string str;
		str = str + ch;
		if(health > 0)
		{
			if(color == 1)
			{
				DrawRectangle(x, y, width, height, colors[LIGHT_GREEN]);
			}
			else if(color == 2)
			{
				DrawRectangle(x, y, width, height, colors[HOT_PINK]);
			}
			else if(color == 3)
			{
				DrawRectangle(x, y, width, height, colors[BLUE]);
			}
			else if(color == 4)
			{
				DrawRectangle(x, y, width, height, colors[CRIMSON]);
			}
			else if(color == 5)
			{
				DrawRectangle(x, y, width, height, colors[OLIVE]);
			}
			//DrawString( x + width / 2 - 4 , y + height / 2 - 8, str, colors[MISTY_ROSE]);
		}
	}	
};

class Ball: public Coordinates
{
	int radius;
	float speed;
	float angle;
	float slope;
	
	public:
	
	Ball(int bx = 595, int by = 420, int br = 10, float s = 7)
	{
		InitRandomizer();
		x = bx, y = by, radius = br, speed = s, angle = GetRandInRange(45, 136);
	}
	
	void setAngle(int theta)
	{
		angle = theta;
	}
	
	void setSpeed(float s)
	{
		speed = s;
	}
	
	float getAngle()
	{
		return angle;
	}
	
	float getSpeed()
	{
		return speed;
	}	
	
	int getRadius()
	{	
		return radius;
	}		
	
	void moveBall(bool f = 0)
	{
		x += (speed * (cos(Deg2Rad(angle))));
		y += (speed * (sin(Deg2Rad(angle))));
		if(y + radius >= 821 && f == 0)
		{
			if(cos(Deg2Rad(angle)) > 0.0)
			{
				int temp = 90 - angle;
				angle = 270 + temp;
			}
			else 
			{
				int temp = angle - 90;
				angle = 270 - temp;
			}	
		}		
		else if(x + radius >= 1001)
		{
			if(sin(Deg2Rad(angle)) > 0.0)
			{
				int temp = 90 - angle;
				angle = 90 + temp;
			}
			else 
			{
				int temp = 360 - angle;
				angle = 180 + temp;
			}
		}
		else if(x - radius <= 189)
		{
			if(sin(Deg2Rad(angle)) > 0.0)
			{
				int temp = 360 - angle;
				angle = 180 + temp;
			}
			else 
			{
				int temp = angle - 180;
				angle = 360 - temp;
			}	
		}
		while(angle >= 360)
		{
			angle -= 360;
		}	
		drawBall();	
	}
	
	void drawBall()
	{
		if(color == 0)
		{
			DrawCircle(x, y, radius, colors[WHITE]);
		}
		else if(color == 1)
		{
			DrawCircle(x, y, radius, colors[LIGHT_GREEN]);
		}
		else if(color == 2)
		{
			DrawCircle(x, y, radius, colors[HOT_PINK]);
		}
		else if(color == 3)
		{
			DrawCircle(x, y, radius, colors[BLUE]);
		}
		else if(color == 4)
		{
			DrawCircle(x, y, radius, colors[CRIMSON]);
		}
		else if(color == 5)
		{
			DrawCircle(x, y, radius, colors[OLIVE]);	
		}
		else 
		{
			DrawCircle(x, y, radius, colors[WHITE]);
		}	
		//DrawLine(0, 420, 1020, 420, 1, colors[MISTY_ROSE]);
		//DrawLine(595, 0, 595, 840, 2, colors[MISTY_ROSE]);
	}
};

class Paddle: public Coordinates
{
	int r;
	int mx;
	int w;
	int max;
	int numOfBalls;
	const int h;
	bool** removedBrick;
	Brick** bricks;
	Ball* ball;
	
	public:

	Paddle(int m = 5, int px = 385, int py = 70): r(12), w(100), h(30)
	{
		x = px, y = py, mx = px, max = m;
		ball = new Ball;
		numOfBalls = 1;
	}			
	
	Brick getBrick(int i, int j)
	{
		return bricks[i][j];
	}
	
	Ball* getBall()
	{
		return ball;
	}	
	
	int getWidth() const
	{
		return w;
	}
	
	int getNumOfBalls()
	{
		return numOfBalls;
	}	
	
	int getHeight() const
	{
		return h;
	}		
	
	int getMouse()
	{
		return mx;
	}
	
	void setWidth(int width)
	{
		if(width > 25 && width < 700)
		{
			w = width;
		}
	}	 
	
	void setMouse(int pmx)
	{
		mx = pmx;
	}
	
	void setMax(int m)
	{
		max = m;
	}
	
	void setBalls(Ball* b, int s)
	{
		if(ball != nullptr)
		{
			delete [] ball;
		}
		ball = b;
		numOfBalls = s;
	}	
	
	void setNumOfBalls(int s)
	{
		numOfBalls = s;
	}
	
	bool** getRemovedBricks()
	{
		return removedBrick;
	}
	
	void collideBrick(int lev = 1)
	{
		for(int n = 0; n < numOfBalls; n++)
		{
			bool f = 0;
			int bx = ball[n].getXCoordinate(), by = ball[n].getYCoordinate(), br = ball[n].getRadius();
			float angle = ball[n].getAngle();
			int height = bricks[0][0].getHeight(), width = bricks[0][0].getWidth(), r = bricks[0][0].getRows(), c = bricks[0][0].getColomns();
			for(int i = 0; i < r; i++)
			{
				if(lev == 3)
				{
					c = bricks[i][0].getColomns();
				}
				for(int j = 0; j < c; j++)
				{
					f = 0;
					if(removedBrick[i][j] == 0)
					{
						if((bx >= bricks[i][j].getXCoordinate() && bx <= bricks[i][j].getXCoordinate() + width) && (by + br >= bricks[i][j].getYCoordinate() && (by + br <= bricks[i][j].getYCoordinate() + height)))
						{
							f = 1;
							if(angle > 0 && angle < 90)
							{
								ball[n].setAngle(360 - angle);
							}
							else if(angle < 180) 
							{
								ball[n].setAngle(270 - (angle - 90));
							}
							else if(angle == 90)
							{
								ball[n].setAngle(260);
							}
						}
						else if((bx >= bricks[i][j].getXCoordinate() && bx <= bricks[i][j].getXCoordinate() + width) && (by - br <= bricks[i][j].getYCoordinate() + height && (by - br >= bricks[i][j].getYCoordinate())))
						{
							f = 1;
							if(angle > 180 && angle < 270)
							{
								ball[n].setAngle(90 + (270 - angle));
							}
							else if(angle > 270 && angle < 360) 
							{
								ball[n].setAngle(360 - angle);
							}
							else if(angle == 270)
							{
								ball[n].setAngle(80);
							}
						}
						else if((by >= bricks[i][j].getYCoordinate() && by <= bricks[i][j].getYCoordinate() + height) && (bx + br >= bricks[i][j].getXCoordinate() && (bx + br <= bricks[i][j].getXCoordinate() + width)))
						{
							f = 1;
							if(angle > 0 && angle < 90)
							{
								ball[n].setAngle(180 - angle);
							}
							else if(angle > 270 && angle < 360) 
							{
								ball[n].setAngle(180 + (360 - angle));
							}
							else if(angle == 0 || angle == 360)
							{
								ball[n].setAngle(188);
							}
						}
						else if((by >= bricks[i][j].getYCoordinate() && by <= bricks[i][j].getYCoordinate() + height) && (bx - br <= bricks[i][j].getXCoordinate() + width && (bx - br >= bricks[i][j].getXCoordinate())))	
						{
							f = 1;
							if(angle > 90 && angle < 180)
							{
								ball[n].setAngle(180 - angle);
							}
							else if(angle > 180 && angle < 270) 
							{
								ball[n].setAngle(270 + (270 - angle));
							}
							else if(angle == 180)
							{
								ball[n].setAngle(8);
							}
						}
						if(f == 1)
						{
							ball[n].setColor(bricks[i][j].getColor());
							bricks[i][j].setHealth(bricks[i][j].getHealth() - 1);
							if(bricks[i][j].getHealth() <= 0)
							{
								removedBrick[i][j] = 1;
							}	
						}
					}	
				}
				
			}
		}
	}
	
	void collidePaddleTwo(Paddle& upper)
	{
		int x = upper.getXCoordinate(), y = upper.getYCoordinate(), w = upper.getWidth();
		for(int n = 0; n < numOfBalls; n++)
		{	
			int bx = ball[n].getXCoordinate(), by = ball[n].getYCoordinate(), br = ball[n].getRadius();
			if(by + r >= y && y + (h / 2) >= by - r)
			{
				if(bx + br >= x && bx - br <= x + w)
				{
					upper.setColor(ball[n].getColor());
					float angle = ball[n].getAngle();
					float incidentAngle = angle;
					if(angle > 180 || angle < 0)
					{
						incidentAngle = angle - 180;
					}
					int p = 0;
					int add = 5;
					float tem = 0;
					float fact = 2.5;
					int partOne = w/20, partTwo = ((w - (partOne * add)) / add), mid = (((w / add) / 2) + 1);
					for(int i = x, k = 0; i <= x + w; i += 5, k++, fact += 1.0)
					{
						if(k < partOne)
						{
							p = 1;
							if(bx + br >= i && bx <= i + add)
							{
								if(incidentAngle >= 90)
								{
									angle = 180 - (add * fact);
								}
								else 
								{
									if(incidentAngle > 60)
									{
										angle = 135 - fact;
									}
									else if(incidentAngle > 40)
									{
										angle = 130 + fact;
									}
									else
									{
										angle = 120 + fact;
									}
								}
								break;
							}
							tem = fact;
						}
						else if(k < partTwo + 1)
						{
							p = 2;
							if(k == partOne)
							{
								fact = 1.5;
							}
							if(k >= mid)
							{
								fact -= 2.0;	
							}	
							if(bx >= i && bx <= i + add)
							{
								if(k == mid - 1 || k == mid || k == mid + 1)
								{
									if(incidentAngle >= 90)
									{
										angle = 85;
									}
									else 
									{
										angle = 95;
									}	
								}
								else 
								{
									if(incidentAngle >= 90)
									{
										angle = 45 + (4*fact);		
									}
									else 
									{
										angle = 135 - (4*fact);
									}
								}
								break;
							}	
							
						}
						else 
						{
							p = 3;
							if(k == partTwo + 1)
							{
								fact = tem;
							}
							if(k > partTwo + 1)
							{
								fact -= 2.0;
							}
							if(bx >= i && bx - br <= i + add)
							{
								if(incidentAngle <= 90)
								{
									angle = 45 - (add * fact);
								}
								else 
								{
									if(incidentAngle < 120)
									{
										angle = 45 + fact;
									}
									else if(incidentAngle < 140)
									{
										angle = 50 - fact;
									}
									else
									{
										angle = 60 - fact;
									}
								}
								break;
							}		
						}				
					}
					if(p == 1)
					{
						ball[n].setAngle(90 + angle);
					}
					else if(p == 2)// || p == 3)
					{
						ball[n].setAngle(180 + angle);
					}	
					else if(p == 3)
					{
						ball[n].setAngle(270 + angle);
					}
				}
			}
		}	
	}
	
	void collidePaddle(bool f = 0)
	{
		for(int n = 0; n < numOfBalls; n++)
		{
			int bx = ball[n].getXCoordinate(), by = ball[n].getYCoordinate(), br = ball[n].getRadius();
			if(y + h >= by - r && y + (h / 2) <= by - r)
			{
				if(bx + br >= x && bx - br <= x + w)
				{
					setColor(ball[n].getColor());
					float angle = ball[n].getAngle();
					float incidentAngle = angle - 180;
					if(angle < 180)
					{
						incidentAngle = 180 - angle;
					}
					int add = 5;
					float tem = 0;
					float fact = 2.5;
					int partOne = w/20, partTwo = ((w - (partOne * add)) / add), mid = (((w / add) / 2) + 1);
					for(int i = x, k = 0; i <= x + w; i += 5, k++, fact += 1.0)
					{
						if(k < partOne)
						{
							if(bx + br >= i && bx <= i + add)
							{
								if(incidentAngle >= 90)
								{
									angle = 180 - (add * fact);
								}
								else 
								{
									if(incidentAngle > 60)
									{
										angle = 135 - fact;
									}
									else if(incidentAngle > 40)
									{
										angle = 130 + fact;
									}
									else
									{
										angle = 120 + fact;
									}
								}
								break;
							}
							tem = fact;
						}
						else if(k < partTwo + 1)
						{
							if(k == partOne)
							{
								fact = 1.5;
							}
							if(k >= mid)
							{
								fact -= 2.0;	
							}	
							if(bx >= i && bx <= i + add)
							{
								if(k == mid - 1 || k == mid || k == mid + 1)
								{
									if(incidentAngle >= 90)
									{
										angle = 85;
									}
									else 
									{
										angle = 95;
									}	
								}
								else 
								{
									if(incidentAngle >= 90)
									{
										angle = 45 + (4*fact);		
									}
									else 
									{
										angle = 135 - (4*fact);
									}
								}
								break;
							}	
							
						}
						else 
						{
							if(k == partTwo + 1)
							{
								fact = tem;
							}
							if(k > partTwo + 1)
							{
								fact -= 2.0;
							}
							if(bx >= i && bx - br <= i + add)
							{
								if(incidentAngle <= 90)
								{
									angle = 45 - (add * fact);
								}
								else 
								{
									if(incidentAngle < 120)
									{
										angle = 45 + fact;
									}
									else if(incidentAngle < 140)
									{
										angle = 50 - fact;
									}
									else
									{
										angle = 60 - fact;
									}
								}
								break;
							}		
						}				
					}
					ball[n].setAngle(angle);
				}
			}
		}	
	}
	
	void LoadLevelThree()
	{
		int k = 1;
		Brick temp(10, 9);
		int r = temp.getRows(), c = temp.getColomns(), w = temp.getWidth(), h = temp.getHeight();
		int y = 580 - h;
		int sc = 270;
		int dc = 5;
		int dy = 3;
		int x = sc;
		bricks = new Brick*[r];
		removedBrick = new bool*[r];
		InitRandomizer();
		Rows(0, r, c, 0, x, y, w, h, bricks, removedBrick);
	}
	
	void Rows(int i, int row, int col, int r, int x, int y, int w, int h, Brick** B, bool** RB)
	{
		if(r == row)
		{
			return;
		}
		else 
		{
			if(i == 0 || r == row - 1)
			{
				B[r] = new Brick[col];
				RB[r] = new bool[col];
				Colomns(i, row, r, col, 0, 270, y, w, B, RB);
			}
			else 
			{
				B[r] = new Brick[col - ((2 * i) - 1)];
				RB[r] = new bool[col - ((2 * i) - 1)];
				Colomns(i, row, r, col - ((2 * i) - 1), 0, 270, y, w, B, RB);
			}
			if(r == (row - 1) / 2)
			{
				Rows(i, row, col, r + 1, 270, y - (h + 3), w, h, B, RB);
			}
			else if(r > (row - 1) / 2)
			{
				Rows(i - 1, row, col, r + 1, 270, y - (h + 3), w, h, B, RB);
			}
			else 
			{
				Rows(i + 1, row, col, r + 1, 270, y - (h + 3), w, h, B, RB);
			}
		}	
	}
	
	void Colomns(int i, int row, int r, int col, int c, int x, int y, int w, Brick** B, bool** RB)
	{
		if(c == col)
		{
			return;
		}
		else 
		{
			if(i != 0)
			{
				if(c == (col / 2))
				x = x + (((2 * i) - 1) * (w + 5));
			}
			int color = GetRandInRange(1, 6);
			RB[r][c] = 0;
			B[r][c].setXCoordinate(x);
			B[r][c].setYCoordinate(y);
			B[r][c].setRows(row);
			B[r][c].setColomns(col);
			B[r][c].setColor(color);
			Colomns(i, row, r, col, c + 1, x + (w + 5), y, w, B, RB);
		}
	}
	
	void LoadLevelTwo()
	{
		Brick temp(15, 3);
		int r = temp.getRows(), c = temp.getColomns(), w = temp.getWidth(), h = temp.getHeight();
		int y = 780 - h;
		int sc = 270;
		int dc = 5;
		int dy = 3;
		int x = sc;
		int k = 1;
		bricks = new Brick*[r];
		removedBrick = new bool*[r];
		InitRandomizer();
		for(int i = 0; i < r; i++)
		{
			bricks[i] = new Brick[c];
			removedBrick[i] = new bool[c];
			for(int j = 0; j < c; j++)
			{
				int col = GetRandInRange(1, 6);
				removedBrick[i][j] = 0;
				bricks[i][j].setXCoordinate(x);
				bricks[i][j].setYCoordinate(y);
				bricks[i][j].setRows(r);
				bricks[i][j].setColomns(c);
				bricks[i][j].setColor(col);
				x += (w + dc);
			}
			if((i + 1) % 3 == 0)
			{
				k++;
			}
			if(k == 2 || k == 4)
			{	 
				x = ((w + dc) * c) + sc;
			}
			else if(k == 3)
			{
				x = (2 * ((w + dc) * c)) + sc;
			}
			else if(k == 1 || k == 5)
			{
				x = sc;
			}		
			y -= (h + dy);
		}
	}
	
	void LoadLevelOne()
	{
		Brick temp(6, 8);
		int r = temp.getRows(), c = temp.getColomns(), w = temp.getWidth(), h = temp.getHeight();
		int dc = 5;
		int dy = 3;
		float screen = (1020 + dc) / 2.0;
		float sc = (screen - (c / 2.0 * (w + dc)) + 85.0);
		int y = 780 - h;
		int x = sc;
		bricks = new Brick*[r];
		removedBrick = new bool*[r];
		InitRandomizer();
		for(int i = 0; i < r; i++)
		{
			bricks[i] = new Brick[c];
			removedBrick[i] = new bool[c];
			for(int j = 0; j < c; j++)
			{
				int col = GetRandInRange(1, 5);
				removedBrick[i][j] = 0;
				bricks[i][j].setXCoordinate(x);
				bricks[i][j].setYCoordinate(y);
				bricks[i][j].setColor(col);
				x += (w + dc);
			}
			x = sc;
			y -= (h + dy);
		}
	}	
	
	void setPaddle(int m = 5)
	{
		max = m;
		ball = new Ball;
		numOfBalls = 1;
	}
	
	void drawPaddle()
	{
		if(color == 0)
		{
			DrawRoundRect(x, y, w, h, colors[WHITE], r);
		}
		else if(color == 1)
		{
			DrawRoundRect(x, y, w, h, colors[LIGHT_GREEN], r);
		}
		else if(color == 2)
		{
			DrawRoundRect(x, y, w, h, colors[HOT_PINK], r);
		}
		else if(color == 3)
		{
			DrawRoundRect(x, y, w, h, colors[BLUE], r);
		}
		else if(color == 4)
		{
			DrawRoundRect(x, y, w, h, colors[CRIMSON], r);
		}
		else if(color == 5)
		{
			DrawRoundRect(x, y, w, h, colors[OLIVE], r);
		}
		else 
		{
			DrawRoundRect(x, y, w, h, colors[WHITE], r);
		}
		DrawLine(x + w / 4.0, y, x + w / 4.0, y + h, 2, colors[WHITE]);
		DrawLine(x + w / 4.0 * 3.0, y, x + w / 4.0 * 3.0, y + h, 2, colors[WHITE]);
	}
	
	void drawWalls(int lev = 1)
	{
		if(lev != 3)
		{
			DrawRectangle(0, 821, 1020, 19, colors[GRAY]);
		}	
		DrawRectangle(170, 0, 19, 840, colors[GRAY]);
		DrawRectangle(0, 0, 19, 840, colors[GRAY]);
		DrawRectangle(1001, 0, 19, 840, colors[GRAY]);
	}
	
	void deletePaddle()
	{
		Brick temp;
		int rows = temp.getRows();
		delete [] ball;
		for(int i = 0; i < rows; i++)
		{
			delete [] bricks[i];
			delete [] removedBrick[i];
		}
		delete [] bricks;
		delete [] removedBrick;
	}
	
	~Paddle()
	{
		deletePaddle();
	}
};

class Powers: public Coordinates
{
	const int width;
	const int height;
	const float radius;
	float speed;
	bool status;
	
	public:
	
	Powers(float s = 2.5): width(30), height(27), radius(14.0)
	{
		speed = s, status = 0;
	}
	
	int getWidth()
	{
		return width;
	}
	
	int getHeight()
	{
		return height;	
	}	
	
	float getRadius()
	{
		return radius;
	}
	
	bool getStatus()
	{
		return status;
	}		
	
	void setStatus(bool s)
	{
		status = s;
	}
	
	void activatePowers(int sx, int sy, int c)
	{
		x = sx - width / 2, y = sy;
		color = c;
		status = 1;
	}
	
	void movePower()
	{
		if(status == 1)
		{
			if(color == 1)
			{
				GreenPowerUp();
			}
			else if(color == 2)
			{
				PinkPowerDown();	
			}
			else if(color == 3)
			{
				BluePowerUp();	
			}
			else if(color == 4)
			{
				RedPowerDown();	
			}
			else if(color == 5)
			{
				YellowPowerUp();	
			}	
		}	
	}
	
	void GreenPowerUp()
	{
		DrawTriangle(x, y, x + width, y, x + width / 2, y + height, colors[LIGHT_GREEN]);
		y -= speed;
		if(y < -height)
		{
			status = 0;
		}	
	}
	
	void PinkPowerDown()
	{
		DrawSquare(x, y, width, colors[DEEP_PINK]);
		y -= speed;
		if(y < -width)
		{
			status = 0;
		}	
	}	
	
	void BluePowerUp()
	{
		DrawCircle(x, y, radius, colors[DARK_CYAN]);
		y -= speed;
		if(y < -width)
		{
			status = 0;
		}
	} 
	
	void RedPowerDown()
	{
		DrawRectangle(x, y, width * 2, width, colors[FIREBRICK]);
		y -= speed;
		if(y < -width)
		{
			status = 0;
		}
	}
	
	void YellowPowerUp()
	{
		DrawSquare(x, y, width, colors[OLIVE]);
		y -= speed;
		if(y < -width)
		{
			status = 0;
		}
	}
};

class Interface
{
	protected:	
	
	Paddle* paddle;
	Powers** powers;
	int lives;
	int score;
	int rows;
	int colomns;
	bool paddleTwo;
	bool** activation;
	bool** applied;
	
	public:
	
	Interface(int r = 6, int c = 8) 
	{
		rows = r, colomns = c;
		lives = 2;
		score = 0;
		paddleTwo = 0;
		paddle = new Paddle;
		powers = new Powers*[rows];
		applied = new bool*[rows];
		activation = new bool*[rows];
		for(int i = 0; i < rows; i++)
		{
			powers[i] = new Powers[colomns];
			applied[i] = new bool[colomns];
			activation[i] = new bool[colomns];
			for(int j = 0; j < colomns; j++)
			{
				activation[i][j] = 0;
				applied[i][j] = 0;
			}	
		}
	}
	
	void allocateInterface(bool f = 0)
	{
		powers = new Powers*[rows];
		applied = new bool*[rows];
		activation = new bool*[rows];
		for(int i = 0; i < rows; i++)
		{
			powers[i] = new Powers[colomns];
			applied[i] = new bool[colomns];
			activation[i] = new bool[colomns];
			for(int j = 0; j < colomns; j++)
			{
				activation[i][j] = 0;
				applied[i][j] = 0;
			}	
		}
	}
	
	int getRows()
	{
		return rows;
	}
	
	bool getPaddleTwo()
	{
		return paddleTwo;
	}	
	
	int getColomns()
	{
		return colomns;
	}	
	
	void setRows(int r)
	{
		rows = r;
	}	
	
	void setColomns(int c)
	{
		colomns = c;
	}	
	
	void checkPowers(int lev = 1)
	{
		bool** brokenBricks = paddle->getRemovedBricks();
		Brick temp;
		int w = temp.getWidth();
		int h = temp.getHeight();
		for(int i = 0; i < rows; i++)
		{
			if(lev == 3)
			{
				colomns = paddle->getBrick(i, 0).getColomns();
			}
			for(int j = 0; j < colomns; j++)
			{
				if(brokenBricks[i][j] == 1 && activation[i][j] == 0)
				{
					if(paddle->getBrick(i, j).getColor() == 3)
					{
						powers[i][j].activatePowers(paddle->getBrick(i, j).getXCoordinate() + w / 2, paddle->getBrick(i, j).getYCoordinate() + h / 2, paddle->getBrick(i, j).getColor());
					}
					else if(paddle->getBrick(i, j).getColor() == 4)
					{
						powers[i][j].activatePowers(paddle->getBrick(i, j).getXCoordinate() + w / 4, paddle->getBrick(i, j).getYCoordinate(), paddle->getBrick(i, j).getColor());
					}
					else 
					{
						powers[i][j].activatePowers(paddle->getBrick(i, j).getXCoordinate() + w / 2, paddle->getBrick(i, j).getYCoordinate(), paddle->getBrick(i, j).getColor());
					}
					score += (10 * paddle->getBrick(i, j).getColor());
					activation[i][j] = 1;
				}
				powers[i][j].movePower();
			}
		}
	}
	
	void displayScore(int x = 25, int y = 600, bool n = 0)
	{
		string str;
		string live;
		char s = '0' + lives;
		live = s + live;
		if(score == 0)
		{
			str = "0";
		}
		else 
		{
			int temp = score;
			while(temp > 0)
			{
				char ch = '0' + (temp % 10);
				str = ch + str;
				temp /= 10;
			}
		}
		if(n == 0)
		{
			DrawString(x, y + 150, "23i-0120", colors[MISTY_ROSE]);
			DrawString(x, y + 100 , "LIVES: " + live, colors[MISTY_ROSE]);
			DrawString(x, y + 50, "SCORE: " + str, colors[MISTY_ROSE]);
			DrawRectangle(2, 600, 170, 19, colors[GRAY]);
		}
		else
		{
			DrawString(x, y, "SCORE: " + str, colors[MISTY_ROSE]);
		}	
	}
	
	void collision(int lev = 1)
	{
		int x = paddle->getXCoordinate(), y = paddle->getYCoordinate(), w = paddle->getWidth(), h = paddle->getHeight();
		bool f = 0;
		for(int i = 0; i < rows; i++)
		{
			if(lev == 3)
			{
				colomns = paddle->getBrick(i, 0).getColomns();
			}
			for(int j = 0; j < colomns; j++)
			{
				if(activation[i][j] == 1 && applied[i][j] == 0)
				{
					int px = powers[i][j].getXCoordinate(), py = powers[i][j].getYCoordinate(), pw = powers[i][j].getWidth(), ph = powers[i][j].getHeight(), c = powers[i][j].getColor();
					float pr = powers[i][j].getRadius();
					f = 0;
					if(c == 1)
					{
						if(py <= y + h && py + ph >= y)
						{
							if((px >= x && px <= x + w) || (px + pw >= x && px + pw <= x + w))
							{
								f = 1;
								paddle->setWidth(2 * w);
								if(lev == 3)
								{
									paddle[1].setWidth(2 * w);
								}		
							}
						}	
					}
					else if(c == 2)
					{
						if(py <= y + h && py + pw >= y)
						{
							if((px >= x && px <= x + w) || (px + pw >= x && px + pw <= x + w))
							{
								f = 1;
								paddle->setWidth(w / 2);
								if(lev == 3)
								{
									paddle[1].setWidth(w / 2);
								}		
							}
						}
					}
					else if(c == 3)
					{
						if(py - pr <= y + h && py + pr >= y)
						{
							if(px + pr >= x && px - pr <= x + w)
							{
								f = 1;
								Timer(1);	
							}
						}
					}
					else if(c == 4)
					{
						if(py <= y + h && py + pw >= y)
						{
							if((px >= x && px <= x + w) || (px + 2 * pw >= x && px + 2 * pw <= x + w))
							{
								f = 1;
								Timer(2);		
							}
						}
					}
					else if(c == 5)
					{
						if(py <= y + h && py + pw >= y)
						{
							if((px >= x && px <= x + w) || (px + pw >= x && px + pw <= x + w))
							{
								f = 1;
								Timer(3);	
							}
						}
					}
					if(f == 1)
					{
						applied[i][j] = 1;
						powers[i][j].setStatus(0);
					}
				}
			}
		}
	}		
	
	Paddle* getPaddle()
	{
		return paddle;
	}
	
	void deleteInterface(bool f = 0)
	{
		if(f == 1)
		{
			paddle = new Paddle[2];
			paddle[1].setYCoordinate(740);
		}
		paddleTwo = f;
		for(int i = 0; i < rows; i++)
		{
			delete [] applied[i];
			delete [] activation[i];
			delete [] powers[i];
		}
		delete [] applied;
		delete [] activation;
		delete [] powers;
	}
	
	void Destroy()
	{
		for(int i = 0; i < rows; i++)
		{
			delete [] applied[i];
			delete [] activation[i];
			delete [] powers[i];
		}
		delete [] applied;
		delete [] activation;
		delete [] powers;
	}
	
	~Interface()
	{
		deleteInterface();
		delete paddle;
	}	
};

class Game: public Interface
{
	int level;
	int menuIterate;
	int pauseIterate;
	int highScore;
	bool history;
	bool hScore;
	bool startGame;
	bool started;
	bool Win;
	bool Loose;
	bool pause;
	
	public:
	
	Game()
	{
		Win = 0, Loose = 0, pause = 0, startGame = 0, started = 0, history = 0, hScore = 0;
		level = 1, pauseIterate = 0, menuIterate = 0, highScore = 0;
		ifstream out;
		out.open("High_Score.txt");
		string str;
		getline(out, str);
		for(int i = 0; str[i] != '\0'; i++)
		{
			highScore += str[i] - '0';
			if(str[i + 1] != '\0')
			{
				highScore *= 10;
			}	
		}	
	}
	
	bool getWin()
	{
		return Win;
	}
	
	bool getHighScore()
	{
		return hScore;	
	}
	
	bool getLoose()
	{
		return Loose;
	}		
	
	bool getHistory()
	{
		return history;
	}
	
	bool getPause()
	{
		return pause;
	}
	
	bool getStarted()
	{
		return started;
	}		
	
	bool getStartGame()
	{
		return startGame;
	}
	
	int getPauseIterate()
	{
		return pauseIterate;
	}
	
	int getMenuIterate()
	{
		return menuIterate;
	}
	
	int getLevel()
	{
		return level;
	}	
	
	void setPause(bool p)
	{
		pause = p;
	}
	
	void setStarted(bool s)
	{
		started = s;
	}	
	
	void setWin(int w)
	{
		Win = w;
	}
	
	void setHighScore(bool f = 0)
	{
		hScore = f;
	}
	
	void setLoose(int l)
	{
		Loose = l; 
	}		
	
	void setPauseIterate(int p)
	{
		if(p < 0)
		{
			pauseIterate = 1;
		}
		else if(p > 1)
		{
			pauseIterate = 0;
		}	
		else 
		{
			pauseIterate = p;
		}
	}	
	
	void setStartGame(bool sg)
	{
		startGame = sg;
	}
	
	void setLevel(int l)
	{
		if(l < 1)
		{
			level = 3;
		}
		else if(l > 3)
		{
			level = 1;
		}	
		else 
		{
			level = l;
		}
	}		
	
	void setMenuIterate(int mi)
	{
		if(mi < 0)
		{
			menuIterate = 4;
		}
		else if(mi > 4)
		{
			menuIterate = 0;
		}	
		else 
		{
			menuIterate = mi;	
		}			
	}	
	
	bool gameOver()
	{
		bool loose = 1, win = 1, mainBall = 0;
		int n = paddle->getNumOfBalls();
		bool** ptr = paddle->getRemovedBricks();
		for(int i = 0; i < n; i++)
		{
			if(paddleTwo == 1)
			{
				if(paddle->getBall()[i].getYCoordinate() > 0 && paddle->getBall()[i].getYCoordinate() < 840)
				{
					loose = 0;
					break;
				}
			}
			else if(paddle->getBall()[i].getYCoordinate() > 0)
			{
				loose = 0;
				break;
				
			}
			else if(i == 0) 
			{	
				mainBall = 1;
			}
		}
		for(int i = 0; i < rows; i++)
		{
			if(level == 3)
			{
				colomns = paddle->getBrick(i, 0).getColomns();
			}
			for(int j = 0; j < colomns; j++)
			{
				if(ptr[i][j] == 0)
				{
					win = 0;
				}
			}
		}
		if(mainBall == 1)
		{
			for(int i = 0; i < n; i++)
			{
				if(paddleTwo == 1)
				{
					if(paddle->getBall()[i].getYCoordinate() > 0 && paddle->getBall()[i].getYCoordinate() < 840)
					{
						paddle->getBall()[0] = paddle->getBall()[i];
					}
				}
				else if(paddle->getBall()[i].getYCoordinate() > 0)
				{
					paddle->getBall()[0] = paddle->getBall()[i];
				}
			}	
		}
		if(win == 1)
		{
			displayWin();
			Win = win;
		}
		else if(loose == 1)
		{
			lives--;
			if(lives > 0)
			{
				Timer(5);
			}
			else 
			{
				displayLost();
				Loose = loose;
			}
		}
		return (loose || win);	
	}	
	
	void pauseMenu()
	{
		DrawRectangle(0, 0, 1020, 840, colors[BLACK]);
		if(pauseIterate == 0)
		{
			DrawRoundRect(250 + 175, 409, 170, 40, colors[DARK_BLUE], 5.0);
		}
		else if(pauseIterate == 1)
		{
			DrawRoundRect(425, 359, 170, 40, colors[DARK_BLUE], 5.0);
		}
		DrawString(288 + 175 , 420, "RESUME", colors[WHITE]);
		DrawString(250 + 190, 370, "MAIN MENU", colors[WHITE]);
	}
	
	void menu()
	{
		DrawRectangle(0, 0, 1020, 840, colors[BLACK]);
		if(menuIterate == 0)
		{
			DrawRoundRect(250 + 175, 459, 170, 40, colors[DARK_BLUE], 5.0);
		}
		else if(menuIterate == 1)
		{
			DrawRoundRect(425, 409, 170, 40, colors[DARK_BLUE], 5.0);
			DrawTriangle(405, 448, 405, 410, 375, 429, colors[DARK_BLUE]);
			DrawTriangle(615, 448, 615, 410, 645, 429, colors[DARK_BLUE]);
		}
		else if(menuIterate == 2)
		{
			DrawRoundRect(240 + 175, 359, 207, 40, colors[DARK_BLUE], 5.0);		
		}
		else if(menuIterate == 3)
		{
			DrawRoundRect(242 + 175, 309, 202, 40, colors[DARK_BLUE], 5.0);
		}
		else if(menuIterate == 4)
		{
			DrawRoundRect(260 + 175, 259, 162, 40, colors[DARK_BLUE], 5.0);	
		}
		DrawString(258 + 175 , 470, "START GAME", colors[WHITE]);
		string lev;
		if(level == 1)
		{
			lev = "LEVEL 1";
		}
		else if(level == 2)
		{
			lev = "LEVEL 2";
		}
		else if(level == 3)
		{
			lev = "LEVEL 3";		
		}
		if(menuIterate == 1)
		{
			DrawString(294 + 175, 420, lev, colors[WHITE]);
		}
		else
		{ 		
			DrawString(250 + 175, 420, "CHANGE LEVEL", colors[WHITE]);
		}
		DrawString(247 + 175, 370, "HIGHEST SCORE", colors[WHITE]);
		DrawString(250 + 175, 320, "GAME HISTORY", colors[WHITE]);
		DrawString(315 + 175, 270, "EXIT", colors[WHITE]);
	}
	
	void displayWin()
	{
		if(level == 3)
		{
			DrawRectangle(0, 821, 1020, 19, colors[GRAY]);
		}
		DrawRectangle(18, 0, 984, 822, colors[BLACK]);
		DrawString(450, 550, "YOU WON!", colors[LIGHT_GREEN]);
		displayScore(457, 500, 1);
		paddle->setNumOfBalls(0);
		if(pauseIterate == 0)
		{
			DrawRoundRect(250 + 175, 409, 170, 40, colors[DARK_BLUE], 5.0);
		}
		else if(pauseIterate == 1)
		{
			DrawRoundRect(425, 359, 170, 40, colors[DARK_BLUE], 5.0);
		}
		if(level != 3)
		{
			DrawString(278 + 160 , 420, "NEXT LEVEL", colors[WHITE]);
			DrawString(250 + 190, 370, "MAIN MENU", colors[WHITE]);
		}
		else
		{
			DrawString(280 + 160 , 420, "NEW GAME", colors[WHITE]);
			DrawString(250 + 190, 370, "MAIN MENU", colors[WHITE]);		
		}		
	}
	
	void displayLost()
	{
		lives = 0;
		if(level == 3)
		{
			DrawRectangle(0, 821, 1020, 19, colors[GRAY]);
		}
		DrawRectangle(18, 0, 984, 822, colors[BLACK]);
		DrawString(450, 550, "YOU LOST!", colors[RED]);
		displayScore(457, 500, 1);
		paddle->setNumOfBalls(0);
		if(pauseIterate == 0)
		{
			DrawRoundRect(250 + 175, 409, 170, 40, colors[DARK_BLUE], 5.0);
		}
		else if(pauseIterate == 1)
		{
			DrawRoundRect(425, 359, 170, 40, colors[DARK_BLUE], 5.0);
		}
		DrawString(282 + 175 , 420, "RESTART", colors[WHITE]);
		DrawString(250 + 190, 370, "MAIN MENU", colors[WHITE]);
	}
	
	void writeHighScore()
	{
		ofstream out;
		out.open("High_Score.txt");
		if(score > highScore)
		{
			highScore = score;
		}
		out << highScore;
		out.close();
	}
	
	void readHighScore()
	{
		ifstream out;
		string str;
		out.open("High_Score.txt");
		getline(out, str);
		out.close();
		if(str == "")
		{
			str = "0";
		}	
		DrawRectangle(0, 0, 1020, 840, colors[DARK_BLUE]);
		int sub = 40;
		DrawString(445 , 840 - sub , "Highest Score: " + str , colors[WHITE] );
		DrawRoundRect(480, 30, 150, 40, colors[SLATE_GRAY], 5 );
		DrawString(520, 40, "DONE", colors[WHITE] );
	}
	
	void writeHistory()
	{
		ofstream out;
		string str;
		if(score == 0)
		{
			str = "0";
		}
		else 
		{
			int temp = score;
			while(temp > 0)
			{
				char ch = '0' + (temp % 10);
				str = ch + str;
				temp /= 10;
			}
		}
		out.open("history.txt", ios :: app);
		out << str << endl;
		out.close();
	}
	
	void readHistory()
	{
		ifstream out;
		string str;
		DrawRectangle(0, 0, 1020, 840, colors[DARK_BLUE]);
		int sub = 40;
		out.open("history.txt");
		while(!(out.eof()))
		{
			getline(out, str);
			if(str == "")
			{
				break;
			}	       
			DrawString(450 , 840 - sub , "Your Score: " + str , colors[WHITE] );
			sub += 40;
			if(sub >= 820)
			{
				break;
			}
		}
		DrawRoundRect(480, 30, 150, 40, colors[SLATE_GRAY], 5 );
		DrawString(520, 40, "DONE", colors[WHITE] );
		out.close();
	}	
	
	void displayHistory(bool h = 1)
	{
		history = h;
	}
	
	void NextLevel(int lev)
	{
		if(lev == 3)
		{
			level = 1;
		}
		else
		{
			level = lev + 1;
		}	
		start();
	}
	
	void start()
	{
		setStartGame(1);
		setStarted(1);
		if(getLevel() == 1)
		{
			getPaddle()->LoadLevelOne();
		}
		else if(getLevel() == 2)
		{
			deleteInterface();
			getPaddle()->LoadLevelTwo();
			setRows(getPaddle()->getBrick(0, 0).getRows());
			setColomns(getPaddle()->getBrick(0, 0).getColomns());
			allocateInterface();
			getPaddle()->getBall()[0].setXCoordinate(800);
			getPaddle()->getBall()[0].setYCoordinate(400);
		}
		else if(getLevel() == 3)
		{
			deleteInterface(1);
			getPaddle()->LoadLevelThree();
			setRows(getPaddle()->getBrick(0, 0).getRows());
			setColomns(getPaddle()->getBrick(0, 0).getColomns());
			allocateInterface(1);
		}
	}	
	
	void RestartLevel(int lev)
	{
		level = lev;
		start();
	}	
	
	void ExitGame()
	{
		Destroy();
		cout << "GoodBye!" << endl;
		exit(0);	
	}	
	
	Game* Reset()
	{
		Game* temp = new Game;
		paddleTwo = 0;
		paddle->setColor(0);
		paddle->getBall()->setColor(0);
		return temp;
	}
};

Game* game = new Game;

void SetCanvasSize(int width, int height) 
{
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

void GameDisplay()
{
	glClearColor(0, 0, 0.0, 0 ); 
	glClear (GL_COLOR_BUFFER_BIT);
	if(game->getStartGame() == 0)
	{
		game->menu();
		if(game->getHistory() == 1)
		{
			game->readHistory();
		}
		else if(game->getHighScore() == 1)
		{
			game->readHighScore();
		}
	}
	else if(game->getPause() == 1)
	{
		game->pauseMenu();
	}	
	else if(game->getStartGame() == 1 && game->getPause() == 0)
	{
		game->getPaddle()->drawWalls(game->getLevel());
		if(game->getLevel() == 3)
		{
			game->getPaddle()->collidePaddleTwo(game->getPaddle()[1]);
		}
		game->getPaddle()->collidePaddle();
		game->getPaddle()->collideBrick(game->getLevel());
		game->displayScore();
		int n = game->getPaddle()->getNumOfBalls();
		for(int i = 0; i < n; i++)
		{
			if(game->getLevel() == 3)
			{
				game->getPaddle()->getBall()[i].moveBall(1);
			}
			else 
			{
				game->getPaddle()->getBall()[i].moveBall();
			}
		}
		game->checkPowers(game->getLevel());
		game->collision(game->getLevel());
		game->getPaddle()->drawPaddle();
		if(game->getLevel() == 3)
		{
			game->getPaddle()[1].drawPaddle();
		}		
		int r = game->getPaddle()->getBrick(0, 0).getRows();
		int c = game->getPaddle()->getBrick(0, 0).getColomns();
		for(int i = 0; i < r; i++)
		{
			if(game->getLevel() == 3)
			{
				c = game->getPaddle()->getBrick(i, 0).getColomns();
			}
			for(int j = 0; j < c; j++)
			{
				game->getPaddle()->getBrick(i, j).drawBrick();
			}
		}
		game->gameOver();
	}	
	glutPostRedisplay();		
	glutSwapBuffers(); 	
}

void NonPrintableKeys(int key, int x, int y)
{
	if(game->getStartGame() == 0)
	{
		if (key == GLUT_KEY_LEFT) 
		{	
			if(game->getMenuIterate() == 1)
			{
				game->setLevel(game->getLevel() - 1);
			}
		} 
		else if (key == GLUT_KEY_RIGHT) 
		{
			if(game->getMenuIterate() == 1)
			{
				game->setLevel(game->getLevel() + 1);
			}
		} 
		else if (key == GLUT_KEY_UP)
		{
			if(game->getHistory() == 0 && game->getHighScore() == 0)
			{
				game->setMenuIterate(game->getMenuIterate() - 1);
			}	
		}
		else if (key == GLUT_KEY_DOWN)
		{
			if(game->getHistory() == 0 && game->getHighScore() == 0)
			{
				game->setMenuIterate(game->getMenuIterate() + 1);
			}
		}
	}
	else if(game->getPause() == 1 || game->getWin() == 1 || game->getLoose() == 1)
	{
		if (key == GLUT_KEY_UP)
		{
			game->setPauseIterate(game->getPauseIterate() - 1);
		}
		else if (key == GLUT_KEY_DOWN)
		{
			game->setPauseIterate(game->getPauseIterate() + 1);
		}
	}
	else if(game->getPaddleTwo() == 1)
	{
		if (key == GLUT_KEY_LEFT) 
		{
			if(game->getPaddle()[1].getXCoordinate() - 21 >= 189)
			{
				game->getPaddle()[1].setXCoordinate(game->getPaddle()[1].getXCoordinate() - 21);
			}	
			else if(game->getPaddle()[1].getXCoordinate() - 5 >= 189)
			{
				game->getPaddle()[1].setXCoordinate(game->getPaddle()[1].getXCoordinate() - 5);
			}
		}
		else if (key == GLUT_KEY_RIGHT) 
		{
			if(game->getPaddle()[1].getXCoordinate() + 21 + game->getPaddle()->getWidth() <= 1001)
			{
				game->getPaddle()[1].setXCoordinate(game->getPaddle()[1].getXCoordinate() + 21);
			}
			else if(game->getPaddle()[1].getXCoordinate() + game->getPaddle()->getWidth() + 5 <= 1001)
			{
				game->getPaddle()[1].setXCoordinate(game->getPaddle()[1].getXCoordinate() + 5);
			}
		}
	}
	glutPostRedisplay();
}

void PrintableKeys(unsigned char key, int x, int y)
{
	if(key == 13)
	{
		int pi = game->getPauseIterate();
		if(game->getWin() == 1)
		{
			game->writeHistory();
			game->writeHighScore();
			if(pi == 0)
			{
				int lev = game->getLevel();
				game = game->Reset();
				game->NextLevel(lev);	
			}
			else if(pi == 1)
			{
				game = game->Reset();
			}
		}
		else if(game->getLoose() == 1)
		{
			game->writeHistory();
			game->writeHighScore();
			if(pi == 0)
			{
				int lev = game->getLevel();
				game = game->Reset();
				game->RestartLevel(lev);	
			}
			else if(pi == 1)
			{
				game = game->Reset();
			}
		}
		else if(game->getPause() == 1)
		{
			if(pi == 0)
			{
				game->setPause(0);
			}
			else if(pi == 1)
			{
				game->writeHistory();
				game->writeHighScore();
				game = game->Reset();
			}
		}
		else if(game->getStartGame() == 0)
		{
			int mi = game->getMenuIterate();
			if(mi == 0)
			{
				if(game->getStarted() == 1)
				{
					game->getPaddle()->deletePaddle();
				}
				game->setStartGame(1);
				game->setStarted(1);
				if(game->getLevel() == 1)
				{
					game->getPaddle()->LoadLevelOne();
				}
				else if(game->getLevel() == 2)
				{
					game->deleteInterface();
					game->getPaddle()->LoadLevelTwo();
					game->setRows(game->getPaddle()->getBrick(0, 0).getRows());
					game->setColomns(game->getPaddle()->getBrick(0, 0).getColomns());
					game->allocateInterface();
					game->getPaddle()->getBall()[0].setXCoordinate(800);
					game->getPaddle()->getBall()[0].setYCoordinate(400);
				}
				else if(game->getLevel() == 3)
				{
					game->deleteInterface(1);
					game->getPaddle()->LoadLevelThree();
					game->setRows(game->getPaddle()->getBrick(0, 0).getRows());
					game->setColomns(game->getPaddle()->getBrick(0, 0).getColomns());
					game->allocateInterface(1);
				}
			}
			else if(mi == 1)
			{
				//game->setPause(0);
			}
			else if(mi == 2)
			{
				if(game->getHighScore() == 1)
				{
					game->setHighScore(0);
				}
				else
				{
					game->setHighScore(1);
				}
			}
			else if(mi == 3)
			{
				if(game->getHistory() == 1)
				{
					game->displayHistory(0);
				}
				else 
				{
					game->displayHistory(1);
				}	
			}
			else if(mi == 4)
			{
				game->ExitGame();
			}
		}		
	}
	
	if (key == 27) 
	{
		if(game->getStartGame() == 1)
		{
			game->setPause(1);
		}
	}
	
	if (key == 'b' || key == 'B')
	{
		cout << "b pressed" << endl;
	}
	glutPostRedisplay();
}
 
void Timer(int m = 0) 
{
	if(game->getStartGame() == 1 && game->getPause() == 0)
	{
		int n = game->getPaddle()->getNumOfBalls();
		float s = game->getPaddle()->getBall()->getSpeed();
		int c = game->getPaddle()->getBall()->getColor();
		if(m == 0)
		{
			for(int i = 0; i < n; i++)
			{
				game->getPaddle()->getBall()[i].setSpeed(7.0);
			}	
		}
		else if(m == 1)
		{
			for(int i = 0; i < n; i++)
			{
				game->getPaddle()->getBall()[i].setSpeed(3.5);
			}
			glutTimerFunc(4500.0, Timer, 0);	
		}
		else if(m == 2)
		{
			for(int i = 0; i < n; i++)
			{
				game->getPaddle()->getBall()[i].setSpeed(12.0);
			}
			glutTimerFunc(4500.0, Timer, 0);
		}
		else if(m == 3)
		{
			Ball* newBalls = new Ball[n + 2];
			for(int i = 0; i < n; i++)
			{
				newBalls[i] = game->getPaddle()->getBall()[i];
				newBalls[i].setSpeed(s);
			}
			if(game->getLevel() == 2)
			{
				newBalls[n].setXCoordinate(800), newBalls[n + 1].setXCoordinate(800);
				newBalls[n].setYCoordinate(400), newBalls[n + 1].setYCoordinate(400);
			}	
			newBalls[n].setSpeed(s), newBalls[n + 1].setSpeed(s);
			newBalls[n].setColor(c), newBalls[n + 1].setColor(c);
			InitRandomizer();
			int a1 = GetRandInRange(45, 136);
			int a2 = GetRandInRange(45, 136);
			if(game->getLevel() == 3)
			{
				do
				{
					a1 = GetRandInRange(0, 361);
				}
				while(a1 == 0 || a1 == 90 || a1 == 180 || a1 == 270 || a1 == 360);
				do
				{
					a2 = GetRandInRange(0, 361);
				}
				while(a2 == 0 || a2 == 90 || a2 == 180 || a2 == 270 || a2 == 360);
			}
			newBalls[n].setAngle(a1), newBalls[n + 1].setAngle(a2);
			game->getPaddle()->setBalls(newBalls, n + 2);
			glutTimerFunc(4500.0, Timer, 4);
		}
		else if(m == 4)
		{
			if(n - 2 > 0)
			{
				Ball* newBalls = new Ball[n - 2];
				for(int i = 0; i < n - 2; i++)
				{
					newBalls[i] = game->getPaddle()->getBall()[i];
				}
				game->getPaddle()->setBalls(newBalls, n - 2);
			}	
		}
		else if(m == 5)
		{
			Ball* newBalls = new Ball;
			if(game->getLevel() == 2)
			{
				newBalls->setXCoordinate(800), newBalls->setYCoordinate(400);
			}
			newBalls->setColor(0);
			game->getPaddle()->setBalls(newBalls, 1);
		}
	}	
}

void MousePressedAndMoved(int x, int y) 
{
	if(game->getStartGame() == 1 && game->getPause() == 0)
	{
		int mx = game->getPaddle()->getMouse();
		int px = game->getPaddle()->getXCoordinate();
		if(mx-x > 0)
		{
			if(px-7 >= 189)
			{
				game->getPaddle()->setXCoordinate(px-7);
			}	
		}
		else 
		{
			if((px + 7 + game->getPaddle()->getWidth()) <= 1001)
			{
				game->getPaddle()->setXCoordinate(px+7);
			}		
		}
		game->getPaddle()->setMouse(x);
	}	
	//glutPostRedisplay();
}

void MouseMoved(int x, int y) 
{
	if(game->getStartGame() == 0)
	{
		game->getPaddle()->setMouse(x);
	}
	else if(game->getStartGame() == 1 && game->getPause() == 0)
	{
		int mx = game->getPaddle()->getMouse();
		int px = game->getPaddle()->getXCoordinate();
		if(mx-x > 0)
		{
			if(px-7 >= 189)
			{
				game->getPaddle()->setXCoordinate(px-7);
			}	
		}
		else 
		{
			if((px + 7 + game->getPaddle()->getWidth()) <= 1001)
			{
				game->getPaddle()->setXCoordinate(px+7);
			}		
		}
		game->getPaddle()->setMouse(x);
	}	
	//glutPostRedisplay();
}

void MouseClicked(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) 
	{
		
	}
	else if (button == GLUT_RIGHT_BUTTON) 
	{
		
	}
	
	glutPostRedisplay();
}
 
int main(int argc, char*argv[]) {

	int width = 1020, height = 840; 
	InitRandomizer(); 
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); 
	glutInitWindowPosition(50, 50); 
	glutInitWindowSize(width, height);
	glutCreateWindow("OOP Project");
	SetCanvasSize(width, height);
	glutDisplayFunc(GameDisplay); 
	glutSpecialFunc(NonPrintableKeys); 
	glutKeyboardFunc(PrintableKeys); 
	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); 
	glutMotionFunc(MousePressedAndMoved); 
	glutMainLoop();
	return 1;
}
#endif /* AsteroidS_CPP_ */
