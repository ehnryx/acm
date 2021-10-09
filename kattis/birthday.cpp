#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 101;
int root[N];
int find(int i) {
  if (root[i] == -1) return i;
  return root[i] = find(root[i]);
}
bool link(int i, int j) {
  i = find(i); j = find(j);
  if (i == j) return false;
  root[i] = j;
  return true;
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

  for (int p,c; cin>>p>>c && p;) {
    vector<pii> edges;
    for (int i=0; i<c; i++) {
      int a, b;
      cin >> a >> b;
      edges.push_back({a,b});
    }
    bool ok = true;
    for (const pii& exclu : edges) {
      memset(root, -1, sizeof(root));
      int cnt = 0;
      for (const pii& e : edges) {
        if (e != exclu) {
          cnt += link(e.first, e.second);
        }
      }
      if (cnt < p-1) {
        ok = false;
        break;
      }
    }
    cout << (ok ? "No" : "Yes") << nl;
  }

  return 0;
}
