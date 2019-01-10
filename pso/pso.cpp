﻿// pso.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "pch.h"
#include <iostream>
#include "particle.h"
#include <stdio.h> //因为要用到sprintf函数。
#include <time.h>
#include <string>
#include <math.h>
#include <fstream> /// 因为要用到ofstream类
using namespace std;
/*
	1.初始化一群粒子
	2.为每个粒子设定一个初始位置，将该位置设定为每个粒子的初始最优位置pbest。
	3.根据第二步的设定，计算每个粒子的适应度。经对比后将最优适应值对应的粒子设定为gbest。
	4.根据设定的惯性因子，随机参数以及学习参数，更新每个粒子在下一代的运动方向和速度。
	5.更新每个粒子的位置，然后计算pbest和gbest。再判断是否符合迭代的要求。
*/
int main()
{
	/******************************粒子群初始化*********************************/
	particle* p[40];  // 设定粒子群内的个体数
	float w;// 惯性因子，实际上是wmax=1.2f;此处设置wmin=0.5;

	particle* temp;
	float randX, randY; // 随机参数
	srand((int)time(NULL));
	for (int i = 0; i < 40; ++i)
	{
		randX = (rand() / (float)RAND_MAX)*30.0f;
		randY = (rand() / (float)RAND_MAX)*30.0f;
		cout << "randX=" << randX << endl;
		cout << "randY=" << randY << endl;

		p[i] = new particle(randX, randY); // 调用自定义的类初始化函数
		cout << "The temp info is X:" << p[i]->getX() << " Y:" << p[i]->getY() << endl;
	}
	/**********计算适应度p、每个粒子的pbest和以及种群最优粒子gbest，寻找最初的种群最优************/
	coordinate gBest;  // 全局最优解的位置
	int bestIndex = 0;   // 
	float bestP; // 最优的适应度值
	bestP = p[0]->getP();  // 函数返回最优适应度值
	gBest = p[0]->getPBest();  // 函数返回最优适应度值对应的粒子的坐标
	for (int i = 1; i < 40; ++i) // 对比粒子群里每个粒子的适应度值
	{
		/*通过循环对比，判断粒子群的最优适应度值及其对应的粒子*/
		if (p[i]->getP() < bestP)
		{
			bestP = p[i]->getP();
			gBest = p[i]->getPBest();
			bestIndex = i;
		}
	}

	cout << "Now the initial gBest is X:" << gBest.x << " Y:" << gBest.y << endl;
	cout << "And the p[0] is X:" << p[0]->getX() << " Y:" << p[0]->getY() << endl;
	cout << "And the p[39] is X:" << p[39]->getX() << " Y:" << p[39]->getY() << endl;
	cout << "Now p[0].p=" << p[0]->getP() << endl;
	
	// 至此，已经寻找到初始时的种群最优。
	char buf[20];
	for (int i = 0; i < 40; ++i)
	{
		sprintf(buf, "coordinate%d.dat", i); // 构建一段字符串
		ofstream out(buf, ios::out); // 创建一个文件，其带文件格式的名称为coordinate_i.dat
		out.close(); // 关闭文件操作
	}
	// 这样做是为了每运行一次都重复添加。
	// 开始迭代计算，以求找出最好的解
	for (int k = 0; k < 100; ++k)   //k为迭代次数。
	{
		
		/*
			这个因子很重要，既不能太大也不能太小。一开始自己就是设置得太大了导致出错。自己通过计算发现采用
			可变的惯性因子可以使得到的结果的精确度高一个数量级(达到1e-006)，而如果采用恒定的惯性因子，则只
			能得到1e-005的精度。一开始wmax=1.0,wmin=0.6,可以达到1e-006的精度，以为很高了，但是实际上
			wmax=0.9f,wmin=0.4f进可以很轻易地达到1e-11的水平，而这已经接近float的精度极限。
		*/
		// w=0.85f;
		w = 0.9f - (0.9f - 0.4f)*k / 99.0f;  		
	   
		// 将所有粒子的位置更新一次
		for (int i = 0; i < 40; ++i)
		{
			temp = p[i];
			temp->setV(gBest, w);
			temp->setcoordinate();
			temp->setP();
			sprintf(buf, "coordinate%d.dat", i);
			temp->outputFile(buf);
		}
		// 再通过逐个对比的方式确定本轮迭代过后，最优适应度对应的例子gbest
		bestP = p[0]->getP();
		gBest = p[0]->getPBest();
		for (int i = 1; i < 40; ++i)
		{
			temp = p[i];
			if (temp->getP() < bestP)
			{
				bestP = temp->getP();
				gBest = temp->getPBest();
				bestIndex = i;
			}
			/*
			if((pow(gBest.x-10,2)+pow(gBest.y-20,2))<0.00001f)
			{
				cout<<"The gBest which is good enough has found!"<<endl;
				cout<<"The index is "<<i<<endl;
				cout<<"gBest is X:"<<gBest.x<<" Y:"<<gBest.y<<endl;
				 exit(0);
			}
			*/
		}
		cout << "Now gBest is X:" << gBest.x << " Y:" << gBest.y << " and the minP=" << p[bestIndex]->getP() << endl;
		cout << "bestIndex=" << bestIndex << endl;
	}
	system("pause");
	return 0;
}