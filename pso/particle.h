#pragma once
#ifndef PARTICLE_H
#define PARTICLE_H
#include "coordinate.h"
#include <math.h>
#include <iostream>
using namespace std;
class Particle
{
	friend ostream& operator<<(ostream &output, const Particle &right);

public:
	Particle(float x, float y);
	void setP();
	float getP()const;

	//void setPBest();  //pBest��������setP()�о�����ˡ�
	Coordinate getPBest()const;

	///////////////////////���ǵ�һ�ַ����������ú㶨��ѧϰ���ӡ�����ʵ���Ͽɱ��ѧϰ����c1,c2����ʹ��Ⱥ������������˴���������ά�ȵ��ٶ����÷���ͬһ�������С�
	void setV(Coordinate gBest, float w); //wΪ�������ӡ�
	float getVx()const;
	float getVy()const;

	void setCoordinate();
	float getX()const;
	float getY()const;

	void outputFile(char Dir[])const;
private:
	Coordinate c;
	float p;  //pΪ��Ӧ�ȡ�
	Coordinate pBest;
	////////////////////��ά�Ļ���Ҫ�������ٶȡ�
	float Vx;
	float Vy;
	static float Xmax, Xmin;
	static float Ymax, Ymin;
	static float Vxmax, Vxmin; //������������������ٶȽ������Ƶģ�������ֻ����һ���ķ�Χ�ڡ�
	static float Vymax, Vymin;
	static float c1, c2; //c1,c2��ѧϰ���ӡ�
	//����Ҫ�����еĶ�����бȽ�֮����ܵõ�Ⱥ�����ţ����������ǲ�
	//static Coordinate gBest; //�����Ⱥ������.����Ⱥ�干��һ�ݾ��У����Խ������ó�static������ע��ǧ��Ҫ��Ϊstatic�����ڳ�ʼ����Ͳ����޸ĵģ�static const����������

};

#endif
