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
  vector h(n+2, vector<int>(m));
  for(int i=1; i<=n; i++) {
    for(int j=0; j<m; j++) {
      cin >> h[i][j]; // height of type j at i
    }
  }

  static constexpr int big = numeric_limits<int>::max();
  vector minh(n+1, vector(n+1, vector<int>(m, big)));
  vector maxh(n+1, vector(n+1, vector<int>(m, 0)));
  vector leaf(n+1, vector<int>(n+1));
  for(int s=1; s<=n; s++) {
    for(int i=s; i<=n; i++) {
      for(int t=0; t<m; t++) {
        minh[s][i][t] = min(minh[s][i-1][t], h[i][t]);
        maxh[s][i][t] = max(maxh[s][i-1][t], h[i][t]);
      }
      leaf[s][i] = true;
      vector<int> at(m);
      vector<pair<int, int>> got;
      for(int ii=s; ii<=i; ii++) {
        for(int t=m-1; t>=0; t--) {
          int diff = h[ii][t] - at[t];
          if(diff < 0) {
            if(got.back() != pair(t, -diff)) {
              leaf[s][i] = false;
              goto quit;
            }
            got.pop_back();
          }
        }
        for(int t=0; t<m; t++) {
          int diff = h[ii][t] - at[t];
          at[t] = h[ii][t];
          if(diff > 0) {
            got.emplace_back(t, diff);
          }
        }
      }
quit:
      ;
    }
  }

  vector<int> sumh(n+1);
  int trivial = 0;
  for(int i=0; i<=n; i++) {
    for(int j=0; j<m; j++) {
      sumh[i] += min(h[i][j], h[i+1][j]);
      trivial += abs(h[i][j] - h[i+1][j]);
    }
  }

  vector dp(n+1, vector<int>(n+1, big));
  for(int d=1; d<=n; d++) {
    for(int s=1; s+d-1<=n; s++) {
      int t = s + d - 1;
      if(leaf[s][t]) {
        dp[s][t] = 0;
        continue;
      }
      int sumhlr = 0;
      for(int j=0; j<m; j++) {
        sumhlr += minh[s][t][j];
      }
      //cerr << "solving " << s << " " << t << nl;
      for(int x=s; x<t; x++) {
        int cost = sumh[x] - sumhlr;
        //cerr << "cost @ " << x << " " << " -> " << cost << nl;
        dp[s][t] = min(dp[s][t], dp[s][x] + dp[x+1][t] + cost);
      }
      //cerr << "dp " << s << " " << t << " -> " << dp[s][t] << nl;
    }
  }

  //cerr << "ans = " << 2 * dp[1][n] << " + " << trivial << nl;
  cout << 2 * dp[1][n] + trivial << nl;

  return;
}

void initialize() {
}

