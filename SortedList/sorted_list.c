#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "sorted_list.h"
//#include "list.h"

struct _node
{
   elem_t elemento;
   sorted_list_t next;
   unsigned int size;

};


sorted_list_t sorted_list_empty()
{
   sorted_list_t inicio;
   //inicio = malloc(sizeof(sorted_list_t));
   inicio = NULL;
   //inicio->size = 0;
   return inicio; 
}

bool sorted_list_is_empty(sorted_list_t list)
{
	return (list == NULL && list->size == 0);
}

elem_t sorted_list_head(sorted_list_t list)
{
	return (list->elemento);
}

sorted_list_t sorted_list_append(sorted_list_t list, elem_t elem)
{
   struct _node *new = malloc(sizeof(struct _node));
   new->elemento = elem;
   new->next = NULL;
   
   if (list == NULL)
   {
      list = new;
      list->size = 1;
   }
   else {
      struct _node *current = list;
      struct _node *prev = NULL;
      while (current != NULL && elem > current->elemento)
      {
         prev = current;
         current = current->next;
      }
      if (prev == NULL) {
         new->next = list;
         list = new;
      }
      else {
         new->next = current;
         prev->next = new;
      }
      list->size = list->size + 1;
   }
   return list;
}



sorted_list_t sorted_list_tail(sorted_list_t list)
{
   struct _node *new = list;
   list = list->next;
   list->size = list->size - 1;
   free(new);
   return list;
}

unsigned int sorted_list_length(sorted_list_t list)
{
   if (list == NULL)
   {
      return 0;
   }
   
   return (list->size);
}

elem_t sorted_list_elem_at(sorted_list_t list, unsigned int index)
{
  elem_t e;
  struct _node *new = list;
  unsigned int i = 0;
  while (i < index)
  {
   new = new->next;
  }
   e = new->elemento;
   return e;
  
}

sorted_list_t sorted_list_take(sorted_list_t list, unsigned int num)
{
   sorted_list_t newlista = malloc(sizeof(sorted_list_t));
   struct _node *aux = list;
   unsigned int i = 0;
   while (aux != NULL || i < num)
   {
      sorted_list_append(newlista,aux->elemento);
      aux = aux->next;
   }
   return newlista;
}

sorted_list_t sorted_list_drop(sorted_list_t list, unsigned int num)
{
   sorted_list_t aux = list;
   unsigned int i = 0;
   sorted_list_t new_list = sorted_list_empty();
   while(aux!=NULL && i<num){
    aux = aux->next;
    i++;
   }
   while(aux!= NULL && i < sorted_list_length(list)){
    new_list = sorted_list_append(new_list, aux->elemento);
    aux = aux->next;
   }
   return new_list;
   
}

void sorted_list_print(sorted_list_t list)
{
   struct _node *aux = list;

   while (aux != NULL)
   {
      printf("%d , ", aux->elemento);
      aux = aux->next;
   }
   
}

sorted_list_t sorted_list_destroy(sorted_list_t list)
{
    struct _node *current = list;
    while (current != NULL) {
        struct _node *next = current->next;
        free(current);
        current = next;
    }
    return NULL;
}
