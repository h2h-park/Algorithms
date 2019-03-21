//https://www.acmicpc.net/problem/1717
#include <stdio.h>

class Disjoint {
public:
	int n;
	int* par;

	Disjoint(int n) {
		this->n = n;
		par = new int[n + 1];

		for (int i = 1; i <= n; i++) par[i] = i;
	}

	~Disjoint(void) {
		delete[] par;
	}

	int find(int p) {
		return (par[p] == p) ? p : (par[p] = find(par[p]));
	}

	void uni(int x, int y) {
		int xr = find(x), yr = find(y);
		if (xr != yr) par[xr] = yr;
	}
};

int main(void) {
	int n, m;
	int a, b, c;
	scanf("%d %d", &n, &m);
	Disjoint dj(n);
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d", &a, &b, &c);
		if (a == 0) dj.uni(b, c);
		else puts((dj.find(b) == dj.find(c)) ? "YES" : "NO");
	}
	return false;
}