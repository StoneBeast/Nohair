#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
// 0:�գ�1����(��ʾ��)��2���ף� 
void Person_Person(int z);															//**************** 
void Person_Computer_ai();
void Person_Computer(int z);															//**************** 
void DrawQipan(int input[19][19]);												//**************** 
void ContinueGame();
void Menu();																	//******************
int  IsFull(int input[19][19]);													//********************
int  IsWin(int input[19][19]);													//*********************
void Surr(int flag,int input[19][19]);											//*********************
void Regret(int input[19][19],int rx_1,int ry_1,int rx_2,int ry_2);				//*******************
void Save(int input[19][19],int flag);											//***************
void End(int flag);																//******************
int  Check(int input[19][19],int x,int y,int flag);								//****************
int  CheckCom(int input[19][19],int x,int y);									//******************
void Randm(int Set[2],int x);													//********************
void Author();																	//*************************
void GetTime(char Time[50]);													//****************
int  Count(int input[19][19],int flag);											//********************** 

int inputQJ[19][19]={0};

int main()
{
	Menu();
	
	return 0;
}

void Menu()
{
	int n,input[19][19]={0};
	
	printf("\t~������~\n");
	printf("1��˫��ģʽ\n");
	printf("2������ģʽ�����ǰ棩\n");
	printf("3������ģʽ��ai�棬��ʱ���У�\n");
	printf("4��������Ϸ\n");
	printf("5����������Ϣ\n");
	printf("6���˳���Ϸ\n");
	
	printf("��ѡ��1~6����");
	scanf("%d",&n);
	
	system("cls");
	
	if(n==1)
		Person_Person(0);
	
	else if(n==2)
		Person_Computer(0);	
	
	else if(n==3)
		{
			printf("��ʱ���С�����\n");
			Menu();
		}
		
	else if(n==4)
		ContinueGame();
	
	else if(n==5)
		Author();
	
	else if(n==6)
	{
		printf("\n��лʹ�ã���");
		exit(0);
	}	
		
}

void DrawQipan(int input[19][19])
{
	printf("x��y�������롰10086�������ɻ���\nx��y�������롰10010�����ɴ���\nx��y�������롰10000����������\n�������֣���Ļ����ʾ��ɫ��\nʹ�ô浵������ȷ���ó���ͬĿ¼�´��ڡ�tem���ļ���\n"); 
	int i,j;
	
	for(i=0; i<19; i++)
	{
		for(j=0; j<19; j++)
		{
			if(input[i][j] == 0)
			{
				if(i==0 && j==0)
					printf("����");
				else if(i==0 && j==18)
					printf("��\t1");
				else if(i==18 && j==0)
					printf("����");
				else if(i==18 && j==18)
					printf("��\t19");
				else if(i==0 && j!=0 && j!=18)
					printf("�ש�");
				else if(i==18 && j!=0 && j!=18)
					printf("�ߩ�");
				else if(j==0 && i!=0 && i!=18)
					printf("�ǩ�");
				else if(j==18 && i!=0 && i!=18)
					printf("��\t%d",i+1);
				else 
					printf("�贈");
			}
			else if(input[i][j] == 1)
				printf("��");
			
			else if(input[i][j] == 2)
				printf("��");
		}
		printf("\n");
	}
	
	for(j=0; j<19; j++)
	{
		printf("%-2d",j+1);
		if(j==18)
			printf("\n");
	}	
}


void Person_Person(int z)
{
	int i,j,x,y,n,flag=0,rx_1=0,ry_1=0,rx_2=0,ry_2=0;
	int input[19][19]={0};

	if(z==1)
	{
		for(i=0;i<19;i++)
		{
			for(j=0;j<19;j++)
			{
				input[i][j]=inputQJ[i][j];
			}
		}
	}	
		
	DrawQipan(input);
	while(1)
	{
		if(Count(input,flag)==2)
			printf("P2:\n");
		else	
			printf("P1:\n");
		printf("������x���꣺");
		scanf("%d",&x);
		
		printf("������y���꣺");
		scanf("%d",&y);
		
	/*	if(Count(input,flag)==2)
		{
			
		}*/
	
		while(1)
		{
			if(Check(input,x,y,flag)==1)
				break;
			else if(Check(input,x,y,flag)==2)
			{
				Regret(input,rx_1,ry_1,rx_2,ry_2);
				system("cls");
				DrawQipan(input);
				
				if(Count(input,flag)==2)
					printf("P2:\n");
				else		
					printf("P1��\n��������������x���꣺");
			
				scanf("%d",&x);
				
				printf("��������������y���꣺");
				scanf("%d",&y);
			}
			else if(Check(input,x,y,flag)==3)
				{
					printf("���̳ɹ��󽫷������˵���\n");
					Save(input,flag);
				}
				
			else
			{


				printf("����x���꣺");
				scanf("%d",&x);
				
				printf("����y���꣺");
				scanf("%d",&y);
			}
				
		}
	
		
		x=x-1;
		y=y-1;
		
		rx_1=y;	//��¼������������ 
		ry_1=x;//
		if(Count(input,flag)==2)
			input[y][x] = 2;
		else
			input[y][x] = 1;
		
		system("cls");
		DrawQipan(input);
		
		if(IsFull(input) ==1)
			End(flag);

		if(IsWin(input) == 1)
			End(flag);
		
		system("cls");
		
		DrawQipan(input);
		
		//*********************************p2***************************************
		if(Count(input,flag)==1)
			printf("P1:\n");
		else
			printf("P2:\n");
			
		printf("������x���꣺");
		scanf("%d",&x);
		printf("������y���꣺");
		scanf("%d",&y);
		
		while(1)
		{
			if(Check(input,x,y,flag)==1)
				break;
			
			else if(Check(input,x,y,flag)==2)
			{
				Regret(input,rx_1,ry_1,rx_2,ry_2);
				system("cls");
				DrawQipan(input);
				
				
				if(Count(input,flag)==2)
					printf("P1:\n");
				else
					printf("P2��\n��������������x���꣺");
			
				scanf("%d",&x);
				
				printf("��������������y���꣺");
				scanf("%d",&y);
			}
			else if(Check(input,x,y,flag)==3)
				{
					printf("���̳ɹ��󽫷������˵���\n");
					Save(input,flag);
				}
				
			else
			{
				
				printf("����x���꣺");
				scanf("%d",&x);
				
				printf("����y���꣺");
				scanf("%d",&y);
			}
			
		}
		
		x=x-1;
		y=y-1;
		
		rx_2=y;
		ry_2=x;
		
		
		if(Count(input,flag)==1)
			input[y][x] = 1;
		else
			input[y][x] = 2;
		
		if(IsFull(input) ==1)
			End(flag);

		if(IsWin(input) == 2)
			End(flag);
		
		system("cls");
		
		DrawQipan(input);
	}
}

void Person_Computer(int z)	
{
	int x,y,n,i,j,flag=1,rx_1,ry_1=0,rx_2=0,ry_2=0;
	int Set[2]={0};
	int input[19][19]={0};
	
	if(z==1)
	{
		for(i=0;i<19;i++)
		{
			for(j=0;j<19;j++)
			{
				input[i][j]=inputQJ[i][j];
			}
		}
	}	
	
	DrawQipan(input);
	while(1)
	{
		printf("P1:\n");
		printf("������x���꣺");
		scanf("%d",&x);
		
		printf("������y���꣺");
		scanf("%d",&y);
	
	
		while(1)
		{
			if(Check(input,x,y,flag)==1)
				break;
			
			else if(Check(input,x,y,flag)==2)
			{
				Regret(input,rx_1,ry_1,rx_2,ry_2);
				system("cls");
				DrawQipan(input);
				
				printf("P1��\n��������������x���꣺");
				scanf("%d",&x);
				
				printf("��������������y���꣺");
				scanf("%d",&y);
			}
			else if(Check(input,x,y,flag)==3)
				{
					printf("���̳ɹ��󽫷������˵���\n");
					Save(input,flag);
				}
			
			else
			{

				printf("����x���꣺");
				scanf("%d",&x);
				
				printf("����y���꣺");
				scanf("%d",&y);
			}
				
		}
		
		x=x-1;
		y=y-1;
		
		rx_1=y; 
		ry_1=x;
		
		input[y][x] = 1;
		
		system("cls");
		DrawQipan(input);
		
		if(IsFull(input) ==1)
			End(flag);

		if(IsWin(input) == 1)
			End(flag);
		
		system("cls");
		
		
		//******************************************rz**************************************
		Randm(Set,x);
		x=Set[0];
		y=Set[1];
		
		
		while(1)
		{
			if(CheckCom(input,x,y)==1)
				break;
			else
			{
				Randm(Set,x);
				x=Set[0];
				y=Set[1];
			}
			
		}
		
		x=x-1;
		y=y-1;
		
		rx_2=y;
		ry_2=x;
		
		input[y][x] = 2;
		
		if(IsFull(input) ==1)
			End(flag);
		
		if(IsWin(input) == 2)
		{
			End(flag);
		}
		
		system("cls");
		
		DrawQipan(input);
	}
}

int IsFull(int input[19][19])// 1:���ˣ�0:û���� 
{
	int i,j,result=1;
	for(i=0;i<19;i++)
	{
		for(j=0;j<19;j++)
		{
			if(input[i][j] != 0)
				result=0;
		}
	}
	
	if(result == 1)
		if(IsWin(input) == 0)
			printf("�����ˣ��������忪��\n");
	
	return result;
}

int IsWin(int input[19][19])
{
	int i,j,n,flag=0,result=0;//2����ʤ����1:��ʤ��;0:��ʤ�� 
	
	for(i=0;i<19;i++)
	{
		for(j=0;j<19;j++)
		{
			if(j<=14)
				for(n=1;n<5;n++)
				{
					if(input[i][j]==input[i][j+n] && input[i][j] != 0)
						flag++;
					
					if(flag==4 && input[i][j]==1)
						result=1;
					else if(flag==4 && input[i][j]==2)
						result=2;	
				}	
	
		flag=0;
	
			if(i<=14)
				for(n=1;n<5;n++)
				{
					if(input[i][j]==input[i+n][j] && input[i][j] != 0)
						flag++;
					
					if(flag==4 && input[i][j]==1)
						result=1;
					else if(flag==4 && input[i][j]==2)
						result=2;		
				}
				
		flag=0;
				
			if(i<=14 && j<=14)
			{
				for(n=1;n<5;n++)
				{
					if(input[i][j]==input[i+n][j+n] && input[i][j] != 0)
						flag++;
					
					if(flag==4 && input[i][j]==1)
						result=1;
					else if(flag==4 && input[i][j]==2)
						result=2;	
				}
			}	
			
			
		}
		
	}
	
	if(result == 1)
		printf("�����ʤ��\n");
	if(result == 2)
		printf("���ӻ�ʤ��\n");
	
	return result;
	
}
void End(int flag)
{
	int n;
	printf("1������һ��\n2���������˵�\n3��ֱ���˳�\n");
	
	printf("��ѡ��(1~3)��");
	scanf("%d",&n);
	
	if(n==1)
		{
			system("cls");
			if(flag==0)
				Person_Person(0);
			if(flag==1)
				Person_Computer(0);
		}
		
	else if(n==2)
	{
		system("cls");
		Menu();
	}
		

	else if(n==3)
	{
		system("cls");
		printf("��лʹ�ã�");
		exit(0);
	}	
		
	else
	{
		printf("��ҪϹ���밡���쵰����\n");
		End(flag);
	}
}

int Check(int input[19][19],int x,int y,int flag)//1:�������룻0���쳣���룻 
{
	int result = 1;
	
	if(x==10000 || y== 10000)
		Surr(flag,input);
	
	else if(x==10086 || y==10086)
		result=2;
	else if(x==10010 || y==10010)
		result=3;
	
	else if(x<1 || x>19 || y<1 || y>19)
	{
		printf("û����һ�񰡣��쵰���������������䣡\n");
		result=0;
	}

	else if(input[y-1][x-1] != 0)
	{
		printf("�п��ǹ����Ǽ��𣿣���һ���Ѿ���ռ�ˣ���\n");
		result=0;
		
	}		

	return result;
}
int CheckCom(int input[19][19],int x,int y)
{
	int result = 1;
	
	if(x<1 || x>19)
		result=0;
	
	if(y<1 || y>19)
		result=0;
	
	else if(input[y-1][x-1] != 0)
		result=0;
	
	return result;
}

void Randm(int Set[2],int x)
{
	int t,result;
	srand(time(NULL)+x);
	
	Set[0]=(rand()%19)+1;
	Set[1] = (rand()%19)+1;
}

void Surr(int flag,int input[19][19])
{
		
	if(Count(input,flag)==1)
	{
		printf("P1������Ͷ������P2�����ӣ���ʤ��\n");
		End(flag);
	}
	else if(Count(input,flag)==2)
	{
		printf("P1������Ͷ������P2�����ӣ���ʤ��\n");
		End(flag);
	}
		
	
	if(flag==1)//�˻�
	{
		printf("���Ͷ�������ǽ���ʤ��\n");
		End(flag);
	} 
}

void Author()
{
	int n;
	
	printf("���ߣ�    ����ʯ��\n");
	printf("�������ڣ�2021.01.xx\n");
	printf("�汾�ţ�  1.0 Beta\n");
	printf("ʹ�ô浵������ȷ���ó���ͬĿ¼�´��ڡ�tem���ļ���.\n");
	printf("֮������ɾ���浵�Ĺ���......\n");
	printf("ai�˻����ڹ�˼�У��п��ܻ���֮�����.....\n");
	
	printf("\n���� 1 �Է������˵��������� 0 ֱ���˳���");
	scanf("%d",&n);
	
	system("cls");
	
	while(1)
	{
		if(n==1)
			Menu();
		else if(n==0)
		{
			printf("\n��лʹ�ã���\n");
			exit(0);
		}	
		else
		{
			printf("��Ҫʲô���������䰡ι��\n");
			
			printf("\n���� 1 �Է������˵��������� 0 ֱ���˳���");
			scanf("%d",&n);
			
			system("cls");
		}	
	}		
	
}

void Regret(int input[19][19],int rx_1,int ry_1,int rx_2,int ry_2)
{
	input[rx_1][ry_1]=0;
	input[rx_2][ry_2]=0;
}

void ContinueGame()										//****************************************************************************************
{
	char ch,temp[200],key[2],addr[100];
	FILE *fp,*fp_p;
	int n,sin,ad,i,j,k,flag;
	fp=fopen("./tem/AllData.txt","r");
	if(fp==NULL)
	{
		system("cls");
		printf("���ļ�ʧ�ܣ����������˵���\n");
		Menu();
	}

	printf("�浵��Ϣ��\n");
	while(!feof(fp))
	{
		ch=fgetc(fp);
		putchar(ch);
	}
	
	printf("���������ѡ��浵��");
	scanf("%d",&n);
	
	rewind(fp);
	
	while(!feof(fp))
	{
		 fseek(fp,1L,1);
		 
		 fscanf(fp,"%d",&sin);
		 
		 if(n==sin)//�ҵ����� 
		 {
		 	system("cls");
		 	printf("���ڴ򿪴浵.....\n");
		 	
		 	while(1)
		 	{
		 		key[0]=fgetc(fp);
			 	key[1]=fgetc(fp);
			 	
			 	if(key[0]=='v' && key[1]=='P')				//�ж���Ϸ���� 
			 		flag=0;						
			 	else if(key[0]=='v' && key[1]=='E')		//
			 		flag=1;
			 		
			 	else if(key[0]=='.' && key[1]=='/')     //�ҵ���ַ 
			 	{
			 		strcpy(addr,key);
			 		for(i=2;;i++)
			 		{
			 			addr[i]=fgetc(fp);
			 			if(addr[i-3]=='.' && addr[i-2]=='t' && addr[i-1]=='x' && addr[i]=='t')
			 			{
			 				break;
						}
					}
			 		
			 		fp_p=fopen(addr,"r");
			 		if(fp_p==NULL)
	                {
	                    system("cls");
	                	printf("���ļ�ʧ�ܣ����������˵���\n");
	                	Menu();
                	}
			 		
			 		for(j=0;j<19;j++)
			 		{
			 			for(k=0;k<19;k++)
			 			{
			 				fscanf(fp_p,"%d",&inputQJ[j][k]);
						}
					}
					
					fclose(fp_p);	//�����ַ��������
					
					if(flag==0)				//���� 
					{
						Person_Person(1);
					}
					else if(flag==1)		//�˻� 
					{
						Person_Computer(1);	
					}
					 
				}
				
				fseek(fp,-1L,1);
			}
		 		 	
		 }
		 
		 else
		 {
		 	fgets(temp,200,fp);
		 }
	}
	
	fclose(fp); 
}														//*****************************************************************************************

void Save(int input[19][19],int flag)
{
	char Time[50],addr[50],fname[50],all[100],mode[3];
	GetTime(Time);
	FILE *fp_a,*fp_p;
	char ch;
	int i,j,n=0;
	
	if(flag==0)
		strcpy(mode,"PvP");
	else if(flag==1)
		strcpy(mode,"PvE");
	
	printf("������Ҫ�洢����Ϸ�浵����Ե�ַ����./***/*** ����ʽ�洢�����Ƽ� ./tem ����");
	scanf("%s",addr);
	while(1)
	{
		if(addr[0] =='.' && addr[1] == '/')
			break;
			
		else
		{
			printf("�밴Ҫ�������ַ��ʽ!"); 
			printf("������Ҫ�洢����Ϸ�浵����Ե�ַ����./***/*** ����ʽ�洢����");
			scanf("%s",addr);
		}

	}
	printf("������浵���ƣ�������չ��,�������򸲸Ǿɴ浵����");
	scanf("%s",fname);
	
	strcpy(all,strcat(addr,"/"));
	strcpy(all,strcat(all,fname));
	
	fp_p = fopen(all,"w");
	if(fp_p==NULL)
   {
	    system("cls");
	    printf("���ļ�ʧ�ܣ����������˵���\n");
	   	Menu();
    }
	
	for(i=0;i<19;i++)
	{
		for(j=0;j<19;j++)
		{
			fprintf(fp_p,"%d  ",input[i][j]);
		}
		fprintf(fp_p,"\n");
	}
	
	fclose(fp_p);
	
	fp_a=fopen("./tem/AllData.txt","a+");
 	if(fp_a==NULL)
    {
	    system("cls");
	    printf("���ļ�ʧ�ܣ����������˵���\n");
	    Menu();
    }
	
	
	while(!feof(fp_a))
	{
		ch=fgetc(fp_a);
		if(ch=='#')
		{
			n=n+1;
		}
	}
	
	fprintf(fp_a,"#%d��  �浵���ƣ�%s\t��Ϸģʽ��%s\t�浵λ�ã�%s\t�浵ʱ�䣺%s",n,fname,mode,all,Time);
	
	fclose(fp_a);
	
	system("cls");
	
	Menu();
}

void GetTime(char Time[50])
{
    time_t rawtime;
    struct tm *info;
 
    time( &rawtime );
 
    info = localtime( &rawtime );
	
	strcpy(Time,asctime(info));
}

int Count(int input[19][19],int flag)
{
	int ConB=0,ConW=0,i=0,j=0,result=0;
	
	for(i=0;i<19;i++)
		{
			for(j=0;j<19;j++)
			{
				if(input[i][j]==1)
					ConW++;
				else if(input[i][j]==2)
					ConB++;
					
			}
		}
		
	
	if(flag==0)//���� 
	{
		
		if(ConB==ConW)//������ 
			result=1;

		else if((ConB+1)==ConW)//������ 
			result=2;
		
	}
	if(flag==1)//�˻�
	{
		if(ConB==ConW)//������ 
			result=3;

		else if((ConB+1)==ConW)//������ 
			result=4;
		
	} 
	
	return result;
}
