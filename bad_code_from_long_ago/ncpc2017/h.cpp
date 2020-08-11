#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG
#define USE_MAGIC_IO

#define ll int
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble double
#define nl '\n'
typedef complex<ldouble> pt;
/*
const ll MOD = 1e9+7;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;*/
const int INF = 0x3f3f3f3f;
const double EPS = 1e-9;

////////////////////////////////////////////////////////////////////////////////
// Maximum flow
////////////////////////////////////////////////////////////////////////////////
//*!
namespace FLOW {
const int N = 400002;
const int M = 800001;
//*/
// data structures and helper functions common to all flow routines
int par[N], first[N], nxt[2*M], ep[2*M], m;
ll flo[2*M], cap[2*M], cost[2*M];
void init() { m = 0; memset(first,-1,sizeof first); memset(flo,0,sizeof flo); }
void add_edge(int a, int b, ll c=1, ll p=0) { //a,b - nodes, c, p - cap, price
  nxt[m] = first[ep[m]=a], first[ep[m]] = m, cap[m] = c, cost[m] =  p, ++m;
  nxt[m] = first[ep[m]=b], first[ep[m]] = m, cap[m] = 0, cost[m] = -p, ++m; }
 
// Dinic's fast maximum flow: tested on NAIPC 2015 F but not theoretically
// proven to be floating-point-safe.
// USAGE: 1) init(); 2) add edges
// 3) ll flow=0; while (bfs(S, T)) flow += dfs(S, T, INF);
// V^2E in general, min(V^(2/3),sqrt(E))E on unit caps, sqrt(V)E on bipartite
int L[N], cur[N];
bool bfs(int s, int t) {
  memset(L, INF, sizeof L);
  queue<int> q; q.push(s); L[s] = 0;
  while (!q.empty()) { int u = q.front(); q.pop();
    for (int v, e = cur[u] = first[u]; e != -1; e = nxt[e])
      if (L[v=ep[e^1]] == INF && flo[e] < cap[e])
        q.push(v), L[v] = L[u]+1;
  } return L[t] < INF; }
ll dfs(int u, int t, ll f) {
  if (u == t) return f;
  ll cf, df = 0;
  for (int v, e = cur[u]; e != -1 && df < f; cur[u] = e = nxt[e])
    if (flo[e] < cap[e] && L[v=ep[e^1]] == L[u]+1) {
      cf = dfs(v, t, min(cap[e]-flo[e], f-df));
      flo[e] += cf; flo[e^1] -= cf; df += cf;
    } return df; }
}

// MAGIC IO
#ifdef USE_MAGIC_IO
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
#else
#define get() getchar()
#define read(x) scanf("%d",&x)
#endif
void readchar(char& c) {
	while (isspace(c = get()));
}

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);

	FLOW::init();

	int S = 400000;
	int T = 400001;

	int n, m; read(n); read(m);
	vector<pair<double, int>> people(n);
	for (int i = 0; i < n; i++) {
		int x, y; read(x); read(y);
		people[i] = {arg(pt(x, y)), i};
		FLOW::add_edge(S, i);
	}

	set<ldouble> lines;
	unordered_map<ldouble, int> dumb;
	int cap[m];
	for (int i = 0; i < m; i++) {
		int x, y; read(x); read(y); read(cap[i]);
		lines.insert(arg(pt(x, y)));
		dumb[arg(pt(x,y))] = i;
	}

	int nans = 0;
	vector<int> ans(n, -1);
	vector<vector<int>> id(n);
	int cid = 0;

	sort(people.begin(), people.end());

	vector<pair<double, int>> todo;
	double prev = 500;

	for (int i = 0; i < n; i++) {
		ldouble a = people[i].first;
		auto it = lines.lower_bound(a);
		auto it2 = it;
		if (it == lines.begin()) {
			it2 = --lines.end();
			if (abs((*it - a) - (a - (*it2 - 2*M_PI))) < EPS) {
				if (abs(prev - a) < EPS)
					id[cid].push_back(people[i].second);
				else {
					prev = a;
					cid++;
				}
			}
			else if ((*it - a) < (a - (*it2 - 2*M_PI)))
				if (cap[dumb[*it]]) {
					cap[dumb[*it]]--;
					nans++;
					ans[people[i].second] = dumb[*it];
				}
			else
				if (cap[dumb[*it2]]) {
					cap[dumb[*it2]]--;
					nans++;
					ans[people[i].second] = dumb[*it2];
				}
		} else if (it == lines.end()) {
			it = lines.begin(), --it2;
			if (abs((*it - a + 2*M_PI) - (a - (*it2))) < EPS) {
				if (abs(prev - a) < EPS)
					id[cid].push_back(people[i].second);
				else {
					prev = a;
					cid++;
				}
			}
			else if ((*it - a + 2*M_PI) < (a - (*it2)))
				if (cap[dumb[*it]]) {
					cap[dumb[*it]]--;
					nans++;
					ans[people[i].second] = dumb[*it];
				}
			else 
				if (cap[dumb[*it2]]) {
					cap[dumb[*it2]]--;
					nans++;
					ans[people[i].second] = dumb[*it2];
				}
		}
		else {
			--it2;
			if (abs((*it - a) - (a - (*it2))) < EPS) {
				if (abs(prev - a) < EPS)
					id[cid].push_back(people[i].second);
				else {
					prev = a;
					cid++;
				}
			}
			else if ((*it - a) < (a - (*it2)))
				if (cap[dumb[*it]]) {
					cap[dumb[*it]]--;
					nans++;
					ans[people[i].second] = dumb[*it];
				}
			else
				if (cap[dumb[*it2]]) {
					cap[dumb[*it2]]--;
					nans++;
					ans[people[i].second] = dumb[*it2];
				}
		}
	}
	for (int i = 0; i < n && !id[i].empty(); i++) {
		FLOW::add_edge(S, i, id[i].size());
		ldouble a = people[id[i][0]].first;
		auto it = lines.lower_bound(a);
		auto it2 = it;
		if (it == lines.begin()) {
			it2 = --lines.end();
		} else if (it == lines.end()) {
			it = lines.begin();
			--it2;
		} else  {
			--it2;
		}
		FLOW::add_edge(i, dumb[*it], id[i].size());
		FLOW::add_edge(i, dumb[*it2], id[i].size());
	}
	for (const auto& p : dumb) {
		FLOW::add_edge(200000+p.second, T, cap[p.second]);
	}

	while (FLOW::bfs(S, T))
		nans += FLOW::dfs(S, T, INF);

	cout << nans << nl;

	return 0;
}
