/***
 *  $Id$
 **
 *  File: graph_constructors.hpp
 *  Created: May 8, 2012
 *
 *  Author: Olga Wodo, Baskar Ganapathysubramanian
 *  Copyright (c) 2012 Olga Wodo, Baskar Ganapathysubramanian
 *  See accompanying LICENSE.
 *
 *  This file is part of GraSPI.
 */

#ifndef GRAPH_CONSTRUCTORS_HPP
#define GRAPH_CONSTRUCTORS_HPP

#include <cmath>
#include <fstream>
#include <sstream>
#include <string>

#include "graspi_types.hpp"


namespace graspi {

    /// This function build the graph from the input stream
    ///
    /// @param is is the input stream
    /// @param G is the reference to the pointer of the graph to be constructed
    /// @param d_g is the reference to the struct storing the dimension of graph vertices
    /// @param C is the reference to the vector storing the labels/colors of vertices in the graph G
    /// @param W is the reference to the map storing the weights of the edges
    /// @param L is the reference to the map storing the labels/colors of the edges in graph G
    /// @return the status of the graph construction
    bool build_graph(std::istream& is,
                     graph_t*& G,
                     dim_g_t& d_g,
                     vertex_colors_t& C,
                     edge_weights_t& W,
                     edge_colors_t& L);

    /// This function build the graph from the file
    ///
    /// @param name is the name of the input file
    /// @param G is the reference to the pointer of the graph to be constructed
    /// @param d_g is the reference to the struct storing the dimension of graph vertices
    /// @param C is the reference to the vector storing the labels/colors of vertices in the graph G
    /// @param W is the reference to the map storing the weights of the edges
    /// @param L is the reference to the map storing the labels/colors of the edges in graph G
    /// @return the status of the graph construction

    bool build_graph(const std::string& name,
                     graph_t*& G,
                     dim_g_t& d_g,
                     vertex_colors_t& C,
                     edge_weights_t& W,
                     edge_colors_t& L) ;
    // {
    //       std::ifstream f(name.c_str());
    //       if (!f) return false;
    //       return build_graph(f, G, d_g, C, W, L);
    //   } // build_graph


    /// This is function to read the colors of vertex - when morphology is stored in the array
    ///
    /// @tparam Container is the container to read the data from
    /// @param name is the filename to read the data from
    /// @param M is the container to store the read data
    /// @param d_a is the reference to the struct storing dimensions of the morphology represented as a array
    /// @param d_g is the reference to the struct storing the dimension of graph vertices
    /// @return the status of the reading data from file
    template <typename Container>
    bool read_array(const std::string& name,
                    Container& M, dim_a_t& d_a, dim_g_t& d_g){
        std::ifstream f(name.c_str());
        if (!f) return false;
        std::string str;
        getline(f,str);
        std::istringstream iss(str);
        iss >> d_a.nx >> d_a.ny >> d_a.nz;
        if(d_a.nz == 0) d_a.nz = 1;
        d_g.n_bulk = d_a.nx * d_a.ny * d_a.nz;
        unsigned int n_total =  d_g.n_total();
        M.resize(n_total);
        for(unsigned int i=0; i< d_g.n_bulk; i++){
            if (!f) return false;
            f >> M[i];
        }
        f.close();
        return true;
    }

    /// This function build the graph of the structured morphologies for whiche labels are available (e.g., read from the file)
    ///
    /// @param G is the reference to the pointer of the graph to be constructed
    /// @param d_g is the reference to the struct storing the dimension of graph vertices
    /// @param C is the reference to the vector storing the labels/colors of vertices in the graph G
    /// @param d_a is the reference to the struct storing dimensions of the morphology represented as a array
    /// @param W is the reference to the map storing the weights of the edges
    /// @param L is the reference to the map storing the labels/colors of the edges in graph G
    /// @return the status of the graph construction

    bool build_graph(graph_t*& G, const dim_g_t& d_g,
                     vertex_colors_t& C, dim_a_t& d_a,
                     edge_weights_t& W,
                     edge_colors_t& L,
                     double pixelsize = 1.0, bool if_per_on_size = false);

    /// This function initialized the meta vertices
    ///
    /// @param C is the reference to the vector storing the labels/colors of vertices in the graph G
    /// @param d_g is the reference to the struct storing the dimension of graph vertices
    void initlize_colors_meta_vertices( vertex_colors_t& C, const dim_g_t& d_g );

    /// This is function to update the graph
    ///
    /// @tparam Container is the container to read the data from
    /// @param M is the container to store the read data
    /// @param d is the reference to the struct storing dimensions of the morphology represented as a array
    /// @param G is the reference to the input graph
    /// @param d_g is the reference to the struct storing the dimension of graph vertices
    /// @param C is the reference to the vector storing the labels/colors of vertices in the graph G
    /// @param W is the reference to the map storing the weights of the edges
    /// @param L is the reference to the map storing the labels/colors of the edges in graph G
    /// @return the status of the update process

    template <typename Container>
    bool update_graph(const Container& M, const dim_a_t& d,
                      graph_t& G, dim_g_t& d_g,
                      vertex_colors_t& C,
                      edge_weights_t& W,
                      edge_colors_t& L);

    /// This is function to add the edge between source and target vertex
    ///
    /// @param s is the source vertex
    /// @param t is the target vertex
    /// @param o is the order of the edges to be added
    /// @param w is the weight of the edge to be added
    /// @param green_vertex is the index of the green vertex
    /// @param dgreen_vertex is the index of the dark green vertex
    /// @param lgreen_vertex is the index of the light green vertex
    /// @param G is the reference to the input graph
    /// @param C is the reference to the vector storing the labels/colors of vertices in the graph G
    /// @param W is the reference to the map storing the weights of the edges
    /// @param L is the reference to the map storing the labels/colors of the edges in graph G
    void add_edge_to_graph(int s, int t, char o, double w,
                           int green_vertex, int dgreen_vertex, int lgreen_vertex,
                           graph_t* G,
                           vertex_colors_t& C,
                           edge_weights_t& W,
                           edge_colors_t& L);

    /// This is function to update edge between source and target vertex
    ///
    /// @param s is the source vertex
    /// @param t is the target vertex
    /// @param o is the order of the edges to be added
    /// @param w is the weight of the edge to be added
    /// @param G is the reference to the input graph
    /// @param C is the reference to the vector storing the labels/colors of vertices in the graph G
    /// @param W is the reference to the map storing the weights of the edges
    /// @param L is the reference to the map storing the labels/colors of the edges in graph G
    void make_update_edge_with_meta_vertex( int s, int meta_t,
                                           double w, char o,
                                           graph_t* G,
                                           edge_weights_t& W,
                                           edge_colors_t& L);

    /// This function computes the index in the array/vector storing the color/labels of vertices
    ///
    /// @param i_x is the index in x-direction of the vertex under consideration
    /// @param i_y is the index in y-direction of the vertex under consideration
    /// @param d_a is the reference to the struct storing dimensions of the morphology represented as a array
    /// @param if_per_on_size is the flag on periodicity, if it is on, then periodicity is reinforcef when generating neigbors
    /// @return the index in the array/vector of colors
    int compute_pos_2D(int i_x, int i_y,
                       const dim_a_t& d_a,
                       bool if_per_on_sides = false );

    /// This function computes the index in the array/vector storing the color/labels of vertices
    ///
    /// @param i_x is the index in x-direction of the vertex under consideration
    /// @param i_y is the index in y-direction of the vertex under consideration
    /// @param i_z is the index in z-direction of the vertex under consideration
    /// @param d_a is the reference to the struct storing dimensions of the morphology represented as a array
    /// @param if_per_on_size is the flag on periodicity, if it is on, then periodicity is reinforcef when generating neigbors
    /// @return the index in the array/vector of colors
    int compute_pos_3D(int i_x, int i_y, int i_z,
                       const dim_a_t& d_a,
                       bool if_per_on_sides = false );

    /// This function generates the neigborhood for a vertex in the array (indices of neighbors are generated)
    ///
    /// @param i is the index in x-direction of the vertex under consideration
    /// @param j is the index in y-direction of the vertex under consideration
    /// @param k is the index in z-direction of the vertex under consideration
    /// @param d_a is the reference to the struct storing dimensions of the morphology represented as a array
    /// @param ngbr is the pointer to pairs of neighbors (this is the pointer that points to the beginning of vector of neigbors that will be created as an output from this function)
    /// @param if_per_on_size is the flag on periodicity, if it is on, then periodicity is reinforcef when generating neigbors
    void generate_ngbr(int i, int j, int k,
                       const dim_a_t& d_a,
                       std::pair<int,char>* ngbr,
                       bool if_per_on_sides = false );

} // graspi


#endif // GRAPH_CONSTRUCTORS_HPP
