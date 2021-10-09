#pragma GCC optimize("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
const ld BS = 1e-6;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

inline char get(void) {
  static char buf[100000], *S = buf, *T = buf;
  if (S == T) {
    T = (S = buf) + fread(buf, 1, 100000, stdin);
    if (S == T) return EOF;
  }
  return *S++;
}
inline void read(int& x) {
  static char c; x = 0; int sgn = 0;
  for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
  for (; c >= '0' && c <= '9'; c = get()) x = x*10 + c-'0';
  if (sgn) x = -x;
}

//typedef complex<ld> pt;

template<class T> struct cplx {
  T x, y; cplx() { x=0.0; y=0.0; }
  cplx(T nx, T ny=0) { x=nx; y=ny; }
  cplx operator + (const cplx& c) const {return { x+c.x, y+c.y }; }
  cplx operator - (const cplx& c) const {return { x-c.x, y-c.y }; }
};
typedef cplx<ld> pt;

ld abs(const pt& a) { return sqrt(a.x*a.x + a.y*a.y); }

const int N = 15;
vector<pt> p[N];
ld adj[N][N];
int minv[N], maxv[N], bot[N];
// anchor at (0,0)

//ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
ld cp(const pt& a, const pt& b) { return a.x*b.y - b.x*a.y; }
int sgn(const ld& x) { return abs(x) < EPS ? 0 : x < 0 ? -1 : 1; }
bool cmp_lex(const pt& a, const pt& b) {
  return a.x<b.x-EPS || (a.x<b.x+EPS && a.y<b.y-EPS);
}
bool seg_x_seg(pt a1, pt a2, pt b1, pt b2) {
  ld za = abs(a2-a1), zb = abs(b2-b1); za=za>EPS?1/za:0; zb=zb>EPS?1/zb:0;
  int s1 = sgn(cp(a2-a1, b1-a1)*za); int s2 = sgn(cp(a2-a1, b2-a1)*za);
  int s3 = sgn(cp(b2-b1, a1-b1)*zb); int s4 = sgn(cp(b2-b1, a2-b1)*zb);
  if (!s1 && !s2 && !s3) {
    if (cmp_lex(a2, a1)) swap(a1, a2);
    if (cmp_lex(b2, b1)) swap(b1, b2);
    return !cmp_lex(b2, a1) && !cmp_lex(a2, b1);
  } return s1*s2 <= 0 && s3*s4 <= 0;
}

ld mem[N][1<<N];

int n;

ld dp(int u, int bm) {
  if (mem[u][bm]<0.5) return mem[u][bm];
  if (bm == (1<<n)-1) return 0;
  //cerr << u << " " << bitset<N>(bm) <<endl;
  ld ans = INFLL;
  for(int v=0;v<n;v++) {
    if (bm>>v&1) continue;
    ans = min(ans, dp(v, (1<<v)|bm)+adj[u][v]);
  }
  return mem[u][bm] = ans;
}

bool intersect(int a, int b, ld d) {
  //cerr << "INT " << a << " " << b << " w/ dist " << d << " -> size " << p[a].size() << " " << p[b].size() << endl;
  int pa = 1;
  int pb = p[b].size()-1;

  while (p[a][pa].y != p[a][pa+1].y && p[b][pb].y != p[b][pb-1].y) {
    //cerr << "try " << pa << " vs " << pb << endl;
    //cerr << p[a][pa] << " " << p[a][pa+1] << " " << p[b][pb] << " " << p[b][pb-1] << endl;
    //cerr << endl; assert(pa < 5);
    if (seg_x_seg(p[a][pa], p[a][pa+1], p[b][pb] + pt(d,0), p[b][pb-1] + pt(d,0))) {
      return true;
    }
    if (p[a][pa+1].y > p[b][pb-1].y) {
      pb--;
    } else {
      pa++;
    }
  }

  return false;
}

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(3);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int k, x, y;
  //cin >> n;
  read(n);

  ld sum = 0;
  for (int i=0; i<n; i++) {
    minv[i] = INF;
    maxv[i] = -INF;

    //cin >> k;
    read(k);
    for (int j=0; j<k; j++) {
      //cin >> x >> y;
      read(x); read(y);
      p[i].push_back(pt(x,y));
      if (j == 1) bot[i] = x;
      minv[i] = min(minv[i], x);
      maxv[i] = max(maxv[i], x);
    }
    sum += maxv[i]-minv[i];
    p[i].push_back(pt(0,0));
  }

  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      if (i != j) {
        ld left, right;
        right = maxv[i] - minv[j];
        left = bot[i];
        ld mid = (left+right)/2;

        while (right - left > BS) {
          mid = (left+right)/2;
          if (intersect(i, j, mid)) {
            left = mid;
          } else {
            right = mid;
          }
        }

        adj[i][j] = mid - (maxv[i] - minv[j]);
        //cerr << i << "->" << j << " : " << adj[i][j] << "  where mid " << mid << endl;
      }
    }
  }

  ld ans = INFLL;
  for(int i=0;i<n;i++) {
    for(int bm=0;bm<(1<<n);bm++) {
      mem[i][bm] = 1;
    }
  }
  for(int i=0;i<n;i++) {
    ans = min(ans, dp(i, 1<<i));
  }
  cout << sum+ans <<endl;

  return 0;
}
