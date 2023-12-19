#include <stdio.h>
#include"clist.h"
#include"point_list.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void fmt_print(intrusive_node* current_node, void* data)
{
	char* fmt = (char*)data;
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
	intrusive_list list;
	init_list(&list);
	void (*op)(intrusive_node* node, void* data);

	while(true)
	{
		int x, y, read_code;
		if (!strcmp(file_type, "loadtext"))
		{
			read_code = fscanf(in_file,"%d %d", &x, &y);
		}
		else if (!strcmp(file_type, "loadbin"))
		{
			read_code = fread(&x,3,1,in_file);
			if (read_code!=0)
			{
				read_code += fread(&y,3,1,in_file);
			}
		}
		if (!(read_code == -1 || read_code == 0))
		{
			add_point(&list, x, y);
		}
		
		if (feof(in_file))
		{
			break;
		}
	}
	if (!strcmp(action, "count"))
	{
		int count = 0;
		op = count_nodes;
		apply(&list, op, &count);
		printf("%d\n", count);
	}
	else if (!strcmp(action, "print"))
	{
		op = fmt_print;
		apply(&list, op, argv[4]);
		printf("\n");
	}
	else
	{
		const char* out_file_path = argv[4];
		FILE* out_file = fopen(out_file_path, "wa");
		intrusive_node* last = last_node(&list);
		while (true)
		{
			point* current_point = container_of(last, point, node);
			int x = current_point->x;
			int y = current_point->y;
			if (!strcmp(action, "savetext"))
			{
				fprintf(out_file, "%d %d\n", x, y);
			}
			else
			{
				fwrite(&x, 3, 1, out_file);
				fwrite(&y, 3, 1, out_file);
			}
			remove_node(&list, last);
			free(current_point);
			if ((last_node(&list))==NULL)
			{
				break;
			}
			last = last_node(&list);
		}
	}
	
	remove_all_points(&list);
}
