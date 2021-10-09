#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';
typedef long long ll;
typedef long double ld;
const int INF = 0x3f3f3f3f;



int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int n;
  cin >> n;
  vector<int> a(n+1), b(n+1);

  set<pair<int,int>> top;
  set<pair<int,int>> right;
  set<pair<int,int>> topright;
  top.insert(make_pair(2*INF, 0));
  right.insert(make_pair(2*INF, 0));
  topright.insert(make_pair(2*INF, 0));

  vector<int> ans;
  for(int i=1; i<=n; i++) {
    cin >> a[i] >> b[i];
    topright.insert(make_pair(a[i] + b[i], i));
  }
  a[0] = b[0] = INF;

  for(int x = 1, y = 1; ans.size() < n; ) {
    for(auto it=topright.begin(); a[it->second] < x || b[it->second] < y; ) {
      int i = topright.begin()->second;
      it = topright.erase(it);
      assert(a[i] >= x || b[i] >= y);
      if(a[i] < x) {
        top.insert(make_pair(b[i], i));
      } else {
        right.insert(make_pair(a[i], i));
      }
    }

    if(top.begin()->first - y <= min(right.begin()->first - x, topright.begin()->first - (x+y))) {
      int i = top.begin()->second;
      top.erase(top.begin());
      ans.push_back(i);
      x = max(x, a[i]);
      y = max(y, b[i]);
    } else if(right.begin()->first - x <= min(top.begin()->first - y, topright.begin()->first - (x+y))) {
      int i = right.begin()->second;
      right.erase(right.begin());
      ans.push_back(i);
      x = max(x, a[i]);
      y = max(y, b[i]);
    } else if(topright.begin()->first - (x+y) <= min(top.begin()->first - y, right.begin()->first - x)) {
      int i = topright.begin()->second;
      topright.erase(topright.begin());
      ans.push_back(i);
      x = max(x, a[i]);
      y = max(y, b[i]);
    }
  }

  for(int it : ans) {
    cout << it << " ";
  }
  cout << nl;

  return 0;
}
