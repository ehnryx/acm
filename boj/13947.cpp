#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "geometry/convex_hull.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
//constexpr ld EPS = 1e-9L;
constexpr ld EPS = 0.L;
random_device _rd; mt19937 rng(_rd());

using pt = complex<ld>;

namespace ubc {
ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
inline bool cmp_lex_i(const pt& a, const pt& b) {
  return a.imag()<b.imag()-EPS
    ||  (a.imag()<=b.imag()+EPS && a.real()<b.real()-EPS); }
using pol = vector<pt>;
pol chull(pol p) {
  sort(p.begin(), p.end(), cmp_lex_i); int top=0, bot=1, n=p.size();
  pol ch(2*n); for (int i = 0, d = 1; i < n && i >= 0; i += d) {
    // If no duplicates, can change <= 0 to < 0 to keep redundant points
    while (top>bot && cp(ch[top-1]-ch[top-2], p[i]-ch[top-2])<=0) top--;
    ch[top++] = p[i]; if (i == n-1) d = -1, bot = top;
  } ch.resize(max(1, top-1)); return ch; }
}

//using pt = point<ld>;

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  vector<pt> p;
  for(int i=0; i<n; i++) {
    char t;
    cin >> t;
    if(t == 'S') {
      p.emplace_back(i, 0);
      p.emplace_back(i+1, 0);
      p.emplace_back(i, 1);
      p.emplace_back(i+1, 1);
    } else if(t == 'T') {
      p.emplace_back(i, 0);
      p.emplace_back(i+1, 0);
      p.emplace_back(i+0.5L, sqrt(3.L)/2);
    } else {
      static constexpr int M = 1e4;
      pt c(i+0.5L, 0.5L);
      for(int j=0; j<M; j++) {
        //p.push_back(c + pt::polar(0.5L, (ld)j/M * 2*numbers::pi_v<ld>));
        p.push_back(c + 0.5L * exp(pt(0, (ld)j/M * 2*numbers::pi_v<ld>)));
      }
    }
  }
  auto h = ubc::chull(p);
  //auto h = convex_hull(1e-9L, p);
  ld ans = 0;
  for(int i=(int)size(h)-1, j=0; j<size(h); i=j++) {
    ans += abs(h[i] - h[j]);
  }
  cout << ans << nl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T = 1;
#ifdef MULTI_TEST
  cin >> T;
#endif
  for(int testnum=1; testnum<=T; testnum++) {
    solve_main(testnum, cin);
  }

  return 0;
}
