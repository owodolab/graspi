/***
 *  $Id$
 **
 *  File: graph_dijkstra.hpp
 *  Created: May 9, 2012
 *
 *  Author: Olga Wodo, Baskar Ganapathysubramanian
 *  Copyright (c) 2012 Olga Wodo, Baskar Ganapathysubramanian
 *  See accompanying LICENSE.
 *
 *  This file is part of GraSPI.
 */

#ifndef GRAPH_DIJKSTRA_HPP
#define GRAPH_DIJKSTRA_HPP

#include "graspi_types.hpp"
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/filtered_graph.hpp>


namespace graspi {
    /// This function determines the shortest paths in the fitered graph.
    ///
    /// This function determines the shortest paths in the filtered graph.
    /// The shortest paths and the lengths (distances) are computed from the source vertex to all vertices in the filtered graph.
    /// The filtered graph is determined using predicate Pred.
    /// @tparam Pred is the predicate used to filter the graph
    /// @param G is the input graph
    /// @param W is the map storing the weights of the edges
    /// @param source is the source vertex with respect to which distances are to be determine_shortest_distanced
    /// @param pred is the predicate used to filter the graph
    /// @param d is the vector of distance to be determined as a result of this function
    template<typename Pred>
    inline void determine_shortest_distances(graph_t*G,
                                             const edge_weights_t& W,
                                             vertex_t source,
                                             const Pred& pred,
                                             std::vector<float>& d){
        boost::filtered_graph<graph_t, Pred> FG(*G,pred);
        unsigned int n = boost::num_vertices(*G);
        std::vector<vertex_t> p(n);
        std::fill(d.begin(), d.end(), 0.0);
        for (unsigned int i = 0; i < n; ++i) p[i] = i;

        boost::dijkstra_shortest_paths(FG, source,
                                       boost::predecessor_map(&p[0])
                                       .
                                       distance_map(&d[0]).weight_map(W));
    }
}//graspi-namespace

#endif
