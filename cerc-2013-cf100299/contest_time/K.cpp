#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int has_cycle(int u, int mpar, vector<vector<int>>& edges, vector<bool>& visited, vector<int>& par)
{
	//cerr << "AT " << u << endl;
	visited[u] = true;
	par[u] = mpar;
	for(auto v : edges[u])
	{
		if(!visited[v]) {
			int res =  has_cycle(v, u, edges, visited, par);
			//cerr << "RETURNING " << res << endl;
			if(res != -1) return res;
		} else {
			if(par[v] != -1) {
				par[v] = u;
				//cerr << "FOUND CYCLE on edge " << u << "-> " << v << endl;
				return v;
			}
		}
	}
	//cerr << "AT END RETURNING -1 " << endl;
	par[u] = -1;
	return -1;
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int TT; cin >> TT;
	while(TT--) {
		vector<vector<bool>> mtrx(26, vector<bool>(26, true));
		int N; cin >> N;
		for(int i=0;i<N;++i) {
			string s; cin >> s;
			//////cerr << "FALSE IS " << (int) s[0]-'a' << "," << (int) s[1]-'a' << endl;
			mtrx[s[0]-'a'][s[1]-'a'] = false;
		}
		vector<vector<int>> adj(26);
		int self_loop = -1;
		for(int i=0;i<26 && self_loop == -1;++i) {
			for(int j=0;j<26;++j) {
				if(mtrx[i][j] && i == j) {
					self_loop = i;
					////cerr << "SELF LOOP!!! " << self_loop << endl;
					break;
				}
				if(mtrx[i][j]) adj[i].push_back(j);
			}
		}
		if(self_loop != -1) {
			for(int i=0;i<20;++i) {
				for(int j=0;j<20;++j) {
					cout << (char) ('a'+self_loop);
				}
				cout << "\n";
			}
			continue;
		}
		vector<bool> visited(26, false);
		vector<int> par(26, -1);
		bool contains_cycle = false;
		vector<int> cycle;
		for(int i=0;i<26 && !contains_cycle;++i) {
			int res = has_cycle(i, 100, adj, visited, par);
		    if(res != -1) {
				//cerr << " CYCLE at " << res << endl;
				cycle.push_back(res);
				for(int v=par[res];v != res;v = par[v]) {
					cycle.push_back(v);
					//cerr << cycle.back() << " ";
				}
				//cerr << endl;
				reverse(cycle.begin(), cycle.end());
				contains_cycle = true;
			}
		}
		//cerr << "b4 contains cycle " << endl;
		if(contains_cycle) {
			for(int i=0;i<20;++i) {
				for(int j=0;j<20;++j) {
					cout << (char) ('a'+cycle[(i+j)%cycle.size()]);
				}
				cout << "\n";
			}
			continue;
		}
		//cerr << "after contains cycle " << endl;
		
		vector<int> in_degree(26, 0);
		par = vector<int>(26, -1);
		vector<int> depth(26, 0);
		queue<int> ready;
		for(int i=0;i<26;++i) {
			for(auto v : adj[i]) {
				in_degree[v]++;
			}
		}
		for(int i=0;i<26;++i) {
			if(in_degree[i] == 0) ready.push(i);
		}
		int best = ready.front();
		while(!ready.empty()) {
			int u = ready.front(); ready.pop();
			for(auto v : adj[u]) {
				if(depth[u] + 1 > depth[v]) {
					depth[v] = depth[u]+1;
					par[v] = u;
					if(depth[v] > depth[best]) {
						best = v;
					}
				}
				if(--in_degree[v] == 0) {
					ready.push(v);
				}
			}
		}
		vector<int> res;
		for(int v = best; v != -1; v = par[v]) {
			res.push_back(v);
		}
		reverse(res.begin(), res.end());
		for(int i=0;i<(res.size()+1)/2;++i) {
			for(int j=0;j<(res.size()+1)/2;++j) {
				cout << (char) ('a'+res[i+j]);
			}
			cout << "\n";
		}
		
	}
	
	return 0;
}
