#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
const int N = 4e5+100, K = 1e5+10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

vector<int> adj[N];
int level[N];
bool vis[N];
unordered_map<int, int> dist[K];

unordered_map<int, int> dp1[K];
int dp2[N];

int solve2(int);
int solve(int line, int stop) {
  if (dp1[line].count(stop)) return dp1[line][stop];
  int cur = dist[line][stop];
  int ans = 0;
  for (const auto& p : dist[line]) {
    if (level[p.first] > level[line]) {
      ans = max(ans, solve2(p.first) + abs(p.second - cur));
    }
  }
  return dp1[line][stop] = ans;
}
int solve2(int stop) {
  if (dp2[stop] != -1) return dp2[stop];
  int ans = 0;
  for (int i : adj[stop]) {
    //cerr << stop-K << " " << i << " " << level[stop] << " " << level[i] <<endl;
    if (level[i] > level[stop]) {
      ans = max(ans, solve(i, stop));
    }
  }
  return dp2[stop] = ans;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int T; cin >> T;
  string s; getline(cin, s);
  while (T--) {
    memset(adj, 0, sizeof adj);
    memset(level, 0, sizeof level);
    memset(vis, 0, sizeof vis);
    memset(dp2, -1, sizeof dp2);
    getline(cin, s);
    getline(cin, s);

    map<string, int> lines, stops;
    {
      istringstream in(s); in >> s;
      int id = 0;
      while (in >> s) {
        if (s.back() == ',') s.pop_back();
        //cerr << "stop " << id << " " << s << endl;
        stops[s] = id++;
      }
    }
    getline(cin, s);
    int n = 0;
    {
      istringstream in(s); in >> s;
      while (in >> s) {
        if (s.back() == ',') s.pop_back();
        //cerr << "line " << n << " " << s << endl;
        lines[s] = n++;
      }
    }
    fill(dp1, dp1 + n + 1, unordered_map<int, int>());
    fill(dist, dist + n + 1, unordered_map<int, int>());

    for (int i = 0; i < n; i++) {
      getline(cin, s);
      istringstream in(s); in >> s >> s;
      int d = 0;
      while (in >> s) {
        if (s.back() == ',') s.pop_back();
        assert(stops.count(s));
        dist[i][stops[s] + K] = d++;
        adj[i].push_back(stops[s] + K);
        adj[stops[s] + K].push_back(i);
      }
    }

    string startn, endn;
    getline(cin, s);
    {
      istringstream in(s);
      in >> s >> s >> s >> startn;
    }
    int start = stops[startn];
    getline(cin, s);
    {
      istringstream in(s);
      in >> s >> s >> s >> endn;
    }
    int end = stops[endn];
    queue<int> q;
    q.push(start + K);
    vis[start+K] = 1;
    while (!q.empty()) {
      int cur = q.front(); q.pop();
      for (int i : adj[cur]) {
        if (!vis[i]) {
          vis[i] = 1;
          level[i] = level[cur]+1;
          q.push(i);
        }
      }
    }
    int linessss = (int)level[end+K]/2;
    for (const auto& it : stops) {
      if (level[it.second+K] == level[end+K] && it.second != end) {
        dp2[it.second+K] = -INF;
      }
    }
    dp2[end+K] = 0;
    int ans = solve2(start + K);
    cout << "optimal travel from " << startn << " to " << endn << ": ";
    cout << linessss << " " << (linessss > 1 ? "lines" : "line") << ", ";
    cout << ans << " " << (ans > 1 ? "minutes" : "minute") << nl;
  }

  return 0;
}
