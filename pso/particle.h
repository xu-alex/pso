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
		C++中的友元机制允许类的非公有成员被一个类或者函数访问。
		友元按类型分为三种：普通非类成员函数作为友元,类的成员函数作为友元，类作为友元。
		友元的声明默认为extern，就是说友元类或者友元函数的作用域已经扩展到了包含该类定义的作用域。
		普通的非类成员函数友元：通常是操作符，例如输入输出操作符。
	*/
	// 声明一个友元函数，在类particle中对操作符<<重载
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
	// c表示粒子的当前位置
	coordinate c;
	float p;  //p为适应度。
	coordinate pBest;
	////////////////////二维的话就要有两个速度。
	float Vx;
	float Vy;
	// 用于限制坐标和速度，使它们在一定的范围内变化
	static float Xmax, Xmin;
	static float Ymax, Ymin;	
	static float Vxmax, Vxmin;
	static float Vymax, Vymin;
	static float c1, c2; //c1,c2是学习因子。
	/*
		由于要对所有的对象进行比较之后才能得到群体最优，所以它还是不
		static coordinate gBest; 
		这个是群体最优.整个群体共享一份就行，所以将它设置成static，
		但是注意千万不要以为static都是在初始化后就不能修改的，static const才是那样。
	*/
	
};
#endif
