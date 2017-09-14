/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
void swap(int row1, int col1, int row2, int col2);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
         clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    
    
    //
    int value = d * d - 1;

    for(int i = 0; i < d; i++)
    {
        //
        for(int j = 0; j < d; j++)
        {
            board[i][j] = value;
            value--;
            
        }
        
    }
    
    // if d is even ie odd number of tiles swap 1 and 2
    if (d % 2 == 0)
    {
        board[d-1][d-2] = 2; 
        board[d-1][d-3] = 1; 
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    //
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            
            if (board[i][j] == 0)
            {
                printf(" _ ");
            }
            
            else if(board[i][j] >= 10)// has 2 digits
            {
                printf("%i ", board[i][j]);
            }
            else// has one digit. incude a space
            {
                printf(" %i ", board[i][j]);
            }
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    int tileRow = -1;
    int tileCol = -1; 
    // linear search for tile
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            if (board[i][j] == tile)
            {
                tileRow = i;
                tileCol = j;
                // break out of loops
            }
        }
    }
    
    // tile not found
    if (tileRow == -1 || tileCol == -1) 
    { 
        printf("Tile not found");
        return false; 
        
    }
    
    int zeroRow = -1;
    int zeroCol = -1;
    // check boarding tiles. is there a better way to do this?
    if (tileRow > 0 && board[tileRow-1][tileCol] == 0) // check up
    {
        zeroRow = tileRow-1;
        zeroCol = tileCol;
    }
    else if (tileRow < d-1 && board[tileRow+1][tileCol] == 0) // check down
    {
        zeroRow = tileRow+1;
        zeroCol = tileCol;
    }
    else if (tileCol > 0 && board[tileRow][tileCol-1] == 0) // check left
    {
        zeroRow = tileRow;
        zeroCol = tileCol-1;
    }
    else if (tileCol < d-1 && board[tileRow][tileCol+1] == 0) // check right
    {
        zeroRow = tileRow;
        zeroCol = tileCol+1;
    }
    else 
    { 
        printf("Blank not adjacent");
        return false; }// tile not adjacent to 0
    
    // if tile boarders 0 swap the tiles
    swap(tileRow, tileCol, zeroRow, zeroCol);
    return true;
}

/**
 * swap the position of two tiles on the board
 */
 void swap(int row1, int col1, int row2, int col2)
 {
     int copy = board[row1][col1];
     board[row1][col1] = board[row2][col2];
     board[row2][col2] = copy;
     
 }

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int value = 1;
    int max = d*d;
    for(int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] != value % max) // done so that d*d maps to 0. ex: 16%16 = 0 
            { return false; }
            value++;
        }
    }
    
    return true;
}