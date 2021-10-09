//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-11;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

int sgn(int x) {
  return x<0 ? -1 : x>0 ? 1 : 0;
}
int sqr(int x) {
  return x*x;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(0);

  int n;
  cin >> n;
  vector<int> x(n), y(n);
  map<tuple<int,int,int>,vector<int>> line;
  for(int i=0; i<n; i++) {
    cin >> x[i] >> y[i];
    for(int j=0; j<i; j++) {
      int a = y[i] - y[j];
      int b = x[i] - x[j];
      int c = y[i]*(x[i]-x[j]) - x[i]*(y[i]-y[j]);
      int g = abs(__gcd(__gcd(a, b), c)) * (sgn(a) ? sgn(a) : sgn(b));
      line[make_tuple(a/g, b/g, c/g)].push_back(i);
      line[make_tuple(a/g, b/g, c/g)].push_back(j);
    }
  }

  ld ans = 0;
  for(const auto& [_, v] : line) {
    pair<int,int> minv(INF,INF), maxv(-INF,-INF);
    for(int i : v) {
      minv = min(minv, make_pair(x[i], y[i]));
      maxv = max(maxv, make_pair(x[i], y[i]));
    }
    ans += sqrt(sqr(minv.first-maxv.first) + sqr(minv.second-maxv.second));
  }
  cout << ans << nl;

  return 0;
}
