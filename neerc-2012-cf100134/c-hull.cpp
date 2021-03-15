#include <bits/stdc++.h>

using namespace std;

#define FILENAME "caravan"

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }

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

  vector<pt> hull;
  tuple<ld,int,int> best(1e19, -1, -1);
  for(int i=n-1; i>=0; i--) {
    pt top(i+1, v[i].second);
    pt bot(i, v[i].first);
    while(hull.size() >= 2 && cp(hull.back() - top, hull[hull.size()-2] - top) < 0) {
      hull.pop_back();
    }
    hull.push_back(top);

    int l = 0;
    int r = hull.size() - 1;
    while(l < r) {
      int m = (l+r) / 2;
      pt p = hull[m];
      if(cp(p-bot, hull[m+1]-p) < 0) {
        l = m+1;
      } else {
        r = m;
      }
    }
    best = min(best, {(hull[r].imag()-bot.imag())/(hull[r].real()-bot.real()), i, (int)hull[r].real()});
  }

  auto [_, li, ri] = best;
  int num = v[ri-1].second - v[li].first;
  int den = ri-li;
  int g = __gcd(num, den);
  num /= g;
  den /= g;

  cout << num << "/" << den << endl;

  return 0;
}
