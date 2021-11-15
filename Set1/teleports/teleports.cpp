#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>

using namespace std;



int partition (int w[], int a[], int b[],int left, int right) {
        int pivot_spot = left + rand()%(right-left+1);
        int pivot = w[pivot_spot];
        int i = left - 1;
        int j = right + 1;
        while (true) {
                while (w[++i] < pivot);
                while (w[--j] > pivot);
                if (i < j) {
                        swap(w[i], w[j]);
                        swap(a[i], a[j]);
                        swap(b[i], b[j]);
                }
                else return j;
        }
}

void quickSort (int w[], int a[], int b[], int left, int right) {
        int q;
        if (left >= right) return;
        q = partition(w, a, b, left, right);
        quickSort(w, a, b, left, q);
        quickSort(w, a, b, q+1, right);
}

class UnionFind {
        private:
                int *parent, *size;
                vector<int> path;
        public:
                UnionFind(int count) {
                        parent = new int[count];
                        size = new int[count];
                        for (int i=0; i<count; ++i) {
                                parent[i] = i;
                                size[i] = 1;
                        }
                }

                ~UnionFind() {
                        delete[] parent;
                        delete[] size;
                }

                int Find (int u) {
                        while (true) {
                                int p = parent[u];
                                if (p == u) break;
                                path.push_back(u);
                                u = p;
                        }
                        int i = 0;
                        while (!path.empty()) {
                                parent[path[i]] = u;
                                ++i;
                                path.pop_back();
                        }
                        return u;
                }

                void Union (int u, int v) {
                        int ru = Find(u);
                        int rv = Find(v);
                        if (ru == rv) return;
                        if (size[ru] < size[rv]) {
                                parent[ru] = rv;
                                size[rv] += size[ru];
                                return;
                        }
                        parent[rv] = ru;
                        size[ru] += size[rv];

                }

                bool are_connected (int x, int y) {
                        return (Find(x) == Find(y));
                }
};


bool Mortys_rescue (int w[], int a[], int b[], int candidate_portal, int c[], int N, int M) {
        UnionFind uf(N+1);
        for (int i=candidate_portal; i<M; ++i) {
                uf.Union(a[i], b[i]);
        }
        for (int i=1; i<N+1; ++i) {
                if (!uf.are_connected(c[i], i)) return false;
        }
        return true;
}

int binarySearch (int w[], int a[], int b[], int left, int right, int c[], int N, int M) {
        if (left >= right) return left;
        int mid = (left + right) / 2;
        bool is_possible = Mortys_rescue(w, a, b, mid, c, N, M);
        if (!is_possible) return binarySearch(w, a, b, left, mid-1, c, N, M);
        return binarySearch(w, a, b, mid+1, right, c, N, M);
}

int main() {
        int N,M;
        cin >> N >> M;
        int c[N+1], a[M], b[M];
        int w[M];

        srand(time(NULL));

        c[0] = 0;
        for (int i=1; i<N+1; ++i){
                cin >> c[i];
        }
        for (int j=0; j<M; ++j){
                cin >> a[j] >> b[j] >> w[j];
        }

        quickSort(w, a, b, 0, M-1);
        int pos = binarySearch(w, a, b, 0, M-1, c, N, M);

        if (!Mortys_rescue(w, a, b, pos, c, N, M)) cout << w[pos-1] << endl;
        else cout << w[pos] << endl;
	

        return 0;
}