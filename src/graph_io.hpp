/***
 *  $Id$
 **
 *  File: graph_io.hpp
 *  Created: May 9, 2012
 *
 *  Author: Olga Wodo, Baskar Ganapathysubramanian
 *  Copyright (c) 2012 Olga Wodo, Baskar Ganapathysubramanian
 *  Distributed under the [LICENSE].
 *  See accompanying LICENSE.
 *
 *  This file is part of GraSPI.
 */

#ifndef GRAPH_IO_HPP
#define GRAPH_IO_HPP

#include <fstream>
#include <string>

#include "graspi_types.hpp"


namespace graspi {

    /// @cond TEST
    /// This function outputs the structure of the graph to the stream os.
    ///
    /// @fn bool output_graph(std::ostream&, graph_t*, dim_g_t&, vertex_colors_t&, edge_weights_t&, edge_colors_t&)
    /// This function outputs the structure of the to the stream os
    /// @param os is the output stream the structure is sent to
    /// @param G is the input graph
    /// @param d_g is the struct storing the dimension of graph vertices
    /// @param C is the vector storing the labels/colors of vertices in the graph G
    /// @param W is the map storing the weights of the edges
    /// @param L is the map storing the labels/colors of the edges in graph G
    bool output_graph(std::ostream& os,
                      graph_t* G,
                      dim_g_t& d_g,
                      vertex_colors_t& C,
                      edge_weights_t& W,
                      edge_colors_t& L){
        /*
         os << d_g.n_bulk << std::endl;
         for(int i = 0; i < (d_g.n_bulk+2); i++){
         os << i << " " << C[i] << "\t";
         int s = i;
         graspi::graph_t::adjacency_iterator u, u_end;
         graspi::edge_descriptor_t e;
         bool e_res = false;
         boost::tie(u, u_end) = boost::adjacent_vertices(s, *G);
         for (; u != u_end; ++u) {
         if ( (*u) < (d_g.n_bulk + 2) ){
         boost::tie(e, e_res) = boost::edge(s, *u, *G);
         int t = *u;
         std::pair<int,int> p
         = std::pair<int,int>(std::min(s,t),std::max(s,t) );
         os << t << " "

         << W[e] << " "

         << L[p] << "\t";
         }
         }
         os << std::endl;
         }*/
        return true;
    }
    /// @endcond


    /// This function outputs the structure of the graph to the file with the given name.
    ///
    /// @fn bool output_graph(const std::string&, graph_t*, dim_g_t&, vertex_colors_t&, edge_weights_t&, edge_colors_t& )
    /// This function outputs the structure of the to the file with the given name
    /// @param name is the filename the structure is sent to
    /// @param G is the input graph
    /// @param d_g is the struct storing the dimension of graph vertices
    /// @param C is the vector storing the labels/colors of vertices in the graph G
    /// @param W is the map storing the weights of the edges
    /// @param L is the map storing the labels/colors of the edges in graph G
    inline bool output_graph(const std::string& name,
                             graph_t* G,
                             dim_g_t& d_g,
                             vertex_colors_t& C,
                             edge_weights_t& W,
                             edge_colors_t& L){
        std::ofstream f(name.c_str());
        if (!f) return false;
        return output_graph(f, G, d_g, C, W, L);
    }

    /// @cond TEST
    /// This function prints the indices of connected components
    ///
    /// @fn bool print_id_ccs(std::ofstream&, const vertex_colors_t&, const vertex_ccs_t&)
    /// @param os is the stream the formated output will be send to
    /// @param C is the vector storing the labels/colors of vertices in the graph G
    /// @param vCC is the vector storing indices of the connected components (CC) of each vector in the graph
    /// @return the status of the printing process.
    inline bool print_id_ccs(std::ofstream& os,
                             const vertex_colors_t& C,
                             const vertex_ccs_t& vCC ){
        if(!os) {
            std::cerr << "Problem with stream - ids of ccs " << std::endl;
            return false;
        }

        for(int i = 0; i < vCC.size(); i++){
            os << vCC[i] << " " << C[i] << std::endl;
        }

        return true;
    }
    /// @endcond


    /// This function prints the indices of connected components
    ///
    /// @fn bool print_id_ccs(std::ofstream&, const vertex_colors_t&, const vertex_ccs_t&)
    /// @param os is the stream the formated output will be send to
    /// @param C is the vector storing the labels/colors of vertices in the graph G
    /// @param vCC is the vector storing indices of the connected components (CC) of each vector in the graph
    /// @return the status of the printing process.
    inline bool print_id_ccs(const std::string& filename,
                             const vertex_colors_t& C,
                             const vertex_ccs_t& vCC ){
        std::ofstream f(filename.c_str());
        if (!f) return false;
        return print_id_ccs(f, C, vCC);
    }
}

#endif
