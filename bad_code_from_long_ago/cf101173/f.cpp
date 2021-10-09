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

int getsize(int leaf, const vector<int>& next) {
  int sz = 0;
  while (leaf != -1) {
    leaf = next[leaf];
    sz++;
  }
  return sz;
}

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  int n;
  cin >> n;
  unordered_set<int> leaffirst, leafsecond;
  vector<bool> f(n), s(n);
  vector<int> first(n), second(n);
  for (int i = 0; i < n; i++) {
    cin >> first[i];
    first[i]--;
    if (first[i] != -1) {
      f[first[i]] = true;
    }
  }
  for (int i = 0; i < n; i++) {
    cin >> second[i];
    second[i]--;
    if (second[i] != -1) {
      s[second[i]] = true;
    }
  }
  for (int i = 0; i < n; i++) {
    if (!f[i]) leaffirst.insert(i);
    if (!s[i]) leafsecond.insert(i);
  }
  int ans = 0;
  for (int leaf : leaffirst) {
    if (leafsecond.count(leaf)) {
      // merge
      int common = 1;
      int temp = leaf;
      while (first[temp] != -1 && first[temp] == second[temp]) {
        temp = first[temp];
        common++;
      }
      ans += getsize(leaf, first) - common;
      ans += getsize(leaf, second) - common;
      leafsecond.erase(leaf);
    } else {
      ans += getsize(leaf, first)-1;
    }
  }
  for (int leaf : leafsecond) {
    ans += getsize(leaf, second)-1;
  }
  cout << ans << nl;

  return 0;
}
