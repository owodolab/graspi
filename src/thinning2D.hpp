//
//  thinning2D.hpp
//  GraspiXcode
//
//  Created by Devyani Jivani on 2/2/21.
//

#ifndef thinning2D_h
#define thinning2D_h

#include "graspi_types.hpp"
#include "graph_constructors.hpp"
#include "performance_indicators.hpp"
#include "graph_cc.hpp"
#include "skeletal-descriptors.hpp"

namespace graspi {


// std::vector<std::pair<float,std::string> > compute_descriptors(const std:vector<unsigned int>& vertex_colors){

std::vector<desc_t> compute_skeletal_descriptors(int **dataMatrix, int nx, int ny){
    
    int **skelImageMatrix;
    
    **skelImageMatrix = skeletonization2D(dataMatrix, nx, ny);
    
    graspi::SKELDESC          skeletal_descriptors;    //container (vector) storing all skeletal descriptors
    
    skeletal_descriptors.initiate_skeletal_descriptors();
    
    return skeletal_descriptors.skeldesc;
}
    
    
}


#endif /* thinning2D_h */
