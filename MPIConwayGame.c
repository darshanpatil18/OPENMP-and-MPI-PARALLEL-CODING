/*
Conway’s Game of Life is played on a rectangular grid of cells that may or may not contain an organism. The state of the cells is updated each time step by applying the following set of rules:  
•  Every organism with two or three neighbours survives.
•  Every organism with four or more neighbours dies from overpopulation.
•  Every organism with zero or one neighbours dies from isolation.
•  Every empty cell adjacent to three organisms gives birth to a new one.
Create an MPI program that evolves a board of arbitrary size (dimensions could be specified at the command line) over several iterations. The board could be randomly generated or real from a file. Try applying the geometric decomposition pattern to partition the work among your process.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <mpi.h>
#define NUMBERROWS 28
#define esc 27
#define cls() printf("%c[2]",esc)
#define pos(row,col) printf("%c[%d;%dH",esc,row,col)

char *DISH0[ NUMBERROWS ];
char *DISH1[ NUMBERROWS ];
char *PATTERN[NUMBERROWS] = {
 " ",
 " # ",
 " # # ### ",
 " ## ",
 " ",
 " # ",
 " # # ",
 " ## ",
 " ",
 " ",
 " ",
 " ",
 " # ",
 " # # ",
 " ## ",
 " ",
 " ",
 " ",
 " ",
 " ",
 " ",
 " ",
 " ",
 " ",
 " ",
 " ",
 " ",
 " "
};

int ROWSIZE = strlen(" ") + 1;
void life( char**, char**, int );
void initDishes( int );
void print( char **, int );
void initDishes( int rank ) {
 int i;
 for (i = 0; i< NUMBERROWS; i++ ) {
   DISH0[i] = (char *) malloc( ( strlen( PATTERN[0] ) + 1 ) * sizeof( char ) );
   strcpy( DISH0[i], PATTERN[i] );
   DISH1[i] = (char *) malloc( (strlen( DISH0[0] )+1) * sizeof( char ) );
   strcpy( DISH1[i], PATTERN[i] );
 }
}
void initDishes2( int rank ) {
 int i;
 for ( i=0; i<NUMBERROWS; i++ ) {
   DISH0[i] = NULL;
   DISH1[i] = NULL;
 }
 if ( rank == 0 ) {
 for (i = 0; i< NUMBERROWS/2+1; i++ ) {
   DISH0[i] = (char *) malloc( (strlen( PATTERN[0] ) + 1 ) * sizeof( char ) );
   strcpy( DISH0[i], PATTERN[i] );
   DISH1[i] = (char *) malloc( (strlen( DISH0[0] )+1) * sizeof( char ) );
   strcpy( DISH1[i], DISH0[i] );
 }
  DISH0[NUMBERROWS-1] = (char *) malloc( (strlen( PATTERN[0] ) + 1 ) * sizeof(char));
 strcpy( DISH0[NUMBERROWS-1], PATTERN[NUMBERROWS-1] );
 DISH1[NUMBERROWS-1] = (char *) malloc( (strlen( PATTERN[0] ) + 1 ) *
sizeof( char ) );
 strcpy( DISH1[NUMBERROWS-1], PATTERN[NUMBERROWS-1] );
}
 if ( rank == 1 ) {
 for (i = NUMBERROWS/2-1; i< NUMBERROWS; i++ ) {
 DISH0[i] = (char *) malloc( (strlen( PATTERN[0] ) + 1 ) * sizeof( char ) );
 strcpy( DISH0[i], PATTERN[i] );
 DISH1[i] = (char *) malloc( (strlen( DISH0[0] )+1) * sizeof( char ) );
 strcpy( DISH1[i], DISH0[i] );
 }
 DISH0[0] = (char *) malloc( (strlen( PATTERN[0] ) + 1 ) * sizeof( char ) );
 strcpy( DISH0[0], PATTERN[0] );
 DISH1[0] = (char *) malloc( (strlen( PATTERN[0] ) + 1 ) * sizeof( char ) );
 strcpy( DISH1[0], PATTERN[01] );
 }
}
void print( char* dish[], int rank ) {
 int i;
 if ( rank == 0 ) {
 for (i=0; i<NUMBERROWS/2; i++ ) {
 if ( dish[i] == NULL ) continue;
 pos( i, 0 );
 printf( "%s\n", dish[i] );
 }
 }
 if ( rank == 1 ) {
 for (i=NUMBERROWS/2; i<NUMBERROWS; i++ ) {
 if ( dish[i] == NULL ) continue;
 pos( i, 0 );
 printf( "%s\n", dish[i] );
 }
 }
}
void check( char** dish, char** future ) {
 int i, j, k, l;
 l = sizeof( dish )/sizeof( dish[0] );
 printf( "length of dish = %d\n", l );
 for ( i=0; i<l; i++ ) {
 k = strlen( dish[i] );
 printf( "%d %s\n", k, dish[i] );
 }
 printf( "\n\n" );
 l = sizeof( future )/sizeof( future[0] );
 printf( "length of future = %d\n", l );
 for ( i=0; i<l; i++ ) {
 k = strlen( future[i] );
 printf( "%d %s\n", k, future[i] );
 }
 printf( "\n\n" );
}
void life( char** dish, char** newGen, int rank ) {
 int i, j, row;
 int rowLength = strlen( dish[0] );
 int dishLength = NUMBERROWS;

 int lowerRow, upperRow;
 if ( rank == 0 ) {
 lowerRow = 0;
 upperRow = NUMBERROWS/2;
 }
 if ( rank == 1 ) {
 lowerRow = NUMBERROWS/2;
 upperRow = NUMBERROWS;
 }

 for (row = lowerRow; row < upperRow; row++) {

 if ( dish[row] == NULL )
 continue;
 for ( i = 0; i < rowLength; i++) {
 int r, j, neighbors = 0;
 char current = dish[row][i];
 for ( r = row - 1; r <= row + 1; r++) {
 int realr = r;
 if (r == -1)
 realr = dishLength - 1;
 if (r == dishLength)
 realr = 0;
 for (int j = i - 1; j <= i + 1; j++) {
 int realj = j;
 if (j == -1)
 realj = rowLength - 1;
 if (j == rowLength)
 realj = 0;
 if (r == row && j == i)
 continue;
 if (dish[realr][realj] == '#')
 neighbors++;
 }
 }
 if (current == '#') {
 if (neighbors < 2 || neighbors > 3)
 newGen[row][i] = ' ';
 else
 newGen[row][i] = '#';
 }
 if (current == ' ') {
 if (neighbors == 3)
 newGen[row][i] = '#';
 else
 newGen[row][i] = ' ';
 }
 }
 }
}
int main( int argc, char* argv[] ) {
 int gens = 3000;
 int i;
 char **dish, **future, **temp;
 int noTasks = 0;
 int rank = 0;
 MPI_Status status;
 MPI_Init( &argc, &argv );
 MPI_Comm_size( MPI_COMM_WORLD, &noTasks );
 if ( noTasks != 2 ) {
 printf( "Number of Processes/Tasks must be 2. Number = %d\n\n", noTasks );
 MPI_Finalize();
 return 1;
 }
 MPI_Comm_rank( MPI_COMM_WORLD, &rank );
 initDishes( rank );
 dish = DISH0;
 future = DISH1;
 cls();
 print( dish, rank );
 for ( i = 0; i < gens; i++) {
    pos( 33+rank, 0 );
   printf( "Rank %d: Generation %d\n", rank, i );
 life( dish, future, rank );
 if (rank==0 ) {
 MPI_Send( future[ 0 ], ROWSIZE, MPI_CHAR, 1, 0,
MPI_COMM_WORLD );
 MPI_Send( future[NUMBERROWS/2-1], ROWSIZE, MPI_CHAR, 1, 0,
MPI_COMM_WORLD );
 MPI_Recv( future[NUMBERROWS-1], ROWSIZE, MPI_CHAR, 1, 0,
MPI_COMM_WORLD, &status );
 MPI_Recv( future[NUMBERROWS/2], ROWSIZE, MPI_CHAR, 1, 0,
MPI_COMM_WORLD, &status );
 }
 if (rank==1 ) {
 MPI_Recv( future[ 0 ], ROWSIZE, MPI_CHAR, 0, 0,
MPI_COMM_WORLD, &status );
 MPI_Recv( future[NUMBERROWS/2-1], ROWSIZE, MPI_CHAR, 0, 0,
MPI_COMM_WORLD, &status );
 MPI_Send( future[NUMBERROWS-1], ROWSIZE, MPI_CHAR, 0, 0,
MPI_COMM_WORLD );
 MPI_Send( future[NUMBERROWS/2], ROWSIZE, MPI_CHAR, 0, 0,
MPI_COMM_WORLD );
 }
 temp = dish;
 dish = future;
 future = temp;
 }
 print(dish, rank);
 pos( 30+rank, 0 );
 MPI_Finalize();
 return 0;
}
