#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// DON'T USE THESE MACROS DURING ICPC PRACTICE
#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
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
  int a,b,c;
};

const int N = 2500+1;
const int M = 5e3+1;
int dist[N], rev[N];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n,m,p;
  cin>>n>>m>>p;

  vector<Edge> edges;
  For(i,m) {
    int a,b,c;
    cin>>a>>b>>c;
    edges.push_back({a,b,p-c});
  }

  memset(dist,INF,sizeof dist);
  memset(rev,INF,sizeof rev);
  dist[1] = 0;
  rev[n] = 0;
  For(i,n-1) {
    for (const Edge& e : edges) {
      dist[e.b] = min(dist[e.b], dist[e.a]+e.c);
      rev[e.a] = min(rev[e.a], rev[e.b]);
    }
  }
  for (const Edge& e : edges) {
    if (dist[e.a]<INF/2 && rev[e.b]<INF/2) {
      if (dist[e.a]+e.c < dist[e.b]) {
        cout << -1 << nl;
        return 0;
      }
    }
  }
  cout << max(0, -dist[n]) << nl;

  return 0;
}
