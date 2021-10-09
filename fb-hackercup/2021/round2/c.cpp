//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
random_device _rd; mt19937 rng(_rd());

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1e9+7;
constexpr ld EPS = 1e-9;

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

#include "../../../../lca/data_structure/segment_tree.h"

struct node_sum {
  int sum, length;
  node_sum() = default;
  void put(int v) { sum += v; }
  int get() const { return sum; }
  void pull(const node_sum& a, const node_sum& b) {
    sum = a.sum + b.sum;
  }
  static int default_value() { return 0; }
  static int merge(int a, int b) { return a + b; }
  bool contains(int& r) const {
    if(sum > r) {
      return true;
    } else {
      r -= sum;
      return false;
    }
  }
};

struct node_min {
  int val, lazy;
  node_min() = default;
  void put(int v) {
    val += v;
    lazy += v;
  }
  int get() const { return val; }
  void push(node_min& a, node_min& b) {
    if(lazy) {
      a.put(lazy);
      b.put(lazy);
      lazy = 0;
    }
  }
  void pull(const node_min& a, const node_min& b) {
    val = min(a.val, b.val);
  }
  static int default_value() { assert(false); }
  static int merge(int a, int b) { return min(a, b); }
};

vector<int> solve(vector<vector<char>> g, int n, int m, int row,
    const vector<pair<int, int>>& upds) {
  row -= 1; // 0 index it
  cerr << "SOLVE row = " << row << nl;

  segment_tree<node_min, int> st(n);
  vector<int> offset(m), fid(m);
  for(int i=0; i<n; i++) { // shift #n
    // calc ans
    int cur = 0;
    for(int j=0; j<m; j++) {
      if(row < offset[j]) {
        cur += 1;
      } else {
        int k = fid[j] + row - offset[j];
        if(k < n && g[k][j] == 'X') {
          cur += 1;
        }
      }
    }
    // update
    st.update_point(i, i + cur);
    cerr << "init " << i << " = " << i+cur << nl;
    // shift
    for(int j=0; j<m; j++) {
      while(fid[j] < n && g[fid[j]][j] == 'X') {
        offset[j]++;
        fid[j]++;
      }
      if(fid[j] < n) {
        fid[j]++;
      }
    }
  }

  vector col(m, segment_tree<node_sum, int, false>(n));
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      if(g[i][j] == 'X') {
        col[j].update_point(i, 1);
      }
    }
  }

  vector<int> ans;
  ans.reserve(size(upds));
  for(auto [a, b] : upds) {
    a -= 1; // 0 index it
    b -= 1; // 0 index it

    // at what time will row be covered entirely?
    int last = col[b].search_left(0, n-1, row);
    cerr << "last = " << last << " vs " << row << nl;
    if(last < n) {
      st.update(last - row, n-1, -1); // undo cover
      cerr << "PUT " << last - row << " ... with -1" << nl;
      last = last - row;
    }

    // update now ?
    g[a][b] ^= 'X' ^ '.';
    int dx = (g[a][b] == 'X' ? 1 : -1);
    col[b].update_point(a, dx);

    // at what time will row be covered entirely?
    int new_last = col[b].search_left(0, n-1, row);
    if(new_last < n) {
      st.update(new_last - row, n-1, 1); // redo cover
      cerr << "PUT " << new_last - row << " ... with +1" << nl;
      new_last = new_last - row;
    }

    int blocks = col[b].query(0, a-1);
    int gaps = a - blocks;
    int need = a - row; // number of gaps needed to get to row
    if(row <= a && need <= gaps) {
      cerr << "dx " << dx << " " << need << " vs " << last << " " << new_last << nl;
      if((dx < 0 && need != last) || (dx > 0 && need != new_last)) {
        st.update_point(need, dx);
        cerr << "update at " << need << " -> " << dx << nl;
      }
    }

    ans.push_back(st.query(0, n-1));
    cerr << "query gets " << ans.back() << nl;
  }

  return ans;
}

void solve_case() {

  cerr << nl;

  int n, m, row, s;
  cin >> n >> m >> row >> s;

  vector g(n, vector<char>(m));
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> g[i][j];
    }
  }

  vector<pair<int, int>> upds;
  for(int i=0; i<s; i++) {
    int a, b;
    cin >> a >> b;
    upds.emplace_back(a, b);
  }

  vector<int> up = solve(g, n, m, row, upds);
  reverse(begin(g), end(g));
  for(auto& [a, b] : upds) {
    a = n - a + 1; // reflect
  }
  vector<int> down = solve(g, n, m, n - row + 1, upds);

  ll ans = 0;
  for(int i=0; i<s; i++) {
    ans += min(up[i], down[i]);
    cerr << i << ": " << up[i] << " vs " << down[i] << " -> " << min(up[i], down[i]) << nl;
  }
  cout << ans << nl;

  return;
}

void initialize() {
}

