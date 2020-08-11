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
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
	os << "[ ";
	for(const T& it:v) os << it << ",  ";
	return os << "]";
}

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
ld dp(const pt& a, const pt& b) { return real(conj(a)*b); }
inline bool eq(const pt &a, const pt &b) { return abs(a-b) < EPS; }
inline ld sgn(const ld& x) { return abs(x) < EPS ? 0 : x/abs(x); }
inline bool cmp_lex(const pt& a, const pt& b) {
	return a.real()<b.real()-EPS||(a.real()<b.real()+EPS&&a.imag()<b.imag()-EPS);
}
inline bool cmp_lex_i(const pt& a, const pt& b) {
	return a.imag()<b.imag()-EPS||(a.imag()<b.imag()+EPS&&a.real()<b.real()-EPS);
}
pol chull(pol p) {
	sort(p.begin(), p.end(), cmp_lex_i); int top=0, bot=1; pol ch(2*p.size());
	for (int i=0, d=1; i < p.size() && i >= 0; i += d) {
		// If there are no duplicates, can change <= 0 to < 0 to keep redundant points
		while (top > bot && cp(ch[top-1]-ch[top-2], p[i]-ch[top-2]) <= 0) top--;
		ch[top++] = p[i]; if (i == p.size()-1) d = -1, bot = top;
	} ch.resize(max(1, top-1)); return ch;
} // pts returned in ccw order.

vector<pt> get_hull(const vector<pt>& p, const pt& a, const pt& b) {
	//cerr<<"getting hull from "<<a<<" to "<<b<<nl;
	//cerr<<"with points "<<p<<nl;
	int inc = 0;
	vector<pt> res = {a};
	for(const pt& v : p) {
		if(inc) {
			res.push_back(v);
		}
		if(eq(v,a) && !inc) inc ^= 1;
		else if(eq(v,b) && inc) inc ^= 1;
	}
	if(!inc) return res;
	for(const pt& v : p) {
		if(inc) {
			res.push_back(v);
		}
		if(eq(v,a) && !inc) assert(false);
		else if(eq(v,b) && inc) break;
	}
	return res;
}

ld perimeter(const vector<pt>& v) {
	ld res = 0;
	for(int i=1;i<v.size();i++) {
		res += abs(v[i]-v[i-1]);
	}
	return res;
}

ld solve_inner(const vector<pt>& h, const vector<pt>& p, const pt& rem) {
	//cerr<<"solve inner @ "<<h<<nl;
	ld ans = 0;
	for(int a=1;a+1<h.size();a++) {
		int i = a-1;
		int j = a+1;
		ld lb = min(min(h[i].real(), h[j].real()), h[a].real());
		ld rb = max(max(h[i].real(), h[j].real()), h[a].real());
		auto lit = lower_bound(p.begin(), p.end(), pt(lb-0.1,0), cmp_lex);
		auto rit = lower_bound(p.begin(), p.end(), pt(rb+0.1,0), cmp_lex);
		vector<pt> cur;
		for(auto it=lit; it!=rit; it++) {
			if(eq(*it,h[a]) || eq(*it,rem)) continue;
			cur.push_back(*it);
		}
		vector<pt> hull = chull(cur);
		vector<pt> inner = get_hull(hull, h[i], h[j]);
		//cerr<<"got hull "<<inner<<nl;
		assert(inner.front() == h[i] && inner.back() == h[j]);
		ld outer = abs(h[i]-h[a]) + abs(h[a]-h[j]);
		ld perim = perimeter(inner);
		assert(outer-perim > EPS);
		ans = max(ans, outer - perim);
	}
	return ans;
}

const int N = 1<<17;
ld st[2*N];
void insert(int i, ld x) {
	st[i+=N] = x;
	for(i/=2;i;i/=2) {
		st[i] = max(st[2*i],st[2*i+1]);
	}
}
ld query(int l, int r) {
	ld res = 0;
	for(l+=N,r+=N+1;l<r;l/=2,r/=2) {
		if(l&1) res = max(res, st[l++]);
		if(r&1) res = max(res, st[--r]);
	}
	return res;
}
ld query_range(int l, int r) {
	if(l<=r) return query(l,r);
	return max(query(0,r), query(l,N-1));
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin >> n;

	vector<pt> p;
	for(int i=0;i<n;i++) {
		int x, y;
		cin >> x >> y;
		p.push_back(pt(x,y));
	}
	sort(p.begin(), p.end(), cmp_lex);

	vector<pt> h = chull(p);
	int m = h.size();
	////cerr<<"got hull "<<h<<nl;
	////cerr<<nl;

	ld ans = 0;

	for(int i=0;i<m;i++) {
		// two adjacent
		{
			int a = (i+1 == m ? 0 : i+1);
			int b = (a+1 == m ? 0 : a+1);
			int j = (b+1 == m ? 0 : b+1);
			//cerr<<"rem two adj "<<a<<" "<<b<<nl;
			ld lb = min(min(h[i].real(), h[j].real()), min(h[a].real(), h[b].real()));
			ld rb = max(max(h[i].real(), h[j].real()), max(h[a].real(), h[b].real()));
			auto lit = lower_bound(p.begin(), p.end(), pt(lb-0.1,0), cmp_lex);
			auto rit = lower_bound(p.begin(), p.end(), pt(rb+0.1,0), cmp_lex);
			vector<pt> cur;
			for(auto it=lit; it!=rit; it++) {
				if(eq(*it,h[a]) || eq(*it,h[b])) continue;
				cur.push_back(*it);
			}
			vector<pt> hull = chull(cur);
			vector<pt> inner = get_hull(hull, h[i], h[j]);
			//cerr<<"got hull "<<inner<<nl;
			assert(inner.front() == h[i] && inner.back() == h[j]);
			ld outer = abs(h[i]-h[a])+abs(h[a]-h[b])+abs(h[b]-h[j]);
			ld res = perimeter(inner);
			assert(outer-res > EPS);
			ans = max(ans, outer - res);
		}

		// one point
		{
			int a = (i+1 == m ? 0 : i+1);
			int j = (a+1 == m ? 0 : a+1);
			//cerr<<"rem one "<<a<<nl;
			ld lb = min(min(h[i].real(), h[j].real()), h[a].real());
			ld rb = max(max(h[i].real(), h[j].real()), h[a].real());
			auto lit = lower_bound(p.begin(), p.end(), pt(lb-0.1,0), cmp_lex);
			auto rit = lower_bound(p.begin(), p.end(), pt(rb+0.1,0), cmp_lex);
			vector<pt> cur;
			for(auto it=lit; it!=rit; it++) {
				if(eq(*it,h[a])) continue;
				cur.push_back(*it);
			}
			vector<pt> hull = chull(cur);
			vector<pt> inner = get_hull(hull, h[i], h[j]);
			//cerr<<"got hull "<<inner<<nl;
			assert(inner.front() == h[i] && inner.back() == h[j]);
			ld outer = abs(h[i]-h[a]) + abs(h[a]-h[j]);
			ld perim = perimeter(inner);
			assert(outer-perim > EPS);
			insert(i, outer - perim);
			ld diff = solve_inner(inner, p, h[a]);
			assert(diff > -EPS);
			ans = max(ans, outer - perim + diff);
		}
	}

	// two points
	if(m>3) {
		for(int i=0;i<m;i++) {
			int l = (i+2)%m;
			int r = (i+m-2)%m;
			ld cur = query_range(i,i);
			ld other = query_range(l,r);
			assert(cur>EPS && other>EPS);
			ans = max(ans, cur + other);
		}
	}

	cout << ans << nl;

	return 0;
}
