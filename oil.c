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
	//no. of data-points
    int N;  
    //degree of polynomial
    int n;  
    printf("Enter the no. of data-points:\n");
    scanf("%d",&N);
    //arrays to store the c and y-axis data-points
    double x[N], y[N];  
    printf("Enter the x-axis values:\n");
    int i,j;
    for(i=0;i<N;i++){
        scanf("%lf",&x[i]);
    }
    printf("Enter the y-axis values:\n");
    for(i=0;i<N;i++){
        scanf("%lf",&y[i]);
    }
    printf("Enter the degree of polynomial to be used:\n");
    scanf("%d",&n);
    // an array of size 2*n+1 for storing N, Sig xi, Sig xi^2, ...., etc. which are the independent components of the normal matrix
    double X[2*n+1];  
    for(i=0;i<=2*n;i++){
        X[i]=0;
        for(j=0;j<N;j++){
            X[i]=X[i]+pow(x[j],i);
        }
    }
    //the normal augmented matrix
    double B[n+1][n+2];  
    // rhs
    double Y[n+1];      
    for(i=0;i<=n;i++){
        Y[i]=0;
        for(j=0;j<N;j++){
            Y[i]=Y[i]+pow(x[j],i)*y[j];
        }
    }
    for(i=0;i<=n;i++){
        for(j=0;j<=n;j++){
            B[i][j]=X[i+j]; 
        }
    }
    for(i=0;i<=n;i++){
        B[i][n+1]=Y[i];
    }
    double A[n+1];
    printf("The polynomial fit is given by the equation:\n");
    printMatrix(n+1,n+2,B);
    gaussEliminationLS(n+1,n+2,B,A);
    for(i=0;i<=n;i++){
        printf("%lfx^%d+",A[i],i);
    }
     
}

/******************************************************
*************Chi-square fitting**************
Polynomial Fitting
******************************************************/
#include<stdio.h>
#include<math.h>
/*******
 Function that performs Gauss-Elimination and returns the Upper triangular matrix and solution of equations:
There are two options to do this in C.
1. Pass the augmented matrix (a) as the parameter, and calculate and store the upperTriangular(Gauss-Eliminated Matrix) in it.
2. Use malloc and make the function of pointer type and return the pointer.
This program uses the first option.
********/
void gaussEliminationLS(int m, int n, double a[m][n], double x[n-1]){
    int i,j,k;
    for(i=0;i<m-1;i++){
        //Partial Pivoting
        for(k=i+1;k<m;k++){
            //If diagonal element(absolute vallue) is smaller than any of the terms below it
            if(fabs(a[i][i])<fabs(a[k][i])){
                //Swap the rows
                for(j=0;j<n;j++){                
                    double temp;
                    temp=a[i][j];
                    a[i][j]=a[k][j];
                    a[k][j]=temp;
                }
            }
        }
        //Begin Gauss Elimination
        for(k=i+1;k<m;k++){
            double  term=a[k][i]/ a[i][i];
            for(j=0;j<n;j++){
                a[k][j]=a[k][j]-term*a[i][j];
            }
        }
         
    }
    //Begin Back-substitution
    for(i=m-1;i>=0;i--){
        x[i]=a[i][n-1];
        for(j=i+1;j<n-1;j++){
            x[i]=x[i]-a[i][j]*x[j];
        }
        x[i]=x[i]/a[i][i];
    }
             
}

void printMatrix(int m, int n, double matrix[m][n]){
    int i,j;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            printf("%lf\t",matrix[i][j]);
        }
        printf("\n");
    } 
}
