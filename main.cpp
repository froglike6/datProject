/*#############################################################################################################
#v8.3-rc1(Add comment, Latest beta)                    														  #
#제목: 전국 유가와 자동차 등록 대수 추세 분석 프로그램 														#
#작성자: 2318 주도현                                   														#
#유가 정보 출처: 한국석유공사 오피넷(https://www.opinet.co.kr/user/opdown/opDownload.do)                      #
#자동차 등록 대수 출처: 통계청 e-나라지표(https://www.index.go.kr/potal/main/EachDtlPageDetail.do?idx_cd=1257)#
#32비트 환경에서 컴파일 후 exe 파일 실행																		#
#############################################################################################################*/

#include <stdio.h>
#include <conio.h>   //키 입력 받는 _getch 함수 사용
#include <math.h>    //수학 계산
#include <graphics.h>//그래프 출력

void setup();                              					         //첫 화면에서 메뉴 선택하는 함수
void dataShow();													 //데이터 보여주는 함수
void dataAnis();													 //데이터 분석하는 페이지
void dataAnisMenu(int cur);											 //데이터 분석하는 함수의 메뉴
void dataAnisMain(int N, double y[]);                                //데이터 분석하는 함수
void gaussEliminationLS(int m, int n, double a[][1<<10], double x[]);//가우스 소거법
void graph(double y[60]);											 //그래프 그리는 함수
void graphcar(double y[60]);										 //자동차 그래프 그리는 함수(값이 커 분리함)
void menu(int cur);													 //메인 메뉴
void mainmenu();													 //제목 출력하는 함수(많이 사용해 분리함)
void home();														 //홈으로 돌아가는 함수

int year[60];											//연도 배열
double gasoline[60], diesel[60], kerosene[60], car[60]; //각각의 데이터에 대한 배열
char strBuffer[260]={0, }, *pstrBuffer = NULL, msg[300];//현재 디렉터리 저장하는 배열
int main(){
	int temp=0, i;
	FILE *data = NULL;
	data = fopen("data/oildata2.csv", "r");//데이터 불러오기
	if (data !=NULL){
		fscanf(data, "%*[^\n]\n");//첫번째 행을 먼저 불러와서 두번째 행부터 인식하도록 함.
		while (!feof(data)){	  //파일의 끝에 도달할 때까지
			fscanf(data, "%d,%lf,%lf,%lf,%lf\n", &year[temp], &gasoline[temp], &diesel[temp], &kerosene[temp], &car[temp]);//각각의 값을 배열에 넣는다
			temp++;
		}
	}
	else{
		printf("Failed to open file. Please check.");//파일 열기 실패시 작동
		return -1;
	}
	fclose(data);
	pstrBuffer = getcwd(strBuffer, 260);//현재 디렉터리를 저장
	setup();//메뉴 선택하는 함수로 넘어감
	return 0;
}

void setup(){
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;//커서를 안보이게 하는 설정
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	system("mode con:cols=100 lines=26");//콘솔 창 사이즈 설정
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	SetConsoleTitle("전국 유가와 자동차 등록 대수 추세 분석 프로그램");//제목 설정
	system("cls");//화면 지움
	mainmenu();//제목 출력
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);//색상 반전!(Bin 1111 0000 이므로 배경색이 흰색, 글자색이 검정색)
	printf("[1]");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);//색상 반전!(Bin 0000 1111 이므로 배경색이 검정색, 글자색이 흰색)
	printf(" 데이터 보기\n");
	printf("[2] 데이터 분석\n");
	printf("[3] 나가기\n\n\n\n\n");
	int cur=1;//현재 흰 커서가 있는 위치
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
			key = _getch();//한번 더 입력 받음(위 화살표의 값은 224 72, 아래 화살표의 값은 224 80)
			switch (key){
				case 72://위 화살표 
					if (cur>1 && cur<=4) cur--;//커서를 위로
					break;
				case 80://아래 화살표
					if (cur>=0 && cur<3) cur++;//커서를 아래로
					break;
				}
		}
		menu(cur);//커서 색 변환 위한 함수
	}
}

void menu(int cur){//메뉴의 번호에 커서 표현하는 함수
	switch (cur){//각각의 케이스에 대해 색을 바꿈
		case 1:
			mainmenu();//제목 적는 함수
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);//색상 반전!(Bin 1111 0000 이므로 배경색이 흰색, 글자색이 검정색)
			printf("[1]");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);//색상 반전!(Bin 0000 1111 이므로 배경색이 검정색, 글자색이 흰색)
			printf(" 데이터 보기\n");
			printf("[2] 데이터 분석\n");
			printf("[3] 나가기\n\n\n\n\n");
			break;
		case 2:
			mainmenu();//제목 적는 함수
			printf("[1] 데이터 보기\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);//색상 반전!(Bin 1111 0000 이므로 배경색이 흰색, 글자색이 검정색)
			printf("[2]");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);//색상 반전!(Bin 0000 1111 이므로 배경색이 검정색, 글자색이 흰색)
			printf(" 데이터 분석\n");
			printf("[3] 나가기\n\n\n\n\n");
			break;
		case 3:
			mainmenu();//제목 적는 함수
			printf("[1] 데이터 보기\n");
			printf("[2] 데이터 분석\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);//색상 반전!(Bin 1111 0000 이므로 배경색이 흰색, 글자색이 검정색)
			printf("[3]");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);//색상 반전!(Bin 0000 1111 이므로 배경색이 검정색, 글자색이 흰색)
			printf(" 나가기\n\n\n\n\n");
			break;
		
	}
}

void dataShow(){//데이터 보여주는 함수
	mainmenu();//제목 적는 함수
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);//색상 반전!(Bin 1111 0000 이므로 배경색이 흰색, 글자색이 검정색)
	printf("[1]");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);//색상 반전!(Bin 0000 1111 이므로 배경색이 검정색, 글자색이 흰색)
	printf(" 가솔린 데이터\n");
	printf("[2] 디젤 데이터\n");
	printf("[3] 케로신 데이터\n");
	printf("[4] 자동차 데이터\n");
	printf("[5] 뒤로 가기\n\n\n\n\n");
	int cur=1;//현재 흰 커서가 있는 위치
	while(1){
		int key = _getch();//키 입력
		if (key == 224) {//방향키라면
			key = _getch();//한번 더 입력 받음(위 화살표의 값은 224 72, 아래 화살표의 값은 224 80)
			switch (key){
				case 72://위 화살표 
					if (cur>1 && cur<=6) cur--;//커서를 위로
					break;
				case 80://아래 화살표
					if (cur>=0 && cur<5) cur++;//커서를 아래로
					break;
				}
		}
		else if (key == 13){//엔터
			switch (cur){
				case 1:
					graph(gasoline);//gasoline에 대한 그래프 출력
					home();//홈으로 돌아가는 함수
					return;
					break;
				case 2:
					graph(diesel);//diesel에 대한 그래프 출력
					home();//홈으로 돌아가는 함수
					return;
					break;
				case 3:
					graph(kerosene);//kerosene에 대한 그래프 출력
					home();//홈으로 돌아가는 함수
					return;
					break;
				case 4:
					graphcar(car);//car에 대한 그래프 출력
					home();//홈으로 돌아가는 함수
					return;
					break;
				case 5:
					setup();//메인 메뉴로 돌아가는 함수
					return;
					break;
			}
		}
		dataAnisMenu(cur);//커서 색 변환 위한 함수
	}	
}

void dataAnis(){//데이터 분석 함수
	mainmenu();//제목 적는 함수
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);//색상 반전!(Bin 1111 0000 이므로 배경색이 흰색, 글자색이 검정색)
	printf("[1]");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);//색상 반전!(Bin 0000 1111 이므로 배경색이 검정색, 글자색이 흰색)
	printf(" 가솔린 데이터\n");
	printf("[2] 디젤 데이터\n");
	printf("[3] 케로신 데이터\n");
	printf("[4] 자동차 데이터\n");
	printf("[5] 뒤로 가기\n\n\n\n\n");
	int cur=1;//현재 흰 커서가 있는 위치
	int N=51;//데이터 개수
	double y[N]; //y축 데이터 갖는 함수
	while(1){
		int key = _getch();//키 입력
		if (key == 224) {//방향키라면
			key = _getch();//한번 더 입력 받음(위 화살표의 값은 224 72, 아래 화살표의 값은 224 80)
			switch (key){
				case 72://위 화살표 
					if (cur>1 && cur<=6) cur--;//커서를 위로
					break;
				case 80://아래 화살표
					if (cur>=0 && cur<5) cur++;//커서를 아래로
					break;
				}
		}
		else if (key == 13){//엔터
			switch (cur){
				case 1:
					for (int i=0; i<51; i++) y[i]=gasoline[i];//가솔린 선택하면, y 배열에 가솔린 배열 넣음
					dataAnisMain(N, y);//데이터 메인 분석 함수 호출
					home();//홈으로 가는 함수
					return;
					break;
				case 2:
					for (int i=0; i<51; i++) y[i]=diesel[i];//디젤 선택하면, y 배열에 디젤 배열 넣음
					dataAnisMain(N, y);//데이터 메인 분석 함수 호출
					home();//홈으로 가는 함수
					return;
					break;
				case 3:
					for (int i=0; i<51; i++) y[i]=kerosene[i];//케로신 선택하면, y 배열에 케로신 배열 넣음
					dataAnisMain(N, y);//데이터 메인 분석 함수 호출
					home();//홈으로 가는 함수
					return;
					break;
				case 4:
					for (int i=0; i<51; i++) y[i]=car[i];//자동차 선택하면, y 배열에 자동차 배열 넣음
					dataAnisMain(N, y);//데이터 메인 분석 함수 호출
					home();//홈으로 가는 함수
					return;
					break;
				case 5:
					setup();//메인 메뉴로 돌아가는 함수
					return;
					break;
			}
		}
		dataAnisMenu(cur);//커서 색 변환 위한 함수
	}
}

void dataAnisMain(int N, double y[1<<10]){//데이터를 분석하는 함수
	int n=0;//차수
	mainmenu();//제목 적는 함수
	printf("회귀할 데이터의 차수를 입력(0<n<11): ");//n차항 식으로 회귀할때, n을 받음
	scanf("%d", &n);
	while (n<1 || n>10){//예외 처리
		printf("\n다시 입력: ");
		fflush(stdin);//버퍼 비우기
		scanf("%d", &n);
	}
	int i, j;
	int x[60];//연도 배열
	for (int i=0; i<51; i++) x[i] = year[i];
	double X[2*n+1], Y[n+1], B[n+1][1<<10], A[n+1];
    for(i=0;i<=2*n;i++){
        X[i]=0;
        for(j=0;j<N;j++)X[i]=X[i]+pow(x[j],i);
    }     
    for(i=0;i<=n;i++){
        Y[i]=0;
        for(j=0;j<N;j++)Y[i]=Y[i]+pow(x[j],i)*y[j];
    }
    for(i=0;i<=n;i++){for(j=0;j<=n;j++)B[i][j]=X[i+j];}
    for(i=0;i<=n;i++) B[i][n+1]=Y[i];
    gaussEliminationLS(n+1,n+2,B,A);//가우스 소거법
    printf("%ex^%d",A[n],n);//회귀식 출력
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
				mainmenu();//제목 적는 함수
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);//색상 반전!(Bin 1111 0000 이므로 배경색이 흰색, 글자색이 검정색)
				printf("[1]");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);//색상 반전!(Bin 0000 1111 이므로 배경색이 검정색, 글자색이 흰색)
				printf(" 가솔린 데이터\n");
				printf("[2] 디젤 데이터\n");
				printf("[3] 케로신 데이터\n");
				printf("[4] 자동차 데이터\n");
				printf("[5] 뒤로 가기\n\n\n\n\n");
				break;
			case 2:
				mainmenu();//제목 적는 함수
				printf("[1] 가솔린 데이터\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);//색상 반전!(Bin 1111 0000 이므로 배경색이 흰색, 글자색이 검정색)
				printf("[2]");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);//색상 반전!(Bin 0000 1111 이므로 배경색이 검정색, 글자색이 흰색)
				printf(" 디젤 데이터\n");
				printf("[3] 케로신 데이터\n");
				printf("[4] 자동차 데이터\n");
				printf("[5] 뒤로 가기\n\n\n\n\n");
				break;
			case 3:
				mainmenu();//제목 적는 함수
				printf("[1] 가솔린 데이터\n");
				printf("[2] 디젤 데이터\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);//색상 반전!(Bin 1111 0000 이므로 배경색이 흰색, 글자색이 검정색)
				printf("[3]");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);//색상 반전!(Bin 0000 1111 이므로 배경색이 검정색, 글자색이 흰색)
				printf(" 케로신 데이터\n");
				printf("[4] 자동차 데이터\n");
				printf("[5] 뒤로 가기\n\n\n\n\n");
				break;
			case 4:
				mainmenu();//제목 적는 함수
				printf("[1] 가솔린 데이터\n");
				printf("[2] 디젤 데이터\n");
				printf("[3] 케로신 데이터\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);//색상 반전!(Bin 1111 0000 이므로 배경색이 흰색, 글자색이 검정색)
				printf("[4]");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);//색상 반전!(Bin 0000 1111 이므로 배경색이 검정색, 글자색이 흰색)
				printf(" 자동차 데이터\n");
				printf("[5] 뒤로 가기\n\n\n\n\n");
				break;
			case 5:
				mainmenu();//제목 적는 함수
				printf("[1] 가솔린 데이터\n");
				printf("[2] 디젤 데이터\n");
				printf("[3] 케로신 데이터\n");
				printf("[4] 자동차 데이터\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
				printf("[5]");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);//색상 반전!(Bin 0000 1111 이므로 배경색이 검정색, 글자색이 흰색)
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
            for(j=0;j<n;j++) a[k][j]=a[k][j]-term*a[i][j];
        }  
    }
    for(i=m-1;i>=0;i--){
        x[i]=a[i][n-1];
        for(j=i+1;j<n-1;j++) x[i]=x[i]-a[i][j]*x[j];
        x[i]=x[i]/a[i][i];
    }
             
}

void graph(double y[60]){//그래프 그리는 함수
	initwindow(640, 1000);//창 크기 설정
	line(0, 1000, 12, 1000-(int)y[1]/2);//첫번째 선 긋기
	for (int i=1;i<50;i++) line(i*12, 1000-(int)y[i]/2, (i+1)*12, 1000-(int)y[i+1]/2);//모든 선 긋기
    sprintf(msg, "%s\\main.exe", pstrBuffer);//msg에 현재 프로그램 위치 저장
	system(msg);//현재 프로그램 다시 실행(그래프 출력시 exit됨)
}

void graphcar(double y[60]){//자동차그래프 그리는 함수
	initwindow(640, 1000);//창 크기 설정
	line(0, 1000, 12, 1000-(int)y[1]/25000);//첫번째 선 긋기
	for (int i=1;i<50;i++) line(i*12, 1000-(int)y[i]/25000, (i+1)*12, 1000-(int)y[i+1]/25000);//모든 선 긋기
	sprintf(msg, "%s\\main.exe", pstrBuffer);//msg에 현재 프로그램 위치 저장
	system(msg);//현재 프로그램 다시 실행(그래프 출력시 exit됨)
}

void home(){//홈으로 돌아가는 함수
	printf("엔터를 눌러 홈으로 돌아가기");
	while (1){
		int key = _getch();//키 입력 받기
		if (key==13)setup();//엔터 누르면 홈으로
	}
	return;
}

void mainmenu(){//많이 사용되어 따로 빼둠
	system("cls");
	for (int i=0; i<100; i++) printf("=");
	printf("                         전국 유가와 자동차 등록 대수 추세 분석 프로그램\n\n\n\n\n");
}