#include <bits/stdc++.h>
using namespace std;
#define rep(i,s,e) for(int i = s; i < (e); ++i)
using ll = long long; using ld = long double;
using pii = pair<int,int>; using pll = pair<ll, ll>;
using vi = vector<int>; using vl = vector<ll>;
const char nl = '\n';
const ll LINF = 0x3f3f3f3f3f3f3f3fll; const int INF = (int)LINF;
const ld EPS = 1e-9, PI = acos(-1.0L);
#define ff first
#define ss second
#define all(c) begin(c),end(c)
#define sz(c) int(c.size())
#define self (*this)

// Matrix stored in column major order
#if 0 // COLUMN MAJOR
#define IDX(i,j) (i+j*m)
#define ROW m,n
#define COL 1,m
#else // ROW MAJOR
#define IDX(i,j) (i*n+j)
#define ROW 1,n
#define COL n,m
#endif
template <class T>
struct matrix: public vector<T> {
  int m,n;
  matrix(int h, int w=1, const T& v=T()): vector<T>(h*w, v), m(h), n(w) {}
  T& operator()(int i, int j=0) { return self[IDX(i,j)]; }
  struct iter: public iterator<forward_iterator_tag, T> {
    T* p; int s; iter(T* a, int b): p(a), s(b) { }
    operator T*() { return p; }
    iter& operator++() { p+=s; return self; }
    iter operator++(int) { return ++iter(self); }
  };
  struct strider {
    T* p; int s, l;
    strider(T* a, int b, int c): p(a), s(b), l(c) { }
    iter begin() { return iter(p, s); }
    iter end() { return iter(p+s*l, s); }
    template <template<typename> class BinOp>
    void element_wise(strider&& o) {
      assert(l == o.l);
      transform(begin(),end(),o.begin(),begin(),BinOp<T>());
    }
    template <template<typename> class BinOp>
    void scalar(T&& x) {
      auto bop = BinOp<T>();
      auto op = [&](T& v) { return bop(v,x); };
      transform(begin(),end(),begin(), op);
    }
  };
  strider row(int i) {
    return strider(self.data() + IDX(i,0), ROW);
  }
  strider col(int i) {
    return strider(self.data() + IDX(0,i), COL);
  }
  strider operator()() { return strider(self.data(), 1, m*n); }
};

template <class T>
void print1(matrix<T>& m) {
  cout << "print1\n";
  rep(i,0,m.m) {
    cout << "| ";
    rep(j,0,m.n) {
      cout << m(i,j) << " ";
    }
    cout << nl;
  }
}

template <class T>
void print2(matrix<T>& m) {
  cout << "print2\n";
  rep(i,0,m.m) {
    cout << "| ";
    for(T v:m.row(i)) {
      cout << v << " ";
    }
    cout << nl;
  }
}

int main() { // Emily <3
  atexit([](){ cerr << "Time: " << (ld)clock() / CLOCKS_PER_SEC << nl; });
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  cout << setprecision(9);
  const int n = 5, m = 4;
  matrix<ld> A(m,n);
  fill(all(A), 3);
  print2(A);
  A.row(1).element_wise<plus>(A.row(3));
  A.col(3).element_wise<multiplies>(A.col(0));
  A().scalar<minus>(3);
  A().scalar<divides>(2);
  print2(A);
  return 0;
}

