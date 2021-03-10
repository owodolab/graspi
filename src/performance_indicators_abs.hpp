/***
 *  $Id$
 **
 *  File: performance_indicators_abs.hpp
 *  Created: May 9, 2012
 *
 *  Author: Olga Wodo, Baskar Ganapathysubramanian
 *  Copyright (c) 2012 Olga Wodo, Baskar Ganapathysubramanian
 *  See accompanying LICENSE.
 *
 *  This file is part of GraSPI.
 */

#ifndef PERFORMANCE_INDICATORS_ABS_HPP
#define PERFORMANCE_INDICATORS_ABS_HPP

#include "graspi_types.hpp"

#include <cmath>

namespace graspi {

    /// The structure to define the weghting function to estimate the probability of contributing to the light absoption
    struct foo_w_abs{
        double Lexp; ///< the light absorption lenght scale

        /// The constructor
        foo_w_abs(double L = 100):Lexp(L){ }
        /// The operator to estimate the contribution to the light absorption
        double operator()(double d)const{ return exp(-1.0*d/Lexp); }
    };


    /// The structure to define homogenous light absorption (no weighting function)
    struct foo_no_w_abs{
        foo_no_w_abs(){ }
        double operator()(double d)const{ return 1.0; }
    };

    /// The function to estimate the contribution of electron donor to light absorption
    /// @tparam WFoo is the weigting function to be used for this descriptor calculation
    /// @param C is the vector storing the labels/colors of vertices in the graph G
    /// @param dim_a is the structure storing information about the labels array
    /// @param wf is the weigting function used for estimating the contribution
    /// @param pixelsize is the pixelsize
    /// @return the weighted fraction of electron donor contributing to light absorption
    template<typename WFoo>
    inline double wf_abs(const vertex_colors_t& C, const dim_a_t& d_a, WFoo wf,
                         double pixelsize){
        double w_abs = 0;
        unsigned int total_n = d_a.nx * d_a.ny;

        if( (d_a.nz == 0) || (d_a.nz == 1) ){//2D
            for(unsigned int j = 0; j < d_a.ny; j++){
                for(unsigned int i = 0; i < d_a.nx; i++){
                    int id = i + d_a.nx * j;
                    if(C[id] == BLACK){
                        double h_diff = (double)(d_a.ny-j)*pixelsize;
                        w_abs += wf(h_diff);
                    }//BLACK
                }//i
            }//j
        }else{//3D
            total_n *= d_a.nz;;
            for(unsigned int k = 0; k < d_a.nz; k++){
                for(unsigned int j = 0; j < d_a.ny; j++){
                    for(unsigned int i = 0; i < d_a.nx; i++){
                        unsigned int id = i + d_a.nx * ( j + d_a.ny * k);
                        if(C[id] == BLACK){
                            double h_diff = (double)(d_a.nz-k)*pixelsize;
                            w_abs += wf(h_diff);
                        }//BLACK
                    }//i
                }//j
            }//k
        }//end-3D

        return w_abs/total_n;
    }

} // namespace graspi

#endif // PERFORMANCE_INDICATORS_HPP
