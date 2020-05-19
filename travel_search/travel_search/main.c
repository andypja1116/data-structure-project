#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include "public_data_structure.h"

void load(void);//根据时刻表生成地图
void output_danger(int, int);
void limit_time(int, int, int);
void output_limit_time();

int pass_number = 0;//旅客数目
Tour passenger[20];
char* cityname[] = { "北京","上海","广州","哈尔滨","沈阳","天津","兰州","成都","贵阳","武汉" };

int main()
{
	FILE* fp;
	int select;
	int i,j;
	int flag = 0;//标记旅客是否存在
	int req;//表示旅客所选择的服务
	char name[10];
	clock_t hour;
	if ((fp= fopen("log.txt", "w")) == NULL)
	{
		exit(0);
	}
loop4:printf("当前系统时间为 第%d天 %d 时\n", ((clock() / CLOCKS_PER_SEC) / 10 / 24) + 1, ((clock() / CLOCKS_PER_SEC) / 10) % 24);
	printf("\n");
	printf("	 -------------------------------------------------------------\n");
	printf("   	                                                              \n");
	printf("   			            *欢迎您使用旅游查询系统*	              \n");
	printf("   	                                                              \n");
	printf("	 ------------------------当前城市列表-------------------------\n");

	for (i = 0; i < 10; i++)
	{
		printf("%2d->%-6s      ", i, cityname[i]);
		if ((i + 1) % 5 == 0)
			printf("\n");
	}
	printf("系统可以为您查询或规划您的旅行路线");

	load();

loop2:printf("\n请您选择所需要的服务\n");
	printf("清除屏幕请按0\n");
	printf("查询路线请按1\n");
	printf("查询状态请按2\n");
	printf("打开日志请按3\n");
	printf("退出系统请按4\n");
	scanf("%d", &req);
	getchar();
	if (req == 0)
	{
		system("cls");
		goto loop4;
	}
	else if (req == 1)
	{
		current_time = ((clock() / CLOCKS_PER_SEC) / 10)%24;
		printf("请输入您的姓名：\n");
		scanf("%s", passenger[pass_number].name);
		printf("\n请输入出发城市编号：\n");
		scanf("%d", &passenger[pass_number].start_city);
		printf("\n请输入目的城市编号：\n");
		scanf("%d", &passenger[pass_number].dest_city);
		printf("\n请选择旅行策略：\n");
		printf("风险最低请按1\n");
		printf("限时风险最低请按2\n");
		scanf("%d", &select);
			
		switch (select)
		{
		case 1:
			output_danger(passenger[pass_number].start_city, passenger[pass_number].dest_city);
			break;
		case 2:
			printf("请输入限制时间（小时）");
			scanf("%d", &lim_time);
			limit_time(passenger[pass_number].start_city, passenger[pass_number].dest_city, current_time);
			output_limit_time();
			break;
		default:
			break;
		}
		printf("\n");
		printf("系统已为您规划完成！\n");
		pass_number++;
		goto loop2;
	}
	else if (req == 2)
	{
	    printf("\n\n请输入您的姓名\n");
		scanf("%s", name);
		for (i = 0; i <= pass_number; i++)
		{
			if (!strcmp(name, passenger[i].name))
			{
				flag = 1;
				printf("已查询到旅客%s的状态如下：\n", passenger[i].name);
				hour = (clock() / CLOCKS_PER_SEC) / 10;
				if (hour <= passenger[i].state[1].leave_time)
				{
					printf("停留在城市%s\n", cityname[passenger[i].state[1].city_num]);
				}
				else
				{
					for (j = 2; j <= passenger[i].length; j++)
					{
						if (hour<passenger[i].state[j].arrive_time && hour>passenger[i].state[j - 1].leave_time)
						{
							printf("在城市%s和城市%s之间\n", cityname[passenger[i].state[j - 1].city_num], cityname[passenger[i].state[j].city_num]);
							switch (passenger[i].state[j - 1].leavestyle[0])
							{
							case 'C':
								printf("乘坐航班：");
								break;
							case 'T':
								printf("乘坐列车：");
								break;
							case 'A':
								printf("乘坐汽车：");
							default:
								break;
							}
							printf("%s\n", passenger[i].state[j - 1].leavestyle);
						}
						else if (hour >= passenger[i].state[j].arrive_time && hour <= passenger[i].state[j].leave_time)
						{
							if (j == passenger[i].length)
							{
								printf("已到达目的地%s\n",cityname[passenger[i].state[j].city_num]);
							}
							else
							{
								printf("停留在城市%s\n", cityname[passenger[i].state[j].city_num]);
							}
						}
					}
				}
				goto loop2;
			}
		}
		if (flag == 0)
		{
			printf("您输入的旅客不存在\n");
			goto loop2;
		}
	}
	else if (req == 3)
	{
		printf("日志文件已生成！");
	}
	else if (req == 4)
	{
		printf("感谢您的使用！下次再见！");
		exit(0);
	}
	fclose(fp);
	return 0;
}