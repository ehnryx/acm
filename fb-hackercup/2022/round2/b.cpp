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

constexpr int MOD = 1e9 + 7;

void solve_case() {

  int n, k;
  cin >> n >> k;
  map<int, int> remap;
  vector<tuple<int, int, int, int, int>> events;
  for(int i=0; i<n; i++) {
    int a, b, x, y;
    cin >> a >> b >> x >> y;
    events.emplace_back(a, b, x, y, i);
    remap[a];
    remap[b];
  }

  int rid = 0;
  for(auto& it : remap) {
    it.second = rid++;
  }

  vector<vector<pair<int, int>>> in(rid), out(rid);
  for(auto [a, b, x, y, i] : events) {
    out[remap[a]].emplace_back(x, i);
    in[remap[b]].emplace_back(y, i);
  }

  for(int i=0; i<rid; i++) {
    sort(begin(in[i]), end(in[i]));
    sort(begin(out[i]), end(out[i]));
  }

  vector<multiset<ll>> paths(n);
  for(int i=0; i<n; i++) {
    paths[i].insert(0);
  }

  for(int day=0; day<rid; day++) {
    multiset<ll> cur;
    for(auto from = begin(in[day]), to = begin(out[day]);
        to != end(out[day]); to++) {
      while(from != end(in[day]) && from->first < to->first) {
        for(auto x : paths[from->second]) {
          cur.insert(x - from->first);
          if(size(cur) > k) {
            cur.erase(begin(cur));
          }
        }
        from++;
      }
      for(auto x : cur) {
        paths[to->second].insert(x + to->first);
        if(size(paths[to->second]) > k) {
          paths[to->second].erase(begin(paths[to->second]));
        }
      }
    }
  }

  vector<ll> all;
  for(int i=0; i<n; i++) {
    for(auto x : paths[i]) {
      all.push_back(x);
    }
  }
  sort(begin(all), end(all), greater<ll>());
  ll ans = 0;
  for(int i=0; i < min(k, (int)size(all)); i++) {
    ans = (ans + all[i]) % MOD;
  }
  cout << ans << nl;

  return;
}

void initialize() {
}

