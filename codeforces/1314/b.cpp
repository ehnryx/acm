//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int L = 18;
const int N = 1<<L;
int win[L][N], lose[2*L][N];
bool good[N];

int countw(int n, int v) {
	//cerr<<"countw"<<nl;
	v /= 2;
	int res = 0;
	for(int j=0; j<n; j++, v/=2) {
		res += !win[j][v];
	}
	return res;
}

void setw(int n, int v) {
	//cerr<<"setw"<<nl;
	v /= 2;
	for(int j=0; j<n; j++, v/=2) {
		win[j][v] = true;
	}
}

int countl(int n, int v) {
	//cerr<<"countl"<<nl;
	int res = !win[0][v/2];
	v /= 4;
	for(int j=1; j<n; j++, v/=2) {
		res += !lose[2*j][v];
		res += !lose[2*j+1][v];
	}
	return res;
}

void setl(int n, int v) {
	//cerr<<"setl"<<nl;
	win[0][v/2] = true;
	v /= 4;
	for(int j=1; j<n; j++, v/=2) {
		lose[2*j][v] = true;
		lose[2*j+1][v] = true;
	}
}

int wrong(int n, const vector<int>& a) {
	int ans = 0;
	for(int v : a) {
		int w = countw(n, v);
		int l = countl(n, v);
		if(w > l) {
			ans += w;
			setw(n, v);
			//cerr<<"win -> "<<v+1<<" counted "<<w<<nl;
		} else if(w < l) {
			ans += l;
			setl(n, v);
			//cerr<<"lose -> "<<v+1<<" counted "<<l<<nl;
		} else {
			ans += w;
			if(rng()%2) setw(n, v);
			else setl(n, v);
		}
	}
	return ans;
}

int solve(int n) {
	vector<int> a;
	a.push_back(0);
	for(int i=0; i<n; i++) {
		for(int j=0; j<1<<i; j++) {
			a.push_back(a[j] + (1<<(n-i-1)));
		}
	}
	vector<int> b;
	for(int v : a) {
		if(good[v]) {
			b.push_back(v);
		}
	}
	return wrong(n, b);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n, k;
	cin >> n >> k;

	vector<int> a(k);
	for(int i=0; i<k; i++) {
		cin >> a[i];
		--a[i];
		good[a[i]] = true;
	}
	int ans = solve(n);
	while(clock()<1.789*CLOCKS_PER_SEC) {
		shuffle(a.begin(), a.end(), rng);
		ans = max(ans, wrong(n, a));
	}
	cout << ans + (k>0) << nl;

	return 0;
}
