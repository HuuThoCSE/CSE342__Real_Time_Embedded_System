#include <iostream>
using namespace std;

int nextFit(int weight[], int n, int c){
    int res = 0, bin_rem = c;

    for (int i = 0; i < n; i++){

        if (weight[i] > bin_rem){
            res++;
            bin_rem = c - weight[i];
        } else {
            bin_rem -= weight[i];
        }
    }
    return res;
}

int firstFit(int weight[], int n, int c){
    int res = 0;
    int bin_rem[n];
    for(int i=0; i < n; i++){
        int j;
        for(j=0; j <res; j++){
            if(bin_rem[j] >= weight[i]){
                bin_rem[j] = bin_rem[j] - weight[i];

                break;
            }
        }

        if (j == res){
            bin_rem[res] = c - weight[i];
            res++;
        }
    }
    return res;
}

int bestFit(int weight[], int n, int c){
    
    // Initialize result (Count of bins)
    int res = 0;

    // Create an array to store
    // remaining space in bins
    // there can be at most n bins
    int bin_rem[n];

    // Place items one by one
    for (int i = 0; i < n; i++){
        // Find the best bin that can accommodate
        // weight[i]
        int j;

        // Initialize minimum space left and index
        // of best bin
        int min = c + 1, bi = 0;

        for (j=0; j < res; j++){
            if (bin_rem[j] >= weight[i] && bin_rem[j] - weight[i] < min){
                bi = j;
                min = bin_rem[j] - weight[i];
            }
        }

        // If no bin could accommodate weight[i],
        // create a new bin
        if (min == c + 1){
            bin_rem[res] = c - weight[i];
            res++;
        } else //
            bin_rem[i] -= weight[i];
    }
    return res;
}

int worstFit(int weight[], int n, int c){
    // Initialize resuft (Count of bins)
    int res = 0;

    // Create an array to store remaining space in bins
    // there can be at most n bins
    int bin_rem[n];

    // Place items one by one
    for (int i = 0; i < n; i++){
        // Find the best bin that can accommodate
        // weight[i]
        int j;

        // Initialize maximum space left and index
        // of worst bin
        int mx = -1, wi = 0;

        for (j = 0; j < res; j++){
            if (bin_rem[j] >= weight[i] && bin_rem[j] - weight[i] > mx){
                wi = j;
                mx = bin_rem[j] - weight[i];
            }
        }

        // If no bin could accommodate weight[i],
        // create a new bin
        if (mx == -1){
            bin_rem[res] = c - weight[i];
            res++;
        } else // Assign the item to best bin
             bin_rem[wi] -= weight[i];
    }
    return res;
}

// Driver program
int main(){
    int weight[] = {2, 5, 4 , 7, 1, 3 , 8};
    int c = 10;
    int n = sizeof(weight) / sizeof(weight[0]);
    cout << "Number of bins required in Next Fit: " << nextFit(weight, n, c) << "\n";
    cout << "Number of bins required in First Fit: " << firstFit(weight, n, c) << "\n";
    cout << "Number of bins required in First Fit: " << bestFit(weight, n, c) << "\n";
    cout << "Number of bins required in First Fit: " << worstFit(weight, n, c) << "\n";
    return 0;
}