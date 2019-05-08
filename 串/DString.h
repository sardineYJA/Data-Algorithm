// ����˳��洢�ṹ�Ķ�̬����

typedef struct
{
	char *str;       // ��̬������׵�ַ
	int maxLength;   // ��̬�����ַ���������
	int length;      // ���ĵ�ǰ����
}DString;


// ��ʼ��
void Initiate(DString *S, int max, char *string)
{
	int i; 
	S->str = (char *)malloc(sizeof(char) * max);    // ���붯̬�ռ�
	S->maxLength = max;                             // ��̬����������
	S->length = strlen(string);                     // ���ĵ�ǰ����ֵ
	for (i = 0; i < S->length; i++)
		S->str[i] = string[i];      // ��ֵ
}


// ������ S �в����Ӵ� T
int Insert(DString *S, int pos, DString T)
{
	int i;
	if (pos < 0)
	{
		printf("���� pos �д�\n");
		return 0;
	}
	else 
	{
		if (S->length + T.length > S->maxLength)
		{
			// ��������

			// realloc��p, size���� p ��ָ���ѷ����ڴ�Ĵ�С��Ϊ size�����·����ڴ��б���ԭ�ڴ������ֵ 
			realloc(S->str, (S->length + T.length) * sizeof(char));
			S->maxLength = S->length + T.length;
		}

		for (i = S->length - 1; i >= pos; i--)
		{
			S->str[i + T.length] = S->str[i];    // pos ������ַ��� S �����һ����ʼ�����κ���T.length	
		}

		for (i = 0; i < T.length; i++)
		{
			S->str[pos + i] = T.str[i];         // �� pos λ�ÿ�ʼ����
		}

		S->length = S->length + T.length;       // ����Ԫ�ظ���
		return 1;
	}
}


// ɾ������ S �� pos λ�ÿ�ʼ�ĳ���Ϊ len ���Ӵ����ɹ����� 1 , ʧ�ܷ��� 0
int Delete(DString *S, int pos, int len)
{
	int i;
	if (S->length <= 0)
	{
		printf("������δ����ַ���\n");
		return 0;
	}
	else if (pos < 0 || len < 0 || pos + len > S->length)
	{
		printf("���� pos �� len ���Ϸ���\n");
		return 0;
	}
	else
	{
		for (i = pos + len; i <= S->length - 1; i++)
		{
			S->str[i -len] = S->str[i];       // �� pos + len ��ĵ�һ���ַ�����ǰ�� len 
		}
		S->length = S->length - len;
		return 1;
	}
}


// ȡ���� S ��λ�� pos λ�ÿ�ʼ�ĳ���Ϊ len ���Ӵ� ���� T ����
int SubString(DString *S, int pos, int len, DString *T)
{
	int i;
	if (pos < 0 || len < 0 || pos + len > S->length)
	{
		printf("���� pos �� len ���Ϸ���\n");
		return 0;
	}

	if (len > T->maxLength)
	{
		// ��������
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


// �ͷ��ڴ� 
void Destroy(DString *S)
{
	free(S->str);
	S->maxLength = 0;
	S->length = 0;
}

