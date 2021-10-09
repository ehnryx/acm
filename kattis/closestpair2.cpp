#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

inline bool cmp_lex(const pt& a, const pt& b) {
  return a.real()<b.real()-EPS||(a.real()<b.real()+EPS&&a.imag()<b.imag()-EPS);}
inline bool cmp_lex_i(const pt& a, const pt& b) {
  return a.imag()<b.imag()-EPS||(a.imag()<b.imag()+EPS&&a.real()<b.real()-EPS);}
pair<pt, pt> closest_pair(vector<pt> v) { // Tested UVa 10245, 11378
  sort(v.begin(), v.end(), cmp_lex);
  ld best = 1e99; auto low = 0u; pair<pt, pt> bestpair;
  set<pt, bool(*)(const pt&,const pt&)> help(cmp_lex_i);
  for(auto i = 0u; i < v.size(); i++) {
    while(low < i && (v[i] - v[low]).real() > best) help.erase(v[low++]);
    for(auto it = help.lower_bound(v[i] - pt(1e99, best));
          it != help.end() && (*it - v[i]).imag() < best; it++)
      if (abs(*it - v[i]) < best)
        best = abs(*it - v[i]), bestpair = make_pair(*it, v[i]);
    help.insert(v[i]); }
  return bestpair;
}

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  for (int n; cin>>n && n; ) {
    vector<pt> p;
    for (int i=0; i<n; i++) {
      ld x, y;
      cin >> x >> y;
      p.push_back(pt(x,y));
    }
    pt s, t;
    tie(s,t) = closest_pair(p);
    cout << s.real() << " " << s.imag() << " " << t.real() << " " << t.imag() << nl;
  }

  return 0;
}
