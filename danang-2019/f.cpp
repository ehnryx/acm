#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
#define nl '\n'

const ld EPS = 1e-11;

const int N = 1e5+1;
int a[N], b[N], d[N];
ld y[N], ans[N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(11);

  int n, t;
  cin >> n >> t;
  ll sum = 0;
  for(int i=1; i<=n; i++) {
    cin >> a[i] >> b[i] >> d[i];
    sum += d[i];
  }

  ld tot = 0;
  for(int i=1; i<=n; i++) {
    y[i] = (ld) t * d[i] / sum;
    ans[i] = min((ld)b[i], max((ld)a[i], y[i]));
    tot += ans[i];
  }

  if(abs(tot-t) < EPS) {
    for(int i=1; i<=n; i++) {
      cout << ans[i] << nl;
    }
    return 0;
  }

  if(tot < t) {
    tot = t-tot;
    vector<pair<ld,int>> nxt;
    for(int i=1; i<=n; i++) {
      if(ans[i] < b[i]-EPS) {
        nxt.push_back(make_pair(2*(ans[i]-y[i])/y[i], i));
        nxt.push_back(make_pair(2*(b[i]-y[i])/y[i], -i));
      }
    }
    sort(nxt.begin(), nxt.end());

    ld cur = 0;
    ld have = 0;
    ld sy = 0;
    for(const auto& it : nxt) {
      ld slope; int i;
      tie(slope, i) = it;

      ld add = (slope-cur) * sy / 2;
      if(have + add > tot-EPS) {
        if(sy < EPS) { while(clock()<.789*CLOCKS_PER_SEC); assert(false); }
        ld want = 2 * (tot-have)/sy + cur;
        for(int j=1; j<=n; j++) {
          if(ans[j] < -1) {
            ans[j] = y[j] + want * y[j]/2;
          }
        }
        break;
      } else {
        have += add;
      }
      cur = slope;

      if(i>0) {
        ans[i] = -2;
        sy += y[i];
      } else {
        i = -i;
        ans[i] = b[i];
        sy -= y[i];
      }
    }

    for(int i=1; i<=n; i++) {
      cout << ans[i] << nl;
    }
  }

  else {
    tot = tot-t;
    vector<pair<ld,int>> nxt;
    for(int i=1; i<=n; i++) {
      if(ans[i] > a[i]+EPS) {
        nxt.push_back(make_pair(2*(y[i]-ans[i])/y[i], i));
        nxt.push_back(make_pair(2*(y[i]-a[i])/y[i], -i));
      }
    }
    sort(nxt.begin(), nxt.end());

    ld cur = 0;
    ld have = 0;
    ld sy = 0;
    for(const auto& it : nxt) {
      ld slope; int i;
      tie(slope, i) = it;
      ld add = (slope-cur)/2 * sy;
      if(have + add > tot-EPS) {
        if(sy < EPS) { while(clock()<.789*CLOCKS_PER_SEC); assert(false); }
        ld want = 2 * (tot-have)/sy + cur;
        for(int j=1; j<=n; j++) {
          if(ans[j] < -1) {
            ans[j] = y[j] - want * y[j]/2;
          }
        }
        break;
      } else {
        have += add;
      }
      cur = slope;

      if(i>0) {
        ans[i] = -2;
        sy += y[i];
      } else {
        i = -i;
        ans[i] = a[i];
        sy -= y[i];
      }
    }

    for(int i=1; i<=n; i++) {
      cout << ans[i] << nl;
    }
  }

  for(int i=1; i<=n; i++) {
    if(a[i]<-1) for(;;);
    assert(a[i]-EPS < ans[i] && ans[i] < b[i]+EPS);
  }

  return 0;
}
