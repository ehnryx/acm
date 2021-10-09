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

const int N = 1e3+1;
ll adj[N][N];

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n;
  cin >> n;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> adj[i][j];
    }
  }

  auto get_diff = [&] (int v) {
    ll res = 0;
    for (int i = 0; i < n; i++) {
      res += adj[i][v] - adj[v][i];
    }
    return res;
  };

  auto solve = [&] (int v) {
    int j = 0;
    for (int i = 0; i < n; i++) {
      while (j < n && adj[v][i] > 0) {
        ll change = min(adj[v][i], adj[j][v]);
        adj[v][i] -= change;
        adj[j][v] -= change;
        adj[j][i] += change;
        if (adj[j][v] == 0) j++;
      }
    }
  };

  vector<pii> ppl;
  for (int i = 0; i < n; i++) {
    ppl.push_back(pii(get_diff(i), i));
  }
  sort(ppl.begin(), ppl.end());

  for (const pii& it : ppl) {
    solve(it.second);
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << adj[i][j] << " ";
    }
    cout << nl;
  }

  return 0;
}
