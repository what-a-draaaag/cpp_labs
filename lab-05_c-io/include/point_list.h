#ifndef POINT_LIST_H
#define POINT_LIST_H

typedef struct point {
  int x;
  int y;
  intrusive_node node;
} point;

void add_point(intrusive_list* list, int x, int y);
void remove_point(intrusive_list* list, int x, int y);
void show_all_points(intrusive_list* list);
void remove_all_points(intrusive_list* list);


#endif