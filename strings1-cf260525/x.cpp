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
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<int> vi;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

// get_sarray()[i] = idx of suffix s[i..L-1] in list of sorted suffixes
struct suff_array {
  const int L; int skip, lvl;
  vector<vi> P; vector<pair<pii,int>> M;
  suff_array(const string &s) : L(s.size()), P(1, vi(L, 0)), M(L) {
    for (int i = 0; i < L-(L==1); i++) P[0][i] = int(s[i]);
    for (skip = 1, lvl = 1; skip < L; skip *= 2, lvl++) {
      P.push_back(vi(L, 0));
      for (int i = 0; i < L; i++)
        M[i] = {{P[lvl-1][i], i+skip<L ? P[lvl-1][i + skip] : -1000}, i};
      sort(M.begin(), M.end());
      for (int i = 0; i < L; i++)
        P[lvl][M[i].second] = (i > 0 && M[i].first == M[i-1].first) ?
            P[lvl][M[i-1].second] : i; } }
  const vi& get_sarray() { return P.back(); }
  //returns len of longest common prefix of s[i...L-1] and s[j...L-1], O(lg L)
  int lcp(int i, int j) {
    int len = 0; if (i == j) return L - i;
    for (int k = P.size() - 1; k >= 0 && i < L && j < L; k--)
      if (P[k][i] == P[k][j]) { i += 1 << k; j += 1 << k; len += 1 << k; }
    return len; }
}; //! code adapted from the Stanford Team Notebook

const int N = 2e3+2;
int lhook[N][2][N], rhook[N][2][N];
ll dp[N][2][N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  string g[2], grev[2];
  for(int i=0;i<2;i++) {
    cin >> g[i];
    grev[i] = g[i];
    reverse(grev[i].begin(), grev[i].end());
  }
  string grid = g[0] + g[1] + grev[0] + grev[1];

  string s;
  cin >> s;

  if(s.size() == 1) {
    int ans = 0;
    for(int i=0;i<2;i++) {
      for(char c:g[i]) {
        ans += (c == s[0]);
      }
    }
    cout << ans << nl;
    return 0;
  }

  if(s.size() == 2) {
    int ans = 0;
    for(int i=0;i<2;i++) {
      for(int j=0;j<g[i].size();j++) {
        if(g[i][j] != s[0]) continue;
        ans += (j>0 && g[i][j-1] == s[1]);
        ans += (j+1<g[i].size() && g[i][j+1] == s[1]);
        ans += (g[i^1][j] == s[1]);
      }
    }
    cout << ans << nl;
    return 0;
  }

  string srev = s;
  reverse(srev.begin(), srev.end());

  int n = g[0].size();
  assert(g[0].size() == g[1].size());
  int m = s.size();

  auto get_id = [&] (int i, int t) {
    --i;
    if(t == 0) return i;
    else return n + i;
  };
  auto get_rev = [&] (int i, int t) {
    --i;
    if(t == 0) return 2*n + (n-1) - i;
    else return 3*n + (n-1) - i;
  };
  auto get_str = [&] (int i) {
    return 4*n + i;
  };

  ll ans = 0;
  ll hook = 0;
  for(const string& it: {s, srev}) {
    //cerr<<"solving "<<it<<nl;
    memset(lhook, 0, sizeof lhook);
    memset(rhook, 0, sizeof rhook);
    memset(dp, 0, sizeof dp);
    suff_array sa(grid + it);

    for(int i=0; i<=n+1; i++) {
      for(int t=0; t<2; t++) {
        lhook[i][t][0] = 1;
        rhook[i][t][0] = 1;
        if(i<1 || i>n) continue;
        for(int j=2; j<=n && 2*j<=m; j++) {
          if(i+j-1 <= n && sa.lcp(get_id(i,t), get_str(m-2*j)) >= j
              && sa.lcp(get_rev(i+j-1,t^1), get_str(m-j)) >= j) {
            rhook[i][t][2*j] = 1;
            //cerr<<"rook " << i << " " << t << " " << 2*j << nl;
          }
          //cerr<<"trying "<<i-j+1<<" "<<t<<" = "<<j<<" and "<<i<<" "<<(t^1)<<" = " << 0 << nl;
          if(i-j+1 >= 1 && sa.lcp(get_id(i-j+1,t), get_str(j)) >= j
              && sa.lcp(get_rev(i,t^1), get_str(0)) >= j) {
            lhook[i][t][2*j] = 1;
            //cerr<<"look " << i << " " << t << " " << 2*j << nl;
          }
        }
      }
    }

    for(int i=1;i<=n;i++) {
      for(int t=0;t<2;t++) {
        for(int j=1;j<=m;j++) {
          if(it[j-1] != g[t][i-1]) continue;
          dp[i][t][j] += dp[i-1][t][j-1];
          dp[i][t][j] += lhook[i-1][t][j-1];
          if(j>1 && it[j-2] == g[t^1][i-1]) {
            dp[i][t][j] += dp[i-1][t^1][j-2];
            dp[i][t][j] += lhook[i-1][t^1][j-2];
          }
          dp[i][t][j] %= MOD;
          //cerr<<"@ "<<i<<" "<<t<<" "<<j<<" -> "<<dp[i][t][j]<<" * "<<rhook[i+1][t][m-j]<<nl;
          ans += dp[i][t][j] * rhook[i+1][t][m-j];
        }
        hook += lhook[i][t][m];
        hook += rhook[i][t][m];
        for(int j=2; j<m; j+=2) {
          hook += 2 * lhook[i][t][j] * rhook[i+1][t][m-j];
        }
      }
    }
    //cerr<<nl;
  }

  assert(hook%2 == 0);
  //cerr << "ans " << ans << " + hook " << hook/2 << nl;
  cout << (ans + hook/2) % MOD << nl;

  return 0;
}
