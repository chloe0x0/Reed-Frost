#include <stdio.h>
#include <iostream>
#include <math.h>
#include <stdint.h>
#include <vector>
#include <random> // binomial distribution

/*
An implementation of the Stochastic Reed-Frost epidemic model

Given S0, I0, R0, p ∈ [0, 1], epochs, 
returns 3 vectors corresponding to the Susceptibles, Infected, and Recovered compartments over time
*/

std::vector<std::vector<long double>> storf(long double S0, long double I0, long double R0, float p, uint64_t epochs) {
    std::vector<long double> S, I, R;
    S = std::vector<long double> (epochs, 0.0);
    I = std::vector<long double> (epochs, 0.0);
    R = std::vector<long double> (epochs, 0.0);
    S[0] = S0;
    I[0] = I0;
    R[0] = R0;

    const long double q = 1.0 - p;
    for (int t = 1; t < epochs; t++) {
        
    }
}