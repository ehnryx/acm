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
const ld PI = acos((ld)-1);
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
// handles ALL cases, uncomment/edit the 3 marked lines to exclude endpoints
bool seg_x_seg(pt a1, pt a2, pt b1, pt b2) {
  //if (eq(a1,a2) || eq(b1,b2)) return false; // uncomment to exclude endpoints
  ld za = abs(a2-a1), zb = abs(b2-b1); za=za>EPS?1/za:0; zb=zb>EPS?1/zb:0;
  int s1 = sgn(cp(a2-a1, b1-a1)*za), s2 = sgn(cp(a2-a1, b2-a1)*za);
  int s3 = sgn(cp(b2-b1, a1-b1)*zb), s4 = sgn(cp(b2-b1, a2-b1)*zb);
  if(!s1 && !s2 && !s3) { // collinear
    if (cmp_lex(a2, a1)) swap(a1, a2); if (cmp_lex(b2, b1)) swap(b1, b2);
    //return cmp_lex(a1, b2) && cmp_lex(b1, a2);//uncomment to exclude endpoints
    return !cmp_lex(b2, a1) && !cmp_lex(a2, b1);
  } return s1*s2 <= 0 && s3*s4 <= 0; } //change to < to exclude endpoints
 
inline pt line_inter(const pt &a, const pt &b, const pt &c, const pt &d) {
  return a + cp(c - a, d - c) / cp(b - a, d - c) * (b - a); }
 
// Projection of (a -> p) to vector (a -> b), SIGNED - positive in front
inline ld proj_dist(const pt &a, const pt &b, const pt &p) {
  return dp(b - a, p - a) / abs(b - a); }
 
// SIGNED distance. Pt on the right of vector (a -> b) will be NEGATIVE.
inline ld lp_dist(const pt &a, const pt &b, const pt &p) {
  return cp(b - a, p - a) / abs(b - a); }
 
// Line segment (a, b) to pt p distance.
inline ld lsp_dist(const pt &a, const pt &b, const pt &p) {
  return dp(b - a, p - a) > 0 && dp(a - b, p - b) > 0 ?
    abs(cp(b - a, p - a) / abs(b - a)) : min(abs(a - p), abs(b - p)); }
 
// Closest pt on line segment (a, b) to pt p.
inline pt lsp_closest(const pt &a, const pt &b, const pt &p) {
  if (dp(b - a, p - a) > 0 && dp(a - b, p - b) > 0)
    return abs(cp(b-a, p-a)) < EPS ? p : line_inter(a, b, p, p+(a-b)*pt(0,1));
  return abs(a - p) < abs(b - p) ? a : b; }
 
// Area of a polygon (convex or concave). Always non-negative.
ld area(const pol &v) { ld s = 0; int n = v.size();
  for(int i = n-1, j = 0; j < n; i = j++) s += cp(v[i], v[j]); return abs(s)/2;}
 
// orientation does not matter
pt centroid(const pol &v) {
  pt res; ld A = 0; int n = v.size();
  for(int i=n-1,j=0;j<n;i=j++) A+=cp(v[i],v[j]), res+=(v[i]+v[j])*cp(v[i],v[j]);
  return abs(A) < EPS ? res : res/3.L/A; }
 
// Left of the vector (a -> b) will be cut off. Convex polygons tested UVa 10117
// Simple polygon tested KTH Challenge 2013 G
pol cut_polygon(const pol &v, const pt &a, const pt &b) { pol out;
  for(int i = v.size() - 1, j = 0; j < v.size(); i = j++) {
    if(cp(b-a, v[i]-a) < EPS) out.push_back(v[i]);
    if(sgn(cp(b-a, v[i]-a)) * sgn(cp(b-a, v[j]-a)) < 0) {
      pt p = line_inter(a, b, v[i], v[j]);
      if(!out.size() || abs(out.back() - p) > EPS) out.push_back(p); } }
  while(out.size() && abs(out[0] - out.back()) < EPS) out.pop_back();
  return out; }
 
// Does NOT include points on the ends of the segment.
inline bool on_segment(const pt &a, const pt &b, const pt &p) {
  return abs(cp(b-a, p-a)) < EPS && dp(b-a, p-a) > 0 && dp(a-b, p-b) > 0; }
 
// Checks if p lies on the boundary of a polygon v.
inline bool on_boundary(const pol &v, const pt &p) { bool res = false;
  for(int i=v.size()-1,j=0;j<v.size();i=j++)
    res |= on_segment(v[i], v[j], p) | (abs(p-v[i]) < EPS); return res; }
 
// orientation does not matter !!!
bool pt_in_polygon(const pt &p, const pol &v){ if(on_boundary(v,p)) return true;
  ld res = 0; for(int i = v.size() - 1, j = 0; j < v.size(); i = j++)
    res += atan2(cp(v[i] - p, v[j] - p), dp(v[i] - p, v[j] - p));
  return abs(res) > 1; } // will be either 2*PI or 0
////////////////////////////////////////////////////////////////////////////////
// Triangle area from three medians
////////////////////////////////////////////////////////////////////////////////
ld triAreaFromMedians(ld ma, ld mb, ld mc) { // Tested UVa 10347
    ld x = (ma + mb + mc)/2, a = x * (x - ma) * (x - mb) * (x - mc);
    return a < 0.0 ? -1.0 : sqrt(a) * 4.0 / 3.0; }
////////////////////////////////////////////////////////////////////////////////
// Rectangle in rectangle
////////////////////////////////////////////////////////////////////////////////
bool contains(ll W, ll H, ll w, ll h) { // tan(t) = (Hw-Wh)/(Ww-Hh)
  if ((w <= W && h <= H) || (w <= H && h <= W)) return true;
  if ((W <= w && W <= h) || (H <= w && H <= h)) return false;
  ll kc = H*w - W*h,   km = w*w - h*h,   xc = w * kc,   yc = W * km - h * kc;
  return xc*xc + yc*yc >= km*km * w*w; }
////////////////////////////////////////////////////////////////////////////////
// Closest pair in n*log(n). Returns the pair. Assumes v.size() >= 2.
////////////////////////////////////////////////////////////////////////////////
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
  return bestpair; }
////////////////////////////////////////////////////////////////////////////////
// Circle-circle intersection (TESTED UVa 453)
////////////////////////////////////////////////////////////////////////////////
// Return number of intersections. Circles must not be identical.
int cc_inter(pt p1, ld r1, pt p2, ld r2, pt &i1, pt &i2) {
  ld dq=norm(p1-p2), rq=r1*r1-r2*r2; pt c=(p1+p2)*0.5L + (p2-p1)*rq*0.5L/dq;
  ld dt=2.0*dq*(r1*r1+r2*r2)-dq*dq-rq*rq;
  if(dt < -EPS) return 0; if(dt < EPS) { i1=i2=c; return 1; }
  dt=sqrt(dt)*0.5/dq; i1=c+(p2-p1)*pt(0,1)*dt; i2=c-(p2-p1)*pt(0,1)*dt;
  return 2; }
////////////////////////////////////////////////////////////////////////////////
// Area of intersection of 2 circles (UNTESTED)
////////////////////////////////////////////////////////////////////////////////
ld cc_area(pt p1, ld r1, pt p2, ld r2) { if(r2 < r1) swap(p1, p2), swap(r1, r2);
  ld d = abs(p2 - p1); if (d + r1 < r2 + EPS) return r1*r1*PI;
  if (d >= r1 + r2) return 0;
  ld dA = (d*d + r1*r1 - r2*r2)/d/2, dB = d-dA;
  return r1*r1*acos(dA/r1) - dA*sqrt(r1*r1-dA*dA)
       + r2*r2*acos(dB/r2) - dB*sqrt(r2*r2-dB*dB); }
////////////////////////////////////////////////////////////////////////////////
// Circles tangents (TESTED Chicago2012-H)
////////////////////////////////////////////////////////////////////////////////
pair<pt, pt> circle_tangent(ld r1, ld r2, ld d, int k) { // use the fcn below
  ld dr = (k & 2) ? (-r1-r2) : (r2-r1); ld t = asin(dr / d);
  pt p1=polar(r1, PI/2+t), p2=polar(r2, PI/2+t); if(k&2) p2*=-1; p2+=pt(d,0);
  if(k&1){ p1=pt(p1.real(),-p1.imag()); p2=pt(p2.real(),-p2.imag()); }
  return make_pair(p1, p2); }
// tested 2008wf conveyor; tangent of 2 circles; CAUTION: INTERSECTION IS BAD
// k=0 top-top, k=1 bot-bot, k=2 top-bot, k=3 bot-top. Also works for points.
pair<pt, pt> circle_tangent(pt p1, ld r1, pt p2, ld r2, int k) {
  // translate/rotate so c1 at (0,0), c2 at x-axis
  pt d = p2-p1; pair<pt, pt> p = circle_tangent(r1, r2, abs(d), k); d /= abs(d);
  p.first *= d; p.second *= d; p.first += p1; p.second += p1; return p;
}
////////////////////////////////////////////////////////////////////////////////

vector<pt> p;
int solve(int n, int cur) {
	//cerr << "SOLVE " << cur << nl;
	int base = 1;
	vector<pair<ld,int>> line;
	for (int i=0; i<n; i++) {
		if (i==cur) continue;
		if (eq(p[i], p[cur])) base++;
		else {
			ld d = abs(p[i]-p[cur]);
			pt a, b; ld s, t;
			if (d < 2+EPS) {
				tie(a,b) = circle_tangent(p[cur], 1, p[i], 1, 0);
				t = arg(a-p[cur])+EPS/2;
				tie(a,b) = circle_tangent(p[cur], 1, p[i], 1, 1);
				s = arg(a-p[cur])-EPS/2;
				line.push_back(pair<ld,int>(s,-1));
				line.push_back(pair<ld,int>(2*PI+t,1));
				//cerr << "add " << s << " " << t << nl;
				if (s < t) {
					line.push_back(pair<ld,int>(2*PI+s,-1));
					line.push_back(pair<ld,int>(t,1));
				}
			} else {
				tie(a,b) = circle_tangent(p[cur], 1, p[i], 1, 0);
				t = arg(a-p[cur])+EPS/2;
				tie(a,b) = circle_tangent(p[cur], 1, p[i], 1, 2);
				s = arg(a-p[cur])-EPS/2;
				line.push_back(pair<ld,int>(s,-1));
				line.push_back(pair<ld,int>(2*PI+t,1));
				//cerr << "add " << s << " " << t << nl;
				if (s < t) {
					line.push_back(pair<ld,int>(2*PI+s,-1));
					line.push_back(pair<ld,int>(t,1));
				}
				tie(a,b) = circle_tangent(p[cur], 1, p[i], 1, 3);
				t = arg(a-p[cur])+EPS/2;
				tie(a,b) = circle_tangent(p[cur], 1, p[i], 1, 1);
				s = arg(a-p[cur])-EPS/2;
				line.push_back(pair<ld,int>(s,-1));
				line.push_back(pair<ld,int>(2*PI+t,1));
				//cerr << "add " << s << " " << t << nl;
				if (s < t) {
					line.push_back(pair<ld,int>(2*PI+s,-1));
					line.push_back(pair<ld,int>(t,1));
				}
			}
		}
	}
	sort(line.begin(), line.end());

	int res = 0;
	int cval = 0;
	for (const auto& it : line) {
		//cerr << it.first << " " << it.second << nl;
		cval -= it.second;
		res = max(res, cval);
		assert(cval >= 0);
	}
	return base+res;
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

	int n;
	cin >> n;

	ld x, y;
	for (int i=0; i<n; i++) {
		cin >> x >> y;
		p.push_back(pt(x,y));
	}

	int ans = 0;
	for (int i=0; i<n; i++) {
		ans = max(ans, solve(n, i));
	}
	cout << ans << nl;

	return 0;
}
