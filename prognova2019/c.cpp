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

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

int check(int a, int b, const string& c) {
  int g = a^b;
  if(g == 0 && (c == "0" || c == "?")) return 1;
  for(int i=(int)c.size()-1; i>=0; i--, g/=10) {
    if(c[i] == '?' && g == 0) {
      return false;
    }
    if(c[i] != '?' && g%10 != c[i]-'0') {
      return false;
    }
  }
  return g == 0;
}

int solve2(int a, string b, const string& c) {
  int i = b.find('?');
  if(i == -1) {
    return check(a, stoi(b), c);
  }
  int res = 0;
  for(int d=(i==0&&b.size()>1); d<10; d++) {
    b[i] = d+'0';
    res += solve2(a, b, c);
  }
  return res;
}

int solve(string a, string b, const string& c) {
  int i = a.find('?');
  if(i == -1) {
    return solve2(stoi(a), b, c);
  }
  int res = 0;
  for(int d=(i==0&&a.size()>1); d<10; d++) {
    a[i] = d+'0';
    res += solve(a, b, c);
  }
  return res;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  string _;
  vector<pair<int,string>> s(3);
  cin >> s[0].second >> _ >> s[1].second >> _ >> s[2].second;

  for(int i=0; i<3; i++) {
    s[i].first = 0;
    for(char c:s[i].second) {
      if(c == '?') {
        s[i].first++;
      }
    }
  }
  sort(s.begin(), s.end());

  cout << solve(s[0].second, s[1].second, s[2].second) << nl;

  return 0;
}
