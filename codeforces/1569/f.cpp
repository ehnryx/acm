#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';

using ll = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m, k;
  cin >> n >> m >> k;

  vector adj(n, vector<bool>(n));

  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    a -= 1;
    b -= 1;
    adj[a][b] = adj[b][a] = true;
  }

  vector pcnt(1<<(n/2), vector<bool>(n));
  for(int bm=0; bm<1<<n; bm++) {
    if(__builtin_popcount(bm) != n/2) continue;
    vector<int> half;
    for(int i=0; i<n; i++) {
      if(bm & 1<<i) {
        half.push_back(i);
      }
    }
    do {
      bool ok = true;
      for(int i=1; i<n/2; i++) {
        ok &= adj[half[i]][half[i-1]];
      }
      pcnt[bm][half[0]] += ok;
    } while(next_permutation(begin(half), end(half)));
  }

  int mask = (1<<n) - 1;
  for(int bm=0; bm<1<<(n-1); bm++) {
    if(__builtin_popcount(bm) != n/2) continue;
    for(int i=0; i<n; i++) {
      if(!(bm & 1<<i)) continue;
      if(!pcnt[bm][i]) continue;
      for(int j=0; j<n; j++) {
        if(bm & 1<<j) continue;
        if(!pcnt[mask ^ bm][j]) continue;
        if(!adj[i][j]) continue;

      }
    }
  }

  return 0;
}
