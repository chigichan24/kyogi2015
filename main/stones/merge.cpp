#include <bits/stdc++.h>

using namespace std;

int main(){
	char fileIndex [] = {'1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g'};

	FILE *target;

	target = fopen("All.txt","w");

	for(int i = 0; i < 16; ++i){
		FILE *fp;
		char tmp[128];
		sprintf(tmp,"%c.txt",fileIndex[i]);
		fp = fopen(tmp,"r");


		char line[9];
		int cnt = 0;
		while(fscanf(fp,"%s",line) != EOF){
			if(cnt % 8 == 0){
				fprintf(target, "\n");
			}
			fprintf(target,"%s\n",line);
			cnt++;
		}
		printf("END : %d\n",i);
		fclose(fp);

	}

	fclose(target);

	return 0;
}