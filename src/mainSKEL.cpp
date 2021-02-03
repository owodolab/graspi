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
#include "skeletal-descriptors.hpp"

int main() {
 
//    int vertex_colors []= {1, 1, 1, 0, 0, 0, 1, 0};
//    int if_per = false;
//    int nx = 4;
//    int ny = 4;
//    int nz = 1;
//    float pixelsize = 1.0;
        
    const std::string& inputFile = "/Users/devyanijivani/Desktop/GraspiXcode/GraspiXcode/data_circle.txt";
    const std::string& outputFile = "/Users/devyanijivani/Desktop/GraspiXcode/GraspiXcode/data_circleskel1.txt";
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
    dataMatrix = new int*[ny+(2*p)];
    for(int i = 0; i < ny+(2*p); i++) { // Matrix with dimensions (ny+2) * (nx+2)
        dataMatrix[i] = new int[nx+ (2*p)];
    }
    for (int i = 0; i < ny+(2*p); i++) { // Initializing with background pixels
        for (int j = 0; j < nx+(2*p); j++) {
            dataMatrix[i][j] = bgPixel;
        }
    }
    
    for(int i = p; i < ny+p; i++) { // Read data into matrix
        for(int j = p; j < (nx+p); j++) {
            f >> dataMatrix[i][j];
        }
    }
    f.close();
    
    graspi::compute_skeletal_descriptors(dataMatrix, nx, ny);
    
    return 0;
}

