#include <bits/stdc++.h>
using namespace std;
#define FILENAME "hash"

typedef long long ll;
typedef long double ld;
const char nl = '\n';


const string s1 = "zyBELYbMlJqBhKNDYW";
const string s2 = "wPXNZzTatDERCbGHsZ";

int hsh(const string& s) {
  int ans = 0;
  for (int i=s.size()-1, j=1; i>=0; --i, j*=31) {
    ans += j*s[i];
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
  int k;
  cin >> k;
  for (int i=0; i<k; ++i) {
    string s;
    for (int j=0; j<11; ++j) {
      if (i&(1<<j)) {
        s += s1;
      } else {
        s += s2;
      }
    }
    assert(hsh(s) == 0);
    cout << s << "\n";
  }


  return 0;
}
