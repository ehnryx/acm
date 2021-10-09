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

const int N = 200;
int adj[N][N];

void init() {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      adj[i][j] = 1;
    }
  }
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
  init();

  int n, m;
  cin >> n >> m;

  unordered_map<string,int> id;
  int num = 1;

  string s, t, $;
  for (int i = 0; i < n; i++) {
    cin >> s >> $ >> $ >> $ >> t;
    if (!id.count(s)) id[s] = num++;
    if (!id.count(t)) id[t] = num++;
    adj[id[s]][id[t]] = 0;
  }

  for (int k = 0; k <= num; k++) {
    for (int i = 0; i <= num; i++) {
      for (int j = 0; j <= num; j++) {
        adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
      }
    }
  }

  for (int i = 0; i < m; i++) {
    cin >> s >> $ >> $ >> $ >> t;
    if (adj[id[s]][id[t]] == 0) {
      cout << "Fact" << nl;
    } else if (adj[id[t]][id[s]] == 0) {
      cout << "Alternative Fact" << nl;
    } else {
      cout << "Pants on Fire" << nl;
    }
  }

  return 0;
}
