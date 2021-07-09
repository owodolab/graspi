# distutils: language=c++

cdef extern from "../src/graspiAPI.hpp":
    float compute_descriptors_only();
