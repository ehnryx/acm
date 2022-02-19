#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;

  int rid = 0;
  unordered_map<string,int> remap;
  vector<int> start;

  vector<pair<bool,vector<int>>> ev;
  for(int i=0; i<n; i++) {
    string s;
    cin >> s;
    if(s == "if") {
      vector<int> g;
      bool a = true;
      string op;
      cin >> s >> op;
      if(!remap.count(s))remap[s] = rid++;
      g.push_back(remap[s]);
      if(op == "or") a=false;
      while(op != "then") {
        cin >> s >> op;
        if(!remap.count(s))remap[s] = rid++;
        g.push_back(remap[s]);
      }
      cin >> s;
      if(!remap.count(s))remap[s] = rid++;
      g.push_back(remap[s]);
      ev.emplace_back(a, g);
    } else {
      if(!remap.count(s))remap[s]=rid++;
      start.push_back(remap[s]);
    }
  }

  vector<bool> have(size(remap));
  for(int s:start)have[s]=true;

  for(bool changed=true; changed; ){
    changed=false;
    for(const auto& [a, g] : ev) {
      if(have[g.back()]) continue;
      bool ok =true;
      if(a){
        for(int i=0; i<size(g)-1; i++) {
          ok &= have[g[i]];
        }
      }else{
        ok=false;
        for(int i=0; i<size(g)-1; i++) {
          ok |= have[g[i]];
        }
      }
      if(ok) {
        have[g.back()] = true;
        changed=true;
      }
    }
  }

  cout << accumulate(begin(have),end(have),int(0)) << nl;

  return 0;
}
