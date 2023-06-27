#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "card.h"

// Definición de la estructura s_card
struct s_card {
    unsigned int num;
    color_t color;
    type_t type;
};

static bool
invrep(card_t c) {
    // Invariante de representación
    bool valid=false;
    valid = c != NULL;
    /*
     * [COMPLETAR]
     *
     * Mejorar la invariante chequeando más
     * propiedades de los campos de la estructura
     *
     */
    return valid;
}



// Función para crear una carta nueva
card_t card_new(unsigned int num, color_t color, type_t s) {
    card_t card = malloc(sizeof(struct s_card));
    card->num = num;
    card->color = color;
    card->type = s;
    assert(invrep(card));
    return card;
}

// Función para obtener el número de la carta
unsigned int card_get_number(card_t card) {
    assert(invrep(card));
    return card->num;
}

// Función para obtener el color de la carta
color_t card_get_color(card_t card) {
    assert(invrep(card));
    return card->color;
}

// Función para obtener el tipo de la carta
type_t card_get_type(card_t card) {
    assert(invrep(card));
    return card->type;
}

// Función para verificar si dos cartas son del mismo color
bool card_samecolor(card_t c1, card_t c2) {
    assert(invrep(c1) && invrep(c2));
    return (c1->color == c2->color);
}

// Función para verificar si dos cartas tienen el mismo número
bool card_samenum(card_t c1, card_t c2) {
    assert(invrep(c1) && invrep(c2));
    return (c1->num == c2->num);
}

// Función para verificar si una carta es compatible con la carta en el tope de la pila de descarte
bool card_compatible(card_t new_card, card_t pile_card) {
    bool compatible = false;
    assert(invrep(new_card) && invrep(pile_card));
    if (new_card->type == pile_card->type) {
        // Cartas especiales siempre son compatibles
        compatible = true;
    } else if (new_card->num == pile_card->num || new_card->color == pile_card->color) {
        // Cartas con el mismo número o color son compatibles
        compatible = true;
    }
    return compatible;
}

// Función para destruir una carta y liberar la memoria
card_t card_destroy(card_t card) {
    assert(invrep(card));
    free(card);
    return NULL;
}
