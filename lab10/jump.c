#include <stdio.h>
#include <stdlib.h>

struct node_t
{
    int i;
    int v;
    struct node_t *prev;
    struct node_t *next;
};

struct node_t* make_node(int i0, int v0)
{
    struct node_t *node = malloc(sizeof *node);
    node->i = i0;
    node->v = v0;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

void insert_after(struct node_t *p, int i, int v)
{
    struct node_t *node = make_node(i, v);
    node->prev = p;
    node->next = p->next;

    if (node->prev)
        node->prev->next = node;

    if (node->next)
        node->next->prev = node;
}

void insert_before(struct node_t *p, int i, int v)
{
    struct node_t *node = make_node(i, v);
    node->next = p;
    node->prev = p->prev;

    if (node->prev)
        node->prev->next = node;

    if (node->next)
        node->next->prev = node;
}

void add_to_field(struct node_t *l, int i, int v)
{
    if (l->i < i)
    {
        struct node_t *p = l->next;
        while (p && p->i <= i)
        {
            l = p;
            p = p->next;
        }

        if (l->i != i)
        {
            insert_after(l, i, 0);
            l = l->next;
        }
    }
    else if (i < l->i)
    {
        struct node_t *p = l->prev;
        while (p && i <= p->i)
        {
            l = p;
            p = p->prev;
        }

        if (l->i != i)
        {
            insert_before(l, i, 0);
            l = l->prev;
        }
    }

    l->v += v;
}

void print_list(const struct node_t *l)
{
    const struct node_t *p, *q;

    p = l->prev;
    q = l;
    while (p)
    {
        q = p;
        p = p->prev;
    }

    while (q)
    {
        printf("(%d, %d) ", q->i, q->v);
        q = q->next;
    }

    printf("\n");
}

void free_list(struct node_t *l)
{
    struct node_t *p, *q;

    p = l->prev;
    q = l;
    while (p)
    {
        q = p;
        p = p->prev;
    }

    while (q)
    {
        p = q->next;
        free(q);
        q = p;
    }
}

int main()
{
    struct node_t *list = make_node(0, 5);

    print_list(list);

    add_to_field(list, 3, 3);
    print_list(list);

    add_to_field(list, 2, 1);
    print_list(list);

    add_to_field(list, 2, 1);
    print_list(list);

    free_list(list);
    return 0;
}
