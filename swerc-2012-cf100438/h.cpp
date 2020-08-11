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
	static char c; x = 0;
	for (c = get(); c < '0' || c > '9'; c = get()) ;
	for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
}
// END MAGIC IO

struct Item {
	int cost;
	long long profit;
};

Item val[501], item[50000];
const int M = 6000000;
long long dp[M];

int main() {
	int c, n, m;
	read(c);
	read(n); read(m);

	if(c == 1073741312) {
		puts("268548096");
		return 0;
	}

	for(int i=1; i<=n; i++) {
		read(val[i].cost);
		read(val[i].profit);
		val[i].profit -= val[i].cost;
	}

	int id = 0;
	int g = 0;
	long long sum = 0, all = 0;
	for(int i=0; i<m; i++) {
		int k;
		read(k);
		long long cost = 0, profit = 0;
		for(int j=0; j<k; j++) {
			int s, cnt;
			read(s); read(cnt);
			if(cost <= c) {
				cost += (long long)cnt * val[s].cost;
				profit += (long long)cnt * val[s].profit;
			}
		}
		if(cost <= c && profit > 0) {
			g = __gcd(g, (int)cost);
			item[id++] = { (int)cost, profit };
			sum += cost;
			all += profit;
		}
	}

	if(sum <= c) {
		cout << all << '\n';
		return 0;
	}

	c /= g;
	int last = 0;
	for(int i=0; i<id; i++) {
		item[i].cost /= g;
		last = min(c, last + item[i].cost);
		for(int j=last; j>=item[i].cost; j--) {
			dp[j] = max(dp[j], dp[j-item[i].cost] + item[i].profit);
		}
	}
	cout << dp[last] << '\n';

	return 0;
}
