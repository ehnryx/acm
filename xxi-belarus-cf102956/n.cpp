#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());



// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n;
  cin >> n;
  vector<int> a(n);
  vector<pair<int,int>> order;
  vector<set<pair<int,int>>> win(n);
  for(int i=0; i<n; i++) {
    cin >> a[i];
    order.emplace_back(a[i], i);
    win[i].insert(pair(a[i], i));
  }
  sort(begin(order), end(order));

  vector<int> dsu(n, -1), sz(n, 1);
  function<int(int)> find = [&](int i) {
    if(dsu[i] == -1) return i;
    return dsu[i] = find(dsu[i]);
  };
  function<void(int,int)> link = [&](int i, int j) {
    i = find(i);
    j = find(j);
    if(i == j) return;
    if(size(win[j]) < size(win[i])) swap(i, j);
    dsu[i] = j;
    sz[j] += sz[i];
    for(const auto& v : win[i]) {
      win[j].insert(v);
    }
    win[i].clear();
  };

  vector<bool> done(n);
  for(auto [v, i] : order) {
    done[i] = true;
    if(i>0 && done[i-1]) {
      int g = find(i-1);
      int add = sz[g] - 1;
      while(!empty(win[g]) && begin(win[g])->first + add < v) {
        win[g].erase(begin(win[g]));
      }
      link(i, i-1);
    }
    if(i+1<n && done[i+1]) {
      int g = find(i+1);
      int add = sz[g] - 1;
      while(!empty(win[g]) && begin(win[g])->first + add < v) {
        win[g].erase(begin(win[g]));
      }
      link(i, i+1);
    }
  }

  vector<int> ans;
  for(const auto& it : win[find(0)]) {
    ans.push_back(it.second + 1);
  }
  sort(begin(ans), end(ans));
  cout << ans.size() << nl;
  for(int v : ans) {
    cout << v << " ";
  }
  cout << nl;

  return 0;
}
