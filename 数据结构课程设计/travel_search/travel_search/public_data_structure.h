#pragma once
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define INFINITY 99999
#define NUM_OF_CITY 10
#define MAX_NUM 6
#define MAX_TIME 48

typedef struct Map
{
	char name[6];
	int cost;
	int start_time;
	int arrive_time;
}Map;

Map map[10][10][6];//用于根据时刻表形成地图

typedef struct CityInfo
{
	int city_num;
	int arrive_time;
	int leave_time;
	char leavestyle[6];
	int danger;
}CityInfo;

typedef struct Tour
{
	int length;
	char name[10];
	int start_city;
	int dest_city;
	int current_city;
	CityInfo state[10];
}Tour;

typedef struct Plan
{
	int min_time;
	int min_cost;
	double min_danger;
	int porder[NUM_OF_CITY];
	long long int city_save[NUM_OF_CITY][2];//0存储到达该城市的时间，1存储从该城市出发的时间
	int ptrans[NUM_OF_CITY];
}Plan;

Plan plan;

void load(void);
void output_danger(int, int);
double output_city_danger(int);
int output_tran_danger(char);
int tool_num(int, int, int);
void find_min_danger(int, int, int);
void save_path(int, int);
void output_city_name(int);
void limit_time(int, int, int);
void lim_time_search(int start, int finish, int final_f[NUM_OF_CITY], int order_f[NUM_OF_CITY], int trans_f[NUM_OF_CITY], int flag);
void output_limit_time();

FILE* file;

int lastnode[NUM_OF_CITY];
int Current[NUM_OF_CITY];
int lim_time;//限制时间
int current_time;//系统当前时间
int trans_num[NUM_OF_CITY][NUM_OF_CITY];
int total_time_1;
//int total_cost_1 = 0;
double total_danger_1;