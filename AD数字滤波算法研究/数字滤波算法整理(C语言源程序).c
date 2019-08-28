/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) http://www.vcan123.com/thread-1114-1-1.html
 * All rights reserved.
 *
 *
 * @file       		数字滤波算法
 * @brief      		
 * @company	   	    
 * @author     		Hu Mingdong
 * @version    		转载
 * @Software 		适用于C编译器
 * @Target core		
 * @date       		2019-03-23
 ********************************************************************************************************************/
 
 /*假定从8位AD中读取数据（如果是更高位的AD可定义数据类型为int）,
 子程序为get_ad(); */
 
 //1、限副滤波法
 
/*  A值可根据实际情况调整 
    value为有效值，new_value为当前采样值   
    滤波程序返回有效的实际值  */ 
#define A 10 
char value; 
char filter() 
{ 
   char  new_value; 
   new_value = get_ad(); 
   if ( ( new_value - value > A ) || ( value - new_value > A )
   {	   
      return value; 
   }
   return new_value; 
} 

//2、中位值滤波法

/*  N值可根据实际情况调整 
    排序采用冒泡法*/ 
#define N  11 
char filter() 
{ 
   char value_buf[N]; 
   char count,i,j,temp; 
   for ( count=0;count<N;count++) 
   { 
      value_buf[count] = get_ad(); 
      delay(); 
   } 
   for (j=0;j<N-1;j++) 
   { 
      for (i=0;i<N-j;i++) 
      { 
         if ( value_buf[i]>value_buf[i+1] ) 
         { 
            temp = value_buf[i]; 
            value_buf[i] = value_buf[i+1];  
            value_buf[i+1] = temp; 
			 /* or ,delete temp variable*/
			 //value_buf[i] = value_buf[i] ^ value_buf[i+1];
			 //value_buf[i+1] = value_buf[i] ^ value_buf[i+1];
			 //value_buf[i] = value_buf[i] ^ value_buf[i+1];
			 /*****************/
         } 
      } 
   } 
   return value_buf[(N-1)/2]; 
}

//3、算术平均滤波法

#define N 12 
char filter() 
{ 
   int  sum = 0; 
   for ( count=0;count<N;count++) 
   { 
      sum + = get_ad(); 
      delay(); 
   } 
   return (char)(sum/N); 
}

//4、递推平均滤波法（又称滑动平均滤波法）

#define N 12  
char value_buf[N]; 
char i=0; 
char filter() 
{ 
   char count; 
   int  sum=0; 
   value_buf[i++] = get_ad(); 
   if ( i == N ) 
   {
	   i = 0; 
   }
   for ( count=0;count<N,count++)
   {	   
      sum = value_buf[count]; 
   }
   return (char)(sum/N); 
}

//5、中位值平均滤波法（又称防脉冲干扰平均滤波法）

#define N 12 
char filter() 
{ 
   char count,i,j; 
   char value_buf[N]; 
   int  sum=0; 
   for  (count=0;count<N;count++) 
   { 
      value_buf[count] = get_ad(); 
      delay(); 
   } 
   for (j=0;j<N-1;j++) 
   { 
      for (i=0;i<N-j;i++) 
      { 
         if ( value_buf[i]>value_buf[i+1] ) 
         { 
            temp = value_buf[i]; 
            value_buf[i] = value_buf[i+1];  
            value_buf[i+1] = temp; 
         } 
      } 
   } 
   for(count=1;count<N-1;count++) 
   {
      sum += value[count]; 
   }
   return (char)(sum/(N-2)); 
}

//6、限幅平均滤波法
/* 
略 参考子程序1、3 
*/   

//7、一阶滞后滤波法 

/* [code]为加快程序处理速度假定基数为100，
a=0~100 */ 

#define a 50 
char value; 
char filter() 
{ 
   char  new_value; 
   new_value = get_ad(); 
   return (100-a)*value + a*new_value;  
}

//8、加权递推平均滤波法

/* coe数组为加权系数表，存在程序存储区。*/ 
#define N 12 
char code coe[N] = {1,2,3,4,5,6,7,8,9,10,11,12}; 
char code sum_coe = 1+2+3+4+5+6+7+8+9+10+11+12; 
char filter() 
{ 
   char count; 
   char value_buf[N]; 
   int  sum=0; 
   for (count=0,count<N;count++) 
   { 
      value_buf[count] = get_ad(); 
      delay(); 
   } 
   for (count=0,count<N;count++)
   {	   
      sum += value_buf[count]*coe[count]; 
   }
   return (char)(sum/sum_coe); 
}

//9、消抖滤波法

#define N 12 
char filter() 
{ 
   char count=0; 
   char new_value; 
   new_value = get_ad(); 
   while (value !=new_value); 
   { 
      count++; 
      if (count>=N)  
	  {
		 return new_value;
	  }		  
      delay(); 
      new_value = get_ad(); 
   } 
   return value;     
} 

//10、限幅消抖滤波法 
/*略 参考子程序1、9*/
