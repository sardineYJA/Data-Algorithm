// 串的顺序存储结构的动态数组

typedef struct
{
	char *str;       // 动态数组的首地址
	int maxLength;   // 动态数组字符的最大个数
	int length;      // 串的当前长度
}DString;


// 初始化
void Initiate(DString *S, int max, char *string)
{
	int i; 
	S->str = (char *)malloc(sizeof(char) * max);    // 申请动态空间
	S->maxLength = max;                             // 动态数组最大个数
	S->length = strlen(string);                     // 串的当前长度值
	for (i = 0; i < S->length; i++)
		S->str[i] = string[i];      // 赋值
}


// 在主串 S 中插入子串 T
int Insert(DString *S, int pos, DString T)
{
	int i;
	if (pos < 0)
	{
		printf("参数 pos 有错！\n");
		return 0;
	}
	else 
	{
		if (S->length + T.length > S->maxLength)
		{
			// 重新申请

			// realloc（p, size）将 p 所指的已分配内存的大小改为 size，在新分配内存中保持原内存的数据值 
			realloc(S->str, (S->length + T.length) * sizeof(char));
			S->maxLength = S->length + T.length;
		}

		for (i = S->length - 1; i >= pos; i--)
		{
			S->str[i + T.length] = S->str[i];    // pos 后面的字符从 S 的最后一个开始，依次后移T.length	
		}

		for (i = 0; i < T.length; i++)
		{
			S->str[pos + i] = T.str[i];         // 从 pos 位置开始插入
		}

		S->length = S->length + T.length;       // 数据元素个数
		return 1;
	}
}


// 删除主串 S 从 pos 位置开始的长度为 len 的子串，成功返回 1 , 失败返回 0
int Delete(DString *S, int pos, int len)
{
	int i;
	if (S->length <= 0)
	{
		printf("数组中未存放字符！\n");
		return 0;
	}
	else if (pos < 0 || len < 0 || pos + len > S->length)
	{
		printf("参数 pos 和 len 不合法！\n");
		return 0;
	}
	else
	{
		for (i = pos + len; i <= S->length - 1; i++)
		{
			S->str[i -len] = S->str[i];       // 从 pos + len 后的第一个字符依次前移 len 
		}
		S->length = S->length - len;
		return 1;
	}
}


// 取主串 S 从位置 pos 位置开始的长度为 len 的子串 ，由 T 传出
int SubString(DString *S, int pos, int len, DString *T)
{
	int i;
	if (pos < 0 || len < 0 || pos + len > S->length)
	{
		printf("参数 pos 和 len 不合法！\n");
		return 0;
	}

	if (len > T->maxLength)
	{
		// 重新申请
		T->str = (char *)malloc(len * sizeof(char));
		T->maxLength = len;
	}

	for (i = 0; i < len; i++)
	{
		T->str[i] = S->str[pos + i];
	}

	T->length = len;
	return 1;
}


// 释放内存 
void Destroy(DString *S)
{
	free(S->str);
	S->maxLength = 0;
	S->length = 0;
}

