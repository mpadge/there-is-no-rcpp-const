Note to Self: Rcpp classes are always passed by reference!
==========================================================

`Rcpp` passes all internals objects by reference only, never by value. This repo demonstrates the implications of this as a clear and simple Note To Self. It relies on these `C++` functions

    // [[Rcpp::export]]
    void rcpp_test1(const Rcpp::DataFrame df) {
        Rcpp::IntegerVector x = df ["x"];
        x = x + 1;
    }

    // [[Rcpp::export]]
    void rcpp_test2(const Rcpp::DataFrame df) {
        std::vector <int> x = df ["x"];
        for (auto i: x)
            i++;
    }

``` r
devtools::load_all (".", export_all = FALSE)
df <- data.frame (x = 1:5, y = 1:5)
test1 (df)
df
```

    ##   x y
    ## 1 2 1
    ## 2 3 2
    ## 3 4 3
    ## 4 5 4
    ## 5 6 5

Running `test1()` alters the values of `df` because the internal `Rcpp::IntegerVector` object is constructed strictly by reference only. In contrast, the `rcpp_test2` function implements an implicit copy-by-value through the typecast to `std::vector`, and so

``` r
test2 (df)
df
```

    ##   x y
    ## 1 2 1
    ## 2 3 2
    ## 3 4 3
    ## 4 5 4
    ## 5 6 5

An alternative is `Rcpp::clone()`, as demonstrated in the third function:

    // [[Rcpp::export]]
    void rcpp_test3(const Rcpp::DataFrame df) {
        const Rcpp::IntegerVector x = df ["x"];
        Rcpp::IntegerVector x2 = Rcpp::clone (x);
        x2 = x2 + 1;
    }

This also leaves the original unmodified:

``` r
test3 (df)
df
```

    ##   x y
    ## 1 2 1
    ## 2 3 2
    ## 3 4 3
    ## 4 5 4
    ## 5 6 5
