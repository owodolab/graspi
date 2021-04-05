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
#include "skeletal_descriptors.hpp"
#include "skeletonization.hpp"
#include "node_identification.hpp"
#include "branch_extraction.hpp"


namespace graspi {


// std::vector<std::pair<float,std::string> > compute_descriptors(const std:vector<unsigned int>& vertex_colors){

std::vector<desc_t> compute_skeletal_descriptors(int **dataMatrix, int nx, int ny, int phasePixel = 1){
    
    int **skelImageMatrix;
    
//    skelImageMatrix = new int*[ny];
//    for(int i = 0; i < (ny); i++) { // Matrix to store the skeleton (ny * nx)
//        skelImageMatrix[i] = new int[nx];
//    }
 //   **skelImageMatrix = initializeSkelMatrix(skelImageMatrix, nx, ny, 0);

    
    skelImageMatrix = skeletonization2D(dataMatrix, nx, ny);
    
    SKELDESC          skeletal_descriptors;    //container (vector) storing all skeletal descriptors
    
    skeletal_descriptors.initiate_skeletal_descriptors();
    
    node* skeleton = new node[(ny+1)*(nx+1)];

    int skelpixel = 0;
    for(int i=0;i<ny;i++) {
        for(int j=0;j<nx;j++) {
            if(skelImageMatrix[i][j]==phasePixel) {
                skeleton[skelpixel].row = i;
                skeleton[skelpixel].col = j;
                skelpixel++;
            }
            std::cout << skelImageMatrix[i][j] << " ";
        }
        std::cout <<  "\n";
    }
    
    skeletal_descriptors.update_desc("SKEL_n",skelpixel);
    
    // Node Identification

    node* branchJunction = new node[nx*ny];
    node* branchEnd = new node[nx*ny];
    
    branchJunction = identifyIntersections(skeleton, skelpixel, 1);
    branchEnd = identifyEnds(skeleton, skelpixel, 1);
    
    
//    for(int i = 0; i < branchJunction->count; i++) {
//        std::cout << branchJunction[i].row << " , " << branchJunction[i].col;
//    }
    
//    for(int i = 0; i < branchEnd->count; i++) {
//        std::cout << branchEnd[i].row << " , " << branchEnd[i].col;
//    }
    
    
 
    
    skeletal_descriptors.update_desc("SKEL_END_n", skelpixel);
    skeletal_descriptors.update_desc("SKEL_INTERSECTION_n",branchJunction->count);
    skeletal_descriptors.update_desc("SKEL_BRANCH_n", branchEnd->count);
    
    
    getBranches(skeleton, skelpixel, branchJunction, branchEnd, phasePixel);
    
    /**********************************************************************
         * Graph definition and declaration                                    *
         *(list of containers to store labels of vertices and edges etc)       *
         *                                                                     *
         **********************************************************************/
        graspi::dim_g_t d_g(2,0,3); //structure storing basic dimensions of G
        graspi::dim_a_t d_a;                     //structure storing color array dimensions
        graspi::vertex_colors_t vertex_colors;   //container storing colors of vertices
        
        /***********************************************************************
         * Graph construction                                                  *
         *                                                                     *
         **********************************************************************/
//   graspi::compute_descriptors(vertex_colors, d_a.nx, d_a.ny, d_a.nz, 1, 1, true, "./");
    
    return skeletal_descriptors.skeldesc;
}
        
}

#endif /* thinning2D_h */
