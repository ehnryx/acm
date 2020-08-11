#pragma GCC optimize("fast-math")
#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

int cc_inter(const pt& p1, ld r1, const pt& p2, ld r2, pt& i1, pt& i2) {
	ld dq = norm(p1-p2), rq = r1*r1 - r2*r2;
	pt c = (p1+p2) / (ld)2 + (p2-p1) * rq / (ld)2 / dq;
	ld dt = (ld)2 * dq * (r1*r1 + r2*r2) - dq*dq - rq*rq;
	if(dt < -EPS) return 0;
	if(dt < EPS) { i1=i2=c; return 1; }
	dt = sqrt(dt)/(ld)2/dq; i1 = c + (p2-p1)*pt(0,1)*dt; i2 = c - (p2-p1)*pt(0,1)*dt;
	return 2;
}

const int N = 51;
set<int> V[N];
int E[N];
unordered_set<int> arc[N];
vector<pt> verts;
vector<int> inc[N*N];

int get_id(const pt& v) {
	for(int i=0; i<verts.size(); i++) {
		if(abs(verts[i] - v) < EPS) return i;
	}
	verts.push_back(v);
	return verts.size() - 1;
}

int dsu[N];
int find(int i) {
	if(dsu[i] == -1) return i;
	return dsu[i] = find(dsu[i]);
}
void link(int i, int j) {
	if(find(i) != find(j)) {
		dsu[find(i)] = find(j);
	}
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

#ifdef ONLINE_JUDGE
	freopen("circles.in", "r", stdin);
	freopen("circles.out", "w", stdout);
#endif

	int n;
	cin >> n;
	vector<pair<pt,ld>> circs;
	for(int i=0; i<n; i++) {
		int x, y, r;
		cin >> x >> y >> r;
		circs.emplace_back(pt(x, y), r);
	}

	for(int i=0; i<n; i++) {
		auto [c, r] = circs[i];
		for(int j=0; j<i; j++) {
			auto [cc, rr] = circs[j];
			pt i1, i2;
			if(cc_inter(c, r, cc, rr, i1, i2)) {
				int id = get_id(i1);
				int jd = get_id(i2);
				arc[i].insert(id);
				arc[i].insert(jd);
				arc[j].insert(id);
				arc[j].insert(jd);
				inc[id].push_back(i);
				inc[id].push_back(j);
				inc[jd].push_back(i);
				inc[jd].push_back(j);
			}
		}
	}

	memset(dsu, -1, sizeof dsu);
	for(int i=0; i<verts.size(); i++) {
		for(int j=1; j<inc[i].size(); j++) {
			link(inc[i][0], inc[i][j]);
		}
	}

	for(int i=0; i<n; i++) {
		for(int j : arc[i]) {
			V[find(i)].insert(j);
		}
		E[find(i)] += arc[i].size();
	}

	int ans = 1;
	for(int i=0; i<n; i++) {
		if(i != find(i)) continue;
		ans += max(E[i], 1) - max((int)V[i].size(), 1) + 1;
	}
	cout << ans << nl;

	return 0;
}
