#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <bitset>
using namespace std;
unsigned  char *Chin,*Eng;//程序执行完后才释放
#define N 7168;
using std::bitset;
int x[100],y[100],z[100],m[100];//被除数  除数  商  余数 
int digit;//大数的位数 
//十六进制数0x123456中,12是高位还是低位?56是高位还是低位?12是高位,56是低位.这是绝对的.
//bitset 中 bit[0]是低位 
//输出的bitset串 如：a :0110101000001001111001100110011111110011101111001100100100001000
//最右边是最低位a[0]=0  a[1]=0  a[2]=0 a[3]=1 
//int index;
bitset<64> a=0x6A09E667F3BCC908;
bitset<64> b=0xBB67AE8584CAA73B;    
bitset<64> c=0x3C6EF372FE94F82B;
bitset<64> d=0xA54FF53A5F1D36F1;
bitset<64> e=0x510E527FADE682D1;
bitset<64> f=0x9B05688C2B3E6C1F;
bitset<64> g=0x1F83D9ABFB41BD6B;
bitset<64> h=0x5BE0CD19137E2179;
void readFile(unsigned char Chin[1000],unsigned char Eng[1000]);
int  UcharToBin(unsigned char input[1000],bitset <6144> &Bit);
void DecToBin(int num,bitset<128> &lengthBit);
int getRealLen(unsigned char input[1000]);
void messageFill(unsigned char input[1000],int messLen,bitset<6144> &messageBit);
void bedding(int &index,bitset<64> x,bitset<512> &H0);
void getH0(bitset<512> &H0);
void functionFirst(bitset<1024> M,bitset<512> temp);
void leftSpin(bitset<512> &input,bitset<512> &output,int loop);
void rightSpin(bitset<512> &input1,bitset<512> &output1,int loop);
void Xor(bitset<512> res1,bitset<512> res2,bitset<512> &res);
void myPower(int n,int a[200]);//计算2的高幂次
char *ulongTos(unsigned long input);
char *intTocharArr(int b[200]);
void sub(int x[],int y[],int len1,int len2);//大数减法 
int judge(int x[],int y[],int len1,int len2);
unsigned long getRemainder(char *a,char *b);
void eachGroup(bitset<1024> group,int k,bitset<512> &H);
void getSummary(unsigned char input[1000],bitset<6144> &messageBit);

int main()
{
	unsigned char Chin[1000],Eng[1000];
	int index;
	bitset<6144> ChBit;
	bitset<6144> EnBit;
	bitset<512> H;
	readFile(Chin,Eng);
	cout<<"中文";
	getSummary(Chin,ChBit);
	cout<<"英语";
	getSummary(Eng,EnBit);

	return 0;
}

void readFile(unsigned char Chin[1000],unsigned char Eng[1000])
{

	string strCh,strEn;
	char Ch[1000];
	char En[1000];
	unsigned long int ChLen,EnLen;
	//unsigned  char *Chin,*Eng;//
	Ch[999]='\0';
	if(Chin==NULL)
		cout<<"Error"<<endl;
	else
		cout<<"memory success"<<endl;
	
	En[999]='\0';
	ifstream fileCh("chinese.txt",ios::in);
	ifstream fileEn("english.txt",ios::in);
	if(!fileCh)
		cout<<"open chinese.txt error!"<<endl;
	else
	{
		//getline(fileCh,strCh);
		fileCh.getline(Ch,1000);
		strcpy((char*)Chin,(const char*)Ch);
		cout<<"读入的字符为: "<<Chin<<endl;
	}
	
	if(!fileEn)
		cout<<"open english.txt error!"<<endl;
	else
	{
		fileEn.getline(En,1000);
		strcpy((char*)Eng,(const char*)En);
		cout<<"读入的字符为: "<<endl;
		for(int i=0;i<675;i++)
			cout<<Eng[i];
	}
	ChLen=strlen((const char *)Chin);
	EnLen=strlen((const char *)Eng);
	cout<<endl;
	cout<<"ChLen:"<<ChLen<<endl;
	cout<<"EnLen:"<<EnLen<<endl;
	
	//int len=strlen("读入"); //一个汉字占3个字节
}

int  UcharToBin(unsigned char input[1000],bitset <6144> &Bit)
{
	int index=0;
	for(int i=0;i<strlen((const char *)input);i++)
	{
		for(int j=7;j>=0;j--)
		{
			Bit[index]=((input[i]>>j)&1);
			index++;
		}
			
	}
	return index;
}
void DecToBin(int num,bitset<128> &lengthBit)
 {
     //十进制转换为若干进制>2,<16 =
     //int num;
     int n;//2-16之间
     int a;
     int i=0;
     bitset <128> s;
	 n=2;
        while(num!=0)
        {
            a=num%n;
            num=num/n;
            
            s[i]=a;
            //cout<<" s["<<i<<"]:"<<s[i]; 
            i++;
 			
        }
       // cout<<"i:"<<i<<endl;
        for(int k=0;k<i;k++)
        	lengthBit[k]=s[i-1-k];
        for(int k=i;k<128;k++)
        	lengthBit[k]=0;
 }
int getRealLen(unsigned char input[1000])
{
	int len=strlen((const char *)input);
	int flag=0,messLen;
	int quotient=(len*8)/1024;
	int remainder=(len*8)%1024;
	int fillNumLen,index;
	if(remainder!=0)//不是1024的倍数
	{
		fillNumLen=(1024*(quotient+1))-len*8;//fillNumLen是为了凑成1024的倍数，需要填充的长度
		if(fillNumLen>=128)
			messLen=(quotient+1)*1024;//messLen是总共的比特数 
		else
			messLen=(quotient+2)*1024;
	}
	else
		messLen=len*8;	
	return messLen;

}
void messageFill(unsigned char input[1000],int messLen,bitset<6144> &messageBit)
{
	int len=strlen((const char *)input);
	int flag=0;
	/*messLen;
	int quotient=(len*8)/1024;
	int remainder=(len*8)%1024;
	int fillNumLen,index,flag=0;
	if(remainder!=0)
	{
		fillNumLen=(1024*(quotient+1))-len*8;//messLen是总共的比特数 
		if(fillNumLen>=128)
			messLen=(quotient+1)*1024;
		else
			messLen=(quotient+2)*1024;
	}
	else
		messLen=len*8;	*/
	int index;
	bitset <128> lengthBit;	
	index=UcharToBin(input,messageBit);//把信息转换成0 1比特存起来 
	messageBit[index]=1;//
	
	for(int i=index+1;i<(messLen-128);i++)
		messageBit[i]=0;//补0 
	DecToBin(len,lengthBit);//获取存信息长度的128比特 
	for(int i=messLen-128;i<messLen;i++)
	{
		messageBit[i]=lengthBit[flag];
		flag++;
	}
}
void bedding(int &index,bitset<64> x,bitset<512> &H0)
{
	
	for(int i=0;i<64;i++)
	{
		H0[index]=x[i];
		index++;
	}

}
void getH0(bitset<512> &H0)
{
	int index=0;	
	//cout<<"index:"<<index<<endl;
	bedding(index,h,H0);
	bedding(index,g,H0);
	bedding(index,f,H0);
	bedding(index,e,H0);
	bedding(index,d,H0);
	bedding(index,c,H0);
	bedding(index,b,H0);
	bedding(index,a,H0);
	
	//cout<<"H: "<<H0<<endl;

}
bitset<512> mlRes;
bitset<512> mrRes;
void functionFirst(bitset<1024> M,bitset<512> temp)
{
	bitset<512> ml;
	bitset<512> mr;
	for(int i=0;i<512;i++)
		mr[i]=M[i];
	for(int i=0;i<512;i++)
		ml[i]=M[i+512];

	for(int i=0;i<512;i++)
		mlRes[i]=ml[i]^temp[i];
	for(int i=0;i<512;i++)
		mrRes[i]=mr[i]&temp[i];	
	
}
void leftSpin(bitset<512> &input,bitset<512> &output,int loop)//512位异或结果左旋 
{
	int len=512,t;
	int index=1;
	bitset<512> temp;
	for(int k=0;k<512;k++)
		temp[k]=input[k];
	for(int i=len-1;i>loop-1;i--)
	{
		t=temp[0];

		for(int j=len-1;j>0;j--)//实际上是先得出右旋一次的结果，左旋n次，相当于右旋length-n次
			input[j-1]=temp[j]; //交换的时候，如果是input自身交换，不能改变值，所以借助了temp数组，每次将temp数组更新
		input[len-1]=t;

		for(int w=0;w<512;w++)
			temp[w]=input[w];
		/*cout<<temp<<endl;
		cout<<"index"<<index<<endl;
		cout<<input<<endl;
		index++;*/
	}
	for(int k=0;k<512;k++)
		output[k]=input[k];
}
void rightSpin(bitset<512> &input1,bitset<512> &output1,int loop)//512位按位与结果右旋 
{
	int len=512,t;
	int index=1;
	bitset<512> temp;
	//int spinNum=(loop*64)%512;
	for(int k=0;k<512;k++)
		temp[k]=input1[k];
	for(int i=0;i<loop;i++)
	{
		t=temp[0];

		for(int j=len-1;j>0;j--)
			input1[j-1]=temp[j]; //交换的时候，如果是input自身交换，不能改变值，所以借助了temp数组，每次将temp数组更新
		input1[len-1]=t;

		for(int w=0;w<512;w++)
			temp[w]=input1[w];
	}
	for(int k=0;k<512;k++)
		output1[k]=input1[k];
}

void Xor(bitset<512> res1,bitset<512> res2,bitset<512> &res)
{
	for(int k=0;k<512;k++)
		res[k]=res1[k]^res2[k];

}
void myPower(int n,int a[200])//计算2的高幂次
{
    int i,j,k,flag=0;
    a[0] = 1;
    for(i=0;i<n;i++)
    {
          for(j=0;j<200;j++)  //先让每一位乘以2
          {
              a[j]*=2;
          }
          for(k=0;k<200;k++) //处理进位
          {
              a[k+1]+=a[k]/10;  
              a[k]=a[k]%10;          
          }       
    } 
    for(i=199;i>=0;i--)
    {
        if(a[i]!=0)
            break;  
    }
    int num=i;

    for(i=num;i>(num/2);i--) //(num-1/2)  如果是num就又给交换回去了  逆序程序
    {
	int temp;
	temp=a[i];
	a[i]=a[num-i];
	a[num-i]=temp;
	flag=flag+1;	
    } 
    //cout<<endl;    
}
char ret[100];
char *ulongTos(unsigned long input)
{
	ostringstream os;
	string str;
	
	ret[99]='\0';
	os<<input;	
        istringstream is(os.str());
	is>>str;
	strcpy(ret,str.c_str());
	return ret;
}
char charRes[20];
char *intTocharArr(int b[200])
{
	string s1;
	int tempn,n=64;
	char tmp[64];
	
	for(int i=0;i<19;i++)
	{
		tempn=b[i];
		sprintf(tmp,"%d",tempn);
		s1+=tmp;
	}
	
	charRes[19]='\0';
	strcpy(charRes,s1.c_str());

	return charRes;
}
void sub(int x[],int y[],int len1,int len2)//大数减法 
{
	int i;
	for(i=0;i<len1;i++)
	{
		if(x[i]<y[i])
		{
			x[i]=x[i]+10-y[i];
			x[i+1]--;
		}
		else
			x[i]=x[i]-y[i];
	}
	for(i=len1-1;i>=0;i--)//判断减法结束之后，被除数的位数 
	{
		if(x[i])
		{ 
			digit=i+1;
			break;		   
		} 
	}
}
int judge(int x[],int y[],int len1,int len2)
{
	int i;
	if(len1<len2)
		return -1;
	if(len1==len2)//若两个数位数相等 
	{
		for(i=len1-1;i>=0;i--)
		{
			if(x[i]==y[i])//对应位的数相等 
				continue;
			if(x[i]>y[i])//被除数 大于 除数，返回值为1 
				return 1;
			if(x[i]<y[i])//被除数 小于 除数，返回值为-1 
				return -1;
		}
		return 0;//被除数 等于 除数，返回值为0 
	}	
}


unsigned long getRemainder(char *a,char *b)//x代表的是被除数 y代表除数 len1被除数长度 len2除数长度
{
	int i,j=0,k=0,temp;
	int len,len1,len2;//len两个大数位数的差值   
	//while(a!=NULL&&b!=NULL)
		len1=strlen(a);//被除数位数
		len2=strlen(b);//除数位数
		for(i=len1-1,j=0;i>=0;i--)//将字符串中各个元素倒序储存在数组中 
			x[j++]=a[i]-'0';
		for(i=len2-1,k=0;i>=0;i--)
			y[k++]=b[i]-'0';		    
		if(len1<len2)//当被除数位数 小于 除数位数时 
		{
			//printf("余数是：");
			//puts(a);
			return 0;
		}
		else //当被除数位数 大于或者 除数位数时
		{
			len=len1-len2;//两个大数位数的差值
			for(i=len1-1;i>=0;i--)//将除数后补零，使得两个大数位数相同。被除数：4541543329 除数：98745,加零后:9874500000 
			{
				if(i>=len)
					y[i]=y[i-len];
				else
					y[i]=0;
			}
			len2=len1;//将两个大数数位相同 		
			digit=len1;	//将原被除数位数赋值给digit 
			for(j=0;j<=len;j++)
           		{
				z[len-j]=0;
				while(((temp=judge(x,y,len1,len2))>=0)&&digit>=k)//判断两个数之间的关系以及位数与除数原位数的关系 
				{	
					sub(x,y,len1,len2);	//大数减法函数			    
					z[len-j]++;//储存商的每一位
					len1=digit;//重新修改被除数的长度
					if(len1<len2&&y[len2-1]==0)		
						len2=len1;//将len1长度赋给len2;						
				}
				if(temp<0)//若被除数 小于 除数，除数减小一位。例如：被除数：4541543329 除数：(原)98745,(加零后)9874500000，后退一位后:0987450000 
				{
					for(i=1;i<len2;i++)
						y[i-1]=y[i];
					y[i-1]=0;
					if(len1<len2) 
						len2--;			        				        
				}
			}
			//printf("余数是：");
			for(i=len1;i>0;i--)
			{
				if(x[i])
					break;
			}
			//for(;i>=0;i--)
			//	printf("%d",x[i]);
			return x[i];
			printf("\n");
		      }
	
}


void eachGroup(bitset<1024> group,int k,bitset<512> &H)
{
	
	bitset<512> leftSpinOutput;
	bitset<512> rightSpinOutput;
//	bitset<1024> group;
	bitset<512> temp;
	bitset<512> xorResult;
	bitset<64> groupXorRes[8];
	bitset<64> groupHRes[8];
	bitset<64> addRes;
	unsigned long number;
	int n=64,retValue,remainder;
	int b[200]={0};//!!必须有初始化否则输出乱码
	char *bchushu=new char[100];
	char *chushu=new char[100];
	bitset<64> Rem[8];//用bitset数组来存512个比特的余数，每组存64个
	
	functionFirst(group,H);
	leftSpin(mlRes,leftSpinOutput,k); //mlRes、mrRes是全局变量
	rightSpin(mrRes,rightSpinOutput,k);
	Xor(leftSpinOutput,rightSpinOutput,xorResult);//旋转后的两个结果按位做异或运算 512bit
	for(int t=0;t<8;t++)//第t组 (每组64bit)
	{
		for(int w=0;w<64;w++)
		{	
			groupXorRes[t][w]=xorResult[w+t*64];//异或结果分为8组，每组64比特
			groupHRes[t][w]=H[w+t*64];//Hi分为8组，每组64比特
			addRes[w]=groupXorRes[t][w]^groupHRes[t][w];//结果的每一位等于对应位相加模二，是不带进位的加法结果
		}
		number=addRes.to_ulong();//相加的结果转化为unsigned long
		myPower(n,b);//2的64次方
		bchushu=ulongTos(number);//被除数
		chushu=intTocharArr(b);//除数
		retValue=getRemainder(bchushu,chushu);//求余数
		if(retValue!=0)
		{
			remainder=retValue;
			bitset<64> bitTemp(retValue);
			for(int g=0;g<64;g++)
				Rem[t][g]=bitTemp[g];
		}
		else
		{
			for(int g=0;g<64;g++)
				Rem[t][g]=addRes[g];
		}	
	}
	for(int q=0;q<8;q++)		//把8组的余数合起来组成下一个H
	{
		for(int inx=0;inx<64;inx++)
			
			H[inx+q*64]=Rem[q][inx];
	}
}

void getSummary(unsigned char input[1000],bitset<6144> &messageBit)
{
	int idealLen;
	string Remainder;
	int remainder=0;
	string strTemp;
	bitset<512> H0;
	bitset<512> H;
	bitset<1024> group;
	bitset<512> endRemainder;
	int k;
	idealLen=getRealLen(input);//获得二进制比特串目的长度
	messageFill(input,idealLen,messageBit);//将字符串填充成符合条件的二进制比特串 调用了UcharToBin（）
	getH0(H0);//获取H0的二进制比特串表示形式
	for(k=0;k<idealLen/1024;k++)//分了多少组1024
	{
		for(int j=0;j<1024;j++)
			group[j]=messageBit[j+k*1024];//第k个1024
		if(k==0)
		{
			eachGroup(group,k,H0); //H0的值经过处理变成了下一次的H
			for(int r=0;r<512;r++)
				H[r]=H0[r];
		}
		else
		{
			eachGroup(group,k,H);
		}	
	}
	cout<<"摘要代表的二进制比特串："<<endl;
	cout<<H<<endl;
	string s=H.template to_string();
	//cout<<s<<endl;
	int cnt=0;
	cout<<"摘要代表的字符："<<endl;
	for(int j=0;j<64;j++)
	{
		for(int m=0;m<8;m++)
		{
			cnt+=(s[m+j*8]-'0')<<(7-m);
			printf("%c",cnt);
		}
		cnt=0;
	}
	cout<<endl;
}

