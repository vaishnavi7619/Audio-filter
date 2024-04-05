#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#define PI 3.1415926535

// Function to compute FFT
complex double *myfft(int n, complex double *a) {
    if (n == 1) return a;
    complex double *g = (complex double *)malloc(n/2 * sizeof(complex double));
    complex double *h = (complex double *)malloc(n/2 * sizeof(complex double));
    for (int i = 0; i < n; i++) { 
        if (i % 2) h[i/2] = a[i];
        else g[i/2] = a[i];
    }
    g = myfft(n/2, g);
    h = myfft(n/2, h);
    for (int i = 0; i < n; i++) 
        a[i] = g[i%(n/2)] + cexp(-I*2*PI*i/n)*h[i%(n/2)];
    free(g); free(h);
    return a;
}

// Main function to demonstrate FFT
int main() {
    int n = 6; // Size of input data
    complex double *data = (complex double *)malloc(n * sizeof(complex double));

    // Initialize input data
    double input_real[] = {1.0, 2.0, 3.0, 4.0, 2.0, 1.0};
    for (int i = 0; i < n; i++) {
        data[i] = input_real[i] + 0.0 * I; // Convert real data to complex
    }

    // Compute FFT
    data = myfft(n, data);

    // Print FFT result
    printf("FFT result:\n");
    for (int i = 0; i < n; i++) {
        printf("%.2f + %.2fi\n", creal(data[i]), cimag(data[i]));
    }

    // Free memory
    free(data);

    return 0;
}
