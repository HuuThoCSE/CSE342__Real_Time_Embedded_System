#include <iostream>
using namespace std;

//------------------nextFit
int nextFit(int weight[], int n, int c){

    // Initialize result (Count of bins) and remaining
    // capacity in current bin.
    int res = 0, bin_rem = c;

    // Place items one by one
    for (int i = 0; i < n; i++){            // O(n)
        // If this item can't fit in current bin
        if (weight[i] > bin_rem){           // O(1)
            res++;  // Use a new bin        // O(1)
            bin_rem = c - weight[i];        // O(1)
        } else {
            bin_rem -= weight[i];
        }
    }
    return res;
}

// Time Complexity: O(n *O(1 *O(1)*O(1))) = O(n)
// Space Complexity: No additional memory usage, hence space O(1)


//------------------firstFit
int firstFit(int weight[], int n, int c){

    // Initialize resuft (Count of bins)
    int res = 0;                                            // O(1)

    // Create an array to store remaining space in bins
    // there can be at most n bins
    int bin_rem[n];                                         // O(1)

    // Place items one by one
    for(int i=0; i < n; i++){                               // O(n)
        // Find the first bin that can accommodate
        // weight[i]
        int j;                                              // O(1)
        for(j=0; j < res; j++){                               
            if(bin_rem[j] >= weight[i]){                    // O(1)
                bin_rem[j] = bin_rem[j] - weight[i];        // O(1)
                break;
            }
        }

        // If no bin could accommodate weight[i]
        if (j == res){
            bin_rem[res] = c - weight[i];
            res++;
        }
    }
    return res;
}

// Time Complexity: O(1)*O(1)*O(n *O(1)) = O(n)
// Space Complexity: No additional memory usage, hence space O(1)

//------------------bestFit
int bestFit(int weight[], int n, int c){
    
    // Initialize result (Count of bins)
    int res = 0;                                                                    // O(1)

    // Create an array to store
    // remaining space in bins
    // there can be at most n bins
    int bin_rem[n];                                                                 // O(1)        

    // Place items one by one
    for (int i = 0; i < n; i++){                                                    // O(n)
        // Find the best bin that can accommodate
        // weight[i]
        int j;                                                                      // O(1)

        // Initialize minimum space left and index
        // of best bin
        int min = c + 1, bi = 0;                                                    // O(1)

        for (j=0; j < res; j++){
            if (bin_rem[j] >= weight[i] && bin_rem[j] - weight[i] < min){           // O(1)
                bi = j;                                                             // O(1)
                min = bin_rem[j] - weight[i];                                       // O(1)
            }
        }

        // If no bin could accommodate weight[i],
        // create a new bin
        if (min == c + 1){                                                          // O(1) 
            bin_rem[res] = c - weight[i];                                           // O(1)
            res++;                                                                  // O(1)
        } else
            bin_rem[i] -= weight[i];
    }
    return res;                                                                     // O(1)
}

// Time Complexity: O(1) + O(n) * O(1) = O(n)
// Space Complexity: No additional memory usage, hence space O(1)


//------------------worstFit
int worstFit(int weight[], int n, int c){
    // Initialize resuft (Count of bins)
    int res = 0;                                                                    // O(1)

    // Create an array to store remaining space in bins
    // there can be at most n bins
    int bin_rem[n];                                                                 // O(1)

    // Place items one by one
    for (int i = 0; i < n; i++){                                                    // O(n)
        // Find the best bin that can accommodate
        // weight[i]
        int j;                                                                      // O(1)

        // Initialize maximum space left and index
        // of worst bin
        int mx = -1, wi = 0;                                                        // O(1)

        for (j = 0; j < res; j++){                                                
            if (bin_rem[j] >= weight[i] && bin_rem[j] - weight[i] > mx){            // O(1)
                wi = j;                                                             // O(1)
                mx = bin_rem[j] - weight[i];                                        // O(1)
            }
        }

        // If no bin could accommodate weight[i],
        // create a new bin
        if (mx == -1){                                                              // O(1)
            bin_rem[res] = c - weight[i];
            res++;
        } else // Assign the item to best bin
             bin_rem[wi] -= weight[i];                                              // O(1)
    }
    return res;                                                                     // O(1)
}

// Time Complexity: O(1) + O(n) * O(1) = O(n)
// Space Complexity: No additional memory usage, hence space O(1)


// Driver program
int main(){
    int weight[] = {2, 5, 4, 7, 1, 3 , 8};
    int c = 10;
    int n = sizeof(weight) / sizeof(weight[0]); 
    cout << "Number of bins required in Next Fit: " << nextFit(weight, n, c) << "\n";
    cout << "Number of bins required in First Fit: " << firstFit(weight, n, c) << "\n";
    cout << "Number of bins required in Best Fit: " << bestFit(weight, n, c) << "\n";
    cout << "Number of bins required in Worst Fit: " << worstFit(weight, n, c) << "\n";
    return 0;
}