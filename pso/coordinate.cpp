#include "coordinate.h"
using namespace std;
/*
	重载与重写的区别在于，重载函数之间是同一个类的函数的参数列表不同。
	而重写函数则涉及到继承问题
*/
// 默认的类构造函数
coordinate::coordinate()
{
	// 为x与y赋默认初值
	x = 0.0f;
	y = .0f;
}
// 对类构造函数的重载
coordinate::coordinate(float x, float y)
{
	// 使用参数列表中参数为x和y赋初值
	this->x = x;
	this->y = y;
}
