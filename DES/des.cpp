#include <cstdio> 
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string.h>
#include <cmath>
#include <fstream>
using namespace std;
#define N 600
#define M 100
//void charTobyte(char c); 
//void charTobit();//char数组转换成二进制数组 
int number;
void charTobit(char message[500],char output[100]);//字符串转化成二
void bitTochar(char output[200]);//二进制数组转换为char数组 
int ifIs64(char output[200]);//判断明文是否是64 bit的倍数 
int IP_64(int message64[64],int output[64]);
int IPR_64(int input[64],int output[64]);
void messageRightTo48(int input[32],int message48[48]);
void Xor(int array1[M],int array2[M],int xorResult[M],int arrayLen);
void binaryTodecimal(int array[],int &result,int arrayLen);//二进制数转十进制数 
void decimalTobinary(int result,int array[4]);//十进制数转二进制 
void message48To32(int input[48],int output[32]);
void message32Rearrange(int input[32],int output[32]);
void key64To56(int input[64],int output[56]);
void keyLeftSpin(int input[28],int output[28],int loop);//28位密钥左旋
void key56Rearrange(int input[56],int output[56]);
void key56To48(int input[56],int output[56]);
void pretreatment(char message[500],char key1[100],int handleMessage[500],int key56[56]); //预处理 
void oneroundEncryption(int Message64[64],int key56[56],int loop);
void DecryKey(int key56[56],int key48[48],int loop);
void oneroundDecryption(int Message64[64],int key56[56],int loop);
void encryption(char message[500],char key1[100]);
void swap(int input[64],int output[64]);
void decryption(int secretMessage[500],char key2[100]);

int IP_Table[64]={58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7};//IP置换矩阵
int IPR_Table[64]={40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25};//IP盒的逆矩阵 
int Table_48[48]={32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1};
int S_box[4][16]={14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13};
int P_Table[32] = {16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25};//  P 盒
int comp_Table[4][16]={{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}};//48bit to 32bit
int loop_Table[16]={1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
int key1_Table[56]={57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4};
int key2_Table[48]={14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32};

int main(int argc,char **argv)
{
	int choice;
	char key1[100]={0},key2[100]={0};
	char message[500]={0},secret[500]={0};
	int secretMessage[500];
	for(int k=0;k<500;k++)
		secretMessage[k]=-1;//对secertMessage初始化 
	
	int flag=0;
	char character;
	cout<<"1.Plaintext encryption"<<endl; 
	cout<<"2.Ciphertext decryption"<<endl;
	cout<<"3.exit"<<endl;
	cout<<"Please enter your choice:"<<endl;
	cin>>choice;
	ifstream myfile;
	do{
		switch(choice){
			case 1:strcpy(message,"yangrong 151002127");
			       strcpy(key1,"12345678");
			       cout<<"message:"<<message<<endl;
			       cout<<"key1:"<<key1<<endl;
			       encryption(message,key1);
			       flag=1;
			       break;
			case 2:cout<<"Please enter ciphertext\n";
			       
			       myfile.open("out.txt");
			       if(!myfile)
				   cout<<"can not open"<<endl;
			       myfile.getline(secret,500);
			       cout<<endl;
			      /* while(myfile)
			       {
				   cout<<"begin read:"<<endl;
			           memset(secret,0,500);
				   getline(secret,500,'\n');

				}
			       	else
					cout<<"read error:"<<endl;*/
			       //cin>>secret;
			       cout<<"read from file:"<<secret<<endl;
                               cout<<"Please enter the key (the key consists of 4 digits/letters)\n";
                               cin>>key2;
			       cout<<"The ciphertext will be decrypted"<<endl;
			       cout<<"decrypted length: "<<strlen(secret)<<endl;
			      for(int i=0;i<strlen(secret);i++)
			       {
				   secretMessage[i]=(int)(secret[i]-48);
				  // cout<<secretMessage[i];
			       }
                               decryption(secretMessage,key2);
                               flag=1;
                               break;
			case 3:flag=1;exit (0);
			default:cout<<"Input errors, please re-enter"<<endl;cin>>choice;break;
		}
	}while((choice!=1&&choice!=2&&choice!=3)||flag==0);
}


void charTobit(char message[500],char output[100])//字符串转化成二进制 
{  
    char str[N]={'\0'};
    strcpy(str,message);
    //char output[100]={0};//初始化很重要，否则后面找不到\0,不知道数组啥时候结束 
    int j;
    int num=0;
    for(int i=0; str[i]; i++)          
	{
		unsigned char k = 0x80;
		for (j=0; j<8; j++, k >>= 1)//字符转换成二进制 
		{
			if (str[i] & k)
			{
				output[num]='1';
			//	printf("1");
		 	}
			else
			{
			//	printf("0");
				output[num]='0';
			}
			num++;
		}
	}

}

void bitTochar(char output[200])
{
	char c[strlen(output)+1]={0};
	char t[9]={0};
	int index=0,i=0;
	while(index<strlen(output)+1)
	{
			t[i]=output[index];	
			if((index+1)%8==0)//index是从0开始的，而每8个比特是1个byte。所以取8位。eg.index为7时，0-7是8个比特 
			{
				int k=0;
				c[k]=strtol(t,0,2);//把t数组(8个比特)转换成1个字符 
				k++;
				i=-1;//将i设为0，始终保持t数组的0-7是一个字符 
			}
			index++;
			i++;//不是8位时,i依然++ 
	}
}
int ifIs64(char output[200])//判断明文是否是64 bit的倍数 
{
	int length;
	//int quotient;//商 
	int flag=-1;
	length=strlen(output);
	//length=126;
	if(length%64==0)
	{
		cout<<"is 64-multiple "<<endl;
		flag=-1;
	}
	else
	{
		cout<<"is not 64-multiple"<<endl;
		flag=0;
	}
	//cout<<"OUTPUT修改:"<<output<<endl; 	
	return flag;
} 

int IP_64(int message64[64],int output[64])
{
	/*char messageInit[65];
	int message64[64];
	message64[64]='\0';
	strcpy(messageInit,message.c_str());
	for(int i=0;i<64;i++)
		message64[i]=(int)(messageInit[i]-48);//把char转换成了int */
	
	for(int k=0;k<64;k++)
		output[k]=message64[IP_Table[k]-1];
} 
int IPR_64(int input[64],int output[64])
{
	for(int i=0;i<64;i++)
	{
		output[i]=input[IPR_Table[i]-1];
	}
} 
void messageRightTo48(int input[32],int message48[48])
{

	for(int j=0;j<48;j++)
		message48[j]=input[Table_48[j]-1]; //Table_48中存的是对应的下标，是位置 
} 
void Xor(int array1[M],int array2[M],int xorResult[M],int arrayLen)
{
	for(int i=0;i<arrayLen;i++)
	{
		xorResult[i]=array1[i]^array2[i];
	}
}

void binaryTodecimal(int array[],int &result,int arrayLen)//二进制数转十进制数 
{
	int sum=0;
	for(int i=0;i<arrayLen;i++)
		sum=sum+array[i]*pow(2,arrayLen-1-i);
	result=sum;
 } 
 
void decimalTobinary(int result,int array[4])//十进制数转二进制 
{
	for(int i=3;i>=0;i--)
	{
		if(result&(1<<i))
			array[3-i]=1;
		else
			array[3-i]=0;
	}
}

void message48To32(int input[48],int output[32]) 
{
	int array1[4],array2[2],array3[4];
	int result1=-1,result2=-1;
	int  insteadNum,j=0,count=1;
	//int getResult[32];
	
	for(int i=0;i<48;i++)
	{
		if((i+1)%6==0)
		{
			array1[0]=input[i-4];
			array1[1]=input[i-3];
			array1[2]=input[i-2];
			array1[3]=input[i-1];//取出中间四位 
			
			array2[0]=input[i-5];
			array2[1]=input[i];
			binaryTodecimal(array1,result1,4);//列下标 			
			binaryTodecimal(array2,result2,2);//行下标
			insteadNum=comp_Table[result2][result1];
			decimalTobinary(insteadNum,array3);
			while(count!=4)
			{
				output[j]=array3[j%4];
				count++;
				j++;
			}
			count=-1;		
		}
	}
}
void message32Rearrange(int input[32],int output[32])
{
	for(int i=0;i<32;i++)
		output[i]=input[P_Table[i]-1];
}

void key64To56(int input[64],int output[56]) 
{
	for(int i=0;i<56;i++)
	{
		if(i<=6)
		{
			output[i]=input[i];
		}
		else if(i<=13&&i>6)
			output[i]=input[i+1];
		else if(i<=20&&i>13)
			output[i]=input[i+2];
		else if(i<=27&&i>20)
		    output[i]=input[i+3];
		else if(i<=34&&i>27)
		    output[i]=input[i+4];
		else if(i<=41&&i>34)
		    output[i]=input[i+5];
		else if(i<=48&&i>41)
		    output[i]=input[i+6];
		else if(i<=55&&i>48)
		    output[i]=input[i+7];
	}
	
}
void keyLeftSpin(int input[28],int output[28],int loop)//28位密钥左旋 
{
	int len=28,t;
	for(int i=len-1;i>loop_Table[loop-1]-1;i--)
	{
		t=input[len-1];
		for(int j=len-1;j>0;j--)
		{
			input[j]=input[j-1]; 
		}
		input[0]=t;
	}
	for(int k=0;k<len;k++)
		output[k]=input[k];
}
void key56Rearrange(int input[56],int output[56])
{
	for(int i=0;i<56;i++)
		output[i]=input[key1_Table[i]-1];
}
void key56To48(int input[56],int output[56])
{
	for(int i=0;i<48;i++)
		output[i]=input[key2_Table[i]-1];
}
void pretreatment(char message[500],char key1[100],int handleMessage[500],int key56[56]) //预处理 
{
	char output[N]={0};
	char t[65];
	output[N-1]='\0';
	t[64]='\0';
	int flag=-1,length,quotient;
	charTobit(message,output);
	length=strlen(output);//strlen()算的长度不包含'\0',sizeof才包含'\0' 
	flag=ifIs64(output);
	if(flag==0) //output不是64的倍数，末尾用0进行补充
	{
		quotient=(int)(length/64);//除以64所得的整数的商 
		number=(quotient+1)*64;
		//cout<<"Quotient"<<quotient<<endl;
		//cout<<"After the expansion is a multiple of 64:(It is)"<<number<<endl;
		output[length]='#';//末尾补充的时候，先补充一个特殊字符 
		for(int j=length+1;j<number;j++)//将明文补成64的倍数，不足的地方补0 
		{ 
			output[j]='0';
		} 
		
		output[number]='\0';
		//cout<<"After the plaintext is multiplied by 64, the 0,1 string is:"<<output<<endl;
	} 
	//cout<<"Convert the message's char array to an int array:";
	for(int i=0;i<number;i++)
	{
		if(output[i]!='#')
			handleMessage[i]=(int)(output[i]-48);//把char转换成了int
		else
			handleMessage[i]=(int)(output[i]-35);
		//cout<<handleMessage[i]<<" ";
	}
	//对密钥的处理
	//key1 先把密钥转化成二进制
	char keyEncry[65];
	int key64[64];
	keyEncry[64]='\0';
	//strcpy(keyEncry,charTobit(key1)); 
	charTobit(key1,keyEncry);
	//cout<<"Convert key's char array to int array:"<<endl;
	for(int k=0;k<64;k++)
	{
		key64[k]=(int)(keyEncry[k]-48);	
		//cout<<key64[k]<<" ";
	}
	key64To56(key64,key56); 
	
}
void oneroundEncryption(int Message64[64],int key56[56],int loop)
{
	//每64位一组进行加密 
	int count=0;
	int message48[48];
	int message64[64];
	int message32[32];
	int xorResult[48];
	int keyLeft[28],keyRight[28];
	int messageRearrange32[32];
	int secondXorResult[32];
	int keyLeftSpinRes1[28],keyLeftSpinRes2[28];
	int keySpinResult[56];
	int key48[48];
	int cipher[64];
	int ciphertext[64];
	int arrayLen;
	for(int k=0;k<28;k++)
		keyLeft[k]=key56[k];
	for(int k=0;k<28;k++)//if there is begin from 28,传过去的的数组是从0-28开始的，没有值
	
		keyRight[k]=key56[k+28];
	//key的左右两部分分别左旋 
	keyLeftSpin(keyLeft,keyLeftSpinRes1,loop);
	keyLeftSpin(keyRight,keyLeftSpinRes2,loop);
	
	//将key左旋的结果合并 
	for(int k=0;k<28;k++)
		keySpinResult[k]=keyLeftSpinRes1[k];
	for(int k=28;k<56;k++)
		keySpinResult[k]=keyLeftSpinRes2[k-28];//keySpinResult[56]就是下一轮输入的key 
	//从key的56 bit中选出48bit
	 key56To48(keySpinResult,key48); 
	 int messRight[32],messLeft[32];
	 //i=-1;//将i设为0，始终取t数组的0-63位 
	 //IP_64(Message64,message64);//将字符串明文s转换成重排后的64位int数组 		
	 for(int m=0;m<32;m++)
		messLeft[m]=Message64[m];
	 for(int m=0;m<32;m++)
		messRight[m]=Message64[32+m];
	 messageRightTo48(messRight,message48);
	 Xor(message48,key48,xorResult,48);
	 message48To32(xorResult,message32);
	 message32Rearrange(message32,messageRearrange32);
	 Xor(messageRearrange32,messLeft,secondXorResult,32);
         for(int m=0;m<32;m++)
		cipher[m]=messRight[m];
	 for(int m=32;m<64;m++)
		cipher[m]=secondXorResult[m-32]; //cipher[64]就是下一轮的输入 
	//count++;
	//将得到的64bit 密文进行重排,但这一步是最后才进行的呀 
	 //IPR_64(cipher,ciphertext);  //cipher作为下一次的密文 
				
	for(int t=0;t<64;t++)
		Message64[t]=cipher[t];//下一轮的64 bit message ,there should be rearrangeMessage	
	for(int t=0;t<56;t++)
		key56[t]=keySpinResult[t];//下一轮的56 bit key 	
}

void DecryKey(int key56[56],int key48[48],int loop)
{

	int keyLeft[28],keyRight[28];
	int keyLeftSpinRes1[28],keyLeftSpinRes2[28];
	for(int k=0;k<28;k++)
		keyLeft[k]=key56[k];
	for(int k=0;k<28;k++)//if there is begin from 28,传过去的的数组是从0-28开始的，没有值	
		keyRight[k]=key56[k+28];
	//key的左右两部分分别左旋 
	keyLeftSpin(keyLeft,keyLeftSpinRes1,loop);
	keyLeftSpin(keyRight,keyLeftSpinRes2,loop);
	//将key左旋的结果合并 
	for(int k=0;k<28;k++)
		key56[k]=keyLeftSpinRes1[k];
	for(int k=28;k<56;k++)
		key56[k]=keyLeftSpinRes2[k-28];//keySpinResult[56]就是下一轮输入的key 	
	//从key的56 bit中选出48bit
	 key56To48(key56,key48); 
}

void oneroundDecryption(int Message64[64],int key56[56],int loop)
{
	
	int count=0;
	int message48[48];
	int message64[64];
	int message32[32];
	int messageRearrange32[32];
	int secondXorResult[32];
	int keySpinResult[56];
	int key48[48],xorResult[48];;
	int cipher[64];
	int ciphertext[64];
	int arrayLen;
	int flag=1;
	int messRight[32],messLeft[32];
	//IP_64(Message64,message64);//将字符串明文s转换成重排后的64位int数组 		
	for(int m=0;m<32;m++)
		messLeft[m]=Message64[m];
	for(int m=0;m<32;m++)
		messRight[m]=Message64[32+m];
	messageRightTo48(messRight,message48);			
	while(flag<=loop)
	{			
		DecryKey(key56,key48,flag);
		flag++;
	}	
	Xor(message48,key48,xorResult,48);
	message48To32(xorResult,message32);
	message32Rearrange(message32,messageRearrange32);
	Xor(messageRearrange32,messLeft,secondXorResult,32);
	for(int m=0;m<32;m++)
		cipher[m]=messRight[m];
	for(int m=32;m<64;m++)
		cipher[m]=secondXorResult[m-32]; //cipher[64]就是下一轮的输入 
	//IPR_64(cipher,ciphertext);  //cipher作为下一次的密文 
	for(int t=0;t<64;t++)
		Message64[t]=cipher[t];//下一轮的64 bit message ,there should be rearrangeMessage
}





void swap(int input[64],int output[64])
{
	int temp[32];
	for(int i=0;i<32;i++)
		temp[i]=input[i];
		
	for(int i=0;i<64;i++)
	{
		if(i<32)
			output[i]=input[i+32];
		else
			output[i]=temp[i-32];
	}
}

void encryption(char message[500],char key1[100])
{
	int handleMessage[N],key56[56];
	int keySpinResult[56];
	int cipher[64];
	int index=0,flag=0,len=64;
        int Message64[64],ciphertext[64],swapMessage[64],rearrangeMessage[64],secondRearrangeMessage64[64];
	pretreatment(message,key1,handleMessage,key56);
	int encryptionResult[number];
	int cnt=0,start,end,differ,result;
	int temp[8];

	while(index<64)
	{
		Message64[index%64]=handleMessage[index];
		if((index+1)%64==0)//每次取出handleMessage的64位进行处理 
	 	{
			IPR_64(Message64,rearrangeMessage);//在加密之前把64bit进行重排
			for(int t=0;t<16;t++)//每64 bit的message都要进行16轮的处理得到密文 
			{
				//cout<<"ROUND: "<<t+1<<endl;
				oneroundEncryption(rearrangeMessage,key56,t+1);//t表示轮数 
			}
			IPR_64(rearrangeMessage,secondRearrangeMessage64);
			swap(secondRearrangeMessage64,ciphertext);
			start=cnt;
			while(differ<64)//每次往encryptionResult数组放入64个元素
			{
				encryptionResult[cnt]=ciphertext[cnt%64];
				cnt++;
				differ++;		
			}
			differ=0;
		}		
		index++;
	}
	ofstream file("out.txt");
	for(int j=0;j<64;j++)
		file<<encryptionResult[j];
	file.close();
}
void decryption(int secretMessage[500],char key2[100])
{
	//cout<<"Start decrypting:(decryption():)"<<endl; 
	int ret;
	int len=0;
	int rearrangeMessage[64];
	int secretLeft[32],secretRight[32],message64[64];
	int keyTemp56[56];
	//----------对密钥进行处理 
	char keyEncry[65];
	int key64[64],key56[56],handleMessage[64];
	int result,index=0; 
	keyEncry[64]='\0';
	charTobit(key2,keyEncry);
	for(int k=0;k<64;k++)
		key64[k]=(int)(keyEncry[k]-48);
	key64To56(key64,key56); 
	for(int i=0;i<56;i++)
		keyTemp56[i]=key56[i];
	for(int i=0;i<500;i++)//求密文的长度 
	{
		if(secretMessage[i]!=-1)
			len++;
		else
			break;
	}
	int decryptionResult[len]; 
	int cnt=0,mark=0;;
	while(index<64)
	{
		handleMessage[index%64]=secretMessage[index]; 
		if((index+1)%64==0)//每次取出64位处理
		{
			IPR_64(handleMessage,rearrangeMessage); //先重排
			for(int i=15;i>=0;i--)
			{
				oneroundDecryption(rearrangeMessage,keyTemp56,i+1);
				for(int k=0;k<56;k++)
				{
					keyTemp56[k]=key56[k];
				}

			}
			IPR_64(rearrangeMessage,message64);//重排得到64bit明文 
			while(mark<64)
			{
				decryptionResult[cnt]=message64[cnt%64];
				cnt++;
				mark++;
			}
			mark=0;	
		}
		index++;
	}

	int flag=0;
	int temp[8];
	char str[len];//解密后的明文 
	while(flag<len)
	{
		temp[flag%8]=decryptionResult[flag];
		if((flag+1)%8==0)
		{			
			binaryTodecimal(temp,result,8);//先把二进制转换成十进制，再把十进制转换成字符  每8位二进制一转呢 
			//cout<<"result:"<<result-48<<endl;
			str[flag%8]=(char)(result-48);//str是转换后的字符 
		}
		flag++; 
	}
	cout<<"解密结果:"<<endl;
	
	for(int i=0;i<len/8;i++)
		cout<<str[i]<<endl;
} 



