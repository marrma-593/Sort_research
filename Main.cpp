// Main.cpp
#include <iostream>
#include <typeinfo>
#include <cstdlib>
#include <ctime>
#define ll long long
#include "Sorts.h"
#include "Score.h"
#include "MyRand.h"
using namespace std;

double gettime(int restart)					// 参数带默认值，非零表示重新计时
{											// 否则累计计时
	const double c = 1.0/CLOCKS_PER_SEC;
	static clock_t t = clock();				// 静态局部变量。第一次调用时，确定计时起点
	if(restart) t = clock();				// 根据实参决定是否重新确定计时起点
	return c*(clock()-t);					// 从上一计时点到现在所经历的时间
}

template <typename T> void InitData(T *data, int n, int flag)
{
	int i;
	switch(flag)
	{
	case 0: for(i=0; i<n; i++) data[i] = n-1-i;				break;	// 逆序（从大到小）
	case 1:	 for(i=0; i<n; i++) data[i] = i;					break;	// 顺序（从小到大）
	case 2:  for(i=0; i<n; i++) data[i] = (T)UniformRand(54,90);break;	// [54,90]上的均匀分布
	case 3: for(i=0; i<n; i++) data[i] = (T)GaussRand(72, 6*6);break;	// 正态分布，均值72，方差36（根方差6）
	}
}

template <typename T> void Test(const T &x)					// 调用本函数的实参的值不重要，重要的是实参的数据类型
{
	T *data0=NULL, *data=NULL;								// 两个指针初始化为NULL非常重要！
	char InitConf[][20] = {"完全逆序", "完全顺序", "均匀分布", "正态分布"};	// C-字符串数组
	char algo[][20] 	= {"冒泡排序", "选择排序", "快速排序", "插入排序", "希尔排序", "桶排序"};  // C-字符串数组
	void (*f[])(T*, int, ll&, ll&) = {Bubble<T>, Select<T>, Qsort<T>, Insertionsort<T>, ShellSort<T>, Bucketsort<T>};
	// j为数据分布设置 n为数据规模 m为函数指针数组f的元素个数
	int i, j, n, m = sizeof(f)/sizeof(*f);
	bool flag[20];											// 这里认为：常量20足够大于变量 m。记录不同算法执行的正确性
	double t[20];											// 同上。记录不同算法的执行时间
	ll cmp[20];
	ll asn[20];
	ll cmp_cnt = 0, asn_cnt = 0;

	for(j = 0; j <= 3; j++)									// 数据分布类型
	{
		cout << fixed << "\n数据类型: " << typeid(T).name() << " (" << InitConf[j] << ")" << endl;
		for(i = 0; i < m; i++)
			cout << '\t' << algo[i];	
		cout << endl;

		for(n=1024; n<=262144; n*=2)
		{
			GetMemory(data, data0, n);						// 申请分配堆空间
			InitData(data0, n, j);							// 设置原始数据
			cout << n;
			for(i=0; i<m; i++)
			{
				if((n>=32768 && i == 2) || (n>=32768 && i == 0)){
					t[i] = -1;
					flag[i] = -1;
					cmp[i] = -1;
					asn[i] = -1;

				}else{
					Reset_counters(cmp_cnt, asn_cnt);
					ReSet(data, data0, n);						// 恢复原始数据
					gettime(1);									// 设置计时起点
					f[i](data, n, cmp_cnt, asn_cnt);			// 第 i 种排序算法
					t[i] = gettime();							// 返回从计时起点到目前所经历的时间（秒）
					cmp[i] = cmp_cnt;
					asn[i] = asn_cnt;
					
					flag[i] = Check(data, n);					// 检验排序的正确性
				}
				cout << "\t" << t[i];

			}

			for(i=0; i<m; i++)
				cout << "\t" << cmp[i];
			for(i=0; i<m; i++)
				cout << "\t" << asn[i];
			
			for(i=0; i<m; i++)				
				if (flag[i]) cout << "\t" << "正确";
				else cout << "\t" << "错误";

			cout << endl;
			FreeMemory(data, data0);						// 释放堆空间资源，并使指针为空
		}
	}
}

int main()						// 主函数
{
	void TestString();			// 函数原型，用于声明
	srand(time(NULL));			// 设置随机数发生器的种子
	
	Test(int(0));				// 测试int类型数据
	Test(double(0));			// 测试double类型数据
	TestScore();				// 测试Score类型数据
	TestString();				// 测试C-字符串数组排序（多种存储方式）
	return 0;
}
