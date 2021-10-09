#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const char nl = '\n';
const ll INF = 0x3f3f3f3f3f3f3f3fLL;

inline char get() {
  static char buf[100000], *S = buf, *T = buf;
  if (S == T) {
    T = (S = buf) + fread(
  }
}

vector<ll> greedy(const vector<int> &v, int n) {
  priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> pq;
  for(int i:v) {
    pq.push({i,i});
  }
  vector<ll> ans;
  for(int i=0;i<n;i++) {
    ans.push_back(pq.top().first);
    pq.push({pq.top().first+pq.top().second, pq.top().second});
    pq.pop();
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int T; cin >> T;
  for (int tt = 1; tt <= T; tt++) {
    cout << "Case #" << tt << ": ";
    int l, n, m; cin >> l >> n >> m;
    vector<int> w(n), d(m);
    for (int i = 0; i < n; i++) {
      cin >> w[i];
    }
    for(int i=0;i<m;i++) {
      cin >> d[i];
    }
    vector<ll> ww = greedy(w, l);
    vector<ll> dd = greedy(d, l);
//    for(int i: ww) cerr << i << " "; cerr << " washers " <<endl;
//    for(int i: dd) cerr << i << " "; cerr << " dryers " <<endl;
    ll ans = 0;
    for(int i=0;i<l;i++) {
      ans = max(ans, ww[i]+dd[l-1-i]);
    }
    cout << ans << endl;
  }

  return 0;
}
