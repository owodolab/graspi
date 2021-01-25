==============================================
 Basic Definitions
==============================================


* An undirected graph :math:`G=(V,E)` is defined by a set of vertices, :math:`V`,
  and a set of edges, :math:`E`, where each  edge in :math:`E` is an unordered
  pair of vertices drawn from :math:`V`.

* A weighted undirected graph :math:`G=(V,E,W)`` is an undirected graph
  :math:`(V,E)` with an associated weight function,
  :math:`W: E \rightarrow {\mathbb R}_{+}``, that assigns a non-negative real
  weight to each edge in :math:`E`.

* A labeled weighted undirected graph :math:`G=(V,E,W, L)` is a weighted
  undirected graph :math:`(V,E,W)` with an associated labeling function, :math:`L`,
  that assigns a label to each vertex in :math:`V`.
  In GraSPI, we label each vertex by a color.

* A path between a source vertex, :math:`s \in V`, and a target vertex,
  :math:`t \in V` is a sequence :math:`p=[v_0, v_1, \dots v_i \dots v_k]` of
  vertices such that :math:`v_o=s`, :math:`v_k=t` and for each :math:`i` from
  :math:`0` to :math:`i-1`, vertices :math:`v_i` and :math:`v_{i+1}`` are
  adjacent in :math:`G`. The length of path :math:`p` is
  :math:`\sum_{i=0}^{k-1}w(e(v_i,v_{i+1}))``.

* A shortest path between a source vertex :math:`s \in V` and a target vertex
  :math:`t \in V` is a path between :math:`s` and :math:`t` that is of the
  shortest length among all paths between :math:`s` and :math:`t` in :math:`G`.
  The distance between vertices :math:`s` and :math:`t` in :math:`G` is the
  length of a shortest path between :math:`s` and :math:`t` in :math:`G`.
  If no such path exists, the distance is defined as infinity.
  Note that the shortest path between a pair of vertices need not be unique,
  but the distance between them is unique.

* A subgraph of :math:`G` is a graph :math:`G' = (V', E')` such that
  :math:`V' \subseteq V` and :math:`E' \subseteq E`. A vertex-induced subgraph
  on vertex set :math:`V' \subseteq V` is the maximal subgraph with the vertex
  set :math:`V'`.

* A graph :math:`G` is connected if there is a path between any pair of vertices
  in :math:`G`. A connected component :math:`C` in :math:`G` is a maximal connected subgraph of :math:`G`.
