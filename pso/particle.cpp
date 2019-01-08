#include "particle.h"
#include <fstream>
#include <iostream>
using namespace std;
float particle::Xmax = 30.0f;   //�Լ�ͨ������֤����ͨ�������ٶȺ�λ������ȡ�������õ�Ч�������Ժ����׵شﵽ1e-006�ľ������ϣ��������ܴﵽ1e-009�ľ��ȡ�ԭ�����������Ⱥ���е����Ӷ��ܸ���ؼ��е���Ӧ�ȸߵ�λ�ã���ȻȺ�����Ž�͸��á�
float particle::Xmin = 0.0f;
float particle::Ymax = 30.0f;
float particle::Ymin = 0.0f;
float particle::Vxmax = Xmax - Xmin;  //ͨ������Vmax=Xmax-Xmin;  
float particle::Vxmin = 0 - Vxmax;
float particle::Vymax = Ymax - Ymin;
float particle::Vymin = 0 - Vymax;

float particle::c1 = 2.0f;
float particle::c2 = 2.0f;


particle::particle(float x, float y)
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

void particle::setP()   //������������Ӧ��ֵp�����ã�Ҳ����˾ֲ�����pBest�����ã����Բ���Ҫ�����һ��setPBest()���� ��
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

float particle::getP()const
{
	return p;
}

coordinate particle::getPBest()const
{
	return pBest;
}

void particle::setV(coordinate gBest, float w)  //wΪ�������ӣ�
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

float particle::getVx()const
{
	return Vx;
}
float particle::getVy()const
{
	return Vy;
}


//////////////////////�����Ƚ���setV()�Ĳ���Ȼ����ܽ����ⲽ����������ӵľͲ��ǵ�k+1�ε��ٶ��ˡ�
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
	ofstream out(Dir, ios::app);  //������Ӱɣ�

	out << this->getX() << " " << this->getY() << " " << pBest.x << " " << pBest.y << endl;
	out.close();

}

ostream& operator<<(ostream &output, const particle &right)
{
	output << "Now the current coordinates is X:" << right.getX() << " Y:" << right.getY() << endl;
	output << "And the pBest is X:" << right.getPBest().x << " Y:" << right.getPBest().y << endl;
	return output;
}
