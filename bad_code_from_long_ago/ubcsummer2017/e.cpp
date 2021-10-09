#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG
#define USE_MAGIC_IO
#ifdef USE_MAGIC_IO
inline char get(void) {
  static char buf[100000], *S = buf, *T = buf;
  if (S == T) {
    T = (S = buf) + fread(buf, 1, 100000, stdin);
    if (S == T) return EOF;
  }
  return *S++;
}
inline void read(int &x) {
  static char c; x = 0; int sgn = 0;
  for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
  for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
  if (sgn) x = -x;
}
#else
#define get() getchar()
#define read(x) scanf("%d",&x)
#endif

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

struct DSU {
  vector<int> root;
  vector<int> weight;
  DSU(int n) {
    root.resize(n);
    memset(&root[0], -1, n*sizeof(root[0]));
    weight.resize(n);
    memset(&weight[0], 0, n*sizeof(weight[0]));
  }
  int find(int i) {
    if (root[i] == -1) return i;
    else return root[i] = find(root[i]);
  }
  void link(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return;
    if (weight[a] < weight[b]) swap(a,b);
    root[b] = a;
    weight[a] += weight[b]+1;
  }
};

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  int lim, sz;
  int n, total;
  cin >> n;
  int a[n], b[n];
  DSU dsu(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i]; a[i]--;
    dsu.link(i, a[i]);
  }
  // get groups
  total = 0;
  map<int,int> group;
  map<int,vector<int>> cycle;
  for (int i = 0; i < n; i++) {
    if (dsu.find(i) == i) {
      total++;
      cycle[i];
      sz = dsu.weight[i]+1;
      lim = sqrt(sz);
      group[sz] = -1;
      for (int j = 2; j <= lim; j++) {
        if (sz%j == 0) {
          group[j] = -1;
          group[sz/j] = -1;
        }
      }
    }
  }
  // find cycles
  for (int i = 0; i < n; i++) {
    if (dsu.find(i) == i) {
      int curr = a[i];
      while (curr != i) {
        cycle[i].push_back(curr);
        curr = a[curr];
      } cycle[i].push_back(curr);
    }
  }
  // input next
  for (int i = 0; i < n; i++) {
    cin >> b[i]; b[i]--;
  }
  // check cycles
  int good = 0;
  bitset<1000001> visited;
  for (int i = 0; i < n; i++) {
    int root = dsu.find(i);
    if (dsu.find(b[i]) == root && !visited[root]) {
      visited[root] = true;
      good++;
      int curr = i;
      int dist = 0;
      while (curr != b[i]) {
        curr = a[curr];
        dist++;
      }
      sz = dsu.weight[root]+1;
      // check cycle
      curr = i;
      for (int j = 0; j < sz; j++) {
        if (cycle[root][(sz-1+j)%sz] != b[curr]) {
          cout << "NO" << nl;
          return 0;
        }
        curr = a[curr];
      }
      // check
      lim = sqrt(sz);
      if (group[sz] == -1) group[sz] = dist;
      if (group[sz] != dist) {
        cout << "NO" << nl;
        return 0;
      }
      for (int j = 2; j <= lim; j++) {
        if (sz%j == 0) {
          if (group[j] == -1) group[j] = dist%j;
          if (group[sz/j] == -1) group[sz/j] = dist%(sz/j);
          if (group[j] != dist%j || group[sz/j] != dist%(sz/j)) {
            cout << "NO" << nl;
            return 0;
          }
        }
      }
    }
  }
  if (good != total) {
    cout << "NO" << nl;
  }
  else {
    cout << "YES" << nl;
  }

  return 0;
}
