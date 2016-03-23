/*
 * In this example we will
 * try to verify the API's
 *
 * Author: Kaushik, Koneru
 * Email:  konerukaushik@gmail.com
 */

#include <graph.h>


int main() {
  
  Graph_t              *G;
  unsigned int          destination;
  unsigned int          source;
  unsigned int          weight = 10;
  bool                  is_directed = FALSE;

  G = Graph_init(10, FALSE);

  source = 0;
  destination = 1;
  Graph_add_edge(G, source, destination, weight, is_directed);

  source = 0;
  destination = 3;
  weight = 20;
  Graph_add_edge(G, source, destination, weight, is_directed);

  source = 0;
  destination = 2;
  weight = 20;
  Graph_add_edge(G, source, destination, weight, is_directed);


  source = 1;
  destination = 2;
  weight = 5;
  Graph_add_edge(G, source, destination, weight, is_directed);


  source = 1;
  destination = 3;
  weight = 7;
  Graph_add_edge(G, source, destination, weight, is_directed);

  printf("----- Dijkstra ----\n");

  Graph_get_dijsktra(G,0);

  return 0;
}
