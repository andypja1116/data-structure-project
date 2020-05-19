#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include "public_data_structure.h"

void load(void);//����ʱ�̱����ɵ�ͼ
void output_danger(int, int);
void limit_time(int, int, int);
void output_limit_time();

int pass_number = 0;//�ÿ���Ŀ
Tour passenger[20];
char* cityname[] = { "����","�Ϻ�","����","������","����","���","����","�ɶ�","����","�人" };

int main()
{
	FILE* fp;
	int select;
	int i,j;
	int flag = 0;//����ÿ��Ƿ����
	int req;//��ʾ�ÿ���ѡ��ķ���
	char name[10];
	clock_t hour;
	if ((fp= fopen("log.txt", "w")) == NULL)
	{
		exit(0);
	}
loop4:printf("��ǰϵͳʱ��Ϊ ��%d�� %d ʱ\n", ((clock() / CLOCKS_PER_SEC) / 10 / 24) + 1, ((clock() / CLOCKS_PER_SEC) / 10) % 24);
	printf("\n");
	printf("	 -------------------------------------------------------------\n");
	printf("   	                                                              \n");
	printf("   			            *��ӭ��ʹ�����β�ѯϵͳ*	              \n");
	printf("   	                                                              \n");
	printf("	 ------------------------��ǰ�����б�-------------------------\n");

	for (i = 0; i < 10; i++)
	{
		printf("%2d->%-6s      ", i, cityname[i]);
		if ((i + 1) % 5 == 0)
			printf("\n");
	}
	printf("ϵͳ����Ϊ����ѯ��滮��������·��");

	load();

loop2:printf("\n����ѡ������Ҫ�ķ���\n");
	printf("�����Ļ�밴0\n");
	printf("��ѯ·���밴1\n");
	printf("��ѯ״̬�밴2\n");
	printf("����־�밴3\n");
	printf("�˳�ϵͳ�밴4\n");
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
		printf("����������������\n");
		scanf("%s", passenger[pass_number].name);
		printf("\n������������б�ţ�\n");
		scanf("%d", &passenger[pass_number].start_city);
		printf("\n������Ŀ�ĳ��б�ţ�\n");
		scanf("%d", &passenger[pass_number].dest_city);
		printf("\n��ѡ�����в��ԣ�\n");
		printf("��������밴1\n");
		printf("��ʱ��������밴2\n");
		scanf("%d", &select);
			
		switch (select)
		{
		case 1:
			output_danger(passenger[pass_number].start_city, passenger[pass_number].dest_city);
			break;
		case 2:
			printf("����������ʱ�䣨Сʱ��");
			scanf("%d", &lim_time);
			limit_time(passenger[pass_number].start_city, passenger[pass_number].dest_city, current_time);
			output_limit_time();
			break;
		default:
			break;
		}
		printf("\n");
		printf("ϵͳ��Ϊ���滮��ɣ�\n");
		pass_number++;
		goto loop2;
	}
	else if (req == 2)
	{
	    printf("\n\n��������������\n");
		scanf("%s", name);
		for (i = 0; i <= pass_number; i++)
		{
			if (!strcmp(name, passenger[i].name))
			{
				flag = 1;
				printf("�Ѳ�ѯ���ÿ�%s��״̬���£�\n", passenger[i].name);
				hour = (clock() / CLOCKS_PER_SEC) / 10;
				if (hour <= passenger[i].state[1].leave_time)
				{
					printf("ͣ���ڳ���%s\n", cityname[passenger[i].state[1].city_num]);
				}
				else
				{
					for (j = 2; j <= passenger[i].length; j++)
					{
						if (hour<passenger[i].state[j].arrive_time && hour>passenger[i].state[j - 1].leave_time)
						{
							printf("�ڳ���%s�ͳ���%s֮��\n", cityname[passenger[i].state[j - 1].city_num], cityname[passenger[i].state[j].city_num]);
							switch (passenger[i].state[j - 1].leavestyle[0])
							{
							case 'C':
								printf("�������ࣺ");
								break;
							case 'T':
								printf("�����г���");
								break;
							case 'A':
								printf("����������");
							default:
								break;
							}
							printf("%s\n", passenger[i].state[j - 1].leavestyle);
						}
						else if (hour >= passenger[i].state[j].arrive_time && hour <= passenger[i].state[j].leave_time)
						{
							if (j == passenger[i].length)
							{
								printf("�ѵ���Ŀ�ĵ�%s\n",cityname[passenger[i].state[j].city_num]);
							}
							else
							{
								printf("ͣ���ڳ���%s\n", cityname[passenger[i].state[j].city_num]);
							}
						}
					}
				}
				goto loop2;
			}
		}
		if (flag == 0)
		{
			printf("��������ÿͲ�����\n");
			goto loop2;
		}
	}
	else if (req == 3)
	{
		printf("��־�ļ������ɣ�");
	}
	else if (req == 4)
	{
		printf("��л����ʹ�ã��´��ټ���");
		exit(0);
	}
	fclose(fp);
	return 0;
}