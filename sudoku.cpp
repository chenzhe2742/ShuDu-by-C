#include<stdio.h>
#include<string.h>
/**
error=1ʱ�޽⡢����
progress=1ʱ��ʾ�н��� 
num_cycle ��ʾѭ������ 
num_error ��ʾ�������
num_guess ��ʾ�������
**/ 
int r[9][9][11],s[63][9][9][11];
int i,j,k,m,x,y,z,error=0,progress=0,num_cycle=0,num_guess=0,num_error=0;

void entry(void) 
{
	printf("Please enter the question of sudoku\n");
	/**
	char t[100];
	for(i=0;i<9;i++)
	{
		printf("Row[%d] : ",i+1);
    	scanf("%s", t);
    	j=0;
		for(int b=0; b<100&&j<9; b++)
		{
			if(t[b]>='0'&&t[b]<='9')
			{
            	r[i][j][0]=t[b]-'0';
            	j++;
			}
		}
	}
	**/
//	/**
	char t[81];
	strcpy(t,"300000010000184003060000200005002400049005008000000070100030000000700086408200000");
	for(i=0; i<81; i++)
	{
		if(t[i]>='0'&&t[i]<='9')
		{
        	r[i/9][i%9][0]=t[i]-'0';
		}
	}
//	**/
}

void exit(void)
{
	printf("\n");
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			printf("%d ",r[i][j][0]);
			if(j%3==2)
				printf("\t");
		}
		printf("\n");
		if(i%3==2)printf("\n");
	}
}

int space(void)//����1��ʾ�п�λ 
{
	int s=0;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			if(r[i][j][0]==0) 
				s=1;
		}
	}
	return s;
}

int check(void)//����1��ʾ������� 
{
	int c=0;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			z=0;
			for(k=0;k<10;k++)
			{
				if(r[i][j][k]==0)
				z++;
			}
			if(z==10)
				c=1;
		}
	}
	return c;
}

void step1(void)//����ά,����ֵ 
{
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			if(r[i][j][0]==0)
				for(k=0;k<=9;k++)
				{
					r[i][j][k]=k;
				}
			else
				for(k=1;k<=9;k++)
				{
					r[i][j][k]=0;
				}
			r[i][j][10]=(3*(i/3)+j/3+1);//�־Ź���	
		}
	}
}

void step2(void)//�ж���û�н���   error=1ʱ�޽⡢����   progress=1ʱ��ʾ�н��� 
{
	error=0;
	progress=0;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{	
			if(r[i][j][0]==0)
			{
				m=0;z=0;
				for(k=1;k<=9;k++)
				{
					if(r[i][j][k]==0)
						z++;
					else
						m=k;
				}
				if(z==8)
				{
					progress=1;
					r[i][j][0]=r[i][j][m];
					r[i][j][m]=0;
				}
				else if(z==9) 
					error=1;
			}
		}
	}
	for(i=0;i<9;i++)//�жϸ�ֵ��û�г��� 
	{
		for(j=0;j<9;j++)
		{
			if(r[i][j][0]!=0)
			{
				for(x=0;x<9;x++)
				{
					if(x!=i&&r[i][j][0]==r[x][j][0])
						error=1;
					if(x!=j&&r[i][j][0]==r[i][x][0])
						error=1;
					for(y=0;y<9;y++)
					{
						if(x!=i&&y!=j&&r[x][y][10]==r[i][j][10]&&r[i][j][0]==r[x][y][0])
						error=1;
					}
				}
			}
		}
	}
}

void step3(void)//���У��У����ж� ����ֵ 
{
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			if(r[i][j][0]==0)
			{
				for(x=0;x<9;x++)
				{
					r[i][j][r[x][j][0]]=0;
					r[i][j][r[i][x][0]]=0;
					for(y=0;y<9;y++)
					{
						if(r[x][y][10]==r[i][j][10]&&r[x][y][0]!=0)
						r[i][j][r[x][y][0]]=0;
					}
				}	
			}
		}
	}
}

void step4(void)//����ǰ��ֵ ������ 
{
	printf("�����%d�μ��裡\n",num_guess+1);	
	num_guess++;
	for(i=0;i<9;i++)//�������� 
	{
		for(j=0;j<9;j++)
		{
			for(k=0;k<11;k++)
			{
				s[num_guess][i][j][k]=r[i][j][k];
			}
		}
	}
	
	for(i=0;i<9;i++)//���� 
	{
		for(j=0;j<9;j++)
		{
			if(r[i][j][0]==0)
			{
				for(k=1;k<10;k++)
				{
					if(r[i][j][k]!=0)
					{
						r[i][j][0]=r[i][j][k];
						r[i][j][k]=0;
						s[num_guess][i][j][k]=0;
						printf("����ļ�����r[%d][%d]=%d\n",i+1,j+1,r[i][j][0]); 
						return ;
					}	
				}
			}
		}
	}
}

void step5(void)//�����ֵ 
{
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			for(k=0;k<11;k++)
			{
				r[i][j][k]=s[num_guess][i][j][k];
			}
		}
	}
	num_guess--;
	num_error++;
	printf("������%d�Σ�\n",num_error);
}

void step6(void)//���� 
{
	if(error==1)
	{
		step5();//�����ֵ 
		step4();
	}
	else if(progress==0)
	{
		step4();
	}
}

int main()
{
	entry();
	exit();
	step1();
	while(space()==1)
	{
		step3();
		step2();
		num_cycle++;
		printf("s:%d\t",num_cycle);
		printf("error=%d\t",error);
		printf("progress=%d\t",progress);
		printf("num_guess=%d\n",num_guess);
		step6();
		if(check()==1)
			num_guess--;
	}
	exit();	
}



