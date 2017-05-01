# include <cmath>
# include <algorithm>
# include <vector>
# include "dtw.h"
# include <iostream>
# include <Rcpp.h>


template <typename T>
T minimum(T  x, T y, T z){
    return std::min(std::min(x, y), z);
    }


// distance between two symbols
template <typename T>
T distance(T ith, T jth){
    // for now, just squared euclidian distance
    return std::abs((ith - jth));
    }


// [[Rcpp:export]] 
RcppExport SEXP dtwCpp(SEXP r_time_series_1, SEXP r_time_series_2){
    
    std::vector<double> time_series_1 = Rcpp::as< std::vector<double> >(r_time_series_1);
    std::vector<double> time_series_2 = Rcpp::as< std::vector<double> >(r_time_series_2);
    int size_1 = time_series_1.size();
    int size_2 = time_series_2.size();
    double dist;


    // create dtw_matrix as continuous array
    //Rcpp::NumericMatrix dtw_matrix(size_1, size_2);
    double * dtw_matrix;
    dtw_matrix = new double[size_1 * size_2];
    dtw_matrix[0] = distance(time_series_1[0], time_series_2[0]);

    // calculate cumulative path cost for first row
    for(int i = 1; i < size_1; i++){
        dist = distance(time_series_1[i], time_series_2[0]);
        dtw_matrix[size_1*i] = dtw_matrix[size_1*(i-1)] + dist;
        }

    // calculate cumulative path cost for first column
    for(int j = 1; j < size_2; j++){
        dist = distance(time_series_1[0], time_series_2[j]);
        dtw_matrix[j] = dtw_matrix[j-1] + dist;
        }

    double insertion, deletion, match;

    // calculate cumulative path cost for rest of matrix
    for(int i = 1; i < size_1; i++){
        for(int j = 1; j < size_2; j++){
            /* Step pattern:
            *
            * Symetric step pattern is:
            * min(insertion + dist, deletion + dist, match + dist)
            *
            * However, Symetric2 step pattern, which has supposedly superior
            * properties is:
            * (min(insertion + dist, deletion + dist, match + 2dist)
            */ 
            dist = distance(time_series_1[i], time_series_2[j]);
            insertion = dtw_matrix[size_1*(i-1) + j] + dist;
            deletion = dtw_matrix[size_1*i + j-1] + dist;
            match = dtw_matrix[size_1*(i-1) + j-1] + 2*dist;
            dtw_matrix[size_1*i + j] = minimum(insertion, deletion, match);
            }
        }



    // backtracing

    // define order of values for both time_series
    std::vector<int> order_1;
    std::vector<int> order_2;

    // reserve length, length would not be larger sum of both sizes
    order_1.reserve(size_1 + size_2);
    order_2.reserve(size_1 + size_2);

    // backtracing
    int i = size_1 - 1;
    int j = size_2 - 1;
    double min;
    order_1.push_back(i+1);
    order_2.push_back(j+1);
    while ( i > 0 or j > 0){
        if (i == 0){
            j -= 1;
            }
        else if(j == 0){
            i -= 1;
            }
        else {
            min = minimum(dtw_matrix[size_1*(i-1) + j-1],
                          dtw_matrix[size_1*(i-1) + j],
                          dtw_matrix[size_1*(i) + j-1]);
            if (dtw_matrix[size_1*(i-1) + j-1] == min){
                i -= 1;
                j -= 1;
                } else if (dtw_matrix[size_1*i + j-1] == min){
                j -= 1;
                } else {
                i -= 1;
                }
            }
        order_1.push_back(i+1);
        order_2.push_back(j+1);
        }
    // results
    double normalized_dist = dtw_matrix[size_1*(size_1-1) + size_2-1]/(size_1 + size_2);

    delete [] dtw_matrix;

    std::reverse(order_1.begin(), order_1.end());
    std::reverse(order_2.begin(), order_2.end());

    Rcpp::List output_list;
    output_list["order_1"] = Rcpp::wrap(order_1);
    output_list["order_2"] = Rcpp::wrap(order_2);
    output_list["normalized_distance"] = Rcpp::wrap(normalized_dist);

    return(output_list);
    }
