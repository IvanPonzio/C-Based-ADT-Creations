#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include <stdio.h>

#include "domino_line.h"
#include "domino.h"

struct _s_line {
    domino_line next;
    domino tile;
    unsigned int length;
};

domino_line line_new(domino first) {
    domino_line line = (domino_line) malloc(sizeof(struct _s_line));
    if (line != NULL) {
        line->next = NULL;
        line->tile = first;
        line->length = 1;
    }
    //assert(line_n_correct(line, 1));
    return line;
}

domino_line line_add(domino_line line, domino t) {
    domino_line new_line = (domino_line) malloc(sizeof(struct _s_line));
    if (new_line != NULL) {
        new_line->tile = t;
        new_line->next = NULL;
        line->length = line->length + 1;

        domino_line curr = line;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = new_line;
    }
    return line;
}

unsigned int line_length(domino_line line) {
    return line->length;
}

bool line_n_correct(domino_line line, unsigned int n) {
    if(line_length(line) == 1){
        return true;
    }
    else{
        if (n == 0){
            return domino_matches(line->tile, line->next->tile);
        }
        else if(n == line_length(line)-1){
            domino_line aux = line;
            domino_line aux2;
            while(aux->next->next != NULL){
                aux = aux->next;
            }
            aux2 = aux->next;
            return domino_matches(aux->tile, aux2->tile );
        }
        else{
            unsigned int i = 0;
            domino_line aux = line;
            domino_line aux2;
            while(i<n-1 && aux->next!= NULL){
                aux = aux->next;
                i++;
            }
            aux2 = aux->next;
            return domino_matches(aux->tile, aux2->tile) && domino_matches(aux2->tile, aux2->next->tile);
        }
    }
}




int line_total_points(domino_line line) {
    domino *array = line_to_array(line);
    int total = 0;
    for (unsigned int i = 0u; i < line_length(line); i++) {
        total += domino_down(array[i]) + domino_up(array[i]);
    }
    free(array);
    return total;
}

domino * line_to_array(domino_line line) {
    domino *array = (domino *) malloc(line_length(line) * sizeof(domino));
    if (array != NULL) {
        domino_line curr = line;
        unsigned int i = 0;
        while (curr != NULL) {
            array[i] = curr->tile;
            curr = curr->next;
            i++;
        }
    }
    return array;
}

void line_dump(domino_line line) {
    domino *array = line_to_array(line);
    for (unsigned int i = 0u; i < line_length(line); i++) {
        domino_dump(array[i]);
    }
    free(array);
}

domino_line line_destroy(domino_line line) {
    if (line != NULL) {
        domino_line curr = line;
        while (curr != NULL) {
            domino_line next = curr->next;
            domino_destroy(curr->tile);
            free(curr);
            curr = next;
        }
    }
    return NULL;
}
