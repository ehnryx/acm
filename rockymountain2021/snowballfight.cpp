#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

vector<pair<ll, char>> step(vector<pair<ll, char>> v) {
  vector<int> hit(3);
  for(int i=0; i<3; i++) {
    if(v[i].first == 0) continue;
    int j = (i + 1) % 3;
    int k = (i + 2) % 3;
    if(v[j].first > v[k].first) {
      hit[j]++;
    } else if(v[j].first < v[k].first) {
      hit[k]++;
    } else if((v[j].second + 1 - 'A') % 3 == v[k].second - 'A') {
      hit[j]++;
    } else {
      hit[k]++;
    }
  }
  for(int i=0; i<3; i++) {
    v[i].first = max(v[i].first - hit[i], (ll)0);
  }
  sort(begin(v), end(v));
  return v;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  ll a, b, c;
  cin >> a >> b >> c;
  auto A = pair(a, 'A');
  auto B = pair(b, 'B');
  auto C = pair(c, 'C');

  vector<pair<ll, char>> v = { A, B, C };
  sort(begin(v), end(v));

  //cerr << v << endl;

  if (v[0].first < v[1].first && v[1].first < v[2].first) {
    ll t = min(v[1].first - v[0].first, v[2].first - v[1].first);
    v[1].first -= t;
    v[2].first -= 2*t;
    sort(begin(v), end(v));
  }

  //cerr << v << endl;

  assert(v[0].first == v[1].first || v[1].first == v[2].first);

  if(v[0].first == v[1].first && v[1].first < v[2].first) {
    ll t2 = min(v[0].first, (v[2].first - v[0].first) / 3);
    t2 = max(t2 - 1, (ll)0);
    v[2].first -= 4 * t2;
    v[1].first -= t2;
    v[0].first -= t2;
    sort(begin(v), end(v));
    for(int j=0; j<5; j++) {
      v = step(v);
    }
  }

  else if(v[0].first < v[1].first && v[1].first == v[2].first) {
    ll t2 = (v[2].first - v[0].first) / 3;
    t2 = max(t2 - 1, (ll)0);
    v[2].first -= 3 * t2;
    v[1].first -= 3 * t2;
    sort(begin(v), end(v));
    for(int j=0; j<5; j++) {
      v = step(v);
    }
  }

  //cerr << v << endl;

  // done
  if (v[0].first == 0 && v[1].first == 0 && v[2].first > 0) {
    cout << v[2].second << " " << v[2].first << nl;
    return 0;
  }

  assert(v[2].first - v[1].first <= 1);

  if(v[0].first == v[2].first) {
    cout << "Rubble!" << nl;
    return 0;
  }

  {
    ll t3 = v[0].first / 3;
    t3 = max(t3 - 1, (ll)0);
    v[0].first -= 3 * t3;
    v[1].first -= 3 * t3;
    v[2].first -= 3 * t3;
    sort(begin(v), end(v));
  }

  for(int j=0; j<42; j++) {
    v = step(v);
  }

  if(v[0].first == v[2].first) {
    cout << "Rubble!" << nl;
  } else {
    cout << v[2].second << " " << v[2].first << nl;
  }

  return 0;
}
