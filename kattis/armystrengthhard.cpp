#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0);
  int T; cin >> T;
  while (T--) {
    int g, m, maxg, maxm, temp;
    cin >> g >> m;
    maxg = maxm = 0;
    while (g--) {
      cin >> temp;
      if (temp > maxg) {
        maxg = temp;
      }
    }
    while (m--) {
      cin >> temp;
      if (temp > maxm) {
        maxm = temp;
      }
    }
    if (maxg >= maxm) {
      cout << "Godzilla" << endl;
    } else {
      cout << "MechaGodzilla" << endl;
    }
  }
  return 0;
}
