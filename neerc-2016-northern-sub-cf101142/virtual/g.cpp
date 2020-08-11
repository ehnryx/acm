#include <bits/stdc++.h>
using namespace std;
#define problem_name "gangsters"

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;

const int N = 1e5+1;
const int L = 19;

pii rmq[2*N][L];
int lg[2*N];
void build() {
	for (int i=2; i<2*N; i++) {
		lg[i] = 31 - __builtin_clz(i);
	}
	for (int j=1; j<L; j++) {
		for (int i=0; i+(1<<j)<=2*N; i++) {
			rmq[i][j] = min(rmq[i][j-1], rmq[i+(1<<(j-1))][j-1]);
		}
	}
}
int rmqpos = 0;


int par[N];
vector<int> adj[N];
int idx[N], remap[N], subt[N], subsz[N], ileft[N], iright[N], rmqid[N];
int ipos = 1;

void dfs(int u, int root, int depth) {
	ileft[u] = ipos;
	remap[u] = ipos;
	rmqid[u] = rmqpos;
	rmq[rmqpos++][0] = pii(depth, u);
	idx[ipos++] = u;
	subt[u] = root;
	if (adj[u].empty()) {
		subsz[u] = 1;
	} else {
		for (int v : adj[u]) {
			dfs(v, root, depth+1);
			rmq[rmqpos++][0] = pii(depth, u);
			subsz[u] += subsz[v];
		}
	}
	iright[u] = ipos;
}


int subcnt[N];

int lca(int l, int r) {
	//cerr << "query lca " << idx[l] << " " << idx[r] << nl;
	l = rmqid[idx[l]]; r = rmqid[idx[r]];
	if (l > r) swap(l,r);
	int j = lg[r-l+1];
	return min(rmq[l][j], rmq[r-(1<<j)+1][j]).second;
}



int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
#ifdef ONLINE_JUDGE
	freopen(problem_name ".in", "r", stdin);
	freopen(problem_name ".out", "w", stdout);
#endif

	int n, q;
	cin >> n >> q;

	for (int i=2; i<=n; i++) {
		cin >> par[i];
		adj[par[i]].push_back(i);
	}

	for (int u : adj[1]) {
		dfs(u, u, 0);
	}
	build();

	set<int> active;
	int ans = 0;
	int second = 0;
	while (q--) {
		char c; int x;
		cin >> c >> x;
		int id = x;
		//cerr << c << " " << x << nl;
		if (c == '+') {
			subcnt[subt[id]]++;
			if (subcnt[subt[id]] == 1) {
				ans++;
				active.insert(remap[id]);
			} else {
				int lb = *active.lower_bound(ileft[subt[id]]);
				int rb = *prev(active.lower_bound(iright[subt[id]]));
				active.insert(remap[id]);
				int nlb = *active.lower_bound(ileft[subt[id]]);
				int nrb = *prev(active.lower_bound(iright[subt[id]]));
				//cerr << "nlbasr " << lb << " " << rb << " " << nlb << " " << nrb << nl;
				int before = lca(lb, rb);
				int after = lca(nlb, nrb);
				//cerr << "lca " << before << " " << after << " subsz: " << subsz[before] << " " << subsz[after] << " subcnt: " << subcnt[subt[id]] << nl;
				second -= subsz[before] - (subcnt[subt[id]]-1);
				second += subsz[after] - (subcnt[subt[id]]);
			}
		}
		else {
			subcnt[subt[id]]--;
			if (subcnt[subt[id]] == 0) {
				ans--;
				active.erase(remap[id]);
			} else {
				int lb = *active.lower_bound(ileft[subt[id]]);
				int rb = *prev(active.lower_bound(iright[subt[id]]));
				active.erase(remap[id]);
				int nlb = *active.lower_bound(ileft[subt[id]]);
				int nrb = *prev(active.lower_bound(iright[subt[id]]));
				int before = lca(lb, rb);
				int after = lca(nlb, nrb);
				second -= subsz[before] - (subcnt[subt[id]]+1);
				second += subsz[after] - (subcnt[subt[id]]);
			}
		}
		cout << ans << " " << second << nl;
	}

	return 0;
}
