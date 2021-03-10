/***
 *  $Id$
 **
 *  File: graspi_predicates.hpp
 *  Created: May 9, 2012
 *
 *  Author: Olga Wodo, Baskar Ganapathysubramanian
 *  Copyright (c) 2012 Olga Wodo, Baskar Ganapthysubramanian
 *  See accompanying LICENSE.
 *
 *  This file is part of GraSPI.
 */

#ifndef GRASPI_PREDICATES_HPP
#define GRASPI_PREDICATES_HPP

#include "graspi_types.hpp"
#include "graspi_cc.hpp"

namespace graspi{

    /// This is predicate to filter edges of the same color (color/label of vertices)
    ///
    /// This predicate identifies edges connecting vertices of the same color
    /// and it is used to identify connected components
    class connect_same_color {
    public:
        /// The constructor to initiate the fields
        connect_same_color() : G_(0), vertex_colors_(0) { }

        /// The constructor to initiate the fields
        ///
        /// @param G is the graph to be filtered and analyzed
        /// @param vertex_colors is the vector storing the labels/colors of vertices in the graph G
        connect_same_color(const graspi::graph_t& G,
                           const graspi::vertex_colors_t& vertex_colors)
        : G_(&G), vertex_colors_(&vertex_colors){ }

        /// This is operator () that checked is edge connects vertices of the same color
        bool operator()(const graspi::edge_descriptor_t& e) const {

            return
            ( (*vertex_colors_)[boost::source(e, *G_)]
             ==
             (*vertex_colors_)[boost::target(e, *G_)]
             );
        }

    private:
        const graspi::graph_t* G_;  ///< Pointer to the graph to be filtered
        const graspi::vertex_colors_t* vertex_colors_; ///< The pointer to the vector of vertex lables/colors
    }; // class connect_same_color

    /// This is predicate to filter the graph that connects vertices to GREEN meta-vertex
    ///
    /// Predicate used to filter original graph to find the shortest distances
    /// from source vertex - GREEN to all BLACK/GREY (color_).
    /// Predicate is used to mask edges in G other than
    /// (BLACK,BLACK) and (BLACK,GREEN) and (color,color).
    /// Since source vertex is GREEN we allow edges to exists between
    /// GREEN and BLACK.
    class connect_color_green {
    public:
        /// The default constructor
        connect_color_green() : G_(0), vertex_colors_(0) { }

        /// The constructor
        ///
        /// @param G is the graph to be filtered
        /// @param C is the reference to the vector storing the labels/colors of vertices in the graph G
        /// @param color is the color of vertices to be filtered as connected to interface/green meta-vertex
        /// @param green is the targeted interface color to be used for filtering
        connect_color_green(const graph_t& G,
                            const vertex_colors_t& C,
                            COLOR color, COLOR green = GREEN)
        : green_(green), color_(color), G_(&G), vertex_colors_(&C)  { }

        /// the operator used to filter the edges satisfying the condition specified in this operator
        bool operator()(const edge_descriptor_t& e) const {
            if ( ( ( (*vertex_colors_)[boost::source(e, *G_)] == green_ )
                  && ( (*vertex_colors_)[boost::target(e, *G_)] == color_ ) )
                ||
                ( ( (*vertex_colors_)[boost::target(e, *G_)] == green_ )
                 && ( (*vertex_colors_)[boost::source(e, *G_)] == color_ ) )
                )
                return true;
            return (
                    (*vertex_colors_)[boost::source(e, *G_)]
                    ==
                    (*vertex_colors_)[boost::target(e, *G_)]
                    );
        }

    private:
        COLOR green_;  ///< the color of the interface to be filtered in the graph
        COLOR color_; ///< the color of the vertices to be filtered in the graph as connected to the interface
        const graph_t* G_; ///< The pointer to the graph to be filtered
        const vertex_colors_t* vertex_colors_; ///< The pointer to the vector of the with the vertex labels
    }; // class connect_black_green


    /// This is predicate to filter the graph that connects vertices to the relevant meta-vertex
    ///
    /// Predicate used to filter original graph to find the shortest distances
    /// from source vertex - the meta-vertex of relevance and any other vertices
    /// where edges between vertices exist only if they connect vertices of the same color
    /// or are connected to top or bottom meta-vertices.

    class connect_same_color_and_relevant_meta_vertex {
    public:
        /// The constructor
        connect_same_color_and_relevant_meta_vertex ()
        : G_(0), vertex_colors_(0) { }

        /// The constructor
        ///
        /// @param G is the reference to the graph to be filtered
        /// @param C is the reference to the vector storing the labels/colors of vertices in the graph G
        connect_same_color_and_relevant_meta_vertex (const graph_t& G,
                                                     const vertex_colors_t& C)
        : G_(&G), vertex_colors_(&C) { }

        /// The operator to filter the graph, this is where the condition
        /// of edge filtering is defined
        /// @param e is the edge to be checked
        bool operator()(const edge_descriptor_t& e) const {
            if ( ((*vertex_colors_)[boost::source(e, *G_)]
                  +
                  (*vertex_colors_)[boost::target(e, *G_)]  )
                == 20) return true; //black+red
            if ( ((*vertex_colors_)[boost::source(e, *G_)]
                  +
                  (*vertex_colors_)[boost::target(e, *G_)]  )
                == 11) return true; //white+blue
            if ( ((*vertex_colors_)[boost::source(e, *G_)]
                  +
                  (*vertex_colors_)[boost::target(e, *G_)]  )
                == 23) return true; //grey+red
            if ( ((*vertex_colors_)[boost::source(e, *G_)]
                  +
                  (*vertex_colors_)[boost::target(e, *G_)]  )
                == 13) return true; //grey+blue

            return ((*vertex_colors_)[boost::source(e, *G_)]
                    ==
                    (*vertex_colors_)[boost::target(e, *G_)]);
        }

    private:
        const graph_t* G_;  ///< The pointer to the graph to be filtered
        const vertex_colors_t* vertex_colors_; ///< The pointer to the vector of vertex label
    }; // class connect_same_color_and_relevant_meta_vertex

    /// The predicate to filter the graph where vertices are screened if the path towards relevant meta-vertex exists
    class connect_relevant_meta_vertex {
    public:
        /// The default constructor
        connect_relevant_meta_vertex()
        : G_(0), vertex_colors_(0), vertex_ccs_(0), ccs_(0), c_(0) { }
        void change_color(COLOR c){ c_ = c; }

        /// The default constructor
        ///
        /// @param G is the reference to the graph to be filtered
        /// @param C is the reference to the vector storing the labels/colors of vertices in the graph G
        /// @param vCC is the vector storing indices of the connected components (CC) of each vector in the graph
        /// @param CC is the vector of CC,
        /// @param color is the vertices og this color to be checked
        connect_relevant_meta_vertex(const graph_t& G,
                                     const vertex_colors_t& C,
                                     const vertex_ccs_t& vCC,
                                     const ccs_t& CC,
                                     COLOR color)
        : G_(&G), vertex_colors_(&C), vertex_ccs_(&vCC),
        ccs_(&CC), c_(color) { }

        /// The operator used to filter the graph
        bool operator()(const vertex_t& vertex_id) const {
            if( (*vertex_colors_)[vertex_id] != c_) return false;

            if (
                ( c_ == BLACK ) &&
                ( (*ccs_)[(*vertex_ccs_)[vertex_id]].if_connected_to_top() )
                ) return true;
            if (
                ( c_ == WHITE ) &&
                ( (*ccs_)[(*vertex_ccs_)[vertex_id]].if_connected_to_bottom() )
                ) return true;
            return false;
        }
    private:
        const graph_t* G_;  ///< The pointer to the graph to be filtered
        const vertex_colors_t* vertex_colors_; ///< The pointer to the vector of vertex labels
        const vertex_ccs_t* vertex_ccs_; ///< The pointer to the vector storing vertex connected component index
        const ccs_t* ccs_; ///< The pointer to the vector storing the connected components
        COLOR c_; ///< The color to be checked against
    }; // connect_relevant_meta_vertex


    // Predicate used to identify descriptor of a given name
    class find_desc_of_name {
    public:
        /// The default constructor
        find_desc_of_name():desc_(" "){}

        /// The constructor
        ///
        /// @param desc_name is the name of the descriptor to be found
        find_desc_of_name(const std::string desc_name)
        : desc_(desc_name){ }

        /// The member to set the the descriptor to be found
        ///
        /// @param desc is the name of the descriptor
        void set_desc(const std::string& desc){desc_=desc;}

        /// The operator
        bool operator()(const std::pair<float,std::string>& p_desc) const {
            return p_desc.second == desc_;
        }

    private:
        std::string desc_;
    }; // class find_desc_of_name

}//graspi-namespace

#endif
