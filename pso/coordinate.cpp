#include "coordinate.h"
using namespace std;
/*
	��������д���������ڣ����غ���֮����ͬһ����ĺ����Ĳ����б�ͬ��
	����д�������漰���̳�����
*/
// Ĭ�ϵ��๹�캯��
coordinate::coordinate()
{
	// Ϊx��y��Ĭ�ϳ�ֵ
	x = 0.0f;
	y = .0f;
}
// ���๹�캯��������
coordinate::coordinate(float x, float y)
{
	// ʹ�ò����б��в���Ϊx��y����ֵ
	this->x = x;
	this->y = y;
}
