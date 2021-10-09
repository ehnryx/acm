#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

#define int ll
const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ll find(int a, int l, int r, int m) {
  if(a == 0 || a == m) return INFLL;
  if(2*a > m) {
    a = m-a;
    int nl = m-r;
    r = m-l;
    l = nl;
  }
  int b = l/a;
  if(b*a == l) return b;
  if(b*a + a <= r) return b+1;
  ll res = find(a-m%a, l%a, r%a, a);
  //cerr<<"find "<<a-m%a<<" "<<l%a<<" "<<r%a<<" "<<a<<" = "<<res<<nl;
  if(res == INFLL) return res;
  return min(INFLL, (l + m*res + a-1) / a); // b + ((m+a-1)/a) * res);
}

ll solve(int w, int h, int s, int t, int x, int a, int b) {
  //cerr<<"solving "<<w<<" "<<h<<" "<<s<<" "<<t<<" "<<x<<" "<<a<<" "<<b<<nl;
  int d = (x-s + w) % w;
  int y = (t+d) % h;
  if(a <= y && y <= b) return d;
  a = (a-y+h) % h;
  b = (b-y+h) % h;
  ll res = find(w%h, a, b, h);
  //cerr<<"find "<<w%h<<" "<<a<<" "<<b<<" "<<h<<" = "<<res<<nl;
  if(res == INFLL) return res;
  //cerr<<"gives -> "<<d <<" + "<< res*w <<" = "<<d+res*w<< nl;
  return d + res*w;
}

ll solve_seg(int w, int h, int s, int t, int x, int a, int b) {
  //cerr<<"solve seg "<<w<<" "<<h<<" "<<s<<" "<<t<<" "<<x<<" "<<a<<" "<<b<<nl;
  if(a > b) swap(a,b);
  ll res = INFLL;
  res = min(res, solve(2*w, 2*h, s, t, x, a, b));
  res = min(res, solve(2*w, 2*h, s, t, x, h + h-b, h + h-a));
  res = min(res, solve(2*w, 2*h, s, t, w + w-x, a, b));
  res = min(res, solve(2*w, 2*h, s, t, w + w-x, h + h-b, h + h-a));
  //cerr<<"res: "<<res<<nl<<nl;
  return res;
}

#undef int
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#define int ll

  int w,h;
  cin>>w>>h;

  int n;
  cin>>n;
  int x[n], y[n];
  for(int i=0;i<n;i++) {
    cin>>x[i]>>y[i];
  }

  int T;
  cin>>T;
  while(T--) {
    int s,t;
    cin>>s>>t;
    ll ans = INFLL;
    for(int j=0;j<n;j++) {
      int nj = (j+1 == n ? 0 : j+1);
      if(x[j] == x[nj]) {
        ans = min(ans, solve_seg(w, h, s, t, x[j], y[j], y[nj]));
      } else {
        ans = min(ans, solve_seg(h, w, t, s, y[j], x[j], x[nj]));
      }
    }
    if(ans<INFLL) {
      int ss = (s+ans) % (2*w);
      if(ss > w) ss = w - (ss-w);
      int tt = (t+ans) % (2*h);
      if(tt > h) tt = h - (tt-h);
      cout<<ans<<" "<<ss<<" "<<tt<<nl;
    } else {
      cout<<-1<<nl;
    }
    //cerr<<nl;
  }

  return 0;
}
