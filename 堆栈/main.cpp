#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MaxStackSize 100  // 顺序堆栈的最大元素个数
typedef char DataType;

#include "SeqStack.h"     // 顺序堆栈
#include "LinStack.h"     // 链式堆栈



////////////////////////////////////////////////////////
// 括号匹配问题
// exp[] 字符串， n 字符串长度
void ExpIsCorrect(char exp[], int n)
{
	SeqStack myStack;
	char c,i;

	StackInitiate(&myStack);  // 初始化

	for (i = 0; i < n; i++)
	{
		// 判断是否是左边括号，是就入栈
		if (exp[i] == '(' || exp[i] == '[' || exp[i] == '{')
		{
			StackPush(&myStack, exp[i]);        // 入栈
		}

		// 右括号匹配
		else if (exp[i] == ')' && StackNotEmpty(myStack) && StackTop(myStack, &c) && c == '(') 
		{
			StackPop(&myStack, &c);             // 匹配成功，出栈
		}
		else if (exp[i] == ')' && StackNotEmpty(myStack) && StackTop(myStack, &c) && c != '(') 
		{
			printf("左右匹配次序不正确！\n");             // 匹配失败
			return;
		}

		// 右括号匹配
		else if (exp[i] == ']' && StackNotEmpty(myStack) && StackTop(myStack, &c) && c == '[') 
		{
			StackPop(&myStack, &c);             // 匹配成功，出栈
		}
		else if (exp[i] == ']' && StackNotEmpty(myStack) && StackTop(myStack, &c) && c != '[') 
		{
			printf("左右匹配次序不正确！\n");             // 匹配失败
			return;
		}

		// 右括号匹配
		else if (exp[i] == '}' && StackNotEmpty(myStack) && StackTop(myStack, &c) && c == '{') 
		{
			StackPop(&myStack, &c);             // 匹配成功，出栈
		}
		else if (exp[i] == '}' && StackNotEmpty(myStack) && StackTop(myStack, &c) && c != '{') 
		{
			printf("左右匹配次序不正确！\n");             // 匹配失败
			return;
		}

		// 右括号匹配，但栈已空
		else if ((exp[i] == ')' || exp[i] == ']' || exp[i] == '}') && !StackNotEmpty(myStack))
		{
			printf("右括号多于左括号！\n");
			return;
		}
	}

	// 匹配完毕，栈不为空
	if (StackNotEmpty(myStack))
		printf("左括号多于右括号！\n");
		
	// 匹配完毕，栈为空
	else
		printf("左右括号匹配成功！\n");
}


//////////////////////////////////////////////////////////////////////
// 计算后缀表达式 str 的值, str字符串以#结尾
int PostExp(char str[])
{
	DataType x;
	DataType x1;
	DataType x2;

	LSNode *head;
	LStackInitiate(&head);    // 初始化链式堆栈

	for (int i = 0; str[i] != '#'; i++)
	{
		// isdigit检查参数是否为阿拉伯数字0到9
		if (isdigit(str[i]))
		{
			x = (int)(str[i] - 48);  // 转换int 
			LStackPush(head, x);     // 入栈
		}
		else
		{
			LStackPop(head, &x2);
			LStackPop(head, &x1);

			switch (str[i])
			{
			case'+':
				{
					x1 = x1 + x2;
					break;
				}

			case'-':
				{
					x1 = x1 - x2;
					break;
				}
			case'*':
				{
					x1 = x1 * x2;
					break;
				}

			case'/':
				{
					if (x2 == 0.0)
					{
						printf("除数为0！\n");
						exit(0);
					}
					else
					{
						x1 = x1 / x2;
						break;
					}
				}
			}
			LStackPush(head, x1);  //  运算结果入栈
		}
	}

	LStackPop(head, &x);          // 得到结果存于x中
	LStackDestroy(head);          // 撤销内存
	return x;

}


//////////////////////////////////////////////////////////////////////////////////////////

// 优先级
// a 栈顶的，b 当前扫描的
// 返回 0 则 a > b;   返回 1 则 a <= b 
int priority( char a, char b)
{
	if (a == '+' || a == '-')
	{
		if (b == '+' || b == '-' || b == ')' || b == '#')
			return 0;
		
		else if (b == '*' || b == '/' ||b == '(')
			return 1;
		
		return 0;
	}

	if (a == '*' || a == '/')
	{
		if (b == '+' || b == '-'|| b == '*' ||
			b == '/'  || b == ')' || b == '#')
			return 0;

		else if (b == '(')
			return 1;

		return 0;
	}

	// '(' 优先级最低
	if (a == '(')
		return 1;
	
	// ')' 优先级最高
	if (a == ')')
		return 0;

	// '#' 优先级最低
	if (a == '#')
		return 1;

	return 0;
}

// 中缀表达式转换后缀表达式
// p 输进的中缀表达式，post 输出的后缀表达式
void change(char *p, char *post)
{
  char c;                // 栈顶字符
  int j = 0;
  SeqStack myStack;            // 此堆栈用于保存字符 ( ) * / + - 

  StackInitiate(&myStack);     // 初始化顺序堆栈
  StackPush(&myStack, '#');    // 栈顶分界符 #

  while (*p != '\0')     // 字符串结束符\0
  {
    switch (*p)
	{
      case ' ': break;

      case '(': StackPush(&myStack,'(');          // ‘(’ 直接入栈
                break;

				// 将 ')' 之前的运算符  ”出栈“  赋给字符串
      case ')': while (StackPop(&myStack, &c) && c != '(')   
                      post[j++] = c;
                break;

      case '+':
      case '-':
      case '*':
      case '/': StackTop(myStack, &c);
				// 如果栈顶的优先级 c >= *p 当前扫描的运算符,则出栈 
                while (priority(c, *p) == 0) 
				{
					StackPop(&myStack, &c);        // 出栈
					post[j++] = c;                 // 将栈中的字符赋给字符串
					//post[j++] = ' ';
					StackTop(myStack, &c);         // 继续循环
                }

				// 如果当前扫描的运算符的优先级 c <= *p 栈顶的则入栈
                StackPush(&myStack, *p);
                break;

	  default: post[j++] = *p;  // 如果是数字则直接赋给 post 字符串
               post[j++] = ' ';
    }
    p++;
  }

  // 字符串 p 扫描完毕，将剩余的栈元素赋给 post 
  while (StackPop(&myStack, &c) && c != '#')
  {
    post[j++] = c;
	//post[j++] = ' ';
  }

  post[j] = '\0';  // post 字符串结束
}



//////////////////////////////////////////////////////////////
// 判断字符串是否为回文
// a[] 要判断的字符串，n-1 字符串长度-1，\0不要
int palindrome(char *a, int n)
{
	int i;
	char c;
	SeqStack myStack;

	// 初始化
	StackInitiate(&myStack);    

	// 入栈
	for (i = 0; i < n; i++)
	{
		StackPush(&myStack, a[i]);
	}

	i = 0;
	// 出栈并进行比较
	while (StackNotEmpty(myStack))
	{
		// 逐个出栈并与原来的字符比较
		StackPop(&myStack, &c);    
		if (c != a[i])
		{
			return 0;
		}
		i++;     // 下一个字符
	}
	return 1;
}

void main()
{
	// 回文问题
	char a[10] = "123454321";
	int m = strlen(a);
	if (palindrome(a, m) == 1)
	{
		printf("该字符串是回文\n");
	} else {
		printf("该字符串不是回文\n");
	}

	// 括号匹配问题
	char b[] = "()()(((} 990 )))";
	int n =  strlen(b);
	printf("\n括号匹配问题：");
	ExpIsCorrect(b, n);
	printf("\n");
	

	 // 中缀表达式转换成后缀表达式
	char str1[] = "(4-3)*(4+1)/5*2+8*(3/1+1)";
	char str2[100];
	change(str1, str2);
	printf("%s\n", str2);

	// 计算后缀表达式的结果
	char str[] = "43-41+*5/2*831/1+*+#";
	int result = PostExp(str);
	printf("后缀算术表达式结果：%d\n", result);
}

