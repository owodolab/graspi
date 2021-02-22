//
//  skeletal-descriptors.hpp
//  GraspiXcode
//
//  Created by Devyani Jivani on 2/2/21.
//

#ifndef skeletal_descriptors_h
#define skeletal_descriptors_h

namespace graspi {

    struct SKELDESC{
        std::vector<desc_t> skeldesc;
        find_desc_of_name find_desc;

        explicit SKELDESC(){}
        
        // set of methods to initiate and
        void initiate_skeletal_descriptors(){
            std::pair <float, std::string> p_desc;
            p_desc.first = -1;  p_desc.second = "SKEL_n";// number_of_skeletal_pixels
            skeldesc.push_back(p_desc);
        }
        
        void print_skeletal_descriptors(std::ostream& os){

            for (unsigned int i=0; i< skeldesc.size();i++){
                if (fabs(skeldesc[i].first +1 ) > 1e-10)
                    os << skeldesc[i].second << " " << skeldesc[i].first << std::endl;
            }
        }
        
        bool update_desc(std::string desc_name,float value){
            
            find_desc.set_desc(desc_name);
            std::vector< std::pair<float, std::string> >::iterator it;
            it = std::find_if( skeldesc.begin(), skeldesc.end(), find_desc );
            if (it == skeldesc.end())
                return false;
            else{
                (*it).first=value;
                return true;
            }
        }
        
    };// struct SKELDESC
}

#endif /* skeletal_descriptors_h */
