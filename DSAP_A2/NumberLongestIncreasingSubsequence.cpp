#include <iostream>
using namespace std;
int NoLIS(int a[], int n) {
int dp[n];
int  p;
int res = 0;
int maxi = 1;
int cnt[n];
int k;
for(int i = 0; i < n; i++) 
{
dp[i] = 1;
cnt[i] = 1;
}
for(p = 0; p< n; p++)
{
for (k = 0; k < p; k++)
{
if(a[k] < a[p] && 1 + dp[k] > dp[p]) {
dp[p] = 1 + dp[k];
cnt[p] = cnt[k];
} 
else if (a[k] < a[p] && 1 + dp[k] == dp[p]) {
cnt[p] += cnt[k];
}
}
maxi =max(maxi,dp[p]);
    }
for (int i = 0; i < n; i++) {
if (dp[i] == maxi) res += cnt[i];
}
return res;
}
int main() {
int n;
cin >> n;
int a[n];
for (int i = 0; i < n; i++) 
cin >> a[i];
cout<<NoLIS(a, n)<<endl;
return 0;
}
