#include "coordinate.h"
using namespace std;
// Ĭ�ϵ��๹�캯��
coordinate::coordinate()
{
	// Ϊx��y����ֵ
	x = 0.0f;
	y = .0f;
}
// ���๹�캯��������
coordinate::coordinate(float x, float y)
{
	this->x = x;
	this->y = y;
}
