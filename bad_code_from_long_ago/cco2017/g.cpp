#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

vector<int> height;
vector<vector<int>> water;
vector<unordered_set<int>> dp;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  
  int n;
  cin >> n;
  height.resize(n+1);
  water.resize(n+1);
  dp.resize(n+1);
  for (int i = 1; i <= n; i++) {
    cin >> height[i];
  }
  sort(height.begin(), height.end());

  for (int h = 2; h <= 50; h++) {
    auto it = lower_bound(height.begin(), height.end(), h);
    if (height.end() - it >= 2 && *it == h) {
      for (int i = 1; height[i] < *it; i++) {
        water[i].push_back(h);
      }
    }
  }

  dp[0].insert(0);
  for (int i = 1; i <= n; i++) {
    for (const int& prev : dp[i-1]) {
      dp[i].insert(prev);
      for (int level : water[i]) {
        dp[i].insert(prev + level - height[i]);
      }
    }
  }

  vector<int> ans;
  for (const int &it : dp[n]) {
    ans.push_back(it);
  }
  sort(ans.begin(), ans.end());

  for (const int& it : ans) {
    cout << it << " ";
  }
  cout << nl;

  return 0;
}
