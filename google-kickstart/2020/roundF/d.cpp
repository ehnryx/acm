#pragma GCC optimize("O3")
#pragma GCC optimize("fast-math")
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
typedef /*long*/ double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

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

template <class T>
vector<T> read_array(int n, int s=1) {
  vector<T> a(n + 2*s);
  for(int i=0; i<n; i++) {
    cin >> a[s+i];
  }
  return a;
}

template <class T>
vector<vector<T>> read_grid(int n, int m, int s=1, int t=1) {
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
    cerr << "Solving case " << cc << nl;
    auto start = chrono::steady_clock::now();

    cout << "Case #" << cc << ": ";
    solve_case();

    cerr << "Time: " << (chrono::steady_clock::now() - start) / 1.0s << "s" << nl << nl;
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////

ll hsh(const vector<int>& v) {
  int n = v.size();
  static const int P = 101;
  ll ha = 0;
  for(int i=0; i<n; i++) {
    ha = (ha * P + v[i]) % MOD;
  }
  return ha;
}

void solve_case() {

  int n, m, k;
  cin >> n >> m >> k;

  auto vals = read_array<int>(k, 0);
  sort(vals.begin(), vals.end(), greater<int>());

  unordered_map<ll,ld> dp;
  function<ld(vector<int>)> solve = [&](const vector<int>& v) -> ld {
    auto ha = hsh(v);
    if(dp.count(ha)) return dp[ha];
    for(int i=0; i<v.size(); i++) {
      if(v[i] > vals[i]) return dp[ha] = INF;
    }
    if(accumulate(v.begin(), v.end(), 0) == n) return dp[ha] = 0;

    vector<pair<ld,vector<int>>> nxt;
    for(int i=0; i<v.size(); i++) {
      vector<int> cur = v;
      cur[i] += 1;
      for(int j=i; j>0 && cur[j]>cur[j-1]; j--) {
        swap(cur[j], cur[j-1]);
      }
      nxt.emplace_back(1/(ld)m, cur);
    }
    int tot = nxt.size();
    if(v.size() < m && v.size() < vals.size()) {
      vector<int> cur = v;
      cur.push_back(1);
      nxt.emplace_back((m-v.size())/(ld)m, cur);
      tot = m;
    }

    ld l = 1;
    ld r = n*m;
    for(int bs=0; bs<32; bs++) {
      ld guess = (l+r)/2;
      ld res = 1;
      for(const auto& [p, w] : nxt) {
        res += min(solve(w), guess) * p;
      }
      res *= m / (ld)tot;
      if(res < guess) {
        r = guess;
      } else {
        l = guess;
      }
    }
    return dp[ha] = r;
  };

  cout << solve({}) << nl;

  return;
}

void initialize() {
}

