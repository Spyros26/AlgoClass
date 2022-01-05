#include <iostream>
#include <fstream>
#include <cmath>


using namespace std;


// m(l): index such that x[m(l)] is the smallest element in which a lis of size l finishes.
// lengths(i): length of lis until index i.
// n(i): smallest number in which the lis of size lengths(i) finishes until index i.
int lis(int x[], int N, int L, int p[], int m[], int lengths[], int n[]) {
	int newL, k;
	int mid, lo, hi;
	for (int i=0; i<N; ++i) {
		lo = 1;
		hi = L+1;
		while(lo<hi){
			mid = int(lo + floor((hi-lo)/2));
			if (x[m[mid]] < x[i]) lo = mid+1;
			else hi = mid;
		}
		newL = lo;
		p[i] = m[newL-1];
		m[newL] = i;
		if(newL > L) {
			L=newL;
		}
		lengths[i] = L;
		n[i] = x[m[L]];
	}
	return L;
}

// m_lds(l): index such that x[m_lds(l)] is the largest element in which a lds of size l finishes.
// lengths_lds(i): length of lds until index i.
// n_lds(i): largest number in which the lds of size lengths_lds(i) finishes until index i.
int lds(int x[], int N, int L, int p_lds[], int m_lds[], int lengths_lds[], int n_lds[], int n[]) {
	int newL, k;
	int mid, lo, hi;
	for (int i=0; i<N-1; ++i) {	
		lo = 1;
		hi = L+1;
		while(lo<hi){
			mid = int(lo + floor((hi-lo)/2));
			if (x[m_lds[mid]] > x[i]) lo = mid+1;
			else hi = mid;
		}
		newL = lo;
		p_lds[i] = m_lds[newL-1];
		m_lds[newL] = i;
		if(newL > L) L=newL;
		lengths_lds[i] = L;
		n_lds[i] = x[m_lds[L]];
		while((n_lds[i] < n[N-2-i]) && lengths_lds[i]>1) {
			lengths_lds[i] = lengths_lds[i]-1;
			n_lds[i] = x[m_lds[lengths_lds[i]]];
		}
		if(lengths_lds[i]<1){
			n_lds[i] = n[N-2-i]-1;
		} 
	}
	return L;
}

int main(int argc, char* argv[])
{
	int N,K;
	ifstream myfile (argv[1]);
    if(myfile.is_open()){
		myfile >> N >> K;
		int x[N], x_rev[N], p[N], m[N+1], lengths[N], n[N], k, p_lds[N], m_lds[N+1], lengths_lds[N], n_lds[N];
		int L, L_lds, l, l_max;

		for (int i=0; i<N; ++i){
			myfile >> x[i];
		}
		for (int i=0; i<N; ++i){
			lengths[i]=-1;
			n[i]=-1;
			x_rev[i]=x[N-1-i]+K;
		}
		
		L = lis(x,N,0,p,m,lengths,n);
		
		L_lds = lds(x_rev,N,0,p_lds,m_lds,lengths_lds,n_lds,n);
		
		l_max = -1;
		for(int i=0; i<N-1; i++){
			if (n[i] <= n_lds[N-2-i]){
				l = lengths[i] + lengths_lds[N-2-i];
				if(l > l_max) l_max = l;
			}
		}
		cout << l_max << endl;
		myfile.close();
	}
	else cout << "Unable to open file" << endl;

	return 0;
}


