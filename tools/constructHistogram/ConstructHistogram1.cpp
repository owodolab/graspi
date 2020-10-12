#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>

// weighting function (f(0)=1 , f(ld)=\sim 0)
double wfoo(double d){
    //	return exp(-1.0*d*d/25.0);
    double A1=6.265;
    double B1=-23.0;
    double C1=17.17;
    return A1*exp(-((d-B1)/C1)*((d-B1)/C1));
    //	return 1.0;
}

// weighting function (f(0)=1 , f(ld)=\sim 0)
double wfoo50(double d){
    //	if ( d < 2 ) return 1.0;
    //	else return 0;

    return exp(-1.0*d*d*d/5000.0);
}


int main(int argc, char* argv[])try{

    if(argc<3) {
	std::cerr << "Usage: ConstructHistogram <inputFileWithVector> <bucket_size> <fooNumber> " << std::endl;
	return 0;
    }

    bool verbose = false;

    std::ifstream f_in(argv[1]);
    double bucket_size = std::atof(argv[2]);
    std::vector<double> v_in;

    int fooNumber = 0;
    if(argc==4) fooNumber = std::atoi(argv[3]);

    //read input data
    if(! f_in) {
	std::cerr << "Problem with inputfile " << std::endl;
	return -1;
    }
    double	tmp;
    do{
	f_in >> tmp;
	if(!f_in)break;
	v_in.push_back(tmp);
    }while(!f_in.eof());

    // sort input data
    sort(v_in.begin(),v_in.end(),std::less<double>());

    // find ranges of problem
    int problem_size = v_in.size();
    double min_value = v_in[0];
    double max_value = v_in[v_in.size()-1]+bucket_size;
    int i_min = std::floor(min_value);
    int i_max = std::ceil(max_value);

    if(verbose){
	std::cout << "Data size: " << problem_size << std::endl;
	std::cout << min_value << " " << max_value << " "
		  << i_min << " " << i_max << std::endl;
    }

    std::vector<std::pair<double,double> > histo;
    std::vector<std::pair<double,double> > cum_histo;

    // create buckets
    double i = 0;
    //	if( fabs( i_min - min_value ) < 1e-10) i = i_min - bucket_size;
    std::pair<double, double> bucket;
    do{
	if(verbose) std::cout << i << std::endl;
	bucket.first = i;
	bucket.second = 0;
	histo.push_back(bucket);
	cum_histo.push_back(bucket);
	i+= bucket_size;
    }while(i < i_max );

    if(verbose) std::cout << "Histo-size: " << histo.size() << std::endl;

    int bucket_index = 0;
    for(int i = 0; i < v_in.size(); i++){
	int index = (int)((v_in[i]+1e-20)/bucket_size);
	histo[index].second++;
    }

    int suma=0;
    for(int i = 0; i < histo.size(); i++){
	suma+=histo[i].second;
	cum_histo[i].second = suma;
	if(verbose) std::cerr << histo[i].first << " " << histo[i].second << std::endl;
    }





    std::ofstream f_out_histo("Histogram.txt");
    std::ofstream f_out_cumhisto("CumHistogram.txt");
    std::ofstream f_out_w_histo("WHistogram.txt");
    std::ofstream f_out_cum_w_histo("CumWHistogram.txt");

    for(int i = 0; i < histo.size(); i++){
	f_out_histo << histo[i].first << " " << histo[i].second << std::endl;
    }

    for(int i = 0; i < cum_histo.size(); i++){
	f_out_cumhisto << cum_histo[i].first << " " << cum_histo[i].second << std::endl;
    }

    double sum=0;
    for(int i = 0; i < histo.size(); i++){
	double w = wfoo(histo[i].first);
	if(fooNumber == 50) w = wfoo50(histo[i].first);
	sum += histo[i].second*w;
	f_out_w_histo << histo[i].first << " " << histo[i].second*w << std::endl;
	f_out_cum_w_histo << histo[i].first << " " << sum << std::endl;
    }


    return 0;
 }
 catch(std::bad_alloc e){
     std::cerr << "Problem with memory allocation " << e.what();
     return -1;
 }
 catch(...){
     std::cerr << "Unknown error" << std::endl;
     return -1;
 }
