//
//  node_identification.hpp
//  GraspiXcode
//
//  Created by Devyani Jivani on 2/7/21.
//

#ifndef node_identification_h
#define node_identification_h

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>


namespace graspi {

  typedef struct{
      int row;
      int col;
  }node;

typedef struct{
    int count;
    int even;
    int odd;
    bool direction[8];
    node neighbors[8];
}neighbor;

/// This function returns the neighbor data for an input pixel.
/// The data includes the count of skeletal neighbors, the count of even and odd neighbors (refer the document), directions of the neighbors, and the pixel positions of all the neighbors
/// @param thispixel  is the pixel for which the neighbor data is to be calculated
/// @param skeleton are the pixel positions corresponding to the skeleton
/// @param skelsize is the length of the skeleton
/// @return neighbordata the information about the 8-neighborhood of the input pixel

neighbor* getNeighbors(node* thispixel, node* skeleton, int skelsize){ //Number of neighbors that belong to the image
    neighbor* neighbordata = new neighbor [9];
    neighbordata->count = 0;
    node neighbors[8] = {{thispixel->row, thispixel->col - 1}, {thispixel->row - 1, thispixel->col - 1}, {thispixel->row - 1, thispixel->col}, {thispixel->row - 1, thispixel->col + 1}, {thispixel->row, thispixel->col + 1}, {thispixel->row + 1, thispixel->col + 1}, {thispixel->row + 1, thispixel->col}, {thispixel->row + 1,
        thispixel->col - 1}};
    neighbordata->count = 0;
    neighbordata->even = 0;
    neighbordata->odd = 0;
    for(int i = 0; i < 8; i++){
        neighbordata->direction[i] = 0;
        for(int j=0; j < skelsize; j++){
            if (neighbors[i].row == skeleton[j].row && neighbors[i].col == skeleton[j].col){
                neighbordata->direction[i] = 1;
                neighbordata->neighbors[neighbordata->count].row = neighbors[i].row;
                neighbordata->neighbors[neighbordata->count].col = neighbors[i].col;
                neighbordata->count++ ;
                if(i % 2 == 0) {
                    neighbordata->even++;
                    break;
                }
                else {
                    neighbordata->odd++;
                    break;
                }
                std::cout << i << " , " << j << "\n";
            }
        }
    }
    std::cout << neighbordata->count++;
    return neighbordata;
}

/// This function returns true/false if a neighbor exists in certain directions
/// @param neighbordata  is the structure storing the information aobut the neighbors
/// @param ndir is the array of directions in which neighbor exists is to be checked
/// @param dir_count is the count of the directions
/// @return neighbor_exists is a true/false value if the neighbor exists in all the input directions

bool getNeighborPosition(neighbor* neighbordata, int* ndir, int dir_count){
    bool neighbor_exists = false;
    int this_dir;
    for(int i = 0; i < dir_count; i++){
        this_dir = ndir[i];
        if (neighbordata->direction[this_dir] == 1){
            neighbor_exists = true;
        }
        else {
            return false;
        }
    }
    return neighbor_exists;
}

/// This function deletes the elements of struct Node
/// @param delposition  is the index to the deleted
/// @param allNodes is the struct from which an entry is to be deleted
/// @param lenAllNodes is the size of the struct
/// @return allNodes is the struct after deletion

node* delNode(int delposition, node* allNodes, int lenAllNodes) {
    for (int i = delposition; i < lenAllNodes - 1; i++) {
        allNodes[i].row = allNodes[i+1].row;
        allNodes[i].col = allNodes[i+1].col;
    }
    allNodes[lenAllNodes].row = -1;
    allNodes[lenAllNodes].col = -1;
    return allNodes;
}

/// This function computes skeletal descriptors of morphology defined on structured matrix
///
/// This function computes a set of descriptors of morphology
/// @param skeletonMatrix is the thinned morphology stored as a 2D matrix of pixel positions corresponding to the skeleton
/// @param nx is the number of voxels in x-direction
/// @param ny is the number of voxels in y-direction
/// @param phasePixel is the value of the pixel that corresponds to the skeleton in skeletonMatrix
/// @return the vector of descriptors, where each descriptor is a pair (std::pair<float,std::string>) consisting of descriptor's value (float) and name (string)

int identifyIntersections(int** skeletonMatrix, int nx, int ny, int phasePixel) {
    
    node* skeleton;

    skeleton = (node*)malloc((ny+1)*(nx+1)*sizeof(node));
    int skelpixel = 0;
    for(int i=1;i<ny;i++) {
        for(int j=1;j<=nx;j++) {
            if(skeletonMatrix[i][j]==phasePixel) {
                skeleton[skelpixel].row = i;
                skeleton[skelpixel].col = j;
                skelpixel++;
            }
        }
    }
 
    neighbor* thispixel_neighbors = new neighbor;
    node* thispixel = new node;

    node* potentialJunction = new node [(ny+1)*(nx+1)];
    node* branchEnd = new node [(ny+1)*(nx+1)];
    
    int endcount = 0, potjunctcount = 0;
    for(int i = 0; i < skelpixel; i++) {
        thispixel = &skeleton[i];
        std::cout << thispixel->row << " , " << thispixel->col << "\n";
        thispixel_neighbors = getNeighbors(thispixel, skeleton, skelpixel - 1);
        
        if(thispixel_neighbors->count == 1) {
            branchEnd[endcount] = *thispixel;
            endcount++;
        }
        else if(thispixel_neighbors->count > 2){
            potentialJunction[potjunctcount] = *thispixel;
            potjunctcount++;
        }
        else if(thispixel_neighbors->count == 2) {
            std::cout << "Do something! \n";
        }
    }

    // Identify junction nodes from potential junction nodes
    node* delpixel = new node[skelpixel];
    int del = 0;
    for(int i = 0; i < potjunctcount; i++) {
        node* curpixel = new node;
        curpixel = &potentialJunction[i];
        neighbor* potJunc_neighbors = new neighbor;
        neighbor* first_neighbors = new neighbor;
        first_neighbors = getNeighbors(curpixel, skeleton, skelpixel - 1);
        potJunc_neighbors = getNeighbors(curpixel, potentialJunction, potjunctcount);
        bool delflag = 0;
        for (int j = 0; j < endcount; j++){
            for (int k = 0; k < first_neighbors->count; k++) {
                if (branchEnd[j].row == first_neighbors->neighbors[k].row && branchEnd[j].col == first_neighbors->neighbors[k].col) {
                    delpixel[del].row = curpixel->row;
                    delpixel[del].col = curpixel->col;
                    del++;
                    delflag = 1;
                    continue;
            }
            
            }
            if (delflag == 1) {
                delflag = 0;
                continue;
            }
            
        }
        if (potJunc_neighbors->count > 0 && first_neighbors->odd == 2) {
            if ((first_neighbors->direction[0] == 1 && first_neighbors->direction[4] == 1) ||
                (first_neighbors->direction[2] == 1 && first_neighbors->direction[6] == 1)) {
                delpixel[del].row = curpixel->row;
                delpixel[del].col = curpixel->col;
                del++;
                delflag = 1;
                continue;
                
            }
            if (delflag == 1) {
                delflag = 0;
                continue;
            }
            
        }
        delete first_neighbors;
        delete potJunc_neighbors;
    }
    int lenAllPot = potjunctcount;
    node* updatedpotentialJunction = new node[potjunctcount];
    for (int d = 0; d < del; d++) {
        for (int i = 0; i < potjunctcount; i++) {
            if (potentialJunction[i].row == delpixel[i].row &&
                potentialJunction[i].col == delpixel[i].col) {
                updatedpotentialJunction = delNode(i, potentialJunction, lenAllPot);
                lenAllPot--;
            }
        }
    }
    
    delete [] delpixel;
    delete [] potentialJunction;
    
    for(int i = 0; i < lenAllPot; i++) {
        
        node* curpixel = new node;
        curpixel = &updatedpotentialJunction[i];
        neighbor* potJunc_neighbors = new neighbor;
        neighbor* first_neighbors = new neighbor;
        first_neighbors = getNeighbors(curpixel, skeleton, skelpixel - 1);
        potJunc_neighbors = getNeighbors(curpixel, potentialJunction, potjunctcount);
        node* delpixel = new node[skelpixel];
        int* odd_second_neighbor_count = new int[potJunc_neighbors->count];
        if (potJunc_neighbors->count > 0) {
            for(int j = 0; j < potJunc_neighbors->count; j++) {
                node* curneighbor = new node;
                curneighbor = &potJunc_neighbors->neighbors[j];
                neighbor* second_neighbors = new neighbor;
                second_neighbors = getNeighbors(curneighbor, skeleton, skelpixel - 1);
                odd_second_neighbor_count = &second_neighbors->odd;
            }
            
        }
        
        
    }
    return 0;
}
}
#endif /* node_identification_h */
