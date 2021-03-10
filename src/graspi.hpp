/***
 *  $Id$
 **
 *  File: graspi.hpp
 *  Created: May 8, 2012
 *
 *  Author: Olga Wodo, Baskar Ganapathysubramanian
 *  Copyright (c) 2012 Olga Wodo, Baskar Ganapathysubramanian
 *  See accompanying LICENSE.
 *
 *  This file is part of GraSPI.
 */

#ifndef GRASPI_HPP
#define GRASPI_HPP

#include "graspi_types.hpp"
#include "graph_constructors.hpp"
#include "performance_indicators.hpp"


namespace graspi {

  /// This function computes descriptors of morphology defined on structured matrix
  ///
  /// This function computes a set of descriptors of morphology
  /// And it is cythonized to be used in python
  /// @param vertex_colors is the morphology stored as an array of colors (row-wise order of matrix)
  /// @param nx is the number of voxels in x-direction
  /// @param ny is the number of voxels in y-direction
  /// @param nz is the number of voxels in z-direction (default value is 1)
  /// @param pixelsize is the physical unit of the voxel (distances will be rescaled according to this value)
  /// @param if_per is the flag setting the periodicity on sides (true value means periodicity on sides, for 2D - in x-dir, for 3D - in x and y-diretion)
  /// @return     the vector of descriptors, where each descriptor is a pair (std::pair<float,std::string>) consisting of descriptor's value (float) and name (string)


    std::vector<desc_t> compute_descriptors(graspi::vertex_colors_t& vertex_colors,
                                            const unsigned int& nx,
                                            const unsigned int& ny,
                                            const unsigned int& nz = 1,
                                            const float& pixelsize = 1.0,
                                            const bool& if_per = true,
                                            const std::string & res_path = "./"){

        // these are settings for two phase morphology
        int n_of_phases=1;
        unsigned int n_bulk = nx*ny*nz;
        unsigned int n_meta = 2;

        graspi::graph_t*        G;
        graspi::dim_g_t         d_g(n_of_phases,n_bulk,n_meta); //structure storing basic dimensions of G
        graspi::dim_a_t         d_a(nx,ny,nz);            //structure storing color array dimensions
        //    graspi::vertex_colors_t vertex_colors;   //container storing colors of vertices
        graspi::vertex_ccs_t    vertex_ccs;      //container storing CC-indices of vertices
        graspi::edge_colors_t   edge_colors;     //container storing colors of edges(f,s,t)
        graspi::edge_map_t      m;
        graspi::edge_weights_t  edge_weights(m); //container storing edge weights
        graspi::ccs_t           ccs;            //container storing basic info of CCs
        graspi::DESC          descriptors;    //container (vector) storing all descriptors


        /***********************************************************************
         * Graph construction                                                  *
         *                                                                     *
         **********************************************************************/

        if( ! graspi::build_graph(G, d_g,
                                  vertex_colors, d_a,
                                  edge_weights, edge_colors,
                                  pixelsize, if_per) ){
            std::cout << "Problem with building graph! " << std::endl;
            //        break;
        }

        descriptors.initiate_descriptors_2_phase();

        /***********************************************************************
         * Connected Components Identification                                 *
         *                                                                     *
         **********************************************************************/
        graspi::identify_connected_components( G, vertex_colors, vertex_ccs );
        graspi::determine_basic_stats_of_ccs( G, d_g, ccs,
                                             vertex_colors, vertex_ccs);

        /***********************************************************************
         * Performance Indicators Computations                                 *
         *                                                                     *
         *                                                                     *
         **********************************************************************/
        all_perfomance_indicators_2phases( descriptors, std::cout,
                                          G, d_g,
                                          vertex_colors, d_a, edge_weights, edge_colors,
                                          vertex_ccs, ccs,
                                          pixelsize,
                                          res_path);

        if(!G) delete G;

        return descriptors.desc;
    }

} // namespace graspi


#endif // GRASPI_HPP
