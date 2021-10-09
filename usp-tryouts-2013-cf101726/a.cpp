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

const int N = 1<<17;
int a[N];
int st[2*N], z[2*N];

void build(int L) {
  for(int i=L-1;i>0;i--) {
    st[i] = max(st[2*i],st[2*i+1]);
    z[i] = 0;
  }
}
void push(int i) {
  if(z[i]) {
    st[2*i] += z[i];
    st[2*i+1] += z[i];
    z[2*i] += z[i];
    z[2*i+1] += z[i];
    z[i] = 0;
  }
}
int query(int x, int i, int s, int e) {
  if(s==e) return st[i];
  push(i);
  int m = (s+e)/2;
  if(x<=m) return query(x,2*i,s,m);
  else return query(x,2*i+1,m+1,e);
}
int find(int l, int r, int v, int i, int s, int e) {
  if(r<s||e<l) return -1;
  if(st[i]<v) return -1;
  if(s==e) return s;
  push(i);
  int m = (s+e)/2;
  int right = find(l,r,v,2*i+1,m+1,e);
  if(right!=-1) return right;
  return find(l,r,v,2*i,s,m);
}
void update(int l, int r, int i, int s, int e) {
  if(r<s||e<l) return;
  if(l<=s&&e<=r) {
    st[i]--;
    z[i]--;
    return;
  }
  push(i);
  int m = (s+e)/2;
  update(l,r,2*i,s,m);
  update(l,r,2*i+1,m+1,e);
  st[i] = max(st[2*i],st[2*i+1]);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin>>T;
  while(T--) {
    int n;
    cin>>n;
    for(int i=0;i<n;i++) {
      cin>>a[i];
    }
    sort(a,a+n,greater<int>());
    int L = 1 << (32-__builtin_clz(n));
    for(int i=0;i<n;i++) {
      st[L+i] = a[i];
    }
    build(L);

    bool ok = true;
    for(int i=0;i<n;i++) {
      int d = query(i, 1,0,L-1);
      //cerr<<"@ "<<i<<" w/ "<<d<<nl;
      if(d==0) {
        break;
      }
      if(i+d>=n) {
        ok = false;
        break;
      }
      int v = query(i+d, 1,0,L-1);
      if(v==0) {
        ok = false;
        break;
      }
      int to = find(i+1,n-1,v+1, 1,0,L-1);
      int last = find(i+1,n-1,v, 1,0,L-1);
      //cerr<<"@ "<<i<<" w/ "<<d<<" search for "<<v<<" -> "<<to<<" "<<last<<nl;
      assert(last!=-1);
      if(to==-1) to = i;
      if(to>i) {
        //cerr<<"update "<<i+1<<" "<<to<<nl;
        update(i+1,to, 1,0,L-1);
      }
      int need = d - (to-i);
      if(need>0) {
        //cerr<<"udpate "<<last-need+1<<" "<<last<<nl;
        update(last-need+1,last, 1,0,L-1);
      }
    }

    if(ok) {
      cout<<"Y"<<nl;
    } else {
      cout<<"N"<<nl;
    }
  }

  return 0;
}
