#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
int sgn(const ld& x) { return abs(x) < EPS ? 0 : x < 0 ? -1 : 1; }
bool cmp_lex(const pt& a, const pt& b) {
  return a.real()<b.real()-EPS
    ||  (a.real()<=b.real()+EPS && a.imag()<b.imag()-EPS); }
bool seg_x_seg(pt a, pt b, pt c, pt d) {
  ld sa=abs(b-a), sc=abs(d-c); sa=sa>EPS?1/sa:0; sc=sc>EPS?1/sc:0;
  int r1 = sgn(cp(b-a, c-a) * sa), r2 = sgn(cp(b-a, d-a) * sa);
  int r3 = sgn(cp(d-c, a-c) * sc), r4 = sgn(cp(d-c, b-c) * sc);
  if(!r1 && !r2 && !r3) { // collinear
    if(cmp_lex(b, a)) swap(a, b);
    if(cmp_lex(d, c)) swap(c, d);
    return !cmp_lex(d, a) && !cmp_lex(b, c);
  } return r1*r2 <= 0 && r3*r4 <= 0;
}


// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  for(int n; cin >> n && n; ) {
    vector<pair<pt,pt>> segs;
    for(int i=0; i<n; i++) {
      ld a, b, c, d;
      cin >> a >> b >> c >> d;
      segs.emplace_back(pt(a, b), pt(c, d));
    }
    int ans = 0;
    for(int i=0; i<n; i++) {
      for(int j=0; j<i; j++) {
        if(!seg_x_seg(segs[i].first, segs[i].second, segs[j].first, segs[j].second)) continue;
        for(int k=0; k<j; k++) {
          ans += seg_x_seg(segs[i].first, segs[i].second, segs[k].first, segs[k].second)
            && seg_x_seg(segs[j].first, segs[j].second, segs[k].first, segs[k].second);
        }
      }
    }
    cout << ans << nl;
  }

  return 0;
}
