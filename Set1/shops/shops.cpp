#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>

using namespace std;



int main() {
        int N,K;

            cin >> N >> K;
            int p[N];
            int a[K+1];

            for (int i=0; i<N; ++i){
                    cin >> p[i];
            }
            for (int i=0; i<=K; ++i){
                    a[i] = (int)1e7;
            }

            int cnt, sum, sum1, cnt1;
            vector<int> sums[N+1];
	        vector<int> cnts[N+1];

            for (int i=0; i<N; i++) {
            	for(int l=0; l<sums[i-1].size(); l++) {
                    sum1 = sums[i-1].at(l);
                    cnt1 = cnts[i-1].at(l);
                    if(a[sum1] > cnt1) {
                        a[sum1] = cnt1;
                    }
	            }
                sum = 0;
                cnt = 0;
                for (int j=i; j<N; j++) {
                    cnt++;
                    sum += p[j];
                    if (sum > K) break;
                    if (a[K] > cnt + a[K-sum]) {
                        a[K] = cnt + a[K-sum];
                    }
                    sums[j].push_back(sum);
			        cnts[j].push_back(cnt);
                }
            }

            if (a[K] == (int)1e7) a[K] = -1;

            cout << a[K] << endl;
	

        return 0;
}