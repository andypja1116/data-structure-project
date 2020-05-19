#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"public_data_structure.h"

extern Plan plan;
extern char* cityname[];

void output_limit_time()
{
	int i;
	int transport;
	int start_city = -1;
	int arrive_city = -1;
	int start_time;
	int arrive_time;

	for (i = 0; plan.porder[i+1] != -1; i++)
	{
		start_city = plan.porder[i];
		arrive_city = plan.porder[i + 1];
		transport = plan.ptrans[arrive_city];
		start_time = map[start_city][arrive_city][transport].start_time;
		arrive_time = map[start_city][arrive_city][transport].arrive_time;

		printf("\n");

		switch (map[start_city][arrive_city][transport].name[0])
		{
		case 'C':
			printf("乘坐航班：");
			break;
		case 'T':
			printf("乘坐列车：");
			break;
		case'A':
			printf("乘坐汽车：");
			break;
		default:
			break;
		}

		printf("%s   ", map[start_city][arrive_city][transport].name);
		printf("\n\t\t");
		printf("始发：");
		printf("[%d]：", start_city);
		output_city_name(start_city);
		printf(" %d时 ", start_time);
		printf("\t到达：");
		printf("[%d]：", arrive_city);
		output_city_name(arrive_city);
		printf(" %d时 \n", arrive_time);
	}
	printf("总共需要%d小时\n", plan.min_time);
	printf("风险值为%.2lf\n", plan.min_danger);
}