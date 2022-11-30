#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
namespace {
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
}

using ll = long long;
using ld = long double;
using pt = complex<ld>;
random_device _rd; mt19937 rng(_rd());

constexpr char nl = '\n';

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  return os << '(' << v.first << ", " << v.second << ')';
}
template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  os << "[ "; for (const T& it : v) { os << it << " , "; }
  return os << ']';
}
template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ "; for (const T& it : v) { os << it << " , "; }
  return os << '}';
}
template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ "; for (const pair<T,U>& it : v) { os << it << " , "; }
  return os << '}';
}

template <class T, class U>
istream& operator >> (istream& is, pair<T,U>& v) {
  return is >> v.first >> v.second;
}
template <int i, class... Ts>
istream& read_tuple_impl(istream& is, tuple<Ts...>& v) {
  if constexpr (i == 0) return is;
  else return read_tuple_impl<i-1>(is, v) >> get<i-1>(v);
}
template <class... Ts>
istream& operator >> (istream& is, tuple<Ts...>& v) {
  return read_tuple_impl<sizeof...(Ts)>(is, v);
}

template <class T = int>
vector<T> read_array(int n, int s=0) {
  vector<T> a(n + 2*s);
  for(int i=0; i<n; i++) {
    cin >> a[s+i];
  }
  return a;
}

template <class T = int>
vector<vector<T>> read_grid(int n, int m, int s=0, int t=0) {
  vector a(n + 2*s, vector<T>(m + 2*t));
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> a[s+i][t+j];
    }
  }
  return a;
}

void solve_case();
void initialize();

////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  initialize();

  int T;
  cin >> T;
  for (int cc = 1; cc <= T; cc++) {
    auto start = chrono::steady_clock::now();
    cout << "Case #" << cc << ": ";
    solve_case();
    if(argc > 1 && argv[1][0] == 't') {
      cerr << "Time: " << (chrono::steady_clock::now() - start) / 1.0s << "s" << nl << nl;
    }
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////

%:include "ds/splay_tree.h"

struct node final : splay_node_base<node, int, ll> {
  using base = splay_node_base<node, int, ll>;
  node(): base() {}
  node(int v): base(v, v) {}
  ll get() { return value; }
  void pull() {
    value = key + left->value + right->value;
  }
};

void solve_case() {

  int n, m;
  cin >> n >> m;

  vector<int> a(n+1);
  vector<splay_tree<node>> cnt(3);
  for(int i=1; i<=n; i++) {
    cin >> a[i];
    cnt[a[i]].insert(i);
  }

  ll ans = 0;

  while(m--) {
    int x, y, z;
    cin >> x >> y >> z;
    cnt[a[x]].erase(x);
    a[x] = y;
    cnt[a[x]].insert(x);

    int sum = cnt[1].size() + 2 * cnt[2].size();
    if(sum % 2) {
      ans += -1;
      continue;
    }

    auto mid1 = cnt[1].lower_bound(z + 1);
    auto mid2 = cnt[2].lower_bound(z + 1);
    int rank1 = cnt[1].rank(mid1);
    int rank2 = cnt[2].rank(mid2);
    int leftsum = rank1 + 2 * rank2;
    int rightsum = sum - leftsum;

    int mv = abs(leftsum - rightsum) / 2;
    if(leftsum < rightsum) {
      if(rank1 < mv || rank2 + mv > cnt[2].size()) {
        ans += -1;
        continue;
      }
      ll left = cnt[1].query_range(cnt[1].at(rank1 - mv - 1), cnt[1].at(rank1));
      ll right = cnt[2].query_range(cnt[2].at(rank2 - 1), cnt[2].at(rank2 + mv));
      ans += right - left;
    } else if(leftsum > rightsum) {
      if(rank2 < mv || rank1 + mv > cnt[1].size()) {
        ans += -1;
        continue;
      }
      ll left = cnt[2].query_range(cnt[2].at(rank2 - mv - 1), cnt[2].at(rank2));
      ll right = cnt[1].query_range(cnt[1].at(rank1 - 1), cnt[1].at(rank1 + mv));
      ans += right - left;
    }
  }

  cout << ans << nl;

  return;
}

void initialize() {
}

