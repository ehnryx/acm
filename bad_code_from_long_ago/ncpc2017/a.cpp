#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG
//#define USE_MAGIC_IO

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

ll l;
int a, b, t, r;
vector<int> coffee;
unordered_map<pair<ll, char>, pair<double, char>> dp; // dp[i] = best time from pos i, 1 if took coffee

// state = 0 if no coffee, 1 if holding coffee, 2 if drinking coffee
pair<double, char> solve(ll pos, char state) {
  if (pos >= l)
    return 0;
  if (dp.count({pos, state}))
    return dp[{pos, state}];
  auto it = lower_bound(coffee.begin(), coffee.end(), pos);
  if (it == coffee.end()) {
    if (state == 0)
      return dp[{pos, state}] = {(double) (l - pos) / a, 0};
    if (state == 1) {
      if (l - pos <= t*a)
        return dp[{pos, state}] = {(double) (l - pos) / a, 0};
      return dp[{pos, state}] = {(double) max(l - pos - a*t, 0) / b + t + (double) max(l - pos - a*t - b*r, 0) / a, 0};
    }
    if (state == 2) {
      if (

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  cin >> l >> a >> b >> t >> r;

  int n; cin >> n;
  for (int i = 0; i < n; i++)
    cin >> coffee[i];

  return 0;
}
