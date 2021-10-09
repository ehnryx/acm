#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';
typedef long long ll;
typedef long double ld;



int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int v, x, m;
  cin >> v >> x >> m;
  int bestp = m;
  int bestq = -1;
  for(int i=1; i<m; i++) {
    int j = (ll)v*i % m;
    if((ll)x*i <= j && j < (ll)(x+1)*i) {
      if(j < bestp) {
        bestp = j;
        bestq = i;
      }
    }
  }

  if(bestq == -1) {
    cout << -1 << nl;
  } else {
    cout << bestp << " " << bestq << nl;
  }

  return 0;
}
