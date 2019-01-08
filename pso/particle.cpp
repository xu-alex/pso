#include "particle.h"
#include <fstream>
#include <iostream>
using namespace std;
float Particle::Xmax = 30.0f;   //�Լ�ͨ������֤����ͨ�������ٶȺ�λ������ȡ�������õ�Ч�������Ժ����׵شﵽ1e-006�ľ������ϣ��������ܴﵽ1e-009�ľ��ȡ�ԭ�����������Ⱥ���е����Ӷ��ܸ���ؼ��е���Ӧ�ȸߵ�λ�ã���ȻȺ�����Ž�͸��á�
float Particle::Xmin = 0.0f;
float Particle::Ymax = 30.0f;
float Particle::Ymin = 0.0f;
float Particle::Vxmax = Xmax - Xmin;  //ͨ������Vmax=Xmax-Xmin;  
float Particle::Vxmin = 0 - Vxmax;
float Particle::Vymax = Ymax - Ymin;
float Particle::Vymin = 0 - Vymax;

float Particle::c1 = 2.0f;
float Particle::c2 = 2.0f;


Particle::Particle(float x, float y)
{
	c.x = x;
	c.y = y;
	//p=100.0f; //�ȸ���һ���ϴ����Ӧ��ֵ����������Ҫ�õ�����һ����С����Ӧֵ����
	p = pow(c.x - 10.0f, 2) + pow(c.y - 20.0f, 2);
	Vx = (Xmax - Xmin) / 8.0f;  //////////////////////�����Ȳ��õ�һ�ֳ�ʼ��������������������һ����ͬ�ĳ�ʼ�ٶ�,ΪVmax/8.0f,��Vmax=Xmax-Xmin=30-0=30;ע�������ʼ�ٶ�ǧ����̫���Լ����Է������Ĵ�С�����ս���ľ���Ӱ��Ҳ�ܴ��м�������������Ȼ��Ҳ����̫С���Լ����Է�����(Xmax-Xmin)/8.0fʱ���Եõ��Ƚϸߵľ��ȡ�
	Vy = (Xmax - Xmin) / 8.0f;

	///��ʼʱ��pBest

	pBest.x = x;
	pBest.y = y;


}

void Particle::setP()   //������������Ӧ��ֵp�����ã�Ҳ����˾ֲ�����pBest�����ã����Բ���Ҫ�����һ��setPBest()���� ��
{
	float temp = pow(c.x - 10.0f, 2) + pow(c.y - 20.0f, 2);
	if (temp < p)
	{
		p = temp;
		//pBest.x=c.x;
		//pBest.y=c.y;
		pBest = c;
	}
}

float Particle::getP()const
{
	return p;
}

Coordinate Particle::getPBest()const
{
	return pBest;
}

void Particle::setV(Coordinate gBest, float w)  //wΪ�������ӣ�
{
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

float Particle::getVx()const
{
	return Vx;
}
float Particle::getVy()const
{
	return Vy;
}


//////////////////////�����Ƚ���setV()�Ĳ���Ȼ����ܽ����ⲽ����������ӵľͲ��ǵ�k+1�ε��ٶ��ˡ�
void Particle::setCoordinate()
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

float Particle::getX()const
{
	return c.x;
}
float Particle::getY()const
{
	return c.y;
}

void Particle::outputFile(char Dir[])const
{
	ofstream out(Dir, ios::app);  //������Ӱɣ�

	out << this->getX() << " " << this->getY() << " " << pBest.x << " " << pBest.y << endl;
	out.close();

}

ostream& operator<<(ostream &output, const Particle &right)
{
	output << "Now the current coordinates is X:" << right.getX() << " Y:" << right.getY() << endl;
	output << "And the pBest is X:" << right.getPBest().x << " Y:" << right.getPBest().y << endl;
	return output;
}
