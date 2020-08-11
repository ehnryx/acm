#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ld EPS = 1e-10;

const int N = 215;
const int M = N*N;

namespace Dinic {
int par[N], first[N], nxt[2*M], ep[2*M], m;
ll flo[2*M], cap[2*M], cost[2*M];
void init() { m = 0; memset(first, -1, sizeof first); memset(flo, 0, sizeof flo); }
void add_edge(int a, int b, ll c=1, ll p=0) {
	nxt[m] = first[ep[m]=a], first[ep[m]] = m, cap[m] = c, cost[m] = p, ++m;
	nxt[m] = first[ep[m]=b], first[ep[m]] = m, cap[m] = 0, cost[m] = -p, ++m; }

int L[N], cur[N];
bool bfs(int s, int t) {
	memset(L, INF, sizeof L);
	queue<int> q; q.push(s); L[s] = 0;
	while (!q.empty()) { int u = q.front(); q.pop();
		for (int v, e = cur[u] = first[u]; e != -1; e = nxt[e])
			if (L[v=ep[e^1]] == INF && flo[e] < cap[e])
				q.push(v), L[v] = L[u]+1;
	} return L[t] < INF; }
ll dfs(int u, int t, ll f) {
	if (u == t) return f;
	ll cf, df = 0;
	for (int v, e = cur[u]; e != -1 && df < f; cur[u] = e = nxt[e])
		if (flo[e] < cap[e] && L[v=ep[e^1]] == L[u]+1) {
			cf = dfs(v, t, min(cap[e]-flo[e], f-df));
			flo[e] += cf; flo[e^1] -= cf; df += cf;
		} return df; }
}

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
bool eq(const pt& a, const pt& b) { return abs(a-b) < EPS; }
int sgn(const ld& x) { return abs(x)<EPS ? 0 : x<0 ? -1 : 1; }
bool cmp_lex(const pt& a, const pt& b) {
	return a.real()<b.real()-EPS || (a.real()<b.real()+EPS && a.imag()<b.imag()-EPS);
}

bool seg_x_seg(pt a1, pt a2, pt b1, pt b2) {
	ld za = abs(a2-a1), zb = abs(b2-b1); za = za>EPS?1/za:0; zb = zb>EPS?1/zb:0;
	int s1 = sgn(cp(a2-a1, b1-a1)*za), s2 = sgn(cp(a2-a1, b2-a1)*za);
	int s3 = sgn(cp(b2-b1, a1-b1)*zb), s4 = sgn(cp(b2-b1, a2-b1)*zb);
	if (!s1 && !s2 && !s3) {
		if (cmp_lex(a2, a1)) swap(a1, a2);
		if (cmp_lex(b2, b1)) swap(b1, b2);
		return !cmp_lex(b2, a1) && !cmp_lex(a2, b1);
	} return s1*s2 <= 0 && s3*s4 <= 0;
}

pt line_inter(const pt& a, const pt& b, const pt& c, const pt& d) {
	return a + cp(c-a, d-c) / cp(b-a, d-c) * (b-a);
}
ld lp_dist(const pt& a, const pt& b, const pt& p) {
	return cp(b-a, p-a) / abs(b-a);
}

struct Line {
	pt a, b;
	Line(pt a, pt b): a(a), b(b) {}
};

struct Arc {
	pt c;
	ld r, s, t;
	Arc(pt a, pt b, pt d) {
		////cerr << "ARC with " << a << " " << b << " " << d << nl;
		pt m = (ld)0.5 * (a+b);
		c = line_inter(m, m+(a-b)*pt(0,1), a, a+d*pt(0,1));
		r = abs(a-c);
		assert(abs(abs(b-c) - r) < EPS);
		if (cp(d, b-a) > 0) {
			s = arg(a-c);
			t = arg(b-c);
		} else {
			s = arg(b-c);
			t = arg(a-c);
		}
	}
	bool in_range(pt x) const {
		ld a = arg(x-c);
		if (s < t) {
			return s-EPS < a && a < t+EPS;
		} else {
			return s-EPS < a || a < t+EPS;
		}
	}
};

vector<Line> lines;
vector<Arc> arcs;

bool intersect(pt a, pt b) {
	if (eq(a,b)) return false;

	for (const Line& x : lines) {
		if (seg_x_seg(a, b, x.a, x.b)) {
			//cerr << a << " " << b << " int " << x.a << " " << x.b << nl;
			return true;
		}
	}

	for (const Arc& x : arcs) {
		ld d = lp_dist(a, b, x.c);
		if (d > x.r) continue;
		pt m = (ld)0.5 * (a+b);

		ld k = sqrt(x.r*x.r - d*d);
		pt p1 = m + (k/abs(a-b))*(a-b);
		pt p2 = m - (k/abs(a-b))*(a-b);

		if (x.in_range(p1) && seg_x_seg(p1, p1, a, b)) {
			//cerr << a << " " << b << " arc " << x.c << " " << x.r << " @ " << p1 << nl;
			return true;
		}
		if (x.in_range(p2) && seg_x_seg(p2, p2, a, b)) {
			//cerr << a << " " << b << " arc " << x.c << " " << x.r << " @ " << p2 << nl;
			return true;
		}
	}

	return false;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	for (int cs=1; ; cs++) {
		arcs.clear();
		lines.clear();

		int n, a, g, x, y, z;
		cin >> n >> a >> g;

		if (!n && !a && !g) break;

		for (int i=0; i<n; i++) {
			int k;
			cin >> k;

			vector<pt> p;
			char c = 0;
			pt d;
			for (int j=0; j<k; j++) {
				cin >> x >> y;

				if (c == 's') {
					lines.push_back(Line(p.back(), pt(x,y)));
				}
				else if (c == 'c') {
					arcs.push_back(Arc(p.back(), pt(x,y), d));
				}
				p.push_back(pt(x,y));

				cin >> c;
				if (c == 'c') {
					cin >> x >> y;
					d = pt(x,y);
				}
			}

			if (c == 's') {
				lines.push_back(Line(p.back(), p.front()));
			} else if (c == 'c') {
				arcs.push_back(Arc(p.back(), p.front(), d));
			}
		}

		////cerr << "LINES: " << nl; for (auto x : lines) {
			////cerr << x.a << " " << x.b << nl; }
		////cerr << "ARCS: " << nl; for (auto x : arcs) {
			////cerr << x.c << " " << x.s << " " << x.t << " " << x.r << " -> " << x.c+x.r*exp(pt(0,x.s)) << " " << x.c+x.r*exp(pt(0,x.t)) << nl; }

		Dinic::init();
		const int source = 210;
		const int sink = 211;

		ll sum = 0;
		vector<pt> art;
		for (int i=0; i<a; i++) {
			cin >> x >> y >> z;
			////cerr << "art " << x << " " << y << nl;
			sum += z;
			Dinic::add_edge(source, i, z);
			art.push_back(pt(x,y));
		}

		for (int i=0; i<g; i++) {
			cin >> x >> y >> z;
			////cerr << "gar " << x << " " << y << nl;
			Dinic::add_edge(a+i, sink, z);
			for (int j=0; j<a; j++) {
				if (!intersect(art[j], pt(x,y))) {
					Dinic::add_edge(j, a+i);
				}
			}
		}

		ll flow = 0;
		while (Dinic::bfs(source, sink)) {
			flow += Dinic::dfs(source, sink, INF);
		}

		//cerr << "flow: " << flow << "  sum: " << sum << nl;

		cout << "Case " << cs << ": ";
		if (flow == sum) {
			cout << "Yes" << nl;
		} else {
			cout << "No" << nl;
		}
	}

	return 0;
}
