#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(clock() + time(nullptr)); }

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
    os << "(" << v.first << "," << v.second << ")"; return os;
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
    for (const T& it : v) os << it << " "; return os;
}

template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
    os << "{ "; for (const T& it : v) os << it << " "; os << "}"; return os;
}

template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
    os << "{ ";
    for (const pair<T,U>& it : v) os << "{" << it.first << "," << it.second << "} "; 
    os << "}"; return os;
}

template <class T>
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9+7;
const ld EPS = 1e-9;

struct Query {
    int t;
    ll x, y;
    Query() {}
    Query(int t, int x, int y): t(t), x(x), y(y) {}
    int left() { return x - y; }
    int right() { return x + y; }
};

unordered_map<int,int> remap;
vector<Query> instr;

const int N = 1<<20;
struct SegTree {
    int n;
    unordered_set<int> nodes[2*N];
    SegTree() { n = N; }

    void insert(int l, int r, int id) {
        for (l += n, r += n+1 ; l < r; l >>= 1, r >>= 1) {
            if (l & 1) nodes[l++].insert(id);
            if (r & 1) nodes[--r].insert(id);
        }
    }

    void remove(int l, int r, int id) {
        for (l += n, r += n+1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) nodes[l++].erase(id);
            if (r & 1) nodes[--r].erase(id);
        }
    }

    int query(int x, int y) {
    ll xpos = x;
    x = remap[x];
        for (x += n; x > 0; x >>= 1) {
            for (int id : nodes[x]) {
                if (sqr(instr[id].x - xpos) + sqr(instr[id].y - y) < sqr(instr[id].y)) {
                    remove(remap[instr[id].left()], remap[instr[id].right()], id);
                    return id+1;
                }
            }
        }
        return -1;
    }
};

SegTree segtree;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    set<int> coords;

    int n;
    cin >> n;

    int t, x, y;
    for (int i = 0; i < n; i++) {
        cin >> t >> x >> y;
        instr.push_back(Query(t, x, y));
        coords.insert(x);
        if (t == 1) {
            coords.insert(x + y);
            coords.insert(x - y);
        }
    }

    int cnum = 1;
    for (int it : coords) {
        remap[it] = cnum;
        cnum++;
    }

    for (int i = 0; i < n; i++) {
        if (instr[i].t == 1) {
            // add target
            segtree.insert(remap[instr[i].left()], remap[instr[i].right()], i);
        }
        else {
            // shoot
            cout << segtree.query(instr[i].x, instr[i].y) << nl;
        }
    }

    return 0;
}
