#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
#define nl '\n'

vector<vector<int>> ans;
void group(int s, int sz, int k, int ch) {
  s = s*sz - sz;
  int step = sz / k;
  for(int j=0; j<step; j++) {
    vector<int> cur;
    for(int i=0; i<k; i++) {
      for(int c=0; c<ch; c++) {
        cur.push_back((s + j + i*step)*ch + c + 1);
      }
    }
    ans.push_back(move(cur));
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int n, k;
  cin >> n >> k;

  int m = n;
  int sz = 1;
  int ch = 1;
gulag:
  //cerr<<"gulag: "<<m<<" "<<k<<" "<<sz<<" "<<ch<<nl;
  while (m % k == 0) {
    sz *= k;
    for(int i=1; i*k<=m; i++) {
      group(i, sz, k, ch);
    }
    m /= k;
  }
  if(__gcd(m,k) != 1) {
    int r = k / __gcd(m,k);
    k /= r;
    sz /= r;
    ch *= r;
    goto gulag;
  }

  if(m != 1) {
    cout << -1 << nl;
  } else {
    assert(ans.size() <= 1e6 && !ans.empty());
    cout << ans.size() << nl;
    for(const vector<int>& v : ans) {
      for(int it : v) {
        cout << it << " ";
      }
      cout << nl;
    }
  }

  return 0;
}
