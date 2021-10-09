#include <bits/stdc++.h>
using namespace std;

bitset<201> prime;
bitset<201> notp;
int win[201];

void init() {
  notp[0] = notp[1] = true;
  for (int i = 2; i < 15; i++) {
    if (!notp[i])
      for (int j = i*i; j <= 200; j+=i)
        notp[j] = true;
  }
  for (int i = 0; i <= 200; i++) {
    if (!notp[i])
      prime[i] = true;
  }
}

int solve(int i) {
  if (win[i] != -1) return win[i];
  for (int j = 1; j <= (i+1)/2; j++) {
    if (prime[j]) {
      for (int k = 0; k < i-j; k++) {
        if (!solve(k) && !solve(i-j-k))
          return win[i] = true;
      }
    }
  }
  return win[i] = false;
}

int main() {
  init();
  memset(win, -1, sizeof(win));
  win[0] = false;
  win[1] = true;
  for (int i = 0; i <= 200; i++) {
    cout << i << ": " << solve(i) << endl;
  }
  return 0;
}
