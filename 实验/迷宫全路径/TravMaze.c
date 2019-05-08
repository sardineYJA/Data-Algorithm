#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

/*
�Թ�ͼ
                    �յ�
 ___       ___       
| 4 |     | 5 |    | 7 |
|   |     |   |    |   |
|   -------   ------   |
|_3_______ 2   ______6_|   
         |    |
		 | 1  |
		 ���


6                    // ·�ڸ���
0 2 0                // ÿһ�б�ʾÿ��·�ڵ�������磺ֻ����·ȥ 2
3 5 6                // ��ȥ 3 �� ��ȥ 6 �� ��ȥ 5 
0 0 4
0 0 0
0 0 0
7 0 0
7                    // ����Ϊ·��7
*/

// ·�ڵĽṹ�嶨��
typedef struct
{
	int left;      // ������
	int forward;   // ��ǰ����
	int rigth;     // ���ҷ���
} InterSection;

// �Թ��Ľṹ�嶨��
typedef struct
{
	int mazeSize;           // ·�ڸ���
	InterSection *intSec;   // ·�ڼ���
	int Exit;               // ����
} Maze;


// �û����㷨�����Թ� m �����з�֧������ currSetValue Ϊ��ǰ������·��
// intSec[currSetValue] �����˵� currSetValue �е�������·���
int TravMaze(Maze *m, int currSetValue)
{
	// currSetValue > 0 ��ʾ·�����ڣ����Լ�����������һ��·��
	if (currSetValue > 0)
	{
		if (currSetValue == m->Exit)           // �ݹ����
		{
			printf("%d <== ", currSetValue);   // ���·�ں� 
			return 1;
		}

		else if (TravMaze(m, m->intSec[currSetValue].left) == 1)      // ����
		{
			// ֻ��̽���ɹ���������ֵΪ 1 ����ִ���������
			printf("%d <== ", currSetValue);                          // ���·�ں�
			return 1;
		}

		else if (TravMaze(m, m->intSec[currSetValue].forward) == 1)   // ��ǰ
		{
			// ֻ��̽���ɹ���������ֵΪ 1 ����ִ���������
			printf("%d <== ", currSetValue);                          // ���·�ں�
			return 1;
		}

		else if (TravMaze(m, m->intSec[currSetValue].rigth) == 1)     // ����
		{
			// ֻ��̽���ɹ���������ֵΪ 1 ����ִ���������
			printf("%d <== ", currSetValue);                          // ���·�ں�
			return 1;
		}
	}

	return 0;       // currSetValue = 0 ��ʾ��·�����ڣ�����0
}


// ���ļ� Filename �д�ŵ����ݴ����Թ� m
void CreateMaze(char *fileName, Maze *m)
{
	FILE *fp;
	int i;

	fp = fopen(fileName, "r");     // ֻ����ʽ���ļ�
	if (!fp)
	{
		printf("�����ļ��޷��򿪣�");
		return;
	}

	fscanf(fp, "%d", &m->mazeSize);    // ����·�ڸ���

	// ���� mazeSize + 1 ��Ԫ�ص�����        ΪëҪ�� 1 ������������������
	m->intSec = (InterSection *)malloc(sizeof(InterSection) * (m->mazeSize+1));

	for (i = 1; i <= m->mazeSize; i++)
	{
		// ����ȫ��·�ڵĽṹ����ֵ
		fscanf(fp, "%d%d%d", &m->intSec[i].left, &m->intSec[i].forward, &m->intSec[i].rigth);
	}

	fscanf(fp, "%d%d%d", &m->Exit);    // ���������ֵ

	fclose(fp); 
}


void maind()
{
	Maze m;
	int start = 1;
	CreateMaze("Maze.txt", &m);
	if (TravMaze(&m, start))
		printf("\n�Թ���һ��·��");
	else
		printf("\n��·");
}

