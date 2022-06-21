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
	pstrBuffer = getcwd(strBuffer, 260);
	setup();
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
	system("cls");
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
		int key = _getch();//Ű �Է�
		if (key == 13){//����
			switch (cur){
				case 1:
					dataShow();//������ ���� �Լ�
					break;
				case 2:
					dataAnis();//������ �м� �Լ� 
					return;
					break;
				case 3:
					printf("Bye!");
					exit(0);//return���� ������ ���� �Լ�
					break;
			}
		}
		else if (key == 224) {//����Ű���
			key = _getch();//�ѹ� �� �Է� ����
			switch (key){
				case 72://�� ȭ��ǥ 
					if (cur>1 && cur<=4) cur--; 
					break;
				case 80://�Ʒ� ȭ��ǥ
					if (cur>=0 && cur<3) cur++; 
					break;
				}
		}
		menu(cur);//Ŀ�� �� ��ȯ ���� �Լ�
	}
}


void menu(int cur){
	int i;
	switch (cur){//������ ���̽��� ���� ���� �ٲ�
		case 1:
			mainmenu();//���� ���� �Լ�
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
			printf("[1]");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			printf(" ������ ����\n");
			printf("[2] ������ �м�\n");
			printf("[3] ������\n\n\n\n\n");
			break;
		case 2:
			mainmenu();
			printf("[1] ������ ����\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
			printf("[2]");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			printf(" ������ �м�\n");
			printf("[3] ������\n\n\n\n\n");
			break;
		case 3:
			mainmenu();
			printf("[1] ������ ����\n");
			printf("[2] ������ �м�\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
			printf("[3]");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			printf(" ������\n\n\n\n\n");
			break;
		
	}
}

void dataShow(){//������ �����ִ� �Լ�
	mainmenu();
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
					graph(gasoline);//gasoline�� ���� �׷��� ���
					home();//Ȩ���� ���ư��� �Լ�
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

void dataAnis(){//������ �м� �Լ�
	mainmenu();
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
					for (int i=0; i<51; i++) y[i]=gasoline[i];//���ָ� �����ϸ�, y �迭�� ���ָ� �迭 ����
					dataAnisMain(N, y);//������ ���� �м� �Լ� ȣ��
					home();//Ȩ���� ���� �Լ�
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
	printf("ȸ���� �������� ������ �Է�(0<n<11): ");//n���� ������ ȸ���Ҷ�, n�� ����
	scanf("%d", &n);
	while (n<1 || n>10){//���� ó��
		printf("\n�ٽ� �Է�: ");
		fflush(stdin);//���� ����
		scanf("%d", &n);
	}
	int i, j;
	int x[60];
	memcpy(x, year, sizeof(year));//�����ϰ� �迭 ���� ���� �޸� ����
	
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
    //ȸ�ͽ� ���
    printf("%ex^%d",A[n],n);
    for(i=n-1;i>0;i--){
    	if (A[i]>0) printf("+");
        printf("%ex^%d",A[i],i);
	}
	if (A[0]>0) printf("+");
	printf("%e\n",A[0]);
}

void dataAnisMenu(int cur){//������ �޴� ���� �Լ�
	switch (cur){
			case 1:
				mainmenu();
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
				mainmenu();
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
				mainmenu();
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
				mainmenu();
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
				mainmenu();
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

void gaussEliminationLS(int m, int n, double a[][1<<10], double x[]){//���콺 �ҰŹ�
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
void graph(double y[60]){//�׷��� �׸��� �Լ�
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
void graphcar(double y[60]){//�ڵ����׷��� �׸��� �Լ�
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
	printf("���͸� ���� Ȩ���� ���ư���");
	while (1){
		int key = _getch();
		if (key==13){//���� ������
			setup();//Ȩ����
		}
	}
	return;
}
void mainmenu(){//���� ���Ǿ� ���� ����
	int i;
	system("cls");
	for (i=0; i<100; i++) printf("=");
	printf("          ���� ��� ������ �ڵ��� ��� ����� ������� �� �ڵ��� ��� ��� ���� ���α׷�\n\n\n\n\n");
}