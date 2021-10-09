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

struct Edge {
  int i, d, c;
  bool operator < (const Edge& o) const {
    return d > o.d;
  }
};

const int N = 345;
vector<Edge> adj[N];
int dist[N][1<<7];

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  unordered_map<char,int> col;
  col['R'] = 0;
  col['O'] = 1;
  col['Y'] = 2;
  col['G'] = 3;
  col['B'] = 4;
  col['I'] = 5;
  col['V'] = 6;
  int goal = (1<<7)-1;

  int n, m;
  cin >> n >> m;

  for (int i=0; i<m; i++) {
    int a, b, d; char c;
    cin >> a >> b >> d >> c;
    adj[a].push_back({b,d,col[c]});
    adj[b].push_back({a,d,col[c]});
  }

  memset(dist, -1, sizeof dist);
  priority_queue<Edge> dijk;
  dijk.push({1,0,0});
  while (!dijk.empty()) {
    Edge cur = dijk.top();
    dijk.pop();
    if (cur.i == 1 && cur.c == goal) {
      cout << cur.d << nl;
      return 0;
    }
    if (dist[cur.i][cur.c] == -1) {
      dist[cur.i][cur.c] = cur.d;
      for (const Edge& e : adj[cur.i]) {
        dijk.push({e.i, e.d+cur.d, 1<<e.c|cur.c});
      }
    }
  }
  assert(false);

  return 0;
}
