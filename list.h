#ifndef _LIST_H
#define _LIST_H

typedef struct list_node {
    void                *data;
    unsigned long       size;

    struct list_node    *next;
} list_node_t;

typedef struct {
    list_node_t   *head;
    list_node_t   *tail;
} list_t;


int list_init(list_t*const list);
int list_insert_tail(list_t*const list, const void*const buf, unsigned long size);
int list_insert_head(list_t*const list, const void*const buf, unsigned long size);
int list_remove_head(list_t*const list);
int list_remove_tail(list_t*const list);
int list_peek(const list_node_t*const lnode, void* buf, unsigned long *size);
unsigned long list_get_count(list_t*const list);
void list_deinit(list_t*const list);

static list_node_t* listnode_init(const void*const buf, unsigned long size);
static void listnode_deinit(list_node_t*const lnode);

#endif
