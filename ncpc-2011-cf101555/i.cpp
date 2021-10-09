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

const int N = 1e4+1;
int dp[N+420][3];

vector<int> primes;
vector<int> adj[N+420];
int degree[N+420];

void init() {
  bitset<N+420> np;
  int lim = sqrt(N+400);
  np[0] = np[1] = true;
  for (int i = 2; i < lim; i++) {
    if (!np[i]) {
      for (int j = i*i; j < N+400; j += i) {
        np[j] = true;
      }
    }
  }
  for (int i = 0; i < N+400; i++) {
    if (!np[i]) {
      primes.push_back(i);
      if (i >= N) break;
    }
  }

  int n = primes.back();
  for (int i = 2; i <= n; i++) {
    if (!np[i]) {
      adj[1].push_back(i);
      degree[i]++;
    }
    else {
      adj[i+1].push_back(i);
      degree[i]++;
      for (int p : primes) {
        if (i % p == 0) {
          adj[i/p].push_back(i);
          degree[i]++;
        }
      }
    }
  }

  memset(dp, INF, sizeof dp);
  queue<int> nxt;
  nxt.push(1);
  while (!nxt.empty()) {
    int cur = nxt.front();
    nxt.pop();

    for (int x : adj[cur]) {
      if (min(cur, dp[cur][2]) < dp[x][0]) {
        dp[x][0] = min(cur, dp[cur][2]);
        dp[x][1] = dp[cur][0];
        dp[x][2] = dp[cur][1];
      }

      degree[x]--;
      if (degree[x] == 0) {
        nxt.push(x);
      }
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

  map<char,int> cnt;
  cnt['O'] = 0;
  cnt['E'] = 1;
  cnt['I'] = 2;

  int n;
  cin >> n;

  char t;
  int v;
  vector<int> ans(3,0);
  for (int i = 0; i < n; i++) {
    cin >> t >> v;
    int id = cnt[t];
    for (int j = 0; j < 3; j++) {
      ans[(id+j)%3] += min(v, dp[v][j]);
    }
  }

  for (int i = 0; i < 3; i++) {
    cout << ans[i] << " ";
  }
  cout << nl;

  return 0;
}
