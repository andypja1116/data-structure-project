#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"public_data_structure.h"

extern int pass_number;
extern Tour passenger[20];
extern char* cityname[];

void output_danger(int startnode, int destnode)
{
	int path[NUM_OF_CITY];
	int i, j, k,w = 1;
	int path_length;
	int trans_number;
	int start_time;
	int arrive_time;
	int start_city = -1;
	int arrive_city = -1;
	int sum_time = 0;
	int sum_cost = 0;
	int pre_arrive_time = 0;
	int start=0;
	double sum_danger_1 = 0;
	
	path[0] = destnode;
	j = destnode;
	i = startnode;
	k = 1;

	Current[startnode] = current_time;
	find_min_danger(startnode, destnode,Current[startnode]);

	while (j != i)
	{
		path[k] = lastnode[j];
		j = lastnode[j];
		k++;
	}
	path_length = k;

	for (i = path_length - 1; i > 0; i--)
	{
		start_city = path[i];
		arrive_city = path[i - 1];
		trans_number = trans_num[start_city][arrive_city];
		start_time = map[start_city][arrive_city][trans_number].start_time;
		arrive_time = map[start_city][arrive_city][trans_number].arrive_time;

		if (i == path_length - 1)
		{
			sum_time = sum_time + (start_time - current_time + 24) % 24;
			pre_arrive_time = start_time;
			start = map[start_city][arrive_city][trans_number].start_time;
		}

		printf("\n");
		
		switch (map[start_city][arrive_city][trans_number].name[0])
		{
		case 'C':
			printf("乘坐航班：");
			break;
		case 'T':
			printf("乘坐列车：");
			break;
		case 'A':
			printf("乘坐汽车：");
			break;
		default:
			break;
		}

		printf("%s   ", map[start_city][arrive_city][trans_number].name);
		printf("\n\t\t");
		printf("始发：");
		printf("[%d]：", start_city);
		output_city_name(start_city);
		printf(" %d时 ", start_time);
		printf("\t到达：");
		printf("[%d]：", arrive_city);
		output_city_name(arrive_city);
		printf(" %d时 ", arrive_time);
		printf("%6d元  \n", map[start_city][arrive_city][trans_number].cost);

		passenger[pass_number].state[w].leave_time = (start - Current[startnode] + 24) % 24 + (24 + start_time - pre_arrive_time) % 24;
		passenger[pass_number].state[w].arrive_time = (start - Current[startnode] + 24) % 24 + sum_time;
		strcpy(passenger[pass_number].state[w].leavestyle, map[start_city][arrive_city][trans_number].name);
		passenger[pass_number].state[w].city_num = start_city;
		w++;

		sum_cost = sum_cost + map[start_city][arrive_city][trans_number].cost;
		sum_time = sum_time + (24 + start_time - pre_arrive_time) % 24 + (24 + arrive_time - start_time) % 24;
		sum_danger_1 = sum_danger_1 + ((24 + start_time - pre_arrive_time) % 24) * output_city_danger(start_city) + ((24 + arrive_time - start_time) % 24) * output_city_danger(start_city) * output_tran_danger(map[start_city][arrive_city][trans_number].name[0]);
		pre_arrive_time = arrive_time;
	}
	passenger[pass_number].state[w].arrive_time = (start - Current[startnode] + 24) % 24 + sum_time;
	passenger[pass_number].state[w].leave_time = 99999999;
	passenger[pass_number].state[w].city_num = arrive_city;
	passenger[pass_number].length = w;

	printf("共需要%d小时\n", sum_time);
	printf("共花费%d元\n", sum_cost);
	printf("风险值为%.2lf\n", sum_danger_1);
}