#include <malloc.h>
#include <stdio.h>

typedef int KeyType;
typedef struct 
{
	KeyType key;
} DataType;

/*
哈希函数采用除留余数法，解决哈希冲突方法采用开放定址的线性探查法
*/

typedef enum
{
	Empty, Active, Deleted
} KindOfItem;          // 表项状态的枚举类型

typedef struct
{
	DataType data;     // 储存数据
	KindOfItem info;   // 状态：Empty, Active, Deleted
} HashItem;            // 表项结构体

typedef struct 
{
	HashItem * ht;     // 哈希表数组
	int tableSize;     // 数组最大个数
	int currentSize;   // 当前表项个数
} HashTable;           // 哈希表结构体

// 初始化函数
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
查找函数
返回数据元素x的哈希地址
若查找成功，则返回值大于等于 0，其返回值为数据元素x 在哈希表中的位置
若查找失败，则返回值小于 0，其返回值为数据元素x 的哈希地址的负值
*/
int Find(HashTable * hash, DataType x)
{
	int i = x.key % hash->tableSize;
	int j = i;

	// 说明有冲突
	while (hash->ht[j].info == Active && hash->ht[j].data.key != x.key)
	{
		j = (j+1) % hash->tableSize;
		if (j == i)          // 说明已遍历整个哈希表未找到且表已满
			return -hash->tableSize;
	}

	if (hash->ht[j].info == Active)
		return j;         // 找到返回正值
	else
		return -j;        // 未找到返回负值
}

// 将数据元素x 插入到哈希表中
int Insert(HashTable * hash, DataType x) 
{
	int i = Find(hash, x);
	if (i >= 0)
		return 0;                    // 数据元素x 已存在
	else if (i != -hash->tableSize)  // 数据元素x 不存在且哈希表未满
	{
		hash->ht[-i].data = x;
		hash->ht[-i].info = Active;
		hash->currentSize++;
		return 1;
	}
	else 
		return 0;
}

// 删除哈希表hash的数据元素x
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


// 释放内存
void Destroy(HashTable * hash) 
{
	free(hash->ht);
}
