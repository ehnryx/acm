#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
const int INF = 0x3f3f3f3f;

/*
 * dp[x][h] = if we coloured everything up to x using colours in hash h, what
 * is the minimum number of offers we need to accept to colour the remaining?
 *
 * from each state (x,h), try accepting an offer that is
 * 1. valid (we don't use more than 3 colours total)
 * 2. increases the prefix of the fence that we colour
 * ^ these transitions are stored in adj
 */

const int L = 1e4;
vector<pair<int,int>> adj[L+1];
unordered_map<int,int> dp[L+1];

const int S = 10;
const int M = (1<<S)-1;
int solve(int x, int ha) {
  if(x == L) return 0;
  if(dp[x].count(ha)) return dp[x][ha];
  int best = INF;
  for(auto [r, c] : adj[x]) {
    // this part is checking if c is in the set of used colours
    int nxt = 0;
    for(int i=0; i<3; i++) {
      int col = ha >> (i*S) & M;
      if(col == 0) {
        nxt = ha | c << (i*S);
        break;
      } else if(col == c) {
        nxt = ha;
        break;
      }
    }
    // nxt is nonzero if we can use c
    if(nxt) {
      best = min(best, 1 + solve(r, nxt));
    }
  }
  return dp[x][ha] = best;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  unordered_map<string,int> idx;
  int cid = 0;
  for(int i=0; i<n; i++) {
    string col; int l, r;
    cin >> col >> l >> r;
    if(!idx.count(col)) {
      idx[col] = ++cid;
    }
    for(int j=0; j<=L; j++) {
      if(l <= j+1 && r > j) {
        adj[j].push_back(make_pair(r, idx[col]));
      }
    }
  }

  int ans = solve(0, 0);
  if(ans == INF) {
    cout << "IMPOSSIBLE" << nl;
  } else {
    cout << ans << nl;
  }

  return 0;
}
