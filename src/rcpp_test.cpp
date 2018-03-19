
#include <Rcpp.h>
using namespace Rcpp;

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
