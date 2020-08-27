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

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  os << "[";
  for(int it : v) {
    os << " " << it << ", ";
  }
  return os << "]";
}

const int N = 2e3 + 1;
int adj[N][N];

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

  int n, k;
  cin >> n >> k;
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      cin >> adj[i][j];
    }
  }

  vector<int> out(k);
  vector<bool> bad(n);
  for(int i=0; i<k; i++) {
    cin >> out[i];
    bad[out[i]] = true;
  }

  vector<pair<int,int>> order, other;
  for(int i=0; i<n; i++) {
    if(bad[i]) {
      int cnt = 0;
      for(int j=0; j<n; j++) {
        if(bad[j]) {
          cnt += adj[j][i];
        }
      }
      other.emplace_back(cnt, i);
    } else {
      int cnt = 0;
      for(int j=0; j<n; j++) {
        if(bad[j]) continue;
        cnt += adj[j][i];
      }
      order.emplace_back(cnt, i);
    }
  }
  sort(order.begin(), order.end());
  sort(other.begin(), other.end());

  vector<int> path, need;
  transform(order.begin(), order.end(), back_inserter(path), [](auto v) {
    return v.second;
  });
  transform(other.begin(), other.end(), back_inserter(need), [](auto v) {
    return v.second;
  });

  for(int i=0; i<need.size(); i++) {
    for(int j=0; j<i; j++) {
      if(adj[need[i]][need[j]]) {
        cout << "impossible" << nl;
        return 0;
      }
    }
  }

  vector<int> allowed(path.size(), -1);
  for(int i=0; i<path.size(); i++) {
    int put = -1;
    bool ok = true;
    for(int j=1; j<need.size(); j++) {
      if(adj[path[i]][need[j]] && adj[need[j-1]][path[i]]) {
        put = j;
      } else if(adj[need[j]][path[i]] && adj[path[i]][need[j-1]]) {
        ok = false;
      }
    }
    if(adj[path[i]][need.front()]) {
      put = 0;
    }
    if(adj[need.back()][path[i]]) {
      put = need.size();
    }
    if(put != -1 && ok) {
      allowed[i] = put;
    }
  }

  vector<vector<int>> dp(path.size() + 1, vector<int>(need.size() + 1, -INF));
  dp[0][0] = 0;
  for(int i=0; i<=path.size(); i++) {
    for(int j=0; j<=need.size(); j++) {
      if(i) {
        // skip
        dp[i][j] = max(dp[i][j], dp[i-1][j]);
        // put
        if(allowed[i-1] == j) {
          dp[i][j] = max(dp[i][j], dp[i-1][j] + 1);
        }
      }
      if(j) {
        // put
        dp[i][j] = max(dp[i][j], dp[i][j-1] + 1);
      }
    }
  }

  int ans = n - dp[path.size()][need.size()];
  if(ans < k) {
    cout << ans << nl;
  } else {
    cout << "impossible" << nl;
  }

  return 0;
}
