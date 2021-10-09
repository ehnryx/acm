#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
const char nl = '\n';

const int N = 2e5 + 1;
int dsu[N];
int find(int i) {
  if(dsu[i]) return dsu[i] = find(dsu[i]);
  return i;
}
bool link(int i, int j) {
  i = find(i);
  j = find(j);
  if(i == j) return 0;
  dsu[i] = j;
  return 1;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int n;
  cin >> n;
  unordered_map<int,vector<int>> vals;
  for(int i=1; i<=n; i++) {
    int m;
    cin >> m;
    for(int j=0; j<m; j++) {
      int v;
      cin >> v;
      vals[v].push_back(i);
    }
  }

  vector<tuple<int,int,int>> ans;
  for(const auto& [v, ids] : vals) {
    for(int j=1; j<ids.size(); j++) {
      if(link(ids[j], ids[j-1])) {
        ans.emplace_back(ids[j], ids[j-1], v);
      }
    }
  }

  if(ans.size() == n-1) {
    for(auto [a, b, c] : ans) {
      cout << a << " " << b << " " << c << nl;
    }
  } else {
    cout << "impossible" << nl;
  }

  return 0;
}
