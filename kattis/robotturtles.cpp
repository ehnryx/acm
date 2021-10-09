//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

enum {
  RIGHT,
  UP,
  LEFT,
  DOWN,
};

const vector<int> di = { 0, -1, 0, 1 };
const vector<int> dj = { 1, 0, -1, 0 };

struct Node {
  int i, j, f, d;
  tuple<int,int,int> p;
  Node() {}
  Node(int _i, int _j, int _f, int _d, int pi, int pj, int pf):
    i(_i), j(_j), f(_f), d(_d), p({pi,pj,pf}) {}
  bool operator < (const Node& o) const {
    return d > o.d;
  }
};

const int N = 8 + 2;
char g[N][N];
int dist[N][N][4];
tuple<int,int,int> pre[N][N][4];


int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  fill(&g[0][0], &g[0][0]+N*N, 'C');
  Node s;
  for(int i=1; i<=8; i++) {
    for(int j=1; j<=8; j++) {
      cin >> g[i][j];
      if(g[i][j] == 'T') {
        s = Node(i, j, RIGHT, 0, 0, 0, 0);
      }
    }
  }

  memset(dist, -1, sizeof dist);
  priority_queue<Node> dijk;
  dijk.push(s);
  while(!dijk.empty()) {
    auto [i, j, f, d, p] = dijk.top();
    dijk.pop();
    if(dist[i][j][f] != -1) continue;
    dist[i][j][f] = d;
    pre[i][j][f] = p;
    // solved
    if(g[i][j] == 'D') {
      string ans;
      for(;;) {
        const auto& [a, b, c] = pre[i][j][f];
        if(a == 0) break;
        if(a == i && b == j) {
          if(f == (c+1)%4) {
            ans.push_back('L');
          } else {
            ans.push_back('R');
          }
        } else if(g[i][j] == 'I') {
          ans.push_back('F');
          ans.push_back('X');
        } else {
          ans.push_back('F');
        }
        i = a; j = b; f = c;
      }
      reverse(ans.begin(), ans.end());
      cout << ans << nl;
      return 0;
    }
    // turns
    dijk.push(Node(i, j, (f+1)%4, d+1, i, j, f));
    dijk.push(Node(i, j, (f+3)%4, d+1, i, j, f));
    // move
    int ni = i + di[f];
    int nj = j + dj[f];
    if(g[ni][nj] == '.' || g[ni][nj] == 'D') {
      dijk.push(Node(ni, nj, f, d+1, i, j, f));
    } else if(g[ni][nj] == 'I') {
      dijk.push(Node(ni, nj, f, d+2, i, j, f));
    }
  }

  cout << "no solution" << nl;

  return 0;
}
