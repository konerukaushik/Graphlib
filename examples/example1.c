/*
 * In this example we will
 * try to verify the API's
 *
 * Author: Kaushik, Koneru
 * Email:  konerukaushik@gmail.com
 */

#include <graph.h>


int main() {
  
  Graph_t     *G;

  G = Graph_init(10, FALSE);

  Graph_add_edge(G, 0, 1, 1, 0);

  Graph_display_graph(G);

  return 0;
}
