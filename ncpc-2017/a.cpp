#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

using ll = long long;
using ld = long double;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  ll L;
  int a, b, t, r;
  cin >> L >> a >> b >> t >> r;

  int n;
  cin >> n;
  vector<ll> v = {0, L};
  vector<ll> starts = {L};
  map<ll, int> id;
  for(int i=0; i<n; i++) {
    ll pos;
    cin >> pos;
    v.push_back(pos);
    v.push_back(min(L, pos + a*t + b*r));
    id[pos] = i;
    starts.push_back(pos);
  }
  sort(v.begin(), v.end());
  v.resize(unique(v.begin(), v.end()) - v.begin());
  sort(starts.begin(), starts.end());

  int m = v.size();
  map<ll, int> inv;
  for(int i=0; i<m; i++) {
    inv[v[i]] = i;
  }

  vector<ld> dp(m, 1e19);
  vector<pair<int,bool>> pre(m);
  dp[0] = 0;
  for(int i=1; i<m; i++) {
    //cerr << "@ " << v[i] << nl;
    // no coffee
    dp[i] = dp[i-1] + (ld) (v[i] - v[i-1]) / a;
    pre[i] = make_pair(i-1, false);
    //cerr << "no coffeee: " << dp[i] << nl;
    // get a coffee
    ll lb = max((ll) 0, v[i] - (a*t + b*r));
    int j = inv[*lower_bound(starts.begin(), starts.end(), lb)];
    //cerr << "try to get coffee from " << v[j] << nl;
    if(j >= i) continue;
    //cerr << "ok!" << nl;
    ld coffee = dp[j] + t + (ld) (v[i] - v[j] - a*t) / b;
    if(v[i] - v[j] > a*t && coffee < dp[i]) {
      dp[i] = coffee;
      pre[i] = make_pair(j, true);
      //cerr << "update -> " << coffee << nl;
    }
  }

  //cerr << "best time: " << dp[m-1] << nl;

  vector<int> ans;
  for(int i=m-1; i>0; ) {
    if(pre[i].second) {
      ans.push_back(id[v[pre[i].first]]);
    }
    i = pre[i].first;
  }
  sort(ans.begin(), ans.end());

  cout << ans.size() << nl;
  for(int it : ans) {
    cout << it << " ";
  }
  cout << nl;

  return 0;
}
