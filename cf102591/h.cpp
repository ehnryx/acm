#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

// MAGIC IO
inline char get(void) {
  static char buf[100000], *S = buf, *T = buf;
  if (S == T) {
    T = (S = buf) + fread(buf, 1, 100000, stdin);
    if (S == T) return EOF;
  }
  return *S++;
}
template <typename T> inline void read(T &x) {
  static char c; x = 0; int sgn = 0;
  for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
  for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
  if (sgn) x = -x;
}
void readchar(char& c) {
  while (isspace(c = get()));
}
// END MAGIC IO

const int M = 1e6 + 1;
const int N = 1e3 + 1;
int g[N][N];
vector<pair<int,int>> vals[M];

// TODO
// double-check correctness
// read limits carefully
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  vector<int> primes;
  for(int i=2; i*i<M; i++) {
    bool ok = true;
    for(int j=2; j<i; j++) {
      if(i%j == 0) {
        ok = false;
        break;
      }
    }
    if(ok) {
      primes.push_back(i);
    }
  }

  function<vector<int>(int)> prime_factor = [=](int v) {
    vector<int> factors;
    for(int p : primes) {
      if(p*p > v) break;
      if(v%p == 0) {
        factors.push_back(p);
        while(v%p == 0) {
          v /= p;
        }
      }
    }
    if(v > 1) {
      factors.push_back(v);
    }
    return factors;
  };

  int n, m;
  //cin >> n >> m;
  read(n); read(m);
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      //cin >> g[i][j];
      read(g[i][j]);
    }
  }

  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      for(int v : prime_factor(g[i][j])) {
        vals[v].emplace_back(i, j);
      }
    }
  }

  ll ans = 0;
  unordered_map<int,int> pre, cur;
  vector<pair<int,int>> stk;
  stk.reserve(n+m);
  for(int v=2; v<M; v++) {
    if(vals[v].empty()) continue;
    pre.clear();
    cur.clear();
    stk.clear();
    int area = 0;

    for(int i=0; i<vals[v].size(); i++) {
      if(i > 0 && vals[v][i].first != vals[v][i-1].first) {
        area = 0;
        stk.clear();

        if(vals[v][i].first == vals[v][i-1].first + 1) {
          pre = move(cur);
          cur.clear();
        } else {
          pre.clear();
          cur.clear();
        }
      }
      if(i > 0 && vals[v][i].second != vals[v][i-1].second + 1) {
        area = 0;
        stk.clear();
      }

      int j = vals[v][i].second;
      int bot = vals[v][i].first;
      int top = cur[j] = pre.count(j) ? pre[j] : bot;
      int left = j;
      while(!stk.empty() && top > stk.back().first) {
        left = stk.back().second;
        int ctop = stk.back().first;
        stk.pop_back();
        int second = stk.empty() ? bot-1 : stk.back().first;
        area -= (j - left) * (second - ctop);
      }
      if(stk.empty() || top < stk.back().first) {
        bot = stk.empty() ? bot-1 : stk.back().first;
        stk.emplace_back(top, left);
        area += (j - left) * (bot - top);
      }
      area += vals[v][i].first - stk.back().first + 1;
      ans += area;
    }
  }

  cout << ans << nl;

  return 0;
}
