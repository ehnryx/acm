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
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
inline bool eq(const pt &a, const pt &b) { return abs(a-b) < EPS; }
inline ld sgn(const ld& x) { return abs(x) < EPS ? 0 : x/abs(x); }
inline bool cmp_lex(const pt& a, const pt& b) {
	return a.real()<b.real()-EPS||(a.real()<b.real()+EPS&&a.imag()<b.imag()-EPS);
}
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
	return a + cp(c - a, d - c) / cp(b - a, d - c) * (b - a);
}

const ld R = 4e3;
pt shrink(const pt& a, const pt& b, const pt& c) {
	pt nab = (b-a)*pt(0,1)/abs(b-a) * R;
	pt nbc = (c-b)*pt(0,1)/abs(c-b) * R;
	return line_inter(a+nab,b+nab,b+nbc,c+nbc);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin>>n;
	vector<pt> p;
	for(int i=0;i<n;i++) {
		int x,y;
		cin>>x>>y;
		p.push_back(pt(x,y));
	}
	reverse(p.begin(),p.end());

	vector<pt> v;
	for(int i=0;i<n;i++) {
		pt pre = p[(i+n-1)%n];
		pt nxt = p[(i+1)%n];
		v.push_back(shrink(pre,p[i],nxt));
	}

	vector<bool> good;
	for(int i=0;i<n;i++) {
		bool ok = true;
		for(int j=0;j<n;j++) {
			if(j==i || (j+1)%n==i) continue;
			if(seg_x_seg(p[i],v[i],v[j],v[(j+1)%n])
					|| seg_x_seg(p[i],v[i],p[j],p[(j+1)%n])) {
				ok = false;
				break;
			}
		}
		good.push_back(ok);
	}

	for(int i=0;i<n;i++) {
		if(!good[i]) continue;
		for(int j=0;j<i;j++) {
			if(!good[j]) continue;
			if(abs(v[i]-v[j]) > 2*R-EPS) {
				cout<<v[i].real()<<" "<<v[i].imag()<<nl;
				cout<<v[j].real()<<" "<<v[j].imag()<<nl;
				return 0;
			}
		}
	}
	cout<<"impossible"<<nl;

	return 0;
}
