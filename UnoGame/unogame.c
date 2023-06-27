#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "unogame.h"
#include "card.h"

#define NO_PLAYER -1

typedef struct s_unonode {
    card_t card;
    player_t player;
    struct s_unonode *next;
} unonode_t;

struct s_ugame {
    unonode_t *top;
    color_t current_color;
    unsigned int count;
};

unogame_t
uno_newgame(card_t card) {
    unogame_t uno = malloc(sizeof(struct s_ugame));
    assert(uno != NULL);

    unonode_t *node = malloc(sizeof(unonode_t));
    assert(node != NULL);

    node->card = card;
    node->player = NO_PLAYER;
    node->next = NULL;

    uno->top = node;
    uno->current_color = card_get_color(card);
    uno->count = 1;

    return uno;
}

card_t
uno_topcard(unogame_t uno) {
    assert(uno != NULL && uno->top != NULL);

    return uno->top->card;
}

unogame_t
uno_addcard(unogame_t uno, card_t c) {
    assert(uno != NULL);

    unonode_t *node = malloc(sizeof(unonode_t));
    assert(node != NULL);

    node->card = c;
    node->player = uno_nextplayer(uno);
    node->next = uno->top;
    uno->top = node;

    uno->current_color = card_get_color(c);
    uno->count++;

    return uno;
}

unsigned int
uno_count(unogame_t uno) {
    assert(uno != NULL);

    return uno->count;
}

bool
uno_validpile(unogame_t uno) {
    assert(uno != NULL);

    if (uno->count == 1) {
        return true;
    }

    card_t top = uno_topcard(uno);
    unonode_t *node = uno->top;

    while (node != NULL) {
        if (!card_compatible(node->card, top)) {
            return false;
        }

        node = node->next;
    }

    return true;
}

color_t
uno_currentcolor(unogame_t uno) {
    assert(uno != NULL);

    return uno->current_color;
}

player_t
uno_nextplayer(unogame_t uno) {
    assert(uno != NULL);

    if (uno->top->player == NO_PLAYER && card_get_type(uno->top->card) != skip) {
        return 0;
    }

    if (uno->top->player == NO_PLAYER && card_get_type(uno->top->card) == skip) {
        return 1;
    }

    player_t next_player = (uno->top->player + 1) % NUM_PLAYERS;
    if (card_get_type(uno->top->card) == skip)
    {
        next_player = (uno->top->player + 2) % NUM_PLAYERS;
    }
    

    return next_player;
}

card_t *
uno_pile_to_array(unogame_t uno) {
    assert(uno != NULL);

    card_t *cards = malloc(sizeof(card_t) * uno->count);
    assert(cards != NULL);

    unonode_t *node = uno->top;
    unsigned int i = 0;

    while (node != NULL) {
        cards[uno->count - i - 1] = node->card;
        node = node->next;
        i++;
    }

    return cards;
}


unogame_t
uno_destroy(unogame_t uno) {
    assert(uno != NULL);

    unonode_t *node = uno->top;

    while (node != NULL) {
        unonode_t *next = node->next;
        free(node);
        node = next;
    }

    free(uno);

    return NULL;
}
