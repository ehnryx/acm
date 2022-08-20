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

void solve_case(int, int);
void initialize();

////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  initialize();

  int T;
  cin >> T;
  int n, k;
  cin >> n >> k;
  for (int cc = 1; cc <= T; cc++) {
    auto start = chrono::steady_clock::now();
    //cout << "Case #" << cc << ": ";
    solve_case(n, k);
    if(argc > 1 && argv[1][0] == 't') {
      cerr << "Time: " << (chrono::steady_clock::now() - start) / 1.0s << "s" << nl << nl;
    }
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////



void solve_case(int n, int /*k*/) {

  vector<int> a(n+1), c(n+1);
  for(int i=1; i<=n; i++) {
    cin >> a[i];
  }

  while(true) {
    vector<vector<int>> cycles;
    for(int i=1; i<=n; i++) {
      if(c[i]) continue;
      vector<int> cyc;
      for(int j=a[i]; j!=i; j=a[j]) {
        c[j] = true;
        cyc.push_back(j);
      }
      c[i] = true;
      cyc.push_back(i);
      if(size(cyc) > 1) {
        cycles.push_back(move(cyc));
      }
    }

    fill(begin(c), end(c), 0);
    int cid = 1;
    for(const auto& cyc : cycles) {
      for(int i : cyc) {
        c[i] = cid;
      }
      cid++;
    }
    for(int i=1; i<=n; i++) {
      if(!c[i]) c[i] = cid++;
      cout << c[i] << " ";
    }
    cout << endl;

    int solved;
    cin >> solved;
    if(solved) {
      if(solved == -1) exit(0);
      break;
    }
    for(int i=1; i<=n; i++) {
      cin >> a[i];
    }
    fill(begin(c), end(c), 0);
  }

  return;
}

void initialize() {
}

