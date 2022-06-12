#include <stdio.h>
#include <math.h>
#include <windows.h>


int main(){
	int year[51];
	double gasoline[51], diesel[51], kerosene[51];
	int car[51];
	int temp=0, i;
	double temp2=0, temp3=0;
	
	double meanGas, meanDie, meanKer, meanCar, meanYar;
	double aGas, aDie, aKer, aCar;
	FILE *data = NULL;
	data = fopen("data/oildata2.csv", "r");
	if (data !=NULL){
		while (!feof(data)){
			fscanf(data, "%d,%lf,%lf,%lf,%d\n", &year[temp], &gasoline[temp], &diesel[temp], &kerosene[temp], &car[temp]);
			temp++;
		}
	}
	fclose(data);
	/*
	Start point for linear regression
	y=ax+b
	*/
	for (i=0; i<51; i++){
		meanGas += gasoline[i];
		meanDie += diesel[i];
		meanKer += kerosene[i];
		meanCar += car[i];
		meanYar += year[i];
	}
	meanGas/=51;
	meanDie/=51;
	meanKer/=51;
	meanCar/=51;
	meanYar/=51;
	//Mean value checked
	
	
	for (i=0; i<51; i++){
		temp2+=(gasoline[i]-meanGas)*(year[i]-meanYar);
		temp3+=(gasoline[i]-meanGas)*(gasoline[i]-meanGas);
	}
	aGas = temp2/temp3;
	temp2=0, temp3=0;
	printf("%lf", aGas);
	/*
	for (i=0; i<51; i++){
		temp2+=((diesel[i]-meanDie)*(year[i]-meanYar));
		temp3+=((diesel[i]-meanDie)*(diesel[i]-meanDie));
	}
	aDie = temp2/temp3;
	temp2=0, temp3=0;
	for (i=0; i<51; i++){
		temp2+=(kerosene[i]-meanKer)*(year[i]-meanYar);
		temp3+=(kerosene[i]-meanKer)*(kerosene[i]-meanKer);
	}
	aKer = temp2/temp3;
	temp2=0, temp3=0;
	for (i=0; i<51; i++){
		temp2+=(car[i]-meanCar)*(year[i]-meanYar);
		temp3+=(car[i]-meanCar)*(car[i]-meanCar);
	}
	aCar = temp2/temp3;
	temp2=0, temp3=0;
	
	printf("%lf, %lf, %lf, %lf", aGas, aDie, aKer, aCar);
	///*
	for (i=0; i<51; i++){
		printf("%d, %lf, %lf, %lf, %d\n", year[i], gasoline[i], diesel[i], kerosene[i], car[i]);
	}
	*/
	return 0;
}

