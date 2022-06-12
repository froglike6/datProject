#include <stdio.h>
#include <math.h>
#include <windows.h>


int main(){
	int year[60];
	double gasoline[60], diesel[60], kerosene[60];
	int car[60];
	int temp=0, i;
	double temp2=0, temp3=0;
	
	double meanGas, meanDie, meanKer, meanCar, meanYar;
	double aGas, aDie, aKer, aCar;
	double bGas, bDie, bKer, bCar;
	
	FILE *data = NULL;
	data = fopen("data/oildata2.csv", "r");
	if (data !=NULL){
		fscanf(data, "%*[^\n]\n");
		while (!feof(data)){
			fscanf(data, "%d,%lf,%lf,%lf,%d\n", &year[temp], &gasoline[temp], &diesel[temp], &kerosene[temp], &car[temp]);
			temp++;
		}
	}
	else{
		printf("Failed to open file. Please check file.");
		return -1;
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
		temp2+=((gasoline[i]-meanGas)*(year[i]-meanYar));
		temp3+=((year[i]-meanYar)*(year[i]-meanYar));
	}
	aGas = temp2/temp3;
	bGas = meanGas-(aGas*meanYar);
	temp2=0;
	for (i=0; i<51; i++){
		temp2+=((diesel[i]-meanDie)*(year[i]-meanYar));
	}
	aDie = temp2/temp3;
	bDie = meanDie - aDie*meanYar;
	temp2=0;
	for (i=0; i<51; i++){
		temp2+=(kerosene[i]-meanKer)*(year[i]-meanYar);
	}
	aKer = temp2/temp3;
	bKer = meanKer - aKer*meanYar;
	temp2=0;
	for (i=0; i<51; i++){
		temp2+=(car[i]-meanCar)*(year[i]-meanYar);
	}
	aCar = temp2/temp3;
	bCar = meanCar - aCar*meanYar;
	temp2=0, temp3=0;
	
	printf("%lf, %lf, %lf, %lf", bGas, bDie, bKer, bCar);
	
	
	/*
	//Print data of file
	for (i=0; i<51; i++){
		printf("%d, %lf, %lf, %lf, %d\n", year[i], gasoline[i], diesel[i], kerosene[i], car[i]);
	}
	*/
	return 0;
}

