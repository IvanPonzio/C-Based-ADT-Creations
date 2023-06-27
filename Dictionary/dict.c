#include <stdlib.h>     /* malloc(), free()... */
#include <stdbool.h>    /* bool type           */
#include <assert.h>     /* assert()            */
#include "key_value.h"  /* key_t               */
#include "dict.h"       /* intarface           */

struct _s_dict {
    unsigned int length;
    struct _node_t * first;
};

// Internal structure
struct _node_t {
    key_t key;
    value_t value;
    struct _node_t *next;
};



struct _node_t * create_node(key_t k, value_t v) {
    struct _node_t *new_node=malloc(sizeof(struct _node_t));
    new_node->key=k;
    new_node->value=v;
    new_node->next=NULL;
    return new_node;
}

struct _node_t *destroy_node(struct _node_t *node) {
    node->key = key_destroy(node->key);
    node->value = value_destroy(node->value);
    free(node);
    node=NULL;
    return node;
}

static bool invrep(dict_t dict) {
    return (dict != NULL && dict->length == dict_length(dict));
}
// --- Interface functions ---

dict_t dict_empty(void) {
    dict_t nuevo;
    nuevo = malloc(sizeof(struct _s_dict));
    nuevo->first = NULL;
    nuevo->length = 0;
    assert(dict_length(nuevo) == 0);
    return nuevo;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
    assert(invrep(dict));
    struct _node_t *aux = dict->first;
    if (dict->first == NULL)
    {
        struct _node_t *new = create_node(word,def);
        dict->first = new;
    }
    else
    {
        if (string_eq(dict->first->key,word))
        {
            dict->first->value = def;
            return dict;
        }
        else {
        while (aux->next != NULL)
        {
            aux = aux->next;
            if (string_eq(aux->key,word))
            {
                aux->value = def;
                assert(dict_exists(dict,word));
                return dict;
            }
            
        }
        struct _node_t *new = create_node(word,def);
        aux->next = new;
        
        
    }
    }
    dict->length = dict->length + 1 ;
    
    assert(dict_exists(dict,word));
    return dict;
    
}

value_t dict_search(dict_t dict, key_t word) {
    assert(invrep(dict));
    struct _node_t *aux = dict->first;
    value_t definicion = NULL;
    while (aux != NULL)
    {
        if (string_eq(aux->key,word))
        {
            definicion = aux->value;
        }
        aux = aux->next;    
    }
    assert((definicion != NULL) == dict_exists(dict, word));
    return definicion;
}

bool dict_exists(dict_t dict, key_t word) {
    assert(invrep(dict));
    struct _node_t *aux = dict->first;
    bool existe = false;
    while (aux != NULL)
    {
        if (string_eq(aux->key,word))
        {
            existe = true;
        }
        
        aux = aux->next;    
    }
    //destroy_node(aux);
    return existe;
}

unsigned int dict_length(dict_t dict) {
    return dict->length;
}

dict_t dict_remove(dict_t dict, key_t word) {
    assert(invrep(dict));
    struct _node_t *aux = dict->first;
    struct _node_t *atras = NULL;
    if (string_eq(aux->key,word))
    {
        dict->first = aux->next;
        destroy_node(aux);
    }
    else {
    while (!string_eq(aux->key,word))
    {
        atras = aux;
        aux = aux->next;    
    }
    atras->next = aux->next;
    destroy_node(aux);
    }
    dict->length = dict->length - 1;
    assert(!dict_exists(dict, word));
    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    assert(invrep(dict));
    for (struct _node_t *check=dict->first; check!=NULL; check=check->next) {
        fprintf(file, "key: ");
        key_dump(check->key, file);
        fprintf(file, "\n");
        fprintf(file, "value: ");
        value_dump(check->value, file);
        fprintf(file, "\n\n");
    }
}

dict_t dict_remove_all(dict_t dict) {
    assert(invrep(dict));
    if (dict->first != NULL) {
        struct _node_t *curr = dict->first;
        while (curr != NULL) {
            struct _node_t *next = curr->next;
            destroy_node(curr);
            curr = next;
            dict->length = dict->length - 1;
        }
    }
    dict->first = NULL; // <--- Agrega esta línea
    assert(dict->length == 0);
    return dict;
}


dict_t dict_destroy(dict_t dict) { 
    assert(invrep(dict));
    dict = dict_remove_all(dict);
    free(dict);
    dict=NULL;
    assert(dict==NULL);
    return dict;
}

