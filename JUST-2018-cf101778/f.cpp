#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define USE_MAGIC_IO

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
// END MAGIC IO

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

const int A = 500;
const int N = 101;
int grid[N][N];
int pref[A+2][N][N];

void build(int n, int m) {
  for (int a = 1; a <= A; a++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        pref[a][i][j] = pref[a][i-1][j] + pref[a][i][j-1] - pref[a][i-1][j-1];
        if (grid[i][j] <= a) pref[a][i][j] += 1;
      }
    }
  }
}

int query(int a, int b, int c, int d, int m) {
  return pref[m][c][d] - pref[m][c][b-1] - pref[m][a-1][d] + pref[m][a-1][b-1];
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int T;
  //cin >> T;
  read(T);
  while (T--) {
    int n, m, q;
    //cin >> n >> m >> q;
    read(n); read(m); read(q);

    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        //cin >> grid[i][j];
        read(grid[i][j]);
      }
    }
    build(n, m);

    int a, b, c, d;
    for (int i = 0; i < q; i++) {
      //cin >> a >> b >> c >> d;
      read(a); read(b); read(c); read(d);
      int area = (c-a+1)*(d-b+1);
      int median = (area+1)/2;
      //cerr << "area: " << area << "  median: " << median << nl;

      int left, right, mid;
      left = 1;
      right = A;
      while (left <= right) {
        mid = (left+right)/2;
        int small = query(a,b,c,d,mid-1);
        int large = query(a,b,c,d,mid);

        //cerr << mid << ": " << small << " " << large << endl;
        if (small < median && median <= large) break;
        else if (small >= median) right = mid-1;
        else left = mid+1;
      }

      cout << mid << nl;
    }
  }

  return 0;
}
