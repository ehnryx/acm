#include <bits/stdc++.h>
using namespace std;

#define FILENAME "identification"

#define nl '\n'
typedef long long ll;
typedef long double ld;

constexpr ll P = 9705276;
constexpr ll Q = 12805858;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  map<ll,pair<int,int>> vals;
  for(int i=0; i<=400; i++) {
    for(int j=0; i+j<=400; j++) {
      assert(vals.insert(make_pair(P*i + Q*j, make_pair(i, j))).second);
    }
  }

  int n;
  scanf("%d", &n);
  //cin >> n;
  vector<ll> v(n);
  for(int i=0; i<n; i++) {
    double in;
    scanf("%lf", &in);
    //cin >> in;
    v[i] = llround(in * 1e5);
  }
  auto [pn, qn] = vals[*max_element(v.begin(), v.end())];

  vector have(pn+1, vector<bool>(qn+1));
  for(int i=0; i<n; i++) {
    auto it = vals.find(v[i]);
    if(it != vals.end() && it->second.first <= pn && it->second.second <= qn) {
      have[it->second.first][it->second.second] = true;
    }
  }

  function<bool(int,int)> valid = [=](int s, int d) {
    return 0 <= s && s <= pn && 0 <= d-s && d-s <= qn;
  };

  static const vector<pair<int,int>> transitions = {
    {0, 0}, {0, 1}, {1, 0}, {1, 1},
  };

  int m = max(pn, qn) + 1;
  int half = (pn + qn) / 2;
  vector dp(m, vector<int>(m, -1));
  vector pre(half+1, vector(m, vector<pair<short,short>>(m)));
  dp[0][0] = 1;
  for(int d=1; 2*d<=pn+qn; d++) {
    vector ndp(m, vector<int>(m, -1));
    for(int s=0; s<=d; s++) {
      if(!valid(s, d)) continue;
      for(int t=0; t<=d; t++) {
        if(!valid(t, d)) continue;
        for(auto [ds, dt] : transitions) {
          if(!valid(s-ds, d-1) || !valid(t-dt, d-1)) continue;
          if(dp[s-ds][t-dt] < 0) continue;
          int front = have[s][d-s] + (s == t ? 0 : have[t][d-t]);
          int back = have[pn-s][qn-(d-s)] + (s == t ? 0 : have[pn-t][qn-(d-t)]);
          int val = dp[s-ds][t-dt] + front + (2*d == pn+qn ? 0 : back);
          if(val > ndp[s][t]) {
            ndp[s][t] = val;
            pre[d][s][t] = make_pair(s-ds, t-dt);
          }
        }
      }
    }
    dp = move(ndp);
  }

  tuple<int,int,int> best(-1, -1, -1);
  for(int s=0; s<=pn; s++) {
    if(valid(s, half) && valid(pn-s, half)) {
      best = max(best, make_tuple(dp[s][pn-s], s, pn-s));
    }
    if((pn+qn) % 2 == 1 && valid(s, half) && valid(pn-s-1, half)) {
      best = max(best, make_tuple(dp[s][pn-s-1], s, pn-s-1));
    }
  }

  string ans(pn + qn, 0);
  auto [_, s, t] = best;
  if((pn+qn) % 2 == 1) {
    ans[half] = (s+t < pn ? 'P' : 'Q');
  }
  for(int i=half; i>0; i--) {
    auto [ns, nt] = pre[i][s][t];
    ans[i-1] = (s != ns ? 'P' : 'Q');
    ans[pn+qn-i] = (t != nt ? 'P' : 'Q');
    s = ns;
    t = nt;
  }
  cout << ans << nl;

  assert(*min_element(ans.begin(), ans.end()) > 0);
  assert(count(ans.begin(), ans.end(), 'P') == pn);

  return 0;
}
