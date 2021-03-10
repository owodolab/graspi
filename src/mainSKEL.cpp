#include <cstdlib>
#include <iostream>
#include "time_check.hpp"
#include "graspi_types.hpp"
#include "graph_constructors.hpp"
#include "graph_io.hpp"
#include "graph_cc.hpp"
#include "performance_indicators.hpp"
#include "graspi_descriptors.hpp"
#include "graspi.hpp"
#include "skeletonization.hpp"
#include "thinning2D.hpp"
#include "skeletal_descriptors.hpp"

int main(int argc, char *argv[]) {
 
//    int vertex_colors []= {1, 1, 1, 0, 0, 0, 1, 0};
//    int if_per = false;
//    int nx = 4;
//    int ny = 4;
//    int nz = 1;
//    float pixelsize = 1.0;

//    printf("Program Name Is: %s",argv[0]); 
    if(argc==1) 
        printf("\nNo Extra Command Line Argument Passed Other Than Program Name"); 
//    if(argc>=2) 
//    { 
//            printf("\nargv[%d]: %s",1,argv[1]); 
//    }

    const std::string& inputFile = argv[1];
    const std::string& outputFile = argv[2];    

    int nx, ny;
    //graspi::thinning2D(inputFile,outputFile);
 //   graspi::compute_descriptors_only(vertex_colors, nx, ny, nz = 1, pixelsize, if_per);
    
    std::ifstream f(inputFile.c_str());
    std::string str;
    getline(f,str);
    std::istringstream iss(str);
    iss >> nx >> ny; // Reading matrix dimensions
    int p = 15;
    int **dataMatrix;
    int bgPixel = 0;
    
    // Allocate memory
    dataMatrix = new int*[ny];
    for(int i = 0; i < ny; i++) { // Matrix with dimensions (ny+2) * (nx+2)
        dataMatrix[i] = new int[nx];
    }
//    for (int i = 0; i < ny+(2*p); i++) { // Initializing with background pixels
//        for (int j = 0; j < nx+(2*p); j++) {
//            dataMatrix[i][j] = bgPixel;
//        }
//    }
    
    for(int i = 0; i < ny; i++) { // Read data into matrix
        for(int j = 0; j < nx; j++) {
            f >> dataMatrix[i][j];
        }
    }
    f.close();
    
    for(int i=0; i < ny;i++){
            for(int j=0; j < nx ;j++){
 //               if(skelImageMatrix[i][j] == 1){
                    std::cout << dataMatrix[i][j];
                    std::cout << " ";
                }
                std::cout << "\n";
            }
        
        
        
    graspi::compute_skeletal_descriptors(dataMatrix, nx, ny);
    
    return 0;
}

