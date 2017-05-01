context("Testing dynamic time warping function")

test_that("I can run simple example", {
    expect_true(!is.null(dtw(1:5, 1:5)))
    expect_true(!is.null(dtw(1:5, c(rep(1,5), 1:5))))
    })


testdata = "testdata"
filename_1 = file.path(testdata, "time_series_1.txt")
filename_2 = file.path(testdata, "time_series_2.txt")
time_series_1 = as.numeric(strsplit(readLines(filename_1, warn=FALSE), split=" ", fixed=TRUE)[[1]])
time_series_2 = as.numeric(strsplit(readLines(filename_2, warn=FALSE), split=" ", fixed=TRUE)[[1]])


test_that("I can run more involved example with real data", {
    expect_true(!is.null(dtw(time_series_1, time_series_2)))
    })


test_that("I get the same normalized distance using dtw::dtw", {
    library("dtw")
    simple_dtw = simpleDTW::dtw(time_series_1, time_series_2)$normalized_distance
    dtw_dtw = dtw::dtw(time_series_1, time_series_2)$normalizedDistance
    expect_equal(simple_dtw, dtw_dtw)
    })
