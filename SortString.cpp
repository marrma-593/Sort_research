// SortString.cpp
/* 思考题
1.	下面的测试函数中，strA、strB、strC、strD联系的C-字符串数组的内容存储在内存的什么区域？
2.	设计BubbleA，BubbleB两个函数之前，思考
	(1) 如何比较两个字符串的内容？
	(2) 存储在什么区域的字符串能交换其内容？
	(3) 若不能交换字符串的内容，排序操作中交换什么？
3.	GetStrings为什么要设计成函数模板，两次调用时，其第二个参数分别是实例化成什么？
4.	GetStrings和FreeStrings函数的第一个参数为什么要使用引用型参数传递二级指针？如果不用引用型参数，会有什么结果？
*/
#include <iostream>
#include <cstring>
#define ll long long
using namespace std;
#define BubbleA(a, b) BubbleA_with_cnt(a, b, cmp_cnt, asn_cnt)
#define BubbleB(a, b) BubbleB_with_cnt(a, b, cmp_cnt, asn_cnt)

#include "Sorts.h"

#define NUM 20

void BubbleA_with_cnt(char (*str)[NUM], int size, ll &cmp_cnt, ll &asn_cnt)			// 数组指针
{
	char temp[NUM];
	for(int i = 1; i < size; i++){
		for(int j = 0; j < size - i; j++){
			if(strcmp(str[j], str[j + 1]) > 0){
				strcpy(temp, str[j]);
				strcpy(str[j], str[j + 1]);
				strcpy(str[j + 1], temp);
				asn_cnt += 3;
			}
			cmp_cnt++;
		}
	}
}

void BubbleB_with_cnt(char *str[], int size, ll &cmp_cnt, ll &asn_cnt)					// 指针数组
{
	char *temp;
	for(int i = 1; i < size; i++){
		for(int j = 0; j < size - i; j++){
			if(strcmp(str[j], str[j + 1]) > 0){
				temp = str[j];
				str[j] = str[j + 1];
				str[j + 1] = temp;
				asn_cnt += 3;
			}
			cmp_cnt++;
		}
	}	
}

template <typename T> void ShowStrings(const char *prompt, const T *strs, int n)
{
	if(n>0)
		cout << prompt << strs[0];
	for(int i=1; i<n; i++)
		cout << ", " << strs[i];
	cout << endl;
}

template <typename T> void GetStrings(char **&dest, const T *source, int n)
{
	dest = new char*[n];
	if(dest == NULL) return;
	int len;
	for(int i=0; i<n; i++)
	{
		len = strlen(source[i]);
		dest[i] = new char[len+1];
		strcpy(dest[i], source[i]);
	}
}

void FreeStrings(char **&strs, int n)
{
	if(strs!=NULL)
	{
		for(int i=0; i<n; i++)
			if(strs[i]!=NULL)
				delete [] strs[i];
		delete [] strs;
		strs = NULL;
	}
}

void TestString()
{
	const char *orig[] = {
    "beautiful", "character", "dangerous", "education", "fantastic", "generous",
    "happiness", "important", "knowledge", "liberation", "magnificent", "necessary",
    "opportunity", "particular", "qualification", "remarkable", "satisfactory", "tremendous",
    "understanding", "valuable", "wonderful", "yesterday", "absolutely", "additional",
    "agreement", "ambitious", "announcement", "appearance", "arrangement", "association",
    "atmosphere", "attraction", "authority", "beginning", "belonging", "beneficial",
    "boundaries", "brilliant", "businessman", "capability", "carefully", "certainty",
    "challenge", "characteristic", "circumstance", "collection", "comfortable", "commandment",
    "commitment", "communication", "companion", "comparison", "competition", "completely",
    "conclusion", "condition", "connection", "conscious", "consequence", "conservation",
    "consider", "consistent", "constitution", "construction", 
	"beautiful", "character", "dangerous", "education", "fantastic", "generous",
    "happiness", "important", "knowledge", "liberation", "magnificent", "necessary",
    "opportunity", "particular", "qualification", "remarkable", "satisfactory", "tremendous",
    "understanding", "valuable", "wonderful", "yesterday", "absolutely", "additional",
    "agreement", "ambitious", "announcement", "appearance", "arrangement", "association",
    "atmosphere", "attraction", "authority", "beginning", "belonging", "beneficial",
    "boundaries", "brilliant", "businessman", "capability", "carefully", "certainty",
    "challenge", "characteristic", "circumstance", "collection", "comfortable", "commandment",
    "commitment", "communication", "companion", "comparison", "competition", "completely",
    "conclusion", "condition", "connection", "conscious", "consequence", "conservation",
    "consider", "consistent", "constitution", "construction",
	"beautiful", "character", "dangerous", "education", "fantastic", "generous",
    "happiness", "important", "knowledge", "liberation", "magnificent", "necessary",
    "opportunity", "particular", "qualification", "remarkable", "satisfactory", "tremendous",
    "understanding", "valuable", "wonderful", "yesterday", "absolutely", "additional",
    "agreement", "ambitious", "announcement", "appearance", "arrangement", "association",
    "atmosphere", "attraction", "authority", "beginning", "belonging", "beneficial",
    "boundaries", "brilliant", "businessman", "capability", "carefully", "certainty",
    "challenge", "characteristic", "circumstance", "collection", "comfortable", "commandment",
    "commitment", "communication", "companion", "comparison", "competition", "completely",
    "conclusion", "condition", "connection", "conscious", "consequence", "conservation",
    "consider", "consistent", "constitution", "construction",
	"beautiful", "character", "dangerous", "education", "fantastic", "generous",
    "happiness", "important", "knowledge", "liberation", "magnificent", "necessary",
    "opportunity", "particular", "qualification", "remarkable", "satisfactory", "tremendous",
    "understanding", "valuable", "wonderful", "yesterday", "absolutely", "additional",
    "agreement", "ambitious", "announcement", "appearance", "arrangement", "association",
    "atmosphere", "attraction", "authority", "beginning", "belonging", "beneficial",
    "boundaries", "brilliant", "businessman", "capability", "carefully", "certainty",
    "challenge", "characteristic", "circumstance", "collection", "comfortable", "commandment",
    "commitment", "communication", "companion", "comparison", "competition", "completely",
    "conclusion", "condition", "connection", "conscious", "consequence", "conservation",
    "consider", "consistent", "constitution", "construction"
};

	char strA[sizeof(orig)/sizeof(*orig)][NUM];
	char *strB[sizeof(orig)/sizeof(*orig)];
	char **strC = NULL, **strD = NULL;

	ll asn_cnt = 0, cmp_cnt = 0;
	int n1 = sizeof(strA)/sizeof(*strA), n2 = sizeof(strB)/sizeof(*strB);

	cout << "\n\t*** 多种不同存储方式的C-字符串数组的排序 ***" << endl;
	cout << fixed << "type time cmp_cnt asn_cnt" << endl;

	const char *labels[] = {"StrA", "StrB", "StrC", "StrD"};

	for (int i = 0; i < 4; i++){
		for (int j = 0; j < n1; j++)
			strcpy(strA[j], orig[j]);
		for (int j = 0; j < n2; j++)
			strB[j] = (char *)orig[j];
		FreeStrings(strC, n1);
		FreeStrings(strD, n2);
		GetStrings(strC, strA, n1);
		GetStrings(strD, strB, n2);

		gettime(1);
		switch (i)		{
		case 0: BubbleA(strA, n1); break;
		case 1: BubbleB(strB, n2); break;
		case 2: BubbleB(strC, n1); break;
		case 3: BubbleB(strD, n2); break;
		}
		cout << labels[i] << " " << gettime() << " " << cmp_cnt << " " << asn_cnt << endl;
		Reset_counters(cmp_cnt, asn_cnt);
	}

	FreeStrings(strC, n1);
	FreeStrings(strD, n2);
}
