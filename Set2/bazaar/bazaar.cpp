#include <iostream>
#include <vector>
#include <utility>

using namespace std;

vector< pair<int,int> > A1, A2, A3, B1, B2, B3, C1, C2, C3;
vector<int> A, B, C, S1, S2, S3;

void store_offer(int x, int y, char item, char seller) {
    switch (seller) {
    
    case '1':
        switch (item) {
            case 'A': A1.push_back(make_pair(x,y)); break;
            case 'B': B1.push_back(make_pair(x,y)); break;
            case 'C': C1.push_back(make_pair(x,y)); break;
            default: cout << "Error with item " << item << endl;
        }
        break;

    case '2':
        switch (item) {
            case 'A': A2.push_back(make_pair(x,y)); break;
            case 'B': B2.push_back(make_pair(x,y)); break;
            case 'C': C2.push_back(make_pair(x,y)); break;
            default: cout << "Error with item " << item << endl;
        }
        break;

    case '3':
        switch (item) {
            case 'A': A3.push_back(make_pair(x,y)); break;
            case 'B': B3.push_back(make_pair(x,y)); break;
            case 'C': C3.push_back(make_pair(x,y)); break;
            default: cout << "Error with item " << item << endl;
        }
        break;
    
    default: cout << "Error with seller " << seller << endl;
    }
}

void knapsack(vector< pair<int,int> > X, vector<int> &R, int N) {
    int units_offered = 0, s = 0;
    for (int i=0; i<X.size(); ++i) units_offered += X[i].first;
    R.resize(min(units_offered, N) + 1);
    R[0] = 0;
    for (int i=1; i<R.size(); ++i) R[i] = 1 + (int) 1e9;

    for (int i=0; i<X.size(); ++i) {
        int size = X[i].first;
        int price = X[i].second;
        s += size;
        for (int j=min(s,N); j>=1; --j) {
            int previous_offer = max(j-size, 0);
            R[j] = min(R[j], R[previous_offer] + price);
        }
    }
}

void merge(vector<int> &X, vector<int> A, vector<int> B, vector<int> C) {
    int size = min(min(A.size(), B.size()), C.size());
    X.resize(size);
    for (int i=0; i<size; ++i) X[i] = A[i] + B[i] + C[i];
}

int main() {
    int N, M, quantity, price, res = 1+(int)1e9;
    char seller, item;

    cin >> N >> M;
    for (int i=0; i<M; ++i) {
        cin >> seller >> item;
        cin >> quantity >> price;
        store_offer(quantity, price, item, seller);
    }

    knapsack(A1, A, N);
    knapsack(B1, B, N);
    knapsack(C1, C, N);
    merge(S1, A, B, C);
    knapsack(A2, A, N);
    knapsack(B2, B, N);
    knapsack(C2, C, N);
    merge(S2, A, B ,C);
    knapsack(A3, A, N);
    knapsack(B3, B, N);
    knapsack(C3, C, N);
    merge(S3, A, B, C);

    if (S1.size() + S2. size() + S3.size() -3 < N) {
        cout << -1 << endl;
        return 0;
    }

    for (int i=0; i<=min(N, (int) S1.size()-1); ++i) 
        for (int j=0; j<=min(N-i, (int) S2.size()-1); ++j)
            if (i + j + S3.size()-1 >= N) res = min(res, S1[i]+S2[j]+S3[N-i-j]);
        
    cout << res << endl;
 
    return 0;
}