#pragma once
#ifndef PARTICLE_H
#define PARTICLE_H
#include "coordinate.h"
#include <math.h>
#include <iostream>
using namespace std;
class particle
{
	//友元函数
	friend ostream& operator<<(ostream &output, const particle &right);

public:
	particle(float x, float y);  // 类的构造函数
	void setP();
	float getP()const;

	//void setPBest();  //pBest的设置在setP()中就完成了。
	coordinate getPBest()const;

	//这是第一种方法，即采用恒定的学习因子。但是实际上可变的学习因子c1,c2
	//可以使种群更快地收敛。此处，将两个维度的速度设置放在同一个函数中。
	void setV(coordinate gBest, float w); //w为惯性因子。
	float getVx()const;
	float getVy()const;

	void setcoordinate();
	float getX()const;
	float getY()const;

	void outputFile(char Dir[])const;
private:
	coordinate c;
	float p;  //p为适应度。
	coordinate pBest;
	////////////////////二维的话就要有两个速度。
	float Vx;
	float Vy;
	static float Xmax, Xmin;
	static float Ymax, Ymin;
	static float Vxmax, Vxmin; //它们是用来对坐标和速度进行限制的，限制它只能在一定的范围内。
	static float Vymax, Vymin;
	static float c1, c2; //c1,c2是学习因子。
	//由于要对所有的对象进行比较之后才能得到群体最优，所以它还是不
	//static coordinate gBest; //这个是群体最优.整个群体共享一份就行，所以将它设置成static，
	//但是注意千万不要以为static都是在初始化后就不能修改的，static const才是那样。
};

#endif
