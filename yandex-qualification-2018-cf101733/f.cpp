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

const int N = 2e5+1;
vector<int> adj[N];
int dist[N], chain[N], deg[N];

int solve(int n, int s, int block, int& res) {
  memset(deg, 0, sizeof deg);
  memset(dist, -1, sizeof dist);
  dist[block] = 0;

  queue<int> bfs;
  dist[s] = 0;
  bfs.push(s);
  while (!bfs.empty()) {
    int cur = bfs.front();
    bfs.pop();
    deg[cur] = adj[cur].size() - (s == cur);
    for (int x : adj[cur]) {
      if (dist[x] == -1) {
        dist[x] = dist[cur]+1;
        bfs.push(x);
      }
    }
  }

  //cerr << "leaves: ";
  int pre, last = 0;
  for (int i=1; i<=n; i++) {
    if (deg[i] == 1) {
      dist[i] = 0;
      bfs.push(i);
      //cerr << i << " ";
    }
  }
  //cerr << nl;
  while (!bfs.empty()) {
    int cur = bfs.front();
    bfs.pop();
    pre = last;
    last = cur;
    deg[cur] = 0;
    for (int x : adj[cur]) {
      deg[x]--;
      if (deg[x] == 1) {
        dist[x] = dist[cur]+1;
        bfs.push(x);
      }
    }
  }

  if (last == 0) {
    last = s;
    res = 0;
  } else {
    res = dist[last] + (dist[last] == dist[pre]);
  }
  //cerr << "solve " << s << " block " << block << " -> " << last << " w/ " << dist[last] << nl;
  return last;
}

pii split(int n, int s, const vector<int>& diam, int& res) {
  int left, right;
  int a = solve(n, diam[s-1], diam[s], left);
  int b = solve(n, diam[s], diam[s-1], right);
  res = max(left,right);
  //cerr << "SPLIT " << s << " -> " << a << " " << b << " w/ " << res << nl << nl;
  return pii(a,b);
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

  int n, a, b;
  cin >> n;

  for (int i=1; i<n; i++) {
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  int last, other;
  queue<int> bfs;

  memset(dist, -1, sizeof dist);
  dist[1] = 0;
  bfs.push(1);
  while (!bfs.empty()) {
    int cur = bfs.front();
    bfs.pop();
    last = cur;
    for (int x : adj[cur]) {
      if (dist[x] == -1) {
        dist[x] = dist[cur]+1;
        bfs.push(x);
      }
    }
  }

  memset(dist, -1, sizeof dist);
  dist[last] = 0;
  bfs.push(last);
  while (!bfs.empty()) {
    int cur = bfs.front();
    bfs.pop();
    other = cur;
    for (int x : adj[cur]) {
      if (dist[x] == -1) {
        dist[x] = dist[cur]+1;
        chain[x] = cur;
        bfs.push(x);
      }
    }
  }

  vector<int> diam;
  for (int i = other; i != last; i = chain[i]) {
    diam.push_back(i);
  }
  diam.push_back(last);
  int m = diam.size();
  //cerr << "DIAMETER: "; for (int i : diam) //cerr << i << " ";
  //cerr << nl << nl;

  int dleft, dright;
  int left, mid, right;
  left = 1;
  right = m-1;
  while (left <= right) {
    mid = (left+right)/2;
    solve(n, diam[mid-1], diam[mid], dleft);
    solve(n, diam[mid], diam[mid-1], dright);
    if (dleft < dright) left = mid+1;
    else right = mid-1;
  }

  int smaller, res, larger;
  split(n, max(1,mid-1), diam, smaller);
  split(n, mid, diam, res);
  split(n, min(m-1,mid+1), diam, larger);

  vector<int> v = {smaller, res, larger};
  sort(v.begin(), v.end());

  if (v[0] == smaller) {
    tie(a,b) = split(n, max(1,mid-1), diam, smaller);
  } else if (v[0] == res) {
    tie(a,b) = split(n, mid, diam, res);
  } else {
    tie(a,b) = split(n, min(m-1,mid+1), diam, larger);
  }

  cout << a << " " << b << nl;

  return 0;
}
