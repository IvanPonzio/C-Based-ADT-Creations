#include "dna.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

struct _node {
    nucleobase_t elem;
    struct _node *next;
};

struct _dna_t
{
    struct _node* chain;
    unsigned int lenght;
};

static struct _node* single_node(nucleobase_t e)
{
    struct _node *node = calloc(1, sizeof(struct _node));
    assert(node != NULL);
    node->elem = e;
    node->next = NULL;
    return (node);
}

dna_t dna_T()
{
    dna_t res = NULL;
    res = malloc(sizeof(struct _dna_t));
    res->chain = single_node(T);
    res->lenght = 1;
    return res;
}

dna_t dna_C()
{
    dna_t res = NULL;
    res = malloc(sizeof(struct _dna_t));
    res->chain = single_node(C);
    res->lenght = 1;
    return res;
}

dna_t dna_A()
{
    dna_t res = NULL;
    res = malloc(sizeof(struct _dna_t));
    res->chain = single_node(A);
    res->lenght = 1;
    return res;
}

dna_t dna_G()
{
    dna_t res = NULL;
    res = malloc(sizeof(struct _dna_t));
    res->chain = single_node(G);
    res->lenght = 1;
    return res;
}


dna_t dna_join(dna_t first, dna_t second)
{
    assert(first !=NULL && second!=NULL);
    struct _node* aux;
    aux = first->chain;
    while (aux->next != NULL)
    {
        aux = aux->next;
    }
    struct _node* aux2;
    aux2 = second->chain;
    while(aux2!= NULL){
        aux->next = single_node(aux2->elem);
        aux = aux->next;
        aux2 = aux2->next;
        first->lenght = first->lenght + 1;
    }

    return first;
}



unsigned int dna_length(dna_t dna)
{
    unsigned int res = 0u;
    res = dna->lenght;
    return res;
}

void dna_print(dna_t dna) {
    assert(dna != NULL);
    struct _node *curr = dna->chain;
    while (curr != NULL) {
        switch (curr->elem) {
            case T:
                printf("T");
                break;
            case C:
                printf("C");
                break;
            case A:
                printf("A");
                break;
            case G:
                printf("G");
                break;
            default:
                break;
        }
        curr = curr->next;
    }
    printf("\n");
}


bool dna_is_prefix(dna_t first, dna_t second)
{
    if (first->lenght > second->lenght)
    {
        return false;
    }
    
    bool is_prefix = true;
    struct _node* aux = first->chain;
    struct _node* aux2 = second->chain;
    while (aux != NULL && is_prefix)
    {
        if (aux->elem != aux2->elem)
        {
            is_prefix = false;
        }
        aux = aux->next;
        aux2 = aux2->next;
    }
    
    return is_prefix;
}

bool dna_is_equal(dna_t first, dna_t second)
{
    
    return (dna_is_prefix(first,second) && first->lenght == second->lenght);
}

dna_t *dna_cut(dna_t dna, unsigned int count)
{
    dna_t* res = NULL;
    res = calloc(2, sizeof(struct _dna_t*));
    res[0] = calloc(1, sizeof(struct _dna_t));
    res[1] = calloc(1, sizeof(struct _dna_t));
    struct _node *aux;
    aux = dna->chain;
    
    unsigned int i = 0;
    struct _node* aux2 = res[0]->chain;
    struct _node* aux3 = res[1]->chain;
    while(aux != NULL){
        if(i<count){
            aux2 = aux;
            res[0]->lenght++;
            aux2 = aux2->next;
        }
else{
            aux3 = aux;
            res[1]->lenght++;
            aux3 = aux3->next;
        }
        aux = aux->next;
        i = i + 1;
    }
    return res;
}



dna_t dna_destroy(dna_t dna)
{
    struct _node *current = dna->chain;
    struct _node *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    free(dna);

    return NULL;
}

