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

struct Graph {
  int vertices;
  const int N = 10007;
  vector<int> g[N];
  Graph(int n) {
    int vertices;
  }
  void add_edge(int a, int b) {
    g[a].push_back(b);
    g[b].push_back(a);
  }
  void build(int s, int t) {
    
  }
};

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  int n;
  cin >> n;
  Graph graph(n);
  
  pair<ll,ll> input[n];
  map<ll,set<int>> vals;
  map<ll,int> ids;
  for (int i = 0; i < n; i++) {
    cin >> input[i].first >> input[i].second;
    vals[input[i].first + input[i].second].insert(i+1);
    vals[input[i].first * input[i].second].insert(i+1);
    vals[input[i].first - input[i].second].insert(i+1);
  }
  int cnt = n+1;
  for (auto& num: vals) {
    graph.add_edge(cnt, 10002);
    for (int id: vals.second) {
      FLOW::add_edge(id, cnt);
    }
    map[num.first] = cnt++;
  }
  for (int i = 0; i < n; i++) {
    FLOW::add_edge(0, i+1);
  }

  return 0;
}
