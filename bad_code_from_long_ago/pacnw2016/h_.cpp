#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG

#define ll long long
#define pii pair<int,int>
#define pdd pair<ldouble,ldouble>
#define ldouble long double
#define pt complex<ldouble>
#define ld ldouble
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ldouble EPS = 1e-9;
const int N = 2e5+10;

ll n; int k;
vector<pair<ll, ll>> s;
ll dp[N];
ll solve(const ll& pos) {
  if (pos >= k) return 0;
  if (dp[pos] != -1) return dp[pos];
  ll ans = solve(pos+1);
  // binary search from pos to k
  int left = pos+1;
  int right = k-1;
  int mid = k;
  while (left <= right) {
    mid = (left+right)/2;
    if (s[mid].first <= s[pos].second)
      left = mid+1;
    else
      right = mid-1;
    if (s[mid].first <= s[pos].second)
      mid++;
  }
  ans = max(ans, s[pos].second - s[pos].first + 1 + solve(mid));
  return dp[pos] = ans;
}

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  cin >> n >> k;
  s.resize(k);
  for (int i = 0; i < k; i++)
    cin >> s[i].first >> s[i].second;
  memset(dp, -1, sizeof dp);
  sort(s.begin(), s.end());
  for (int i = k-1; i >= 0; i--)
    solve(i);
  cout << n - solve(0) << endl;

  return 0;
}
