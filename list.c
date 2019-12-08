#include "list.h"
#include <string.h>
#include <stdlib.h>

int list_init(list_t*const list)
{
    if(list == NULL) return -1;

    list->head = list->tail = NULL;

    return 0;
}

static list_node_t* listnode_init(const void*const buf, const unsigned long size)
{
    if(buf == NULL || size == 0) return NULL;

    list_node_t *lnode = malloc(sizeof(list_node_t));
    if(lnode == NULL) return NULL;

    lnode->next = NULL;

    lnode->data = malloc(size);
    if(lnode->data == NULL){
        free(lnode);
        return NULL;
    }

    memcpy(lnode->data, buf, size);
    lnode->size = size;

    return lnode;
}

static void listnode_deinit(list_node_t*const lnode)
{
    if(lnode == NULL) return;

    if(lnode->data)
        free(lnode->data);

    free(lnode);
}

int list_insert_tail(list_t*const list, const void*const buf, const unsigned long size)
{
    list_node_t *newtail;

    if(list == NULL || buf == NULL || size == 0)
        return -1;

    newtail = listnode_init(buf, size);
    if(newtail == NULL)
        return -1;

    if(list->tail == NULL)
        list->head = list->tail = newtail;
    else {
        list->tail->next = newtail;
        list->tail = list->tail->next;
    }

    return 0;
}

int list_insert_head(list_t*const list, const void*const buf, const unsigned long size)
{
    list_node_t *newhead;

    if(list == NULL || buf == NULL || size == 0)
        return -1;

    newhead = listnode_init(buf, size);
    if(newhead == NULL)
        return -1;

    if(list->head == NULL)
        list->head = list->tail = newhead;
    else {
        newhead->next = list->head;
        list->head = newhead;
    }

    return 0;
}

int list_remove_head(list_t*const list)
{
    list_node_t *lnode;

    if(list == NULL || list->head == NULL)
        return -1;

    lnode = list->head;
    list->head = list->head->next;

    listnode_deinit(lnode);

    return 0;
}

int list_remove_tail(list_t*const list)
{
    list_node_t *lnode;

    if(list == NULL || list->tail == NULL)
        return -1;

    if(list->head == list->tail){
        listnode_deinit(list->tail);
        list->head = list->tail = NULL;
        return 0;
    }

    for(lnode=list->head; lnode->next!=list->tail;lnode=lnode->next);

    lnode->next = NULL;
    listnode_deinit(list->tail);
    list->tail = lnode;

    return 0;
}

int list_peek(const list_node_t*const lnode, void *buf, unsigned long *size)
{
    if(lnode == NULL)
        return -1;

    memcpy(buf, lnode->data, lnode->size);
    *size = lnode->size;

    return 0;
}

unsigned long list_get_count(list_t*const list)
{
    list_node_t *lncur;
    unsigned long count;

    for(lncur=list->head,count=0;lncur;lncur=lncur->next,count++);

    return count;
}

void list_deinit(list_t*const list)
{
    list_node_t *lncur, *lntmp;

    if(list == NULL) return;

    for(lncur = list->head; lncur;){
        lntmp = lncur;
        lncur = lncur->next;
        listnode_deinit(lntmp);
    }

}
