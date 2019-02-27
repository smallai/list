#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"


typedef struct line_t {
    struct list_head list;
    int a;
    int b;
} line_t;


int main(int argc, char *argv[])
{
//    struct list_head lines;
    struct list_head *pos, *q;
    line_t *line;

    (void)(argc);
    (void)(argv);

//    INIT_LIST_HEAD(&lines);
    LIST_HEAD(lines);

    for (int i=0; i<10; i++)
    {
        line = (line_t *)malloc(sizeof(line_t));
        line->a = i;
        line->b = i * i;
        list_add_tail(&line->list, &lines);

        if (list_size(&lines) > 3)
        {
            line = (line_t *)list_entry(lines.next, line_t, list);
            list_del(&line->list);
            free(line);
        }

        //printf("list size: %zu\n", list_size(&lines));
    }

    //删除第一个结点
//    line = (line_t *)list_entry(lines.next, line_t, list);
//    list_del(line);

//    //删除最后一个节点
//    line = (line_t *)list_entry(lines.prev, line_t, list);
//    list_del(line);

    //正向遍历
    printf("list_for_each\n");
    list_for_each(pos, &lines)
    {
        line = (line_t *)list_entry(pos, line_t, list);
        printf("a=%d, b=%d\n", line->a, line->b);
    }

    //反向遍历
    printf("list_for_each_prev\n");
    list_for_each_prev(pos, &lines)
    {
        line = (line_t *)list_entry(pos, line_t, list);
        printf("a=%d, b=%d\n", line->a, line->b);
    }

    //如果需要删除元素,应该使用带safe的宏
    //正向安全遍历
    list_for_each_safe(pos, q, &lines)
    {
        line = (line_t *)list_entry(pos, line_t, list);
        list_del(&line->list);
        free(line);
    }

    //反向安全遍历
    list_for_each_prev_safe(pos, q, &lines)
    {
        line = (line_t *)list_entry(pos, line_t, list);
        list_del(&line->list);
        free(line);
    }

    return 0;
}
