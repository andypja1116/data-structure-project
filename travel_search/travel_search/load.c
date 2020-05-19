#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"public_data_structure.h"

void load()
{
	FILE* fp;
	int a, b, c, i, j, k;
	Map temp;

	if ((fp = fopen("time.txt", "r")) == NULL)
	{
		printf("打开文件失败！\n");
		exit(0);
	}
	fscanf(fp, "%d %d %d %s %d %d %d", &a, &b, &c, temp.name, &temp.cost, &temp.start_time, &temp.arrive_time);

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			for (k = 0; k < 6; k++)
			{
				if (i == a && j == b && k == c)
				{
					strcpy(map[i][j][k].name, temp.name);
					map[i][j][k].cost = temp.cost;
					map[i][j][k].start_time = temp.start_time;
					map[i][j][k].arrive_time = temp.arrive_time;
					fscanf(fp, "%d %d %d %s %d %d %d", &a, &b, &c, temp.name, &temp.cost, &temp.start_time, &temp.arrive_time);
				}
				else
				{
					strcpy(map[i][j][k].name, "\0");
					map[i][j][k].cost = INFINITY;
					map[i][j][k].start_time = -1;
					map[i][j][k].arrive_time = -1;
				}
			}
		}
	}
	fclose(fp);
}