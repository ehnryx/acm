#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "tilings"

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

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  os << "[";
  for(const T& it : v) {
    os << " " << (int)it << ", ";
  }
  return os << "]";
}

const vector<int> di = { 0, 0, 1, -1 };
const vector<int> dj = { 1, -1, 0, 0 };

const int M = 4;
const int N = 52;
bool g[N][N], gg[2*N][2*N];

int dsu[4*N*N];
int find(int i) {
  if(dsu[i] == -1) return i;
  return dsu[i] = find(dsu[i]);
}
int link(int i, int j) {
  if(find(i) == find(j)) return 0;
  dsu[find(i)] = find(j);
  return 1;
}

int fail[N*N*M];
void kmp_init(char v[], int n) {
  memset(fail, 0, sizeof fail);
  for(int i=0, j=-1; ; i++, j++) {
    fail[i] = j;
    if(i == n) return;
    while(j>=0 && v[i]!=v[j]) j = fail[j];
  }
}
bool kmp_match(char t[], int n, char v[], int m) {
  for(int i=0, j=0; ; i++, j++) {
    if(j == m) return true;
    if(i == n) return false;
    while(j >= 0 && t[i] != v[j]) j = fail[j];
  }
  return false;
}

vector<tuple<int,int,int,int>> edges;
pair<int,int> to[M*N][M*N];
char last[M*N][M*N];

int get_pat(char v[], int s, int t, int start, int goal, bool rev) {
  int i = 0;
  while(last[s][t] != start) {
    tie(s, t) = to[s][t];
  }
  while(last[s][t] != goal) {
    auto [ns, nt] = to[s][t];
    if(rev) v[i++] = (ns == s ? (nt < t ? 0 : 1) : (ns < s ? 2 : 3));
    else v[i++] = (ns == s ? (nt > t ? 0 : 1) : (ns > s ? 2 : 3));
    tie(s, t) = to[s][t];
  }
  if(rev) reverse(v, v+i);
  return i;
}

bool solve(int s, int t) {
  memset(last, -1, sizeof last);
  static char hay[N*N*2], pat[N*N];
  int hlen = 0, plen = 0;

  for(int i=0; i<M; i++) {
    for(auto [a, b, x, y] : edges) {
      to[a+s*i][b+t*i] = make_pair(x+s*i, y+t*i);
      last[a+s*i][b+t*i] = i;
    }
  }
  for(int i=0; i<N && !hlen; i++) {
    for(int j=0; j<N && !hlen; j++) {
      if(last[i][j] == 0) {
        hlen = get_pat(hay, i, j, 1, M-1, false);
      }
    }
  }

  for(int i=M-1; i>=0; i--) {
    for(auto [a, b, x, y] : edges) {
      to[a+s*i][b+t*i] = make_pair(x+s*i, y+t*i);
      last[a+s*i][b+t*i] = i;
    }
  }
  for(int i=0; i<N && !plen; i++) {
    for(int j=0; j<N && !plen; j++) {
      if(last[i+(M-1)*s][j+(M-1)*t] == M-1) {
        plen = get_pat(pat, i+(M-1)*s, j+(M-1)*t, M-2, 1, true);
      }
    }
  }

  kmp_init(pat, plen);
  return kmp_match(hay, hlen, pat, plen);
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  for(int i=0; i<N; i++) {
    string s;
    if(cin >> s) {
      for(int j=0; j<s.size(); j++) {
        if(s[j] == '*') {
          g[i+1][j+1] = 1;
        }
      }
    }
  }

  for(int i=1; i+1<N; i++) {
    for(int j=1; j+1<N; j++) {
      if(!g[i][j]) continue;
      if(!g[i-1][j]) edges.emplace_back(i-1, j-1, i-1, j);
      if(!g[i+1][j]) edges.emplace_back(i, j, i, j-1);
      if(!g[i][j-1]) edges.emplace_back(i, j-1, i-1, j-1);
      if(!g[i][j+1]) edges.emplace_back(i-1, j, i, j);
    }
  }

  for(int s=0; s<N; s++) {
    for(int t=0; t<N; t++) {
      bool ok = true;
      memset(gg, 0, sizeof gg);
      for(int i=0; i<N && ok; i++) {
        for(int j=0; j<N && ok; j++) {
          gg[i][j] |= g[i][j];
          gg[i+s][j+t] |= g[i][j];
          if(s<=i && t<=j && g[i][j] && g[i-s][j-t]) {
            ok = false;
            break;
          }
        }
      }

      if(ok) {
        memset(dsu, -1, sizeof dsu);
        int groups = 0;
        for(int i=0; i<N+s; i++) {
          for(int j=0; j<N+t; j++) {
            groups++;
            for(int d=0; d<4; d++) {
              int ni = i + di[d];
              int nj = j + dj[d];
              if(0<=ni && ni<N+s && 0<=nj && nj<N+t && gg[i][j]==gg[ni][nj]) {
                groups -= link(i*2*N + j, ni*2*N + nj);
              }
            }
          }
        }

        if(groups == 2 && solve(s, t)) {
          cout << "YES" << nl;
          return 0;
        }
      }
    }
  }

  cout << "NO" << nl;

	return 0;
}
