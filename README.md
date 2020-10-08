
<!-- README.md is generated from README.Rmd. Please edit that file -->

# TravelExample

This is an example package to show how to build package based upon the
Travel package. Please see code under `src/` to find the detailed
information. You can run these test code to see the result

``` r
devtools::load_all()
#> Loading TravelExample

## Create a super lengthy arithmetic sequence
x <- make_sequence_altrep(n = 1024*1024*1024*64, start = 1, step = 2)
length(x)
#> [1] 68719476736
x[1:10]
#>  [1]  1  3  5  7  9 11 13 15 17 19

## You can change the value of the vector without any problem
x[1] <- 100
x[1:10]
#>  [1] 100   3   5   7   9  11  13  15  17  19

## The private data of the vector will be GC
## When the vector is not in used(see `Seq_info` in `main.cpp`)
rm(x)
gc()
#> I am called from GC
#>           used (Mb) gc trigger (Mb) max used (Mb)
#> Ncells  676505 36.2    1212567 64.8  1212567 64.8
#> Vcells 1207166  9.3    8388608 64.0  1871389 14.3
```
