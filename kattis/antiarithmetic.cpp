//#pragma GCC optimize("-O3")
#include <bits/stdc++.h>
using namespace std;

// MAGIC IO
inline char get(void) {
	static char buf[100000], *S = buf, *T = buf;
	if (S == T) {
		T = (S = buf) + fread(buf, 1, 100000, stdin);
		if (S == T) return EOF;
	}
	return *S++;
}
inline void read(int &x) {
	static char c; x = 0; int sgn = 0;
	for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
	for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
	if (sgn) x = -x;
}
void readchar(char& c) {
	while (isspace(c = get()));
}
// END MAGIC IO

#define nl '\n'

const int N = 1e4+1;
int arr[N];
int rcnt[N];
bitset<2*N> lv, rv;

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n; char c;
	for (;;) {
		cin >> n;
		if (!n) break;
		cin >> c;

		memset(rcnt, 0, sizeof rcnt);
		lv.reset(); rv.reset();
		for (int i=0; i<n; i++) {
			cin >> arr[i];
			rv.set(arr[i]+n);
			rcnt[arr[i]]++;
		}

		bool bad = false;
		for (int i=0; i<n; i++) {
			--rcnt[arr[i]];
			if (!rcnt[arr[i]]) {
				rv.reset(arr[i]+n);
			}
			if ((lv<<arr[i] & rv>>arr[i]).any()) {
				bad = true;
				break;
			}
			if (!rcnt[arr[i]]) {
				lv.set(n-arr[i]);
			}
		}
		cout << (bad?"no":"yes") << nl;
	}

	return 0;
}

