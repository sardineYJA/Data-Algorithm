#include <stdio.h>
__forceinline unsigned _int64 My_clock(void) 
{ 
	_asm    _emit 0x0F 
	_asm    _emit 0x31 
} 

unsigned _int64 Start(void) 
{ 
	return My_clock(); // ��ʼʱ��
}  


unsigned _int64 Stop(unsigned _int64 m_start, unsigned _int64 m_overhead) 
{
	return My_clock()-m_start - m_overhead; // ͣʱ��
}  


void main()
{
	unsigned _int64 m_start = 0, m_overhead = 0; 
	unsigned int N;
	int a;
	m_start = My_clock(); 
	m_overhead = My_clock() - m_start - m_overhead;
	m_start = My_clock();// ��ʽ��ʼ
	
	
	//����д��Ҫ�����ʱ�ĳ����!!!!!!!!!!!!!!!!!!!!!!!!


	
	//���Գ���� End
	N = Stop(m_start,m_overhead); // ��ȡ��ʱ.
	printf("Time��%I64d us\n", N);
}
