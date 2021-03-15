#include <bits/stdc++.h>

using namespace std;

#define FILENAME "caravan"

#define nl '\n'
typedef long long ll;
typedef long double ld;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n;
  cin >> n;

  vector<pair<int,int>> v;
  for(int i=0; i<n; i++) {
    int l, r;
    cin >> l >> r;
    v.emplace_back(l, r);
  }
  sort(v.begin(), v.end());

  ld l = 0;
  ld r = v[0].second - v[0].first;
  for(int bs=0; bs<300; bs++) {
    ld m = (l+r) / 2;
    ld lb = -1;
    bool ok = true;
    for(int i=0; i<n && ok; i++) {
      lb = max(lb, (ld)v[i].first) + m;
      ok &= (lb <= v[i].second);
    }
    if(ok) {
      l = m;
    } else {
      r = m;
    }
  }

  pair<ld,int> best(7, 0);
  for(int i=1; i<=n; i++) {
    best = min(best, make_pair(abs(r*i - llround(r*i)), i));
  }
  ll a = llround(r * best.second);
  ll b = best.second;
  ll g = __gcd(a, b);
  cout << a/g << "/" << b/g << nl;

  return 0;
}
