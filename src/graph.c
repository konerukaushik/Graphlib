/*
 * In this File we define various function & API regarding Graph 
 * for C Library
 * 
 * Author: Kaushik, Koneru
 * Email: konerukaushik@gmail.com
 */

/*
 *
 * ToDo:
 *  -> Need to replace Shallow Copying with Depth Copying
 *  -> Need to Modularize the Graph_add_edge directed version
 */

#include "graph.h"

/*Function:
 * Graph_node_in_adjacency
 *
 * In this function we verify whether the node is
 * present in adjacency List of a vertex
 *
 * Input:
 *      Graph_edges_t
 *      vertex_number_t
 *
 * Output:
 *      bool - True  - IF Present
 *             False - IF not Present
 */
bool
Graph_node_in_adjacency(Graph_edges_t *adjacency_list, vertex_number_t node) {
  
  Graph_edges_t         *runner;

  runner  = adjacency_list;

  while(runner != NULL) {
    if (runner->target == node) {
      return TRUE;
    }
    runner = runner->next;
  }

  return FALSE;
}

/*
 * Function:
 *  Graph_has_edge
 *
 * In this function we validate whether
 * there is a edge between
 * two vetices
 *
 * Input:
 *    Graph_t
 *    vertex_number_t
 *    vertex_number_t
 *
 * Output:
 *     bool True <-- If there is Edge
 *          False <-- If there is no Edge
 */
bool
Graph_has_edge(Graph_t *G, vertex_number_t S, vertex_number_t D) {

  Graph_vertices_t    *vertex;

  vertex  = Graph_get_vertex(G,S);
  if (vertex == NULL) {
    LOG_DEBUG("Vertex :%d has no edges",S);
    return FALSE;
  }

  return Graph_node_in_adjacency(vertex->adjacency_list,D);

}

/*
 * Function:
 *  Graph_node_in_priority_list
 *
 *  In this function we verify
 *  whether node is already present in 
 *  priority_list before appending to
 *  priority_list
 *
 * Input
 *    Graph_priority_t
 *    vertex_number_t
 *
 * output
 *    True (If already present)
 *    False (If not present)
 */
bool
Graph_node_in_priority_list(Graph_priority_t *prio,
                              vertex_number_t node) {
    Graph_priority_t    *S;

    S = prio;

    while(S != NULL) {
      if (S->vertex == node) {
        return TRUE;
      }
      S = S->next;
    }

    return FALSE;
}

/* Function:
 * Graph_dump_prio_list
 *
 * In this function we dump complete Priority 
 * List
 *
 * Input:
 *    Graph_priority_t *S
 *
 * Output:
 *    none
 */
void
Graph_dump_prio_list(Graph_priority_t *S) {

  Graph_priority_t      *runner = S;


  if (S == NULL) {
    LOG_DEBUG("Priority List is NULL");
    return;
  }

  printf("<-----Prio List ----->\n");
  while(S != NULL) {
    printf(" Node -> %d\n",S->vertex);
    S = S->next;
  }
  printf("<-------------------->\n");


  return;
}

/*
 * Function:
 * Graph_get_vertex
 *
 * In this function we vertex pointer
 * from graph
 *
 * Input:
 *      Graph_t   
 *      vertex_number_t
 *
 * Output:
 *      Graph_vertices_t
 */
Graph_vertices_t *
Graph_get_vertex(Graph_t *G, vertex_number_t node) {
  
    Graph_vertices_t    *runner;

    runner  = G->vertices_list;

    while(runner != NULL && runner->interface_number != node) {
      runner = runner->next;
    }

    return runner;
}

/*
 * Function:
 * Graph_add_edge_to_vertex
 *
 * In this function we append new_edge to
 * the adjacency list of vertices list
 *
 * Input: Graph_edges_t     adjacency_list
 *        Graph_edges_t     new_edge
 * output:
 *        Graph_edges_t* (Graph Vertex adjacencyList)
 */
Graph_edges_t *
Graph_add_edge_to_vertex(Graph_edges_t  *adjacency_list,
                         Graph_edges_t  *new_edge) {

  Graph_edges_t      *runner; /* To Parse through to vertices_list */
  
  if (adjacency_list == NULL) {
    free(runner);
    return new_edge;
  }

  runner = adjacency_list;

  /* Parse till we reach end of Adjacency List */
  while(runner->next != NULL) {
    runner = runner->next;
  }

  /* Append the New edge to List */
  runner->next = new_edge;

  return adjacency_list;
}

/* 
 * Function:
 * Graph_add_edge_template
 *
 * In this function we create new Edge Object
 * to append into the vertices Adjacency List
 * So, We consider destination and weight only
 *
 * Input:
 *      vertex_number_t destination (Destination Vertex)
 *      edge_weight_t   weight  (Weight of edge)
 * Output:
 *      Graph_edges_t  (new edge Object)
 */
Graph_edges_t *
Graph_add_edge_template(vertex_number_t Destination,
                        edge_weight_t   weight) {

    Graph_edges_t      *temp;

    temp = (Graph_edges_t *)malloc(sizeof(Graph_edges_t));

    if (temp == NULL) {
      LOG_ERR("Unable to allocate memory for Edge with Dest:%d",Destination);
      goto destroy;
    }

    temp->target = Destination;
    temp->weight = weight;
    temp->next   = NULL;

    return temp;
    
destroy:
    free(temp);
    return NULL;
}

/* Function: Graph_append_edge
 * In this function we add edges
 * to a Specifc Graph
 *
 * Input:
 *      G <-- Graph In which we Need to Append the Edge
 *      Source <-- This will Source
 *      weight <-- Edge Weight
 *      Destination <-- This is Destination
 * Output:
 *      Modified G
 */
Graph_t *
Graph_append_edge(Graph_t *G, vertex_number_t S, vertex_number_t D,
                  edge_weight_t weight) {

  Graph_edges_t       *new_edge;
  Graph_vertices_t    *vertex;
  int                  found = 0;

  new_edge   =  Graph_add_edge_template(D, weight);
  if (new_edge == NULL) {
    LOG_ERR("Unable to Create edge Template for Source %d - Destination %d\n",S,D);
    goto destroy;
  }

  vertex  = Graph_get_vertex(G, S);
  if (vertex == NULL) {
    LOG_ERR("Unable to find vertex: %d",S);
    goto destroy;
  }

  /* If we are unable to add certain edge, Notify User
   * and Proceed to execute further
   */
  vertex->adjacency_list = Graph_add_edge_to_vertex(vertex->adjacency_list, new_edge);

  return G;

destroy:
  free(vertex);
  free(new_edge);
}
      
/*
 * Function: Graph_add_edge
 *
 * This function is the API for 
 * adding Edge
 *
 * Input:
 *      G <-- Graph In which we Need to Append the Edge
 *      Source <-- This will a 
 *      Destination <-- 
 *      is_directed <-- if then add to specific one vertices
 *                      else add to both vertices
 *                     
 */
Graph_t *
Graph_add_edge(Graph_t *G, vertex_number_t S, vertex_number_t D,  
                edge_weight_t weight, bool is_directed) {

  
  G = Graph_append_edge(G,S,D,weight);

  if (!is_directed) {
    G = Graph_append_edge(G,D,S,weight);
  }

  return G;
}
  

/*
 * Function: Graph_add_vertices_template()
 *
 * In this function we create 
 * single vertex and return it
 *
 * Input : none
 * output: Graph_vertices_t object or NULL
 */
Graph_vertices_t *
Graph_add_vertices_template() {
  
    Graph_vertices_t     *V;

    V = (Graph_vertices_t *)malloc(sizeof(Graph_vertices_t));
    if (V == NULL) {
      LOG_ERR("Unable to assign Memory for Vertices");
      goto destroy;
    }

    /* Initialize V with template */
    V->interface_number   = NaN;
    V->is_visited         = FALSE;
    V->adjacency_list     = NULL;
    V->min_distance       = NaN;
    V->next               = NULL;


    return V;

destroy:
    free(V);
    return NULL;
}

/*
 * Function: Graph_add_vertices
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
    int                   iterator = G->total_vertices;

    V = G->vertices_list;

    while(V != NULL && V->next != NULL) {
      V = V->next;
    }

    while(iterator < no_of_vertices + G->total_vertices) {
      LOG_DEBUG("Memory Appending for vertices %d",iterator);
      LOG_DEBUG("Total required vertices %d, Present vertices %d",no_of_vertices, G->total_vertices);

      runner  = Graph_add_vertices_template();
      if (runner == NULL) {
        LOG_ERR("Runner is NULL for iterator %d",iterator);
        goto destroy;
      }

      LOG_DEBUG("Appending Vertex with ID:%d",iterator);
      runner->interface_number = iterator;

      if (V == NULL) {
          V                = runner;
          G->vertices_list = V;
      } else {
          V->next = runner;
          V       = V->next;
      }
    
      runner = runner->next;

      iterator = iterator + 1;
    }

    G->total_vertices += iterator;

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
Graph_init_template() {

    Graph_t         *G = NULL;

    /* 
     * Allocate Memory for Graph Object 
     */
    G   =   (Graph_t *) malloc(sizeof(Graph_t));
    if (G == NULL) {
        LOG_ERR("Unable to allocate memory");
        goto destroy;
    }

    /* 
     * Initialize variables
     */
    G->total_vertices   =   0;
    G->total_edges      =   0;
    G->vertices_list    =   NULL;
    G->source           =   NaN;
    G->is_directed      =   FALSE;

    return G;

destroy:
    free(G);
    return NULL;
}


/* 
 * In this function we create 
 * Graph Object and initiate basic template
 * and Initialize N Vertices and 
 * set if it is a Directed or Not (Passed as Argument)
 *
 * Input : int no_of_vertices
 *         bool is_directed
 * Output: Graph_t Object
 */
Graph_t *
Graph_init(int no_of_vertices, bool is_directed) {
    
    Graph_t             *G      = NULL;

    G   =   Graph_init_template();
    if(G == NULL) {
        LOG_ERR("Unable to Initialize %d vertices",no_of_vertices);
        goto destroy;
    }

    Graph_add_vertices(G, no_of_vertices);
    if (G->vertices_list  == NULL) {
      LOG_ERR("Unable to create %d vertices",no_of_vertices);
      goto destroy;
    }

    G->is_directed = is_directed; 

    return G;

destroy:
    free(G);
    return NULL;
}


/*
 * Function
 * Graph_dump_vertices
 *
 * In this function we display Vertices with 
 * Adjacency List
 * 
 * Input:
 *      Graph_vertices_t  - Vertices
 *      print_adjacency   - True/False (If adjacency needs
 *                                      to be printed)
 * Output:
 *      no-return
 */
void
Graph_dump_vertices(const Graph_vertices_t *V, bool print_adjacency) {
  
    Graph_edges_t       *adjacency_list;

    if (V == NULL) {
      return;
    }

    printf("-------------------------\n");
    printf("| Vertex ID : %4d      |\n",V->interface_number);
    printf("| is_visited: %s     |\n",V->is_visited?"TRUE":"FALSE");
    if (V->min_distance == NaN) {
      printf("| min_dis   : NaN       |\n");
    } else {
      printf("| min_dis   : %3lu       |\n",(V->min_distance));
    }
    printf("-------------------------\n");

    if (print_adjacency) {
      if (V->adjacency_list != NULL) {
        printf("-------------------------\n");
        printf("Adjacency ");
        adjacency_list = V->adjacency_list;
        while(adjacency_list != NULL) {
          printf("%3d",adjacency_list->target);
          adjacency_list = adjacency_list->next;
        }
        printf("\n");
        printf("-------------------------\n");

      }
    }

    return;
}

/*
 * Function:
 * Graph_display_graph
 *
 * In this function we display complete graph 
 * Information
 *
 * Input: 
 *      Graph_t  - Graph Pointer
 *
 * Output:
 *      NULL
 */
 void
 Graph_display_graph(const Graph_t *G) {
  
   Graph_vertices_t         *V_parse;

   if (G == NULL) {
    LOG_INFO("Provided Graph to display is NULL");
    goto destroy;
   }

   if (G->total_vertices == 0 ) {
     LOG_INFO("There are no vertices in the Graph");
     goto destroy;
   }

   if (G->vertices_list == NULL) {
      LOG_ERR("Unable to retrieve interfaces info from Graph");
      goto destroy;
   }

   V_parse  = G->vertices_list;

   while (V_parse != NULL) {
     Graph_dump_vertices(V_parse, TRUE);
     V_parse = V_parse->next;
   }
 
destroy:

   free(V_parse);
   return;
 }


Graph_vertices_t *
Graph_Dj_get_next_vertex(Graph_t *G, Graph_priority_t *priority_list) {

  if (priority_list == NULL) {
    return NULL;
  }

  return Graph_get_vertex(G,priority_list->vertex); 
}

Graph_priority_t *
Graph_get_priority_list_template() {

  Graph_priority_t      *temp;

  temp  = (Graph_priority_t *) malloc(sizeof(Graph_priority_t));
  if (temp == NULL) {
      LOG_ERR("Unable to allocate memory for new Prio List");
      goto destroy;
  }

  temp->vertex = 0;
  temp->next   = NULL;

  return temp;

destroy:
  free(temp);
  return NULL;
}

bool
Graph_Dj_set_min_distance(Graph_t *G,
                          edge_weight_t weight, 
                          vertex_number_t vertex_ID) {

  Graph_vertices_t            *vertex;

  vertex  = Graph_get_vertex(G,vertex_ID);
  if (vertex == NULL) {
    LOG_ERR("Unable to find vertex with ID :%d ",vertex_ID);
    return FALSE;
  }


  if (vertex->min_distance > weight) {
      vertex->min_distance = weight;
      return TRUE;
  }

  return FALSE;
}

Graph_priority_t *
Graph_get_priority_list(Graph_t *G,
                         Graph_priority_t  *priority_list, 
                          Graph_vertices_t *vertex) {

  Graph_edges_t             *adjacency_list;
  Graph_priority_t          *prio_runner;
  Graph_priority_t          *temp;

  /* Need to make sure that vertex sent is proper */
  assert(vertex);

  adjacency_list  = vertex->adjacency_list;
  prio_runner     = priority_list;

  while(prio_runner != NULL && prio_runner->next != NULL ) {
    prio_runner = prio_runner->next;
  }

  while(adjacency_list != NULL) {
    /* Add to Priority List only if 
     * vertex distance + weight is less than existing 
     * new vertex min distance
     */
    if (Graph_Dj_set_min_distance(G, 
                        (vertex->min_distance+adjacency_list->weight),
                          adjacency_list->target)) {
      if (!Graph_node_in_priority_list(priority_list, adjacency_list->target)) { 
        temp  =  Graph_get_priority_list_template(); 
        temp->vertex = adjacency_list->target;
        if (priority_list == NULL || prio_runner == NULL) {
          priority_list = temp;
          prio_runner   = temp;
        } else {
          prio_runner->next = temp;
          prio_runner   = prio_runner->next;
        }
        temp = temp->next;
      } 
    }
    adjacency_list = adjacency_list->next;
  }

  return priority_list;
}

Graph_priority_t *
Graph_Dj_pop_priority_list(Graph_priority_t *priority_list) {

  Graph_priority_t      *runner;

  assert(priority_list);
  runner = priority_list;
  priority_list = priority_list->next;

  /* Destroy Unnecessary Node */
  free(runner);

  return priority_list;
}

/*
 * Function
 * Graph_get_dijkstra
 *
 * In this function we find shortest distance 
 * from Source (argument) to all the vertices
 * and distance
 *
 * Input:
 *       Graph_t * G (Graph)
 * Output:
 *       None 
 */
void
Graph_get_dijsktra(Graph_t  *G, vertex_number_t S) {
 
  Graph_vertices_t      *vertex;
  Graph_edges_t         *adjacency_list;
  Graph_priority_t      *priority_list;

  vertex = Graph_get_vertex(G,S);

  if (vertex == NULL) {
    LOG_ERR("Unable to find vertex %d",S);
    return;
  }
  
  vertex->min_distance = 0;
  adjacency_list = vertex->adjacency_list;
  priority_list = Graph_get_priority_list(G, priority_list, vertex);

#ifdef DEBUG
  Graph_dump_prio_list(priority_list);
#endif

  while(priority_list != NULL) {
    /* Return Last vertex from Priority List */
    vertex = Graph_Dj_get_next_vertex(G, priority_list);
    /* Pop PriorityList */
    priority_list = Graph_Dj_pop_priority_list(priority_list);
    /* Populate min distance for new vertices */
    priority_list = Graph_get_priority_list(G, priority_list,vertex); 
#ifdef DEBUG
    Graph_dump_prio_list(priority_list);
#endif
  }

  Graph_display_graph(G);

  return;
}
