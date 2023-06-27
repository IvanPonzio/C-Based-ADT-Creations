#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "position.h"
int main()
{
    unsigned int dimension;
    printf("Inserte aqui su dimension");
    scanf("%u" , &dimension);
    position_t matrix = position_initial(dimension);
    matrix = position_left(matrix);
    matrix = position_right(matrix);
    matrix = position_left(matrix);
    matrix = position_left(matrix);
    matrix = position_down(matrix);
    //matrix = position_up(matrix);
    unsigned int **board = position_board(matrix);
    printf("Board:\n");
    for (unsigned int i = 0; i < dimension; i++) {
        for (unsigned int j = 0; j < dimension; j++) {
            printf("%u ", board[i][j]);
        }
        printf("\n");
    }

    list_t movements = position_movements(matrix);
    printf("Movements:\n");
    list_it_t it = list_get_iterator(movements);
    while (!list_iterator_end(it)) {
        movement_t movement = list_iterator_elem(it);
        printf("%s ", movement == RIGHT ? "R" : "D");
        it = list_iterator_next(it);
    }
    printf("\n");

    position_destroy(matrix);
    list_destroy(movements);
    free(board);
    for (unsigned int i = 0; i < dimension; i++)
    {
        free(board[i]);
        
    }
    
    return 0;
}