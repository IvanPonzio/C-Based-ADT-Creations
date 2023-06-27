#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "position.h"

struct _position {
        unsigned int row;
        unsigned int column;
        unsigned int dimension;
};


position_t position_initial(unsigned int dimension)
{
        position_t inicial;
        inicial = malloc(sizeof(struct _position));
        inicial->column = 0;
        inicial->row = 0;
        inicial->dimension = dimension;
        return inicial;
}

position_t position_absolute(unsigned int row, unsigned int column,
                             unsigned int dimension)
{
        assert(row <= dimension && column <= dimension);
        position_t absolute;
        absolute = malloc(sizeof(struct _position));
        absolute->column = column;
        absolute->row = row;
        absolute->dimension = dimension;
        return absolute;
}

position_t position_left(position_t pos)
{

        pos->column = (pos->column + pos->dimension - 1) % pos->dimension; 
        return pos;

}

position_t position_right(position_t pos)
{
        pos->column = (pos->column + pos->dimension + 1) % pos->dimension; 
        return pos;
        
}

position_t position_down(position_t pos)
{
        pos->row = (pos->row + pos->dimension + 1) % pos->dimension; 
        return pos;
        
}

position_t position_up(position_t pos)
{
        pos->row = (pos->row + pos->dimension - 1) % pos->dimension; 
        return pos;
}

unsigned int position_row(position_t pos)
{
        return pos->row;
}

unsigned int position_column(position_t pos)
{
        return pos->column;
}

unsigned int **position_board(position_t pos)
{
        unsigned int **board = calloc(pos->dimension, sizeof(unsigned int *));
        for (unsigned int i = 0; i < pos->dimension; i++)
        {
                board[i] = calloc(pos->dimension, sizeof(unsigned int));
                
        }
        board[pos->row][pos->column] = 1;
        return board;
        
}

list_t position_movements(position_t pos)
{       
        list_t list = list_empty();
        for (unsigned int i = 0; i < pos->column; i++)
        {
                list = list_append(list,RIGHT);
        }
        for (unsigned int i = 0; i < pos->row; i++)
        {
               list = list_append(list,DOWN);
        }
        return list;
}


position_t position_destroy(position_t pos)
{
    if (pos != NULL) {
        free(pos);
    }
    return NULL;
}
