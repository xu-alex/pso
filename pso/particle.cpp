#include "particle.h"
#include <fstream>
#include <iostream>
using namespace std;
/*
	通过测试证明，限制速度和位置的坐标取得了良好的效果，能很轻易
	地达到1e-006以上的精度，甚至于能达到1e-009的精度。因为整个
	群体中的粒子都能更快地集中到适应度高的位置，自然群体最优解就更好。
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

// 设置学习因子为常数值
float particle::c1 = 2.0f;
float particle::c2 = 2.0f;

particle::particle(float x, float y)
{
	// 类构造函数的定义
	c.x = x;
	c.y = y;
	// 计算该粒子的初始位置到（10，20）的距离，作为粒子适应度的初值
	p = pow(c.x - 10.0f, 2) + pow(c.y - 20.0f, 2);
	/*
		采用第一种速度初始化方法，即给所有粒子一个相同的初始速度,为Vmax/8.0f,
		而Vmax=Xmax-Xmin=30-0=30;注意这个初始速度千万不能太大，经测试发现它的
		大小对最终结果的精度影响也很大，有几个数量级。当然，也不能太小。经测试发现
		在(Xmax-Xmin)/8.0f时可以得到比较高的精度。
	*/
	Vx = (Xmax - Xmin) / 8.0f;  
	Vy = (Xmax - Xmin) / 8.0f;

	// 将每个粒子的历史最优适应度值初始化
	pBest.x = x;
	pBest.y = y;
}

void particle::setP()   
{
	// 设置粒子的最优解pBest
	float temp = pow(c.x - 10.0f, 2) + pow(c.y - 20.0f, 2);
	if (temp < p)
	{
		p = temp;
		pBest = c;
	}
}

float particle::getP() const
{
	// 返回粒子的当前适应度值
	return p;
}

coordinate particle::getPBest() const
{
	// 返回当前粒子的最优解
	return pBest;
}

void particle::setV(coordinate gBest, float w)
{
	// 设置粒子的更新速度
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

void particle::setcoordinate()
{
	// 更新粒子的位置
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
	// 将粒子的当前位置信息和最优位置信息写入文件中并保存
	/*
		ios::app表示以追加模式打开文件夹。如果没有文件，那么生成空文件；
		如果有文件，那么在文件尾追加
	*/
	ofstream out(Dir, ios::app);

	out << this->getX() << " " << this->getY() << " " << pBest.x << " " << pBest.y << endl;
	out.close();

}

ostream& operator<<(ostream &output, const particle &right)
{
	// 操作符重载
	output << "Now the current coordinates is X:" << right.getX() << " Y:" << right.getY() << endl;
	output << "And the pBest is X:" << right.getPBest().x << " Y:" << right.getPBest().y << endl;
	return output;
}
