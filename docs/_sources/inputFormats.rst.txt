=================
Input Formats
=================

|graspi| accepts two input formats for structured and unstructured data.
The structured data assumes that size of discrete points in each dimension is known.
The dimensionality is provided in the first line of the input file: :math:`n_x, n_y, n_z`.
The reminder of the input file contains the array (row-wise representation of the corresponding matrix) with the corresponding phases from the set of available labels. Since the data is structured, the local neighborhood can be constructed as the data is read by |graspi|.

.. image:: figs/simpleMorphExample.png
  :width: 400


The input file for the above figure

.. literalinclude:: figs/simpleMorphExample.txt
    :linenos:
    :language: none
    :lines: 1, 3-5

The second format corresponds to unstructured data, where information about
phases needs to provided along with the neighborhood.
Here, we use the adjacency matrix to inform |graspi| on the neigborhood.
The input file start with the total number of vertices in the data set.
Next each line provides the information about each vortex.
First the index of the vertex is provided followed by the color of the vertex.
The reminder of the line consist of triplets with information about the neighbors.
The triplet consists of the index of the neighbor, the distance from to the neighbor and type of the neighbor.
In this example, two types of neighbors are considered: ``f``, ``s`` and ``t`` that
corresponds to first-, second- and third-order neighbors, respectively.
The set of types may be redefined to encode additional information.

.. literalinclude:: figs/simpleMorphExample.graphe
    :linenos:
    :language: none
