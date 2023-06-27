#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "card.h"
#include "cf_match.h"

struct _s_match {
    card *cartas;
    unsigned int size;
};

cf_match match_new(void)
{
    cf_match new_game;
    new_game = malloc(sizeof(struct _s_match));
    new_game->cartas = NULL;
    new_game->size = 0;
    assert(new_game != NULL);
    return new_game;
}

cf_match match_add(cf_match match, card c)
{
    assert(match != NULL);
    size_t capac = match->size == 0 ? 1*sizeof(card) : (match->size+1)*sizeof(card);
    match->cartas = realloc(match->cartas, capac);
    match->cartas[match->size] = c;
    match->size++; 
    assert(match!=NULL && match->cartas != NULL && match->size!=0);
    return match;
}

unsigned int match_size(cf_match match)
{
    assert(match!=NULL);
    return match->size;
}

bool is_match_correct(cf_match match)
{
    assert(match!=NULL);
    bool correct = true;
    if(card_player(match->cartas[0])!= 1){
        return !correct;
    }
    else if(match->size % 2 != 0){
        return !correct;
    }
    else{
        for (unsigned int i = 0; i < match->size-1; i++){
            if(card_player(match->cartas[i]) == card_player(match->cartas[i+1])){
                return !correct;
            }
            else if(card_color(match->cartas[i]) == card_color(match->cartas[i+1])){
                return !correct;
            }
        }
    }
    return correct;
}

static int player_score(cf_match match, unsigned int player)
{
    assert(match!=NULL);
    bool isFlush;
    bool UpwardFlush;
    int points = 0;
    for(unsigned int i = 1; i < match->size; i++){
        if(i==1){
            isFlush = false;
            UpwardFlush = false;
        }
        else{
            if(card_number(match->cartas[i-1]) == card_number(match->cartas[i-2]) + 1 ){
                isFlush = true;
                UpwardFlush = true;
            }
            else if(card_number(match->cartas[i-1]) == card_number(match->cartas[i-2]) - 1){
                isFlush = true;
                UpwardFlush = false;
            }
            else{
                isFlush = false;
                UpwardFlush = false;
            }
        }
        if(player == 1 && i%2 == 0){
            points = points + card_drop_points(match->cartas[i-1], match->cartas[i], isFlush, UpwardFlush);

        }
        if (player == 2 && i%2 != 0){
            points = points + card_drop_points(match->cartas[i-1], match->cartas[i], isFlush, UpwardFlush);
        }
    }
    return points;
}

unsigned int match_winner(cf_match match)
{
    assert(match!=NULL);
    if (!is_match_correct(match)){
        return -1;
    }
    else if (player_score(match, 1) == player_score(match, 2)){
        return 0;
    }
    else if (player_score(match, 1) > player_score(match, 2 )){
        return 1;
    }
    else if (player_score(match, 1) < player_score(match, 2 )){
        return 2;
    }
    return 0;
}

unsigned int winner_total_points(cf_match match)
{
    if (!is_match_correct(match)) {
        return -1;
    }

    int playerOneScore = player_score(match, 1);
    int playerTwoScore = player_score(match, 2);

    if (playerOneScore == playerTwoScore) {
        return 0;
    }
    return playerOneScore > playerTwoScore ? playerOneScore : playerTwoScore;
}

card* match_to_array(cf_match match)
{
    return match->cartas;
}

void match_dump(cf_match match)
{
    card* array = match_to_array(match);
    for (unsigned int i = 0u; i < match_size(match); i++) {
        card_dump(array[i]);
    }
    free(array);
}

cf_match match_destroy(cf_match match)
{
    assert(match!=NULL);
    free(match);
    return NULL;
}