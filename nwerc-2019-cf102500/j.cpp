#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
const char nl = '\n';



int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int n, c, r;
  cin >> n >> c >> r;

  vector<int> a(n);
  vector<pair<int,int>> vals;
  for(int i=0; i<n; i++) {
    cin >> a[i];
    vals.emplace_back(abs(a[i]), i);
  }
  sort(vals.begin(), vals.end(), greater<pair<int,int>>());
  vals.emplace_back(-1, -1);

  ll pos = 0;
  ll neg = 0;
  for(int i=0; i<n; i++) {
    ll npos = (a[i] > 0 ? neg : pos + r);
    ll nneg = (a[i] < 0 ? pos : neg + r);
    pos = npos;
    neg = nneg;
  }
  ll ans = min(pos, neg);

  function<bool(int,int)> bad = [=](int i, int j) {
    if((ll)a[i]*a[j] < 0) return abs(i-j)%2 == 0;
    if((ll)a[i]*a[j] > 0) return abs(i-j)%2 == 1;
    return true;
  };

  int fix = 0;
  set<int> active;
  for(int i=0; i<n; i++) {
    if(vals[i].first == 0) break;
    int j = vals[i].second;
    int v = vals[i+1].first + 1;
    auto it = active.insert(j).first;
    if(it != active.begin() && next(it) != active.end()) {
      fix -= bad(*prev(it), *next(it));
    }
    if(it != active.begin()) {
      fix += bad(*prev(it), *it);
    }
    if(next(it) != active.end()) {
      fix += bad(*it, *next(it));
    }
    ans = min(ans, (ll)c*v + (ll)fix*r);
  }
  cout << ans << nl;

  return 0;
}
