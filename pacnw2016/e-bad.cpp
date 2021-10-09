#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

////////////////////////////////////////////////////////////////////////////////
// General 2D geometry, Polygon cutting, Point in polygon
////////////////////////////////////////////////////////////////////////////////
ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
ld dp(const pt& a, const pt& b) { return real(conj(a)*b); }
// dist(const pt& a, const pt& b) ==> abs(a-b)
inline bool eq(const pt &a, const pt &b) { return abs(a-b) < EPS; }
inline ld sgn(const ld& x) { return abs(x) < EPS ? 0 : x/abs(x); }
inline bool cmp_lex(const pt& a, const pt& b) {
  return a.real()<b.real()-EPS||(a.real()<b.real()+EPS&&a.imag()<b.imag()-EPS);}
inline bool cmp_lex_i(const pt& a, const pt& b) {
  return a.imag()<b.imag()-EPS||(a.imag()<b.imag()+EPS&&a.real()<b.real()-EPS);}
////////////////////////////////////////////////////////////////////////////////
// 2D convex hull (TESTED SPOJ BSHEEP, UVA 11096)
////////////////////////////////////////////////////////////////////////////////
// Assumes nondegenerate, i.e. CH is not a line. 
pol chull(pol p) {
  sort(p.begin(), p.end(), cmp_lex_i); int top=0, bot=1; pol ch(2*p.size());
  for (int i=0, d=1; i < p.size() && i >= 0; i += d) {
  // If there are no duplicates, can change <= 0 to < 0 to keep redundant points
    while (top > bot && cp(ch[top-1]-ch[top-2], p[i]-ch[top-2]) <= 0) top--;
    ch[top++] = p[i]; if (i == p.size()-1) d = -1, bot = top;
  } ch.resize(max(1, top-1)); return ch;
} // pts returned in ccw order.
ld poly_area(const pol &v) { ld s = 0; int n = v.size();
  for (int i = n-1, j = 0; j < n; i = j++) s += cp(v[i], v[j]);
  return abs(s);
}

ld tri_area(const pt& a, const pt& b, const pt& c) {
  return cp(b-a, c-a);
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

  int n, k;
  cin >> n >> k;

  int x, y;
  vector<pt> in, out;
  for (int i=0; i<k; i++) {
    cin >> x >> y;
    in.emplace_back(x,y);
    out.emplace_back(x,y);
  }
  for (int i=k; i<n; i++) {
    cin >> x >> y;
    out.emplace_back(x,y);
  }
  in = chull(in);
  out = chull(out);
  ld original = poly_area(in);
  k = in.size();

  ////cerr << "done convex hull, w/ area " << original << endl;

  auto get_id = [&] (int i) {
    if (i<0) return i+k;
    else if (i<k) return i;
    else return i-k;
  };

  vector<ld> parea(2*k, 0);
  for (int i=1; i<2*k; i++) {
    parea[i] = parea[i-1] + cp(in[get_id(i-1)], in[get_id(i)]);
    //cerr << i << ": " << parea[i] << nl;
  }

  auto get_area = [&] (int a, int b) {
    a = get_id(a);
    b = get_id(b);
    ld tri = cp(in[b], in[a]);
    if (a > b) b += k;
    return parea[b] - parea[a] + tri;
  };

  ////cerr << "done precomputing parea" << endl;

  int left, right;
  for (left = 0; left < k; left++) {
    int i = get_id(left-1);
    int j = get_id(left+1);
    if (cp(in[left]-out[0], in[j]-in[left]) > 0
      && cp(in[left]-out[0], in[i]-in[left]) >= 0) {
      break;
    }
  }
  for (right = 0; right < k; right++) {
    int i = get_id(right-1);
    int j = get_id(right+1);
    if (cp(in[right]-out[0], in[j]-in[right]) <= 0
      && cp(in[right]-out[0], in[i]-in[right]) < 0) {
      break;
    }
  }
  assert(left<k && right<k);

  ////cerr << "done initializing rotating callipers" << endl;

  ld ans = 0;
  for (const pt& p : out) {
    if (abs(p-in[left]) < EPS) {
      right = get_id(left-1);
      left = get_id(left+1);
    } else {
      int i, j;
      i = get_id(left-1);
      j = get_id(left+1);
      while (!(cp(in[left]-p, in[j]-in[left]) > 0
        && cp(in[left]-p, in[i]-in[left]) >= 0)) {
        left = get_id(left+1);
        i = get_id(left-1);
        j = get_id(left+1);
      }
      i = get_id(right-1);
      j = get_id(right+1);
      while (!(cp(in[right]-p, in[j]-in[right]) <= 0
        && cp(in[right]-p, in[i]-in[right]) < 0)) {
        right = get_id(right+1);
        i = get_id(right-1);
        j = get_id(right+1);
      }
    }
    ans = max(ans, tri_area(p, in[left], in[right]) - get_area(right, left));
    //cerr << p << " -> " << in[left] << " " << in[right];
    //cerr << " + " << tri_area(p,in[left],in[right])-get_area(right,left) << nl;
  }
  cout << (ans+original)/2 << nl;

  return 0;
}
