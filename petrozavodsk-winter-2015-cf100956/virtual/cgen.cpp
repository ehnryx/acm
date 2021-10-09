#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;
const ll MOD = 1000000000000000000LL;

mt19937_64 rng;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n=5000;
  int m=5000;
  cout << n << " " << m << nl;
  for (int i=0; i<n; i++) {
    if (i>0) cout << " ";
    cout << rng()%MOD + 1;
  }
  cout << nl;
  for (int i=0; i<m; i++) {
    if (i>0) cout << " ";
    cout << rng()%MOD + 1;
  }
  cout << nl;

  int k=50;
  cout << k << nl;
  for (int i=0; i<k; i++) {
    cout << rng()%(MOD-1) + 2 << nl;
  }

  return 0;
}
