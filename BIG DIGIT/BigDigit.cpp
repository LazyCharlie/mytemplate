#include<iostream>
#include<algorithm>
using namespace std;
#define SIZE 128
bool isfail = false;
class _int {
private:
	char s[SIZE];
	int length;			//表示十进制数的长度
	bool sign;			//标记正负号
public:
	template<class T>
	_int(T _num);
	_int();
	_int(const _int &a);

	template<class T>
	T operator=(T _a);

	const _int& operator=(const _int &_a);

	friend ostream& operator<<(ostream &os, const _int &a);

	template<class T>
	friend const _int operator+(T a, _int _b);

	template<class T>
	const _int operator+(T a);

	const _int operator+(_int a);

	friend istream& operator>>(istream &is, _int &a);

	template<class T>
	friend bool operator!=(T a, const _int &b);

	~_int();
};

template<class T>
_int::_int(T _num) {
	*this = _num;
}

template<class T>
const _int operator+(T a, _int _b)//只写了正数相加或负数相加   还差正数和负数相加
{
	int cnt = 0, add = 0;
	a = abs(a);
	if (a < 0 && _b.sign == true || a >= 0 && _b.sign == false) {
		while (a) {
			char t = _b.s[cnt];
			if (cnt >= _b.length)_b.s[cnt] = '0';
			_b.s[cnt] = (_b.s[cnt] - '0' + a % 10 + add) % 10 + '0';
			cnt++;
			add = (t - '0' + a % 10 + add) / 10;
			a /= 10;
		}
		if (add > 0) {
			_b.s[cnt++] = add + '0';
		}
		_b.length = max(cnt, _b.length);
	}
	else {

	}
	return _b;
}

istream& operator>>(istream &is, _int &a)  //包含了处理eof模块，可以从输入流中读取位数不超过SIZE的大整数
{								  //能达到和平常cin基本一致的效果
	int cnt = 0; bool signflag = false;//判断是否读入了负号
	bool read = false;			//判断输入流是否到达结尾
	char k[SIZE], t = ' ';
	while (~scanf("%c", &t)) {
		if (!isspace(t)) {
			read = true;
			break;
		}
	}
	bool hassign = false;
	if (read&&isdigit(t))k[cnt++] = t;
	else if (read&&t == '-') {
		a.sign = true; 
		hassign = true;
	}  //读入负数
	else if (read&&t == '+') {
		a.sign = false;
		hassign = true;
	}
	else if (read)is.unget();
	while (~scanf("%c", &t)) {
		if (isdigit(t)) {
			k[cnt++] = t;
		}
		else if (isspace(t)) {
			is.unget();
			break;
		}
		else {
			is.unget();
			if (hassign && !cnt)is.unget();
			break;
		}
	}
	int j = cnt;
	bool flag = false;
	for (int i = 0; i < cnt; i++) {
		if (k[i] != '0' && !flag) {
			flag = true;
		}
		else if (flag == false && i != cnt - 1)j--;
		if (flag || i == cnt - 1) {
			a.s[cnt - i - 1] = k[i];
		}
	}
	a.length = j;
	if (isspace(t) && !j) {
		is.setstate(ios::failbit);    //如果只读到空格或者空格也没读到  说明已经到了文件结尾
		isfail = false;
	}
	else if (!isspace(t) && isfail || !j && !isspace(t)) {
		is.setstate(ios::failbit);   //如果之前一次读取已经遇到了其他字符，说明类型不符
		isfail = false;
	}
	else if (!isspace(t) && !isfail)isfail = true;     //如果之前一次读取正常但这次遇到其他字符，先进行记录
	else isfail = false;
	return is;
}

template<class T>
bool operator!=(T a, const _int &b)
{
	if (a < 0 && b.sign == false || a >= 0 && b.sign == true)return true;
	for (int i = 0; i < b.length; i++) {
		if (b.s[i] - '0' != a % 10)return true;
		a /= 10;
	}
	if (a)return true;
	return false;
}

const _int _int::operator+(_int a)
{
	int len = max(a.length, length);
	int add = 0;
	if (a.sign == sign) {
		for (int i = 0; i < len; i++) {
			char ta = i < a.length ? a.s[i] : '0';
			char tb = i < length ? s[i] : '0';
			a.s[i] = (ta + tb - '0' * 2 + add) % 10 + '0';
			add = (ta + tb - '0' * 2 + add) / 10;
		}
		if (add)a.s[len++] = '0' + add;
		a.length = len;
	}
	return a;
}

template<class T>
const _int _int::operator+(T a)
{
	return a + *this;
}

const _int& _int::operator=(const _int &_a)
{
	length = _a.length;
	sign = _a.sign;
	for (int i = length - 1; i >= 0; i--) {
		s[i] = _a.s[i];
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
	if (_a == 0)s[cnt++] = '0';
	else while (_a) {
		s[cnt++] = _a % 10 + '0';
		_a /= 10;
	}
	length = cnt;
	return k;
}

_int::_int(const _int &a)
{
	*this = a;
}

_int::~_int() {}

_int::_int() {
	*this = 0;
}

ostream& operator<<(ostream &os, const _int &a)
{
	if (a.sign)printf("-");
	for (int i = a.length - 1; i >= 0; i--)printf("%c", a.s[i]);
	return os;
}
_int a, b;
//long long a, b;
int main()
{
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	//cin >> a >> b;
	while (cin >> a >> b&&(0!=a||0!=b)) {
		cout << a + b << endl;
	}
	///for (int i = 0; i < 10000; i++) {
	//	int d = rand() % 18 + 1;
	//	for (int i = 0; i < d; i++)printf("%d", rand() % 9 + 1);
	//	d = rand() % 18 + 1;
	//	printf(" ");
	//	for (int i = 0; i < d; i++)printf("%d", rand() % 9 + 1);
	//	printf("\n");
//	}
}
