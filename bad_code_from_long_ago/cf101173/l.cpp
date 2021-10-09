#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG
//#define USE_MAGIC_IO

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

int check(const vector<set<int>>& g, int sol, int forbidden) {
  //cerr << "Try " << sol << nl;
  int start;
  for (int i = 0; i < 8; i++) {
    if (forbidden & (1<<i)) continue;
    if (sol & (1<<i)) start = i+8;
    else start = i;

    //cerr << "start from " << start << nl;
    bitset<16> vis;
    queue<int> next;
    next.push(start);
    vis[i] = true;
    while (!next.empty()) {
      int cur = next.front();
      next.pop();
      //cerr << "visit " << cur << " with " << (sol & (1<<(cur%8))) << nl;
      if (cur < 8 && sol & (1<<cur)) {
        return 0;
      } else if (cur >= 8 && !(sol & (1<<(cur-8)))) {
        return 0;
      }
      for (int neighbour : g[cur]) {
        if (!vis[neighbour]) {
          next.push(neighbour);
          vis[neighbour] = true;
        }
      }
    }
  }
  return 1;
}

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  int n;
  cin >> n;
  vector<int> col(n, 0);
  vector<int> a[3];

  // get the input
  for (int r = 0; r < 3; r++) {
    a[r].resize(n);
    for (int i = 0; i < n; i++) {
      cin >> a[r][i];
      if (a[r][i]) col[i] |= 1<<r;
    }
  }
  
  // group based on columns
  vector<int> group[8];
  for (int i = 0; i < n; i++) {
    group[col[i]].push_back(i);
    //cerr << "add " << i << " to group " << col[i] << nl;
  }

  // build graph between groups
  vector<set<int>> adj(16); // 0-7 incl: false, 8-15 incl: true
  int forbidden = 0;
  for (int i = 0; i < 8; i++) {
    if (group[i].empty()) {
      forbidden |= 1<<i;
    } else {
      for (int j = 0; j < 8; j++) {
        if (i == j) continue;
        if (group[j].empty()) continue;
        int imp0 = -1;
        int imp1 = -1;
        for (int r = 0; r < 3; r++) {
          if (a[r][group[i].back()] == 0) {
            if (imp0 == -1) imp0 = a[r][group[j].back()];
            else if (imp0 != a[r][group[j].back()]) imp0 = 2;
          } else {
            if (imp1 == -1) imp1 = a[r][group[j].back()];
            else if (imp1 != a[r][group[j].back()]) imp1 = 2;
          }
        }
        //cerr << "connecting " << i << " " << j << nl;
        if (imp0 == -1) {
          adj[i].insert(j);
          adj[i].insert(j+8);
        } else if (imp0 == 0) {
          adj[i].insert(j);
        } else if (imp0 == 1) {
          adj[i].insert(j+8);
        }
        if (imp1 == -1) {
          adj[i+8].insert(j);
          adj[i+8].insert(j+8);
        } else if (imp1 == 0) {
          adj[i+8].insert(j);
        } else if (imp1 == 1) {
          adj[i+8].insert(j+8);
        }
      }
    }
  }

  //cerr << "graph: " << nl; for (int i = 0; i < 16; i++) {
    //cerr << i << ": "; for (int j : adj[i]) {
      //cerr << j << " "; }
    //cerr << nl; }
  //cerr << nl;

  // brute force to check
  int ans = 0;
  for (int bm = 0; bm < 1<<8; bm++) {
    if (forbidden & bm) continue;
    ans += check(adj, bm, forbidden);
    //cerr;if (check(adj, bm, forbidden)) //cerr << "solution: " << bm << nl;
  }

  // check output
  if (ans != 3) {
    // impossible
    cout << -1 << nl;
  } else {
    // get answers
    int edges = 0;
    for (const auto& it : adj) {
      edges += it.size();
    }
    for (int i = 0; i < 8; i++) {
      edges += max(0, 2*((int)group[i].size()-1));
    }
    cout << edges << nl;
    for (int i = 0; i < 16; i++) {
      for (int j : adj[i]) {
        if (i < 8) cout << "!";
        cout << "x" << group[i%8].back()+1 << " -> ";
        if (j < 8) cout << "!";
        cout << "x" << group[j%8].back()+1 << nl;
      }
    }
    for (int g = 0; g < 8; g++) {
      if (!group[g].empty()) {
        for (int i = 1; i < group[g].size(); i++) {
          cout << "x" << group[g][i-1]+1 << " -> " << "x" << group[g][i]+1 << nl;
          cout << "!x" << group[g][i-1]+1 << " -> " << "!x" << group[g][i]+1 << nl;
        }
      }
    }
  }

  return 0;
}
