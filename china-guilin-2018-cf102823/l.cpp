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
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

int sgn(ld x) {
  return x<-EPS ? -1 : x>EPS ? 1 : 0;
}

ld cp(const pt& a, const pt& b) { return imag(conj(a) * b); }
ld dp(const pt& a, const pt& b) { return real(conj(a) * b); }
pt line_inter(const pt &a, const pt &b, const pt &c, const pt &d) {
  return a + cp(c - a, d - c) / cp(b - a, d - c) * (b - a); }

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
    return cmp_lex(a, d) && cmp_lex(c, b);
  } return r1*r2 < 0 && r3*r4 < 0; }

pair<pt,pt> read_seg() {
  int a, b, x, y;
  cin >> a >> b >> x >> y;
  return pair(pt(a, b), pt(x, y));
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

  int T;
  cin >> T;
  for(int testnum=1; testnum<=T; testnum++) {
    cout << "Case " << testnum << ": ";

    auto [a, b] = read_seg();
    auto [c, d] = read_seg();
    int sc = sgn(cp(b-a, c-a));
    int sd = sgn(cp(b-a, d-a));

    if(sc * sd < 0 || (sc == 0 && sd == 0)) {
      cout << 0 << nl;
    }

    else if(sc * sd > 0) {
      if(seg_x_seg(a, c, b, d)) swap(c, d);
      pt x = line_inter(a, c, b, d);
      int sx = sgn(cp(b-a, x-a));
      if(sx * sc < 0) {
        cout << abs(cp(b-a, x-a)) / 2 << nl;
      } else {
        cout << "inf" << nl;
      }
    }

    else {
      if(sc) {
        swap(c, d);
        swap(sc, sd);
      }
      if(abs(c-a) + abs(c-b) > abs(b-a) + EPS) {
        cout << 0 << nl;
      } else {
        cout << "inf" << nl;
      }
    }
  }

  return 0;
}
