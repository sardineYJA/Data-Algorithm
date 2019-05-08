#include <malloc.h>
#include <stdio.h>

typedef int KeyType;
typedef struct 
{
	KeyType key;
} DataType;

/*
��ϣ�������ó����������������ϣ��ͻ�������ÿ��Ŷ�ַ������̽�鷨
*/

typedef enum
{
	Empty, Active, Deleted
} KindOfItem;          // ����״̬��ö������

typedef struct
{
	DataType data;     // ��������
	KindOfItem info;   // ״̬��Empty, Active, Deleted
} HashItem;            // ����ṹ��

typedef struct 
{
	HashItem * ht;     // ��ϣ������
	int tableSize;     // ����������
	int currentSize;   // ��ǰ�������
} HashTable;           // ��ϣ��ṹ��

// ��ʼ������
int Initate(HashTable * hash, int mSize) 
{
	hash->tableSize = mSize;
	hash->ht = (HashItem *)malloc(sizeof(HashItem) * mSize);
	if (hash->ht == NULL)
		return 0;
	else 
	{
		hash->currentSize = 0;
		return 1;
	}
}


/*
���Һ���
��������Ԫ��x�Ĺ�ϣ��ַ
�����ҳɹ����򷵻�ֵ���ڵ��� 0���䷵��ֵΪ����Ԫ��x �ڹ�ϣ���е�λ��
������ʧ�ܣ��򷵻�ֵС�� 0���䷵��ֵΪ����Ԫ��x �Ĺ�ϣ��ַ�ĸ�ֵ
*/
int Find(HashTable * hash, DataType x)
{
	int i = x.key % hash->tableSize;
	int j = i;

	// ˵���г�ͻ
	while (hash->ht[j].info == Active && hash->ht[j].data.key != x.key)
	{
		j = (j+1) % hash->tableSize;
		if (j == i)          // ˵���ѱ���������ϣ��δ�ҵ��ұ�����
			return -hash->tableSize;
	}

	if (hash->ht[j].info == Active)
		return j;         // �ҵ�������ֵ
	else
		return -j;        // δ�ҵ����ظ�ֵ
}

// ������Ԫ��x ���뵽��ϣ����
int Insert(HashTable * hash, DataType x) 
{
	int i = Find(hash, x);
	if (i >= 0)
		return 0;                    // ����Ԫ��x �Ѵ���
	else if (i != -hash->tableSize)  // ����Ԫ��x �������ҹ�ϣ��δ��
	{
		hash->ht[-i].data = x;
		hash->ht[-i].info = Active;
		hash->currentSize++;
		return 1;
	}
	else 
		return 0;
}

// ɾ����ϣ��hash������Ԫ��x
int Delete(HashTable * hash, DataType x) 
{
	int i = Find(hash, x);
	if (i >= 0) 
	{
		hash->ht[i].info = Deleted;
		hash->currentSize--;
		return 1;
	}
	else 
		return 0;
}


// �ͷ��ڴ�
void Destroy(HashTable * hash) 
{
	free(hash->ht);
}
