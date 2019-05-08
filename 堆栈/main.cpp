#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MaxStackSize 100  // ˳���ջ�����Ԫ�ظ���
typedef char DataType;

#include "SeqStack.h"     // ˳���ջ
#include "LinStack.h"     // ��ʽ��ջ



////////////////////////////////////////////////////////
// ����ƥ������
// exp[] �ַ����� n �ַ�������
void ExpIsCorrect(char exp[], int n)
{
	SeqStack myStack;
	char c,i;

	StackInitiate(&myStack);  // ��ʼ��

	for (i = 0; i < n; i++)
	{
		// �ж��Ƿ���������ţ��Ǿ���ջ
		if (exp[i] == '(' || exp[i] == '[' || exp[i] == '{')
		{
			StackPush(&myStack, exp[i]);        // ��ջ
		}

		// ������ƥ��
		else if (exp[i] == ')' && StackNotEmpty(myStack) && StackTop(myStack, &c) && c == '(') 
		{
			StackPop(&myStack, &c);             // ƥ��ɹ�����ջ
		}
		else if (exp[i] == ')' && StackNotEmpty(myStack) && StackTop(myStack, &c) && c != '(') 
		{
			printf("����ƥ�������ȷ��\n");             // ƥ��ʧ��
			return;
		}

		// ������ƥ��
		else if (exp[i] == ']' && StackNotEmpty(myStack) && StackTop(myStack, &c) && c == '[') 
		{
			StackPop(&myStack, &c);             // ƥ��ɹ�����ջ
		}
		else if (exp[i] == ']' && StackNotEmpty(myStack) && StackTop(myStack, &c) && c != '[') 
		{
			printf("����ƥ�������ȷ��\n");             // ƥ��ʧ��
			return;
		}

		// ������ƥ��
		else if (exp[i] == '}' && StackNotEmpty(myStack) && StackTop(myStack, &c) && c == '{') 
		{
			StackPop(&myStack, &c);             // ƥ��ɹ�����ջ
		}
		else if (exp[i] == '}' && StackNotEmpty(myStack) && StackTop(myStack, &c) && c != '{') 
		{
			printf("����ƥ�������ȷ��\n");             // ƥ��ʧ��
			return;
		}

		// ������ƥ�䣬��ջ�ѿ�
		else if ((exp[i] == ')' || exp[i] == ']' || exp[i] == '}') && !StackNotEmpty(myStack))
		{
			printf("�����Ŷ��������ţ�\n");
			return;
		}
	}

	// ƥ����ϣ�ջ��Ϊ��
	if (StackNotEmpty(myStack))
		printf("�����Ŷ��������ţ�\n");
		
	// ƥ����ϣ�ջΪ��
	else
		printf("��������ƥ��ɹ���\n");
}


//////////////////////////////////////////////////////////////////////
// �����׺���ʽ str ��ֵ, str�ַ�����#��β
int PostExp(char str[])
{
	DataType x;
	DataType x1;
	DataType x2;

	LSNode *head;
	LStackInitiate(&head);    // ��ʼ����ʽ��ջ

	for (int i = 0; str[i] != '#'; i++)
	{
		// isdigit�������Ƿ�Ϊ����������0��9
		if (isdigit(str[i]))
		{
			x = (int)(str[i] - 48);  // ת��int 
			LStackPush(head, x);     // ��ջ
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
						printf("����Ϊ0��\n");
						exit(0);
					}
					else
					{
						x1 = x1 / x2;
						break;
					}
				}
			}
			LStackPush(head, x1);  //  ��������ջ
		}
	}

	LStackPop(head, &x);          // �õ��������x��
	LStackDestroy(head);          // �����ڴ�
	return x;

}


//////////////////////////////////////////////////////////////////////////////////////////

// ���ȼ�
// a ջ���ģ�b ��ǰɨ���
// ���� 0 �� a > b;   ���� 1 �� a <= b 
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

	// '(' ���ȼ����
	if (a == '(')
		return 1;
	
	// ')' ���ȼ����
	if (a == ')')
		return 0;

	// '#' ���ȼ����
	if (a == '#')
		return 1;

	return 0;
}

// ��׺���ʽת����׺���ʽ
// p �������׺���ʽ��post ����ĺ�׺���ʽ
void change(char *p, char *post)
{
  char c;                // ջ���ַ�
  int j = 0;
  SeqStack myStack;            // �˶�ջ���ڱ����ַ� ( ) * / + - 

  StackInitiate(&myStack);     // ��ʼ��˳���ջ
  StackPush(&myStack, '#');    // ջ���ֽ�� #

  while (*p != '\0')     // �ַ���������\0
  {
    switch (*p)
	{
      case ' ': break;

      case '(': StackPush(&myStack,'(');          // ��(�� ֱ����ջ
                break;

				// �� ')' ֮ǰ�������  ����ջ��  �����ַ���
      case ')': while (StackPop(&myStack, &c) && c != '(')   
                      post[j++] = c;
                break;

      case '+':
      case '-':
      case '*':
      case '/': StackTop(myStack, &c);
				// ���ջ�������ȼ� c >= *p ��ǰɨ��������,���ջ 
                while (priority(c, *p) == 0) 
				{
					StackPop(&myStack, &c);        // ��ջ
					post[j++] = c;                 // ��ջ�е��ַ������ַ���
					//post[j++] = ' ';
					StackTop(myStack, &c);         // ����ѭ��
                }

				// �����ǰɨ�������������ȼ� c <= *p ջ��������ջ
                StackPush(&myStack, *p);
                break;

	  default: post[j++] = *p;  // �����������ֱ�Ӹ��� post �ַ���
               post[j++] = ' ';
    }
    p++;
  }

  // �ַ��� p ɨ����ϣ���ʣ���ջԪ�ظ��� post 
  while (StackPop(&myStack, &c) && c != '#')
  {
    post[j++] = c;
	//post[j++] = ' ';
  }

  post[j] = '\0';  // post �ַ�������
}



//////////////////////////////////////////////////////////////
// �ж��ַ����Ƿ�Ϊ����
// a[] Ҫ�жϵ��ַ�����n-1 �ַ�������-1��\0��Ҫ
int palindrome(char *a, int n)
{
	int i;
	char c;
	SeqStack myStack;

	// ��ʼ��
	StackInitiate(&myStack);    

	// ��ջ
	for (i = 0; i < n; i++)
	{
		StackPush(&myStack, a[i]);
	}

	i = 0;
	// ��ջ�����бȽ�
	while (StackNotEmpty(myStack))
	{
		// �����ջ����ԭ�����ַ��Ƚ�
		StackPop(&myStack, &c);    
		if (c != a[i])
		{
			return 0;
		}
		i++;     // ��һ���ַ�
	}
	return 1;
}

void main()
{
	// ��������
	char a[10] = "123454321";
	int m = strlen(a);
	if (palindrome(a, m) == 1)
	{
		printf("���ַ����ǻ���\n");
	} else {
		printf("���ַ������ǻ���\n");
	}

	// ����ƥ������
	char b[] = "()()(((} 990 )))";
	int n =  strlen(b);
	printf("\n����ƥ�����⣺");
	ExpIsCorrect(b, n);
	printf("\n");
	

	 // ��׺���ʽת���ɺ�׺���ʽ
	char str1[] = "(4-3)*(4+1)/5*2+8*(3/1+1)";
	char str2[100];
	change(str1, str2);
	printf("%s\n", str2);

	// �����׺���ʽ�Ľ��
	char str[] = "43-41+*5/2*831/1+*+#";
	int result = PostExp(str);
	printf("��׺�������ʽ�����%d\n", result);
}

