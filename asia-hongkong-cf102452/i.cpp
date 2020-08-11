#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
#define nl '\n'

struct Index {
	int x;
	ll val, init;
};

const int N = 2e5 + 1;
ll off[N];
int goal[N];
vector<Index> idx[N]; // index, value, init off
set<pair<ll,int>> vals[N]; // value -> index

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int n, m;
	cin >> n >> m;
	int last = 0;
	int pid = 0;
	for(int i=0; i<m; i++) {
		int t;
		cin >> t;
		if(t == 1) {
			++pid;
			int y, k;
			cin >> y >> k;
			y ^= last;
			//cerr<<"id = "<<pid<<" got new goal: "<<y<<nl;
			goal[pid] = y;
			int sep = (y + k-1) / k;
			for(int j=0; j<k; j++) {
				int x;
				cin >> x;
				x ^= last;
				idx[pid].push_back({x, sep + off[x], off[x]});
				vals[x].insert(make_pair(sep + off[x], pid));
				//cerr<<"add id "<<pid<<" to "<<x<<" w/ "<<sep<<" + "<<off[x]<<nl;
			}
		} else {
			int x, y;
			cin >> x >> y;
			x ^= last; y ^= last;
			//cerr<<"increase "<<x<<" by "<<y<<": "<<off[x]<<" -> "<<off[x]+y<<nl;
			off[x] += y;
			vector<int> out;
			while(!vals[x].empty() && vals[x].begin()->first <= off[x]) {
				int id = vals[x].begin()->second;
				//cerr<<"done @ "<<id<<" because "<<vals[x].begin()->first<<" <= "<<off[x]<<nl;
				int done = 0;
				for(auto [j, v, init] : idx[id]) {
					done += off[j] - init;
					//cerr<<"collected "<<off[j]-init<<" at "<<j<<nl;
					vals[j].erase(make_pair(v, id));
				}
				goal[id] -= done;
				//cerr<<"have "<<goal[id]<<" left"<<nl;
				if(goal[id] > 0) {
					int k = idx[id].size();
					int sep = (goal[id] + k-1) / k;
					for(auto& it : idx[id]) {
						it.val = sep + off[it.x];
						it.init = off[it.x];
						//cerr<<"add "<<sep<<" + "<<off[it.x]<<" @ "<<it.x<<nl;
						vals[it.x].insert(make_pair(sep + off[it.x], id));
					}
				} else {
					out.push_back(id);
				}
			}
			sort(out.begin(), out.end());
			last = out.size();
			cout << out.size();
			for(int it : out) {
				cout << " "<< it;
			}
			cout << nl;
		}
	}

	return 0;
}
