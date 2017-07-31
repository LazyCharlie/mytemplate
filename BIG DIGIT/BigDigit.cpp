#include<bits/stdc++.h>
using namespace std;
#define SIZE 128      //注意：做大整数乘法运算时，开的数组大小不小于一个大于这两个数之和的最小二次幂
//size开多大基本上对时间影响不大，除非_int数组开很大   预定义size主要是考虑空间复杂度优化
const double PI = acos(-1.0);
int ans[SIZE];//储存乘法的答案;
bool isfail = false;
//复数结构体
struct cmplex
{
	double r, i;
	cmplex(double _r = 0.0, double _i = 0.0)
	{
		r = _r; i = _i;
	}
	cmplex operator +(const cmplex &b)
	{
		return cmplex(r + b.r, i + b.i);
	}
	cmplex operator -(const cmplex &b)
	{
		return cmplex(r - b.r, i - b.i);
	}
	cmplex operator *(const cmplex &b)
	{
		return cmplex(r*b.r - i*b.i, r*b.i + i*b.r);
	}
}x1[SIZE], x2[SIZE];
void change(cmplex y[], int len)
{
	int i, j, k;
	for (i = 1, j = len / 2; i < len - 1; i++)
	{
		if (i < j)swap(y[i], y[j]);
		//交换互为小标反转的元素，i<j保证交换一次
		//i做正常的+1，j左反转类型的+1,始终保持i和j是反转的
		k = len / 2;
		while (j >= k)
		{
			j -= k;
			k /= 2;
		}
		if (j < k) j += k;
	}
}
/*
* 做FFT 时,len必须为2^k形式，
* on==1时是DFT，on==-1时是IDFT
*/
void fft(cmplex y[], int len, int on)
{
	change(y, len);
	for (int h = 2; h <= len; h <<= 1)
	{
		cmplex wn(cos(-on * 2 * PI / h), sin(-on * 2 * PI / h));
		for (int j = 0; j < len; j += h)
		{
			cmplex w(1, 0);
			for (int k = j; k < j + h / 2; k++)
			{
				cmplex u = y[k];
				cmplex t = w*y[k + h / 2];
				y[k] = u + t;
				y[k + h / 2] = u - t;
				w = w*wn;
			}
		}
	}
	if (on == -1)
		for (int i = 0; i < len; i++)
			y[i].r /= len;
}

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
	
	_int operator*(const _int &a);

	operator bool();

//	template<class T>
//	_int operator/(T a);

	bool cmp(const char *a, const char *b, int len);

	const _int& operator=(const _int &_a);

	friend istream& operator>>(istream &is, _int &a);

	friend ostream& operator<<(ostream &os, const _int &a);


	template<class T>
	friend const _int operator+(T a, _int _b);

	template<class T>
	friend const _int operator*(T a, _int _b);

	template<class T>
	friend const _int operator-(T a, _int _b);

	bool operator<=(const _int &a);

	template<class T>
	bool operator<=(T a);

	template<class T>
	friend bool operator<=(T a, const _int &b);

	bool operator>=(const _int &a);

	template<class T>
	bool operator>=(T a);

	template<class T>
	friend bool operator>=(T a, const _int &b);

	template<class T>
	bool operator<(T a);

	bool operator<(const _int &a);

	template<class T>
	friend bool operator<(T a, _int& b);

	template<class T>
	friend bool operator>(T a, _int &b);

	template<class T>
	bool operator>(T a);

	bool operator>(const _int &a);

	_int operator++(int);    //后置++

	_int operator--(int);    //后置--

	_int operator++();

	_int operator--();

	const _int operator+(_int a);

	const _int operator-(_int a);

	template<class T>
	const _int operator-(T a);

	template<class T>
	const _int operator+(T a);

	template<class T>
	const _int operator*(T a);

	template<class T>
	void operator+=(T a);

	template<class T>
	void operator-=(T a);

	void operator+=(_int &a);

	void operator*=(const _int &a);

	void operator-=(_int &a);

	template<class T>
	bool operator!=(T a);    

	bool operator!=(_int &a);

	template<class T>
	friend bool operator!=(T a, const _int &b);

	bool operator==(_int &a);

	~_int();
}tmp;//临时数据;

_int::operator bool()
{
	if (length == 1 && s[0] == '0')return false;
	return true;
}

bool _int::cmp(const char *a, const char *b, int len)
{
	for (int i = len - 1; i >= 0; i--) {
		if (a[i] < b[i])return true;
		if (a[i] > b[i])return false;
	}
	return true;
}

template<class T>
const _int operator*(T a, _int _b)
{
	tmp = a;
	return tmp*_b;
}

template<class T>
bool _int::operator>(T a)
{
	tmp = a;
	return *this > tmp;
}

bool _int::operator<=(const _int &a)
{
	return !(a < *this);
}

template<class T>
bool operator>(T a, _int &b)
{
	tmp = a;
	return tmp > b;
}

template<class T>
bool operator<=(T a, const _int &b)
{
	tmp = a;
	return tmp <= b;
}

template<class T>
bool _int::operator>=(T a)
{
	tmp = a;
	return *this >= a;
}

template<class T>
bool _int::operator<=(T a)
{
	tmp = a;
	return tmp <= *this;
}

bool _int::operator>(const _int &a)
{
	if (a.length > length)return false;
	if (a.length < length)return true;
	for (int i = length - 1; i >= 0; i--) {
		if (a.s[i] > s[i])return false;
		else if (a.s[i] < s[i])return true;
	}
	return false; //完全相等
}

bool _int::operator<(const _int &a)
{
	if (a.length > length)return true;
	if (a.length < length)return false;
	for (int i = length - 1; i >= 0; i--) {
		if (a.s[i] > s[i])return true;
		else if (a.s[i] < s[i])return false;
	}
	return false;
}

template<class T>
bool operator<(T a,_int& b)
{
	tmp = a;
	return tmp < b;
}

bool _int::operator>=(const _int &a)
{
	return !(a > *this);
}

template<class T>
bool operator>=(T a, const _int &b)
{
	tmp = a;
	return a >= b;
}

template<class T>
bool _int::operator<(T a)
{
	tmp = a;
	return *this < tmp;
}

template<class T>
_int::_int(T _num) {
	*this = _num;
}

template<class T>
const _int _int::operator*(T a)
{
	return a*(*this);
}

void _int::operator-=(_int &a)
{
	*this = *this - a;
}

_int _int::operator ++(int)
{
	*this += 1;
	return *this - 1;
}

_int _int::operator--(int)
{
	*this -= 1;
	return *this + 1;
}

_int _int::operator--()
{
	*this -= 1;
	return *this;
}

void _int::operator*=(const _int &a)
{
	*this = *this*a;
}

_int _int::operator*(const _int &a)  //时间复杂度NlogN的大数乘法，假设相乘的两个数位数都是N;
{
	_int res;
	int len = 1;
	while (len < a.length + length + 1)len = len << 1;
	for (int i = 0; i < a.length; i++)x1[i] = cmplex((double)(a.s[i] - '0'), 0);
	for (int i = a.length; i < len; i++) x1[i] = cmplex(0, 0);
	fft(x1, len, 1);
	for (int i = 0; i < length; i++)x2[i] = cmplex((double)(s[i] - '0'), 0);
	for (int i = length; i < len; i++) x2[i] = cmplex(0, 0);
	fft(x2, len, 1);
	for (int i = 0; i < len; i++) x1[i] = x1[i] * x2[i];
	fft(x1, len, -1);
	for (int i = 0; i < len; i++) ans[i] = (int)(x1[i].r + 0.5);
	ans[len] = 0;
	for (int i = 1; i < len; i++) {
		ans[i] += ans[i - 1] / 10;
		ans[i - 1] %= 10;
	}
	while (len>0 && !ans[len]) len--;
	res.length = len + 1;
	for (int i = len; i >= 0; i--)res.s[i] = ans[i] + '0';
	if (a.sign && !sign || !a.sign&&sign)res.sign = true;
	return res;
}

_int _int::operator++()
{
	*this += 1;
	return *this;
}

const _int _int::operator-(_int a)
{
	a.sign = !a.sign;
	return *this + a;
}

template<class T>
void _int::operator-=(T a)
{
	*this = *this - a;
}

template<class T>
const _int operator-(T a, _int _b)
{
	tmp = a;
	return tmp - _b;
}

template<class T>
const _int _int::operator-(T a)
{
	a = -a;
	return *this + a;
}

bool _int::operator==(_int &a)
{
	return !(a != *this);
}

template<class T>
void _int::operator+=(T a)
{
	tmp = a;
	*this = tmp + *this;
}

template<class T>
const _int operator+(T a, _int _b)
{
	int cnt = 0, add = 0;
	T k = a;
	a = abs(a);
	if (k < 0 && _b.sign == true || k >= 0 && _b.sign == false) {
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
		tmp = k;     //将a升为_int 类型
		_b = tmp + _b;
	}
	return _b;
}

bool _int::operator!=(_int &a)
{
	if (a.length != length)return true;
	else for (int i = 0; i < a.length; i++) {
		if (a.s[i] != s[i])return true;
	}
	return false;
}

void _int::operator+=(_int &a) {
	*this = a + *this;
}

istream& operator>>(istream &is, _int &a)  //包含了处理eof模块，可以从输入流中读取位数不超过SIZE的大整数
{								  //能达到和平常cin基本一致的效果
	int cnt = 0;
	bool read = false;			//判断输入流是否到达结尾
	char k[SIZE], t = ' ';
	a.sign = false;   //默认为正
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
			//is.unget();
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
bool _int::operator!=(T a)
{
	return a != *this;
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

template<class T>
_int _int::operator/(T a)
{
	tmp = a;
	_int ans;

}

const _int _int::operator+(_int a)
{
	bool flag = false;
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
	else {
		if (a.length > length|| a.length == length&&!cmp(a.s,s,len)) {    //a>b
			for (int i = 0; i < len; i++) {
				char tmp = i < length ? s[i] : '0';
				if (a.s[i] - tmp + add >= 0) {
					a.s[i] = a.s[i] - tmp + add + '0';
					add = 0;
				}
				else {
					a.s[i] = a.s[i] - tmp + add + 10 + '0';
					add = -1;
				}
				if (!add&&i >= length)break;
			}
		}
		else {     //a<=b
			for (int i = 0; i < len; i++) {
				char tmp = i < a.length ? a.s[i] : '0';
				if (s[i] - tmp + add >= 0) {
					a.s[i] = s[i] - tmp + add + '0';
					add = 0;
				}
				else {
					a.s[i] = s[i] - tmp + add + 10 + '0';
					add = -1;
				}
				if (!add&&i >= length)break;
			}
			a.length = length;
			a.sign = sign;
		}
		for (int i = len - 1; i >= 0; i--) {
			if (a.s[i] == '0'&&i)a.length--;
			else break;
		}
		if (a.length == 1 && a.s[0] == '0')a.sign = false;
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
//long long a,b;
int main()
{
	while (cin>>a>>b) {
		memset(ans, 0, sizeof(ans));
		cout << a*b << endl;
	}
	//for (int i = 0; i < 10000; i++) {
	//	int d = rand() % 18 + 1;
	//	for (int i = 0; i < d; i++)printf("%d", rand() % 9 + 1);
	//	d = rand() % 18 + 1;
	//	printf(" ");
	//	for (int i = 0; i < d; i++)printf("%d", rand() % 9 + 1);
	//	printf("\n");
//	}
}