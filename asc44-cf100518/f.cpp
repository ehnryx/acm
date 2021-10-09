#include <bits/stdc++.h>
using namespace std;

#define nl '\n'

const int N = 1e5+1;
const int K = 1e2+1;
int dp[K][N];
int pre[K][N];
int arr[N];
int cur[N];

// left endpoint should be in [l,r]
// cur stores values from arr[r+1,s-1] initially
void solve(int k, int l, int r, int s, int e, int curv) {
  if (s > e) return;
  int m = (s+e)/2;

  int rightv = curv;
  // update cur to arr[r+1,m]
  for (int i=max(r+1,s); i<=m; i++) {
    rightv = max(rightv, ++cur[arr[i]]);
  }
  // sweep left from r->l
  int opt = -1;
  int oopt = -1;
  int maxv = rightv;
  for (int i=min(m,r); i>=l; i--) {
    maxv = max(maxv, ++cur[arr[i]]);
    int nxt = dp[k-1][i-1] + maxv;
    if (nxt > dp[k][m]) {
      dp[k][m] = nxt;
      opt = i;
    }
    if (nxt == dp[k][m]) {
      oopt = i;
    }
  }
  pre[k][m] = opt;

  // now cur has [l,m], undo to [r+1,m]
  for (int i=l; i<=min(m,r); i++) {
    cur[arr[i]]--;
  }
  solve(k, oopt, r, m+1, e, rightv);

  // undo to [r+1,s-1]
  for (int i=max(r+1,s); i<=m; i++) {
    cur[arr[i]]--;
  }

  // update to [opt+1,s-1]
  for (int i=min(s-1,r); i>opt; i--) {
    curv = max(curv, ++cur[arr[i]]);
  }
  solve(k, l, opt, s, m-1, curv);

  // update to [r+1,s-1]
  for (int i=min(s-1,r); i>opt; i--) {
    cur[arr[i]]--;
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

#ifdef ONLINE_JUDGE
  freopen("funny.in", "r", stdin);
  freopen("funny.out", "w", stdout);
#endif

  for (int n, k; cin >> n >> k && n; ) {
    for (int j=1; j<=k; j++) {
      memset(dp[j], 0, (n+1)*sizeof(int));
      memset(pre[j], -1, (n+1)*sizeof(int));
    }
    unordered_map<int,int> remap;
    int rid = 1;
    for (int i=1; i<=n; i++) {
      cin >> arr[i];
      if (!remap.count(arr[i])) {
        remap[arr[i]] = rid++;
      }
    }

    memset(cur, 0, rid*sizeof(int));
    int maxv = 0;
    for (int i=1; i<=n; i++) {
      arr[i] = remap[arr[i]];
      maxv = max(maxv, ++cur[arr[i]]);
      dp[1][i] = max(dp[1][i-1], maxv);
    }

    memset(cur, 0, rid*sizeof(int));
    for (int i=2; i<=k; i++) {
      solve(i, i, n, i, n, 0);
      for (int j=1; j<=n; j++) {
        if (dp[i][j-1] > dp[i][j]) {
          dp[i][j] = dp[i][j-1];
          pre[i][j] = pre[i][j-1];
        }
      }
    }
    vector<int> ans;
    for (int p = pre[k][n], l=k; p != -1; p = pre[--l][p]) {
      ans.push_back(p-1);
    }
    reverse(ans.begin(), ans.end());

    cout << dp[k][n] << nl;
    for (int it : ans) {
      cout << it << " ";
    }
    cout << nl;
  }

  return 0;
}
