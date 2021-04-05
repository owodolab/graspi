//
//  branch_extraction.hpp
//  GraspiXcode
//
//  Created by Devyani Jivani on 3/15/21.
//

#ifndef branch_extraction_h
#define branch_extraction_h

#include "node_identification.hpp"

namespace graspi {

/// This function checks if a pixel is in a structure

/// @param thispixel is the pointer to the pixel
/// @param branches is the pointer to the structure
/// @param n is the number of pixels in branches
/// @return true or false

bool isInStruct(node* thispixel, node* branches, int n) {
    for(int i = 0; i < n; i++) {
        if(thispixel->row == branches[i].row && thispixel->col == branches[i].col) {
            return true;
        }
    }
    return false;
}

/// This function counts the number of times a pixel is in a structure

/// @param thispixel is the pointer to the pixel
/// @param branches is the pointer to the structure
/// @param n is the number of pixels in branches
/// @return count of occurence of thispixel in branches

int isInCount(node* thispixel, node* branches, int n) {
    int count = 0;
    for(int i = 0; i < n; i++) {
        if(thispixel->row == branches[i].row && thispixel->col == branches[i].col) {
            count++;
        }
    }
    return count;
}

/// This function returns the untraversed pixel according to the priority (refer document)

/// @param this_neighbor is the pointer to the neighbors of a pixel just traversed
/// @param branches is the pointer to the structure of all branches stored
/// @param n is the number of pixels in branches
/// @return the next node to be traversed

node* getUntraversed(neighbor* this_neighbor,  node* branches, int n) {
   // node* priority = new node[89];
    node* temp_node = new node;
    temp_node->row = -1;
    temp_node->col = -1;
    temp_node->count = 0;
    int ncount = -1;
    for(int i = 0; i < 8; i++) {
        if(this_neighbor->direction[i] == true) {
            ncount++;
            if (i%2 == 0 && (isInStruct(&this_neighbor->neighbors[ncount], branches, n) == false))
                return &this_neighbor->neighbors[ncount];
    }
    }
    ncount = -1;
    for(int i = 0; i < 8; i++) {
        if(this_neighbor->direction[i] == true) {
            ncount++;
            if (isInStruct(&this_neighbor->neighbors[ncount], branches, n) == false)
                return &this_neighbor->neighbors[ncount];
    }
    }
    
    return temp_node;
    
}

/// This function returns the untraversed pixel according to the priority (refer document)

/// @param skeleton is the pointer to the skeleton
/// @param skelpixel is the size of the skeleton
/// @param branchJunction is the pointer to the intersections in the skeleton
/// @param branchEnd is the pointer to the ends of the skeleton
/// @param phasepixel is the value corresponding to the phase
/// @return descriptors

int getBranches(graspi::node* skeleton, int skelpixel, graspi::node* branchJunction, graspi::node* branchEnd, int phasepixel) {
    
    std::cout << "I am in branch extraction\n";
    
    node* branches = new node[skelpixel + branchJunction->count + branchEnd->count];
    int bcount = 0;
    
    for(int p = 0; p < branchJunction->count; p++) {
        node* curpixel = new node;
        curpixel = &branchJunction[p];
        neighbor* first_neighbors = new neighbor;
        first_neighbors = getNeighbors(curpixel, skeleton, skelpixel);
        if(isInCount(curpixel, branches, bcount) == first_neighbors->count) {
            continue;
        }
        else {
            
            branches[bcount].row = curpixel->row;
            branches[bcount].col = curpixel->col;
            bcount++;
            
            
            
 //           curpixel = getUntraversed(first_neighbors, branches, bcount); //check for even neighbors 
            for (int n = 0; n < first_neighbors->count; n++) {
                
                curpixel = getUntraversed(first_neighbors, branches,  bcount);
                if (curpixel->row == -1) {
                    continue;
                }
                if(isInStruct(curpixel, branches, bcount) == true) {
                    continue;
                }
                else {
                    bool flag = true;
                    while(flag == true){
                        if((isInStruct(curpixel, branchJunction, branchJunction->count) == true) || (isInStruct(curpixel, branchEnd, branchEnd->count) == true)) {
                            branches[bcount].row = curpixel->row;
                            branches[bcount].col = curpixel->col;
                            bcount++;
                            branches[bcount].row = -2;
                            branches[bcount].col = -2;
                            bcount++;
                            flag = false;
                            break;
                        }
                        else {
                            branches[bcount].row = curpixel->row;
                            branches[bcount].col = curpixel->col;
                            bcount++;
                        }
                        neighbor* next_local_neighbor = new neighbor;
                        next_local_neighbor = getNeighbors(curpixel, skeleton, skelpixel);
                        if (next_local_neighbor->count > 2) {
                            node* priority_node = new node;
                            priority_node = getUntraversed(next_local_neighbor, branches, bcount);
                            if (priority_node->row == -1) {
                                break;
                            }
                            if((isInStruct(priority_node,branchJunction, branchJunction->count) == true) || (isInStruct(priority_node, branchEnd, branchEnd->count) == true)) {
                                branches[bcount].row = priority_node->row;
                                branches[bcount].col = priority_node->col;
                                bcount++;
                                branches[bcount].row = -2;
                                branches[bcount].col = -2;
                                bcount++;
                                flag = false;
                            }
                            else {
                                branches[bcount].row = priority_node->row;
                                branches[bcount].col = priority_node->col;
                                bcount++;
                                next_local_neighbor = getNeighbors(priority_node, skeleton, skelpixel);
                                curpixel = getUntraversed(next_local_neighbor, branches, bcount);
                                if (curpixel->row == -1) {
                                    continue;
                                }
                            }
                        }
                        else {
                            node* priority_node = new node;
                            priority_node = getUntraversed(next_local_neighbor, branches, bcount);
                            if (priority_node->row == -1) {
                                break;
                            }
                            if((isInStruct(priority_node, branchJunction, branchJunction->count) == true) || (isInStruct(priority_node, branchEnd, branchEnd->count) == true)) {
                                branches[bcount].row = priority_node->row;
                                branches[bcount].col = priority_node->col;
                                bcount++;
                                branches[bcount].row = -2;
                                branches[bcount].col = -2;
                                bcount++;
                                flag = false;
                            }
                            else {
                                branches[bcount].row = priority_node->row;
                                branches[bcount].col = priority_node->col;
                                bcount++;
                                next_local_neighbor = getNeighbors(priority_node, skeleton, skelpixel);
                                curpixel = getUntraversed(next_local_neighbor, branches, bcount);
                            }
                            
                        }
                    }
                }
            }
        }
            
    }
    int branch_count = 0;
    for(int i = 0; i < bcount; i++) {
    std::cout << branches[i].row << " , " << branches[i].col << "\n";
        if (branches[i].row == -2) {
            branch_count++;
        }
    }
    
    for (int e = 0; e < branchEnd->count; e++) {
        node* curpixel = new node;
        curpixel = &branchEnd[e];
        if(isInStruct(curpixel, branches, bcount) == true) {
            continue;
        }
        neighbor* first_neighbors = new neighbor;
        first_neighbors = getNeighbors(curpixel, skeleton, skelpixel);
        branches[bcount].row = curpixel->row;
        branches[bcount].col = curpixel->col;
        bcount++;
        if(first_neighbors->count > 0) {
            curpixel = getUntraversed(first_neighbors, branches, bcount);
            if (curpixel->row == -1) {
                continue;
            }
            bool flag = true;
            while(flag == true){
                if((isInStruct(curpixel, branchEnd, branchEnd->count) == true)) {
                    branches[bcount].row = curpixel->row;
                    branches[bcount].col = curpixel->col;
                    bcount++;
                    branches[bcount].row = -2;
                    branches[bcount].col = -2;
                    bcount++;
                    flag = false;
                }
                else {
                    branches[bcount].row = curpixel->row;
                    branches[bcount].col = curpixel->col;
                    bcount++;
                    neighbor* next_local_neighbor = new neighbor;
                    next_local_neighbor = getNeighbors(curpixel, skeleton, skelpixel);
                    curpixel = getUntraversed(next_local_neighbor, branches, bcount);
                }
            }
        }
    }
    
    for (int i = 0; i < skelpixel; i++) {
        node* curpixel = new node;
        curpixel = &skeleton[i];
        if(isInStruct(curpixel, branches, bcount) == true) {
            continue;
        }
        neighbor* first_neighbors = new neighbor;
        first_neighbors = getNeighbors(curpixel, skeleton, skelpixel);
        branches[bcount].row = curpixel->row;
        branches[bcount].col = curpixel->col;
        bcount++;
        if(first_neighbors->count > 0) {
            curpixel = getUntraversed(first_neighbors, branches, bcount);
            if (curpixel->row == -1) {
                continue;
            }
            // CHANGE CONDITIONS
            bool flag = true;
            while(flag == true) {
                if((isInStruct(curpixel, branchEnd, branchEnd->count) == true)) {
                    branches[bcount].row = curpixel->row;
                    branches[bcount].col = curpixel->col;
                    bcount++;
                    branches[bcount].row = -2;
                    branches[bcount].col = -2;
                    bcount++;
                    flag = false;
                }
                else {
                    branches[bcount].row = curpixel->row;
                    branches[bcount].col = curpixel->col;
                    bcount++;
                    neighbor* next_local_neighbor = new neighbor;
                    next_local_neighbor = getNeighbors(curpixel, skeleton, skelpixel);
                    curpixel = getUntraversed(next_local_neighbor, branches, bcount);
                }
            }
        }
    }
    

    return 0;




}

}
#endif /* branch_extraction_h */
