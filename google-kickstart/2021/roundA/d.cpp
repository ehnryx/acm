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
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  return os << '(' << v.first << ',' << v.second << ')';
}
template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  for (const T& it : v) { os << it << " "; } return os;
}
template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ "; for (const T& it : v) { os << it << " "; }
  return os << '}';
}
template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ "; for (const pair<T,U>& it : v) { os << it << " "; }
  return os << '}';
}

void casesolve();

////////////////////////////////////////////////////////////////////////



int main(int argc, char** argv) {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin >> T;
  for (int cc = 1; cc <= T; cc++) {
    cout << "Case #" << cc << ": ";
    casesolve();
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////



void casesolve() {

  int n;
  cin >> n;
  vector grid(n, vector<int>(n));
  vector cost(n, vector<int>(n));
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      cin >> grid[i][j];
    }
  }
  ll total = 0;
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      cin >> cost[i][j];
      total += cost[i][j];
    }
  }
  for(int i=0, _; i<2*n; i++) {
    cin >> _;
  }

  // maximum spanning tree ?
  vector<tuple<int,int,int>> edges;
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      if(grid[i][j] == -1) {
        edges.emplace_back(cost[i][j], i, j);
      }
    }
  }
  sort(edges.begin(), edges.end(), greater<tuple<int,int,int>>());

  vector<int> dsu(n*n, -1);
  function<int(int)> find = [&](int i) {
    if(dsu[i] == -1) return i;
    return dsu[i] = find(dsu[i]);
  };
  function<void(int,int)> link = [&](int i, int j) {
    if(find(i) != find(j)) {
      dsu[find(i)] = find(j);
    }
  };

  vector have(n, vector<bool>(n));
  for(auto [_, i, j] : edges) {
    int h = -1;
    int v = -1;
    for(int k=0; k<n; k++) {
      if(have[k][j]) {
        h = find(k*n + j);
      }
      if(have[i][k]) {
        v = find(i*n + k);
      }
    }
    if(h != -1 && h == v) continue;
    have[i][j] = true;
    total -= cost[i][j];
    if(h != -1) link(h, i*n + j);
    if(v != -1) link(v, i*n + j);
  }
  cout << total << nl;

  return;
}

