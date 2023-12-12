#include "clist.h"
#include "stddef.h"

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
		if (node->next != NULL)
		{
			node->next = node->prev;
		}
		node->prev->next = node->next;
	}
}

int get_length(intrusive_list* list)
{
	int length = 0;
	if (list->head == NULL)
	{
		return 0;
	}
	intrusive_node* start = list->head;
	length = 1;
	while(start->next != NULL)
	{
	  start = start->next;
	  length++;
	}
	return length;
}