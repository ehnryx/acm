//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

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

const int N = 1 << 19;
int st[2*N];

void insert(int i, int v) {
  st[i+=N] = v;
  for(i/=2; i; i/=2) {
    st[i] = min(st[2*i], st[2*i+1]);
  }
}

int query(int l, int r, int v, int i=1, int s=0, int e=N-1) {
  if(r<s || e<l || st[i] >= v) return 0;
  if(s == e) return s;
  int m = (s+e) / 2;
  int x = query(l, r, v, 2*i, s, m);
  if(x) return x;
  else return query(l, r, v, 2*i+1, m+1, e);
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  memset(st, 0x3f, sizeof st);

  int n;
  cin >> n;
  vector<int> a(n+1);
  vector<vector<int>> idx(n+1);
  vector<set<int>> all(n+1);
  for(int i=1; i<=n; i++) {
    cin >> a[i];
    idx[a[i]].push_back(i);
    all[i].insert(INF);
  }

  vector<tuple<int,int,int>> segs;
  for(int i=1; i<=n; i++) {
    if(idx[i].size() <= 1) continue;
    for(int j=0; j<idx[i].size(); j++) {
      if(j > 0) {
        segs.emplace_back(idx[i].front(), idx[i][j], 1);
        segs.emplace_back(idx[i][j], idx[i].front(), -1);
      }
      if(j+1 < idx[i].size()) {
        segs.emplace_back(idx[i][j], idx[i].back(), 0);
      }
    }
  }
  sort(segs.begin(), segs.end());

  pair<int,int> ans(INF, INF);
  for(auto [l, r, t] : segs) {
    assert(a[l] == a[r]);
    if(t == 1) {
      all[a[r]].insert(r);
      insert(a[r], *all[a[r]].begin());
    } else if(t == -1) {
      all[a[r]].erase(l);
      insert(a[r], *all[a[r]].begin());
    } else {
      int x;
      if(a[r] > 1 && (x = query(1, a[r]-1, r))) {
        ans = min(ans, pair(x, a[r]));
      } else if(a[r] < n && (x = query(a[r]+1, n, r))) {
        ans = min(ans, pair(x, a[r]));
      }
    }
  }

  if(ans.first == INF) {
    cout << -1 << nl;
  } else {
    cout << ans.first << " " << ans.second << nl;
  }

  return 0;
}
