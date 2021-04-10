#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
const char nl = '\n';

const int N = 507*507 * 4;
vector<pair<int,int>> adj[N];
ll dijk[N];
int in[N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int s, d, t;
	cin >> s >> d >> t;

	map<int,int> remap;
	int rid = 0;
	remap[0] = rid++;
	remap[s] = rid++;

	int n;
	cin >> n;
	set<pair<int,int>> land;
	vector<int> init = {0, s};
	for(int i=0; i<n; i++) {
		int l, r;
		cin >> l >> r;
		land.insert(make_pair(l, r));
		init.push_back(l);
		init.push_back(r);
		if(!remap.count(l)) remap[l] = rid++;
		if(!remap.count(r)) remap[r] = rid++;
	}
	sort(init.begin(), init.end());

	function<bool(int)> in_island = [=](int x) {
		auto it = land.lower_bound(make_pair(x, -1));
		if(it == land.begin()) return false;
		return x < prev(it)->second;
	};

	function<bool(int,int)> valid = [=](int l, int r) {
		if(in_island(l) || in_island(r)) return false;
		auto it = land.lower_bound(make_pair(l, -1));
		if(it == land.end()) return false;
		return it->second <= r;
	};

	function<int(int)> get_next = [=](int x) {
		auto it = prev(land.lower_bound(make_pair(x, -1)));
		return it->first + d;
	};

	function<int(int)> get_prev = [=](int x) {
		auto it = land.lower_bound(make_pair(x, -1));
		return it->second - d;
	};

	for(int it : init) {
		// jumps
		auto is = land.lower_bound(make_pair(it, -1));
		for(auto js=is; js!=land.end(); js++) {
			int lb = js->second - it;
			int len = (lb+d-1)/d * d;
			int right = it + len;
			if(in_island(right-d)) break;
			if(!valid(it, right)) break;
			if(!remap.count(right)) remap[right] = rid++;
			adj[remap[it]].emplace_back(remap[right], (ll)len/d * t);
		}
		for(auto js=is; js!=land.begin(); js--) {
			int lb = it - prev(js)->first;
			int len = (lb+d-1)/d * d;
			int left = it - len;
			if(in_island(left+d)) break;
			if(!valid(left, it)) break;
			if(!remap.count(left)) remap[left] = rid++;
			adj[remap[left]].emplace_back(remap[it], (ll)len/d * t);
		}

		// to islands
		for(int jt : init) {
			if(it < jt && jt - it <= d) {
				adj[remap[it]].emplace_back(remap[jt], t);
				in[remap[jt]]++;
				//cerr<<"island edge "<<it<<" -> "<<jt<<nl;
			}
		}
	}

	// water
	for(int i=1; i<init.size(); i+=2) {
		auto left = remap.find(init[i-1]);
		assert(left != remap.end());
		for(auto it = left; it != remap.end() && it->first < init[i]; it++) { // strict
			for(auto jt = next(it); jt != remap.end() && jt->first <= init[i]; jt++) { // nonstrict
				int a = remap[it->first];
				int b = remap[jt->first];
				ll diff = jt->first - it->first;
				ll dist = diff;
				dist = min(dist, (diff/d) * t + diff % d);
				dist = min(dist, (diff+d-1)/d * t);
				adj[a].emplace_back(b, dist);
				in[b]++;
				//cerr<<"water edge "<<it->first<<" -> "<<jt->first<<nl;
			}
		}
	}

	assert(in[remap[0]] == 0);

	memset(dijk, 0x3f, sizeof dijk);
	queue<int> bfs;
	for(int i=0; i<rid; i++) {
		if(in[i] == 0) {
			bfs.push(i);
		}
	}
	dijk[0] = 0;
	while(!bfs.empty()) {
		int u = bfs.front();
		bfs.pop();
		for(auto [v, c] : adj[u]) {
			dijk[v] = min(dijk[v], dijk[u] + c);
			if(--in[v] == 0) {
				bfs.push(v);
			}
		}
	}
	cout << dijk[remap[s]] << nl;

	return 0;
}
