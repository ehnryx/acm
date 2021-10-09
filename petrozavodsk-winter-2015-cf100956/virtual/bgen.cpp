#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;

const int C = 2e9+1;
const int O = 1e9;

mt19937 rng;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n = 1e5;
  cout << n << nl;
  for (int i=0; i<n; i++) {
    cout << ((int)rng()%C - O) << " " << ((int)rng()%C - O) << nl;
  }

  return 0;
}
