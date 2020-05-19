#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "public_data_structure.h"

void output_city_name(int city_number)
{
	switch (city_number)
	{
	case 0:
		printf("北京");
		break;
	case 1:
		printf("上海");
		break;
	case 2:
		printf("广州");
		break;
	case 3:
		printf("哈尔滨");
		break;
	case 4:
		printf("沈阳");
		break;
	case 5:
		printf("天津");
		break;
	case 6:
		printf("兰州");
		break;
	case 7:
		printf("成都");
		break;
	case 8:
		printf("贵阳");
		break;
	case 9:
		printf("武汉");
		break;
	default:
		break;
	}
}

double output_city_danger(int city_number)
{
	switch (city_number)
	{
	case 0:
		return 0.9;
		break;
	case 1:
		return 0.9;
		break;
	case 2:
		return 0.5;
		break;
	case 3:
		return 0.5;
		break;
	case 4:
		return 0.5;
		break;
	case 5:
		return 0.9;
		break;
	case 6:
		return 0.2;
		break;
	case 7:
		return 0.2;
		break;
	case 8:
		return 0.2;
		break;
	case 9:
		return 0.9;
		break;
	default:
		break;
	}
}

int output_tran_danger(char a)
{
	switch (a)
	{
	case 'C':
		return 9;
		break;
	case 'T':
		return 5;
		break;
	case 'A':
		return 2;
		break;
	default:
		break;
	}
}

int tool_num(int start, int finish,int current_time)
{
	int m, tool=-1;
	double temp;

	if (map[start][finish][0].cost < INFINITY)
	{
		temp = (((map[start][finish][0].arrive_time - map[start][finish][0].start_time + 24) % 24) * output_city_danger(start) * output_tran_danger(map[start][finish][0].name[0]) + ((map[start][finish][0].start_time - current_time + 24) % 24) * output_city_danger(start));
		tool = 0;
		for (m = 1; m < MAX_NUM&&map[start][finish][m].cost < INFINITY ; m++)
		{
			if ((((map[start][finish][m].arrive_time - map[start][finish][m].start_time + 24) % 24) * output_city_danger(start) * output_tran_danger(map[start][finish][m].name[0]) + ((map[start][finish][m].start_time - current_time + 24) % 24) * output_city_danger(start)) < temp)
			{
				temp = (((map[start][finish][m].arrive_time - map[start][finish][m].start_time + 24) % 24) * output_city_danger(start) * output_tran_danger(map[start][finish][m].name[0]) + ((map[start][finish][m].start_time - current_time + 24) % 24) * output_city_danger(start));
				tool = m;
			}
		}
	}
	return tool;
}

void save_path(int start, int finish)
{
	int i, j;

	for (i = 0; i < NUM_OF_CITY; i++)
	{
		for (j = 0; j < NUM_OF_CITY; j++)
		{
			trans_num[i][j] = -1;
		}
	}

	for (i = finish; i != start; i = lastnode[i])
	{
		trans_num[lastnode[i]][i] = tool_num(lastnode[i], i, Current[lastnode[i]]);
	}
}

void lim_time_search(int start, int finish, int final_f[NUM_OF_CITY], int order_f[NUM_OF_CITY], int trans_f[NUM_OF_CITY], int flag)
{
	int i, j, k;
	int temp_time = 0;
	double temp_danger = 0;
	if (start == finish)
	{
		if ((total_time_1 <= lim_time) && (plan.min_danger == 0))
		{
			plan.min_danger = total_danger_1;
			plan.min_time = total_time_1;

			for (i = 0; i < NUM_OF_CITY; i++)
			{
				plan.porder[i] = order_f[i];
				plan.ptrans[i] = trans_f[i];
			}
		}
		else if (total_danger_1 < plan.min_danger && total_time_1 <= lim_time)
		{
			plan.min_danger = total_danger_1;
			plan.min_time = total_time_1;

			for (i = 0; i < NUM_OF_CITY; i++)
			{
				plan.porder[i] = order_f[i];
				plan.ptrans[i] = trans_f[i];
			}
		}
	}
	else
	{
		for (i = 0; i < NUM_OF_CITY; i++)
		{
			if (final_f[i] != 1 && map[start][i][0].cost < INFINITY)
			{
				for (k = 0; k < MAX_NUM&&map[start][i][k].cost<INFINITY; k++)
				{
					temp_time = (map[start][i][k].start_time - plan.city_save[start][0] % 24 + 24) % 24 + (map[start][i][k].arrive_time - map[start][i][k].start_time + 24) % 24;
					if (total_time_1 + temp_time > lim_time);
					else
					{
						trans_f[i] = k;
						total_time_1 = total_time_1 + temp_time;

						for (j = 0; j < NUM_OF_CITY && order_f[j] != -1 && order_f[j] != start; j++);

						if (order_f[j] == start)
						{
							order_f[j + 1] = i;
						}

						final_f[i] = 1;
						plan.city_save[start][1] = plan.city_save[start][0] + (map[start][i][k].start_time - plan.city_save[start][0] % 24 + 24) % 24;
						plan.city_save[i][0] = plan.city_save[start][1] + (map[start][i][k].arrive_time - map[start][i][k].start_time + 24) % 24;

						if (flag == 1)
						{
							temp_danger = (plan.city_save[i][0] - plan.city_save[start][1]) * output_city_danger(start) * output_tran_danger(map[start][i][k].name[0]);
						}
						else
						{
							temp_danger = ((plan.city_save[i][0] - plan.city_save[start][1]) * output_city_danger(start) * output_tran_danger(map[start][i][k].name[0])) + ((plan.city_save[start][1] - plan.city_save[start][0]) * output_city_danger(start));
						}

						total_danger_1 = total_danger_1 + temp_danger;

						lim_time_search(i, finish, final_f, order_f, trans_f, 0);

						total_danger_1 = total_danger_1 - temp_danger;
						total_time_1 = total_time_1 - temp_time;

						for (j = 0; j < NUM_OF_CITY && order_f[j] != -1 && order_f[j] != i; j++);
						if (order_f[j] == i)
						{
							order_f[j] = -1;
						}

						final_f[i] = 0;
						trans_f[i] = -1;

						plan.city_save[i][0] = 0;
						plan.city_save[start][1] = 0;
					}
				}
			}
		}
	}
}