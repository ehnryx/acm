#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const char nl = '\n';

const int mask = 0b111;
const int G = 4200;
const int D = 7;
int gid = 0;
int groups[G];
int skipg[G], addg[G], stopg[G][D][2], transg[G][D][2], pairg[G][D][D][2][2];
set<int> all_groups;

void init() {
	memset(skipg, -1, sizeof skipg);
	memset(addg, -1, sizeof addg);
	memset(stopg, -1, sizeof stopg);
	memset(transg, -1, sizeof transg);
	memset(pairg, -1, sizeof pairg);
}

int put(int g, int i, int v) {
	return g ^ ((g >> 3*i & mask) ^ v) << 3*i;
}

int renumerate(int g) {
	vector<int> seen(D+1);
	int sid = 0;
	for(int i=0; i<D; i++) {
		int v = g >> 3*i & mask;
		if(v == 0) continue;
		if(!seen[v]) seen[v] = ++sid;
		g = put(g, i, seen[v]);
		assert((g >> 3*i & mask) == seen[v]);
	}
	return g;
}

int flatten(vector<int> vals) {
	int res = 0;
	for(int i=0; i<vals.size(); i++) {
		res |= vals[i] << 3*i;
	}
	return res;
}

void generate_groups(int n, vector<int> cur) {
	if(n == 0) {
		int res = renumerate(flatten(cur));
		if(all_groups.insert(res).second) {
			groups[gid++] = res;
		}
		return;
	}
	for(int i=0; i<=D; i++) {
		cur.push_back(i);
		generate_groups(n-1, cur);
		cur.pop_back();
	}
}

int mex(int g) {
	vector<bool> seen(D+1);
	for(int i=0; i<D; i++) {
		seen[g >> 3*i & mask] = true;
	}
	for(int i=1; i<=D; i++) {
		if(!seen[i]) return i;
	}
	assert(false);
}

int join(int g, int a, int b) {
	for(int i=0; i<D; i++) {
		if((g >> 3*i & mask) == a) {
			g = put(g, i, b);
		}
	}
	return g;
}

int index(int g) {
	int* it = lower_bound(groups, groups + gid, g);
	assert(it != groups + gid);
	assert(*it == g);
	return it - groups;
}

void generate_transitions(int n) {
	int len = 3 * (n-1);
	for(int i=0; i<gid; i++) {
		int g = groups[i];

		addg[i] = index(renumerate(g >> 3 | mex(g>>3) << len));
		skipg[i] = index(renumerate(g >> 3));

		for(int j=0; j<n; j++) {
			int jv = g >> 3*j & mask;
			if(jv == 0) continue;

			int remj = put(g, j, 0);
			stopg[i][j][0] = index(renumerate(remj >> 3));
			stopg[i][j][1] = index(renumerate(g >> 3));
			transg[i][j][0] = index(renumerate(remj >> 3 | jv << len));
			transg[i][j][1] = index(renumerate(g >> 3 | jv << len));

			for(int k=0; k<j; k++) {
				int kv = g >> 3*k & mask;
				if(kv == 0 || kv == jv) continue;

				int remjk = put(put(g, j, 0), k, 0);
				int remk = put(g, k, 0);
				pairg[i][j][k][0][0] = index(renumerate(join(remjk >> 3, jv, kv)));
				pairg[i][j][k][0][1] = index(renumerate(join(remj >> 3, jv, kv)));
				pairg[i][j][k][1][0] = index(renumerate(join(remk >> 3, jv, kv)));
				pairg[i][j][k][1][1] = index(renumerate(join(g >> 3, jv, kv)));
			}
		}
	}
}

int dp[1<<D][G][3], ndp[1<<D][G][3];
void push(int g, int c, int st, int v) {
	ndp[c][g][st] = max(ndp[c][g][st], v);
}

// TODO
// double-check correctness
// read limits carefully
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	init();

	int n, d, m;
	cin >> n >> d >> m;

	generate_groups(d, {});
	sort(groups, groups + gid);
	generate_transitions(d);
	//cerr<<"groups: "<<gid<<nl;
	assert(gid < G);

	int a[n];
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}

	memset(dp, -1, sizeof dp);
	dp[0][0][0] = 0;

	for(int i=0; i<n; i++) {
		memset(ndp, -1, sizeof ndp);
		//cerr<<"iteration "<<i<<nl;

		for(int c=0; c<1<<d; c++) {

			for(int r=0; r<gid; r++) {
				int g = groups[r];

				for(int st=0; st<=2; st++) {
					if(dp[c][r][st] == -1) continue;
					int val = dp[c][r][st];
					//cerr<<"dp "<<bitset<2>(c)<<" "<<bitset<6>(g)<<" "<<st<<" -> "<<val<<nl;

					// the first node in the window has connections
					if(g & mask) {
						if((c & 1) || i-d < 0 || abs(a[i] - a[i-d]) > m) continue;

						// right endpoint
						if(st < 2) {
							push(stopg[r][0][0], c >> 1, st + 1, val + 1);
						}

						// straight
						push(transg[r][0][0], c >> 1, st, val + 1);

						// right turn
						for(int j=1; j<d; j++) {
							int cj = c >> j & 1;
							if(i-d+j < 0 || abs(a[i] - a[i-d+j]) > m || pairg[r][j][0][cj][0] == -1) continue;
							push(pairg[r][j][0][cj][0], (c ^ cj << j) >> 1, st, val + 1);
						}

					}

					// no connections
					else {

						// skip
						push(skipg[r], c >> 1, st, val);

						// take endpoints
						if(st < 2) {
							// left endpoint
							push(addg[r], c >> 1, st + 1, val + 1);
							// right endpoint
							for(int j=1; j<d; j++) {
								int cj = c >> j & 1;
								if(i-d+j < 0 || abs(a[i] - a[i-d+j]) > m || stopg[r][j][cj] == -1) continue;
								push(stopg[r][j][cj], (c ^ cj << j) >> 1, st + 1, val + 1);
							}
						}

						// left turn
						push(addg[r], c >> 1 | 1 << (d-1), st, val + 1);

						// connections
						for(int j=1; j<d; j++) {
							int cj = c >> j & 1;
							if(i-d+j < 0 || abs(a[i] - a[i-d+j]) > m || transg[r][j][cj] == -1) continue;

							// straight
							push(transg[r][j][cj], (c ^ cj << j) >> 1, st, val + 1);

							for(int k=1; k<j; k++) {
								int ck = c >> k & 1;
								if(i-d+k < 0 || abs(a[i] - a[i-d+k]) > m || pairg[r][j][k][cj][ck] == -1) continue;

								// right turn
								push(pairg[r][j][k][cj][ck], (c ^ cj << j ^ ck << k) >> 1, st, val + 1);
							}
						}

					}

				}
			}
		}

		swap(dp, ndp);
		//cerr<<nl;
	}

	cout << max(1, dp[0][0][2]) << nl;

	return 0;
}
