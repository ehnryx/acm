#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;

#define nl '\n'

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;
const ll MOD = 1e9+9;
const ll P = 29;

string pattern[2];
int plen; // length of P
ll shift;
ll pat[2];

const int L = 18;
const int N = 1<<L;
char badval[N];

vector<int> adj[N];

struct BIT {
	int freq[N];
	BIT() { memset(freq, 0, sizeof freq); }
	void insert(int x, int v) {
		for (; x<N; x+=x&-x)
			freq[x]+=v;
	}
	int query(int x) {
		int res = 0;
		for (; x; x-=x&-x)
			res += freq[x];
		return res;
	}
	int query(int lx, int rx) {
		return query(rx)-query(lx-1);
	}
	void set(int x, int v) {
		int pv = query(x,x);
		insert(x, v-pv);
	}
};

template<class T> struct RMQ {
	T rmq[N][L];
	int lg[N];
	void build() {
		for (int i=1; i<N; i++) {
			lg[i] = 31 - __builtin_clz(i);
		}
		for (int j=1; j<L; j++) 
			for (int i=0; i+(1<<j)-1<N; i++)
				rmq[i][j] = min(rmq[i][j-1], rmq[i+(1<<(j-1))][j-1]);
	}
	T query(int l, int r) {
		if (l>r) swap(l,r);
		int j = lg[r-l+1];
		return min(rmq[l][j], rmq[r-(1<<j)+1][j]);
	}
};

struct LCA : RMQ<pii> {
	int depth[N], segpos[N];
	int parent[N], subsz[N];
	int lcanum = 0;
	LCA() {
		lcanum = 0;
		depth[0] = 0;
	}
	void build(int root) {
		build(root, 0);
		RMQ::build();
	}
	int build(int cur, int par) {
		depth[cur] = depth[par]+1;
		segpos[cur] = lcanum;
		parent[cur] = par;
		subsz[cur] = 1;
		RMQ::rmq[lcanum++][0] = pii(depth[cur], cur);
		for (int x : adj[cur]) {
			if (x != par) {
				subsz[cur] += build(x,cur);
				RMQ::rmq[lcanum++][0] = pii(depth[cur], cur);
			}
		}
		return subsz[cur];
	}
	int query(int a, int b) {
		return RMQ::query(segpos[a], segpos[b]).second;
	}
};

struct HLD : LCA {
	vector<int> sz, root, start;
	int chain[N], pos[N];
	char value[N]; // values from tree
	BIT bit[2]; // bit
	int hldnum, segnum;

	HLD(): LCA() {
		hldnum = 0;
		segnum = 1; // seg as bit
	}
	int get(int i) const { return start[chain[i]]+pos[i]; }
	void build(int root) {
		LCA::build(root);
		build_hld(root, 0);
		build_chain();
	}

	void build_hld(int cur, int par) {
		if (hldnum == root.size()) {
			root.push_back(cur);
			start.push_back(segnum);
			sz.push_back(0);
		}
		chain[cur] = hldnum;
		pos[cur] = sz[chain[cur]]++;
		segnum++;
		value[get(cur)] = badval[cur]; // update value from tree
		int best = -1, child = -1;
		for (int x : adj[cur]) {
			if (x != par && subsz[x] > best) {
				best = subsz[x];
				child = x;
			}
		}
		if (child != -1) build_hld(child, cur);
		for (int x : adj[cur]) {
			if (x != par && x != child) {
				hldnum++;
				build_hld(x, cur);
			}
		}
	}

	void build_chain() {
		for (int c=0; c<start.size(); c++) {
			for (int t=0; t<2; t++) {
				ll ha = 0;
				for (int i=0; i<sz[c]; i++) {
					ha = (ha*29 + value[start[c]+i]-'a'+1)%MOD;
					if (i>=plen) {
						ha = (ha - (shift * (value[start[c]+i-plen]-'a'+1)) % MOD + MOD) % MOD;
					}
					if (i+1>=plen && ha == pat[t]) {
						bit[t].insert(start[c]+i, 1);
					}
				}
			}
		}
	}

	void update(int a, char v) {
		int c = chain[a];
		int s = start[c];
		int id = s+pos[a];
		value[id] = v;
		int left = max(s, id-plen+1);
		int right = min(id+plen-1, s+sz[c]-1);
		for (int t=0; t<2; t++) {
			ll ha = 0;
			for (int i=0; left+i<=right; i++) {
				ha = (ha*29 + value[left+i]-'a'+1)%MOD;
				if (i>=plen) {
					ha = (ha - (shift * (value[left+i-plen]-'a'+1)) % MOD + MOD) % MOD;
				}
				if (i+1>=plen) {
					if (ha == pat[t]) {
						bit[t].set(left+i, 1);
					} else {
						bit[t].set(left+i, 0);
					}
				}
			}
		}
	}

	///////////////////////
	vector<char> top[2];
	char temps[N];

	int query_path(int id, int a, int b) {
		top[id].clear();
		int sum = 0;
		int len = 0;
		while (chain[a] != chain[b]) {
			int s = start[chain[a]];
			if (s+plen-1 <= s+pos[a]) {
				sum += bit[id].query(s+plen-1, s+pos[a]);
			}

			// do lca part
			int diff = depth[root[chain[a]]]-depth[b];
			for (int i=min(pos[a],plen-diff-1); i>=0; i--) {
				top[id].push_back(value[s+i]);
			}

			// add bottom to cur string
			for (int i=pos[a]; i>=0 && pos[a]-i<plen-1; i--) {
				temps[len++] = value[s+i];
			}
			// do chain part
			if (pos[a] >= plen-1) {
				//cerr << "calc @ " << a << nl;
				sum += calc(len, !id);
				len = 0;
				// add top to cur string
				for (int i=min(pos[a],plen-2); i>=0; i--) {
					temps[len++] = value[s+i];
				}
			}

			// next
			a = parent[root[chain[a]]];
		}

		if (pos[a] != pos[b]) {
			int s = start[chain[a]];
			if (s+pos[b]+plen <= s+pos[a]) {
				sum += bit[id].query(s+pos[b]+plen, s+pos[a]);
			}

			// do lca part
			for (int i=min(pos[a], pos[b]+plen-1); i>=pos[b]; i--) {
				top[id].push_back(value[s+i]);
			}

			// add bottom to cur string
			for (int i=pos[a]; i>pos[b] && pos[a]-i<plen-1; i--) {
				temps[len++] = value[s+i];
			}
		} else {
			top[id].push_back(value[get(b)]);
		}
		sum += calc(len, !id);
		len = 0;
		return sum;
	}

	int query_lca() {
		int len = 0;
		reverse(top[0].begin(), top[0].end());
		assert(!top[1].empty());
		top[1].pop_back();
		for (int t=1; t>=0; t--) {
			for (char c : top[t]) {
				temps[len++] = c;
			}
		}
		return calc(len, 0);
	}

	int calc(int len, int t) {
		//cerr << " calc" << nl;
		int res = 0;
		ll ha = 0;
		for (int i=0; i<len; i++) {
			//cerr << "  " << i << ": " << temps[i] << nl;
			ha = (ha*29 + temps[i]-'a'+1)%MOD;
			if (i>=plen) {
				ha = (ha - (shift * (temps[i-plen]-'a'+1)) % MOD + MOD) % MOD;
			}
			if (i+1>=plen && ha == pat[t]) {
				res += 1;
			}
		}
		//cerr << res << nl;
		return res;
	}
};

HLD hld;

int answer(int a, int b) {
	//cerr << nl << "ANSWER: " << a << " " << b << nl;
	int ans = 0;
	int lca = hld.query(a,b);
	ans += hld.query_path(1, a, lca);
	//cerr << "first path: " << ans << nl;
	ans += hld.query_path(0, b, lca);
	//cerr << "second path: " << ans << nl;
	ans += hld.query_lca(); // we should have the stuff already
	//cerr << "lca part: " << ans << nl;
	return ans;
}

void init() {
	pattern[1] = pattern[0];
	reverse(pattern[1].begin(), pattern[1].end());
	plen = pattern[0].size();
	pat[0] = pat[1] = 0;
	shift = 1;
	for (int i=0; i<plen; i++) {
		shift = (shift*P)%MOD;
		pat[0] = (pat[0]*P + pattern[0][i]-'a'+1) % MOD;
		pat[1] = (pat[1]*P + pattern[1][i]-'a'+1) % MOD;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n, q;
	cin >> n >> q;

	cin >> pattern[0];
	for (int i=1; i<=n; i++) {
		cin >> badval[i];
	}
	init();
	//cerr << pat[0] << " " << pat[1] << " " << pattern[0] << " " << pattern[1] << nl;

	int a, b;
	for (int i=1; i<n; i++) {
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	hld.build(1);

	//cerr << "HLD" << nl; for (int i=1; i<=n; i++) {
		//cerr << i << ": " <<  hld.chain[i] << nl; }
	//cerr << nl;

	int t; char c;
	while (q--) {
		cin >> t;
		if (t == 1) {
			cin >> a >> b;
			cout << answer(a,b) << nl;
		} else {
			cin >> a >> c;
			hld.update(a,c);
		}
	}

	return 0;
}
