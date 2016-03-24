# Graphlib
Graphlib is C Library for Graph. Importing this to application provides various API's of Graph.

In this Graph Model is maintaining Adjacency List for every vertices. 
If its a Directed Graph we append to only single vertex else for both vertices


Following are the API's

Graph_init

  - This API is used to Initiate Graph Object
      - This takes 2 parameters (No Of Vertices, is_Directed)
      - If Graph is semi directed & non-directed then there is flexibility of mentioning while adding edges

Graph_add_vertices

  - This API will provide an interface if we want to append more vertices to an existing Graph
      - This API takes 2 Parameters (Graph, No of New vertices to append)

Graph_add_edge
  
  - This API provides interface to add edges between two vertices along with weight and 
    whether the edge is directed or not
      - This API takes 5 Parameters (Graph, Source Vertex, Destination Vertex, Weight, Directed/or Not)

Graph_display_graph

  - This API provides interface to display graph along with adjacency List

Graph_has_edge

  - This API provides interace to verify whether the there is a edge 
    between 2 vertices in a Graph
      
Graph_get_dijkstra

  - This API display's minimum distance between Vertices using Dijkstras

#Compilation


##Present Working Items

  Display Pattern (As of Now presenting in raw format)

  Following API's to come soon...
ToDo: <br/>
  Graph_Prims <br />
  Graph_init_from_xml <br />
