//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "morpher"

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

const int M = 1789;
const int N = 10;
const int L = 20;
string f[N];
int in[N], to[N];

string convert(string s, int k) {
  while(k--) {
    string res;
    for(char c : s) {
      res += f[c-'A'];
    }
    if(res.size() > L) {
      res.resize(L);
    }
    s = move(res);
  }
  return s;
}

vector<int> get_cycle(int s) {
  vector<int> res = {s};
  for(int u = f[s][0]-'A'; u != s; u = f[u][0]-'A') {
    res.push_back(u);
    assert(res.size() <= N);
  }
  return res;
}

string jump(const string& s, int k) {
  string res;
  for(char c : s) {
    vector<int> cyc = get_cycle(c - 'A');
    int len = cyc.size();
    res.push_back(cyc[k % len] + 'A');
    if(in[c-'A'] == 0) break;
  }
  return res;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n, k, x;
  cin >> n >> k >> x;
  string s;
  cin >> s;
  memset(to, -1, sizeof to);
  for(int i=0; i<n; i++) {
    cin >> f[i];
    if(f[i].size() == 1) {
      to[i] = f[i][0] - 'A';
      in[to[i]]++;
    }
  }

  queue<int> bfs;
  for(int i=0; i<n; i++) {
    if(in[i] == 0) {
      bfs.push(i);
    }
  }
  while(!bfs.empty()) {
    int u = bfs.front();
    bfs.pop();
    if(to[u] == -1) continue;
    if(--in[to[u]] == 0) {
      bfs.push(to[u]);
    }
  }

  if(k < M*7) {
    s = convert(s, k);
  } else {
    s = convert(s, M);
    s = jump(s, k - 2*M);
    s = convert(s, M);
  }

  s.resize(x, '-');
  cout << s[x-1] << nl;
  //cerr<<"result: "<<s<<nl;

  return 0;
}
