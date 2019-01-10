#include "particle.h"
#include <fstream>
#include <iostream>
using namespace std;
/*
	ͨ������֤���������ٶȺ�λ�õ�����ȡ�������õ�Ч�����ܺ�����
	�شﵽ1e-006���ϵľ��ȣ��������ܴﵽ1e-009�ľ��ȡ���Ϊ����
	Ⱥ���е����Ӷ��ܸ���ؼ��е���Ӧ�ȸߵ�λ�ã���ȻȺ�����Ž�͸��á�
*/
float particle::Xmax = 30.0f;   
float particle::Xmin = 0.0f;
float particle::Ymax = 30.0f;
float particle::Ymin = 0.0f;
// ͨ������Vmax=Xmax-Xmin;
float particle::Vxmax = Xmax - Xmin;   
float particle::Vxmin = 0 - Vxmax;
float particle::Vymax = Ymax - Ymin;
float particle::Vymin = 0 - Vymax;

// ����ѧϰ����Ϊ����ֵ
float particle::c1 = 2.0f;
float particle::c2 = 2.0f;

particle::particle(float x, float y)
{
	// �๹�캯���Ķ���
	c.x = x;
	c.y = y;
	// ��������ӵĳ�ʼλ�õ���10��20���ľ��룬��Ϊ������Ӧ�ȵĳ�ֵ
	p = pow(c.x - 10.0f, 2) + pow(c.y - 20.0f, 2);
	/*
		���õ�һ���ٶȳ�ʼ��������������������һ����ͬ�ĳ�ʼ�ٶ�,ΪVmax/8.0f,
		��Vmax=Xmax-Xmin=30-0=30;ע�������ʼ�ٶ�ǧ����̫�󣬾����Է�������
		��С�����ս���ľ���Ӱ��Ҳ�ܴ��м�������������Ȼ��Ҳ����̫С�������Է���
		��(Xmax-Xmin)/8.0fʱ���Եõ��Ƚϸߵľ��ȡ�
	*/
	Vx = (Xmax - Xmin) / 8.0f;  
	Vy = (Xmax - Xmin) / 8.0f;

	// ��ÿ�����ӵ���ʷ������Ӧ��ֵ��ʼ��
	pBest.x = x;
	pBest.y = y;
}

void particle::setP()   
{
	// �������ӵ����Ž�pBest
	float temp = pow(c.x - 10.0f, 2) + pow(c.y - 20.0f, 2);
	if (temp < p)
	{
		p = temp;
		pBest = c;
	}
}

float particle::getP() const
{
	// �������ӵĵ�ǰ��Ӧ��ֵ
	return p;
}

coordinate particle::getPBest() const
{
	// ���ص�ǰ���ӵ����Ž�
	return pBest;
}

void particle::setV(coordinate gBest, float w)
{
	// �������ӵĸ����ٶ�
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
	// �������ӵ�λ��
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
	// �����ӵĵ�ǰλ����Ϣ������λ����Ϣд���ļ��в�����
	/*
		ios::app��ʾ��׷��ģʽ���ļ��С����û���ļ�����ô���ɿ��ļ���
		������ļ�����ô���ļ�β׷��
	*/
	ofstream out(Dir, ios::app);

	out << this->getX() << " " << this->getY() << " " << pBest.x << " " << pBest.y << endl;
	out.close();

}

ostream& operator<<(ostream &output, const particle &right)
{
	// ����������
	output << "Now the current coordinates is X:" << right.getX() << " Y:" << right.getY() << endl;
	output << "And the pBest is X:" << right.getPBest().x << " Y:" << right.getPBest().y << endl;
	return output;
}
