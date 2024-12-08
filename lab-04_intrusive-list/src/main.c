#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include "clist.h"
#define container_of(ptr, type, member) (type *)((char *)(ptr)-offsetof(type, member))

struct point
{
    int x, y;
    struct intrusive_node node;
};

void add_point(intrusive_list_t *my_list, int x, int y)
{
    point_t *points = malloc(sizeof(point_t));
    points->x = x;
    points->y = y;
    add_node(my_list, &(points->node));
}

void remove_point(intrusive_list_t *my_list, int x, int y)
{
    intrusive_node_t *head = my_list->head;
    while (head->next)
    {
        intrusive_node_t *current = head->next;
        point_t *points = container_of(current, point_t, node);
        if (points->x != x || points->y != y)
        {
            head = head->next;
            continue;
        }
        remove_node(current);
        free(points);
    }
}

void show_all_points(intrusive_list_t *my_list)
{
    intrusive_node_t *head = my_list->head;
    while (head->next)
    {
        head = head->next;
        point_t *points = container_of(head, point_t, node);
        printf("(%d %d)", points->x, points->y);
        if (head->next)
            printf(" ");
    }
    printf("\n");
}

void remove_all_points(intrusive_list_t *my_list)
{
    intrusive_node_t *head = my_list->head;
    while (head->next)
    {
        intrusive_node_t *current = head->next;
        point_t *points = container_of(current, point_t, node);
        remove_node(current);
        free(points);
    }
}

int main()
{
    intrusive_list_t my_list;
    init_list(&my_list);

    char input[239];
    while (1)
    {
        scanf("%239s", input);

        if  (strcmp(input, "add") == 0)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            add_point(&my_list, x, y);
        }
        else if (strcmp(input, "rm") == 0)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            remove_point(&my_list, x, y);
        }
        else if (strcmp(input, "print") == 0)
        {
            show_all_points(&my_list);
        }
        else if (strcmp(input, "rma") == 0)
        {
            remove_all_points(&my_list);
        }
        else if (strcmp(input, "len") == 0)
        {
            printf("%d\n", get_length(&my_list));
        }
        else if (strcmp(input, "exit") == 0)
        {
            break;
        }
        else
        {
            printf("Unknown command\n");
        }
    }

    remove_all_points(&my_list);
    free(my_list.head);
    return 0;
}