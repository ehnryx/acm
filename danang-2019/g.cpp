#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
#define nl '\n'

ll solve(int x) {
  const int X = x;
  int t = 0;
  vector<int> digs = {x%10};
  ll ans = 0;
  while (x/=10) {
    ans += (9 + 10*t);
    t++;
    digs.push_back(x%10);
  }
  reverse(digs.begin(), digs.end());
  bool all0 = true;
  for (int i = 1; i < digs.size(); i++) {
    if (digs[i] != 0) {
      all0 = false;
      break;
    }
  }
  if (all0 && digs.size() > 1) {
    return solve(X-1)+1ll;
  }
  const int n = digs.size();
  vector<int> cur(n);
  cur.front() = 1;
  bool lswap = false;
  for(int i = 0; i < n; i++) {
    if (digs[i] != cur[i]) {
      while(cur.back() != digs[i]) {
        cur.back()++;
        ans++;
        lswap = false;
      }
      if (i < n-1 && !lswap)
        ans++;
      swap(cur[i], cur.back());
      lswap = true;
      for (int j = i+1; j < n; j++) {
        if (digs[j] == cur.back()) {
          swap(cur[j], cur.back());
        }
      }
    }
  }
  return ans;
}

void deal() {
  int x; cin >> x;
  cout << solve(x) << nl;;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int T; cin >> T;
  while(T--) {
    deal();
  }

  return 0;
}

