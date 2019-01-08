#include "particle.h"
#include <fstream>
#include <iostream>
using namespace std;
/*
	自己通过测试证明，通过限制速度和位置坐标取得了良好的效果，可以很轻易地达到1e-006的精度以上，
	甚至于能达到1e-009的精度。原因就在于整个群体中的粒子都能更快地集中到适应度高的位置，自然群体最优解就更好。
*/
float particle::Xmax = 30.0f;   
float particle::Xmin = 0.0f;
float particle::Ymax = 30.0f;
float particle::Ymin = 0.0f;
// 通常设置Vmax=Xmax-Xmin;
float particle::Vxmax = Xmax - Xmin;   
float particle::Vxmin = 0 - Vxmax;
float particle::Vymax = Ymax - Ymin;
float particle::Vymin = 0 - Vymax;

float particle::c1 = 2.0f;
float particle::c2 = 2.0f;

// 类构造函数的定义
particle::particle(float x, float y)
{
	c.x = x;
	c.y = y;
	// p=100.0f,先给它一个较大的适应度值（这里我们要得到的是一个较小的适应值）。
	p = pow(c.x - 10.0f, 2) + pow(c.y - 20.0f, 2);
	/*
		这里先采用第一种初始化方法，即给所有粒子一个相同的初始速度,为Vmax/8.0f,而Vmax=Xmax-Xmin=30-0=30;注意这个初始速度千万不能太大,
		自己测试发现它的大小对最终结果的精度影响也很大，有几个数量级。当然，也不能太小，自己测试发现在(Xmax-Xmin)/8.0f时可以得到比较高的精度。
	*/
	Vx = (Xmax - Xmin) / 8.0f;
	Vy = (Xmax - Xmin) / 8.0f;

	///初始时的pBest

	pBest.x = x;
	pBest.y = y;
}

void particle::setP()   
{
	/*
	该函数完成了适应度p的设置，也完成了局部最优pBest的设置
	*/
	float temp = pow(c.x - 10.0f, 2) + pow(c.y - 20.0f, 2);
	if (temp < p)
	{
		p = temp;
		//pBest.x=c.x;
		//pBest.y=c.y;
		pBest = c;
	}
}

float particle::getP()const
{
	return p;
}

coordinate particle::getPBest()const
{
	return pBest;
}

void particle::setV(coordinate gBest, float w)
{
	// w为惯性因子
	float r1, r2;
	r1 = rand() / (float)RAND_MAX;
	r2 = rand() / (float)RAND_MAX;
	Vx = w * Vx + c1 * r1*(pBest.x - c.x) + c2 * r2*(gBest.x - c.x);
	if (Vx > Vxmax)
		Vx = Vxmax;
	else if (Vx < Vxmin)
		Vx = Vxmin;
	Vy = w * Vy + c1 * r1*(pBest.y - c.y) + c2 * r2*(gBest.y - c.y);
	if (Vy > Vxmax)
		Vy = Vxmax;
	else if (Vy < Vxmin)
		Vy = Vxmin;
}

float particle::getVx()const
{
	return Vx;
}
float particle::getVy()const
{
	return Vy;
}


// 必须先进行setV()的操作然后才能进行这步，否则坐标加的就不是第k+1次的速度了。
void particle::setcoordinate()
{
	c.x = c.x + Vx;
	if (c.x > Xmax)
		c.x = Xmax;
	else if (c.x < Xmin)
		c.x = Xmin;
	c.y = c.y + Vy;
	if (c.y > Ymax)
		c.y = Ymax;
	else if (c.y < Ymin)
		c.y = Ymin;
}

float particle::getX()const
{
	return c.x;
}
float particle::getY()const
{
	return c.y;
}

void particle::outputFile(char Dir[])const
{
	// 这是添加吧？
	ofstream out(Dir, ios::app);

	out << this->getX() << " " << this->getY() << " " << pBest.x << " " << pBest.y << endl;
	out.close();

}

ostream& operator<<(ostream &output, const particle &right)
{
	output << "Now the current coordinates is X:" << right.getX() << " Y:" << right.getY() << endl;
	output << "And the pBest is X:" << right.getPBest().x << " Y:" << right.getPBest().y << endl;
	return output;
}
