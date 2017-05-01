// dtw.h

# ifndef DTW_H
# define DTW_H

struct dtw_output {
    std::vector<int> order_1;
    std::vector<int> order_2;
    double * dtw_matrix;
    };

dtw_output * dtw(int size_1, double time_series_1[], int size_2, double time_series_2[]);

# endif
