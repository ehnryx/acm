//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
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
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 200 + 7;
int cap[N];

ld ncr[N][N];
ld choose(int n, int r) {
  if(r<0 || r>n) return 0;
  return ncr[n][r];
}

// params
int n, g, t;

// probability of filling [l, r]
ld pf[N][N];
ld pfill(int l, int r) {
  if(l > r) return 1; // always fill empty interval
  if(pf[l][r] > -1) return pf[l][r];
  ld res = 0;
  for(int i=l; i<=r; i++) {
    // if last to be filled is i
    ld cur = (ld) (cap[i] - cap[l-1]) / g;
    // fill left and right and interleave
    cur *= pfill(l, i-1) * pfill(i+1, r) * choose(r-l, i-l);
    res += cur;
  }
  //cerr<<"fil "<<l<<" "<<r<<" = "<<res<<nl;
  assert(res > -1);
  return pf[l][r] = res;
}

ld pre[N][N];
ld prefix(int r, int k) {
  if(r <= 0) return (k == 0); // can fill empty with nothing
  if(k > r) return 0; // too much to place
  if(pre[r][k] > -1) return pre[r][k];
  if(k == r) return pre[r][k] = pfill(1, r); // must fill when k=r
  ld res = prefix(r-1, k); // skip
  for(int j=1; j<=k; j++) {
    // place j consecutive, then one empty, and interleave
    res += prefix(r-j-1, k-j) * pfill(r-j+1, r) * choose(k, j);
  }
  //cerr<<"pre "<<r<<" "<<k<<" = "<<res<<nl;
  assert(res > -1);
  return pre[r][k] = res;
}

ld suf[N][N];
ld suffix(int s, int k) {
  if(s >= n+t+1) return (k == 0);
  if(k > n+t-s+1) return 0;
  if(suf[s][k] > -1) return suf[s][k];
  if(k == n+t-s+1) return suf[s][k] = pfill(s, n+t);
  ld res = suffix(s+1, k);
  for(int j=1; j<=k; j++) {
    res += suffix(s+j+1, k-j) * pfill(s, s+j-1) * choose(k, j);
  }
  //cerr<<"suf "<<s<<" "<<k<<" = "<<res<<nl;
  assert(res > -1);
  return suf[s][k] = res;
}

// actually computes pfill(l,r) * expectation(l,r)
ld ev[N][N];
ld expect(int l, int r) {
  if(l > r) return 0;
  if(ev[l][r] > -1) return ev[l][r];
  ld res = 0;
  for(int i=l; i<=r; i++) {
    ld p = (ld) (cap[i] - cap[l-1]) / g * choose(r-l, i-l);
    ld last = (i <= n ? (ld) (cap[l-1]+1 + cap[i]) / 2 : 0);
    last *= p * pfill(l, i-1) * pfill(i+1, r);
    ld left = expect(l, i-1) * p * pfill(i+1, r);
    ld right = expect(i+1, r) * p * pfill(l, i-1);
    ld cur = last + left + right;
    res += cur;
    //cerr<<"expect "<<l<<" "<<r<<" w/ last "<<i<<" -> "<<cur<<nl;
  }
  //cerr<<"expect "<<l<<" "<<r<<" = "<<res<<nl;
  assert(res > -1);
  return ev[l][r] = res;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  for(int i=0; i<N; i++) {
    ncr[i][0] = ncr[i][i] = 1;
    for(int j=1; j<i; j++) {
      ncr[i][j] = ncr[i-1][j] + ncr[i-1][j-1];
    }
  }

  fill(&pf[0][0], &pf[0][0] + N*N, -7);
  fill(&pre[0][0], &pre[0][0] + N*N, -7);
  fill(&suf[0][0], &suf[0][0] + N*N, -7);
  fill(&ev[0][0], &ev[0][0] + N*N, -7);

  cin >> n >> g >> t;
  for(int i=1; i<=n; i++) {
    cin >> cap[i];
    cap[i] = min(cap[i], g);
  }
  sort(cap+1, cap+1+n);
  for(int i=1; i<=t; i++) {
    cap[n+i] = g;
  }
  //cerr<<"CAPS: "; for(int i=1; i<=n+t; i++) { //cerr<<cap[i]<<" "; }
  //cerr<<nl;

  ld ans = 0;
  for(int i=1; i<=n+t; i++) {
    for(int j=1; j<=i; j++) {
      int len = i-j+1;
      if(len > t) continue;
      for(int k=0; k<=t-len; k++) {
        // place k on left and t-len-k on right
        ld p = prefix(j-2, k) * choose(t, k); // fill left, interleave
        p *= suffix(i+2, t-len-k) * choose(t-k, t-len-k); // fill right, interleave
        ld cur = p * expect(j, i); // expected total if we fill the range
        //cerr<<"X "<<j<<" "<<i<<" -> "<<cur<<" kps: "<<k<<" "<<prefix(j-2,k)<<" "<<suffix(i+2,t-len-k)<<nl;
        ans += cur;
      }
    }
  }
  cout << ans << nl;

  return 0;
}
