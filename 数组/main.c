#include <stdio.h>
#include <malloc.h>

// ��̬����

// ��ά��̬����
int **Make2DArray(int row, int col)
{
	int **a;
	int i;

	// ��̬���� row �� int ָ�����͵��ڴ�ռ�
	a = (int **)calloc(row, sizeof(int *));

	// ѭ�� row �Σ���̬���� col ��int ���͵��ڴ�ռ�
	for (i = 0; i < row; i++)
	{
		a[i] = (int *)calloc(col, sizeof(int));
	}
	return a;
}

// �ͷ��ڴ�
void Deliver2DArray(int **a, int row)
{
	int i;
	for (i = 0; i < row; i++)
		free(a[i]);       // ��������ͷ�a[i]

	free(a);
}

void main()
{

}




