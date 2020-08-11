//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "numbers"

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

enum {
	ONE,
	DOUBLE,
	TEN,
	HUNDRED,
	THOUSAND,
	MILLION,
	AND,
	SPACE,
	NO,
};

const unordered_map<string,int> special = {
	{"and", AND},
	{"hundred", HUNDRED},
	{"thousand", THOUSAND},
	{"million", MILLION},
	{" ", SPACE},
	{"\n", SPACE},
};

const unordered_map<string,int> number = {
	{"one", 1},
	{"two", 2},
	{"three", 3},
	{"four", 4},
	{"five", 5},
	{"six", 6},
	{"seven", 7},
	{"eight", 8},
	{"nine", 9},
	{"ten", 10},
	{"eleven", 11},
	{"twelve", 12},
	{"thirteen", 13},
	{"fourteen", 14},
	{"fifteen", 15},
	{"sixteen", 16},
	{"seventeen", 17},
	{"eighteen", 18},
	{"nineteen", 19},
	{"twenty", 20},
	{"thirty", 30},
	{"forty", 40},
	{"fifty", 50},
	{"sixty", 60},
	{"seventy", 70},
	{"eighty", 80},
	{"ninety", 90},
};

string tolower(string s) {
	for(char& c : s) {
		c = tolower(c);
	}
	return s;
}

bool update(int& x, int v) {
	x = max(x, v);
	return x == v;
}

const int N = 2e4 + 1;

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);
///*
#ifdef ONLINE_JUDGE
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#endif
//*/

	vector<string> words;
	for(char c; (c = getchar()) != EOF; ) {
		if(words.empty() || !isalpha(c) || !isalpha(words.back().back())) {
			words.push_back(string(1, c));
		} else {
			words.back().push_back(c);
		}
	}

	int n = words.size();
	vector<int> arr;
	transform(words.begin(), words.end(), back_inserter(arr), [](string& w) -> int {
		string s = tolower(w);
		if(s == "zero") w = "0";
		if(special.count(s)) return special.at(s);
		if(number.count(s)) {
			if(number.at(s) < 10) return ONE;
			if(number.at(s) >= 20) return TEN;
			return DOUBLE;
		}
		return NO;
	});
	arr.push_back(NO);

	const int S = 15;
	vector<vector<int>> dp(n+1, vector<int>(S, -INF));
	vector<vector<pair<int,int>>> pre(n+1, vector<pair<int,int>>(S, make_pair(-1, -1))); // state, length
	dp[n][0] = 0;

	//  O HA  T  O |M| O HA T O |T| O HA T O |_|
	// 14 13 12 11  10 9  8 7 6  5  4  3 2 1  0
	for(int i=n-1; i>=0; i--) {
		if(arr[i] == DOUBLE) {
			if(update(dp[i][2], dp[i+1][0] + 1)) pre[i][2] = make_pair(0, 1);
			if(arr[i+1] == SPACE) {
				if(update(dp[i][7], dp[i+2][5] + 1)) pre[i][7] = make_pair(5, 2);
				if(update(dp[i][12], dp[i+2][10] + 1)) pre[i][12] = make_pair(10, 2);
			}
		}

		else if(arr[i] == ONE) {
			if(update(dp[i][1], dp[i+1][0] + 1)) pre[i][1] = make_pair(0, 1);
			if(arr[i+1] == SPACE) {
				if(update(dp[i][4], dp[i+2][3] + 1)) pre[i][4] = make_pair(3, 2);
				for(int j=5; j<S; j+=5) {
					if(update(dp[i][1+j], dp[i+2][0+j] + 1)) pre[i][1+j] = make_pair(0+j, 2);
					if(update(dp[i][4+j], dp[i+2][3+j] + 1)) pre[i][4+j] = make_pair(3+j, 2);
				}
			}
		}

		else if(arr[i] == TEN) {
			if(update(dp[i][2], dp[i+1][0] + 1)) pre[i][2] = make_pair(0, 1);
			if(arr[i+1] == SPACE) {
				if(update(dp[i][2], dp[i+2][1] + 1)) pre[i][2] = make_pair(1, 2);
				for(int j=5; j<S; j+=5) {
					if(update(dp[i][2+j], dp[i+2][0+j] + 1)) pre[i][2+j] = make_pair(0+j, 2);
					if(update(dp[i][2+j], dp[i+2][1+j] + 1)) pre[i][2+j] = make_pair(1+j, 2);
				}
			}
		}

		else if(arr[i] == HUNDRED) {
			if(update(dp[i][3], dp[i+1][0] + 1)) pre[i][3] = make_pair(0, 1);
			if(arr[i+1] == SPACE) {
				if(arr[i+2] == AND && arr[i+3] == SPACE) {
					if(update(dp[i][3], dp[i+4][1] + 2)) pre[i][3] = make_pair(1, 4);
					if(update(dp[i][3], dp[i+4][2] + 2)) pre[i][3] = make_pair(2, 4);
				}
				for(int j=5; j<S; j+=5) {
					if(update(dp[i][3+j], dp[i+2][0+j] + 1)) pre[i][3+j] = make_pair(0+j, 2);
					if(arr[i+2] == AND && arr[i+3] == SPACE) {
						if(update(dp[i][3+j], dp[i+4][1+j] + 2)) pre[i][3+j] = make_pair(1+j, 4);
						if(update(dp[i][3+j], dp[i+4][2+j] + 2)) pre[i][3+j] = make_pair(2+j, 4);
					}
				}
			}
		}

		else if(arr[i] == THOUSAND) {
			if(update(dp[i][5], dp[i+1][0] + 1)) pre[i][5] = make_pair(0, 1);
			if(arr[i+1] == SPACE) {
				if(update(dp[i][5], dp[i+2][1] + 1)) pre[i][5] = make_pair(1, 2);
				if(update(dp[i][5], dp[i+2][2] + 1)) pre[i][5] = make_pair(2, 2);
				if(update(dp[i][5], dp[i+2][4] + 1)) pre[i][5] = make_pair(4, 2);
			}
		}

		else if(arr[i] == MILLION) {
			if(update(dp[i][10], dp[i+1][0] + 1)) pre[i][10] = make_pair(0, 1);
			if(arr[i+1] == SPACE) {
				if(update(dp[i][10], dp[i+2][1] + 1)) pre[i][10] = make_pair(1, 2);
				if(update(dp[i][10], dp[i+2][2] + 1)) pre[i][10] = make_pair(2, 2);
				if(update(dp[i][10], dp[i+2][4] + 1)) pre[i][10] = make_pair(4, 2);
				if(update(dp[i][10], dp[i+2][5] + 1)) pre[i][10] = make_pair(5, 2);
				if(update(dp[i][10], dp[i+2][6] + 1)) pre[i][10] = make_pair(6, 2);
				if(update(dp[i][10], dp[i+2][7] + 1)) pre[i][10] = make_pair(7, 2);
				if(update(dp[i][10], dp[i+2][9] + 1)) pre[i][10] = make_pair(9, 2);
			}
		}

		if(update(dp[i][0], dp[i+1][0])) pre[i][0] = make_pair(0, 1);
		if(number.count(tolower(words[i]))) {
			for(int j=0; j<S; j+=5) {
				if(update(dp[i][0], dp[i][1+j])) pre[i][0] = make_pair(1+j, 0);
				if(update(dp[i][0], dp[i][2+j])) pre[i][0] = make_pair(2+j, 0);
				if(update(dp[i][0], dp[i][4+j])) pre[i][0] = make_pair(4+j, 0);
			}
		}
	}

	//cerr<<nl;
	//cerr<<"RECOVER" << nl;

	//cerr<<"n = "<<n<<endl;
	for(int i=0, j=0, res=0; i<n; ) {
		auto [nj, len] = pre[i][j];
		//cerr<<"@ "<<i<<" "<<j<<" -> "<<nj<<" "<<len<<endl;
		assert(len >= 0);
		if(j == 0 && nj == 0) {
			cout << words[i];
		} else {
			if(j == 1 || j == 2) {
				res += number.at(tolower(words[i]));
			} else if(j == 4) {
				res += number.at(tolower(words[i])) * 1e2;
			} else if(j == 6 || j == 7) {
				res += number.at(tolower(words[i])) * 1e3;
			} else if(j == 9) {
				res += number.at(tolower(words[i])) * 1e2 * 1e3;
			} else if(j == 11 || j == 12) {
				res += number.at(tolower(words[i])) * 1e6;
			} else if(j == 14) {
				res += number.at(tolower(words[i])) * 1e2 * 1e6;
			}
			if(nj == 0) {
				cout << to_string(res);
				res = 0;
			}
			//cerr<<"- "<<words[i];
		}
		i += len;
		j = nj;
		//cerr<<";"<<endl;
	}

	//cerr << dp[0][0] << " words converted" << nl;

	return 0;
}
