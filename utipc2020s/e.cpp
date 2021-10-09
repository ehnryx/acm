#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';
typedef long long ll;
typedef double ld;

const int N = 5e2;
const int T = 1e4 + 1;
vector<int> adj[N];
ld distr[T][N];
ld sum[T][N];
ld dp[T][N];

void build(int s) {
  fill(&distr[0][0], &distr[0][0] + T*N, 0);
  distr[0][s] = 1;
  for(int t=1; t<T; t++) {
    for(int i=0; i<N; i++) {
      int sz = adj[i].size();
      for(int j : adj[i]) {
        distr[t][j] += distr[t-1][i] / sz;
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(9);

  int n, m;
  cin >> n >> m;
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  int p;
  cin >> p;
  for(int i=0; i<p; i++) {
    int w;
    cin >> w;
    build(w);
    for(int t=0; t<T; t++) {
      for(int j=0; j<n; j++) {
        sum[t][j] += distr[t][j];
      }
    }
  }

  ld ans = 1e18;
  fill(&dp[0][0], &dp[0][0] + T*N, 1e18);
  dp[0][0] = 0;
  for(int t=1; t<T; t++) {
    for(int i=0; i<n; i++) {
      for(int j : adj[i]) {
        dp[t][i] = min(dp[t][i], dp[t-1][j] + sum[t][i]);
      }
    }
    ans = min(ans, dp[t][n-1]);
  }
  cout << ans << nl;

  return 0;
}
