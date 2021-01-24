#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

const int INF = 0x3f3f3f3f;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n;
  cin >> n;

  vector<string> f(n);
  unordered_map<string,int> toi;
  for(int i=0; i<n; i++) {
    cin >> f[i];
    toi[f[i]] = i;
  }

  vector<vector<int>> adj(n);
  for(int i=0; i<n; i++) {
    string line; int k;
    cin >> line >> k;
    assert(line == f[i]);
    getline(cin, line);
    for(int j=0; j<k; j++) {
      getline(cin, line);
      istringstream in(line);
      string s;
      in >> s; // ignore `import'
      while(in >> s) {
        if(s.back() == ',') {
          s.pop_back();
        }
        adj[i].push_back(toi[s]);
      }
    }
  }

  function<vector<string>(int)> get_cycle = [=](int s) {
    vector<int> dist(n, INF), pre(n, -1);
    queue<int> bfs;
    for(int v : adj[s]) {
      dist[v] = 1;
      bfs.push(v);
    }
    while(!bfs.empty()) {
      int u = bfs.front();
      bfs.pop();
      for(int v : adj[u]) {
        if(dist[u] + 1 < dist[v]) {
          dist[v] = dist[u] + 1;
          pre[v] = u;
          bfs.push(v);
        }
      }
    }
    vector<string> out;
    if(dist[s] < INF) {
      for(int u=s; u!=-1; u=pre[u]) {
        out.push_back(f[u]);
      }
      reverse(out.begin(), out.end());
    }
    return out;
  };

  pair<int,vector<string>> best(INF, {});
  for(int i=0; i<n; i++) {
    vector<string> cycle = get_cycle(i);
    if(!cycle.empty()) {
      best = min(best, make_pair((int)cycle.size(), cycle));
    }
  }
  if(best.second.empty()) {
    cout << "SHIP IT" << nl;
  } else {
    for(string s : best.second) {
      cout << s << " ";
    }
    cout << nl;
  }

  return 0;
}
