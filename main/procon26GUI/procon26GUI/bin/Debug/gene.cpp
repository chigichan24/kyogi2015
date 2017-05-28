#include<string>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<complex>
#include<cmath>
#include<algorithm>
#include<map>
#include<vector>
#include<sstream>
#include<iostream>
#include<ctime>
using namespace std;
int main(void){
    srand(time(NULL));
    int N,M,Q;
    cin>>N>>M>>Q;
    cout<<N<<" "<<M<<" "<<Q<<endl;
    for(int i = 0;i < N;i++){
        cout<<rand()%M;
        for(int j = 1;j < N;j++){
            cout<<" "<<rand()%M;
        }
        cout<<endl;
    }

    for(int i = 0;i < Q;i++){
        printf("%+d\n",-100+rand()%200);
    }


    return 0;
}
