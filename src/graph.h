/*
 * This is Graph Header File
 * This File Contains
 *      - Graph Structure
 *      - Graph Vertices Structure
 *      - Graph Edges Structure
 *      - Graph Function Decalarations
 *
 * Following API are available
 *
 * API                                            Functionality
 * Graph_t * Graph_init( );                       This Function is used to create
 *                                                basic template of Graph Object
 *
 * Graph_t * Graph_add_vertices(int N);            
 *
 *
 * Author: Kaushik, Koneru
 * Email : konerukaushik@gmail.com
 */

#ifndef  __GRAPH_H__
#define __GRAPH_H__

/* 
 * Basic Includes
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * List of typedef
 */
typedef struct graph_ Graph_t;
typedef struct graph_vertices_ Graph_vertices_t;
typedef struct graph_edge_ Graph_edges_t;
typedef int vertex_number_t;
typedef int edge_weight_t;
typedef int bool;

/* 
 * This Structure maintains
 * all information regarding Graph
 */
struct graph_ {
    vertex_number_t      total_vertices; /* To Store total number of vertices */
    edge_weight_t        total_edges;    /* To Store total number of edges */
    Graph_vertices_t    *vertices_list;  /* To store vertices */
    Graph_edges_t       *edges_list;     /* To store edges List, Connecting Vertices */
    vertex_number_t      source;         /* To Maintain Source Node */
    bool                 is_directed;    /* Set True If Graph is Directed, Else False */

};

/*
 * This Structure maintains
 * information regarding 
 * vertices in graph
 */
struct graph_vertices_ {
    vertex_number_t         interface_number;     /* To Store Vertex Index(Number) */

    bool                    is_visited;     /* To Check whether This 
                                              interface is parsed 
                                              This interface will be set False back
                                              once done with parsing */

    Graph_edges_t          *adjacency_list; /* To Maintain List of adjacent to 
                                               present vertex */
    long                    min_distance;   /* This is used to calculate 
                                               min distance from source to
                                               this vertex
                                            */
    Graph_vertices_t       *next;           /* Pointer to Next Vertex */
};

/*
 * This structure maintains
 * information regarding
 * edges in graph (Adjacency Matrix) 
 * So, This is used basing on particular vertex
 */
struct graph_edges_ {

    vertex_number_t        target; /* Target of the Edge */
    edge_weight_t          weight; /* Weight of the edge, If not given 
                                      determined as 1
                                    */
    Graph_edges_t         *next;   /* Pointer to next edge */
};

/*
 * Following Defines are to Make life easy
 */
#define LOG_ERR(f_, ...)   printf("%s:%d ERROR: "f_"\n",__FILE__, __LINE__, ## __VA_ARGS__)
#define LOG_INFO(f_, ...)  printf("%s:%d INFO:  "f_"\n",__FILE__, __LINE__, ## __VA_ARGS__)
#ifdef DEBUG
#define LOG_DEBUG(f_, ...) printf("%s:%d DEBUG: "f_"\n",__FILE__, __LINE__, ## __VA_ARGS__)
#else
#define LOG_DEBUG(f_, ...)
#endif /* DEBUG */
#define FALSE 0
#define TRUE  1

/*
 * NaN is maintain that int variable 
 * is still not available
 */
#define NaN     32767

/*
 * API Declaration
 */

Graph_t*  
Graph_init(int, bool);

Graph_vertices_t* 
Graph_add_vertices(Graph_t*, int);

void      
Graph_display_graph(Graph_t *);


#endif /* End of __GRAPH_H__ */
