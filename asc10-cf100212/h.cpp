#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "tilings"

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

const int N = 50;

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  vector<pair<int,int>> v;
  int maxx = -INF;
  int minx = INF;
  int maxy = -INF;
  int miny = INF;
  for(int i=0; i<N; i++) {
    string s;
    if(cin >> s) {
      for(int j=0; j<s.size(); j++) {
        if(s[j] == '*') {
          v.emplace_back(i, j);
          maxx = max(maxx, i);
          minx = min(minx, i);
          maxy = max(maxy, j);
          miny = min(miny, j);
        }
      }
    }
  }

  int dx = maxx - minx + 1;
  int dy = maxy - miny + 1;
  for(int s=0; s<=dx; s++) {
    for(int t=0; t<=dy; t++) {
      for(int x=-dx; x<=dx; x++) {
        for(int y=-dy; y<=dy; y++) {
          if(abs(s*y - t*x) != v.size()) continue;
          set<pair<int,int>> have;
          bool ok = true;
          for(auto [i, j] : v) {
            ok &= have.insert(make_pair(i, j)).second;
            ok &= have.insert(make_pair(i+s, j+t)).second;
            ok &= have.insert(make_pair(i+x, j+y)).second;
            ok &= have.insert(make_pair(i+s+x, j+t+y)).second;
            if(!ok) break;
          }
          if(ok) {
            cout << "YES" << nl;
            return 0;
          }
        }
      }
    }
  }

  cout << "NO" << nl;

	return 0;
}
