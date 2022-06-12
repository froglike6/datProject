#include <stdio.h>

int main(){
	int year[51];
	double gasoline[51], diesel[51], kerosene[51];
	int car[51];
	int temp=0, i;
	FILE *data = NULL;
	data = fopen("data/oildata2.csv", "r");
	if (data !=NULL){
		while (!feof(data)){
			fscanf(data, "%d,%lf,%lf,%lf,%d\n", &year[temp], &gasoline[temp], &diesel[temp], &kerosene[temp], &car[temp]);
			temp++;
		}
	}
	fclose(data);
	for (i=0; i<51; i++){
		printf("%d, %lf, %lf, %lf, %d\n", year[i], gasoline[i], diesel[i], kerosene[i], car[i]);
	}
	return 0;
}

