#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Node {
	int id;
	int age;
	vector<int> im;
	vector<int> ic;
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	vector<Node> v;
	vector<int> id;
	int n, m, q, a, b;
	char c;
	cin >> n >> m >> q;
	v.resize(n);
	id.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> v[i].age;
		v[i].id = i;
		id[i] = i;
	}
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		v[a-1].ic.push_back(b-1);
		v[b-1].im.push_back(a-1);
	}

	cerr << "what" << endl;
	// queries
	int curr;
	stack<int> dfs;
	bitset<500> visited;
	//#define DEBUG
	while (q--) {
		cin >> c;
		if (c == 'P') {
			int cmin = 1e9+7;
			cin >> a;
			visited.reset();
			visited[id[a-1]] = true;
			dfs.push(id[a-1]);
			while (!dfs.empty()) {
				curr = dfs.top();
				dfs.pop();
				for (auto& parent: v[curr].im) {
					if (!visited[parent])
						dfs.push(parent);
				}
				if (visited[curr]) continue;
				visited[curr] = true;
				cmin = min(cmin, v[curr].age);
			}
			if (cmin == 1e9+7) cout << "*" << endl;
			else cout << cmin << endl;
		}
		else {
			#ifdef DEBUG 
			for (int i = 0; i < n; i++) {
				cerr << i+1 << ": "; 
				cerr<<"\tim: "; for(auto&it: v[i].im) cerr << it+1 << " "; cerr<<endl;
				cerr<<"\tic: "; for(auto&it: v[i].ic) cerr << it+1 << " "; cerr<<endl;
			}
			#endif
			cin >> a >> b;
			a--; b--;
			// id[a]; id[b];
			int temp;
			temp = id[a];
			id[a] = id[b];
			id[b] = temp;
			temp = v[id[a]].id;
			v[id[a]].id = v[id[b]].id;
			v[id[b]].id = temp;
			temp = v[id[a]].age;
			v[id[a]].age = v[id[b]].age;
			v[id[b]].age = temp;
		}
	}
	#ifdef DEBUG 
	for (int i = 0; i < n; i++) {
		cerr << i+1 << ": "; 
		cerr<<"\tim: "; for(auto&it: v[i].im) cerr << it+1 << " "; cerr<<endl;
		cerr<<"\tic: "; for(auto&it: v[i].ic) cerr << it+1 << " "; cerr<<endl;
	}
	#endif

	return 0;
}
