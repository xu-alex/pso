#pragma once
#ifndef PARTICLE_H
#define PARTICLE_H
#include "coordinate.h"
#include <math.h>
#include <iostream>
using namespace std;
class particle
{
	//��Ԫ����
	friend ostream& operator<<(ostream &output, const particle &right);

public:
	particle(float x, float y);  // ��Ĺ��캯��
	void setP();
	float getP()const;

	//void setPBest();  //pBest��������setP()�о�����ˡ�
	coordinate getPBest()const;

	//���ǵ�һ�ַ����������ú㶨��ѧϰ���ӡ�����ʵ���Ͽɱ��ѧϰ����c1,c2
	//����ʹ��Ⱥ������������˴���������ά�ȵ��ٶ����÷���ͬһ�������С�
	void setV(coordinate gBest, float w); //wΪ�������ӡ�
	float getVx()const;
	float getVy()const;

	void setcoordinate();
	float getX()const;
	float getY()const;

	void outputFile(char Dir[])const;
private:
	coordinate c;
	float p;  //pΪ��Ӧ�ȡ�
	coordinate pBest;
	////////////////////��ά�Ļ���Ҫ�������ٶȡ�
	float Vx;
	float Vy;
	static float Xmax, Xmin;
	static float Ymax, Ymin;
	static float Vxmax, Vxmin; //������������������ٶȽ������Ƶģ�������ֻ����һ���ķ�Χ�ڡ�
	static float Vymax, Vymin;
	static float c1, c2; //c1,c2��ѧϰ���ӡ�
	//����Ҫ�����еĶ�����бȽ�֮����ܵõ�Ⱥ�����ţ����������ǲ�
	//static coordinate gBest; //�����Ⱥ������.����Ⱥ�干��һ�ݾ��У����Խ������ó�static��
	//����ע��ǧ��Ҫ��Ϊstatic�����ڳ�ʼ����Ͳ����޸ĵģ�static const����������
};

#endif
