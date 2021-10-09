#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

///* advent of code
typedef istringstream iss;
#define pb push_back
#define ins insert
#define multiset mset
#define getl(A) getline(cin, A)
//*/

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

typedef pii Edge;
typedef pt Point;

struct Query {
  int type;
  int a, b;
  Query(int d, int a, int b): type(d), a(a), b(b) {}
};

const int N = 2e5;

vector<ld> area;

struct DSU {
  int root[N+1];
  DSU() { 
    memset(root, -1, sizeof root);
  }

  int find(int i) {
    if (root[i] == -1) return i;
    else return root[i] = find(root[i]);
  }

  void link(int i, int j) {
    i = find(i);
    j = find(j);
    if (i == j) return;
    root[j] = i;
    area[i] += area[j];
  }
};

vector<Query> query;
vector<Point> points;
vector<int> graph[N+1];

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
ld dp(const pt& a, const pt& b) { return real(conj(a)*b); }

int base;
bool cmp (const int& i, const int& j) {
  return arg(points[i]-points[base]) < arg(points[j]-points[base]);
}

struct Tri {
  vector<int> i;
  Tri () {}
  Tri(int d, int e, int f) {
    i = {d, e, f};
    sort(i.begin(), i.end());
  }
  bool operator < (const Tri& other) const {
    return i < other.i;
  }
};



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(0);

  ll x, y;
  bool linear = true;
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> x >> y;
    points.push_back(Point(x, y));
    if (i > 0 && cp(points[0]-points[i], points[0]-points[i-1]) != 0) {
      linear = false;
    }
  }

  if (linear) {
    int d, a, b;
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
      cin >> d >> a >> b;
      if (d == 0) {
        cout << -1 << nl;
      }
    }
    return 0;
  }

  map<Edge, pii> neighbour;
  int d, a, b;
  int q;
  cin >> q;
  for (int i = 0; i < q; i++) {
    cin >> d >> a >> b;
    query.push_back(Query(d, a, b));
    if (d == 1) {
      graph[a].push_back(b);
      graph[b].push_back(a);
      neighbour[Edge(a,b)] = pii(0,0);
      neighbour[Edge(b,a)] = pii(0,0);
    }
  }

  area.push_back(INFLL);

  map<Tri, int> seen;
  for (int i = 0; i < n; i++) {
    base = i;
    sort(graph[i].begin(), graph[i].end(), cmp);
    int m = graph[i].size();
    for (int j = 0; j < m; j++) {
      ld ta = cp(points[graph[i][j]]-points[i], points[graph[i][(j+1)%m]]-points[i]);
      Tri curTri(i, graph[i][j], graph[i][(j+1)%m]);
      if (ta > 0) {
        if (!seen.count(curTri)) {
          int id = seen[curTri] = area.size();
          area.push_back(ta);
          neighbour[Edge(i,graph[i][j])].first = id;
          neighbour[Edge(graph[i][j], i)].second = id;
          neighbour[Edge(i,graph[i][(j+1)%m])].second = id;
          neighbour[Edge(graph[i][(j+1)%m], i)].first = id;
          neighbour[Edge(graph[i][j], graph[i][(j+1)%m])].first = id;
          neighbour[Edge(graph[i][(j+1)%m], graph[i][j])].second = id;
        }
      }
    }
  }

  DSU dsu;
  vector<ll> ans;
  for (int i = q-1; i >= 0; i--) {
    if (query[i].type == 0) {
      ans.push_back(area[dsu.find(neighbour[Edge(query[i].a, query[i].b)].first)]);
    }
    else {
      pii id = neighbour[Edge(query[i].a, query[i].b)];
      dsu.link(id.first, id.second);
    }
  }

  for (int i = ans.size()-1; i >= 0; i--) {
    if (ans[i] <= 0) for(;;);
    cout << ((ans[i]<INFLL) ? ans[i] : -1) << nl;
  }

  return 0;
}
