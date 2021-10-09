//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;

inline char get(void) {
  static char buf[100000], *S = buf, *T = buf;
  if (S == T) {
    T = (S = buf) + fread(buf, 1, 100000, stdin);
    if (S == T) return EOF;
  }
  return *S++;
}
template <typename T> inline void read(T &x) {
  static char c; x = 0;
  for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') ;
  for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
}

char buf1 [220 << 20] alignas(16);
size_t buf_ind1 = sizeof buf1;
template<class T> struct small1 {
  typedef T value_type;
  small1() {}
  template<class U> small1(const U&) {}
  T* allocate(size_t n) {
    buf_ind1 -= n * sizeof(T);
    buf_ind1 &= 0 - alignof(T);
    return (T*)(buf1 + buf_ind1);
  }
  void deallocate(T*, size_t) {}
};

char buf2 [220 << 20] alignas(16);
size_t buf_ind2 = sizeof buf2;
template<class T> struct small2 {
  typedef T value_type;
  small2() {}
  template<class U> small2(const U&) {}
  T* allocate(size_t n) {
    buf_ind2 -= n * sizeof(T);
    buf_ind2 &= 0 - alignof(T);
    return (T*)(buf2 + buf_ind2);
  }
  void deallocate(T*, size_t) {}
};

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;

const int N = 1<<19;
const int M = N>>3;
vector<int, small2<int>> sm[2*N];
set<int, less<int>, small1<int>> st[M];

void reset(int n) {
  for(int i=1; i<=n; i++) {
    for(int x=i+N; x; x/=2) {
      if(x<M) {
        st[x].clear();
        sm[x].clear();
      } else {
        sm[x].clear();
      }
    }
  }
}

void insert(int x, int h) {
  x += N;
  for(;x;x/=2) {
    sm[x].push_back(h);
  }
}

int get(int x, int h) {
  int res = INF;
  if(x<M) {
    for(int v : sm[x]) st[x].insert(v);
    sm[x].clear();
    auto it = st[x].lower_bound(h);
    if(it != st[x].end()) res = min(res, *it - h);
    if(it != st[x].begin()) res = min(res, h - *prev(it));
  } else {
    for(int v : sm[x]) {
      res = min(res, abs(v-h));
    }
  }
  return res;
}

int query(int l, int r, int h) {
  int res = INF;
  for(l+=N, r+=N+1; l<r; l/=2, r/=2) {
    if(l&1) res = min(res, get(l++, h));
    if(r&1) res = min(res, get(--r, h));
  }
  return res;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int T;
  read(T);
  while(T--) {
    int n, m;
    read(n); read(m);
    reset(n);
    for(int i=0; i<m; i++) {
      int t;
      read(t);
      if(t == 0) {
        int x, h;
        read(x); read(h);
        insert(x, h);
      } else {
        int l, r, h;
        read(l); read(r); read(h);
        int res = query(l, r, h);
        if(res < INF) printf("%d\n", res);
        else printf("-1\n");
      }
    }
  }

  return 0;
}
