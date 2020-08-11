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

const vector<int> gray = {
	0b0,
	0b1,
	0b11, 0b10,
	0b110, 0b111, 0b101, 0b100,
	0b1100, 0b1101, 0b1111, 0b1110, 0b1010, 0b1011, 0b1001, 0b1000,
	0b11000, 0b11001, 0b11011, 0b11010, 0b11110, 0b11111, 0b11101, 0b11100,
	0b10100, 0b10101, 0b10111, 0b10110, 0b10010, 0b10011, 0b10001, 0b10000,
	0b110000, 0b110001, 0b110011, 0b110010, 0b110110, 0b110111, 0b110101, 0b110100,
	0b111100, 0b111101, 0b111111, 0b111110, 0b111010, 0b111011, 0b111001, 0b111000,
	0b101000, 0b101001, 0b101011, 0b101010, 0b101110, 0b101111, 0b101101, 0b101100,
	0b100100, 0b100101, 0b100111, 0b100110, 0b100010, 0b100011, 0b100001, 0b100000,
	0b000000
};

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n, k;
	cin >> n >> k;
	k = (2*n-1)/3;

	int bf = -1;
	for (int i=1; i<=n; i++) {
		if (i + (n-i+1)/2 >= k) {
			bf = i;
			break;
		}
	}
	assert(bf != -1);

	vector<int> ans;
	for (int i=1; i<1<<bf; i++) {
		ans.push_back(32 - __builtin_clz(gray[i-1]^gray[i]));
	}
	ans.push_back(bf);
	for (int j=bf+1; j<=n; j++) {
		ans.push_back(j);
	}
	for (int i=1; i<1<<bf; i++) {
		ans.push_back(32 - __builtin_clz(gray[i-1]^gray[i]));
	}

	cerr << "allowed: " << 6*n+6 << nl;
	cout << ans.size() << nl;
	for (int it : ans) {
		cout << it << " ";
	}
	cout << nl;

	return 0;
}
