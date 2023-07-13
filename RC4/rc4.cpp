#include <stdio.h>
#include <stdlib.h>
#define N 20000
void rc4(char *key,int length);
void swap(int *x,int *y);
void statistic();
int main(int argc,char **argv)
{
 char key[]="network";
 int key_length=sizeof(key)/sizeof(key[0])-1;
 printf("the length of array:%d\n",key_length);
 rc4(key,key_length);
 statistic();
 return 0;
      
} 


//swap two numbers
void swap(int *x,int *y)
{
     int temp;
     temp=*x;
     *x=*y;
     *y=temp;
   //  printf("X:%d Y:%d\n",*x,*y);     
}

//produce a random number sequence and write to file 
void rc4(char *key,int length)
{
 int s[256];
 char t[256];
 int i,j,n,g,k;
 FILE *fp;
 //use key to init array t
 k=0;
 while(k!=256)
 {
       t[k]=key[k%length];
       //printf("array t[%d]:%d\n",k,t[k]);     
       k++;            
 }     
 
 //init array s
 for(int index=0;index<256;index++)
   s[index]=index;  
 
 //扰乱数组s 
 j=0;
 for(i=0;i<256;i++)//i variable make every element of array S be handled
 {
  j=(j+s[i]+t[i])%256;//j variable make disturbing array s be random 
  swap(&s[i],&s[j]);                  
 }
 
 
 i=0,j=0,n=0;
 fp=fopen("random.txt","w"); 
 while(n<N)
 {
   i=(i++)%256;
   j=(j+s[i])%256;
   swap(&s[i],&s[j]);
   g=(s[i]+s[j])%256;
   //printf("输出随机数s[:%d]:%d\n",g,s[g]);
   //write the random into a file
   if(fp)
         fprintf(fp,"%d ",s[g]);      
   //printf("n:%d\n",n);
   n++;          
 }   
 fclose(fp);
}


void statistic()
{
 
 FILE *fp1,*fp2;
 int array[N],num[256]; 
 int temp,index=0;
 double number;
 for(int i=0;i<256;i++)
    num[i]=0;//i表示要统计次数的数字 
 fp1=fopen("random.txt","r");
 if(fp1==NULL)
    printf("open file failed\n");
  //return -1; 
 while(!feof(fp1))
 {
   fscanf(fp1,"%d ",&temp);
   array[index]=temp;
   index++;
 }
 //统计数据
 //printf("arrayLength:%d\n",sizeof(array)/sizeof(array[0]));
 for(int j=0;j<sizeof(array)/sizeof(array[0]);j++)
   num[array[j]]++;
 fp2=fopen("frequence.txt","w"); 
 
 //输出统计结果
 for(int j=0;j<256;j++)
 {
   number=num[j];
   printf("%d ocurrence number:%d frequency:%lf\n",j,num[j],number/N); 
   fprintf(fp2,"%d ocurrence number:%d,frequency:%lf ",j,num[j],number/N);
 }
 //将统计结果写入文件
 fclose(fp1);
 fclose(fp2);
}
