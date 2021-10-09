#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
#define nl '\n'

const int N = 1e4+1;
vector<int> adj[N];
bool primes[N];
int dist[N];

int bfs(int s, int t) {
  memset(dist, -1, sizeof dist);
  queue<int> nxt;
  nxt.push(s);
  dist[s] = 0;
  while(!nxt.empty()) {
    int u = nxt.front();
    nxt.pop();
    if(u == t) {
      return dist[u];
    }
    for(int v:adj[u]) {
      if(dist[v] == -1) {
        dist[v] = dist[u] + 1;
        nxt.push(v);
      }
    }
  }
  return -1;
}

int hamming(int a, int b) {
  int res = 0;
  for(int i=1; i<N; i*=10) {
    res += ((a/i)%10 != (b/i)%10);
  }
  return res;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  for(int i=1000; i<=9999; i++) {
    bool ok = true;
    for(int j=2; j*j<=i; j++) {
      ok &= (i%j != 0);
    }
    if(ok) {
      primes[i] = true;
      for(int j=1000; j<i; j++) {
        if(primes[j] && hamming(i,j) == 1) {
          adj[i].push_back(j);
          adj[j].push_back(i);
        }
      }
    }
  }

  int T;
  cin >> T;
  while(T--) {
    int a, b;
    cin >> a >> b;
    int ans = bfs(a, b);
    if(ans == -1) cout << "Impossible" << nl;
    else cout << ans << nl;
  }

  return 0;
}
