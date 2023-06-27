#include <stdlib.h>
#include "fence.h"
#include <stdio.h>

struct _fence_t {
    fence_t next;
    type_t type;
    unsigned int size;
};


fence_t fence_P(){
    fence_t fenc;

    fenc = malloc(sizeof(struct _fence_t));
    fenc->type = P;
    fenc->next = NULL;
    fenc->size = 1;
    return fenc;
}

fence_t fence_add_P(fence_t fence){
    fence_t new = fence_P();
    fence_t new2;
    new2 = fence;
    while (new2->next != NULL)
    {
        new2 = new2->next;
    }
    new2->next = new; 
    fence->size = fence->size + 1 ;
    return fence;
}

fence_t fence_add_A(fence_t fence){
    fence_t new;
    new = malloc(sizeof(struct _fence_t));
    new->type = A;
    new->next = NULL;
   // new->size = 1;
    fence_t new2;
    new2 = fence;
    while (new2->next != NULL)
    {
        new2 = new2->next;
    }
    new2->next = new; 
    fence->size = fence->size + 1 ;
    return fence;
}

fence_t fence_add_H(fence_t fence){
    fence_t new;
    new = malloc(sizeof(struct _fence_t));
    new->type = H;
    new->next = NULL;
   // new->size = 1;
    fence_t new2;
    new2 = fence;
    while (new2->next != NULL)
    {
        new2 = new2->next;
    }
    new2->next = new; 
    fence->size = fence->size + 1 ;
    return fence;

}
fence_t fence_add_T(fence_t fence){

    fence_t new;
    new = malloc(sizeof(struct _fence_t));
    new->type = T;
    new->next = NULL;
   // new->size = 1;
    fence_t new2;
    new2 = fence;
    while (new2->next != NULL)
    {
        new2 = new2->next;
    }
    new2->next = new; 
    fence->size = fence->size + 1 ;
    return fence;
}

bool fence_is_correct(fence_t fence) {
    bool tranquera = false;
    fence_t siguente = fence;
    fence_t anterior = NULL;
    while (siguente != NULL) {
        if (siguente->type == T) {
            tranquera = true;
        } 
            if (anterior != NULL && 
                anterior->type != P && 
                siguente->type != P) {
                return false;
            }
            if (siguente->next != NULL && 
                siguente->next->type != P && 
                siguente->type != P) {
                return false;
            }
        
        anterior = siguente;
        siguente = siguente->next;
    }
    if (anterior != NULL && anterior->type != P) {
        return false;
    }
    return tranquera;
}



unsigned int fence_perimeter(fence_t fence){
    unsigned int perimetro = 0;
    fence_t new;
    new = fence;
    while (new != NULL)
    {
        if (new->type == A || new->type == H || new->type == T)
        {
            perimetro = perimetro + 3;
        }
        new = new->next;
        
    }
    return perimetro;
}


unsigned int fence_size(fence_t fence){
    return fence->size;
}

type_t *fence_to_array(fence_t fence) {
    unsigned int size = fence_size(fence);
    type_t *array = malloc(size * sizeof(type_t));
    fence_t current_node = fence;
    for (int i = size - 1; i >= 0; i--) {
        array[i] = current_node->type;
        current_node = current_node->next;
    }
    return array;
}

fence_t fence_destroy(fence_t fence) {
    fence_t current = fence;
    while (current != NULL) {
        fence_t next = current->next;
        free(current);
        current = next;
    }
    return NULL;
}