#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void knapsack(int capacity, const vector<int>& weights, const vector<int>& values, int itemCount) {
    vector<vector<int>> dp(itemCount + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= itemCount; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    cout << "The maximum value obtainable: " << dp[itemCount][capacity] << endl;
    cout << "Items included in the knapsack:\n";

    int w = capacity;
    int maxProfit = dp[itemCount][capacity];
    for (int i = itemCount; i > 0 && maxProfit > 0; i--) {
        if (maxProfit != dp[i - 1][w]) {
            cout << "Item " << i << " (Weight: " << weights[i - 1] << ", Value: " << values[i - 1] << ")\n";
            maxProfit -= values[i - 1];
            w -= weights[i - 1];
        }
    }
}

int main() {
    int itemCount, capacity;
    cout << "Enter the number of items: ";
    cin >> itemCount;
    cout << "Enter the capacity of the knapsack: ";
    cin >> capacity;

    vector<int> weights(itemCount), values(itemCount);
    for (int i = 0; i < itemCount; i++) {
        cout << "Enter weight and value for item " << i + 1 << " (weight value): ";
        cin >> weights[i] >> values[i];
    }

    knapsack(capacity, weights, values, itemCount);
    return 0;
}

