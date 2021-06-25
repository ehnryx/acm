#include <bits/stdc++.h>
using namespace std;


const char nl = '\n';
using ll = long long;
using ld = long double;


int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    for (int j = 0; j < m; j++) {
      a[i] |= (s[j] == 'T') << j;
    }
  }

  int ans = m;
  for (int bm = 0; bm < 1 << m; bm++) {
    int wrong = 0;
    for (int i = 0; i < n; i++) {
      wrong = max(wrong, __builtin_popcount(a[i] ^ bm));
    }
    ans = min(ans, wrong);
  }
  cout << m - ans << nl;

  return 0;
}
