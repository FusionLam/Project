#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define MaxSize 30
void Transfer(char *equation,int *A_B_C)
{
	int i = 0,j = 0;
	int element[3];
	int temp = 0;
	int transfer[100];
	element[0] = 0;															//存放方程A、B、C数值
	element[1] = 0;
	element[2] = 0;
	int m = 0;
	while(j<100)
	{
		transfer[j] = 0;
		j++; 
	}
	while(equation[i] != '\n')   											//遍历字符串
	{
		if((equation[i] == 'x' || equation[i] == 'X'))    					//识别到X
		{
			int power = 1;													//默认次方为1，只有两个可能
			if(i == 0)
			{
				transfer[m++] = 999;
				transfer[m++] = 1;										//x在首位
			}
			if(equation[i+1] == '1')
			{
				power = 1;
				i++;
			}
			else if(equation[i+1] == '2')
			{
				power = 2;
				i++;
			} 
			while(power>0)
			{
				transfer[m++] = 0;                     					//利用0哨兵值代替X
				power--;
			}
			i++;
			continue;
		}
		if(equation[i] == '+')										//识别到加号或是第一个元素情况下
		{
			transfer[m++] = 999;					
			if(isdigit(equation[i+1]))										//把数组内数字转换成int类型
			{
				int reg[4];
				int count = 0;
				int k = 0;
				temp = 0;
				i++;
				while(isdigit(equation[i]))
				{
					reg[k] = equation[i] - '0';
					k++;
					count++;
					i++;													//i会指向不是数字后的非数字元素
				}
				while(count > 0)
   				{
					k = 0;
					temp += reg[k] * (pow(10,count-1)); 
					count--;
					k++;
				} 
				transfer[m++] = temp;
				if(equation[i] == 'X' ||equation[i] == 'x') 				//x前系数不为1
				{
					continue;
				}
			}
			else if(equation[i+1] == 'X' ||equation[i+1] == 'x')				//加号后的x系数为1
			{
				transfer[m++] = 1;
				i++;
			}	
		}
		else if(isdigit(equation[0]) && i == 0)
		{
			transfer[m++] = 999;
			temp = 0;
			if(isdigit(equation[i]))										//把数组内数字转换成int类型
			{
				int reg[4];
				int count = 0;
				int k = 0;
				for(int l = 0;l < 4;l++)
				{
					reg[l] = 0;
				}
				while(isdigit(equation[i]))
				{
					reg[k++] = equation[i] - '0';
					count++;													
					i++;													//i会指向不是数字后的非数字元素
				}
				while(count > 0)
				{
					k = 0;
					temp += reg[k] * (pow(10,count-1)); 
					count--;
					k++;
				}
			}
			else if(equation[i] == 'X' ||equation[i] == 'x')				//加号后的x系数为1
			{
				transfer[m++] = 1;
			}
			transfer[m++] = temp;
		}
		else if(equation[i] == '-')
		{
			transfer[m++] = 999;					
			if(isdigit(equation[i+1]))
			{
				int reg[4];
				int count = 0;
				int k = 0;
				temp = 0;
				i++;
				while(isdigit(equation[i]))
				{
					reg[k] = equation[i] - '0';
					k++;
					count++;
					i++;
				}
				while(count > 0)
				{
					k = 0;
					temp += reg[k] * (pow(10,count-1)); 
					count--;
					k++;
				}
				transfer[m++] = -temp;	
				if(equation[i] == 'X' ||equation[i] == 'x') 				//x前系数不为1
				{
					continue;
				}
			}
			else if(equation[i+1] == 'X' ||equation[i+1] == 'x')				//加号后的x系数为-1
			{
				transfer[m++] = -1;
				i++;
			}	
		}	
	}
	transfer[m] = -999;    //标记结束
	int n = 0;
	while(transfer[n] != -999)
	{
		if(transfer[n] == 999)   //检测为一个项   999 1 999 1 0 999 2 999 2 0 0 -999
		{
			n++;
			int temp = transfer[n++];      //n+1
			int power = 0;
			if(transfer[n] == 0)
			{
				while(transfer[n] == 0)
				{
					power++;
					n++;					// n指向最后一个0后面一个项
				}
			}
			if(power == 0)
			{
				element[2] += temp;
				continue;
			}
			else if(power == 1)
			{
				element[1] += temp;
				continue;
			}
			else if(power == 2)
			{
				element[0] += temp;
				continue;
			}
		}
	}
	A_B_C[0] = element[0];
	A_B_C[1] = element[1];
	A_B_C[2] = element[2];
}
void ComPuting()
{
	char equation[30];
	double A = 0,B = 0,C = 0;
	int A_B_C[3];
	double result = 0;
	system("cls");
	printf("****************************************************\n");
	printf("***************欢迎来到解方程计算系统***************\n");
	printf("****************************************************\n");
	printf("----------------------------------------------------\n");
	printf("|                    请输入方程                    |\n");
	printf("----------------------------------------------------\n");
	while(getchar() != '\n');
	fgets(equation,sizeof(equation),stdin);
	Transfer(equation,A_B_C);
	A = A_B_C[0];
	B = A_B_C[1];
	C = A_B_C[2];
	if(A == 0 && B == 0)		
	{
		result = C;
		printf("%.0f",result);
	}
	else if(A != 0)
	{
		double delta = 0;
		delta = pow((int)B,2) - (4 * (int)A * (int)C);
		if(delta == 0)
		{
			result = (-B + sqrt(delta)) / (2 * A);
			if(floor(result) != result)
			{
				printf("[-%.0f ± √%.0f]/2*%.0f",B,delta,A);
			}
			printf("%.0f",result);
		}
		else if(delta > 0)
		{
			double temp1 = 0,temp2 = 0;
			temp1 = (-B + sqrt(delta)) / (2 * A);
			temp2 = (-B - sqrt(delta)) / (2 * A);
			if(floor(temp1) != temp1)
			{
				printf("[-%.0f + √%.f]/2*%.0f\n",B,delta,A);
			}
			if(floor(temp2) != temp2)
			{
				printf("[-%.0f - √%.f]/2*%.0f",B,delta,A);
			}
			else
			{
				printf("%.0f %.0f",temp1,temp2);
			}
		}
		else if(delta < 0)
		{
			printf("德尔塔小于0算集贸");
		}
	}
	else if(A == 0 && B != 0)
	{
		result = -C / B;
		if(floor(result) != result)
		{
			printf("-%.0f/%.0f",floor(C),floor(B));
		}
		else if(floor(result) == result)
		{
			printf("%.0f",result);
		}
	}
}
int Instruction()
{
	system("cls");
	int user_key;
	printf("****************************************************\n");
	printf("***************欢迎来到解方程计算系统***************\n");
	printf("****************************************************\n");
	printf("----------------------------------------------------\n");
	printf("|                     使用方法                     |\n");
	printf("----------------------------------------------------\n");
	printf("----------------------------------------------------\n");
	printf("|输入你要解的方程，用x代替未知量，如果要表示次方， |\n");
	printf("|直接在x后面加不大于2的数字，输入后按回车,系统会使 |\n");
	printf("|运算改方程，输出结果。                            |\n");
	printf("----------------------------------------------------\n");
	printf("请输入1返回:");
	scanf("%d",&user_key);
	return user_key;
}
int MainMeau()
{
	system("cls");
	int instruction_seq;  
	printf("****************************************************\n");
	printf("***************欢迎来到解方程计算系统***************\n");
	printf("****************************************************\n");
	printf("----------------------------------------------------\n");
	printf("|                   1.开始计算                     |\n");
	printf("|                   2.使用说明                     |\n");
	printf("|                   3.退出系统                     |\n");
	printf("----------------------------------------------------\n");
	printf("请输入指令序号:");
	scanf("%d",&instruction_seq);
	return instruction_seq;
}
int main()
{
	int instruction_seq = MainMeau();
	switch (instruction_seq) {
	case 1:
		ComPuting();
		break;
	case 2:
		int user_key = Instruction();
		if(user_key == 1) main();
		else break;
	case 3:
		exit(0);
	default:
		break;
	}
	return 0;
}

