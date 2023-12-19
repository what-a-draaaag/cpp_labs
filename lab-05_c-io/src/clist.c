#include "clist.h"
#include "stddef.h"
#include "stdlib.h"
#include "point_list.h"
#include "string.h"
#include "stdbool.h"
#include "stdio.h"

void init_list(intrusive_list* list)
{
	list->head = NULL;
}

void add_node(intrusive_list* list, intrusive_node* node)
{
	if (list->head == NULL)
	{
		node->prev = NULL;
		node->next = NULL;
		list->head = node;
	}
	else
	{
		node->prev = NULL;
		node->next = list->head;
		list->head->prev = node;
		list->head = node;
	}
}

void remove_node(intrusive_list* list, intrusive_node* node)
{
	if (node->prev == NULL)
	{
		list->head = node->next;
		if (node->next != NULL)
		{
			node->next->prev = NULL;
		}
	}
	else
	{
		node->prev->next = node->next;
		if (node->next != NULL)
		{
			node->next = node->prev;
		}
	}
}

intrusive_node* last_node(intrusive_list* list)
{
	if (list->head == NULL)
	{
		return NULL;
	}
	intrusive_node* start = list->head;
	while(start->next!=NULL)
	{
		start = start->next;
	}
	return start;
}

void apply(intrusive_list *list, void (*op)(intrusive_node *node, void *data), void *data)
{
	if (last_node(list)==NULL)
	{
		return;
	}
	intrusive_node* last = last_node(list);
	point* last_point = container_of(last, point, node);
	op(last, data);
	remove_node(list, last);
	free(last_point);
	apply(list, op, data);
}

void savefile(const char* out_file_path, const char* action, intrusive_list* list)
{
	FILE* out_file = fopen(out_file_path, "wa");
	intrusive_node* last = last_node(list);
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
		remove_node(list, last);
		free(current_point);
		if ((last_node(list))==NULL)
		{
			break;
		}
		last = last_node(list);
	}
}
