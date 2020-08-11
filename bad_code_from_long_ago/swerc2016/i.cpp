#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG
#define USE_MAGIC_IO
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

#define ll int
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
#define nl '\n'
const ll MOD = 13;
const int INF = 0x3f3f3f3f;
//const ll INFLL = 0x3f3f3f3f3f3f3f3f;

// 39 lines
/**
 * Automatically mods everything by MOD
 *
 * egcd(a,b,x,y) calculates x,y that satisfy ax+by=gcd(a,b)
 * to find a^-1 mod m use egcd(a,b,x,y) and x = a^-1
 * egcd also returns the gcd of a and b
 */
ll egcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    ll d = egcd(b, a%b, y, x);
    y -= x * (a/b);
    return d;
}
struct Int {
    ll x;
    Int(ll n=0) { x = n % MOD; if (x < 0) x += MOD; }
    operator ll() const { return x; }
    #define op Int operator
    #define opr Int& operator
    op + (const Int& n) { return Int(x + n.x); }
    op - (const Int& n) { return Int(x - n.x); }
    op * (const Int& n) { return Int(x * n.x); }
    op / (const Int& n) { return Int(x * n.inverse()); }
    opr += (const Int& n) { x = (x + n.x) % MOD; return *this; }
    opr -= (const Int& n) { x = (x + MOD - n.x) % MOD; return *this; }
    opr *= (const Int& n) { x = (x * n.x) % MOD; return *this; }
    opr /= (const Int& n) { x = (x * n.inverse()) % MOD; return *this; }
    ll inverse() const {
        if (x == 0) throw runtime_error("divide by zero");
        ll c, d;
        egcd(x, MOD, c, d);
        return (c+MOD) % MOD;
    }
};

// 125 lines
/**
 * USAGE:
 *  to declare an nxn diagonal matrix: Matrix<T> mat(n,d);
 *  can convert vector<vector<T>> to Matrix<T> implicitly;
 *  operators + * - are all usable
 *
 *  to solve a system of equations: Ax = b
 *  define Matrix<T> A;
 *  then x = A.solve(b) where x and b are vectors
 *  free variables are all arbitrarily set to 0
 *  returns an empty vector if no solution
 */
template <class T> struct Matrix {
    // /* remove if EPS is defined elsewhere
    const T EPS = 1e-15;
    Matrix<T>& operator = (const Matrix<T>& other) { a = other.a; return *this; }
    // */
    int rows, cols;
    vector<vector<T>> a;
    Matrix(int r, int c) {
        rows = r;
		cols = c;
        a.resize(r, vector<T>(c,0));
    }
    vector<T>& operator [] (unsigned int i) {
        return a[i];
    }
    vector<T> solve(vector<T> goal) {
        vector<int> piv, first; // pivot and first
        vector<T> res; // the solution
        for (int i = 0; i < rows; i++) {
            first.push_back(cols);
            for (int j = 0; j < cols; j++) {
                if (a[i][j] != 0 && first[i] == cols)
                    first[i] = j;
            }
        }
        for (int i = 0; i < rows; i++) {
            piv.push_back(0);
            for (int j = 0; j < rows; j++) {
                if (i == 0 || first[piv[i-1]] < first[j]) {
                    piv[i] = j;
                    break;
                }
            }
            for (int j = piv[i]+1; j < rows; j++)
                if (i == 0 || first[piv[i-1]] < first[j])
                    if (first[j] < first[piv[i]])
                        piv[i] = j;
            if (first[piv[i]] == cols) {
                piv.pop_back();
                break;
            }
            for (int j = 0; j < rows; j++) {
                if (j != piv[i] && first[j] == first[piv[i]]) { 
                    bool zero = true;
                    T factor = a[j][first[piv[i]]] / a[piv[i]][first[piv[i]]];
                    goal[j] -= factor * goal[piv[i]];
                    for (int k = first[piv[i]]; k < cols; k++) {
                        a[j][k] -= factor * a[piv[i]][k];
                        if (abs(a[j][k]) <= EPS)
                            a[j][k] = 0;
                        if (a[j][k] == 0 && zero)
                            first[j]++;
                        else if (a[j][k] != 0)
                            zero = false;
                    }
                    if (zero && goal[j] != 0)
                        return res;
                }
            }
        }
        res.resize(cols, 0);
        int pos = cols-1;
        while (piv.empty() == false) {
            int curr = piv.back();
            piv.pop_back();
            while (first[curr] < pos) 
                pos--;
            res[pos] = goal[curr];
            for (int j = pos+1; j < cols; j++)
                res[pos] -= res[j] * a[curr][j];
            res[pos] /= a[curr][pos];
            pos--;
        }
        return res;
    }
};

struct Edge {
	int a, b;
	Edge(int x=0, int y=0) {
		if (x < y) a = x, b = y;
		else a = y, b = x;
	}
	bool operator < (const Edge& other) const {
		if (a != other.a) return a < other.a;
		else return b < other.b;
	}
};

struct Graph {
	int vertices;
	vector<vector<pair<int,int>>> g;
	Graph (int n) {
		g.resize(n);
		vertices = n;
	}
	void add_edge(int a, int b, int c) {
		g[a].push_back(pii(b,c));
		g[b].push_back(pii(a,c));
	}
	int dijkstra(int s, int t) {
		struct Node {
			int id;
			int dist;
			Node(int id=-1, int d=INF):
				id(id), dist(d) {}
			bool operator < (const Node& other) const {
				return dist > other.dist;
			}
		};
		int dist[vertices];
		memset(dist, INF, sizeof(dist));
		priority_queue<Node> next;
		next.push(Node(s, 0));
		while (!next.empty()) {
			Node cur = next.top();
			next.pop();
			if (cur.id == t) return cur.dist;
			if (dist[cur.id] == INF) {
				dist[cur.id] = cur.dist;
				for (const auto& e : g[cur.id]) {
					if (dist[e.first] == INF)
						next.push(Node(e.first, cur.dist + e.second));
				}
			}
		}
		return -1;
	}
};

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);

	map<Edge,int> idx;
	vector<Edge> edges;
	int ecnt = 0;
	int path[1000];
	int d, p;
	int N, A, R, T;
	//cin >> N >> A >> R >> T;
	read(N); read(A); read(R); read(T);
	int rawmat[T][N*N];
	memset(rawmat, 0, sizeof(rawmat));
	vector<Int> goal(T, 0);
	for (int i = 0; i < T; i++) {
		//cin >> d >> p;
		read(d); read(p);
		for (int j = 0; j < p; j++) {
			//cin >> path[j];
			read(path[j]);
			if (j) {
				Edge e = Edge(min(path[j-1], path[j]), max(path[j-1], path[j]));
				if (!idx.count(e)) {
					idx[e] = ecnt++;
					edges.push_back(e);
				}
				assert(idx[e] < N*N);
				rawmat[i][idx[e]] += 1;
			}
		}
		goal[i] = d;
	}
	Matrix<Int> mat(T, ecnt);
	for (int i = 0; i < T; i++)
		for (int j = 0; j < ecnt; j++)
			mat[i][j] = Int(rawmat[i][j]);
	vector<Int> ans = mat.solve(goal);
	Graph graph(N+1);
	for (int i = 0; i < ecnt; i++) {
		graph.add_edge(edges[i].a, edges[i].b, ans[i]);
	}
	cout << graph.dijkstra(A, R) << nl;

	return 0;
}
