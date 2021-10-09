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

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
int sgn(const ld& x) { return abs(x)<EPS ? 0 : (x<0 ? -1 : 1); }
inline bool cmp_lex_i(const pt& a, const pt& b) {
  return a.imag()<b.imag()-EPS||(a.imag()<b.imag()+EPS&&a.real()<b.real()-EPS);}
vector<pt> chull(vector<pt> p) {
  sort(p.begin(), p.end(), cmp_lex_i); int top=0, bot=1; vector<pt> ch(2*p.size());
  for (int i=0, d=1; i < p.size() && i >= 0; i += d) {
  // If there are no duplicates, can change <= 0 to < 0 to keep redundant points
    while (top > bot && sgn(cp(ch[top-1]-ch[top-2], p[i]-ch[top-2])) < 0) top--;
    ch[top++] = p[i]; if (i == p.size()-1) d = -1, bot = top;
  } ch.resize(max(1, top-1)); return ch;
} // pts returned in ccw order.

pii to_pii(const pt& v) {
  return pii(round(v.real()), round(v.imag()));
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin>>T;
  while(T--) {
    int n;
    cin>>n;
    vector<pt> p;
    map<pii,int> idx;
    for(int i=0;i<n;i++) {
      int x,y;
      cin>>x>>y;
      idx[pii(x,y)] = i;
      p.push_back(pt(x,y));
    }
    vector<pt> hull = chull(p);

    set<pii> ignore;
    int cut = n;
    for(int i=0;i<n;i++) {
      if(i>0 && hull[i].imag() < hull[i-1].imag()) {
        cut = i;
        break;
      } else {
        ignore.insert(to_pii(hull[i]));
      }
    }
    hull.resize(cut);

    vector<pt> rest;
    for(const pt& it:p) {
      if(!ignore.count(to_pii(it))) {
        rest.push_back(it);
      }
    }
    sort(rest.begin(),rest.end(),cmp_lex_i);
    reverse(rest.begin(),rest.end());
    for(const pt& it:rest) {
      cout<<idx[to_pii(it)]<<" ";
    }
    for(const pt& it:hull) {
      cout<<idx[to_pii(it)]<<" ";
    }
    cout<<nl;
  }

  return 0;
}
