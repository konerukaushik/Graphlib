/*
 * In this File we define various function & API regarding Graph 
 * for C Library
 * 
 * Author: Kaushik, Koneru
 * Email: konerukaushik@gmail.com
 */

#include <graph.h>


/*
 * Function: Graph_add_vertices()
 *
 * In this function we create 
 * single vertex and return it
 *
 * Input : none
 * output: Graph_vertices_t object or NULL
 */
Graph_vertices_t *
Graph_add_vertices() {
  
    Graph_vertices_t     *V;

    V = (Graph_vertices_t *)malloc(sizeof(Graph_vertices_t));
    if (V == NULL) {
      LOG_ERR("Unable to assign Memory for Vertices");
      goto destroy;
    }

    /* Initialize V with template */
    V->interface_number   = NaN;
    V->is_visited         = false;
    V->adjacency_list     = NULL;
    V->min_distance       = NaN;
    V->next               = NULL;


    return V;
destroy:
    free(V);
    return NULL;
}

/*
 * Function: Graph_add_vertices(int N)
 *
 * In this function we create 
 * single vertex and return it
 *
 * Input : N <- No Of vertices to create
 *         G <- To Which we need to append N vertices
 * output: Graph_vertices_t object or NULL
 */
Graph_vertices_t *
Graph_add_vertices(Graph_t *G, int no_of_vertices) {
  
    Graph_vertices_t     *V        = NULL;
    Graph_vertices_t     *runner   = NULL;
    int                   iterator = G->no_of_vertices;

    V = G->vertices_list;


    while(V != NULL || V->next != NULL) {
      V = V->next;
    }

    while(iterator < no_of_vertices + G->no_of_vertices) {

      runner  = Graph_add_vertices();
      if (runner == NULL) {
        goto destroy;
      }

      runner->interface_number = iterator;

      if (V == NULL) {
          V       = runner;
      } else {
          V->next = runner;
          V       = V->next;
      }

      runner = runner->next;

      G->no_of_vertices++;

      iterator++;
    }

    return G->vertices_list;

destroy:
    free(V);
    free(runner);
    return G->vertices_list;;
}
/* 
 * In this function we create 
 * Graph Object and initiate basic template
 *
 * Input : none
 * Output: Graph_t Object
 */
Graph_t *
Graph_init() {

    Graph_t         *G = NULL;

    /* 
     * Allocate Memory for Graph Object 
     */
    G   =   (Graph_t *) malloc(sizeof(Graph_t));
    if (G = NULL) {
        LOG_ERR("Unable to allocate memory");
        goto destroy;
    }

    /* 
     * Initialize variables
     */
    G->total_vertices   =   0;
    G->total_edges      =   0;
    G->vertices_list    =   NULL;
    G->edges_list       =   NULL;
    G->source           =   NaN;

    return G;

destroy:
    free(G);
    return NULL;
}


/* 
 * In this function we create 
 * Graph Object and initiate basic template
 * and Initialize N Vertices (Passed as Argument)
 *
 * Input : int no_of_vertices
 * Output: Graph_t Object
 */
Graph_t *
Graph_init(int no_of_vertices) {
    
    Graph_t             *G      = NULL;

    G   =   Graph_init();
    if(G == NULL) {
        LOG_ERR("Unable to Initialize %d vertices",no_of_vertices);
        goto destroy;
    }

    G->vertex = Graph_add_vertices(no_of_vertices);
    if (G->vertex == NULL) {
      LOG_ERR("Unable to create %d vertices",no_of_vertices);
      goto destroy;
    }

    return G;

destroy:
    free(G);
    return NULL;
}
