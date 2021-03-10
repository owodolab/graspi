/***
 *  $Id$
 **
 *  File: graspi_cc.hpp
 *  Created: May 9, 2012
 *
 *  Author: Olga Wodo, Baskar Ganapathysubramanian
 *  Copyright (c) 2012 Olga Wodo, Baskar Ganapthysubramanian
 *  See accompanying LICENSE.
 *
 *  This file is part of GraSPI.
 */

#ifndef GRASPI_CC_HPP
#define GRASPI_CC_HPP

#include "graspi_types.hpp"

namespace graspi{

    /// The class to store information about individual component

    struct CC{
        COLOR color; ///< the color of the connected component
        int size; ///< the number of vertices this component consists of
        int if_connected_to_electrode; ///< the information about connectivity to meta-vertices
        /// 0 - does not connected, 1 - connected to bottom
        /// 2 - connected to top,   3 - connected to both

        /// The constructor
        CC():color(0), size(0),
        if_connected_to_electrode(0) { }

        /// Returns if given component is connected to both bottom OR top meta-vertex
        bool if_connected_to_top_or_bottom()const{
            return (if_connected_to_electrode > 0 );
        }

        /// Returns if given component is connected to both bottom AND top meta-vertex
        bool if_connected_to_top_and_bottom()const{
            return (if_connected_to_electrode == 3 );
        }

        /// Returns if given component is connected to top meta-vertex
        bool if_connected_to_top()const{
            if( (if_connected_to_electrode == 2)
               ||
               (if_connected_to_electrode == 3) ) return true;
            return false;
        }

        /// Returns if given component is connected to bottom meta-vertex
        bool if_connected_to_bottom()const{
            if( (if_connected_to_electrode == 1)
               ||
               (if_connected_to_electrode == 3) ) return true;
            return false;
        }

        /// Function to output information about the members of this structure
        ///
        /// @param os is the steam to send to
        /// @param c is the reference to the connected component
        friend std::ostream& operator << (std::ostream& os, const CC& c){
            return os << " color: " << c.color << " size: " << c.size
            << " if connected: " << c.if_connected_to_electrode
            <<  std::endl;
        }
    };//struct CC

}//graspi-namespace

#endif
