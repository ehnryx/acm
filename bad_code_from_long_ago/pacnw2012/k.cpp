#include <bits/stdc++.h>

using namespace std;

const int N = 30 * 30 + 10, M = 30 * 30 * 30 + 10;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, 1, -1};
const int INF = 0x3f3f3f3f;

int par[N], first[N], nxt[2*M], ep[2*M], m;
long long flo[2*M], cap[2*M];
int L[N], cur[N];

string getl() {
	char ch = getchar();
	if (ch == EOF) {
		return "-1";
	}
	string ans(1, ch);
	ch = getchar();
	while (ch != '\n' && ch != -1) {
		ans += ch;
		ch = getchar();
	}
	//cerr << "debug: " << ans << endl;
	return ans;
}

void init() {
	m = 0;
	memset(first, -1, sizeof first);
	memset(flo, 0, sizeof flo);
}

void addedge(int a, int b, long long c = 1) {
	nxt[m] = first[ep[m]=a]; first[ep[m]] = m; cap[m] = c; ++m;
	nxt[m] = first[ep[m]=b]; first[ep[m]] = m; cap[m] = 0; ++m;
}

bool bfs(int s, int t) {
	memset(L, INF, sizeof L);
	queue<int> q;
	q.push(s);
	L[s] = 0;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int v, e = cur[u] = first[u]; e != -1; e = nxt[e]) {
			if (L[v=ep[e^1]] == INF && flo[e] < cap[e]) {
				q.push(v);
				L[v] = L[u] + 1;
			}
		}
	}
	return L[t] < INF;
}

long long dfs(int u, int t, long long f) {
	if (u == t) {
		return f;
	}
	long long cf, df = 0;
	for (int v, e = cur[u]; e != -1 && df < f; cur[u] = e = nxt[e]) {
		if (flo[e] < cap[e] && L[v = ep[e^1]] == L[u] + 1) {
			cf = dfs(v, t, min(cap[e] - flo[e], f - df));
			flo[e] += cf;
			flo[e^1] -= cf;
			df += cf;
		}
	}
	return df;
}

int main() {
		/*
	while (true) {
		puts("!!!");
		string ss = getl();
		while (ss == "") {
			ss = getl();
		}
		if (ss == "-1") {
			break;
		}*
		vector<string> grid;
		grid.push_back(ss);
		ss = getl();
		while (ss != "" && ss != "-1") {
			grid.push_back(ss);
			ss = getl();
		}*/
	vector<string> grid;
	string ss;
	while (getline(cin, ss)) {
		grid.clear();
		do {
			//cerr << "ss: " << ss << endl;
			if (ss == "") break;
			grid.push_back(ss);
		} while (getline(cin, ss));
		//cerr << "endloop" << endl;
		int n = grid.size(), m = grid[0].length();
		int s = n * m + 1, t = n * m + 2;
		init();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (grid[i][j] == 'W') {
					addedge(s, i * m + j + 1, 1);
					for (int k = 0; k < 4; k++) {
						int x = i + dx[k], y = j + dy[k];
						if (x >= 0 && x < n && y >= 0 && y < m && grid[x][y] == 'I') {
							addedge(i * m + j + 1, x * m + y + 1, 1);
						}
					}
				} else if (grid[i][j] == 'N') {
					addedge(i * m + j + 1, t, 1);
				} else {
					for (int k = 0; k < 4; k++) {
						int x = i + dx[k], y = j + dy[k];
						if (x >= 0 && x < n && y >= 0 && y < m && grid[x][y] == 'N') {
							addedge(i * m + j + 1, x * m + y + 1, 1);
						}
					}
				}
			}
		}
		//cerr << "built graph" << endl;
		long long flow = 0;
		while (bfs(s, t)) {
			flow += dfs(s, t, INF);
		}
		printf("%lld\n", flow);
	}
}
