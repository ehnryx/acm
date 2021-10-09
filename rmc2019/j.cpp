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

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 20;
const int M = 400 + 1;
int all[M];
int cnt[N][N];
int dp[1<<N];
int solve(int bm, int n) {
  if(bm == 0) return 0;
  if(dp[bm] != -1) return dp[bm];
  memset(cnt, 0, sizeof cnt);
  int pre = -1;
  for(int i=0; i<n; i++) {
    if(!(bm & 1<<all[i])) continue;
    if(pre != -1) {
      cnt[pre][all[i]] += 1;
    }
    pre = all[i];
  }
  vector<int> sk(N);
  for(int i=0; i<N; i++) {
    if(!(bm & 1<<i)) continue;
    sk[i] = (i == pre ? 1 : 0);
    for(int j=0; j<N; j++) {
      if(!(bm & 1<<j) || i==j) continue;
      sk[i] += cnt[i][j];
    }
  }
  int res = INF;
  for(int i=0; i<N; i++) {
    if(!(bm & 1<<i)) continue;
    res = min(res, sk[i] + solve(bm ^ 1<<i, n));
  }
  return dp[bm] = res;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;
  string s;
  cin >> s;
  unordered_map<char,int> idx;
  int id = 0;
  transform(s.begin(), s.end(), all, [&] (char c) {
    if(!idx.count(c)) idx[c] = id++;
    return idx[c];
  });
  memset(dp, -1, sizeof dp);
  cout << solve((1<<m)-1, n) << nl;

  return 0;
}
