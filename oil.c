#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <memory.h>
#include <math.h>

void setup();
void dataShow();
void dataAnis();
void dataAnisMenu(int cur);
void dataAnisMain(int N, double y[N]);
void gaussEliminationLS(int m, int n, double a[m][n], double x[n-1]);
void gt(int x, int y);
void graph(double y[60]);
double mx(double x[60]);
double mi(double x[60]);
void menu(int cur);
void coordinatePlane();
int year[60];
void home();
double gasoline[60], diesel[60], kerosene[60];
double car[60];

int main(){
	int temp=0, i;
	
	FILE *data = NULL;
	data = fopen("data/oildata2.csv", "r");//������ �ҷ�����
	if (data !=NULL){
		fscanf(data, "%*[^\n]\n");//ù��° ���� ���� �ҷ��ͼ� �ι�° ����� �ν��ϵ��� ��.
		while (!feof(data)){
			fscanf(data, "%d,%lf,%lf,%lf,%lf\n", &year[temp], &gasoline[temp], &diesel[temp], &kerosene[temp], &car[temp]);//������ ���� �迭�� �ִ´�
			temp++;
		}
	}
	else{
		printf("Failed to open file. Please check.");//���� ���� ���н� �۵�
		return -1;
	}
	fclose(data);
	setup();//���� �Լ��� �Ѿ
	return 0;
}

void setup(){
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;//Ŀ���� �Ⱥ��̰� �ϴ� ����
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	system("mode con:cols=100 lines=26");//�ܼ� â ������ ����
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	SetConsoleTitle("2318 �ֵ���");//���� ����
	int i;
	for (i=0; i<100; i++) printf("=");
	printf("          ���� ��� ������ �ڵ��� ��� ����� ������� �� �ڵ��� ��� ��� ���� ���α׷�\n\n\n\n\n");
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);//���� ����!
	printf("[1]");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf(" ������ ����\n");
	printf("[2] ������ �м�\n");
	printf("[3] ������\n\n\n\n\n");
	
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
	int i;
	switch (cur){
		case 1:
			system("cls");
			for (i=0; i<100; i++) printf("=");
			printf("          ���� ��� ������ �ڵ��� ��� ����� ������� �� �ڵ��� ��� ��� ���� ���α׷�\n\n\n\n\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
			printf("[1]");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			printf(" ������ ����\n");
			printf("[2] ������ �м�\n");
			printf("[3] ������\n\n\n\n\n");
			break;
		case 2:
			system("cls");
			for (i=0; i<100; i++) printf("=");
			printf("          ���� ��� ������ �ڵ��� ��� ����� ������� �� �ڵ��� ��� ��� ���� ���α׷�\n\n\n\n\n");
			printf("[1] ������ ����\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
			printf("[2]");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			printf(" ������ �м�\n");
			printf("[3] ������\n\n\n\n\n");
			break;
		case 3:
			system("cls");
			for (i=0; i<100; i++) printf("=");
			printf("          ���� ��� ������ �ڵ��� ��� ����� ������� �� �ڵ��� ��� ��� ���� ���α׷�\n\n\n\n\n");
			printf("[1] ������ ����\n");
			printf("[2] ������ �м�\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
			printf("[3]");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			printf(" ������\n\n\n\n\n");
			break;
		
	}
}

void dataShow(){
	int i;
	system("cls");
	for (i=0; i<100; i++) printf("=");
	printf("          ���� ��� ������ �ڵ��� ��� ����� ������� �� �ڵ��� ��� ��� ���� ���α׷�\n\n\n\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
	printf("[1]");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf(" ���ָ� ������\n");
	printf("[2] ���� ������\n");
	printf("[3] �ɷν� ������\n");
	printf("[4] �ڵ��� ������\n");
	printf("[5] �ڷ� ����\n\n\n\n\n");
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
					coordinatePlane();
					graph(gasoline);
					home();
					return;
					break;
				case 2:
					coordinatePlane();
					graph(diesel);
					home();
					return;
					break;
				case 3:
					coordinatePlane();
					graph(kerosene);
					home();
					return;
					break;
				case 4:
					coordinatePlane();
					graph(car);
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

void dataAnis(){
	system("cls");
	int i;
	for (i=0; i<100; i++) printf("=");
	printf("          ���� ��� ������ �ڵ��� ��� ����� ������� �� �ڵ��� ��� ��� ���� ���α׷�\n\n\n\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
	printf("[1]");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf(" ���ָ� ������\n");
	printf("[2] ���� ������\n");
	printf("[3] �ɷν� ������\n");
	printf("[4] �ڵ��� ������\n");
	printf("[5] �ڷ� ����\n\n\n\n\n");
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
					home();
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

void dataAnisMain(int N, double y[N]){
	int n=0;
	system("cls");
	for (int i=0; i<100; i++) printf("=");
	printf("          ���� ��� ������ �ڵ��� ��� ����� ������� �� �ڵ��� ��� ��� ���� ���α׷�\n\n\n\n\n");
	printf("ȸ���� �������� ������ �Է�(0<n<11): ");
	scanf("%d", &n);
	while (n<1 || n>10){
		printf("\n�ٽ� �Է�: ");
		fflush(stdin);
		scanf("%d", &n);
	}
	int i, j;
	int x[60];
	memcpy(x, year, sizeof(year));
	
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
    gaussEliminationLS(n+1,n+2,B,A);
    printf("%ex^%d",A[n],n);
    for(i=n-1;i>0;i--){
    	if (A[i]>0) printf("+");
        printf("%ex^%d",A[i],i);
	}
	if (A[0]>0) printf("+");
	printf("%e\n",A[0]);
}

void dataAnisMenu(int cur){
	switch (cur){
			case 1:
				system("cls");
				for (int i=0; i<100; i++) printf("=");
				printf("          ���� ��� ������ �ڵ��� ��� ����� ������� �� �ڵ��� ��� ��� ���� ���α׷�\n\n\n\n\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
				printf("[1]");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				printf(" ���ָ� ������\n");
				printf("[2] ���� ������\n");
				printf("[3] �ɷν� ������\n");
				printf("[4] �ڵ��� ������\n");
				printf("[5] �ڷ� ����\n\n\n\n\n");
				break;
			case 2:
				system("cls");
				for (int i=0; i<100; i++) printf("=");
				printf("          ���� ��� ������ �ڵ��� ��� ����� ������� �� �ڵ��� ��� ��� ���� ���α׷�\n\n\n\n\n");
				printf("[1] ���ָ� ������\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
				printf("[2]");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				printf(" ���� ������\n");
				printf("[3] �ɷν� ������\n");
				printf("[4] �ڵ��� ������\n");
				printf("[5] �ڷ� ����\n\n\n\n\n");
				break;
			case 3:
				system("cls");
				for (int i=0; i<100; i++) printf("=");
				printf("          ���� ��� ������ �ڵ��� ��� ����� ������� �� �ڵ��� ��� ��� ���� ���α׷�\n\n\n\n\n");
				printf("[1] ���ָ� ������\n");
				printf("[2] ���� ������\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
				printf("[3]");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				printf(" �ɷν� ������\n");
				printf("[4] �ڵ��� ������\n");
				printf("[5] �ڷ� ����\n\n\n\n\n");
				break;
			case 4:
				system("cls");
				for (int i=0; i<100; i++) printf("=");
				printf("          ���� ��� ������ �ڵ��� ��� ����� ������� �� �ڵ��� ��� ��� ���� ���α׷�\n\n\n\n\n");
				printf("[1] ���ָ� ������\n");
				printf("[2] ���� ������\n");
				printf("[3] �ɷν� ������\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
				printf("[4]");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				printf(" �ڵ��� ������\n");
				printf("[5] �ڷ� ����\n\n\n\n\n");
				break;
			case 5:
				system("cls");
				for (int i=0; i<100; i++) printf("=");
				printf("          ���� ��� ������ �ڵ��� ��� ����� ������� �� �ڵ��� ��� ��� ���� ���α׷�\n\n\n\n\n");
				printf("[1] ���ָ� ������\n");
				printf("[2] ���� ������\n");
				printf("[3] �ɷν� ������\n");
				printf("[4] �ڵ��� ������\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
				printf("[5]");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				printf(" �ڷ� ����\n\n\n\n\n");
				break;
	}
}

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
            double term=a[k][i]/ a[i][i];
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

void coordinatePlane(){
	system("cls");
	for (int i=0; i<100; i++) printf("=");
	printf("          ���� ��� ������ �ڵ��� ��� ����� ������� �� �ڵ��� ��� ��� ���� ���α׷�\n\n\n");
	for (int i=0; i<20; i++) printf("��\n");
	printf("��");
	for (int i=2; i<100; i++) printf("��");
	
}

void gt(int x, int y){
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); 
}

double mx(double x[60]){
	double temp=x[0];
	for (int i=0; i<51; i++){
		if (x[i]>temp) temp = x[i];
	}
	return temp;
}
double mi(double x[60]){
	double temp=x[0];
	for (int i=0; i<51; i++){
		if (temp>x[i]) temp = x[i];
	}
	return temp;
}
void graph(double y[60]){
	double max = mx(y);
	double min = mi(y);
	int x[60]={0, };
	for (int i=0; i<51; i++){
		x[i]= ((y[i]-min)*20/(max-min))+0.5;
		gt(i+1, 23-x[i]);
		printf("*");
	}
	gt(0, 25);
}
void home(){
	printf("���͸� ���� Ȩ���� ���ư���");
	while (1){
		int key = _getch();
		if (key==13){
			setup();
		}
	}
	return;
}