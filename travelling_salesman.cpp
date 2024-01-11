#include <climits>
#include <iostream>
#include <vector>
using namespace std;

// Function to solve the Travelling Salesman Problem using dynamic programming
// dist: A 2D vector representing distances between cities
// startingCity: The city from which the salesman starts the journey
// numberOfCities: Total number of cities in the problem
// dp: A 2D vector used for memoization to store minimum distances
void travellingSalesman(vector<vector<int>> dist, int startingCity, int numberOfCities, vector<vector<int>>& dp) {
    // Iterate through all subsets of cities
    for (int setOfCities = 1; setOfCities < (1 << numberOfCities); setOfCities++) {
        // Iterate through all cities for current subset
        for (int choice = 0; choice < numberOfCities; choice++) {
            // Check if the current city is in the subset
            if ((setOfCities & (1 << choice)) > 0) {
                int prev = (setOfCities - (1 << choice));
                // Base case: If previous set is empty, set distance from the starting city
                if (prev == 0)
                    dp[setOfCities][choice] = dist[choice][startingCity];
                else {
                    // Calculate minimum distance for current subset and city
                    for (int city = 0; city < numberOfCities; city++) {
                        if (dp[prev][city] != INT_MAX) {
                            dp[setOfCities][choice] = min(dp[setOfCities][choice], dp[prev][city] + dist[city][choice]);
                        }
                    }
                }
            }
        }
    }
}

int main() {
    // Initialize the distance matrix for the cities
    vector<vector<int>> dist = {{0, 20, 42, 25},
                                {20, 0, 30, 34},
                                {42, 30, 0, 10},
                                {25, 34, 10, 0}};
    // Initialize the dynamic programming table with max value
    vector<vector<int>> dp(1 << 4, vector<int>(4, INT_MAX));

    // Call the function to solve the problem
    travellingSalesman(dist, 0, 4, dp);

    // Output the minimum distance to traverse all cities and return to the starting city
    cout << dp[(1 << 4) - 1][0] << endl;

    return 0;
}
