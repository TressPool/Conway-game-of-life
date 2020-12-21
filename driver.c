#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "graph.h"
#include "point2D.h"

/* Size of matrix **/
#define MATRIX_SIZE 40

/*** Function Prototypes **/
Graph* createAutomataState( int size );
void randomizeAutomataState( Graph *g, int size );
void updateAutomataState( Graph *g, int size );
bool updateAlive( bool b, int numAdjacent );
void printAutomataState( Graph *g, int size );

void createGlider( Graph *g, int size );
void createAcorn( Graph *g, int size );
void setAlive( Graph *g, int size, int i, int j );

int mod( int index, int modulus );


/**********************************************/
/***************** MAIN ***********************/
/**********************************************/
int main( int argc, char *argv[] )
{
    int size = MATRIX_SIZE;
    int i;
    char userInput = ' ';
    Graph *g;

    srand(time(0));

    g = createAutomataState( size );

    // play game until user quits
    while( userInput!='x' && userInput!='X' )
    {
        // print out menu
        printf("Enter r/R to randomize the graph.\n");
        printf("Enter u/U # to run update the graph that many times.\n");
        printf("Enter x/X to terminate.\n\n");
        // invalid input 
        do{
            scanf("%c", &userInput);
        } while( isspace(userInput) );

        //Simulate for given user input
        switch(userInput)
        {
            // randomize
            case 'r':
            case 'R':
                randomizeAutomataState( g, size );
                printAutomataState( g, size );
                break;
            // update board
            case 'u':
            case 'U':
                scanf("%d", &i);
                for( ; i>0; i--){
                    printAutomataState( g, size );
                    updateAutomataState( g, size );
                }
                break;
            // create glider
            case 'g': //Cheat code to make a glider
            case 'G':
                createGlider( g, size );
                printAutomataState( g, size );
                break;
            // create acorn
            case 'a': //Cheat code to make an acorn
            case 'A':
                createAcorn( g, size );
                printAutomataState( g, size );
                break;
        }
    }
    freeGraph( g ); // free the board that the cellular automata had made
    return 0;
}

/** Greats the automata board ***/
Graph* createAutomataState( int size ){
    int i,j;
    Graph* g = createGraph( size*size ); // creates the graph


    // inputing the vertices into the graph, they are all dead 
    for( i=0; i<size; i++ )
        for( j=0; j<size; j++ )
            addVertex( g, createPoint( i, j, false ) );

    // creating the edges for the graph
    for( i=0; i<size; i++ )
        for( j=0; j<size; j++ ){
            //orthogonal edges
            setEdge( g, createPoint( i, j, false ), createPoint( mod(i-1, size), j, false ), true );
            setEdge( g, createPoint( i, j, false ), createPoint( mod(i+1, size), j, false ), true );
            setEdge( g, createPoint( i, j, false ), createPoint( i, mod(j-1, size), false ), true );
            setEdge( g, createPoint( i, j, false ), createPoint( i, mod(j+1, size), false ), true );
            //diagonal edges
            setEdge( g, createPoint( i, j, false ), createPoint( mod(i-1, size), mod(j-1, size), false ), true );
            setEdge( g, createPoint( i, j, false ), createPoint( mod(i+1, size), mod(j-1, size), false ), true );
            setEdge( g, createPoint( i, j, false ), createPoint( mod(i-1, size), mod(j+1, size), false ), true );
            setEdge( g, createPoint( i, j, false ), createPoint( mod(i+1, size), mod(j+1, size), false ), true );
        }

    // creating the cellular automata graph
    return g;
}

void randomizeAutomataState( Graph *g, int size ){
    int i,j;
    Point2D *p;

    for( i=0; i<size; i++ )
        for( j=0; j<size; j++ ){
            p = getVertex( g, i*size+j );
            p->alive = (bool)(rand()%2);
        }
}

void updateAutomataState( Graph *g, int size ){
    int i,j,k,numAdjacent;
    Point2D *p, *q;

    for( i=0; i<size; i++ )
        for( j=0; j<size; j++ ){
            p = getVertex( g, i*size+j );
            numAdjacent=k=0;
            while( (q=getToEdge( g, *p, k++ )) )
                if( q->alive )
                    numAdjacent++;
            p->nextAlive = updateAlive( p->alive, numAdjacent );
        }

    for( i=0; i<size; i++ )
        for( j=0; j<size; j++ ){
            p = getVertex( g, i*size+j );
            p->alive = p->nextAlive;
        }
}

bool updateAlive( bool b, int numAdjacent ){
    if( numAdjacent<2 )
        return false;
    else if( numAdjacent==2 )
        return b;
    else if( numAdjacent==3 )
        return true;
    else //if( numAdjacent>3 )
        return false;
}

void printAutomataState( Graph *g, int size ){
    int i,j;
    Point2D* p;

    for( i=0; i<size; i++ ) {
        for( j=0; j<size; j++ ){
            p = getVertex( g, i*size+j );
            if( p->alive==true )
                printf("O");
            else
                printf(".");
        }
        printf("\n");
    }
    printf("\n");
}

//Creates the glider pattern near the top left of the matrix
void createGlider( Graph *g, int size ){
    setAlive( g, size, 1, 1 );
    setAlive( g, size, 2, 2 );
    setAlive( g, size, 2, 3 );
    setAlive( g, size, 3, 2 );
    setAlive( g, size, 3, 1 );
}

//Creates the acorn pattern near the center of the matrix
void createAcorn( Graph *g, int size ){
    int a = size/2-3;
    setAlive( g, size, a+3, a+1 );
    setAlive( g, size, a+3, a+2 );
    setAlive( g, size, a+1, a+2 );
    setAlive( g, size, a+2, a+4 );
    setAlive( g, size, a+3, a+5 );
    setAlive( g, size, a+3, a+6 );
    setAlive( g, size, a+3, a+7 );
}

void setAlive( Graph *g, int size, int i, int j ){
    Point2D *p;

    i = mod( i, size );
    j = mod( j, size );
    p = getVertex( g, i*size + j );
    p->alive = true;
}

int mod( int index, int modulus ){
    index = index%modulus;
    if( index<0 )
        index+=modulus;
    return index;
}
