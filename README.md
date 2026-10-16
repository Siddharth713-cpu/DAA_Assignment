# DAA Assignment - 0/1 Knapsack

C++ implementation of the **0/1 Knapsack using Dynamic Programming**.

## Features
- Reads multiple test cases separated by `#Test`.
- Reads `n W`, followed by `n` lines of `weight value`.
- Computes the maximum total value using 0/1 Knapsack DP.
- Shows a live ASCII visualization of the DP table row-by-row.
- Saves every answer in `result.txt` in the required format.

## Compile
```bash
g++ -std=c++17 knapsack.cpp -o knapsack
```

## Run
```bash
./knapsack "Knapsack data (2).txt"
```
For instant execution without animation:
```bash
./knapsack "Knapsack data (2).txt" --fast
```

## DP recurrence
`dp[i][w] = dp[i-1][w]` if item `i` is not selected.

If `weight[i-1] <= w`:
`dp[i][w] = max(dp[i-1][w], value[i-1] + dp[i-1][w-weight[i-1]])`.

Time complexity: **O(nW)** per test case.  
Space complexity: **O(nW)**.
