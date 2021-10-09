//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "unfair"

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

const int N = 20;
ll I[N], A[N], L[N], O[N]; // j
ll T[N], Z[N], V[N], C[N]; // i

int solve(const vector<int> v, int t, int l) {
  vector<tuple<ll,ll,int>> rank;
  for(int i=0; i<t; i++) {
    vector<pair<ll,ll>> can;
    for(int j : v) {
      if(T[i] + C[i] > I[j] - O[j]) {
        ll expected = (I[j] + O[j]-1) / O[j] + max((A[j] + C[i]-1) / C[i], (ll)5);
        ll actual = max(I[j] - T[i], (ll)0) + (A[j] + (Z[i]+C[i]-1)) / (Z[i]+C[i])
          + (L[j] + V[i]-1) / V[i];
        can.emplace_back(expected, actual);
      }
    }
    sort(can.begin(), can.end());

    ll cur = 0;
    ll cnt = 0;
    ll pen = 0;
    for(auto [_, len] : can) {
      if(cur + len > l) break;
      cur += len;
      cnt++;
      pen += cur;
    }
    rank.emplace_back(-cnt, pen, i);
  }

  sort(rank.begin(), rank.end());
  for(int i=0; i<t; i++) {
    if(get<2>(rank[i]) == 0) {
      return i;
    }
  }
  assert(false);
}

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

  int m, n, t, l;
  cin >> m >> n >> t >> l;
  for(int i=0; i<m; i++) {
    cin >> I[i] >> A[i] >> L[i] >> O[i];
  }
  for(int i=0; i<t; i++) {
    cin >> T[i] >> Z[i] >> V[i] >> C[i];
  }

  int rank = INF;
  vector<int> ans;
  for(int bm=0; bm<1<<m; bm++) {
    if(__builtin_popcount(bm) == n) {
      vector<int> v;
      for(int i=0; i<m; i++) {
        if(bm & 1<<i) {
          v.push_back(i);
        }
      }
      int cur = solve(v, t, l);
      if(cur < rank) {
        rank = cur;
        ans = move(v);
      }
    }
  }

  for(int it : ans) {
    cout << it + 1 << " ";
  }
  cout << nl;

  return 0;
}
