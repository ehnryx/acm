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

const int N = 1e5+7;

struct Group {
  vector<int> v[3];
};

vector<Group> groups;
vector<int> ans[3];

unordered_set<int> adj[2*N];
bool vis[2*N];
int first[2*N];

void visit(Group& cur, int s, int id) {
  vis[s] = true;
  if (cur.v[id].empty()) first[s] = id;
  cur.v[id].push_back(s);
  for (int t : adj[s]) {
    if (!vis[t]) visit(cur,t,id);
  }
}

void query(const vector<pii>& edges) {
  cout << "Q " << edges.size();
  for (const pii& it : edges) {
    cout << " " << it.first << " " << it.second;
  }
  cout << endl;
  for (int i=0; i<edges.size(); i++) {
    char c;
    cin >> c;
    if (c=='1') {
      //cerr << "add edge " << edges[i].first << " " << edges[i].second << nl;
      adj[edges[i].first].insert(edges[i].second);
      adj[edges[i].second].insert(edges[i].first);
    }
  }
}

void find_groups(int n) {
  memset(first, -1, sizeof first);
  for (int i=0; i<2*N; i++) {
    adj[i].clear();
  }

  // FIRST QUERY
  {
    vector<pii> edges;
    for (int i=1; i<=n; i+=2) {
      if (i+1<=n) {
        edges.push_back(pii(i,i+1));
      }
    }
    query(edges);
  }

  // SECOND QUERY
  {
    vector<pii> edges;
    for (int i=1; i<=n; i += (i%4==1 ? 1 : 3)) {
      if (i+2<=n) {
        edges.push_back(pii(i,i+2));
      }
    }
    query(edges);
  }

  // THIRD QUERY
  {
    vector<pii> edges;
    for (int i=1; i<=n; i += (i%4==1 ? 1 : 3)) {
      if (i%4==1) {
        if (i+3<=n) {
          edges.push_back(pii(i,i+3));
        }
      } else {
        if (i+1<=n) {
          edges.push_back(pii(i,i+1));
        }
      }
    }
    query(edges);
  }

  groups.clear();
  memset(vis, 0, sizeof vis);
  for (int i=1; i<=n; i+=4) {
    Group cur;
    int gid = 0;
    for (int j=0; j<4 && i+j<=n; j++) {
      if (!vis[i+j]) {
        visit(cur, i+j, gid++);
      }
    }
    groups.push_back(cur);
  }
}

void bfs(int n, int m, int s, int id) {
  vis[s] = true;
  if (s <= n) ans[id].push_back(s);
  for (int t : adj[s]) {
    if (!vis[t]) {
      bfs(n,m,t,id);
    }
  }
}

void query2(const vector<pii>& edges) {
  cout << "Q " << edges.size();
  for (const pii& it : edges) {
    cout << " " << it.first << " " << it.second;
  }
  cout << endl;
  for (int i=0; i<edges.size(); i++) {
    const pii& it = edges[i];
    char c;
    cin >> c;
    if (c=='1') {
      int gid = (it.first-1)/4;
      int gjd = (it.second-1)/4;
      for (int j=0; j<3; j++) {
        if (groups[gjd].v[j][0] != it.second) {
          adj[it.first].erase(groups[gjd].v[j][0]);
          adj[groups[gjd].v[j][0]].erase(it.first);
        }
        if (groups[gid].v[j][0] != it.first) {
          adj[it.second].erase(groups[gid].v[j][0]);
          adj[groups[gid].v[j][0]].erase(it.second);
        }
      }
    } else {
      adj[it.first].erase(it.second);
      adj[it.second].erase(it.first);
    }
  }
}

#define DEBUG
void solve(int n) {
#ifdef DEBUG
  cerr << "GROUPS" << endl;
  for (const Group& g : groups) {
    for (int i=0; i<3; i++) {
      cerr << i << ": ";
      for (int it : g.v[i]) {
        cerr << it << " ";
      }
      cerr << endl;
    }
  }
#endif

  int m = groups.size();
  for (int i=1; i<=n; i++) {
    int gid = (i-1)/4;
    if (gid < m-1) {
      Group& cur = groups[gid];
      Group& nxt = groups[gid+1];
      for (int j=0; j<3; j++) {
        for (int k=0; k<3; k++) {
          if (cur.v[j].empty()) cur.v[j].push_back(i+n);
          if (nxt.v[k].empty()) nxt.v[k].push_back(i+4+n);
          adj[cur.v[j][0]].insert(nxt.v[k][0]);
          adj[nxt.v[k][0]].insert(cur.v[j][0]);
        }
      }
    }
  }

  for (int s=0; s<2; s++) {
    // QUERY 4 and QUERY 6
    {
      vector<pii> edges;
      for (int i=s; i<m; i+=2) {
        if (i+1<m) {
          Group& cur = groups[i];
          Group& nxt = groups[i+1];
          for (int j=0; j<3; j++) {
            if (cur.v[j][0] <= n && nxt.v[j][0] <= n) {
              edges.push_back(pii(cur.v[j][0], nxt.v[j][0]));
            }
          }
        }
      }
      query2(edges);
    }

    // QUERY 5 and QUERY 7
    {
      vector<pii> edges;
      for (int i=s; i<m; i+=2) {
        if (i+1<m) {
          Group& cur = groups[i];
          Group& nxt = groups[i+1];
          for (int j=0; j<3; j++) {
            if (cur.v[j][0] <= n && nxt.v[(j+1)%3][0] <= n) {
              edges.push_back(pii(cur.v[j][0], nxt.v[(j+1)%3][0]));
            }
          }
        }
      }
      query2(edges);
    }
  }

  for (int i=1; i<=n; i++) {
    int gid = (i-1)/4;
    if (gid+1<m) {
      Group& nxt = groups[gid+1];
      int j = first[i];
      if (adj[i].count(nxt.v[(j+2)%3][0])) {
        adj[i].erase(nxt.v[j][0]);
        adj[nxt.v[j][0]].erase(i);
        adj[i].erase(nxt.v[(j+1)%3][0]);
        adj[nxt.v[(j+1)%3][0]].erase(i);
      }
    }
  }

#ifdef DEBUG
  cerr << "GRAPH" << endl;
  for (int i=1; i<=n; i++) {
    cerr << i << " -> ";
    for (int it : adj[i]) cerr << it << " ";
    cerr << nl;
  }
#endif

  for (int i=0; i<3; i++) {
    ans[i].clear();
  }

  memset(vis, 0, sizeof vis);
  int col = 0;
  for (int i=1; i<=n; i++) {
    if (!vis[i]) {
      bfs(n, m, i, col++);
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

  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    assert(n != -1);

    find_groups(n);
    solve(n);
    cout << "A";
    for (int i=0; i<3; i++) {
      cout << " " << ans[i].size();
    }
    cout << endl;
    for (int i=0; i<3; i++) {
      for (int it : ans[i]) {
        cout << it << " ";
      }
      cout << endl;
    }
  }

  return 0;
}
