#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

//*!
template <class Node, class T>
struct SegmentTree {
    int n;
    vector<Node> segt;
    SegmentTree(int len) {
        n = 1 << (32 - __builtin_clz(len-1));
        segt.resize(2*n);
    }
    void set(int i, const T& v) {
        segt[n+i] = Node(v);
    }
    void build() {
        for (int i = n-1; i > 0; i--) {
            segt[i].pull(segt[2*i], segt[2*i+1]);
        }
    }
    void update(int l, int r, const T& v) {
        update(l, r, v, 1, 0, n-1);
    }
    void update(int l, int r, const T& v, int i, int s, int e) {
        if (e < l || s > r) return;
        if (l <= s && e <= r && segt[i].put(v)) {
            segt[i].update(v, e-s+1);
            if (i<n) segt[i].pull(segt[2*i], segt[2*i+1]);
            return;
        }
        segt[i].push(segt[2*i], segt[2*i+1], e-s+1);
        int m = (s + e) / 2;
        update(l, r, v, 2*i, s, m);
        update(l, r, v, 2*i+1, m+1, e);
        segt[i].pull(segt[2*i], segt[2*i+1]);
    }
    Node query(int l, int r) {
        return query(l, r, 1, 0, n-1);
    }
    Node query(int l, int r, int i, int s, int e) {
        if (e < l || s > r) return Node();
        if (l <= s && e <= r && segt[i].get()) {
            return segt[i];
        }
        segt[i].push(segt[2*i], segt[2*i+1], e-s+1);
        int m = (s + e) / 2;
        return Node().pull(query(l, r, 2*i, s, m), query(l, r, 2*i+1, m+1, e));
    }
};
//*/

////////////////////////////////////////////////////////////////////////
// t mod K Rectangle Union -- O(knlog(n)) Uses the SegmentTree
// Finds the area of the union of axis-aligned rectangles
// Allows storing of prefix areas up to specific points, for prefix sums
// USAGE:
//  1. add_rect(x1,y1,x2,y2); with x1<x2 and y1<y2
//   This defines the rectangle [x1,x2] x [y1,y2]
//  2. add_query(l,r); with l<r. Query is for the area with l<x<r
//  3. solve(); to compute the areas, should only be called ONCE
//  4. query(t,l,r); to query t mod K area
//*!
template<int K> struct ModRectangleUnion {
    struct Segment {
        int a, b, v;
        Segment(): v(0) {}
        Segment(int a, int b, int v): a(a), b(b), v(v) {}
    };
    map<ll,vector<Segment>> segs;
    map<ll,int> cmpr;
    vector<ll> decmp;
    unordered_map<ll,ll> area[K];

    void add_rect(ll a, ll b, ll x, ll y) {
        segs[a].push_back(Segment(b,y,1));
        segs[x].push_back(Segment(b,y,-1));
        cmpr[b]; cmpr[y];
    }
    void add_query(ll a, ll b) {
        segs[a].push_back(Segment());
        segs[b].push_back(Segment());
    }
    ll query(int t, ll a, ll b) {
        if (!area[t].count(a) || !area[t].count(b)) {
            throw runtime_error("query not added");
        }
        return area[t][b] - area[t][a];
    }

    struct Node {
        ll cover[K], tag, length;
        Node(ll l=0): tag(0), length(l) {
            memset(cover, 0, sizeof cover);
            if (K>1) cover[0] = length;
        }
        bool put(int v) { return true; }
        bool get() { return true; }
        void update(int v, int len) {
            tag += v;
            if (len==1) {
                memset(cover, 0, sizeof cover);
                if (K>1) cover[tag%K] = length;
                else cover[0] = (tag ? length : 0);
            }
        }
        void push(Node& left, Node& right, int len) {}
        Node pull(const Node& left, const Node& right) {
            length = left.length + right.length;
            if (K>1) {
                int s = tag%K;
                for (int i=0; i<K; i++) {
                    cover[(i+s)%K] = left.cover[i] + right.cover[i];
                }
            } else {
                cover[0] = (tag ? length : left.cover[0] + right.cover[0]);
            }
            return *this;
        }
    };

    void solve() {
        int cnt = 0;
        vector<ll> len;
        for (auto it = cmpr.begin(); it != cmpr.end(); it++) {
            if (next(it) == cmpr.end()) len.push_back(0);
            else len.push_back(next(it)->first - it->first);
            decmp.push_back(it->first);
            it->second = cnt++;
        }
        SegmentTree<Node,int> segt(cnt);
        for (int i=0; i<cnt; i++) {
            segt.set(i, len[i]);
        }
        segt.build();

        ll cur[K]; memset(cur, 0, sizeof cur);
        ll pre = 0x5F3759DF;
        for (const pair<int,vector<Segment>>& it : segs) {
            for (int i=0; i<K; i++) {
                cur[i] += segt.segt[1].cover[i] * (it.first - pre);
                for (const Segment& s : it.second) {
                    if (s.v == 0) area[i][it.first] = cur[i];
                    else segt.update(cmpr[s.a], cmpr[s.b]-1, s.v);
                }
            }
            pre = it.first;
        }
    }
};
//*/

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n;
  cin >> n;

  ModRectangleUnion<2> ru;
  for (int i=0; i<n; i++) {
    int a, b, x, y;
    cin >> a >> b >> x >> y;
    ru.add_rect(a,b,x,y);
  }
  ru.add_query(-1, 1e9+2);
  ru.solve();
  cout << ru.query(1, -1, 1e9+2) << nl;

  return 0;
}
