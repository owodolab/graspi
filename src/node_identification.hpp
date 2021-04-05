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
    int count;
}node;


typedef struct{
    int count;
    int even;
    int odd;
    bool direction[8];
    node neighbors[8];
}neighbor;

/// This function returns a pointer to the neighbor data for an input pixel.
/// The data includes the count of skeletal neighbors, the count of even and odd neighbors (refer the document), directions of the neighbors, and the pixel positions of all the neighbors
/// @param thispixel  is the pointer to the pixel for which the neighbor data is to be calculated
/// @param skeleton is the pointer to the structure containing the pixel positions of the skeleton
/// @param skelsize is the length of the skeleton
/// @return pointer to the struct encoding the information about the 8-neighborhood of the input pixel

neighbor* getNeighbors(node* thispixel, node* skeleton, int skelsize){ //Number of neighbors that belong to the image
    neighbor* neighbordata = new neighbor [9];
    neighbordata->count = 0;
    node neighbors[8] = {{thispixel->row, thispixel->col - 1}, {thispixel->row - 1, thispixel->col - 1}, {thispixel->row - 1, thispixel->col}, {thispixel->row - 1, thispixel->col + 1}, {thispixel->row, thispixel->col + 1}, {thispixel->row + 1, thispixel->col + 1}, {thispixel->row + 1, thispixel->col}, {thispixel->row + 1,
        thispixel->col - 1}};
    neighbordata->count = 0;
    neighbordata->even = 0;
    neighbordata->odd = 0;
    for(int i = 0; i < 8; i++){
//        std::cout << neighbors[i].row << " , " << neighbors[i].col << " --- \n";
        neighbordata->direction[i] = 0;
        for(int j=0; j < skelsize; j++){
//            std::cout << skeleton[j].row << " , " << skeleton[j].col << "\n";
            if (neighbors[i].row == skeleton[j].row && neighbors[i].col == skeleton[j].col){
                neighbordata->direction[i] = 1;
//                std::cout << skeleton[j].row << " , " << skeleton[j].col << "-------" << neighbors[i].row << " , " << neighbors[i].col << "\n";
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
//    std::cout << neighbordata->count;
    return neighbordata;
}

/// This function returns true/false if a neighbor exists in certain directions
/// @param neighbordata  is a pointer to  the structure storing the information aobut the neighbors
/// @param ndir is a pointer to the array of directions in which neighbor exists is to be checked
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


/// This function deletes the elements from a structure and returns the structure
/// @param delposition  is the index to the deleted
/// @param allNodes is a pointer to the struct from which an entry is to be deleted
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

/// This function return true if the element is in the array
/// @param val  is the element
/// @param inputArray is a pointer to the array
/// @param sizeA is the size of inputArray
/// @return true if the element is in inputArray

bool isInArray(int val, int* inputArray, int sizeA){
    for(int i = 0; i < sizeA; i++) {
        if (inputArray[i] == val)
            return true;
    }
    return false;
}

/// This function returns the information about the branch ends of a skeleton
/// @param skeleton  is a pointer to the struct the contains the skeletal pixel postitions
/// @param skelpixel is the size of the skeleton structure
/// @param phasePixel is the value corresponding to the phase of the skeleton
/// @return pointer to the structure containing information (count and positions) about the branch ends

node* identifyEnds(node* skeleton, int skelpixel,int phasePixel) {
    node* branchEnd = new node [skelpixel];
    neighbor* thispixel_neighbors = new neighbor;
    node* thispixel = new node;
    
    int endcount = 0;
    
    for(int i = 0; i < skelpixel; i++) {
        thispixel = &skeleton[i];
//        std::cout << thispixel->row << " , " << thispixel->col << "\n";
        thispixel_neighbors = getNeighbors(thispixel, skeleton, skelpixel);
        
        if(thispixel_neighbors->count == 1) {
            branchEnd[endcount] = *thispixel;
            endcount++;
        }
        else if(thispixel_neighbors->count == 2) {
            //            std::cout << "Do something! \n";
        }
    }
    branchEnd->count = endcount;
    return branchEnd;
}

/// This function returns the information about the intersections of a skeleton
/// @param skeleton  is a pointer to the struct the contains the skeletal pixel postitions
/// @param skelpixel is the size of the skeleton structure
/// @param phasePixel is the value corresponding to the phase of the skeleton
/// @return pointer to the structure containing information (count and positions) about the intersections

node* identifyIntersections(node* skeleton, int skelpixel, int phasePixel) {
    
    
    neighbor* thispixel_neighbors = new neighbor;
    node* thispixel = new node;

    node* potentialJunction = new node [skelpixel];
    node* branchEnd = new node [skelpixel];
    
    branchEnd = identifyEnds(skeleton, skelpixel, phasePixel);
    int endcount = branchEnd->count;
    
    int potjunctcount = 0;
    for(int i = 0; i < skelpixel; i++) {
        thispixel = &skeleton[i];
//        std::cout << thispixel->row << " , " << thispixel->col << "\n";
        thispixel_neighbors = getNeighbors(thispixel, skeleton, skelpixel);
        if(thispixel_neighbors->count > 2){
            potentialJunction[potjunctcount] = *thispixel;
            potjunctcount++;
        }
        
    }
    
    
    // DEBUG
//    for(int i = 0 ; i < potjunctcount; i++){
//        std::cout <<  potentialJunction[i].row << " , " << potentialJunction[i].col << "\n";
//    }
//    for(int i = 0 ; i < endcount; i++){
//        std::cout <<  branchEnd[i].row << " , " << branchEnd[i].col << "\n";
//    }

    // Identify junction nodes from potential junction nodes
    node* delpixel = new node[skelpixel];
    int* delIdx = new int[potjunctcount];
    int del = 0;
    for(int i = 0; i < potjunctcount; i++) {
        node* curpixel = new node;
        curpixel = &potentialJunction[i];
        neighbor* potJunc_neighbors = new neighbor;
        neighbor* first_neighbors = new neighbor;
        first_neighbors = getNeighbors(curpixel, skeleton, skelpixel);
        potJunc_neighbors = getNeighbors(curpixel, potentialJunction, potjunctcount);
        bool delflag = 0;
        for (int j = 0; j < endcount; j++){
            for (int k = 0; k < first_neighbors->count; k++) {
                if (branchEnd[j].row == first_neighbors->neighbors[k].row && branchEnd[j].col == first_neighbors->neighbors[k].col) {
 //                   delpixel[del].row = curpixel->row;
 //                   delpixel[del].col = curpixel->col;
                    delIdx[del] = i;
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
        if (potJunc_neighbors->count > 0 && first_neighbors->even == 2) {
            if ((first_neighbors->direction[0] == true && first_neighbors->direction[4] == true) ||
                (first_neighbors->direction[2] == true && first_neighbors->direction[6] == true)) {
                delpixel[del].row = curpixel->row;
                delpixel[del].col = curpixel->col;
                delIdx[del] = i;
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
//    std::cout << del;
    node* updatedpotentialJunction = new node[potjunctcount];
    
    int tlen = 0;
    
    // Deleting marked pixels
    
    if(del == 0) {
        updatedpotentialJunction = potentialJunction;
        tlen = potjunctcount;
    }
    else {
        for (int i = 0; i < potjunctcount; i++) {
            if (isInArray(i, delIdx, del)) {
                continue;
            }
            else {
                updatedpotentialJunction[tlen].row = potentialJunction[i].row;
                updatedpotentialJunction[tlen].col = potentialJunction[i].col;
                tlen++;
            }
        }
    }
    
    
    delete [] delpixel;
    delete [] potentialJunction;
    
    del = 0;
    
    for(int i = 0; i < tlen; i++) {
        
        node* curpixel = new node;
        curpixel = &updatedpotentialJunction[i];
        neighbor* potJunc_neighbors = new neighbor;
        neighbor* first_neighbors = new neighbor;
        first_neighbors = getNeighbors(curpixel, skeleton, skelpixel);
        potJunc_neighbors = getNeighbors(curpixel, updatedpotentialJunction, tlen);
        int tempsize = potJunc_neighbors->count + 1;
        int* even_neighbor_count = new int[tempsize];
        even_neighbor_count[0] = first_neighbors->even;
        node* temp_node = new node[tempsize];
        temp_node[0].row = curpixel->row;
        temp_node[0].col = curpixel->col;
        if (potJunc_neighbors->count > 0) {
            for(int j = 0; j < potJunc_neighbors->count; j++) {
                node* curneighbor = new node;
                curneighbor = &potJunc_neighbors->neighbors[j];
                neighbor* second_neighbors = new neighbor;
                second_neighbors = getNeighbors(curneighbor, skeleton, skelpixel);
                even_neighbor_count[j+1] = second_neighbors->even;
                temp_node[j+1].row = curneighbor->row;
                temp_node[j+1].col = curneighbor->col;
            }
            int maximumIdx = 0;
            int max = even_neighbor_count[0];
            for (int d = 0; d < tempsize; d++){
                if (even_neighbor_count[d] > max){
                        max = even_neighbor_count[d];
                        maximumIdx = d;
                }
            }
            for (int d = 0; d < tempsize; d++){
                if (d == maximumIdx){
                    continue;
                }
                else {
                    delpixel[del].row = temp_node[d].row;
                    delpixel[del].col = temp_node[d].col;
                    del++;
                }
            }
            
        }
        
    }
    
    node* branchJunction = new node[tlen];
    
    int junctcount = 0;
    
    // Deleting marked pixels
    int* removeIdx  = new int[tlen];
    int r = -1;
    if(del == 0) {
        branchJunction = updatedpotentialJunction;
        junctcount = tlen;
    }
    else {
        for (int i = 0; i < tlen; i++) {
            for(int j = 0 ; j < del; j++) {
                if(updatedpotentialJunction[i].row == delpixel[j].row && updatedpotentialJunction[i].col == delpixel[j].col) {
                    r++;
                    removeIdx[r] = i;
                    continue;
                }
            }
        }
    }
    
    for (int rem = 0; rem <= r; rem++) {
        if(isInArray(rem, removeIdx, r+1)){
            continue;
        }
        else {
            branchJunction[junctcount].row = updatedpotentialJunction[rem].row;
            branchJunction[junctcount].col = updatedpotentialJunction[rem].col;
            std::cout << branchJunction[junctcount].row << " , " << branchJunction[junctcount].col << "\n";
            junctcount++;
        }
        
    }
    branchJunction->count = junctcount;
    int* node_counts = new int[2];
    node_counts[0] = endcount;
    node_counts[1] = junctcount;
    
    
    
    return branchJunction;
}
}

#endif /* node_identification_h */
