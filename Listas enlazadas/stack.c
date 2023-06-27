#include <stdlib.h>
#include <assert.h>

#include "stack.h"

#define CHUNK_CAPACITY 5

struct s_node {
    stack_elem chunk[CHUNK_CAPACITY];
    unsigned int used;
    node next;
};

struct _s_stack {
    
    node top;
    unsigned int length;
};

// static bool
// valid_chunks(stack s) {
//     bool valid=true;
//     struct s_node *check=s->top;
//     if (check!=NULL) {
//         while (check != NULL)
//         {
//             valid = valid && check->used > 0 && check->used <= CHUNK_CAPACITY;
//             check = check->next; 
//         }
        
//     }
//     return valid;
// }

// static bool
// invrep(stack s) {
//     // COMPLETAR

//     return (s!=NULL && valid_chunks(s));
// }

static struct s_node *create_node(void) {
    // Reservamos memoria para un nuevo nodo de la pila.
    struct s_node *node = (struct s_node *)malloc(sizeof(struct s_node));
    if (node == NULL) { // Verificamos si se pudo reservar la memoria correctamente.
        return NULL;
    }

    // Inicializamos los valores de los campos del nuevo nodo.
    node->used = 0;
    node->next = NULL;

    return node;
}

static struct s_node *destroy_node(struct s_node *node) {
    // Liberamos la memoria reservada para el nodo.
    free(node);
    return NULL;
}

stack stack_empty(void) {
    stack s;
    s = malloc(sizeof(struct _s_stack));
    s->length = 0;
    s->top = NULL;
    return s;
}


stack stack_push(stack s, stack_elem e) {
    assert(s!=NULL);
    if (s->top == NULL){
        struct s_node* node = create_node();
        node->chunk[0] = e;
        ++node->used;
        s->top = node;
        ++s->length;
    }
    else{
        if(s->top->used == CHUNK_CAPACITY){
            struct s_node* node = create_node();
            node->chunk[0] = e;
            ++node->used;
            node->next = s->top;
            s->top = node;
            ++s->length;
        }
        else{
            s->top->chunk[s->top->used] = e;
            ++s->top->used;
            ++s->length;
        }
    }
    assert(s->top!=NULL);
    return s;
}


stack stack_pop(stack s) {
    if(s->top->used == 1){
        struct s_node * aux;
        aux = s->top;
        s->top = s->top->next;
        --s->length;
        destroy_node(aux);
    }
    else{
        --s->top->used;
        --s->length;
    }
    return s;
    }

unsigned int stack_size(stack s) {
    return s->length;
}

void stack_top(stack s, stack_elem *top) {
    *top = s->top->chunk[s->top->used - 1];
}

bool stack_is_empty(stack s) {
    return s->top == NULL && s->length == 0;
}

stack_elem *stack_to_array(stack s) {
   stack_elem *array;
   if(stack_is_empty(s)){
        array = NULL;
    }
    else{
        array = calloc(s->length, sizeof(stack_elem));
        int i = s->length -1;
        struct s_node * aux = s->top;
        while (aux != NULL)
        {
            for(int j = aux->used -1; j>=0; --j){
                array[i] = aux->chunk[j];
                --i;
            }
            aux = aux->next;
        }
        destroy_node(aux);
    }
    
    
    return array;
}


stack stack_destroy(stack s) {
    node n = s->top;
    while (n != NULL) {
        node next = n->next;
        destroy_node(n);
        n = next;
    }
    s->top = NULL;
    s->length = 0;
    return s;
}