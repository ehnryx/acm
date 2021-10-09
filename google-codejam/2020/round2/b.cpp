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

const int BIG = 1e6;

const int N = 100 + 1;
vector<int> adj[N];
int val[N];
int par[N];
int dist[N];

const int M = 1e3 + 1;
int ans[M];

void casesolve() {

  int n, m;
  cin >> n >> m;
  vector<int> values;
  adj[1].clear();
  for(int i=2; i<=n; i++) {
    cin >> val[i];
    adj[i].clear();
    if(val[i] < 0) {
      values.push_back(-val[i]);
    }
  }
  sort(values.begin(), values.end());
  values.resize(unique(values.begin(), values.end()) - values.begin());
  values.push_back(INF);

  map<pair<int,int>,int> eid;
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
    eid[make_pair(a, b)] = i;
    eid[make_pair(b, a)] = i;
  }
  fill(ans, ans+m, BIG);

  memset(par, 0, sizeof par);
  int fcnt = 0;
  for(int v : adj[1]) {
    par[v] = 1;
    fcnt++;
  }
  par[1] = -1;

  for(int t=0, cur=1; fcnt>0; ) {
    vector<int> add, other;
    int minv = INF;
    for(int i=1; i<=n; i++) {
      if(par[i] <= 0) continue;
      if(val[i] < 0) {
        if(-val[i] == cur) {
          add.push_back(i);
        }
      } else {
        if(val[i] < minv) {
          other.clear();
          minv = val[i];
        }
        if(val[i] == minv) {
          other.push_back(i);
        }
      }
    }
    assert(t <= minv);

    if(!add.empty()) {
      ++t;
      cur += add.size();
      fcnt -= add.size();
      for(int i : add) {
        ans[eid[make_pair(i, par[i])]] = t - dist[par[i]];
        dist[i] = t;
        par[i] = -1;
        for(int j : adj[i]) {
          if(!par[j]) {
            par[j] = i;
            fcnt++;
          }
        }
      }
    }

    else {
      cur += other.size();
      fcnt -= other.size();
      for(int i : other) {
        ans[eid[make_pair(i, par[i])]] = minv - dist[par[i]];
        dist[i] = minv;
        par[i] = -1;
        for(int j : adj[i]) {
          if(!par[j]) {
            par[j] = i;
            fcnt++;
          }
        }
      }
      t = minv;
    }
  }

  for(int i=0; i<m; i++) {
    cout << ans[i] << " ";
  }
  cout << nl;

  return;
}

