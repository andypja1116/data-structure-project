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
			printf("�������ࣺ");
			break;
		case 'T':
			printf("�����г���");
			break;
		case'A':
			printf("����������");
			break;
		default:
			break;
		}

		printf("%s   ", map[start_city][arrive_city][transport].name);
		printf("\n\t\t");
		printf("ʼ����");
		printf("[%d]��", start_city);
		output_city_name(start_city);
		printf(" %dʱ ", start_time);
		printf("\t���");
		printf("[%d]��", arrive_city);
		output_city_name(arrive_city);
		printf(" %dʱ \n", arrive_time);
	}
	printf("�ܹ���Ҫ%dСʱ\n", plan.min_time);
	printf("����ֵΪ%.2lf\n", plan.min_danger);
}