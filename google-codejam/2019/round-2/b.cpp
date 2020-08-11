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
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
	return os << '(' << v.first << ',' << v.second << ')';
}
template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
	for (const T& it : v) { os << it << " "; } return os;
}
template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
	os << "{ "; for (const T& it : v) { os << it << " "; }
	return os << '}';
}
template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
	os << "{ "; for (const pair<T,U>& it : v) { os << it << " "; }
	return os << '}';
}

void casesolve();

////////////////////////////////////////////////////////////////////////

//int M, K;

void init() {
}

int main(int argc, char** argv) {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	//M = atoi(argv[1]);
	//K = atoi(argv[2]);

	init();

	int T;
	cin >> T;
	for (int cc = 1; cc <= T; cc++) {
		//cout << "Case #" << cc << ": ";
		casesolve();
	}

	//cerr<<"params: "<<M<<" "<<K<<nl;
	return 0;
}

////////////////////////////////////////////////////////////////////////



void caseinit() {
}

void casesolve() {
	caseinit();

	const int M = 6; // 7; // 8;
	const int K = 10; // 11; // 16;
	int day;

	for(int i=0; i<100-M-K-1; i++) {
		cin >> day;
		cout << M+1 + i%(20-M) << " " << 1 << endl;
	}

	vector<ld> cnt(M+1);
	for(int i=1; i<=M; i++) {
		cin >> day;
		cout << i << " " << 0 << endl;
		int n;
		cin >> n;
		for(int j=0; j<n; j++) {
			int v;
			cin >> v;
		}
		cnt[i] = n;
	}
	cnt[0] = INF;

	int put = 0;
	for(int i=1; i<=M; i++) {
		if(cnt[i] <= cnt[put]) {
			put = i;
		}
	}
	assert(put);

	for(int i=0; i<K; i++) {
		cin >> day;
		int add = 0;
		for(int j=1; j<=M; j++) {
			if(j == put) continue;
			if(cnt[j] <= cnt[add]) {
				add = j;
			}
		}
		assert(add);
		cnt[add] += 1;
		cout << add << " " << 1 << endl;
	}

	cin >> day;
	cout << put << " " << 100 << endl;
	assert(day == 100);

	return;
}

