#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1e5+1;
vector<int> adj[N];
map<int,deque<int>> to[N];
int leaf[N], par[N];

int precmp(int u, int p) {
  par[u] = p;
  leaf[u] = (adj[u].size() == 1);
  for (int v : adj[u]) {
    if (v!=p) {
      leaf[u] += precmp(v, u);
      to[u][leaf[v]].push_back(v);
    }
  }
  return leaf[u];
}

vector<int> todo;

int get(int u, int r) {
  if (to[u].empty()) {
    return u;
  }

  auto it = prev(to[u].end());
  int nxt = it->second.back();
  it->second.pop_back();
  if (it->second.empty()) {
    to[u].erase(it);
  }

  if (u != r) {
    todo.push_back(u);
  }
  return get(nxt, r);
}

void update(int r) {
  for (int u : todo) {
    for (const auto& jt : to[u]) {
      for (int add : jt.second) {
        to[r][jt.first].push_front(add);
      }
    }
    to[u].clear();
  }
  todo.clear();
}

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n, r;
  cin >> n >> r;

  For(i,n-1) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  precmp(r, -1);

  vector<pii> ans;
  while (!to[r].empty()) {
    if (to[r].size() == 1 && to[r].begin()->second.size() == 1) {
      int u = get(r, r);
      ans.push_back(pii(u,r));
    } else {
      int u = get(r, r);
      int v = get(r, r);
      ans.push_back(pii(u,v));
    }
    update(r);
  }

  cout << ans.size() << nl;
  for (const pii& it : ans) {
    cout << it.first << " " << it.second << nl;
  }

  return 0;
}
