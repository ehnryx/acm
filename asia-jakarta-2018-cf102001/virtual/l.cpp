#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  ll k, s; string in;
  cin >> k >> in;
  bitset<63> bs(in);
  s = bs.to_ullong();
  int ans = 0;
  while (s > k) {
    ans++;
    int cnt = 0;
    for (int i=60; i>=0; i--) {
      if (1LL<<i & s) {
        cnt++;
        if (cnt == 2) {
          ll mask = (1LL<<i)-1;
          s = (s & mask) | (s >> 1 & ~mask);
          break;
        }
      }
    }
    if (cnt == 2) continue;
    s >>= 1;
  }
  cout << ans << nl;

  return 0;
}
