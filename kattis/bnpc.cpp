#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
//%:include "data_structure/heap.h"

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
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n, k;
  cin >> n >> k;

  vector<int> have(n);
  unordered_map<string, int> remap;
  for(int i=0; i<n; i++) {
    string s;
    cin >> s >> have[i];
    remap[s] = i;
  }

  int m;
  cin >> m;
  vector<int> type(m), need(m);
  vector<int> maxn(n, -1);
  for(int i=0; i<m; i++) {
    string s;
    cin >> s >> need[i];
    type[i] = remap[s];
    maxn[type[i]] = max(maxn[type[i]], need[i]);
  }

  for(int i=0; i<n && k>=0; i++) {
    k -= max(0, maxn[i] - have[i]);
    have[i] = max(have[i], maxn[i]);
  }

  if(k < 0) {
    cout << 0 << nl;
    return 0;
  }

  ll ans = 0;
  vector<ll> first(n), second(n);
  for(int i=0; i<m; i++) {
    if(need[i] < have[type[i]]) {
      ans += have[type[i]];
      first[type[i]] += 1;
      second[type[i]] += 1;
    } else {
      first[type[i]] += have[type[i]] + 1;
      second[type[i]] += 1;
    }
  }

  priority_queue<pair<ll, int>> todo;
  //heap<pair<ll, int>, greater<pair<ll, int>>> todo(n);
  for(int i=0; i<n; i++) {
    todo.emplace(first[i], 2*i + 1);
  }
  for(; todo.top().second % 2 && k > 0; k--) {
    auto [v, i] = todo.top();
    todo.pop();
    ans += v;
    todo.emplace(second[i/2], i-1);
  }
  ans += todo.top().first * k;

  cout << ans << nl;

  return 0;
}

