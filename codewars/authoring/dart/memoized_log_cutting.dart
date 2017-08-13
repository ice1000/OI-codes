import 'dart:math';

// Your new function as given to you by me, your boss.
Function cutLog = (List p, int n) {
  if (n == 0) return 0;
// Some array to store calculated values
  var resultTable = new List(n + 1);
  for (int i = 0; i <= n; i++) resultTable[i] = 0;
// try all lengths up to 'n'
  for (int j = 1; j <= n; j++) {
//try to cut out one piece along the price table
//and calculate the price as sum of this piece plus the price of 'the rest'
    for (int k = 1; k <= j; k++) {
      // Two nested loops = Θ(n^2)
// no magic: since we start at length 0,
// we will already have calculated the price of 'the rest' in our resultTable
      resultTable[j] = max(resultTable[j], p[k] + resultTable[j - k]);
    }
  }
  return resultTable[n]; // Good luck intern!
};

