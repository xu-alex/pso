#include "coordinate.h"
using namespace std;
// 默认的类构造函数
coordinate::coordinate()
{
	// 为x与y赋初值
	x = 0.0f;
	y = .0f;
}
// 对类构造函数的重载
coordinate::coordinate(float x, float y)
{
	this->x = x;
	this->y = y;
}
