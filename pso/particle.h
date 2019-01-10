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
		普通的非类成员函数友元：通常是操作符，例如输入或输出操作符。
	*/
	// 声明一个友元函数，在类particle中对操作符<<重载
	friend ostream& operator<<(ostream &output, const particle &right);  

public:
	// particle类的构造函数
	particle(float x, float y);  
	// 计算粒子的适应度值
	void setP();
	// 获取粒子的适应度值
	float getP()const;

	// 获取粒子的历史最优适应度值对应的坐标
	coordinate getPBest()const;

	/*
		由于要对所有的对象进行比较之后才能得到群体最优，所以gBest是个静态变量，
		整个群体共享一份就行。static在初始化后就还能修改，且所有的particle类的实例中
		gBest值都是一样的。而static const就不能在初始化之后进行修改。
	*/
	static coordinate gBest;

	// 使用恒定的学习因子更新粒子的速度，虽然可变的学习因子可以使计算更快的收敛
	void setV(coordinate gBest, float w); 
	// 获取速度V在x维度的分量
	float getVx()const;
	// 获取速度V在y维度的分量
	float getVy()const;

	// 根据前面计算的速度更新粒子的位置
	void setcoordinate();
	// 获取位置在x维度的分量
	float getX()const;
	// 获取位置在y维度的分量
	float getY()const;

	void outputFile(char Dir[])const;
private:
	// c表示粒子的当前位置
	coordinate c;
	//p表示适应度值
	float p;
	// 表示粒子的最优适应度对应的坐标
	coordinate pBest;
	// 定义两个类的私有成员存储粒子的位置
	float Vx;
	float Vy;
	// 用于限制粒子的位置以及运动速度，使它们在一定的范围内变化
	static float Xmax, Xmin;
	static float Ymax, Ymin;	
	static float Vxmax, Vxmin;
	static float Vymax, Vymin;
	// c1,c2是学习因子。
	static float c1, c2; 
	
};
#endif
