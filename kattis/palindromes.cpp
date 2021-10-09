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
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct SuffixArray {
  const int L; int skip, lvl; vector<vector<int>> P; vector<pair<pii,int>> M;
  SuffixArray(const string &s) : L(s.size()), P(1, vector<int>(L, 0)), M(L) {
    for (int i = 0; i < L-(L==1); i++) P[0][i] = int(s[i]);
    for (skip = 1, lvl = 1; skip < L; skip *= 2, lvl++) {
      P.push_back(vector<int>(L, 0));
      for (int i = 0; i < L; i++)
        M[i] = {{P[lvl-1][i], i+skip<L ? P[lvl-1][i + skip] : -1000}, i};
      sort(M.begin(), M.end());
      for (int i = 0; i < L; i++)
        P[lvl][M[i].second] = (i > 0 && M[i].first == M[i-1].first) ?
          P[lvl][M[i-1].second] : i; } }
  const vector<int>& get_sarray() { return P.back(); }
  //returns len of longest common prefix of s[i...L-1] and s[j...L-1], O(lg L)
  int lcp(int i, int j) {
    int len = 0; if (i == j) return L - i;
    for (int k = P.size() - 1; k >= 0 && i < L && j < L; k--)
      if (P[k][i] == P[k][j]) { i += 1 << k; j += 1 << k; len += 1 << k; }
    return len; }
};

const int N = 1<<17;
struct SegTree {
  vector<int> st[2*N];
  vector<ll> pre[2*N];
  void set(int i, int v) {
    st[N+i].push_back(v);
    pre[N+i].push_back(v);
  }
  void build() {
    for(int i=N-1;i>0;i--) {
      st[i] = st[2*i+1];
      st[i].insert(st[i].end(),st[2*i].begin(),st[2*i].end());
      sort(st[i].begin(),st[i].end());
      if(!st[i].empty()) {
        pre[i].resize(st[i].size());
        pre[i][0] = st[i][0];
        for(int j=1;j<st[i].size();j++) {
          pre[i][j] = pre[i][j-1]+st[i][j];
        }
      }
    }
  }
  ll query(int l, int r, int ub) {
    //cerr<<"query "<<l<<" "<<r<<" "<<ub<<nl;
    ll res = 0;
    for(l+=N,r+=N+1;l<r;l/=2,r/=2) {
      if(l&1) res += get(l++,ub);
      if(r&1) res += get(--r,ub);
    }
    return res;
  }
  ll get(int i, int ub) {
    auto it = lower_bound(st[i].begin(),st[i].end(),ub);
    ll res = (ll)ub * (st[i].end()-it);
    //cerr<<"get @ "<<i<<": "<<ub<<" * "<<(st[i].end()-it)<<" = "<<res<<nl;
    if(it!=st[i].begin()) res += pre[i][it-st[i].begin()-1];
    //cerr<<" += pre "<<it-st[i].begin()-1<<" : "<<pre[i][it-st[i].begin()-1]<<nl;
    //cerr<<"this is at : ";for(int jt:st[i]) //cerr<<jt<<" ";
    //cerr<<nl;
    return res;
  }
};

SegTree e_up, e_down, o_up, o_down;

ll sum(int l, int r) {
  //cerr<<" w/ sum: "<<(ll)r*(r+1)/2-(ll)l*(l-1)/2<<nl;
  return (ll)r*(r+1)/2 - (ll)l*(l-1)/2;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << fixed << setprecision(10);

  string s;
  cin>>s;
  int n=s.size();
  string t = s;
  reverse(t.begin(),t.end());
  SuffixArray sa(s+t);

  int even[n],odd[n];
  for(int i=0;i<n;i++) {
    odd[i] = sa.lcp(i,2*n-1-i);
    o_up.set(i,odd[i]-i);
    o_down.set(i,odd[i]+i);
    //cerr<<"o_up "<<i<<": "<<odd[i]<<" - "<<i<<" = "<<odd[i]-i<<nl;
    //cerr<<"o_down "<<i<<": "<<odd[i]<<" + "<<i<<" = "<<odd[i]+i<<nl;
    if(i>0) {
      even[i] = sa.lcp(i,2*n-i);
      e_up.set(i,even[i]-i);
      e_down.set(i,even[i]+i);
      //cerr<<"e_up "<<i<<": "<<even[i]<<" - "<<i<<" = "<<even[i]-i<<nl;
      //cerr<<"e_down "<<i<<": "<<even[i]<<" + "<<i<<" = "<<even[i]+i<<nl;
    }
    //cerr<<nl;
  }
  o_up.build();
  o_down.build();
  e_up.build();
  e_down.build();
  //cerr<<nl;

  int q;
  cin>>q;
  for(int i=0;i<q;i++) {
    int l,r;
    cin>>l>>r;
    --l; --r;
    ll ans = 0;
    int m = (l+r)/2;
    //cerr<<"o_up: ";
    ans += o_up.query(l, m, -l+1) + sum(l, m);
    //cerr<<"o_down: ";
    ans += o_down.query(m+1, r, r+1) - sum(m+1, r);
    //cerr<<"e_up: ";
    ans += e_up.query(l+1, m, -l) + sum(l+1, m);
    //cerr<<"e_down: ";
    ans += e_down.query(m+1, r, r+1) - sum(m+1, r);
    cout<<ans<<nl;
    //cerr<<nl;
  }

  return 0;
}
