//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "genus"

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

tuple<int,int,int> read_point() {
  int x, y, z;
  cin >> x >> y >> z;
  return make_tuple(x, y, z);
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
  set<tuple<int,int,int>> V;
  set<tuple<int,int,int,int,int,int>> E;
  for(int i=0; i<n; i++) {
    tuple<int,int,int> a = read_point();
    tuple<int,int,int> b = read_point();
    tuple<int,int,int> c = read_point();
    V.insert(a);
    V.insert(b);
    V.insert(c);
    E.insert(tuple_cat(min(a, b), max(a, b)));
    E.insert(tuple_cat(min(b, c), max(b, c)));
    E.insert(tuple_cat(min(c, a), max(c, a)));
  }
  int euler = (int)V.size() + n - (int)E.size();
  cout << 1 - euler/2 << nl;

  return 0;
}
