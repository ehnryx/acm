#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  ll n;
  cin >> n;

  string num = to_string(n);
  set<char> nots(begin(num), end(num));
  set<char> s;
  for(char i='0'; i<='9'; i++) {
    if(!nots.count(i)) {
      s.insert(i);
    }
  }

  for(char c : num) {
    assert(!s.count(c));
  }

  vector<pair<ll,ll>> all;
  for(char a : s) {
    for(char b : s) {
      for(int i=0; i<=17; i++) {
        ll x = stoll(string(1, a) + string(i, b));
        assert(x >= 0);
        //if(x) {
          all.emplace_back(abs(n-x), x);
        //}
      }
    }
  }

  sort(begin(all), end(all));
  all.resize(unique(begin(all), end(all)) - begin(all));

  if(empty(all)) {
    cout << "Impossible" << nl;
  } else if(size(all) == 1) {
    cout << all[0].second << nl;
  } else if(all[0].first == all[1].first) {
    assert(all[0].second < all[1].second);
    cout << all[0].second << " " << all[1].second << nl;
  } else {
    cout << all[0].second << nl;
  }

  /*
  if(empty(s)) {
    cout << "Impossible" << nl;
    return 0;
  }

  if (size(s) == 1 && *s.begin() == '0') {
    cout << 0 << nl;
    return 0;
  }

  ll a = -1;
  ll b = -1;

  char first = num.front();

  if (s.lower_bound(first) == s.begin()) {
    a = stoll(string(num.size() - 1, *s.rbegin()));
  } else {
    char f = *prev(s.lower_bound(first));
    a = stoll(string(1, f) + string(num.size() - 1, *s.rbegin()));
  }
  assert(a < n && a != -1);

  if (s.lower_bound(first) == s.end()) {
    if (*s.begin() == '0') {
      if (s.size() > 1) {
        b = stoll(string(1, *next(s.begin())) + string(num.size(), *s.begin()));
      }
    } else {
      b = stoll(string(num.size() + 1, *s.begin()));
    }
  } else {
    char f = *s.lower_bound(first);
    b = stoll(string(1, f) + string(num.size() - 1, *s.begin()));
  }
  assert(b == -1 || n < b);

  if (a == 0 && b == -1) {
    cout << "Impossible" << nl;
    return 0;
  }

  if (a == 0) {
    cout << b << nl;
    return 0;
  }

  if (b == -1) {
    cout << a << nl;
    return 0;
  }

  if (abs(n-a) < abs(n-b)) {
    cout << a << nl;
  } else if(abs(n-a) > abs(n-b)) {
    cout << b << nl;
  } else {
    cout << a << " " << b << nl;
  }
  */

  return 0;
}
