#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;

inline ll zig(ll x) {
  if (x >= 0) return 2*x;
  return -2*x-1;
}

inline ll ziginv(unsigned long long x) {
  if (x%2) {
    ll k = x / 2;
    cerr << x << " " << k << nl;
    return -k;
  } else {
    return x/2;
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  for (int i = -255; i <= 255; i++) {
    cerr << i << " " << zig(i) << " " << ziginv(i) << nl;
    assert(ziginv(zig(i)) == i);
  }
  int n; cin >> n;
  vector<int> v(n);
  for (int& i : v) cin >> i;
  for (int i : v) cerr << bitset<8>(i) << " "; cerr << nl;
  unsigned long long cur = 0; ll mul = 1;
  for (int i : v) {
    if (i & (1 << 7)) {
      cur += (i ^ (1 << 7)) * mul;
    } else {
      cur += i;
      cout << ziginv(cur) << nl;
      cur = 0;
      mul = 1;
    }
    mul <<= 7;
  }

  return 0;
}
