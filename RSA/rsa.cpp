#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
bool isPrime(int num);
int exgcd(int a, unsigned long int b,unsigned long int &x,unsigned long int &y);
unsigned long int Plus(unsigned long int a,unsigned long int b,unsigned long int c);
unsigned long int Multiplies(unsigned long int a,unsigned long int b,unsigned long int c);
unsigned long int PowerMod(unsigned long int a,unsigned long int  b,unsigned long int c); 

int main()
{
	int prime[500]={0};
	bool ret;
	srand(time(NULL));
	int flag=1;

	int i=0,num,index=0;
	int message=2127;
	int secretMess;
	unsigned long int d,p,q,T,e,n,y;
	//ifstream file; ifstream输入
	fstream file;
	file.open("prime.txt",ios::out);
	if(!file)
		cout<<"error open"<<endl;
	
	for(int k=2;k<500;k++)
	{
		ret=isPrime(k);
		if(ret)
		{
			file<<k<<" ";
			prime[index]=k;
			//cout<<"index:"<<index<<" prime:"<<k<<endl;
			index++;
		}
	}

	for(int k=0;k<=index;k++)
	{
		if(prime[k]>300)
		{
			p=prime[k-1];
			q=prime[k];
			break;
		}
	}
	cout<<"小于300的最大素数:"<<p<<endl;
	cout<<"大于300最小素数:"<<q<<endl;
	n=p*q;
	T=(p-1)*(q-1);
	for(int j=0;j<T;j+=1331)  
	{
		int gcd=exgcd(j,T,d,y);
		if(gcd==1&&d>0)
		{
			e=j;
			break;
		}
	}
	//d=getParaD(e,T);
	unsigned long  x;   //2^64-1
	cout<<"e:"<<e<<endl;
	cout<<"d:"<<d<<endl;
	cout<<"n:"<<n<<endl;
	cout<<"T:"<<T<<endl;
	x=e*d;
	cout<<"e*d:"<<x<<endl;
	cout<<"e *d mod T:"<<((e*d)%T+T)%T<<endl;
	cout<<"1 mod T:"<<(1%T+T)%T<<endl;
    // 当指数太大时 pow()结果INF */
	int decryMess;
	//secretMess=PowMod(message,e,n);
	secretMess=PowerMod(message,e,n);
	cout<<"secretMess:"<<secretMess<<endl;


	decryMess=PowerMod(secretMess,d,n);
	cout<<"decryMess:"<<decryMess<<endl;
	file.close();
	return 0;
}


bool isPrime(int num)
{
	int tmp=sqrt(num);
	for(int i=2;i<=tmp;i++)
	{
		if(num==0||num==1||num%i==0)
		{
			//cout<<"is not prime"<<endl;
			return false;
		}
	}

	return true;

}
//拓展欧几里得  已知a,b 求满足ax + by = gcd(a, b) 的一组解
int exgcd(int a, unsigned long int b,unsigned long int &x,unsigned long int &y)
{
    if (b == 0){
        x = 1;
        y = 0;
        return a;
    }
    unsigned long int x1,y1;
    int ans = exgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - a / b * y1;
    return ans;
}


unsigned long int Plus(unsigned long int a,unsigned long int b,unsigned long int c)//  (a+b)%c 
{
     if(a+b>=a)  return  (a+b)%c;  //  不溢出 
     return  (a%c+b%c-c);
} 
unsigned long int Multiplies(unsigned long int a,unsigned long int b,unsigned long int c)//  (a*b)%c 
{
     if (a*b/a==b)  return  (a*b)%c;  //  不溢出 
     unsigned long int s  =   0 ;
     for (unsigned long int t=a; b; t=Plus(t,t,c),b>>=1)
     {
         if ((b&1)!=0)
            s=Plus(s,t,c);
    } 
     return  s;
} 
unsigned long int PowerMod(unsigned long int a,unsigned long int  b,unsigned long int c)//  (a^b)%c 
{
    unsigned long int s=1 ;
	cout<< endl <<a<<"^"<<b<<"mod("<<c<<")=";
    for(unsigned long int t=a;b;t=Multiplies(t,t,c),b>>=1)
    {
         if ((b&1)!=0)
            s=Multiplies(s,t,c);
    } 
	cout<<s<<endl;
    return  s;
} 













