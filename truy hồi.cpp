#include <bits/stdc++.h>
using namespace std;
int n,k;
int a[100];
int f[100][100];
void bale(){
for(int i=1;i<=n;i++){
	f[i][1]=1;
}
for(int j=2;j<=k;j++){
	for(int i=j;i<=n;i++){
		f[i][j]=0;
		for(int m=1;m<i;m++){
			if(a[m]<a[i]){
				f[i][j]+=f[m][j-1];
			}
		}
	}
}int tong=0;
for(int i=k;i<=n;i++){
	tong+=f[i][k];
}
cout<<tong;
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}bale();
	return 0;
}

