#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../lca/data_structure/splay_tree.h"

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

using node = splay_node<ll, void>;

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int k;
  cin >> k;

  vector<int> factors;
  int lim = sqrt(k);
  for (int i = 1; i <= lim; i++) {
    if (k % i == 0) {
      factors.push_back(i);
      if (i*i != k) factors.push_back(k/i);
    }
  }

  splay_tree<node> fsqr;
  int n = factors.size();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= i; j++) {
      fsqr.insert_if_none((ll)factors[i]*factors[j]);
    }
  }

  ll v = (ll)k*k;
  cout << fsqr.size() << nl;
  for (ll f : fsqr) {
    cout << f+k << " " << v/f+k << nl;
  }

  return 0;
}
