#include <bits/stdc++.h>
using namespace std;

#define nl '\n'

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef pair<int,int> pii;
typedef vector<pt> pol;

const ld EPS = 1e-11;
const int INF = 0x3f3f3f3f;

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }

bool cmp_lex_i(const pt& a, const pt& b) {
  return a.imag()<b.imag()-EPS || (a.imag()<b.imag()+EPS && a.real()<b.real()-EPS);
}

ld lp_dist(const pt& a, const pt& b, const pt& p) {
  return cp(b-a, p-a) / abs(b-a);
}

pol chull(pol p) {
  sort(p.begin(), p.end(), cmp_lex_i); int top=0, bot=1; pol ch(2*p.size());
  for (int i=0, d=1; i<p.size() && i>=0; i+=d) {
    while (top>bot && cp(ch[top-1]-ch[top-2], p[i]-ch[top-2]) <= 0) top--;
    ch[top++] = p[i]; if (i==p.size()-1) d=-1, bot=top;
  } ch.resize(max(1,top-1)); return ch;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << fixed << setprecision(2);

  for (int n, tt=1; cin >> n && n; tt++) {
    vector<pt> p;
    for (int i=0; i<n; i++) {
      int x, y;
      cin >> x >> y;
      p.push_back(pt(x,y));
    }
    p = chull(p);

    n = p.size();
    ld ans = INF;
    for (int i=0; i<n; i++) {
      int j = (i+1==n ? 0 : i+1);
      ld cur = 0;
      for (int k=0; k<n; k++) {
        cur = max(cur, abs(lp_dist(p[i], p[j], p[k])));
      }
      ans = min(ans, cur);
    }
    ans = ceil(ans*100-EPS)/100;
    cout << "Case " << tt << ": " << ans << nl;
  }

  return 0;
}
