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

vector<bitset<N>> read_mat(int n) {
  vector<bitset<N>> a(n);
  for(int i=0; i<n; i++) {
    string s;
    cin >> s;
    for(int j=0; j<n; j++) {
      a[i][j] = to_num(s[j/4]) >> (3-j+j/4*4) & 1;
    }
  }
  return a;
}

bitset<N> operator * (const vector<bitset<N>>& a, const bitset<N>& v) {
  bitset<N> res;
  for(int i=0; i<a.size(); i++) {
    res[i] = (a[i] & v).count() % 2;
  }
  return res;
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

  uniform_int_distribution<int> paul(0, 1);

  int n;
  cin >> n;
  vector<bitset<N>> a = read_mat(n);
  vector<bitset<N>> b = read_mat(n);
  vector<bitset<N>> c = read_mat(n);

  bool ok = true;
  for(int bs=0; bs<99; bs++) {
    bitset<N> v;
    for(int i=0; i<N; i++) {
      v[i] = paul(rng);
    }
    ok &= (a * (b * v) == c * v);
  }

  if(ok) {
    cout << "YES" << nl;
  } else {
    cout << "NO" << nl;
  }

  return 0;
}

// 4
