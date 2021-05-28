#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * Algorytm na podstawie rozwiązania z Olimpiady Informatycznej 1996/1997.
 * Implementacja na sparse array.
 */

// Sparse array

typedef struct node_t
{
    int i;
    int v;
    struct node_t *prev;
    struct node_t *next;
} node_t;

node_t* make_node(int i0, int v0);

void insert_after(node_t *p, int i, int v);

void insert_before(node_t *p, int i, int v);

node_t* get_first(node_t *p);

node_t* get_last(node_t *p);

node_t* get_index(node_t *l, int i);

node_t* get_rel(node_t *p, int i);

void print_list(node_t *l);

void free_list(node_t *l);

// !Sparse array

// Algorithm

void move_right(node_t *p);

void move_left(node_t *p);

void unload(node_t *p);

void solve(node_t *l);

// !Algorithm

int main()
{
    int n;
    scanf("%d", &n);

    int i, v;
    scanf("%d %d", &i, &v);
    struct node_t *tape = make_node(i, v);

    for (int j = 1; j < n; ++j)
    {
        scanf("%d %d", &i, &v);
        get_index(tape, i)->v = v;
    }

    solve(tape);

    node_t *p = get_first(tape);
    while (p)
    {
        if (p->v > 0)
            printf("%d ", p->i);
        p = p->next;
    }

    free_list(tape);
    return 0;
}

void unload(node_t *p)
{
    int k = p->v / 3;
    p->v -= k * 3;
    get_rel(p, -2)->v += k;
    get_rel(p, 2)->v += k;
}

void solve(node_t *l)
{
    l = get_first(l);

    bool lap;
    do
    {
        node_t *p = l;
        while (p)
        {
            if (p->v >= 3)
            {
                unload(p);
                if (get_index(p, p->i - 2)->v >= 3)
                    lap = true;
            }

            p = p->next;
        }
    } while (lap);

    node_t *p = get_last(l)->prev;

    for (;;)
    {
        if (p->v > 0 && get_rel(p, 1)->v > 0)
        {
            move_right(p);
            p = get_rel(p, 2);
        }
        else if (p->v == 2 && get_rel(p, -1)->v > 0)
        {
            p = get_rel(p, -1);
        }
        else if (p->v == 2 && get_rel(p, 1)->v == 0)
        {
            move_left(p);
            move_right(get_rel(p, -1));
            p = get_rel(p, 1);
        }
        else if (p->v == 3)
        {
            unload(p);
            p = get_rel(p, 2);
        }
        else if (!p->prev)
        {
            break;
        }
        else
        {
            p = p->prev;
        }
    }
}

// Sparse array

node_t* make_node(int i0, int v0)
{
    node_t *node = malloc(sizeof *node);
    node->i = i0;
    node->v = v0;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

void insert_after(node_t *p, int i, int v)
{
    node_t *node = make_node(i, v);
    node->prev = p;
    node->next = p->next;

    if (node->prev)
        node->prev->next = node;

    if (node->next)
        node->next->prev = node;
}

void insert_before(node_t *p, int i, int v)
{
    node_t *node = make_node(i, v);
    node->next = p;
    node->prev = p->prev;

    if (node->prev)
        node->prev->next = node;

    if (node->next)
        node->next->prev = node;
}

void print_list(node_t *l)
{
    node_t *q = get_first(l);

    while (q)
    {
        printf("(%d, %d) ", q->i, q->v);
        q = q->next;
    }

    printf("\n");
}

void free_list(node_t *l)
{
    node_t *q = get_first(l);

    while (q)
    {
        node_t *p = q->next;
        free(q);
        q = p;
    }
}

node_t* get_first(node_t *p)
{
    while (p->prev)
        p = p->prev;
    return p;
}

node_t *get_last(node_t *p)
{
    while (p->next)
        p = p->next;
    return p;
}

node_t* get_index(node_t *l, int i)
{
    if (l->i < i)
    {
        node_t *p = l->next;
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
        node_t *p = l->prev;
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
    return l;
}

node_t *get_rel(node_t *p, int i)
{
    return get_index(p, p->i + i);
}

void move_right(node_t *p)
{
    p->v--;
    get_rel(p, 1)->v--;
    get_rel(p, 2)->v++;
}

void move_left(node_t *p)
{
    p->v--;
    get_rel(p, -1)->v++;
    get_rel(p, -2)->v++;
}
