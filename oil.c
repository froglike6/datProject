#include <stdio.h>
#include <conio.h>
#include <windows.h>


void setup();
void dataShow();
void dataAnis();
void dataAnisMenu(int cur);
void dataAnisMain(int N, double y[N]);

int year[60];
double gasoline[60], diesel[60], kerosene[60];
int car[60];

int main(){
	int temp=0, i;
	
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
	setup();
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
	while(1){
		int key = _getch();
		if (key == 13){
			switch (cur){
				case 1:
					dataShow();
					break;
				case 2:
					dataAnis();
					return;
					break;
				case 3:
					printf("Bye!");
					exit(0);
					break;
			}
		}
		else if (key == 224) {
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
		menu(cur);
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
	system("cls");
	for (int i=0; i<100; i++) printf("=");
	printf("          전국 평균 유가와 자동차 등록 대수의 상관관계 및 자동차 등록 대수 예측 프로그램\n\n\n\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
	printf("[1]");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf(" 가솔린 데이터\n");
	printf("[2] 디젤 데이터\n");
	printf("[3] 케로신 데이터\n");
	printf("[4] 자동차 데이터\n");
	printf("[5] 뒤로 가기\n\n\n\n\n");
	int cur=1;
	int N=51; //Number of data points
	double y[N]; //array of x and y data points
	while(1){
		int key = _getch();
		if (key == 224) {
			key = _getch();
			switch (key){
				case 72:
					if (cur>1 && cur<=6) cur--; 
					break;
				case 80:
					if (cur>=0 && cur<5) cur++; 
					break;
				}
		}
		else if (key == 13){
			switch (cur){
				case 1:
					for (int i=0; i<51; i++) y[i]=gasoline[i];
					dataAnisMain(N, y);
					return;
					break;
				case 2:
					for (int i=0; i<51; i++) y[i]=diesel[i];
					dataAnisMain(N, y);
					return;
					break;
				case 3:
					for (int i=0; i<51; i++) y[i]=kerosene[i];
					dataAnisMain(N, y);
					return;
					break;
				case 4:
					for (int i=0; i<51; i++) y[i]=car[i];
					dataAnisMain(N, y);
					return;
					break;
				case 5:
					setup();
					return;
					break;
			}
		}
		dataAnisMenu(cur);
	}
}

void dataAnisMain(int N, double y[N]){
	int n=0;
	system("cls");
	for (int i=0; i<100; i++) printf("=");
	printf("          전국 평균 유가와 자동차 등록 대수의 상관관계 및 자동차 등록 대수 예측 프로그램\n\n\n\n\n");
	printf("회귀할 데이터의 차수를 입력(0<n<11): ");
	scanf("%d", &n);
	while (n<1 || n>10){
		printf("\n다시 입력: ");
		fflush(stdin);
		scanf("%d", &n);
	}
    int i,j;
    long double X[2*n+1];  
    for(i=0;i<=2*n;i++){
        X[i]=0;
        for(j=0;j<N;j++){
            X[i]=X[i]+pow(year[j],i);
        }
    }
    long double B[n+1][n+2];  
    long double Y[n+1];      
    for(i=0;i<=n;i++){
        Y[i]=0;
        for(j=0;j<N;j++){
            Y[i]=Y[i]+pow(year[j],i)*year[j];
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
    long double A[n+1];
    gaussEliminationLS(n+1,n+2,B,A);
    for(i=0;i<=n-1;i++)
		printf("%ex^%d+",A[i],i);
	printf("%ex^%d", A[n], n);
	return;
}

void dataAnisMenu(int cur){
	switch (cur){
			case 1:
				system("cls");
				for (int i=0; i<100; i++) printf("=");
				printf("          전국 평균 유가와 자동차 등록 대수의 상관관계 및 자동차 등록 대수 예측 프로그램\n\n\n\n\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
				printf("[1]");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				printf(" 가솔린 데이터\n");
				printf("[2] 디젤 데이터\n");
				printf("[3] 케로신 데이터\n");
				printf("[4] 자동차 데이터\n");
				printf("[5] 뒤로 가기\n\n\n\n\n");
				break;
			case 2:
				system("cls");
				for (int i=0; i<100; i++) printf("=");
				printf("          전국 평균 유가와 자동차 등록 대수의 상관관계 및 자동차 등록 대수 예측 프로그램\n\n\n\n\n");
				printf("[1] 가솔린 데이터\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
				printf("[2]");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				printf(" 디젤 데이터\n");
				printf("[3] 케로신 데이터\n");
				printf("[4] 자동차 데이터\n");
				printf("[5] 뒤로 가기\n\n\n\n\n");
				break;
			case 3:
				system("cls");
				for (int i=0; i<100; i++) printf("=");
				printf("          전국 평균 유가와 자동차 등록 대수의 상관관계 및 자동차 등록 대수 예측 프로그램\n\n\n\n\n");
				printf("[1] 가솔린 데이터\n");
				printf("[2] 디젤 데이터\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
				printf("[3]");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				printf(" 케로신 데이터\n");
				printf("[4] 자동차 데이터\n");
				printf("[5] 뒤로 가기\n\n\n\n\n");
				break;
			case 4:
				system("cls");
				for (int i=0; i<100; i++) printf("=");
				printf("          전국 평균 유가와 자동차 등록 대수의 상관관계 및 자동차 등록 대수 예측 프로그램\n\n\n\n\n");
				printf("[1] 가솔린 데이터\n");
				printf("[2] 디젤 데이터\n");
				printf("[3] 케로신 데이터\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
				printf("[4]");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				printf(" 자동차 데이터\n");
				printf("[5] 뒤로 가기\n\n\n\n\n");
				break;
			case 5:
				system("cls");
				for (int i=0; i<100; i++) printf("=");
				printf("          전국 평균 유가와 자동차 등록 대수의 상관관계 및 자동차 등록 대수 예측 프로그램\n\n\n\n\n");
				printf("[1] 가솔린 데이터\n");
				printf("[2] 디젤 데이터\n");
				printf("[3] 케로신 데이터\n");
				printf("[4] 자동차 데이터\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
				printf("[5]");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				printf(" 뒤로 가기\n\n\n\n\n");
				break;
	}
}

void gaussEliminationLS(int m, int n, long double a[m][n], long double x[n-1]){
    int i,j,k;
    for(i=0;i<m-1;i++){
        //Partial Pivoting
        for(k=i+1;k<m;k++){
            //If diagonal element(absolute vallue) is smaller than any of the terms below it
            if(fabs(a[i][i])<fabs(a[k][i])){
                //Swap the rows
                for(j=0;j<n;j++){                
                    long double temp;
                    temp=a[i][j];
                    a[i][j]=a[k][j];
                    a[k][j]=temp;
                }
            }
        }
        //Begin Gauss Elimination
        for(k=i+1;k<m;k++){
            long double  term=a[k][i]/ a[i][i];
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

