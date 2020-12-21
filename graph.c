#include "graph.h"

int getIndex( Graph* g, graphType p );

/* create
 * input: none
 * output: a pointer to a Graph (this is malloc-ed so must be freed eventually!)
 *
 * Creates a new empty Graph and returns a pointer to it.
 */
Graph* createGraph( int capacity )
{
    int i,j;
    Graph* g = (Graph*)malloc(sizeof(Graph));   // allocate memory for struct graph
    g->vertexArray = (Vertex*)malloc(sizeof(Vertex)*capacity); // allocate memory for Vertex array
    g->adjacencyMatrix = (bool**)malloc(sizeof(bool*)*capacity); // allocate memory for adjacency matrix

    // allocate memory for the pointers in the adjacency matrix
    for( i=0; i<capacity; i++ )
        g->adjacencyMatrix[i] = (bool*)malloc(sizeof(bool)*capacity);

    // initialize values in adjacency matrix
    for( i=0; i<capacity; i++ )
        for( j=0; j<capacity; j++ )
            g->adjacencyMatrix[i][j] = false;

    // initialize graph values
    g->numVertices = 0;
    g->capacity = capacity;
    return g;
}

/* freeGraph
 * input: a pointer to a Graph
 * output: none
 *
 * frees the given Graph and all of it's Vertex elements
 */
void freeGraph( Graph* g )
{
    int i;

    // the graph is null
    if( g==NULL ){
        printf("ERROR - Attempt to free NULL Graph pointer\n");
        exit(-1);
    }

    // free the adjacency matrix pointers
    for( i=0; i<g->capacity; i++ )
        free(g->adjacencyMatrix[i]); // free adjacency matrix pointers

    free(g->adjacencyMatrix);   // free the adjacency matrix
    free(g->vertexArray);   // free the vertex array
    free(g);    // free the graph
}

/* addVertex
 * input: a pointer to a Graph, a graphType p
 * output: none
 *
 * adds a new vertex to the graph with its data set to p
 */
void addVertex( Graph* g, graphType p ){
    // unable to add vertex because capactiy is met
    if( g->numVertices==g->capacity){
        printf("ERROR - Attempt to add more vertices than the capacity of the graph\n");
        exit(-1);
    }

    // initialize the values for the vertex in the vertex array
    g->vertexArray[g->numVertices].data = p;
    g->vertexArray[g->numVertices].index = g->numVertices;

    // increment the number of vertices for the graph
    g->numVertices++;
}

/* isVertex
 * input: a pointer to a Graph, a graphType p
 * output: a bool
 *
 * returns true if the given graphType is contained in the graph
 */
bool isVertex( Graph* g, graphType p ){
    return getIndex( g, p )!=-1;
}

/* getVertex
 * input: a pointer to a Graph, an int, a pointer to a graphType
 * output: a bool
 *
 * finds index-th vertex added to the graph and returns a pointer to its data.
 * Alternatively, returns NULL if no such vertex exists.
 */
graphType* getVertex( Graph* g, int index ){
    if( index>=g->numVertices )
        return NULL;
    return &g->vertexArray[index].data;
}

/* setEdge
 * input: a pointer to a Graph, two graphType variables, a bool
 * output: none
 *
 * Sets the specified edge in the graph to the bool value
 */
void setEdge( Graph* g, graphType p1, graphType p2, bool value )
{
    int i = getIndex( g, p1 );
    int j = getIndex( g, p2 );

    if( i==-1 || j==-1){
        printf("ERROR - Attempt to set invalid edge\n");
        exit(-1);
    }

    g->adjacencyMatrix[i][j] = value;
}

/* getEdge
 * input: a pointer to a Graph, two graphType variables
 * output: a bool
 *
 * Returns whether the specified edge is in the graph
 */
bool getEdge( Graph* g, graphType p1, graphType p2 )
{
    int i = getIndex( g, p1 );
    int j = getIndex( g, p2 );

    if( i==-1 || j==-1){
        printf("ERROR - Attempt to get invalid edge\n");
        exit(-1);
    }

    return g->adjacencyMatrix[i][j];
}

/* getToEdge
 * input: a pointer to a Graph, a graphType 'from', an int, a pointer to a graphType 'to'
 * output: a bool
 *
 * Finds index-th edge starting at 'from'.  It returns a pointer to the destination of this edge.
 * Returns NULL if no such edge exists.
 */
graphType* getToEdge( Graph* g, graphType from, int index )
{
    int i = getIndex( g, from );
    int j;

    if( i==-1 ){
        printf("ERROR - Attempt to call getToEdge for invalid vertex\n");
        exit(-1);
    }

    for( j=0; j<g->numVertices; j++ ){
        if( g->adjacencyMatrix[i][j]==true )
            index--;
        if( index<0 ){
            return &g->vertexArray[j].data;
        }
    }
    return NULL;
}

/* getFromEdge
 * input: a pointer to a Graph, a graphType 'to', an int, a pointer to a graphType 'from'
 * output: a bool
 *
 * Finds index-th edge ending at 'to'.  It returns a pointer to the origin of this edge.
 * Returns NULL if no such edge exists.
 */
graphType* getFromEdge( Graph* g, graphType to, int index )
{
    int i;
    int j = getIndex( g, to );

    if( j==-1 ){
        printf("ERROR - Attempt to call getFromEdge for invalid vertex\n");
        exit(-1);
    }

    for( i=0; i<g->numVertices; i++ ){
        if( g->adjacencyMatrix[i][j]==true )
            index--;
        if( index<0 ){
            return &g->vertexArray[i].data;
        }
    }
    return NULL;
}

/* getIndex
 * INTERNAL USE ONLY
 */
int getIndex( Graph* g, graphType p ){
    int i;

    for( i=0; i<g->numVertices; i++){
        if( equals(g->vertexArray[i].data, p) )
            return i;
    }
    return -1;
}

void setVisited( Graph* g, graphType p, bool value ){
    int i = getIndex( g, p );

    if( i==-1 ){
        printf("ERROR - Attempt to set visited for invalid vertex\n");
        exit(-1);
    }

    g->vertexArray[i].visited = value;
}

bool getVisited( Graph* g, graphType p ){
    int i = getIndex( g, p );

    if( i==-1 ){
        printf("ERROR - Attempt to get visited for invalid vertex\n");
        exit(-1);
    }

    return g->vertexArray[i].visited;
}
