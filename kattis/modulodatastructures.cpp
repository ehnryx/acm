#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2,abm,fma")
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
template <typename T> inline void read(T &x) {
	static char c; x = 0; int sgn = 0;
	for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
	for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
	if (sgn) x = -x;
}
void readchar(char& c) {
	while (isspace(c = get()));
}
// END MAGIC IO

const int N = 2e5 + 1;
const int S = 200;
int val[N], memo[S][S];

int main() {
	int n, m;
	read(n); read(m);
	while(m--) {
		int t;
		read(t);
		if(t == 1) {
			int a, b, c;
			read(a); read(b); read(c);
			if(b < S) {
				memo[b][a] += c;
			} else {
				for(int i=a; i<=n; i+=b) {
					val[i] += c;
				}
			}
		} else {
			int x;
			read(x);
			int res = val[x];
			for(int i=1; i<S; i++) {
				res += memo[i][x%i];
			}
			printf("%d\n", res);
		}
	}
	return 0;
}
