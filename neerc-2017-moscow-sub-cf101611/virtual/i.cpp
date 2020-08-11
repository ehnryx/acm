#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const int N = 1501;

int v[N][N];
bitset<N> b[N];
int tcnt[N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int n, k; cin >> n >> k;
	fill(tcnt, tcnt+n, 1);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			cin >> v[i][j];
			b[i][j] = abs(v[i][j])%2;
		}
	}

	for (int j=0; j<k; j++) {
		if (!b[j][j]) {
			for (int i=j+1; i<n; i++) {
				if (b[i][j]) {
					swap(b[i],b[j]);
					swap(tcnt[i],tcnt[j]);
				}
			}
		}
		for (int i=j+1; i<n; i++) {
			if (b[i][j]) {
				b[i] ^= b[j];
				tcnt[i] ^= tcnt[j];
			}
		}
	}

	for (int i=k; i<n; i++) {
		for (int j=0; j<k; j++) {
			if (b[i][j]) {
				b[i] ^= b[j];
				tcnt[i] ^= tcnt[j];
			}
		}
		if (tcnt[i] == 1) {
			cout << "No" << nl;
			return 0;
		}
	}

	cout << "Yes" << nl;

	return 0;
}
