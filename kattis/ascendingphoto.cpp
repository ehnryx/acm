#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n;
  cin >> n;

  map<int,int> cmpr;
  int arr[n];
  for (int i=0; i<n; i++) {
    cin >> arr[i];
    cmpr[arr[i]];
  }

  int m = 0;
  for (auto& it : cmpr) {
    it.second = ++m;
  }

  vector<int> vals;
  for (int i=0; i<n; i++) {
    arr[i] = cmpr[arr[i]];
    if (vals.empty() || arr[i] != vals.back()) {
      vals.push_back(arr[i]);
    }
  }

  n = vals.size();
  unordered_set<int> connect[m+1];
  connect[vals[0]].insert(1);
  int id = 1;
  for (int i=1; i<n; i++) {
    if (vals[i] != vals[i-1]+1) {
      id++;
    }
    connect[vals[i]].insert(id);
  }

  int dp[m+1], dp2[m+1], best[m+1];
  memset(dp, -1, sizeof dp);
  memset(dp2, -1, sizeof dp2);
  dp[0] = dp2[0] = best[0] = 0;
  for (int i=1; i<=m; i++) {
    // transitions
    for (int it : connect[i]) {
      // calculate
      int cur = 0;
      if (it != best[i-1]) {
        if (connect[i-1].count(it)) {
          cur = dp[i-1]+1;
        } else {
          cur = dp[i-1];
        }
      } else {
        if (connect[i-1].count(it)) {
          cur = dp2[i-1]+1;
        } else {
          cur = dp2[i-1];
        }
      }
      // update
      if (cur > dp[i]) {
        dp2[i] = dp[i];
        dp[i] = cur;
        best[i] = it;
      } else if (cur > dp2[i]) {
        dp2[i] = cur;
      }
    }
    // if unique
    if (dp2[i] == -1) {
      dp2[i] = dp[i];
    }
  }

  cout << (n-1) - dp[m] << nl;

  return 0;
}
