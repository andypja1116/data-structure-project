#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"public_data_structure.h"

void find_min_danger(int a, int b, int current_time)
{
	double temp_danger_tran = 0, temp_danger_city = 0, temp_danger = 0, min;
	int dest, num_tool;
	int i, j, k;
	int final[NUM_OF_CITY];
	double passenger[NUM_OF_CITY];
	double sum_danger = 0;

	for (i = 0; i < NUM_OF_CITY; i++)
	{
		final[i] = 0;
		passenger[i] = INFINITY;
		lastnode[i] = a;
	}

	for (i = 0; i < NUM_OF_CITY; i++)
	{
		if (map[a][i][0].cost < INFINITY)
		{
			temp_danger_tran = ((map[a][i][0].arrive_time - map[a][i][0].start_time + 24) % 24) * output_city_danger(a) * output_tran_danger(map[a][i][0].name[0]);
			//temp_danger_city = ((map[a][i][0].start_time - current_time + 24) % 24) * output_city_danger(a);
			temp_danger = temp_danger_tran;
			for (j = 1; (j < MAX_NUM) && (map[a][i][j].cost < INFINITY); j++)
			{
				if ((((map[a][i][j].arrive_time - map[a][i][j].start_time + 24) % 24) * output_city_danger(a) * output_tran_danger(map[a][i][j].name[0])) < temp_danger)
				{
					temp_danger = ((map[a][i][j].arrive_time - map[a][i][j].start_time + 24) % 24) * output_city_danger(a) * output_tran_danger(map[a][i][j].name[0]);
				}
			}
			passenger[i] = temp_danger;
		}
		else
			passenger[i] = INFINITY;
	}
	final[a] = 1;
	Current[a] = current_time;

	for (i = 0; i < NUM_OF_CITY; i++)
	{
		temp_danger = INFINITY;
		for (j = 0; j < NUM_OF_CITY; j++)
		{
			if (final[j] != 1 && passenger[j] < INFINITY && passenger[j] < temp_danger)
			{
				dest = j;
				temp_danger = passenger[j];
			}
		}
		//sum_danger = sum_danger + temp_danger;
		final[dest] = 1;
		num_tool = tool_num(lastnode[dest], dest,Current[lastnode[dest]]);
		Current[dest] = map[lastnode[dest]][dest][num_tool].arrive_time;
		
		if (dest == b)
			break;

		for (j = 0; j < NUM_OF_CITY; j++)
		{
			if (map[dest][j][0].cost < INFINITY && (j != dest) && final[j] != 1)
			{
				min = (((map[dest][j][0].arrive_time - map[dest][j][0].start_time + 24) % 24) * output_city_danger(dest) * output_tran_danger(map[dest][j][0].name[0]) + ((map[dest][j][0].start_time - Current[dest] + 24) % 24) * output_city_danger(dest));
				for (k = 1; k < MAX_NUM && map[dest][j][k].cost < INFINITY; k++)
				{
					if ((((map[dest][j][k].arrive_time - map[dest][j][k].start_time + 24) % 24) * output_city_danger(dest) * output_tran_danger(map[dest][j][k].name[0]) + ((map[dest][j][k].start_time - Current[dest] + 24) % 24) * output_city_danger(dest)) < min)
					{
						min = (((map[dest][j][k].arrive_time - map[dest][j][k].start_time + 24) % 24) * output_city_danger(dest) * output_tran_danger(map[dest][j][k].name[0]) + ((map[dest][j][k].start_time - Current[dest] + 24) % 24) * output_city_danger(dest));
					}
				}
				if (final[j] != 1 && (passenger[dest] + min < passenger[j]))
				{
					passenger[j] = passenger[dest] + min;
					lastnode[j] = dest;
				}
			}
		}
	}

	save_path(a, b);
	//return sum_danger;
}