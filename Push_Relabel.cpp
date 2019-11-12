// https://www.acmicpc.net/problem/11378

#include <vector>


template <typename T>
class Push_Relabel {
public:
	int n;
	std::vector<int>* vec;
	T** f;
	T** c;
	int* h;
	T* e;

	Push_Relabel(int n) {
		this->n = n;
		vec = new std::vector<int>[n + 1];
		f = new T*[n + 1];
		c = new T*[n + 1];
		h = new int[n + 1];
		e = new T[n + 1];
		for (int i = 0; i <= n; i++) {
			h[i] = 0;
			e[i] = 0;
		}
		for (int i = 0; i <= n; i++) {
			f[i] = new T[n + 1];
			c[i] = new T[n + 1];
			for (int j = 0; j <= n; j++) f[i][j] = 0;
		}
	}

	~Push_Relabel(void) {
		delete[] vec;
		delete[] f;
		delete[] h;
		delete[] e;
	}

	void add_edge(int x, int y, T cost) {
		vec[x].push_back(y);
		vec[y].push_back(x);
		c[x][y] = cost;
		c[y][x] = 0;
	}

	int overflow(void) {
		for (int i = 0; i <= n; i++) {
			if (e[i] > 0) return i;
		}
		return -1;
	}

	bool push(int u) {
		for (int v : vec[u]) {
			if (f[u][v] == c[u][v]) continue; // saturated
			if (h[u] > h[v]) {
				T flow = (c[u][v] - f[u][v] > e[u]) ? e[u] : c[u][v] - f[u][v];
				e[u] -= flow;
				e[v] += flow;
				f[u][v] += flow;
				if (c[v][u] == 0) {
					c[v][u] = flow;
					f[v][u] = 0;
				}
				else f[v][u] -= flow;
				return true;
			}
		}
		return false;
	}

	void relabel(int u) {
		int mn = 1 << 30;
		for (int v : vec[u]) {
			if (f[u][v] == c[u][v]) continue;
			if (h[v] < mn) mn = h[v];
		}
		h[u] = mn + 1;
	}

	T max_flow(int src, int snk) {
		h[src] = n + 1;
		for (int v : vec[src]) {
			f[src][v] = c[src][v];
			f[v][src] = -c[src][v];
			e[v] = c[src][v];
			e[src] -= c[src][v];
		}

		for (; overflow() != -1;) { 
			int u = overflow();
			if (!push(u)) relabel(u);
		}
		return e[snk];
	}
};

int main(void) {
	int n, m, k, i, j, t;
	scanf("%d %d %d", &n, &m, &k);
	Push_Relabel<int> PR(n + m + 3);
	PR.add_edge(0, 1, n);
	PR.add_edge(0, 2, k);
	for (i = 1; i <= n; i++) {
		PR.add_edge(1, i + 2, 1);
		PR.add_edge(2, i + 2, k);
		for (scanf("%d", &j); j--;) {
			scanf("%d", &t);
			PR.add_edge(i + 2, n + 2 + t, 1);
		}
	}
	for (i = 1; i <= m; i++) {
		PR.add_edge(n + 2 + i, n + m + 3, 1);
	}
	printf("%d\n", PR.max_flow(0, n + m + 3));
	return false;
}