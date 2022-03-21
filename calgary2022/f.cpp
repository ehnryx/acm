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

  int n;
  cin >> n;
  vector<string> names(2*n);
  map<string, int> remap;
  vector<int> to(2*n, -1);
  vector<int> start(n);
  for(int i=0, rid=0; i<n; i++) {
    string a, b;
    cin >> a >> b;
    if(!remap.count(a)) {
      remap[a] = rid;
      names[rid++] = a;
    }
    if(!remap.count(b)) {
      remap[b] = rid;
      names[rid++] = b;
    }
    to[remap[a]] = remap[b];
    start[i] = remap[a];
  }

  function<int(int)> solve = [&](int i) {
    if(to[i] == -1) return i;
    return to[i] = solve(to[i]);
  };

  for(int i=0; i<n; i++) {
    cout << names[start[i]] << " " << names[solve(start[i])] << nl;
  }

  return 0;
}
