#include <bits/stdc++.h>
using namespace std;
#define _USE_MAdoubleH_DEFINES

//#define DEBUG
//#define USE_MAGIC_IO

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

// 178 lines, 114 lines without rref
/**
 * USAGE:
 *   to declare an nxn diagonal matrix: Matrix<T> mat(n,d);
 *  can convert vector<vector<T>> to Matrix<T> implicitly;
 *  operators + * - are all usable
 *
 *  to solve a system of equations: Ax = b
 *  define Matrix<T> A;
 *  then x = A.solve(b) where x and b are vectors
 *  free variables are all arbitrarily set to 0
 *  returns an empty vector if no solution
 */
template <class T>
struct Matrix {
  const T epsilon = 1e-15;
  int rows;
  vector<vector<T>> a;
  Matrix(int r, int v=0) {
    rows = r;
    a.resize(r, vector<T>(r));
    if (v) for (int i = 0; i < r; i++)
      a[i][i] = v;
  }
  Matrix(const vector<vector<T>>& v) {
    rows = v.size(); 
    a = v;
  }
  vector<T>& operator [] (unsigned int i) {
    return a[i];
  }
  int size() {
    return rows;
  }
  // this operator is needed or g++ will be 
  // "confused by earlier errors" and "bail out"
  Matrix<T>& operator = (const Matrix<T>& other) {
    a = other.a;
    return (*this);
  }
  bool operator == (const Matrix& other) const {
    return a == other.a;
  }
  Matrix<T>& operator *= (const Matrix<T>& other) {
    return (*this) = (*this) * (other);
  }
  Matrix<T>& operator += (const Matrix<T>& other) {
    for (int i = 0; i < rows; i++)
      for (int j = 0; j < rows; j++) 
        a[i][j] += other.a[i][j];
    return (*this);
  }
  Matrix<T>& operator -= (const Matrix<T>& other) {
    for (int i = 0; i < rows; i++)
      for (int j = 0; j < rows; j++) 
        a[i][j] -= other.a[i][j];
    return (*this);
  }
  Matrix<T> operator * (const Matrix<T>& other) {
    Matrix<T> res(rows);
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < rows; j++) {
        res[i][j] = 0;
        for (int k = 0; k < rows; k++) 
          res[i][j] += a[i][k] * other.a[k][j];
      }
    }
    return res;
  }
  vector<T> operator * (const vector<T>& v) {
    vector<T> res(rows);
    for (int i = 0; i < rows; i++) {
      res[i] = 0;
      for (int j = 0; j < rows; j++)
        res[i] += a[i][j] * v[j];
    }
    return res;
  }
  Matrix<T> operator + (const Matrix<T>& other) {
    Matrix<T> res(rows);
    for (int i = 0; i < rows; i++)
      for (int j = 0; j < rows; j++) 
        res[i][j] = a[i][j] + other.a[i][j];
    return res;
  }
  Matrix<T> operator - (const Matrix<T>& other) {
    Matrix<T> res(rows);
    for (int i = 0; i < rows; i++)
      for (int j = 0; j < rows; j++) 
        res[i][j] = a[i][j] - other.a[i][j];
    return res;
  }
  Matrix<T> operator - () {
    Matrix<T> res(rows);
    for (int i = 0; i < rows; i++)
      for (int j = 0; j < rows; j++) 
        res[i][j] = -a[i][j];
    return res;
  }
  void print() {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < rows; j++)
        cout << a[i][j] << " ";
      cout << nl;
    }
  }
  void print(const vector<T>& v) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < rows; j++)
        cout << a[i][j] << " ";
      cout << "| " << v[i] << nl;
    }
  }
//};
  vector<T> solve(vector<T> goal) {
    vector<int> pivot;
    vector<T> res;
    Matrix<T> reduced(rows);
    vector<int> first;
    for (int i = 0; i < rows; i++) {
      first.push_back(rows);
      for (int j = 0; j < rows; j++) {
        reduced[i][j] = a[i][j];
        if (a[i][j] != 0 && first[i] == rows)
          first[i] = j;
      }
    }
    for (int i = 0; i < rows; i++) {
      pivot.push_back(0);
      for (int j = 0; j < rows; j++) {
        if (i == 0 || first[pivot[i-1]] < first[j]) {
          pivot[i] = j;
          break;
        }
      }
      for (int j = pivot[i]+1; j < rows; j++)
        if (i == 0 || first[pivot[i-1]] < first[j])
          if (first[j] < first[pivot[i]])
            pivot[i] = j;
      if (first[pivot[i]] == rows) {
        pivot.pop_back();
        break;
      }
      for (int j = 0; j < rows; j++) {
        if (j != pivot[i] && first[j] == first[pivot[i]]) { 
          bool allzero = true;
          T factor = reduced[j][first[pivot[i]]] / reduced[pivot[i]][first[pivot[i]]];
          goal[j] -= factor * goal[pivot[i]];
          for (int k = first[pivot[i]]; k < rows; k++) {
            reduced[j][k] -= factor * reduced[pivot[i]][k];
            if (abs(reduced[j][k]) <= epsilon)
              reduced[j][k] = 0;
            if (reduced[j][k] == 0 && allzero)
              first[j]++;
            else if (reduced[j][k] != 0)
              allzero = false;
          }
          if (allzero && goal[j] != 0)
            return res;
        }
      }
    }
    res.resize(rows, 0);
    int pos = rows-1;
    while (pivot.empty() == false) {
      int curr = pivot.back();
      pivot.pop_back();
      while (first[curr] < pos) 
        pos--;
      res[pos] = goal[curr];
      for (int j = pos+1; j < rows; j++)
        res[pos] -= res[j] * reduced[curr][j];
      res[pos] /= reduced[curr][pos];
      pos--;
    }
    return res;
  }
};

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  double p;
  int n, tmp;
  cin >> n;
  int h = n*(n+1)/2;
  vector<double> goal(h);
  Matrix<double> holes(h, 1);
  vector<double> value(h);

  vector<int> row_start(n+40);
  vector<int> row_of(h+200);
  row_start[0] = -1;
  int cr = 0;
  for (int i = 0; i < h+200; i++) {
    if (i == cr*(cr+1)/2) {
      cr++;
      row_start[cr] = i;
    }
    row_of[i] = cr;
  }
  
  for (int i = 0; i < h; i++)
    cin >> value[i];
  for (int i = 0; i < h; i++) {
    // nw
    cin >> p;
    tmp = row_start[row_of[i]-1]-1 + i - row_start[row_of[i]];
    if (row_of[i] > 1 && row_start[row_of[i]-1] <= tmp && tmp < row_start[row_of[i]]) {
      holes[i][tmp] -= p;
    }
    // ne
    cin >> p;
    tmp = row_start[row_of[i]-1] + i - row_start[row_of[i]];
    if (row_of[i] > 1 && row_start[row_of[i]-1] <= tmp && tmp < row_start[row_of[i]]) {
      holes[i][tmp] -= p;
    }
    // sw
    cin >> p;
    tmp = row_start[row_of[i]+1] + i - row_start[row_of[i]];
    if (row_of[i] < n && row_start[row_of[i]+1] <= tmp && tmp < row_start[row_of[i]+2]) {
      holes[i][tmp] -= p;
    }
    // se
    cin >> p;
    tmp = row_start[row_of[i]+1]+1 + i - row_start[row_of[i]];
    if (row_of[i] < n && row_start[row_of[i]+1] <= tmp && tmp < row_start[row_of[i]+2]) {
      holes[i][tmp] -= p;
    }
    // in
    cin >> p;
    goal[i] = p * value[i];
  }

  vector<double> ans = holes.solve(goal);
  cout << fixed << setprecision(10) << ans[0] << endl;

  return 0;
}
