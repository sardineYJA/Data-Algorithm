#include <stdio.h>
__forceinline unsigned _int64 My_clock(void) 
{ 
	_asm    _emit 0x0F 
	_asm    _emit 0x31 
} 

unsigned _int64 Start(void) 
{ 
	return My_clock(); // 开始时间
}  


unsigned _int64 Stop(unsigned _int64 m_start, unsigned _int64 m_overhead) 
{
	return My_clock()-m_start - m_overhead; // 停时间
}  


void main()
{
	unsigned _int64 m_start = 0, m_overhead = 0; 
	unsigned int N;
	int a;
	m_start = My_clock(); 
	m_overhead = My_clock() - m_start - m_overhead;
	m_start = My_clock();// 正式开始
	
	
	//这里写你要计算耗时的程序段!!!!!!!!!!!!!!!!!!!!!!!!


	
	//测试程序段 End
	N = Stop(m_start,m_overhead); // 获取耗时.
	printf("Time：%I64d us\n", N);
}
