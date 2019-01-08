#pragma once
// 声明了一个类coordinate，用于表示解空间中粒子的坐，包含四个公有成员，两个变量与两个函数
#ifndef COORDINATE_H
#define COORDINATE_H
class coordinate
{
public:
	float x;
	float y;
	coordinate();
	coordinate(float x, float y);  // 重载了类的构造函数
};
#endif
