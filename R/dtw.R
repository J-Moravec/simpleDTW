#' Performs dynamic time warping
#'
#' Performs dynamic time warping for two input time series.
#'
#' @param time_series_1 first time series
#' @param time_series_2 second time series
#'
#' @return gods now what
#'
#' @export
dtw = function(time_series_1, time_series_2){
    tryCatch({
        time_series_1 = as.numeric(time_series_1)
        time_series_2 = as.numeric(time_series_2)
        },
        error = function(x){
            message("Time series bust be coercible into numeric vector!")
            stop(x)
            }
        )
    .Call("dtwCpp", time_series_1, time_series_2, package="simpleDTW")
    }



#' @importFrom Rcpp evalCpp
#' @useDynLib simpleDTW
NULL
