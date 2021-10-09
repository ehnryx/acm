#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';
typedef long long ll;
typedef long double ld;

const int INF = 0x3f3f3f3f;



int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int n, k;
  cin >> n >> k;
  vector<int> a(n);
  for(int i=0; i<n; i++) {
    cin >> a[i];
  }

  function<int(int)> count = [=](int j) {
    int p = 0;
    int cnt = 0;
    for(int i=1; i<n; i++) {
      if(i == n-1 || p+j < a[i+1]) {
        if(p + j < a[i]) return INF;
        p = a[i];
        cnt++;
      }
    }
    return cnt;
  };

  int l = 1;
  int r = a[n-1];
  while(l < r) {
    int m = (l+r+1) / 2;
    if(count(m) < k) {
      r = m-1;
    } else {
      l = m;
    }
  }
  if(count(r) == k) {
    assert(count(r+1) != k);
    cout << r << nl;
  } else {
    cout << -1 << nl;
  }

  return 0;
}
