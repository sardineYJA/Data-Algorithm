
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>


///////////////////////////////////////////////////////////////////////////////////
/*
某一行的皇后a[n]不能和之前的皇后a[i]位置有冲突，约束条件为：

// 当成二位数组， a[n]即 n 是第几行也是一位数组的，数组值就是列号
实际：a[n] 是一维数组
a[0]
a[1]
a[2]
a[3]
a[4]
a[5]
a[6]
a[7]

1 2 3 4 5 6 7 8
1 2 3 4 5 6 7 8
1 2 3 4 5 6 7 8
1 2 3 4 5 6 7 8
1 2 3 4 5 6 7 8
1 2 3 4 5 6 7 8
1 2 3 4 5 6 7 8
1 2 3 4 5 6 7 8


a、不在同一列：a[n] != a[i]  值不同则列号不同

b、不在同一行：因为现在是每一行求一个皇后的位置，所以同一行不会有冲突，不需要考虑。

c、不在同一对左角线：a[n]-a[i] != n-i

d、不在同一右对角线：a[n]-a[i] != -(n-i)

条件c和d可以合成：abs(a[n]-a[i]) != abs(n-i)
*/


// a[] 已经决定的皇后位置，n 是第 n 个皇后的位置，a[n]
int Check(int a[],int n)  
{  
	// 与前面 n-1 个皇后位置矛盾，则返回 0 
    for(int i=1;i<n;i++)  
    {  
        if(abs(a[i]-a[n])==abs(i-n) || a[i]==a[n])
            return 0;  
    }  
    return 1;  
}  


void eightFor()  
{  
    int a[9];  
    int i,t=1;  
    for(a[1]=1;a[1]<9;a[1]++)  
        for(a[2]=1;a[2]<9;a[2]++)  
        {  
            if(!Check(a,2)) continue;      // 通过改变a[n]的值，来决定第 n 行的皇后位置列号
            for(a[3]=1;a[3]<9;a[3]++)  
            {  
                if(!Check(a,3)) continue;  // continue 可以直接下一个循环
                for(a[4]=1;a[4]<9;a[4]++)  
                {  
                    if(!Check(a,4)) continue;  
                    for(a[5]=1;a[5]<9;a[5]++)  
                    {  
                        if(!Check(a,5)) continue;  
                        for(a[6]=1;a[6]<9;a[6]++)  
                        {  
                            if(!Check(a,6)) continue;  
                            for(a[7]=1;a[7]<9;a[7]++)  
                            {  
                                if(!Check(a,7)) continue;  
                                for(a[8]=1;a[8]<9;a[8]++)  
                                {  
                                    if(!Check(a,8)) continue;  
                                    else   
                                    {  
                                        printf("第%d种解法：\n",t++);  
                                        //for(i=1;i<9;i++)  
                                            //printf("第%d个皇后：%d\n",i,a[i]); 
										for (i = 1; i <9; i++)
										{
											for (int j = 1; j < 9; j++)
											{
												if (a[i] == j)
													printf("■");
												else
													printf("□");
											}
											printf("\n");
										}                                      
}}}}}}}}}



////////////////////////////////////////////////////////////////////////////
int a[20];
int n = 8;  // 8 皇后
int i;
int t = 1;   // 第 t 种解法
  
void Try(int i)     // 从第 i 行开始
{  
    int j;  
    for (j = 1; j <= n; j++)  
    {  
        a[i] = j;  
        if (Check(a, i))             ///////////////////////////////////////如果第j列不会与之前的皇后冲突  
        {  
            if (i < n)               //////////////////////////////////////////如果i<n，即还没有找到八个皇后，继续递归  
                Try(i + 1);  
            else                     ////////////////////////////////////////////如果找到了一组解就输出  
            {  
                printf("第%d种解法：\n", t++);  
                //for(k = 1; k <= n; k++)  
                    //printf("第%d个皇后：%d\n", k, a[k]);  
				for (i = 1; i <9; i++)
				{
					for (int j = 1; j < 9; j++)
					{
						if (a[i] == j)
							printf("■");
						else
							printf("□");
					}
					printf("\n");
				}
			}  
		} 
	}  
}  

//////////////////////////////////////////////////////////////////////////////////////////////

void mainy()
{
	//eightFor();
	//Try(1); 
}

