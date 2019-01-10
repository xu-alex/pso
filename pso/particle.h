#pragma once
#ifndef PARTICLE_H
#define PARTICLE_H
#include "coordinate.h"
#include <math.h>
#include <iostream>
using namespace std;
class particle
{
	/*
		C++�е���Ԫ����������ķǹ��г�Ա��һ������ߺ������ʡ�
		��Ԫ�����ͷ�Ϊ���֣���ͨ�����Ա������Ϊ��Ԫ,��ĳ�Ա������Ϊ��Ԫ������Ϊ��Ԫ��
		��Ԫ������Ĭ��Ϊextern������˵��Ԫ�������Ԫ�������������Ѿ���չ���˰������ඨ���������
		��ͨ�ķ����Ա������Ԫ��ͨ���ǲ���������������������������
	*/
	// ����һ����Ԫ����������particle�жԲ�����<<����
	friend ostream& operator<<(ostream &output, const particle &right);  

public:
	// particle��Ĺ��캯��
	particle(float x, float y);  
	// �������ӵ���Ӧ��ֵ
	void setP();
	// ��ȡ���ӵ���Ӧ��ֵ
	float getP()const;

	// ��ȡ���ӵ���ʷ������Ӧ��ֵ��Ӧ������
	coordinate getPBest()const;

	/*
		����Ҫ�����еĶ�����бȽ�֮����ܵõ�Ⱥ�����ţ�����gBest�Ǹ���̬������
		����Ⱥ�干��һ�ݾ��С�static�ڳ�ʼ����ͻ����޸ģ������е�particle���ʵ����
		gBestֵ����һ���ġ���static const�Ͳ����ڳ�ʼ��֮������޸ġ�
	*/
	static coordinate gBest;

	// ʹ�ú㶨��ѧϰ���Ӹ������ӵ��ٶȣ���Ȼ�ɱ��ѧϰ���ӿ���ʹ������������
	void setV(coordinate gBest, float w); 
	// ��ȡ�ٶ�V��xά�ȵķ���
	float getVx()const;
	// ��ȡ�ٶ�V��yά�ȵķ���
	float getVy()const;

	// ����ǰ�������ٶȸ������ӵ�λ��
	void setcoordinate();
	// ��ȡλ����xά�ȵķ���
	float getX()const;
	// ��ȡλ����yά�ȵķ���
	float getY()const;

	void outputFile(char Dir[])const;
private:
	// c��ʾ���ӵĵ�ǰλ��
	coordinate c;
	//p��ʾ��Ӧ��ֵ
	float p;
	// ��ʾ���ӵ�������Ӧ�ȶ�Ӧ������
	coordinate pBest;
	// �����������˽�г�Ա�洢���ӵ�λ��
	float Vx;
	float Vy;
	// �����������ӵ�λ���Լ��˶��ٶȣ�ʹ������һ���ķ�Χ�ڱ仯
	static float Xmax, Xmin;
	static float Ymax, Ymin;	
	static float Vxmax, Vxmin;
	static float Vymax, Vymin;
	// c1,c2��ѧϰ���ӡ�
	static float c1, c2; 
	
};
#endif
