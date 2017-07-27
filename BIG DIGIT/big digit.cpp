#include<bits/stdc++.h>
using namespace std;
class _int {
private:
	int size = 128;		//最大的位数
	char *pt;
	int length;			//表示十进制数的长度
	bool sign;			//标记正负号
public:
	template<class T>
	_int(T _num);
	_int();
	_int(_int &a);
	template<class T>
	T operator=(T _a);
	friend ostream& operator<<(ostream &os, _int &a);
	const _int& operator=(const _int &_a);
	~_int();
};

template<class T>
_int::_int(T _num) {
	pt = new char[size]();
	*this = _num;
}

const _int& _int::operator=(const _int &_a)
{
	length = _a.length;
	sign = _a.sign;
	for (int i = length - 1; i >= 0; i--) {
		pt[i] = _a.pt[i];
	}
	return _a;
}

template<class T>
T _int::operator=(T _a) {
	int cnt = 0;
	T k = _a;
	if (_a < 0)sign = true;
	else sign = false;
	_a = abs(_a);
	if (_a == 0)pt[cnt++] = '0';
	else while (_a) {
		pt[cnt++] = _a % 10 + '0';
		_a /= 10;
	}
	length = cnt;
	return k;
}

_int::_int(_int &a)
{
	pt = new char[size]();
	*this = a;
}

_int::~_int() {
	delete[]pt;
}

_int::_int() {
	pt = new char[size]();
	*this = 0;
}

ostream& operator<<(ostream &os, _int &a)
{
	if (a.sign)printf("-");
	for (int i = a.length - 1; i >= 0; i--)printf("%c", a.pt[i]);
	return os;
}

int main()
{
	_int a = 10;
	_int b = a;
	a = 1000;
	b = a;
	cout << a << " " << b;
	return 0;
}