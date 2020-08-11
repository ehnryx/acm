#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;

const int INF = 0x3f3f3f3f;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    int n, m;
    cin >> n >> m;
    
    int deg[n]; 
    memset(deg, 0, sizeof deg);
    
    int a, b;
    vector<pii> edges;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        deg[a]++;
        deg[b]++;
        edges.push_back(pii(a,b));
    }
    
    vector<int> graph[n];
    vector<bool> leaf(n);
    for (const pii& e : edges) {
        if (deg[e.first] > deg[e.second]) {
            graph[e.first].push_back(e.second);
            leaf[e.second] = true;
        } else if (deg[e.second] > deg[e.first]) {
            graph[e.second].push_back(e.first);
            leaf[e.first] = true;
        }
    }

	for (int i = 0; i < n; i++) {
		cerr << i << ": ";
		for (int it : graph[i]) 
			cerr << it << " ";
		cerr << endl;
	}
    
    queue<int> next;
    int len[n];
    memset(len, 0, sizeof len);
    for (int i = 0; i < n; i++) {
        if (!leaf[i]) {
            next.push(i);
            len[i] = 1;
        }
    }
    
    int ans = 0;
    while (!next.empty()) {
        int cur = next.front();
        next.pop();
		cerr << "visit " << cur << endl;
        ans = max(ans, len[cur]);
        for (int neighbour : graph[cur]) {
            if (len[neighbour] == 0) {
                next.push(neighbour);
            }
            len[neighbour] = max(len[neighbour], 1+len[cur]);
        }
    }
    cout << ans << endl;
    
    return 0;
}
