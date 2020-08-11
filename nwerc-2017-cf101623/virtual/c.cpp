#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

struct Edge {
	int id, dx, dy, dist, p, pdx, pdy;
	bool operator < (const Edge& o) const {
		return dist > o.dist;
	}
};

vector<int> sx = { 1, 1, -1, -1 };
vector<int> sy = { 1, -1, -1, 1 };
vector<int> dx = { 0, 1 };
vector<int> dy = { 1, 0 };

int sgn(int x) { return x<0 ? -1 : x==0 ? 0 : 1; }
int cp(int ax, int ay, int bx, int by) {
	return ax*by - bx*ay;
}

const int N = 16;
const int M = 4;

int grid[M][M];
int px[N+1], py[N+1];
map<pii,vector<Edge>> adj[N+1];
map<pii,Edge> par[N+1];
set<pii> vis[N+1];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	for (int i=1; i<=N+1; i++) {
		for (int j=1; j<=i; j++) {
			if (__gcd(i,j) == 1) {
				dx.push_back(i);
				dy.push_back(j);
				dx.push_back(j);
				dy.push_back(i);
			}
		}
	}

	for (int i=0; i<M; i++) {
		for (int j=0; j<M; j++) {
			cin >> grid[i][j];
			px[grid[i][j]] = i;
			py[grid[i][j]] = j;
		}
	}

	int m = dx.size();
	for (int a=0; a<4; a++) for (int i=0; i<m; i++) {
		adj[0][pii(0,0)].push_back({1,sx[a]*dx[i],sy[a]*dy[i],1});
	}

	for (int i=1; i<N; i++) {
		for (int a=0; a<4; a++) for (int ai=0; ai<m; ai++) {
			for (int b=0; b<4; b++) for (int bi=0; bi<m; bi++) {
				int adx = sx[a]*dx[ai];
				int ady = sy[a]*dy[ai];
				int bdx = sx[b]*dx[bi];
				int bdy = sy[b]*dy[bi];
				int gdx = px[i+1]-px[i];
				int gdy = py[i+1]-py[i];
				if (adx==bdx && ady==bdy) {
					if (cp(adx,ady,gdx,gdy) == 0) {
						if (sgn(adx*gdx) >= 0 && sgn(ady*gdy) >= 0) {
							adj[i][pii(adx,ady)].push_back({i+1,bdx,bdy,0});
						}
					}
				}
				else if (adx==-bdx && ady==-bdy) {
					if (cp(adx,ady,gdx,gdy) == 0) {
						adj[i][pii(adx,ady)].push_back({i+1,bdx,bdy,1});
					}
				}
				else {
					assert(cp(adx,ady,bdx,bdy) != 0);
					if (sgn(cp(adx,ady,bdx,bdy)) != -sgn(cp(adx,ady,gdx,gdy))
						&& sgn(cp(bdx,bdy,adx,ady)) != -sgn(cp(bdx,bdy,gdx,gdy))) {
						adj[i][pii(adx,ady)].push_back({i+1,bdx,bdy,1});
					}
				}
			}
		}
	}

	priority_queue<Edge> nxt;
	nxt.push(Edge({0,0,0,0}));
	while (!nxt.empty()) {
		Edge cur = nxt.top();
		nxt.pop();
		pii dir = pii(cur.dx, cur.dy);
		if (!vis[cur.id].count(dir)) {
			vis[cur.id].insert(dir);
			par[cur.id][dir] = {cur.p, cur.pdx, cur.pdy};
			if (cur.id == 16) {
				cout << cur.dist << nl;
				break;
			}
			for (const Edge& e : adj[cur.id][dir]) {
				nxt.push({e.id, e.dx, e.dy, e.dist+cur.dist});
			}
		}
	}

	return 0;
}
