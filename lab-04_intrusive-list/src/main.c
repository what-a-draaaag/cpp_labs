#include "clist.h"
#include "stddef.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "stdbool.h"

typedef struct point {
  int x;
  int y;
  intrusive_node node;
} point;


void add_point(intrusive_list* list, int x, int y) 
{
    point* new_point = malloc(sizeof(point));
    new_point->x = x;
    new_point->y = y;
    add_node(list, &(new_point->node));
}

void remove_point(intrusive_list* list, int x, int y) 
{
  intrusive_node* start_node = list->head;
  while(start_node != NULL)
  {
    intrusive_node* current_node = start_node;

    start_node = start_node->next;
    point* current_point = container_of(current_node, point, node);
    if (!(current_point->x == x && current_point->y == y))
    {
      continue;
    }
    remove_node(list, current_node);
    free(current_point);
  }
}

void show_all_points(intrusive_list* list) 
{
  intrusive_node* start_node = list->head;
  while (start_node != NULL)
  {
    point* current_point = container_of(start_node, point, node);
    printf("(%d %d) ", current_point->x, current_point->y);
    if (start_node->next == NULL)
    {
      printf("(%d %d)\n", current_point->x, current_point->y);
    }
    else
    {
      printf("(%d %d) ", current_point->x, current_point->y);
    }
    start_node = start_node->next;
  }
}

void remove_all_points(intrusive_list* list) 
{
  intrusive_node* start_node = list->head;
  while(start_node != NULL)
  {
    intrusive_node* current_node = start_node;
    start_node = start_node->next;
    point* current_point = container_of(current_node, point, node);
    remove_node(list, current_node);
    free(current_point);
  }
}


int main() {
   intrusive_list list;
   init_list(&list);
   int x, y;
   char input[300];

   while(true)
   {
      scanf("%300s", input);
      {
        if (!strcmp(input, "add"))
        {
          scanf("%d %d", &x, &y);
          add_point(&list, x, y);
        }
        else if (!strcmp(input, "rm"))
        {
          scanf("%d %d", &x, &y);
          remove_point(&list, x, y);
        }
        else if (!strcmp(input, "len"))
        {
          printf("%d\n", get_length(&list));
        }
        else if (!strcmp(input, "print"))
        {
          show_all_points(&list);
        }
        else if (!strcmp(input, "rma"))
        {
          remove_all_points(&list);
        }
        else if (!strcmp(input, "exit"))
        {
          break;
        }
        else
        {
          printf("Unknown command\n");
        }
      }
   }

  return 0;
  
}
