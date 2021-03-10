/***
 *  $Id$
 **
 *  File: graspi_types.hpp
 *  Created: May 8, 2012
 *  Last modified: March 2021
 *
 *  Author: Olga Wodo, Baskar Ganapathysubramanian
 *  Copyright (c) 2012 Olga Wodo, Baskar Ganapthysubramanian
 *  See accompanying LICENSE.
 *
 *  This file is part of GraSPI.
 */

#ifndef GRASPI_TYPES_HPP
#define GRASPI_TYPES_HPP

#include <map>
#include <vector>
#include <boost/graph/adjacency_list.hpp>

/// this macro defines the type of vertex labels to be unsigned int
#define COLOR unsigned int

/// this macro defines the color of donor label (D) as BLACK and assigns the value of 0
#define BLACK   0

/// this macro defines the color of acceptor label (A) as WHITE and assigns the value of 1
#define WHITE   1

/// this macro defines the color of mixed-phase label (D+A) as GREY and assigns the value of 3
#define GREY    3

/// this macro defines the color of cathode/bottom/negative-electrode label as BLUE and assigns the value of 10
#define BLUE   10

/// this macro defines the color of anode/top/positive-electrode label as RED and assigns the value of 20
#define RED    20

/// this macro defines the color of interface (between D/A) label as GREEN and assigns the value of 30
#define GREEN  30

/// this macro defines the color of interface (between D/D+A) label as DGREEN and assigns the value of 31
#define DGREEN 31

/// this macro defines the color of interface (between A/D+A) label as DGREEN and assigns the value of 32
#define LGREEN 32

namespace graspi {

    /// graph_t is the alias of the graph type from boost library
    ///
    /// where graph_t is stored as adjacency list with two containers:
    /// boost::setS - is the set of edges
    /// boost::vecS - is the vector of vertices
    /// the graph is undirected
    /// all remaining parameters are unset
    typedef boost::adjacency_list<boost::setS, boost::vecS, boost::undirectedS,
				boost::no_property, boost::no_property> graph_t;

    /// the type used to identity vertices in the graph.
    typedef boost::graph_traits<graph_t>::vertex_descriptor vertex_t;

    /// the type used to identify edges in the graph
    typedef boost::graph_traits<graph_t>::edge_descriptor   edge_descriptor_t;

    /// the property of vertices characterizing the label/color of the vertex
    typedef std::vector<COLOR> vertex_colors_t;

    /// the property of vertices characterizing the index of CC for a given vertex
    typedef std::vector<int>   vertex_ccs_t;

    /// the property of edges stored in the dictionary (map), types include: f,s,r (first-, second-, third- order edges)
    typedef std::map<std::pair<int,int> ,char >         edge_colors_t;

    /// the property of edges  to store edge weight (e.g., distances between vertices)
    /// it is linked with associative map (see next type)
    typedef std::map<edge_descriptor_t, float>          edge_map_t;

    /// the adaptor that converts into into a mutable map, retains a reference to the container (edge_map_t)
    typedef boost::associative_property_map<edge_map_t> edge_weights_t;

    /// Connected Components (CC) type
    struct CC;

    /// vector storing CCs
    typedef std::vector<CC> ccs_t;

    /// descriptor type defined as a pair of value and descriptive string;
    typedef std::pair<float,std::string> desc_t;

    /// structure storing dimensions of graph vertices
    struct dim_g_t {
        unsigned int n_phases;           ///< number of phases (currently 2 or 3)
        unsigned int n_bulk;             ///< all BLACK,WHITE and GREY vertices
        unsigned int n_meta_basic;       ///< basic meta vertices (anode, cathode)
        unsigned int n_meta_interfacial; ///< interfacial meta vertices between (BLACK/WHITE), (BLACK/GREY), (WHITE/GREY)

        /// constructor
        ///
        /// @param n_phases is the number of phases considered
        /// @param bulk is the number of bulk vertieces
        /// @param meta is the number of meta vertices associated with the {2,3}-phase morphology
        explicit dim_g_t(unsigned int n_phases = 2,
                         unsigned int bulk = 0,
                         unsigned int meta = 2)
        : n_phases(n_phases), n_bulk(bulk), n_meta_basic(2), n_meta_interfacial(1) {
            if(n_phases == 3) n_meta_interfacial = 3;
        }

        /// returns the total number of vertices in the graph (bulk and meta vertices)
        int n_total()     const{ return n_bulk+n_meta_basic+n_meta_interfacial; }

        /// returns the number of basic meta vertices (e.g., top and bottom electrode)
        int n_meta()      const{ return n_meta_basic; }

        /// returns the number of interfacial meta vertices
        int n_meta_int()  const{ return n_meta_interfacial; }

        /// returns the number of all meta vertices (basic and interfacial)
        int n_meta_total()const{ return n_meta_basic+n_meta_interfacial; }

        /// returns the index of meta vertex of color c
        int id(COLOR c)const{
            if(c == BLUE)   return id_blue();
            if(c == RED)    return id_red();
            if(c == GREEN)  return id_green();
            if(c == DGREEN)  return id_dgreen();
            if(c == LGREEN)  return id_lgreen();
            return -1;
        }

        /// returns the index of blue meta-vertex
        int id_blue() const{ return n_bulk;   }
        /// returns the index of red meta-vertex
        int id_red()  const{ return n_bulk+1; }
        /// returns the index of green meta-vertex
        int id_green()const{ return n_bulk+2; }
        /// returns the index of dark green  meta-vertex
        int id_dgreen()const{ return n_bulk+3; }
        /// returns the index of light green meta-vertex
        int id_lgreen()const{ return n_bulk+4; }
    }; // struct dim_g_t

    /// dimension descriptor
    ///
    /// structure to store the dimensions of the graph when morphology
    /// is passed as array (structured data)
    struct dim_a_t {
        /// constructor
        ///
        /// @param x is the number of voxels in x direction
        /// @param y is the number of voxels in y direction
        /// @param z is the number of voxels in z direction

        explicit dim_a_t(unsigned int x = 1, unsigned int y = 1,
                         unsigned int z = 1)
        : nx(x), ny(y), nz(z) { }

        unsigned int nx; ///< nx is the total number of voxels in x direction
        unsigned int ny; ///< ny is the total number of voxels in y direction
        unsigned int nz; ///< nz is the total number of voxels in z direction

    }; // struct dim_t

} // namespace graspi

#endif // GRASPI_TYPES_HPP
