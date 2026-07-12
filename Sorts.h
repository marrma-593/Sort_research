#pragma once

#include<iostream>
#include<vector>
#include<algorithm>
#define ll long long
#define Asn(a, b) Asn_with_cnt(a, b, asn_cnt)
#define Cmp(a, b) Cmp_with_cnt(a, b, cmp_cnt)
#define Cmp2(a, b) Cmp_with_cnt2(a, b, cmp_cnt)
#define Excg(a, b) Excg_with_cnt(a, b, asn_cnt)
using namespace std;

double gettime(int restart=0);

template <typename T> void GetMemory(T *&data, T *&data0, int n)	// 分配堆内存空间，通过参数"返回"首地址
{																	// 隐含约定：指针非空就表示指针"拥有"堆空间资源
	if(data0!=NULL) delete [] data0;								// 先释放原先所"拥有"的堆空间资源
	if(data !=NULL) delete [] data;
	data0 = new T[n];												// 重新申请新的（容量符合要求的）堆空间资源
	data = new T[n];
}

template <typename T> void FreeMemory(T *&data, T *&data0)			// 释放指针所"拥有"的堆空间资源
{
	if(data0!=NULL) delete [] data0;
	if(data !=NULL) delete [] data;
	data0 = data = NULL;											// 这一条赋值语句非常重要！保持"隐含约定"
}

//恢复为原始数据
template <typename T> void ReSet(T *data, const T *data0, int n)	// 用于恢复"原始数据"，以保证不同的排序算法处理完全相同的数据
{
	for(int i=0; i<n; i++)
		data[i] = data0[i];
}

//检查是否排序成功（升序）
template <typename T> bool Check(const T *a, int size)				// 检验数组元素是否已按升序排列
{
	for(int i=1; i<size; i++)
		if(a[i-1] > a[i])
			return false;
	return true;
}


//重置计数器
inline void Reset_counters(ll &cmp_cnt, ll &asn_cnt){
	cmp_cnt = 0;
	asn_cnt = 0;
}

//带有计数的比较（大于）
template <typename T> inline bool Cmp_with_cnt(const T a, const T b, ll &cmp_cnt){
	cmp_cnt++;
	return a > b;
}

//带有计数的比较(大于等于)
template <typename T> inline bool Cmp_with_cnt2(const T a, const T b, ll &cmp_cnt){
	cmp_cnt++;
	return a >= b;
}

//带有计数的赋值
template <typename T> inline void Asn_with_cnt(T &a, T &b, ll &asn_cnt){
	asn_cnt++;
	a = b;
}

//带有计数的交换变量的值
template <typename T> inline void Excg_with_cnt(T &a, T &b, ll &asn_cnt){
	T temp;
	Asn_with_cnt(temp, a, asn_cnt);
	Asn_with_cnt(a, b, asn_cnt);
	Asn_with_cnt(b, temp, asn_cnt);
}



// 冒泡排序
template <typename T> void Bubble(T *a, int size, ll &cmp_cnt, ll &asn_cnt)	
{
	T temp;											// 定义一个局部变量，数据类型与形式数据类型相同
	int i, j;
	for(i=1; i<size; i++)							// 共进行 size-1 轮比较和交换
	{
		for(j=0; j<size-i; j++)
		{
			if(Cmp(a[j], a[j+1]))						// 相邻元素之间比较，必要时
			{
				Excg(a[j], a[j + 1]);
			}
		}
	}
}

// 选择排序
template <typename T> void Select(T *a, int size, ll &cmp_cnt, ll &asn_cnt)	
{
	T temp;
	int i, j, k=0;
	for(i=1; i<size; i++)							// 循环size-1次
	{
		for(j=i; j<size; j++)
			if(Cmp(a[k], a[j]))
				k = j;								// 找出当前范围内"最小"元素的下标
		if(k!=i-1)									// 若"最小"元素不是a[i-1]，则交换之
		{					
			Excg(a[k], a[i -  1]); // 交换 a[j] 与 a[j+1]
		}
		k = i;
	}
}

// 快速排序
template <typename T> void Qsort(T *a, int size, ll &cmp_cnt, ll &asn_cnt)	
{
	T pivot, temp;
	int left=0, right=size-1;						// 下标（整数）

	if(size<=1) return;

	pivot = a[right];								// 选择最后一个值为分界值
	do
	{
		while(left<right && Cmp2(pivot, a[left])) left++;	// 此处 "<=" 是让与分界值相等的元素暂时留在原地
		while(left<right && Cmp2(a[right], pivot)) right--;// 此处 ">=" 是让与分界值相等的元素暂时留在原地
		if(left < right)
		{						
			Excg(a[left], a[right]);          // 交换 a[j] 与 a[j+1]
		}
	}while(left < right);
	Asn(a[size-1], a[left]);
	Asn(a[left], pivot);			// 找到分界点 left
	Qsort(a, left, cmp_cnt, asn_cnt);									// 递归调用(左侧部分)
	Qsort(a+left+1, size-left-1, cmp_cnt, asn_cnt);					// 递归调用(右侧部分)
}

//插入排序
template <typename T> void Insertionsort(T *a, int size, ll &cmp_cnt, ll &asn_cnt){    
	for(int i = 1; i < size; i++){
		T key;
		Asn(key, a[i]);
		int j = i - 1;
		while(j >= 0 && Cmp(key, a[j])){   //a[j] < key
			Asn(a[j + 1], a[j]);
			j--;
		}
		Asn(a[j + 1], key);
	}
}

//希尔排序
template <typename T> void ShellSort(T *a, int size, ll &cmp_cnt, ll &asn_cnt) {
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            T temp;
            Asn(temp, a[i]); 
            
            int j = i;
            while (j >= gap && Cmp(a[j - gap], temp)) {
                Asn(a[j], a[j - gap]);
                j -= gap;
            }
            Asn(a[j], temp); 
        }
    }
}

//桶排序
template <typename T> void Bucketsort(T *a, int size, ll &cmp_cnt, ll &asn_cnt){
	int root = 0;
	int min_idx = root;
    int max_idx = root;

    for (int i = 1; i < size; ++i) {
        if (Cmp(a[min_idx], a[root + i])) {
            min_idx = root + i;
        }
        if (Cmp(a[root + i], a[max_idx])) {
            max_idx = root + i;
        }
    }

    int bucket_count = size/100;
    vector<vector<T>> buckets(bucket_count);

    double range = static_cast<double>(a[max_idx] - a[min_idx]);
    for (int i = 0; i < size; ++i) {
        double diff = static_cast<double>(a[root + i] - a[min_idx]);
        int b_idx = static_cast<int>((diff / range) * (bucket_count - 1));
        
        if (b_idx >= bucket_count) b_idx = bucket_count - 1;
        
        buckets[b_idx].push_back(a[root + i]);
    }

    int current = 0;
    for (int i = 0; i < bucket_count; ++i) {
        for (size_t j = 0; j < buckets[i].size(); ++j) {
            Asn(a[root + current], buckets[i][j]);
            current++;
        }
    }

    for (int i = 1; i < size; ++i) {
        for (int j = i; j > 0; --j) {
            if (Cmp(a[root + j - 1], a[root + j])) {
                Excg(a[root + j - 1], a[root + j]);
            } else {
                break;
            }
        }
    }
}
