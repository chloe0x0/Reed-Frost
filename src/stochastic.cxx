#include <stdio.h>
#include <iostream>
#include <math.h>
#include <stdint.h>
#include <vector>
#include <random> // binomial distribution
#include <time.h>

// Function for binomial random variate sampling
long double rbinom(int size, long double p, std::default_random_engine gen) {
    std::binomial_distribution<int> distr(size, p);
    return distr(gen);
}

/*
An implementation of the Stochastic Reed-Frost epidemic model

Given S0, I0, R0, p ∈ [0, 1], epochs, 
returns 3 vectors corresponding to the Susceptibles, Infected, and Recovered compartments over time
*/

std::vector<std::vector<long double>> storf(long double S0, long double I0, long double R0, float p, uint64_t epochs) {
    std::default_random_engine gen(time(0));

    std::vector<long double> S, I, R;
    S = std::vector<long double> (epochs, 0.0);
    I = std::vector<long double> (epochs, 0.0);
    R = std::vector<long double> (epochs, 0.0);
    S[0] = S0;
    I[0] = I0;
    R[0] = R0;

    const long double q = 1. - p;
    for (int t = 1; t < epochs; t++) {
        I[t] = rbinom(S[t-1], 1. -pow(q,I[t-1]), gen);
        S[t] = S[t - 1] - I[t];
        R[t] = R[t - 1] + I[t - 1];
    }

    std::vector<std::vector<long double>> compartments = {S, I, R};
    return compartments;
}

int main(void) {
    long double N = 201;
    long double S0, I0, R0;
    I0 = 1.0;
    R0 = 0.0;
    S0 = N - I0 - R0;

    uint64_t epochs = 50;

    std::vector<std::vector<long double>> trajectory = storf(S0, I0, R0, 0.01, epochs);

    std::cout << "S\tI\tR" << std::endl;
    for (int i = 0; i < epochs; i++) {
        long double S, I, R;
        S = trajectory[0][i];
        I = trajectory[1][i];
        R = trajectory[2][i];

        std::cout << S << '\t' << I << '\t' << R << std::endl;
    }

    std::cout << "I = [";
    for (int i = 0; i < epochs; i++) {
        std::cout << trajectory[1][i] << ", ";
    }
    std::cout << "]" << std::endl; 

    std::cout << "S = [";
    for (int i = 0; i < epochs; i++) {
        std::cout << trajectory[0][i] << ", ";
    }
    std::cout << "]";
}