/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements the Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// board's minimal dimension
#define MIN 3

// board's maximal dimension
#define MAX 9

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];

// board's dimension
int d;

//global for space and temporary int storage
int tmp;


// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void save(void);
 

int main(int argc, string argv[])
{

    // greet player
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < MIN || d > MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            MIN, MIN, MAX, MAX);
        return 2;
    }

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // saves the current state of the board (for testing)
        save();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }
        
        // sleep for animation's sake
        usleep(500000);
        
    }

    // that's all folks
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
    printf("GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */
void init(void)
{
    int even = (d * d) % 2;
    int k = d * d - 1;
    
    //creates rows
    for(int i = 0; i < d; i++)
    {
        //creates columns
        for(int j = 0; j < d; j++)
        { 
        
          //if demensions of board are even, switch placement of 2 and 1. 0 equals character. 
          if(even == 0)
          {
                if(k == 2)
                {
                    board[i][j] = 1;
                    k--;
                }
                else if(k == 1)
                {
                    board[i][j] = 2;
                    k--;
                }
                else if(k == 0)
                {
                    board[i][j] = 95;
                    k--;
                }
                else
                {
                    board[i][j] = k;
                    k--;
                }    
          
          }
          //if demensions of board are odd create intergers in descending order. 0 equals character.  
          else
          {
              if( k == 0 )
              {
                 board[i][j] = 95;
                 k--;
              }
              else
              {      
                board[i][j] = k;
                k--;
              }
          }
        }
     }      
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{   
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {           
          if(board[i][j] == 95)
            {  
            printf(" %2c", (char) board[i][j]);
            }
          else
          {  
          printf(" %2d" , (board[i][j]));
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
    //checks to make sure d is between 3 and 9
    if(tile <= (d*d)-1 || tile > 0)
    {    
        //searches by row
        for(int i = 0; i < d; i++)
        {   
        
            //searches by column
            for(int j = 0; j < d; j++)
            {
            
                //if number at board location equals tile number, search all adjacent sides
                if((board[i][j]) == tile)
                {
                    
                    //if character is found below tile, switch integers and return true
                    if((board[i + 1][j]) == 95)
                    {   
                        tmp = board[i][j];
                        board[i][j] = board[i + 1][j];
                        board[i + 1][j] = tmp;
                        return true;    
                    }
                    //if space is found above tile, switch integers and return true
                    else if((board[i - 1][j]) == 95) 
                    {
                        tmp = board[i][j];
                        board[i][j] = board[i - 1][j];
                        board[i - 1][j] = tmp;
                        return true;
                    }
                    //if space is found to the right, switch integers and return true
                    else if((board[i][j + 1]) == 95)
                    {
                        tmp = board[i][j];
                        board[i][j] = board[i][j + 1];
                        board[i][j + 1] = tmp;
                        return true;
                    }
                    //if space is found to the left, switch integers and return true
                    else if((board[i][j - 1]) == 95)
                    {
                        tmp = board[i][j];
                        board[i][j] = board[i][j - 1];
                        board[i][j - 1] = tmp;
                        return true;
                    }
                    //if space isn't found, return false
                    else
                    {   
                        return false;
                    }
                }
            }    
        }
    }    
    else
    {   
        return false;
    }
return false;
}


/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
  //counter used to count through tiles  
  int counter = 1;  
  
  //search through columns
  for(int i = 0; i < d; i++)
  {
    //search through rows
    for(int j = 0; j< d; j++)
    {
        //if counter matches number at tile, add one to counter
        if(counter == board[i][j])
        {
            counter = counter + 1;
        }    
        
        //if counter doesn't match tile but has counted through all tiles, check if tile is 95, is is 95 return true
        else if(counter == d * d && board[i][j] == 95) 
        {
            return true;
        }    
        else
        {
            return false;
        }
    }
  }
  return false;  
}
/**
 * Saves the current state of the board to disk (for testing).
 */
void save(void)
{
    // log
    const string log = "log.txt";

    // delete existing log, if any, before first save
    static bool saved = false;
    if (!saved)
    {
        unlink(log);
        saved = true;
    }

    // open log
    FILE* p = fopen(log, "a");
    if (p == NULL)
    {
        return;
    }

    // log board
    fprintf(p, "{");
    for (int i = 0; i < d; i++)
    {
        fprintf(p, "{");
        for (int j = 0; j < d; j++)
        {
            fprintf(p, "%i", board[i][j]);
            if (j < d - 1)
            {
                fprintf(p, ",");
            }
        }
        fprintf(p, "}");
        if (i < d - 1)
        {
            fprintf(p, ",");
        }
    }
    fprintf(p, "}\n");

    // close log
    fclose(p);
}
