#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>



using namespace std;

void update_array(std::vector< int > sums[], std::vector< int > cnts[], int a[], int tail) {
	
	for(int i=0; i<sums[tail].size(); i++) {
		int sum = sums[tail].at(i);
		int cnt = cnts[tail].at(i);
		if(a[sum]==-1 || a[sum] > cnt) {
			a[sum] = cnt;
		}
	}
}

int blocks(int N, int K, int p[], int a[], int ret) {
	
	std::vector<int> sums[N+1];
	std::vector<int> cnts[N+1];
	int head = 0;
	int tail = 0;
	int current_sum = p[0];
	int pos, len;
	
	while(tail<N) {
		if(current_sum > K) {
			update_array(sums, cnts ,a , tail);
			tail++;
			head = tail;
			current_sum = p[head];
		}
		else if(current_sum <= K) {
			if(a[K-current_sum] != -1) {
				if(ret==-1 || ret > head - tail + 1 + a[K-current_sum]) {
					ret = head - tail + 1 + a[K-current_sum];
				}
			}
			sums[head].push_back(current_sum);
			cnts[head].push_back(head-tail+1);
			head++;
			current_sum += p[head];
			if(head>N-1) {
				current_sum = K + 1;
			}
		}
		
	}
	
	return ret;
	
}


int main(int argc, char *argv[]) {
	int N,K;
	ifstream myfile (argv[1]);
        if(myfile.is_open()){
		myfile >> N >> K;
	           
	    int p[N];
	    
	    for (int i=0; i<N; ++i){
	        myfile >> p[i];
	    }
	    
	    int a[K+1];
	    
	    a[0] = 0;
	    for (int i=1; i<K+1; ++i){
	        a[i] = -1;
	    }
	    
	    int result = -1;
	    
	    result = blocks(N, K, p, a, result);
	        
	    cout << result << endl;
	               myfile.close();
        }
        else cout << "Unable to open file" << endl;

	return 0;
}

