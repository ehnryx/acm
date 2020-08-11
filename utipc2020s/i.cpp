#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';
typedef long long ll;
typedef long double ld;

const int N = 1e5 + 1;
int f[2][N];
unordered_set<int> vals[2][N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int n;
	cin >> n;
	for(int t=0; t<2; t++) {
		for(int i=1; i<=n; i++) {
			cin >> f[t][i];
			vals[t][f[t][i]].insert(i);
		}
	}

	set<pair<int,int>> cur[2];
	for(int t=0; t<2; t++) {
		for(int i=0; i<N; i++) {
			if(!vals[t][i].empty()) {
				cur[t].insert(make_pair(vals[t][i].size(), i));
			}
		}
	}

	set<int> alive;
	for(int i=1; i<=n; i++) {
		alive.insert(i);
	}

	int q;
	cin >> q;
	for(int t=0; q--; t^=1) {
		string s;
		cin >> s;
		if(s == "YES") {
			while(!cur[t].empty() && cur[t].rbegin()->first > 1) {
				int v = cur[t].rbegin()->second; // f(x)
				cur[t].erase(prev(cur[t].end()));
				assert(vals[t][v].size() > 1);
				for(int i : vals[t][v]) { // x
					assert(alive.count(i));
					alive.erase(i);
					int g = f[t^1][i]; // g(x)
					assert(cur[t^1].count(make_pair(vals[t^1][g].size(), g)));
					cur[t^1].erase(make_pair(vals[t^1][g].size(), g));
					assert(vals[t^1][g].count(i));
					vals[t^1][g].erase(i);
					if(!vals[t^1][g].empty()) {
						assert(cur[t^1].insert(make_pair(vals[t^1][g].size(), g)).second);
					}
				}
				vals[t][v].clear();
			}
			if(cur[t].empty()) {
				cout << -1 << nl;
				return 0;
			}
		} else {
			while(!cur[t].empty() && cur[t].begin()->first == 1) {
				int v = cur[t].begin()->second; // f(x)
				cur[t].erase(cur[t].begin());
				assert(vals[t][v].size() == 1);
				int i = *vals[t][v].begin(); // x
				assert(alive.count(i));
				alive.erase(i);
				vals[t][v].clear();
				int g = f[t^1][i]; // g(x)
				assert(cur[t^1].count(make_pair(vals[t^1][g].size(), g)));
				cur[t^1].erase(make_pair(vals[t^1][g].size(), g));
				assert(vals[t^1][g].count(i));
				vals[t^1][g].erase(i);
				if(!vals[t^1][g].empty()) {
					assert(cur[t^1].insert(make_pair(vals[t^1][g].size(), g)).second);
				}
			}
			if(cur[t].empty()) {
				cout << -1 << nl;
				return 0;
			}
		}
	}

	if(alive.empty()) for(;;);
	for(int it : alive) {
		cout << it << " ";
	}
	cout << nl;

	return 0;
}
