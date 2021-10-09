#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';
typedef long long ll;
typedef long double ld;



int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int k;
  cin >> k;

  vector<vector<int>> ans;
  ans.push_back({0});
  ans.push_back({1, 2, 1});
  ans.push_back({1, 3, 1});
  for(int i=1; i<k; i++) {
    if(i%2 == 1) {
      ans.push_back({2, 2, i/2+1, 3, i/2+1});
    } else {
      ans.push_back({2, 2, i/2+1, 3, i/2});
      ans.push_back({2, 2, i/2, 3, i/2+1});
    }
  }

  cout << ans.size() << nl;
  for(const vector<int>& v : ans) {
    for(int it : v) {
      cout << it << " ";
    }
    cout << nl;
  }

  return 0;
}
