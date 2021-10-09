#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;
const int N = 2010;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  string s;
  cin >> s;

  int n = s.size();
  int ones = 0;
  for (int i=0; i<n; i++) {
    ones += (s[i] == '1');
  }

  if (2*ones == n) {
    for (int i=0; i<n-1; i++) {
      cout << s[n-1];
    }
    if (s[n-1] == '1') cout << '0';
    else cout << '1';
    cout << nl;
  } else if (2*ones < n) {
    for (int i=0; i<n; i++) {
      cout << 1;
    }
    cout << nl;
  } else {
    for (int i=0; i<n; i++) {
      cout << 0;
    }
    cout << nl;
  }

  return 0;
}

