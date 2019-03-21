//https://www.acmicpc.net/problem/11375

#include <stdio.h>
#include <algorithm>
#include <vector>

class BPM{
public:
	int n, m;
	int* A;
	int* B;
	bool* check;
	std::vector<int>* vec;

	BPM(int n, int m) {
		this->n = n;
		this->m = m;
		A = new int[n + 1];
		B = new int[m + 1];
		check = new bool[n + 1];
		vec = new std::vector<int>[n + 1];
	}

	~BPM(void) {
		delete[] A;
		delete[] B;
		delete[] vec;
		delete[] check;
	}

	void add_edge(int x, int y) {
		vec[x].push_back(y);
	}

	bool dfs(int now) {
		if (check[now]) return false;
		check[now] = true;
		for (int chd : vec[now]) {
			if (B[chd] == 0 || dfs(B[chd])) {
				A[now] = chd;
				B[chd] = now;
				return true;
			}
		}
		return false;
	}

	int max_bpm(void) {
		int ret = 0;
		for (int i = 1; i <= n; i++) A[i] = 0;
		for (int i = 1; i <= m; i++) B[i] = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) check[j] = false;
			if (dfs(i)) ret++;
		}
		return ret;
	}
};

int main(void) {
	int n, m, x;
	scanf("%d %d", &n, &m);
	BPM bpm(n, m);
	for (int i = 1; i <= n; i++) {
		int j;
		scanf("%d", &j);
		for (; j--;) {
			scanf("%d", &x);
			bpm.add_edge(i, x);
		}
	}
	printf("%d\n", bpm.max_bpm());
	return false;
}