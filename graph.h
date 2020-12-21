#ifndef _graph_h
#define _graph_h
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "point2D.h"


/** Graph Type **/
typedef struct Point2D graphType;       // struct Point2D ====== graphType

/** Vertex **/
typedef struct Vertex
{
    bool visited;
    graphType data; // Point2D struct 
    int index;
}  Vertex;

/** Graph **/
typedef struct Graph
{
    Vertex* vertexArray;    // array of vertices
    bool** adjacencyMatrix; // 2 dimensional adjacency matrix
    int numVertices;    // number of vertices it currently has
    int capacity;   // the total capacity of total vertices it can contain
}  Graph;


/** Graph functions **/
Graph* createGraph( int numVertex );
void freeGraph( Graph* g );

/** Vertex functions **/
void addVertex( Graph* g, graphType p );
bool isVertex( Graph* g, graphType p );
graphType* getVertex( Graph* g, int index );


/** Edge functions **/
void setEdge( Graph* g, graphType p1, graphType p2, bool value );
bool getEdge( Graph* g, graphType p1, graphType p2 );

/** Get Edges **/
graphType* getToEdge( Graph* g, graphType from, int index );
graphType* getFromEdge( Graph* g, graphType to, int index );

/** Visited vertices **/
void setVisited( Graph* g, graphType p, bool value );
bool getVisited( Graph* g, graphType p );

#endif
