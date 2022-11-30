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

%:include "string/suffix_array.h"

void solve_case() {

  int n, k;
  cin >> n >> k;
  map<int, int> remap;
  vector<int> a(n);
  for(int i=0; i<n; i++) {
    cin >> a[i];
    remap[a[i]];
  }
  vector<int> b(n);
  for(int i=0; i<n; i++) {
    cin >> b[i];
  }

  int rid = 0;
  for(auto& it : remap) {
    it.second = ++rid;
  }
  for(int i=0; i<n; i++) {
    a[i] = remap[a[i]];
    b[i] = remap[b[i]];
  }

  bool equal = (a == b);

  if(k == 0) {
    cout << (equal ? "YES" : "NO") << nl;
    return;
  }

  if(n == 2) {
    if(a[0] == a[1]) {
      cout << "YES" << nl;
    } else {
      cout << ((k % 2 == 0) == equal ? "YES" : "NO") << nl;
    }
    return;
  }

  basic_string a_str(begin(a), end(a));
  a_str += a_str;
  suffix_array sa(a_str);

  basic_string b_str(begin(b), end(b));
  b_str += b_str;
  suffix_array sb(b_str);

  if(k == 1 && equal) {
    bool periodic = [n, &sa, &a_str]() -> bool {
      vector<int> rots;
      for(int i=0; i<2*n && size(rots)<2; i++) {
        if(sa[i] < n) {
          rots.push_back(sa[i]);
        }
      }
      assert(size(rots) == 2);
      // got the two smallest rotations
      return a_str.substr(rots[0], n) == a_str.substr(rots[1], n);
    }();
    cout << (periodic ? "YES" : "NO") << nl;
    return;
  }

  auto min_rotation = [n](vector<int>& s, auto& suf) -> vector<int>& {
    for(int i=0; i<2*n; i++) {
      if(suf[i] < n) {
        rotate(begin(s), begin(s) + suf[i], end(s));
        return s;
      }
    }
    assert(false);
  };
  cout << (min_rotation(a, sa) == min_rotation(b, sb) ? "YES" : "NO") << nl;

  return;
}

void initialize() {
}

