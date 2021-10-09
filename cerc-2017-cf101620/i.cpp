#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/rope>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_cxx;
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

struct Query {
  int l,r,i;
};

const int N = 1e5+1;
int a[N], idx[N];
pii ans[N];

tuple<int,int,int,int> expand(int l, int r, int li, int ri, int lv, int rv) {
  if(rv-lv > r-l) return tuple<int,int,int,int>(0,0,0,0);
  int nlv = lv;
  int nrv = lv;
  swap(rv, nrv);
  while(nlv!=lv || nrv!=rv) {
    int nli = li;
    int nri = ri;
    for(int i=nlv; i<lv; i++) {
      nli = min(nli, idx[i]);
      nri = max(nri, idx[i]);
    }
    for(int i=nrv; i>rv; i--) {
      nli = min(nli, idx[i]);
      nri = max(nri, idx[i]);
    }
    lv = nlv;
    rv = nrv;
    if(nli<l || nri>r) return tuple<int,int,int,int>(0,0,0,0);
    for(int i=nli; i<li; i++) {
      nlv = min(nlv, a[i]);
      nrv = max(nrv, a[i]);
    }
    for(int i=nri; i>ri; i--) {
      nlv = min(nlv, a[i]);
      nrv = max(nrv, a[i]);
    }
    li = nli;
    ri = nri;
  }
  return tuple<int,int,int,int>(li, ri, lv, rv);
}

pii interval[N];
void solve(int l, int r, const vector<Query>& q) {
  if(l==r) {
    for(const Query& it:q) {
      ans[it.i] = pii(l,r);
    }
    return;
  }

  int m = (l+r)/2;
  fill(interval+l, interval+r+1, pii(0,0));

  // expand left
  {
    //cerr<<"expand left"<<nl;
    int li, ri, lv, rv;
    tie(li,ri,lv,rv) = expand(l, r, m, m+1, min(a[m],a[m+1]), max(a[m],a[m+1]));
    while(l<=li && ri<=r) {
      //cerr<<"interval "<<li<<" "<<ri<<nl;
      assert(interval[li].first == 0);
      for(int i=li; i<=m && interval[i].first==0; i++) {
        interval[i] = pii(li,ri);
      }
      tie(li,ri,lv,rv) = expand(l, r, li-1, ri, min(a[li-1],lv), max(a[li-1],rv));
    }
  }

  // expand right
  {
    //cerr<<"expand right"<<nl;
    int li, ri, lv, rv;
    tie(li,ri,lv,rv) = expand(l, r, m, m+1, min(a[m],a[m+1]), max(a[m],a[m+1]));
    while(l<=li && ri<=r) {
      //cerr<<"interval "<<li<<" "<<ri<<nl;
      assert(interval[ri].first == 0);
      for(int i=ri; i>m && interval[i].first==0; i--) {
        interval[i] = pii(li,ri);
      }
      tie(li,ri,lv,rv) = expand(l, r, li, ri+1, min(a[ri+1],lv), max(a[ri+1],rv));
    }
  }

  vector<Query> lq, rq;
  for(const Query& it:q) {
    if(it.r <= m) lq.push_back(it);
    if(it.l > m) rq.push_back(it);

    if(interval[it.l].first && interval[it.r].first) {
      int left = min(interval[it.l].first, interval[it.r].first);
      int right = max(interval[it.l].second, interval[it.r].second);
      //cerr<<"improve "<<it.i<<": "<<it.l<<" "<<it.r<<" to "<<left<<" "<<right<<nl;
      if(right-left < ans[it.i].second-ans[it.i].first) ans[it.i] = pii(left,right);
    }
  }

  solve(l, m, lq);
  solve(m+1, r, rq);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin>>n;
  for(int i=1;i<=n;i++) {
    cin>>a[i];
    idx[a[i]] = i;
  }

  int m;
  cin>>m;
  vector<Query> q;
  for(int i=0;i<m;i++) {
    int l,r;
    cin>>l>>r;
    q.push_back({l,r,i});
    ans[i] = pii(1,n);
  }
  solve(1,n,q);

  for(int i=0;i<m;i++) {
    cout<<ans[i].first<<" "<<ans[i].second<<nl;
  }

  return 0;
}
