#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
constexpr char nl = '\n';
const int INF = 0x3f3f3f3f;

#define FNAME "improvements"

int main() {
  string __fname = FNAME;
#ifdef ONLINE_JUDGE
  freopen(FNAME ".in", "r", stdin);
  freopen(FNAME ".out", "w", stdout);
#endif
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n;
  cin >> n;
  vector<pair<int,int>> order;
  for(int i=0; i<n; i++) {
    int v;
    cin >> v;
    order.emplace_back(v, i);
  }
  sort(order.begin(), order.end());

  vector<int> a(n);
  for(int i=0; i<n; i++) {
    a[i] = order[i].second;
  }
  vector<int> r = a;
  reverse(r.begin(), r.end());

  vector<int> lis(n, INF), sil(n, INF);
  vector<int> front(n), back(n);
  for(int i=0; i<n; i++) {
    auto it = lower_bound(lis.begin(), lis.end(), a[i]);
    front[i] = it - lis.begin();
    *it = a[i];
    auto jt = lower_bound(sil.begin(), sil.end(), r[i]);
    back[i] = jt - sil.begin();
    *jt = r[i];
  }

  int ans = 0;
  for(int i=0; i<n; i++) {
    ans = max(ans, 1 + front[i] + back[n-1-i]);
  }
  cout << ans << nl;

  return 0;
}
