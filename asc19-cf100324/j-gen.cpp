//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME sadcactussociety

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

const int N = 16;
int dsu[N];
int find(int i) {
  if(dsu[i] == -1) return i;
  return dsu[i] = find(dsu[i]);
}
int link(int i, int j) {
  i = find(i);
  j = find(j);
  if(i == j) return 0;
  dsu[i] = j;
  return 1;
}

int get_groups(int n, int bm) {
  int cnt = 0;
  stack<int> s;
  for(int i=0; i<n; i++) {
    if(bm & 1<<i) {
      s.push(i);
    } else if(s.empty()) {
      return INF;
    } else {
      cnt += link(s.top(), i);
      s.pop();
    }
  }
  return cnt;
}

int outer(int n, int bm) {
  int cnt = 0;
  int s = 0;
  for(int i=0; i<n; i++) {
    if(bm & 1<<i) {
      cnt += (s == 0);
      s++;
    } else {
      s--;
    }
  }
  return cnt;
}

ll solve(int n) {
  ll ans = 0;
  int half = (n+1) / 2;
  for(int bm=0; bm<1<<n; bm++) {
    if(__builtin_popcount(bm) != half) continue;
    for(int om=0; om<1<<n; om++) {
      if(__builtin_popcount(om) != half) continue;
      memset(dsu, -1, sizeof dsu);
      int groups = n;
      groups -= get_groups(n, bm);
      groups -= get_groups(n, om);
      if(groups != 1) continue;
      if(n % 2) {
        ans++;
      } else {
        ans += outer(n, om);
      }
    }
  }
  return ans * (n % 2 ? 2 : 4);
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
  for(int i=1; i<=n; i++) {
    cout << "dp[" << i << "] = " << solve(i) << ";" << nl;
  }

  return 0;
}
