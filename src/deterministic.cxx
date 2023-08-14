#include <stdio.h>
#include <iostream>
#include <math.h>
#include <stdint.h>
#include <vector>

/*
An implementation of the Deterministic Reed-Frost Epidemic Model

Given S0, I0, R0, p ∈ [0, 1], epochs, 
returns 3 vectors corresponding to the Susceptibles, Infected, and Recovered compartments over time

*/

std::vector<std::vector<long double>> rfdet(long double S0, long double I0, long double R0, long double p, uint64_t epochs) {
    // track the compartments over time, each will require epochs many elements and so we ought to pre-alocate them
    std::vector<long double> S, I, R;
    S = std::vector<long double> (epochs, 0.0);
    I = std::vector<long double> (epochs, 0.0);
    R = std::vector<long double> (epochs, 0.0);
    // Set the first element to be the initial conditions
    S[0] = S0;
    I[0] = I0;
    R[0] = R0;
    // The probability of succesful transmission
    const long double q = 1.0 - p;
    // Simulate the system forward in time with a deterministic update
    for (int t = 1; t < epochs; t++) {
        // get the new infected
        I[t] = S[t - 1]*(1.0 - pow(q, I[t - 1]));
        // new Susceptibles
        S[t] = S[t - 1] - I[t];
        // new Recovered
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

    uint64_t epochs = 16;

    std::vector<std::vector<long double>> trajectory = rfdet(S0, I0, R0, 0.01, epochs);

    std::cout << "S\tI\tR" << std::endl;
    for (int i = 0; i < epochs; i++) {
        long double S, I, R;
        S = trajectory[0][i];
        I = trajectory[1][i];
        R = trajectory[2][i];

        std::cout << S << '\t' << I << '\t' << R << std::endl;
    }

    std::cout << "[";
    for (int i = 0; i < epochs; i++) {
        std::cout << trajectory[1][i] << ", ";
    }
    std::cout << "]";

    std::cout << "[";
    for (int i = 0; i < epochs; i++) {
        std::cout << trajectory[0][i] << ", ";
    }
    std::cout << "]";
}
