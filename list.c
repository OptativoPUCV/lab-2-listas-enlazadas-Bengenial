#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List *list = (List *) malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;

    return list;
}

void * firstList(List * list) {
    list->current = list->head;
    if(list->current) return list->current->data;
    return NULL;
}

void * nextList(List * list) {
    if(list->current)
        list->current = list->current->next;
    if(list->current) return list->current->data;
    return NULL;
}

void * lastList(List * list) {
    if (list->current)
        list->current = list->tail;
    return list->current->data;
}

void * prevList(List * list) {
    if (list->current)
        list->current = list->current->prev;
    if (list->current) return list->current->data;
    return NULL;
}

void pushFront(List * list, void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    new->data = data;
    new->prev = NULL;
    new->next = list->head;

    if (list->head) 
        list->head->prev = new;
    else
        list->tail = new;
    
    list->head = new;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    new->data = data;

    if(list->current->next){
        new->prev = list->current;
        new->next = list->current->next;
        list->current->next->prev = new;
        list->current->next = new;
    }else{
        new->next = NULL;
        new->prev = list->current;
        list->current->next = new;
        list->tail = new;
    }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    void * data = list->current->data;

    if (list->current == list->head){
        list->head = list->current->next;
        if (list->head) list->head->prev = NULL;
        free(list->current);
        list->current = list->head;

    }
    else if (list->current == list->tail){
        list->tail = list->current->prev;
        if (list->tail) list->tail->next = NULL;

        free(list->current);
        list->current = list->head;
    }
    else{
        Node *aux = list->current;
        list->current->prev->next = list->current->next;
        list->current->next->prev = list->current->prev;
        free(aux);

    }
    return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}