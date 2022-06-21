/*
v8.2-beta3(Some test)
*/
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <memory.h>
#include <math.h>
#include <graphics.h>
#include <direct.h>
void setup();
void dataShow();
void dataAnis();
void dataAnisMenu(int cur);
void dataAnisMain(int N, double y[]);
void gaussEliminationLS(int m, int n, double a[][1<<10], double x[]);
void graph(double y[60]);
void graphcar(double y[60]);
void menu(int cur);
void mainmenu();
int year[60];
void home();
double gasoline[60], diesel[60], kerosene[60];
double car[60];
char strBuffer[260]={0, };
char *pstrBuffer = NULL;
char msg[300];
int main(){
	int temp=0, i;
	
	FILE *data = NULL;
	data = fopen("data/oildata2.csv", "r");//데이터 불러오기
	if (data !=NULL){
		fscanf(data, "%*[^\n]\n");//첫번째 행을 먼저 불러와서 두번째 행부터 인식하도록 함.
		while (!feof(data)){
			fscanf(data, "%d,%lf,%lf,%lf,%lf\n", &year[temp], &gasoline[temp], &diesel[temp], &kerosene[temp], &car[temp]);//각각의 값을 배열에 넣는다
			temp++;
		}
	}
	else{
		printf("Failed to open file. Please check.");//파일 열기 실패시 작동
		return -1;
	}
	fclose(data);
	pstrBuffer = getcwd(strBuffer, 260);
	setup();
	return 0;
}

void setup(){
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;//커서를 안보이게 하는 설정
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	system("mode con:cols=100 lines=26");//콘솔 창 사이즈 설정
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	SetConsoleTitle("2318 주도현");//제목 설정
	system("cls");
	int i;
	for (i=0; i<100; i++) printf("=");
	printf("          전국 평균 유가와 자동차 등록 대수의 상관관계 및 자동차 등록 대수 예측 프로그램\n\n\n\n\n");
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);//색상 반전!
	printf("[1]");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf(" 데이터 보기\n");
	printf("[2] 데이터 분석\n");
	printf("[3] 나가기\n\n\n\n\n");
	
	int cur=1;
	while(1){
		int key = _getch();//키 입력
		if (key == 13){//엔터
			switch (cur){
				case 1:
					dataShow();//데이터 보기 함수
					break;
				case 2:
					dataAnis();//데이터 분석 함수 
					return;
					break;
				case 3:
					printf("Bye!");
					exit(0);//return보다 강력한 종료 함수
					break;
			}
		}
		else if (key == 224) {//방향키라면
			key = _getch();//한번 더 입력 받음
			switch (key){
				case 72://위 화살표 
					if (cur>1 && cur<=4) cur--; 
					break;
				case 80://아래 화살표
					if (cur>=0 && cur<3) cur++; 
					break;
				}
		}
		menu(cur);//커서 색 변환 위한 함수
	}
}


void menu(int cur){
	int i;
	switch (cur){//각각의 케이스에 대해 색을 바꿈
		case 1:
			mainmenu();//제목 적는 함수
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
			printf("[1]");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			printf(" 데이터 보기\n");
			printf("[2] 데이터 분석\n");
			printf("[3] 나가기\n\n\n\n\n");
			break;
		case 2:
			mainmenu();
			printf("[1] 데이터 보기\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
			printf("[2]");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			printf(" 데이터 분석\n");
			printf("[3] 나가기\n\n\n\n\n");
			break;
		case 3:
			mainmenu();
			printf("[1] 데이터 보기\n");
			printf("[2] 데이터 분석\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
			printf("[3]");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			printf(" 나가기\n\n\n\n\n");
			break;
		
	}
}

void dataShow(){//데이터 보여주는 함수
	mainmenu();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
	printf("[1]");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf(" 가솔린 데이터\n");
	printf("[2] 디젤 데이터\n");
	printf("[3] 케로신 데이터\n");
	printf("[4] 자동차 데이터\n");
	printf("[5] 뒤로 가기\n\n\n\n\n");
	int cur=1;
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
					graph(gasoline);//gasoline에 대한 그래프 출력
					home();//홈으로 돌아가는 함수
					return;
					break;
				case 2:
					graph(diesel);
					home();
					return;
					break;
				case 3:
					graph(kerosene);
					home();
					return;
					break;
				case 4:
					graphcar(car);
					home();
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

void dataAnis(){//데이터 분석 함수
	mainmenu();
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
					for (int i=0; i<51; i++) y[i]=gasoline[i];//가솔린 선택하면, y 배열에 가솔린 배열 넣음
					dataAnisMain(N, y);//데이터 메인 분석 함수 호출
					home();//홈으로 가는 함수
					return;
					break;
				case 2:
					for (int i=0; i<51; i++) y[i]=diesel[i];
					dataAnisMain(N, y);
					home();
					return;
					break;
				case 3:
					for (int i=0; i<51; i++) y[i]=kerosene[i];
					dataAnisMain(N, y);
					home();
					return;
					break;
				case 4:
					for (int i=0; i<51; i++) y[i]=car[i];
					dataAnisMain(N, y);
					home();
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

void dataAnisMain(int N, double y[1<<10]){
	int n=0;
	mainmenu();
	printf("회귀할 데이터의 차수를 입력(0<n<11): ");//n차항 식으로 회귀할때, n을 받음
	scanf("%d", &n);
	while (n<1 || n>10){//예외 처리
		printf("\n다시 입력: ");
		fflush(stdin);//버퍼 비우기
		scanf("%d", &n);
	}
	int i, j;
	int x[60];
	memcpy(x, year, sizeof(year));//간단하게 배열 복사 위한 메모리 복사
	
	double X[2*n+1];
    for(i=0;i<=2*n;i++){
        X[i]=0;
        for(j=0;j<N;j++){
            X[i]=X[i]+pow(x[j],i);
        }
    }
    double B[n+1][1<<10];  
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
    gaussEliminationLS(n+1,n+2,B,A);
    //회귀식 출력
    printf("%ex^%d",A[n],n);
    for(i=n-1;i>0;i--){
    	if (A[i]>0) printf("+");
        printf("%ex^%d",A[i],i);
	}
	if (A[0]>0) printf("+");
	printf("%e\n",A[0]);
}

void dataAnisMenu(int cur){//데이터 메뉴 선택 함수
	switch (cur){
			case 1:
				mainmenu();
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
				mainmenu();
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
				mainmenu();
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
				mainmenu();
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
				mainmenu();
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

void gaussEliminationLS(int m, int n, double a[][1<<10], double x[]){//가우스 소거법
    int i,j,k;
    for(i=0;i<m-1;i++){
        for(k=i+1;k<m;k++){
            if(fabs(a[i][i])<fabs(a[k][i])){
                for(j=0;j<n;j++){                
                    double temp;
                    temp=a[i][j];
                    a[i][j]=a[k][j];
                    a[k][j]=temp;
                }
            }
        }
        for(k=i+1;k<m;k++){
            double term=a[k][i]/ a[i][i];
            for(j=0;j<n;j++){
                a[k][j]=a[k][j]-term*a[i][j];
            }
        }  
    }
    for(i=m-1;i>=0;i--){
        x[i]=a[i][n-1];
        for(j=i+1;j<n-1;j++){
            x[i]=x[i]-a[i][j]*x[j];
        }
        x[i]=x[i]/a[i][i];
    }
             
}
void graph(double y[60]){//그래프 그리는 함수
	int gd=0, gm, status;
	initwindow(640, 1000);
	int data[60]={0, };
	line(0, 1000, 12, 1000-(int)y[1]/2);
	for (int i=1;i<50;i++){
		line(i*12, 1000-(int)y[i]/2, (i+1)*12, 1000-(int)y[i+1]/2);
	}
    sprintf(msg, "%s\\main.exe", pstrBuffer);
	system(msg);
	getch();
}
void graphcar(double y[60]){//자동차그래프 그리는 함수
	int gd=0, gm;
	initwindow(640, 1000);
	int data[60]={0, };
	line(0, 1000, 12, 1000-(int)y[1]/25000);
	for (int i=1;i<50;i++){
		delay(1000);
		line(i*12, 1000-(int)y[i]/25000, (i+1)*12, 1000-(int)y[i+1]/25000);
	}
	sprintf(msg, "%s\\main.exe", pstrBuffer);
	system(msg);
	getch();	
}
void home(){
	printf("엔터를 눌러 홈으로 돌아가기");
	while (1){
		int key = _getch();
		if (key==13){//엔터 누르면
			setup();//홈으로
		}
	}
	return;
}
void mainmenu(){//많이 사용되어 따로 빼둠
	int i;
	system("cls");
	for (i=0; i<100; i++) printf("=");
	printf("          전국 평균 유가와 자동차 등록 대수의 상관관계 및 자동차 등록 대수 예측 프로그램\n\n\n\n\n");
}