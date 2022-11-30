#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  vector<int> a(n);
  unordered_map<int, int> idx, good;
  for(int i=0; i<n; i++) {
    cin >> a[i];
    idx[a[i]] = i;
  }
  auto b = a;
  sort(begin(b), end(b));
  for(int i=0; i<n; i++) {
    good[b[i]] = i;
  }

  int m;
  cin >> m;
  for(int i=0; good[m] != idx[m]; ) {
    if(a[i] == b[i]) {
      i++;
      continue;
    }
    int to = good[a[i]];
    swap(a[i], a[to]);
    swap(idx[a[i]], idx[a[to]]);
  }

  for(auto i : a) {
    cout << i << " ";
  }
  cout << nl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T = 1;
#ifdef MULTI_TEST
  cin >> T;
#endif
  for(int testnum=1; testnum<=T; testnum++) {
    solve_main(testnum, cin);
  }

  return 0;
}
