#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
pt line_inter(const pt& a, const pt& b, const pt& c, const pt& d) {
    return a + cp(c-a, d-c) / cp(b-a, d-c) * (b-a);
}

const ld g = 9.80665;

const int L = 21;
const int N = L*L;
int height[L][L];
int dist[N][N];

struct Parabola {
    ld a, b, c;
    ld eval(ld x) const {
        return a*x*x + b*x + c;
    }
};

ld w, v;
int n, m;

Parabola get_parabola(ld d, ld h1, ld h2) {
    ld dh = h1 - h2;
    ld left, right, vx, vy;
    left = 0;
    right = v;
    while (right - left > EPS) {
        vx = (left+right)/2;
        vy = sqrt(v*v-vx*vx);
        if (dh + vy*d/vx - 0.5*g*d*d/(vx*vx) > 0) {
            right = vx;
        } else {
            left = vx;
        }
    }
    cerr << "vx: " << vx << "  vy: " << vy << endl;
    return { -g/(2*vx*vx), vy/vx, h1 };
}

// use coordinates as in array
bool valid(int first, int second) {
    int ai = first / m;
    int aj = first % m;
    int bi = second / m;
    int bj = second % m;

    pt start = pt(w*ai, w*aj);
    pt end = pt(w*bi, w*bj);

    // get parabola
    cerr << endl;
    cerr << "get parabola: " << pt(ai,aj) << " " << pt(bi,bj) << " --> " << start << " " << end << endl;
    Parabola func = get_parabola(abs(start-end), height[ai][aj], height[bi][bj]);

    // check x-lines
    for (int i = min(ai,bi); i < max(ai,bi); i++) {
        pt it = line_inter(start, end, pt(w/2+i*w, 0), pt(w/2+i*w, 1));
        ld id = (it.imag()+w/2)/w;
        int j = floor(id+EPS/2);
        ld val = 0;
        if (abs(id-j) < EPS) {
            val = max(max(height[i][j], height[i+1][j]), 
                    max(height[i][j-1], height[i+1][j-1]));
        } else {
            val = max(height[i][j], height[i+1][j]);
        }
        if (val > func.eval(abs(it-start))) return false;
    }

    // check y-lines
    for (int j = min(aj,bj); j < max(aj,bj); j++) {
        pt it = line_inter(start, end, pt(0, w/2+j*w), pt(1, w/2+j*w));
        ld id = (it.real()+w/2)/w;
        int i = floor(id+EPS/2);
        ld val = 0;
        if (abs(id-j) < EPS) {
            val = max(max(height[i][j], height[i][j+1]), 
                    max(height[i-1][j], height[i-1][j+1]));
        } else {
            val = max(height[i][j], height[i][j+1]);
        }
        if (val > func.eval(abs(it-start))) return false;
    }

    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(10);

    int x, y;
    cin >> n >> m >> w >> v >> x >> y;
    swap(n, m); swap(x, y);

    // source
    int source = (x-1)*m + (y-1);

    // get input
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> height[i][j];
        }
    }

    // get jumps
    for (int i = 0; i < n*m; i++) {
        for (int j = 0; j < n*m; j++) {
            if (i == j) dist[i][j] = 0;
            else dist[i][j] = valid(i, j) ? 1 : 9001;
        }
    }

    // floyd warshall
    for (int k = 0; k < n*m; k++) {
        for (int i = 0; i < n*m; i++) {
            for (int j = 0; j < n*m; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    // output
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (dist[source][i*m+j] > 9000) cout << "X ";
            else cout << dist[source][i*m+j] << " ";
        }
        cout << nl;
    }

    return 0;
}

