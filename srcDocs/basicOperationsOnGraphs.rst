==========================
Basic Operations On Graphs
==========================

For a targeted application, characterization can be posed as a graph query
operation using three graph-based algorithms:

* finding connected components, and
* computing the shortest paths.
* the graph filtering operation which enables the query definitions that capture
  some aspects of underlying physics.

Identifying connected components of a graph
===========================================

We start by explaining the link between the question of quantifying the number
of individual domains and the graph queries. Here, we aim to identify the
sub-domains of the morphology, where the sub-domain is part of the morphology
that is surrounded by sub-domains of other color(s). We accomplish it by
assigning an index of their connected component (CC) to each vertex.
The process requires two steps. First, we define the filtered graph by
masking the edges connecting  vertices of different labels/colors. In other words,
we ensure that only the edges connecting vertices of the same label are considered.
In the second step, we invoke the the connected components algorithm on  the filtered graph.

Translating this process into the code requires only few lines of code (included below).
We use data structure and functions from the ``boost`` library.
First, the code defines the predicate to facilitate graph filtering via
class ``edge_same_color_predicate``. This class has ``operator()`` that checks
if a given edge satisfies the filtering condition (returns a ``true``
or a ``false`` value if the condition is satisfied or not). In this case, we
check the condition whether the colors of the two vertices that build the edge
``e`` (``source`` and ``target``) are the same. To look up the labels of vertices
constituting the edge, the class additionally stores pointers to the graph
``G_`` and the vector of vertices labels (``color_``).

.. code-block:: cpp
  :linenos:

  class edge_same_color_predicate {
  public:
      edge_same_color_predicate() : G_(0), color_(0) { }
      edge_same_color_predicate(const gt::graph_t& G, const std::vector<COLOR>& color)
	     : G_(&G), color_(&color) { }
       bool operator()(const gt::edge_t& e) const {
	      return ((*color_)[boost::source(e, *G_)] == (*color_)[boost::target(e, *G_)]);
        }
        private:
        const gt::graph_t* G_;
        const std::vector<COLOR>* color_;
        };


Once the graph filtering is defined, it is used to filter the original graph.
The function to determine the connected components in the graph is included below. It consists of three lines:

1. the declaration of the object ``p`` of type defined above,
2. the declaration of the filtered graph ``FG`` of type ``filtered_graph`` defined in ``boost::graph`` library and
3. the call of function ``connected_components`` from ``boost::graph`` library that determines connected components in the filtered graph.

The outcome from this procedure is stored in the vector ``components`` with integer values that corresponds to the index of the connected components.

.. code-block:: c++
  :linenos:

  void DetermineConnectedComponents(gt::graph_t* G, const std::vector<COLOR>& color,
	 std::vector<int>& components){
      edge_same_color_predicate p( *G, color);
      boost::filtered_graph<gt::graph_t, edge_same_color_predicate> FG(*G, p);
      boost::connected_components(FG, &components[0]);
      }
