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

struct Node {
  int par;
  int weight;
  vector<int> child;
  vector<int> sum;
  int depth;
};

int getdepth(int u, vector<Node>& nodes) {
  if (u != 1) {
    nodes[u].depth = 1 + nodes[nodes[u].par].depth;
  }
  int md = 1;
  for (int child: nodes[u].child) {
    md = max(md, 1 + getdepth(child, nodes));
  }
  return md;
}
void build (int u, vector<Node>& nodes, int maxdepth) {
  int len = maxdepth - nodes[u].depth + 1;
  nodes[u].sum.resize(len);
  memset(&nodes[u].sum[0], 0, len*sizeof(nodes[u].sum[0]));
  nodes[u].sum[0] = nodes[u].weight;
  for (int child: nodes[u].child) {
    build(child, nodes, maxdepth);
    for (int i = 1; i < len; i++) {
      nodes[u].sum[i] += nodes[child].sum[i-1];
    }
  }
}

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  int n, m, w;
  int a, b;
  cin >> n >> m >> w;
  vector<Node> nodes(n+1);
  nodes[1].par = -1;
  nodes[1].weight = w;
  nodes[1].depth = 0;
  for (int i = 1; i < n; i++) {
    cin >> a >> b >> w;
    nodes[a].par = b;
    nodes[a].weight = w;
    nodes[b].child.push_back(a);
  } 
  int maxdepth = getdepth(1, nodes);
  build(1, nodes, maxdepth);

  //cerr << "tree: " << nl; for (int i = 1; i <= n; i++) {
    //cerr << i << ": depth: " << nodes[i].depth << " sum: "; for (int it: nodes[i].sum) //cerr << it << " "; 
    //cerr << nl; }

  int root;
  for (int i = 0; i < m; i++) {
    cin >> root;
    int ans = 0;
    for (int i = 0; i < nodes[root].depth; i++) {
      ans = max(ans, nodes[1].sum[i]);
    }
    for (int i = nodes[root].depth; i < maxdepth; i++) {
      ans = max(ans, nodes[1].sum[i] - nodes[root].sum[i-nodes[root].depth]);
    }
    cout << ans << nl;
  }

  return 0;
}
