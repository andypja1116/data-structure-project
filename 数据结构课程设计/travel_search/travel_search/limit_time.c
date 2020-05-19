#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"public_data_structure.h"

void limit_time(int startnode, int arrivenode, int current_time)
{
	int i, j;
	int final[NUM_OF_CITY];
	int order[NUM_OF_CITY];
	int trans[NUM_OF_CITY];

	for (i = 0; i < NUM_OF_CITY; i++)
	{
		final[i] = 0;
		plan.ptrans[i] = -1;
		plan.porder[i] = -1;
		order[i] = -1;
		trans[i] = -1;
	}

	for (i = 0; i < NUM_OF_CITY; i++)
	{
		for (j = 0; j <= 1; j++)
		{
			plan.city_save[i][j] = 0;
		}
	}

	plan.city_save[startnode][0] = current_time;
	plan.porder[0] = startnode;
	plan.min_cost = 0;
	plan.min_danger = 0;
	plan.min_time = 0;
	final[startnode] = 1;
	order[0] = startnode;
	total_danger_1 = 0;

	lim_time_search(startnode, arrivenode, final, order, trans, 1);
}