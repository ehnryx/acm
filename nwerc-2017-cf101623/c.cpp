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

namespace std {
	template<> struct hash<pii> {
		size_t operator () (const pii& v) const {
			return v.first<<15^v.second;
		}
	};
}

struct Edge {
	int id; pii dir; int dist;
	bool operator < (const Edge& o) const {
		return dist > o.dist;
	}
};

int sgn(int x) { return x==0 ? 0 : x<0 ? -1 : 1; }
int cp(int ax, int ay, int bx, int by) { return ax*by-bx*ay; }

vector<int> sx = { 1, 1, -1, -1 };
vector<int> sy = { 1, -1, -1, 1 };
vector<int> dx, dy;

const int N = 4;
const int M = 4*4;
int grid[N][N];
int px[M+1], py[M+1];
unordered_map<pii,vector<Edge>> adj[M+1];
unordered_set<pii> vis[M+1];

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	for (int i=1; i<=M; i++) {
		for (int j=0; j<=i; j++) {
			if (__gcd(i,j) == 1) {
				dx.push_back(i);
				dy.push_back(j);
				dx.push_back(j);
				dy.push_back(i);
			}
		}
	}

	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			cin >> grid[i][j];
			px[grid[i][j]] = i;
			py[grid[i][j]] = j;
		}
	}

	int ns = sx.size();
	int nd = dx.size();
	for (int i=1; i<M; i++) {
		for (int as=0; as<ns; as++) for (int a=0; a<nd; a++) {
			for (int bs=0; bs<ns; bs++) for (int b=0; b<nd; b++) {
				int adx = sx[as]*dx[a];
				int ady = sy[as]*dy[a];
				int bdx = sx[bs]*dx[b];
				int bdy = sy[bs]*dy[b];
				int gdx = px[i+1]-px[i];
				int gdy = py[i+1]-py[i];
				pii adir = pii(adx,ady);
				pii bdir = pii(bdx,bdy);
				if (adx==bdx && ady==bdy) {
					if (cp(adx,ady,gdx,gdy)==0 && adx*gdx>=0 && ady*gdy>=0) {
						adj[i][adir].push_back({i+1,bdir,0});
					}
				}
				else if (adx==-bdx && ady==-bdy) {
					if (cp(adx,ady,gdx,gdy)==0) {
						adj[i][adir].push_back({i+1,bdir,1});
					}
				}
				else {
					assert(cp(adx,ady,bdx,bdy) != 0);
					if (sgn(cp(adx,ady,bdx,bdy)) != -sgn(cp(adx,ady,gdx,gdy))
						&& sgn(cp(bdx,bdy,adx,ady)) != -sgn(cp(bdx,bdy,gdx,gdy))) {
						adj[i][adir].push_back({i+1,bdir,1});
					}
				}
			}
		}
	}
	for (int i=0; i<ns; i++) for (int j=0; j<nd; j++) {
		adj[0][pii(0,0)].push_back({1,pii(sx[i]*dx[j],sy[i]*dy[j]),1});
	}

	priority_queue<Edge> nxt;
	nxt.push({0,pii(0,0),0});
	while (!nxt.empty()) {
		Edge cur = nxt.top();
		nxt.pop();
		if (!vis[cur.id].count(cur.dir)) {
			vis[cur.id].insert(cur.dir);
			if (cur.id == 16) {
				cout << cur.dist << nl;
				return 0;
			}
			for (const Edge& e : adj[cur.id][cur.dir]) {
				nxt.push({e.id,e.dir,e.dist+cur.dist});
			}
		}
	}

	assert(false);

	return 0;
}
