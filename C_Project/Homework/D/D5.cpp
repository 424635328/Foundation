/*假设以I和O分别表示入栈和出战操作，栈的初始和终态均为空，入栈和出战的操作序列可表示为仅有I和O组成的序列
判断下面哪些是合法的序列？并写出算法，判断所给的操作序列是否为合法序列。序列可以用字符串表示。
A. IOIIOIOO   B.IOOIOIIO   *C. IIIOIOIO   D. IIIOOIOO*/
#include <stdio.h>
#include <string.h>

void Judge(char *arr, char *s)
{

	if (!arr || strlen(arr) == 0)
	{
		printf("输入为空或无效\n");
		return;
	}
	int m = 0;		 // 初始化栈计数
	int isValid = 1; // 标记是否合法

	for (int i = 0; i < strlen(arr); i++)
	{ // 在任何时刻，出栈数不会大于入栈数
		if (arr[i] == 'I')
		{
			m++;
		}
		else if (arr[i] == 'O')
		{
			m--;
			if (m < 0)
			{ // 如果出栈数大于入栈数，标记为不合法
				isValid = 0;
				break; // 不需要继续检查，直接退出循环
			}
		}
	}

	if (isValid && m == 0)
	{ // 终态时m为0
		printf("%c 合法\n", (*s)++);
	}
	else
	{
		printf("%c 不合法\n", (*s)++);
	}
}

int main()
{
	char s = 'A';
	char A[] = "IOIIOIOO";
	char B[] = "IOOIOIIO";
	char C[] = "IIIOIOIO";
	char D[] = "IIIOOIOO";
	Judge(A, &s);
	Judge(B, &s);
	Judge(C, &s);
	Judge(D, &s);
	return 0;
}