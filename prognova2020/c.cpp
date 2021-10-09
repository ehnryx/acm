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

vector<pt> v = {
  {0,0}, {0,1}, {0,2},
  {1,0}, {1,1}, {1,2},
  {2,0}, {2,1}, {2,2},
};

pt dir(const pt& x) {
  assert(abs(x)>EPS);
  return x / abs(x);
}

ld cp(const pt& a, const pt& b) {
  return imag(conj(a)*b);
}
int sgn(const ld& x) {
  return abs(x)<EPS ? 0 : x<0 ? -1 : 1;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  string s;
  cin >> s;

  const int n = 9;
  int p[n];
  for(int i=0; i<n; i++) {
    p[i] = i;
  }

  int ans = 0;
  do {
    pt pre = v[p[0]];
    pt cur = v[p[1]];
    pt first = (pre+cur) / (ld)2;
    if(abs(first.real()-round(first.real()))<EPS && abs(first.imag()-round(first.imag()))<EPS) {
      continue;
    }
    bool ok = true;
    for(int i=2; i<n && ok; i++) {
      pt nxt = v[p[i]];
      pt mid = (cur+nxt) / (ld)2;
      if(abs(mid.real()-round(mid.real()))<EPS && abs(mid.imag()-round(mid.imag()))<EPS) {
        bool bad = true;
        for(int j=0; j<i; j++) {
          if(abs(v[p[j]] - mid) < EPS) {
            bad = false;
            break;
          }
        }
        if(bad) {
          ok = false;
          break;
        }
      }
      int g = sgn(cp(cur-pre, nxt-cur));
      if(g<0) {
        ok &= (s[i-2] == '?' || s[i-2] == 'R');
      } else if(g>0) {
        ok &= (s[i-2] == '?' || s[i-2] == 'L');
      } else {
        if(abs(dir(cur-pre) - dir(nxt-cur)) < EPS) {
          ok &= (s[i-2] == '?' || s[i-2] == 'S');
        } else {
          ok &= (s[i-2] == '?' || s[i-2] == 'A');
        }
      }
      pre = cur;
      cur = nxt;
    }
    ans += ok;
  } while(next_permutation(p,p+n));

  cout << ans << nl;

  return 0;
}
