#include<bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define se second
#define fi first

using namespace std;

string decToBinary(int n) 
{ 
    // counter for binary array 
    int i = 0; 
    string num;
    char c;
    while (n > 0) { 
  
        // storing remainder in binary array 
        int t=n%2;
        c=t+'0';
        //cout<<"here: "<<c;
        num.pb(c);
        n = n / 2; 
    } 
    
    reverse(num.begin(), num.end());
    return num;
} 

int main(){
    cout<<decToBinary(10);
    return 0;
}