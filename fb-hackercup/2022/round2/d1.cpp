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



void solve_case() {

  int n, m;
  cin >> n >> m;

  vector<int> a(n+1);
  vector<ordered_set<int>> cnt(4);
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

    int l1 = cnt[1].order_of_key(z + 1);
    int l2 = cnt[2].order_of_key(z + 1);
    int l3 = cnt[3].order_of_key(z + 1);
    int left = l1 + 2 * l2 + 3 * l3;

    int r1 = cnt[1].size() - l1;
    int r2 = cnt[2].size() - l2;
    int r3 = cnt[3].size() - l3;
    int right = r1 + 2 * r2 + 3 * r3;

    if(left > right) {
      swap(left, right);
      swap(l1, r1);
      swap(l2, r2);
      swap(l3, r3);
    }

    int diff = right - left;
    if(diff % 2) {
      ans += -1;
      continue;
    }

    int base = 0;

    {
      int mv = min(diff / 4, min(r3, l1));
      base += mv;
      left += mv * 2;
      right -= mv * 2;
      l1 -= mv; l3 += mv;
      r1 += mv; r3 -= mv;
      diff = right - left;
      assert(diff >= 0);
    }

    {
      int mv = min(diff / 2, min(r2, l1));
      base += mv;
      left += mv * 1;
      right -= mv * 1;
      l1 -= mv; l2 += mv;
      r1 += mv; r2 -= mv;
      diff = right - left;
      assert(diff >= 0);
    }

    {
      int mv = min(diff / 2, min(r3, l2));
      base += mv;
      left += mv * 1;
      right -= mv * 1;
      l2 -= mv; l3 += mv;
      r2 += mv; r3 -= mv;
      diff = right - left;
      assert(diff >= 0);
    }

    if(diff == 0) {
      ans += base;
    } else {
      ans += -1;
    }
  }

  cout << ans << nl;

  return;
}

void initialize() {
}

