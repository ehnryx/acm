#include <bits/stdc++.h>

using namespace std;

const int N = 1000000 + 5;

int a[N];
int id[N], orig[N], sz[N];
int son[N], ed[N], nxt[N];
int tag[N * 4], seg_min[N * 4], seg_max[N * 4];
bool vis[N];

inline void addedge(int x, int y, int& m) {
	nxt[++m] = son[x];
	son[x] = m;
	ed[m] = y;
}

void dfs(int begin) {
	vector<int> stk;
	int cnt = 0;
	stk.push_back(begin);
	while (!stk.empty()) {
		int x = stk.back();
		if (!vis[x]) {
			id[x] = ++cnt;
			orig[cnt] = x;
			sz[x] = 1;
			for (int i = son[x]; i; i = nxt[i]) {
				stk.push_back(ed[i]);
			}
			vis[x] = true;
		} else {
			stk.pop_back();
			vis[x] = false;
			for (int i = son[x]; i; i = nxt[i]) {
				sz[x] += sz[ed[i]];
			}
		}
	}
}

/*
int cnt = 0;
void dfs(int x) {
	if (x == 1) {
		cnt = 0;
	}
	sz[x] = 1;
	id[x] = ++cnt;
	orig[cnt] = x;
	for (int i = son[x]; i; i = nxt[i]) {
		dfs(ed[i]);
		sz[x] += sz[ed[i]];
	}
}
*/

inline void update(int x) {
	seg_min[x] = min(seg_min[x * 2], seg_min[x * 2 + 1]);
	seg_max[x] = max(seg_max[x * 2], seg_max[x * 2 + 1]);
}

inline void propagate(int x) {
	if (tag[x]) {
		tag[x * 2] += tag[x];
		tag[x * 2 + 1] += tag[x];
		seg_min[x * 2] += tag[x];
		seg_min[x * 2 + 1] += tag[x];
		seg_max[x * 2] += tag[x];
		seg_max[x * 2 + 1] += tag[x];
		tag[x] = 0;
	}
}

void build_seg(int x, int l, int r, int n) {
	if (l == r) {
		tag[x] = 0;
		if (l <= n) { 
			seg_min[x] = a[orig[l]];
			seg_max[x] = a[orig[l]];
		} else {
			seg_min[x] = INT_MAX;
			seg_max[x] = INT_MIN;
		}
		return;
	}
	int mid = (l + r) / 2;
	build_seg(x * 2, l, mid, n);
	build_seg(x * 2 + 1, mid + 1, r, n);
	update(x);
}

pair<int, int> query_seg(int x, int l, int r, int ll, int rr) {
	if (l == ll && r == rr) {
		return make_pair(seg_min[x], seg_max[x]);
	}
	propagate(x);
	int mid = (l + r) / 2;
	if (rr <= mid) {
		return query_seg(x * 2, l, mid, ll, rr);
	} else if (ll > mid) {
		return query_seg(x * 2 + 1, mid + 1, r, ll, rr);
	} else {
		auto pr_l = query_seg(x * 2, l, mid, ll, mid);
		auto pr_r = query_seg(x * 2 + 1, mid + 1, r, mid + 1, rr);
		return make_pair(min(pr_l.first, pr_r.first), max(pr_l.second, pr_r.second));
	}
}

void add_seg(int x, int l, int r, int ll, int rr, int d) {
	if (l == ll && r == rr) {
		tag[x] += d;
		seg_min[x] += d;
		seg_max[x] += d;
		return;
	}
	propagate(x);
	int mid = (l + r) / 2;
	if (rr <= mid) {
		add_seg(x * 2, l, mid, ll, rr, d);
	} else if (ll > mid) {
		add_seg(x * 2 + 1, mid + 1, r, ll, rr, d);
	} else {
		add_seg(x * 2, l, mid, ll, mid, d);
		add_seg(x * 2 + 1, mid + 1, r, mid + 1, rr, d);
	}
	update(x);
}

void build(int n) {
	build_seg(1, 1, n, n);
}

int query(int x, int n) {
	auto pr = query_seg(1, 1, n, id[x], id[x] + sz[x] - 1);
	return pr.second - pr.first;
}

void raise(int x, int d, int n) {
	add_seg(1, 1, n, id[x], id[x] + sz[x] - 1, d);
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			son[i] = 0;
		}
		for (int i = 2, m = 0; i <= n; i++) {
			int x;
			scanf("%d", &x);
			addedge(x, i, m);
		}
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
		}
		dfs(1);
		build(n);
		int q;
		scanf("%d", &q);
		while (q--) {
			char op[2];
			scanf("%s", op);
			if (*op == 'Q') {
				int x;
				scanf("%d", &x);
				printf("%d\n", query(x, n));
			} else {
				int x, y;
				scanf("%d%d", &x, &y);
				raise(x, y, n);
			}
		}
		memset(tag, 0, n * 4 * sizeof(int));
		memset(seg_min, 0, n * 4 * sizeof(int));
		memset(seg_max, 0, n * 4 * sizeof(int));
	}
	return 0;
}
