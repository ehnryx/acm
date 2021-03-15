#include <bits/stdc++.h>
using namespace std;

// 13:46 -> 14:01
// 15 minutes

#define FILENAME "disjoint"

#define nl '\n'
typedef long long ll;
typedef long double ld;

const int A = 26;

vector<vector<int>> build_dfa(const string& s) {
  vector<vector<int>> adj;
  adj.push_back(vector<int>(A, -1));
  adj.push_back(vector<int>(A, -1));

  stack<int> pstart, pend, start, end;
  pstart.push(0);
  pend.push(1);
  start.push(0);
  end.push(0);

  for(char c : s) {
    if(isalpha(c)) {
      int id = adj.size();
      adj.push_back(vector<int>(A, -1));
      adj.push_back(vector<int>(A, -1));
      // join with previous block
      adj[end.top()].push_back(id);
      // set edge inside current block
      adj[id][c - 'a'] = id + 1;
      // set start / end of current block
      start.top() = id;
      end.top() = id + 1;
    } else if(c == '*') {
      // join start and end of current block
      adj[start.top()].push_back(end.top());
      adj[end.top()].push_back(start.top());
    } else if(c == '(') {
      int id = adj.size();
      adj.push_back(vector<int>(A, -1));
      adj.push_back(vector<int>(A, -1));
      // join with previous block
      adj[end.top()].push_back(id);
      // set start / end of current block
      start.top() = id;
      end.top() = id + 1;
      // descend into current block
      pstart.push(id);
      pend.push(id + 1);
      start.push(id);
      end.push(id);
    } else if(c == ')') {
      // join with end of parent block
      adj[end.top()].push_back(pend.top());
      // ascend from current block
      pstart.pop();
      pend.pop();
      start.pop();
      end.pop();
    } else if(c == '|') {
      // join with end of parent block
      adj[end.top()].push_back(pend.top());
      // move current block to start of parent block
      start.top() = end.top() = pstart.top();
    } else {
      assert(false);
    }
  }

  // join with end
  adj[end.top()].push_back(1);

  return adj;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  string ss, tt;
  cin >> ss >> tt;
  auto f = build_dfa(ss);
  auto g = build_dfa(tt);

  vector dist(f.size(), vector(g.size(), vector<int>(2, -1)));
  vector pre(f.size(), vector(g.size(), vector<tuple<int,int,int,int>>(2)));

  deque<tuple<int,int,int>> bfs;
  bfs.emplace_back(0, 0, 0);
  dist[0][0][0] = 0;
  while(!bfs.empty()) {
    auto [a, b, t] = bfs.front();
    bfs.pop_front();
    int d = dist[a][b][t];
    for(int c=0; c<A; c++) {
      if(f[a][c] != -1 && g[b][c] != -1 && dist[f[a][c]][g[b][c]][t|1] == -1) {
        dist[f[a][c]][g[b][c]][t|1] = d + 1;
        pre[f[a][c]][g[b][c]][t|1] = make_tuple(a, b, t, c);
        bfs.emplace_back(f[a][c], g[b][c], t|1);
      }
    }
    for(int c=A; c<f[a].size(); c++) {
      if(dist[f[a][c]][b][t] == -1) {
        dist[f[a][c]][b][t] = d;
        pre[f[a][c]][b][t] = make_tuple(a, b, t, c);
        bfs.emplace_front(f[a][c], b, t);
      }
    }
    for(int c=A; c<g[b].size(); c++) {
      if(dist[a][g[b][c]][t] == -1) {
        dist[a][g[b][c]][t] = d;
        pre[a][g[b][c]][t] = make_tuple(a, b, t, c);
        bfs.emplace_front(a, g[b][c], t);
      }
    }
  }

  if(dist[1][1][1] == -1) {
    cout << "Correct" << nl;
  } else {
    cout << "Wrong" << nl;
    string ans;
    for(int a=1, b=1, t=1; a || b || t; ) {
      auto [pa, pb, pt, c] = pre[a][b][t];
      if(c < A) {
        ans.push_back('a' + c);
      }
      tie(a, b, t) = tie(pa, pb, pt);
    }
    reverse(ans.begin(), ans.end());
    cout << ans << nl;
  }

  return 0;
}
