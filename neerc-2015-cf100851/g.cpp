#include <bits/stdc++.h>
using namespace std;
#define FILENAME "generators"

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;


const ll INF = 0x3f3f3f3f3f3f3f3fLL;
const int MAXN = 1e4+10;
ll n, k;

ll x0[MAXN], a[MAXN], b[MAXN], c[MAXN];

map<int, int> m[MAXN];
map<int, int> t[MAXN];

int bestt[MAXN];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  cin >> n >> k;
  for(int i=0;i<n;i++) {
    cin >> x0[i] >> a[i] >> b[i] >> c[i];
    int x = x0[i];
    for(int j=0;j<2100;j++) {
      if (m[i][x%k] < x) {
        //cerr << "i " << i << " reached " << x%k << " at time " << j << " with " << x <<endl;
        m[i][x%k] = x;
        t[i][x%k] = j;
      }
      x = (a[i]*x+b[i])%c[i];
    }
  }
  ll ans = 0;
  ll best = INF;
  int id = -1;
  int sect = -1;
  for(int i=0;i<n;i++) {
    vector<pair<int,int>> pos;
    for (auto p: m[i]) {
      //cerr<< "@ "<<i << " " << p.first << " " << p.second <<endl;
      pos.emplace_back(p.second, t[i][p.first]);
    }
    sort(pos.begin(),pos.end());
    auto p = pos.back();
    ans+=p.first;
    bestt[i] = p.second;
    if (pos.size() > 1) {
      pos.pop_back();
      auto p2 = pos.back();
      if (best > p.first - p2.first) {
        best = p.first -p2.first;
        id = i;
        sect = p2.second;
      }
    }
  }

  if (ans%k) {
    cout << ans <<endl;
    for(int i=0;i<n;i++) cout << bestt[i] << " "; cout <<endl;
  }
  else {
    if (best==INF) {
      cout << -1 <<endl;
    }
    else {
      cout <<  ans - best << endl;
      for(int i=0;i<n;i++) {
        if (i!=id) cout << bestt[i] << " ";
        else cout << sect <<" ";
      } 
      cout <<endl;
    }
  }




  return 0;
}
