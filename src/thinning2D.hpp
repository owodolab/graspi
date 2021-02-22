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
#include "skeletonization.hpp"
#include "node_identification.hpp"

namespace graspi {


// std::vector<std::pair<float,std::string> > compute_descriptors(const std:vector<unsigned int>& vertex_colors){

std::vector<desc_t> compute_skeletal_descriptors(int **dataMatrix, int nx, int ny){
    
    int **skelImageMatrix;
    
//    skelImageMatrix = new int*[ny];
//    for(int i = 0; i < (ny); i++) { // Matrix to store the skeleton (ny * nx)
//        skelImageMatrix[i] = new int[nx];
//    }
 //   **skelImageMatrix = initializeSkelMatrix(skelImageMatrix, nx, ny, 0);

    
    skelImageMatrix = skeletonization2D(dataMatrix, nx, ny);
    
    graspi::SKELDESC          skeletal_descriptors;    //container (vector) storing all skeletal descriptors
    
    skeletal_descriptors.initiate_skeletal_descriptors();
    int skelpixel = 0;
    
    std::cout << "\n\n\n";
    for(int i=0; i < ny;i++){
        for(int j=0; j < nx ;j++){
            if(skelImageMatrix[i][j] == 1){
                std::cout << skelImageMatrix[i][j];
                std::cout << " ";
                skelpixel++;
            }
        }
        std::cout << "\n";
    }
    
    identifyIntersections(skelImageMatrix, nx, ny, 1);
    
    skeletal_descriptors.update_desc("SKEL_n",skelpixel);
    
    return skeletal_descriptors.skeldesc;
}
        
}

#endif /* thinning2D_h */
