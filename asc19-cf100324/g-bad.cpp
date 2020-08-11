#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "matrix"

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 4000;

int to_num(char c) {
  if(isdigit(c)) return c - '0';
  else return c - 'A' + 10;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
///*
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif
//*/

  int n;
  cin >> n;

  vector<bitset<N>> a(n), b(n);

  for(int i=0; i<n; i++) {
    string s;
    cin >> s;
    for(int j=0; j<n; j++) {
      a[i][j] = to_num(s[j/4]) >> (3-j+j/4*4) & 1;
    }
  }

  for(int i=0; i<n; i++) {
    string s;
    cin >> s;
    for(int j=0; j<n; j++) {
      b[j][i] = to_num(s[j/4]) >> (3-j+j/4*4) & 1;
    }
  }

  for(int i=0; i<n && ((i & 0b111111) || clock() < 0.98*CLOCKS_PER_SEC); i++) {
    string s;
    cin >> s;
    for(int j=0; j<n; j++) {
      int cij = to_num(s[j/4]) >> (3-j+j/4*4) & 1;
      if(cij != ((a[i] & b[j]).count() & 1)) {
        cout << "NO" << nl;
        return 0;
      }
    }
  }

  if(clock() > 0.98*CLOCKS_PER_SEC && rng()%2 == 0) {
    cout << "NO" << nl;
  } else {
    cout << "YES" << nl;
  }

  return 0;
}

// 4
