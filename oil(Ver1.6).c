#include <stdio.h>
#include <conio.h>
#include <windows.h>


void setup();
void dataShow();
void dataAnis();


int main(){
	setup();
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
		printf("Failed to open file. Please check.");
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
	
	//printf("%lf, %lf, %lf, %lf", bGas, bDie, bKer, bCar);
	
	
	/*
	//Print data of file
	for (i=0; i<51; i++){
		printf("%d, %lf, %lf, %lf, %d\n", year[i], gasoline[i], diesel[i], kerosene[i], car[i]);
	}
	*/
	return 0;
}

void setup(){
	system("mode con:cols=100 lines=50");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	SetConsoleTitle("전국 평균 유가와 자동차 등록 대수의 상관관계 및 자동차 등록 대수 예측");
	for (int i=0; i<100; i++) printf("=");
	printf("          전국 평균 유가와 자동차 등록 대수의 상관관계 및 자동차 등록 대수 예측 프로그램\n\n\n\n\n");
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
	printf("[1]");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf(" 데이터 보기\n");
	printf("[2] 데이터 분석\n");
	printf("[3] 나가기\n\n\n\n\n");
	
	int cur=1;
	int brk=0;
	while(1){
		int key = _getch();
		if (key == 224) {
			key = _getch();
			switch (key){
				case 72:
					if (cur>1 && cur<=4) cur--; 
					break;
				case 80:
					if (cur>=0 && cur<3) cur++; 
					break;
				}
		}
		else if (key == 13){
			brk = 1;
			switch (cur){
				case 1:
					dataShow();
					break;
				case 2:
					dataAnis();
					break;
				case 3:
					printf("Bye!");
					exit(0);
					break;
			}
		}
		if (brk==1){
			break;
		}
		else{
			menu(cur);
		}
	}
}


void menu(int cur){
	switch (cur){
		case 1:
			system("cls");
			for (int i=0; i<100; i++) printf("=");
			printf("          전국 평균 유가와 자동차 등록 대수의 상관관계 및 자동차 등록 대수 예측 프로그램\n\n\n\n\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
			printf("[1]");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			printf(" 데이터 보기\n");
			printf("[2] 데이터 분석\n");
			printf("[3] 나가기\n\n\n\n\n");
			break;
		case 2:
			system("cls");
			for (int i=0; i<100; i++) printf("=");
			printf("          전국 평균 유가와 자동차 등록 대수의 상관관계 및 자동차 등록 대수 예측 프로그램\n\n\n\n\n");
			printf("[1] 데이터 보기\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
			printf("[2]");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			printf(" 데이터 분석\n");
			printf("[3] 나가기\n\n\n\n\n");
			break;
		case 3:
			system("cls");
			for (int i=0; i<100; i++) printf("=");
			printf("          전국 평균 유가와 자동차 등록 대수의 상관관계 및 자동차 등록 대수 예측 프로그램\n\n\n\n\n");
			printf("[1] 데이터 보기\n");
			printf("[2] 데이터 분석\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
			printf("[3]");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			printf(" 나가기\n\n\n\n\n");
			break;
		
	}
}

void dataShow(){
	
}

void dataAnis(){
	
}