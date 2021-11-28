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

  int d, n;
  cin >> d >> n;

  // we never add more than n numbers, so might as well put them in a set
  vector<int> all(n);
  iota(begin(all), end(all), 1);
  set<int> available(begin(all), end(all));

  // store the numbers to re-add to available
  vector<vector<int>> to_add(n+d);

  for(int i=0; i<n; i++) {
    char t;
    cin >> t;
    if(t == 'a') {
      // add
      int x = *available.begin();
      available.erase(available.begin());
      cout << x << nl;
    } else {
      // remove
      int x;
      cin >> x;
      to_add[i+d-1].push_back(x);
    }

    // add the previously reserved numbers
    for(int x : to_add[i]) {
      available.insert(x);
    }
  }

  return 0;
}
