#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

struct Matrix {
	vector<vector<ll>> m;
	ll mod;

	Matrix() {
		mod = 1e9+7;
	}
	Matrix(int row) {
		resize(row);
		mod = 1e9+7;
		init();
	}
	Matrix(int row, ll mod, ll diag=1) {
		resize(row);
		set_mod(mod);
		init(diag);
	}
	void init(ll v = 1) {
		for (int i = 0; i < m.size(); i++)
			for (int j = 0; j < m[0].size(); j++)	
				m[i][j] = ((i==j)*v) % mod;
	}
	void resize(int row) {
		m.resize(row);
		for (int i = 0; i < row; i++)
			m[i].resize(row);
	}
	void set_mod(ll v) {
		mod = v;
	}
	void set_val(int i, int j, ll v) {
		m[i][j] = v;
	}

	vector<ll>& operator [] (int i) {
		return m[i];
	}
	void operator = (const Matrix& other) {
		for (int i = 0; i < m.size(); i++)
			for (int j = 0; j < m[0].size(); j++)
				this->m[i][j] = other.m[i][j];
	}
	Matrix operator * (const Matrix& other) {
		Matrix temp(m.size(), mod);
		for (int i = 0; i < m.size(); i++) {
			for (int j = 0; j < m[0].size(); j++) {
				temp[i][j] = 0;
				for (int k = 0; k < m.size(); k++)
					temp[i][j] = (temp[i][j] + (this->m[i][k]*other.m[k][j]) % mod) % mod;
			}
		}
		return temp;
	}
	Matrix operator * (ll c) {
		Matrix temp(m.size(), mod);
		for (int i = 0; i < m.size(); i++)
			for (int j = 0; j < m[0].size(); j++)
				temp[i][j] = (m[i][j]*c) % mod;
		return temp;
	}
	void operator *= (const Matrix& other) {
		(*this) = (*this) * (other);
	}
	void operator *= (ll c) {
		for (int i = 0; i < m.size(); i++)
			for (int j = 0; j < m[0].size(); j++)
				m[i][j] = (m[i][j]*c) % mod;
	}
	Matrix operator + (const Matrix& other) {
		Matrix temp(m.size(), mod);
		for (int i = 0; i < m.size(); i++)
			for (int j = 0; j < m[0].size(); j++) 
				temp[i][j] = (m[i][j] + other.m[i][j]) % mod;
		return temp;
	}
	void operator += (const Matrix& other) {
		for (int i = 0; i < m.size(); i++)
			for (int j = 0; j < m[0].size(); j++) 
				m[i][j] = (m[i][j] + other.m[i][j]) % mod;
	}
		
	void square() {
		(*this) *= (*this);
	}

	void print() {
		cerr << "matrix: " << endl;
		for (int i = 0; i < m.size(); i++) {
			for (int j = 0; j < m[0].size(); j++) 
				cerr << m[i][j] << " ";
			cerr << endl;
		}
		cerr << "mod: " << mod << endl;
	}
};

int main() {
	Matrix ans(2, 1e6);
	Matrix mat(2, 1e6);
	ll n, K, L;
	cin >> n >> K >> L;
	n = n/5-1;
	mat[0][0] = K % mat.mod;
	mat[0][1] = L % mat.mod;
	mat[1][0] = 1;
	mat[1][1] = 0;
	for (ll bit = 1LL; bit <= n; bit = bit<<1) {
		if (bit & n)
			ans *= mat;
		mat.square();
	}
	int temp = ((ans[0][0]*(K % ans.mod))%ans.mod + ans[0][1]) % ans.mod;
	vector<int> num;
	while (num.size() < 6) {
		num.push_back(temp % 10);
		temp /= 10;
	}
	for (int i = 5; i >= 0; i--)
		cout << num[i];
	cout << endl;

	return 0;
}
