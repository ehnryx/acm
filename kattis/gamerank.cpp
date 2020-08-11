//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

vector<int> need(26);

pair<int,int> increase(int rank, int star) {
	if(star == need[rank]) {
		return make_pair(rank - 1, 1);
	} else {
		return make_pair(rank, star + 1);
	}
}

pair<int,int> decrease(int rank, int star) {
	if(star == 0) {
		if(rank < 20) {
			return make_pair(rank + 1, need[rank + 1] - 1);
		} else {
			assert(rank == 20 && star == 0);
			return make_pair(20, 0);
		}
	} else {
		return make_pair(rank, star - 1);
	}
}

// TODO
// double-check correctness
// read limits carefully
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	need[0] = INF;
	for(int i=1; i<=10; i++) need[i] = 5;
	for(int i=11; i<=15; i++) need[i] = 4;
	for(int i=16; i<=20; i++) need[i] = 3;
	for(int i=21; i<=25; i++) need[i] = 2;

	string s;
	cin >> s;
	int rank = 25;
	int star = 0;
	int wcnt = 0;
	for(char c : s) {
		if(c == 'W') {
			if(++wcnt >= 3 && rank > 5) {
				tie(rank, star) = increase(rank, star);
			}
			tie(rank, star) = increase(rank, star);
		} else {
			wcnt = 0;
			if(1 <= rank && rank <= 20) {
				tie(rank, star) = decrease(rank, star);
			}
		}
	}

	if(rank > 0) {
		cout << rank << nl;
	} else {
		cout << "Legend" << nl;
	}

	return 0;
}
