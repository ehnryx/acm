#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const int N = 3e5+10;

int l[N], r[N];
int w[N][10];
int b[N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int TT; cin >> TT;
	for (int tt = 1; tt <= TT; tt++) {
		cout << "Case #" << tt << ":\n";
		int n, m; cin >> n >> m;
		for (int i = 0; i < n; i++) {
			cin >> l[i] >> r[i];
			for (int j = 0; j < r[i] - l[i] + 1; j++) {
				cin >> w[i][j];
			}
		}
		for (int i = 0; i < m; i++) {
			cin >> b[i];
		}
	}

	return 0;
}
