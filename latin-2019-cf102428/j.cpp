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

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1<<18;
int a[N];

pii st[2*N];

void insert(int i, int v) {
  pii val = make_pair(v, i);
  st[i+=N] = val;
  for(i/=2; i>0; i/=2) {
    st[i] = max(st[2*i], st[2*i+1]);
  }
}

pii query(int l, int r) {
  pii ans = make_pair(-1, -1);
  for(l+=N,r+=N+1; l<r; l/=2,r/=2) {
    if(l&1) ans = max(ans, st[l++]);
    if(r&1) ans = max(ans, st[--r]);
  }
  return ans;
}

int search_left(int l, int r, int v, int i=1, int s=0, int e=N-1) {
  if(r<s || e<l || st[i].first <= v) return -1;
  if(s==e) return s;
  int m = (s+e)/2;
  int res = search_left(l,r,v,2*i,s,m);
  if(res != -1) return res;
  return search_left(l,r,v,2*i+1,m+1,e);
}

int search_right(int l, int r, int v, int i=1, int s=0, int e=N-1) {
  if(r<s || e<l || st[i].first <= v) return -1;
  if(s==e) return s;
  int m = (s+e)/2;
  int res = search_right(l,r,v,2*i+1,m+1,e);
  if(res != -1) return res;
  return search_right(l,r,v,2*i,s,m);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;
  for(int i=1; i<=n; i++) {
    cin >> a[i];
    insert(i, a[i]);
  }

  for(int i=0; i<m; i++) {
    char c;
    cin >> c;
    if(c == 'U') {
      int x, h;
      cin >> x >> h;
      a[x] = h;
      insert(x, h);
    } else {
      int x;
      cin >> x;
      int lv, li, rv, ri;
      tie(lv, li) = query(1, x);
      tie(rv, ri) = query(x, n);
      if(lv == rv) {
        cout << x << nl;
      } else if(lv < rv) {
        ri = search_left(x, n, lv);
        assert(ri != -1);
        if(x == li && c == 'L') cout << x << nl;
        else cout << ri << nl;
      } else {
        li = search_right(1, x, rv);
        assert(li != -1);
        if(x == ri && c == 'R') cout << x << nl;
        else cout << li << nl;
      }
    }
  }

  return 0;
}
