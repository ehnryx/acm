#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
#define nl '\n'

const int N = 26;
int a[N], cnt[N+1];

int dsu[N], sz[N];
int find(int i) {
	if(dsu[i] == -1) return i;
	return dsu[i] = find(dsu[i]);
}
void link(int i, int j) {
	i = find(i); j = find(j);
	if(i != j) {
		dsu[i] = j;
		sz[j] += sz[i];
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int T;
	cin >> T;
	while(T--) {
		fill(dsu, dsu+N, -1);
		fill(sz, sz+N, 1);
		memset(cnt, 0, sizeof cnt);
		string s;
		cin >> s;
		for(int i=0; i<N; i++) {
			a[i] = s[i]-'A';
			link(i, a[i]);
		}
		for(int i=0; i<N; i++) {
			if(i == find(i)) {
				cnt[sz[i]]++;
			}
		}
		bool ok = true;
		for(int i=2; i<=N; i+=2) {
			ok &= (cnt[i]%2 == 0);
		}
		if(ok) cout << "Yes" << nl;
		else cout << "No" << nl;
	}

	return 0;
}
