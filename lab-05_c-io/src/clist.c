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
		node->prev->next = node->next;
		if (node->next != NULL)
		{
			node->next = node->prev;
		}
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
	if (list->head==NULL)
	{
		return;
	}
	intrusive_node* last = last_node(list);
	op(last, data);
	remove_node(list, last);
	apply(list, op, data);
}
