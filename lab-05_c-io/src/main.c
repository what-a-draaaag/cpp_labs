#include "stdio.h"
#include "clist.h"
#include "point_list.h"
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"

void fmt_print(intrusive_node* current_node, void* data)
{
	const char* fmt = (const char*)data;
	point* current_point = container_of(current_node, point, node);
	int x = current_point->x;
	int y = current_point->y;
	printf(fmt, x, y);
}

void count_nodes(intrusive_node* current_node, void* data)
{
	int* tmp = data;
	(*tmp)++;
}

void loadtxt(FILE* file, intrusive_list* list)
{
	int x, y;
	while(fscanf(file,"%d %d", &x, &y)==2)
	{
		add_point(list, x, y);
	}
}

void loadbin(FILE* file, intrusive_list* list)
{
	int arr[2];
	arr[0] = 0;
	arr[1] = 0;
	int last_positive = 0x7fffff;
	int index = 0;
	while(fread(&arr[index], 3, 1, file))
	{
		if (arr[index] > last_positive)
		{
			arr[index] -= 1 << 24;
		}
		index = 1 - index;
		if (index == 0)
		{
			add_point(list, arr[0], arr[1]);
			arr[0] = 0;
			arr[1] = 0;
		}
	}
}

void process_empty_file(FILE* file, const char* action, void**argv)
{
	if (!strcmp(action,"print"))
	{
		printf("\n");
	}
	else if (!strcmp(action,"count"))
	{
		printf("0\n");
	}
	else
	{
		const char* file_path = argv[4];
		FILE* empty_file = fopen(file_path, "wa");
		fclose(empty_file);
	}
}



int main(int argc, void** argv)
{
	const char* file_type = argv[1];
	const char* file_path = argv[2];
	const char* action = argv[3];
	FILE* in_file = fopen(file_path, "r");

	if (in_file==NULL)
	{
		return 0;
	}
	fseek(in_file, 0, SEEK_END);
	if (ftell(in_file)==0)
	{
		process_empty_file(in_file, action, argv);
		return 0;
	}
	fseek(in_file, 0, SEEK_SET);

	intrusive_list list;
	init_list(&list);

	if (!strcmp(file_type, "loadtext"))
	{
		loadtxt(in_file, &list);
	}
	else if (!strcmp(file_type, "loadbin"))
	{
		loadbin(in_file, &list);
	}
		
	if (!strcmp(action, "count"))
	{
		int count = 0;
		apply(&list, count_nodes, &count);
		printf("%d\n", count);
	}
	else if (!strcmp(action, "print"))
	{
		apply(&list, fmt_print, argv[4]);
		printf("\n");
	}
	else
	{
		const char* out_file_path = argv[4];
		savefile(out_file_path, action, &list);
	}
	
	remove_all_points(&list);
	fclose(in_file);
}
