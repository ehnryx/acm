#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int H = 19;
const int N = 1<<H;
int arr[N], rend[N], clen[N];

struct RMQ {
	int rmq[2*N];

	void build(int n, int a[]) {
		memset(rmq, INF, sizeof rmq);
		for (int i=1; i<=n; i++) rmq[i+N] = a[i];
		for (int i=N-1; i>0; i--) rmq[i] = max(rmq[2*i], rmq[2*i+1]);
	}

	int search(int i, int lb) {
		i += N;
		while (i > 1) {
			if (i%2 == 0) i /= 2;
			else if (rmq[i] <= lb) i = i/2+1;
			else break;
		}
		while (i < N) {
			i *= 2;
			if (rmq[i] <= lb) i++;
		}
		return i-N;
	}

	int query(int l, int r) {
		int res = 0;
		for (l+=N, r+=N; l < r; l/=2, r/=2) {
			if (l&1) res = max(res, rmq[l++]);
			if (r&1) res = max(res, rmq[--r]);
		}
		return res;
	}
};

RMQ input, reach, lengths;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n, m;
	cin >> n >> m;

	unordered_map<int,vector<int>> index;
	for (int i=1; i<=n; i++) {
		cin >> arr[i];
		index[arr[i]].push_back(i);
	}
	input.build(n, arr);

	for (int i=1; i<=n; i++) {
		int rb = input.search(i+1, arr[i]);
		rend[i] = *prev(upper_bound(index[arr[i]].begin(), index[arr[i]].end(), rb));
		clen[i] = rend[i] - i;
		cerr << i << ": " << rend[i] << " -> " << clen[i] << nl;
	}
	reach.build(n, rend);
	lengths.build(n, clen);

	int a, b;
	while (m--) {
		cin >> a >> b;
	}

	return 0;
}
