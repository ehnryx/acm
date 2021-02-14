#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';


int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;

    unordered_map<string,int> remap;
    for(int i=0; i<n; i++) {
      string s;
      cin >> s;
      remap[s] = i;
    }

    vector<int> groups;
    groups.push_back(0);
    for(int i=0, maxv=-1; i<n; i++) {
      string s;
      cin >> s;
      maxv = max(maxv, remap[s]);
      if(maxv == i) {
        groups.push_back(i + 1);
      }
    }

    for(int i=1; i<groups.size(); i++) {
      cout << groups[i] - groups[i-1] << " ";
    }
    cout << nl;
  }

  return 0;
}
