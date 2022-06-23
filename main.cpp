/*#################################################################################################################################
#v8.5-beta1(Shorten code, Flicker-Free)     														  		 				 	  #
#����: ���� ������ �ڵ��� ��� ��� �߼� �м� ���α׷� 														  					  #
#�ۼ���: 2318 �ֵ���                                   														  					  #
#���� ���� ��ó: �ѱ��������� ���ǳ�(https://www.opinet.co.kr/user/opdown/opDownload.do)                      					  #
#�ڵ��� ��� ��� ��ó: ���û e-������ǥ(https://www.index.go.kr/potal/main/EachDtlPageDetail.do?idx_cd=1257)					  #
#32��Ʈ ȯ�濡�� ������ �� exe ���� ����																						  #
#���� �ִ� ��� ���ϰ� ���� ���̺귯�� ���� include�� �����Ϸ��� -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32 �߰� �� ������#
#################################################################################################################################*/

#include <stdio.h>
#include <conio.h>   //Ű �Է� �޴� _getch �Լ� ���
#include <math.h>    //���� ���
#include <graphics.h>//�׷��� ���
#include <unistd.h>  //���� ���͸� ����

void setup();                              					         //ù ȭ�鿡�� �޴� �����ϴ� �Լ�
void dataShow();													 //������ �����ִ� �Լ�
void dataAnis();													 //������ �м��ϴ� ������
void dataAnisMain(int N, double y[]);                                //������ �м��ϴ� �Լ�
void gaussEliminationLS(int m, int n, double a[][1<<10], double x[]);//���콺 �ҰŹ�
void graph(double y[60], int divider);								 //�׷��� �׸��� �Լ�
void mainmenu();													 //���� ����ϴ� �Լ�(���� ����� �и���)
void home();														 //Ȩ���� ���ư��� �Լ�
void specialmainmenu();                                              //Ư���� ����
void gtx(int x, int y);												 //gotoxy �Լ� 
void cursor(int x, int y);											 //Ŀ�� ��ġ�� �� ���� �Լ� 
void normalMenu();													 //�޴� �̸� ��� �Լ� 

int year[60];											//���� �迭
double gasoline[60], diesel[60], kerosene[60], car[60]; //������ �����Ϳ� ���� �迭
char strBuffer[260]={0, }, *pstrBuffer = NULL, msg[300], name[100], date[100], boool;//���� ���͸�, ���� �̸�, ���� ȭ�� ���� ���� �����ϴ� �迭

int main(){
	int temp=0, i;
	FILE *data = NULL;
	data = fopen("data/oildata2.csv", "r");//������ �ҷ�����
	if (data !=NULL){
		fscanf(data, "%*[^\n]\n");//ù��° ���� ���� �ҷ��ͼ� �ι�° ����� �ν��ϵ��� ��.
		while (!feof(data)){	  //������ ���� ������ ������
			fscanf(data, "%d,%lf,%lf,%lf,%lf\n", &year[temp], &gasoline[temp], &diesel[temp], &kerosene[temp], &car[temp]);//������ ���� �迭�� �ִ´�
			temp++;
		}
	}
	else{
		printf("Failed to open file. Please check.");//���� ���� ���н� �۵�
		return -1;
	}
	fclose(data);
	pstrBuffer = getcwd(strBuffer, 260);//���� ���͸��� ����
	setup();//�޴� �����ϴ� �Լ��� �Ѿ
	return 0;
}

void setup(){
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;//Ŀ���� �Ⱥ��̰� �ϴ� ����
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	system("mode con:cols=100 lines=26");//�ܼ� â ������ ����
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	SetConsoleTitle("���� ������ �ڵ��� ��� ��� �߼� �м� ���α׷�");//���� ����
	system("cls");//ȭ�� ����
	specialmainmenu();//Ư���� ���� ��� 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);//���� ����!(Bin 1111 0000 �̹Ƿ� ������ ���, ���ڻ��� ������)
	printf("[1]");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);//���� ����!(Bin 0000 1111 �̹Ƿ� ������ ������, ���ڻ��� ���)
	printf(" ������ ����\n");
	printf("[2] ������ �м�\n");
	printf("[3] ������\n\n\n\n\n");
	int cur=1;//���� �� Ŀ���� �ִ� ��ġ
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
			key = _getch();//�ѹ� �� �Է� ����(�� ȭ��ǥ�� ���� 224 72, �Ʒ� ȭ��ǥ�� ���� 224 80)
			switch (key){
				case 72://�� ȭ��ǥ 
					if (cur>1 && cur<=4) cur--;//Ŀ���� ����
					break;
				case 80://�Ʒ� ȭ��ǥ
					if (cur>=0 && cur<3) cur++;//Ŀ���� �Ʒ���
					break;
				}
		}
		cursor(cur, 3);
		gtx(0, 9);
	}
}

void dataShow(){//������ �����ִ� �Լ�
	mainmenu();//���� ���� �Լ�
	normalMenu();
	int cur=1;//���� �� Ŀ���� �ִ� ��ġ
	while(1){
		int key = _getch();//Ű �Է�
		if (key == 224) {//����Ű���
			key = _getch();//�ѹ� �� �Է� ����(�� ȭ��ǥ�� ���� 224 72, �Ʒ� ȭ��ǥ�� ���� 224 80)
			switch (key){
				case 72://�� ȭ��ǥ 
					if (cur>1 && cur<=6) cur--;//Ŀ���� ����
					break;
				case 80://�Ʒ� ȭ��ǥ
					if (cur>=0 && cur<5) cur++;//Ŀ���� �Ʒ���
					break;
				}
		}
		else if (key == 13){//����
			switch (cur){
				case 1:
					strcpy(name, "Gasoline");
					graph(gasoline, 2);//gasoline�� ���� �׷��� ���
					home();//Ȩ���� ���ư��� �Լ�
					return;
					break;
				case 2:
					strcpy(name, "Diesel");
					graph(diesel, 2);//diesel�� ���� �׷��� ���
					home();//Ȩ���� ���ư��� �Լ�
					return;
					break;
				case 3:
					strcpy(name, "Kerosene");
					graph(kerosene, 2);//kerosene�� ���� �׷��� ���
					home();//Ȩ���� ���ư��� �Լ�
					return;
					break;
				case 4:
					strcpy(name, "Car");
					graph(car, 25000);//car�� ���� �׷��� ���
					home();//Ȩ���� ���ư��� �Լ�
					return;
					break;
				case 5:
					setup();//���� �޴��� ���ư��� �Լ�
					return;
					break;
			}
		}
		cursor(cur, 5);
	}	
}

void dataAnis(){//������ �м� �Լ�
	mainmenu();//���� ���� �Լ�
	normalMenu();
	int cur=1;//���� �� Ŀ���� �ִ� ��ġ
	int N=51;//������ ����
	double y[N]; //y�� ������ ���� �Լ�
	while(1){
		int key = _getch();//Ű �Է�
		if (key == 224) {//����Ű���
			key = _getch();//�ѹ� �� �Է� ����(�� ȭ��ǥ�� ���� 224 72, �Ʒ� ȭ��ǥ�� ���� 224 80)
			switch (key){
				case 72://�� ȭ��ǥ 
					if (cur>1 && cur<=6) cur--;//Ŀ���� ����
					break;
				case 80://�Ʒ� ȭ��ǥ
					if (cur>=0 && cur<5) cur++;//Ŀ���� �Ʒ���
					break;
				}
		}
		else if (key == 13){//����
			switch (cur){
				case 1:
					for (int i=0; i<51; i++) y[i]=gasoline[i];//���ָ� �����ϸ�, y �迭�� ���ָ� �迭 ����
					dataAnisMain(N, y);//������ ���� �м� �Լ� ȣ��
					home();//Ȩ���� ���� �Լ�
					return;
					break;
				case 2:
					for (int i=0; i<51; i++) y[i]=diesel[i];//���� �����ϸ�, y �迭�� ���� �迭 ����
					dataAnisMain(N, y);//������ ���� �м� �Լ� ȣ��
					home();//Ȩ���� ���� �Լ�
					return;
					break;
				case 3:
					for (int i=0; i<51; i++) y[i]=kerosene[i];//�ɷν� �����ϸ�, y �迭�� �ɷν� �迭 ����
					dataAnisMain(N, y);//������ ���� �м� �Լ� ȣ��
					home();//Ȩ���� ���� �Լ�
					return;
					break;
				case 4:
					for (int i=0; i<51; i++) y[i]=car[i];//�ڵ��� �����ϸ�, y �迭�� �ڵ��� �迭 ����
					dataAnisMain(N, y);//������ ���� �м� �Լ� ȣ��
					home();//Ȩ���� ���� �Լ�
					return;
					break;
				case 5:
					setup();//���� �޴��� ���ư��� �Լ�
					return;
					break;
			}
		}
		cursor(cur, 5);
	}
}

void dataAnisMain(int N, double y[1<<10]){//�����͸� �м��ϴ� �Լ�
	int n=0;//����
	mainmenu();//���� ���� �Լ�
	printf("ȸ���� �������� ������ �Է�(0<n<11): ");//n���� ������ ȸ���Ҷ�, n�� ����
	scanf("%d", &n);
	while (n<1 || n>10){//���� ó��
		printf("\n�ٽ� �Է�: ");
		fflush(stdin);//���� ����
		scanf("%d", &n);
	}
	int i, j;
	int x[60];//���� �迭
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
    gaussEliminationLS(n+1,n+2,B,A);//���콺 �ҰŹ�
    printf("%ex^%d",A[n],n);//ȸ�ͽ� ���
    for(i=n-1;i>0;i--){
    	if (A[i]>0) printf("+");
        printf("%ex^%d",A[i],i);
	}
	if (A[0]>0) printf("+");
	printf("%e\n",A[0]);
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
            for(j=0;j<n;j++) a[k][j]=a[k][j]-term*a[i][j];
        }  
    }
    for(i=m-1;i>=0;i--){
        x[i]=a[i][n-1];
        for(j=i+1;j<n-1;j++) x[i]=x[i]-a[i][j]*x[j];
        x[i]=x[i]/a[i][i];
    }
             
}

void graph(double y[60], int divider){//�׷��� �׸��� �Լ�
	initwindow(640, 1000);//â ũ�� ����
	line(0, 1000, 12, 1000-(int)y[1]/divider);//ù��° �� �߱�
	for (int i=1;i<50;i++) line(i*12, 1000-(int)y[i]/divider, (i+1)*12, 1000-(int)y[i+1]/divider);//��� �� �߱�
	settextstyle(9,0,5);
	outtextxy(0, 0, name);//���� ��� ���� ��� 
	for (int i=0; i<100; i++) name[i]=0;//�迭 �ʱ�ȭ
    sprintf(msg, "%s\\main.exe", pstrBuffer);//msg�� ���� ���α׷� ��ġ ����
	system(msg);//���� ���α׷� �ٽ� ����(�׷��� ��½� exit��)
}

void home(){//Ȩ���� ���ư��� �Լ�
	printf("���͸� ���� Ȩ���� ���ư���");
	while (1){
		int key = _getch();//Ű �Է� �ޱ�
		if (key==13)setup();//���� ������ Ȩ����
	}
	return;
}

void mainmenu(){//���� ���Ǿ� ���� ����
	system("cls");
	for (int i=0; i<100; i++) {SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i%15); printf("=");}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("                         ���� ������ �ڵ��� ��� ��� �߼� �м� ���α׷�\n\n\n\n\n");
}

void specialmainmenu(){//Ư���� ���θ޴�
	if (!boool){ 
		system("cls");
		for (int i=0; i<100; i++) { delay(1); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i%15); printf("=");}
		printf("                         ");
		char title[100]={0, };
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		sprintf(title, "���� ������ �ڵ��� ��� ��� �߼� �м� ���α׷�");
		for(int i=0; title[i]; i++) {delay(1); printf("%c", title[i]);}
		printf("\n\n\n\n\n"); delay(1);
		boool=1;
	}
	else mainmenu();
}

void gtx(int x, int y){
	COORD pos={x,y};	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); 
}

void cursor(int x, int y){
	gtx(0, x+5);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);//���� ����!(Bin 1111 0000 �̹Ƿ� ������ ���, ���ڻ��� ������)
	printf("[%d]", x);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);//���� ����!(Bin 0000 1111 �̹Ƿ� ������ ������, ���ڻ��� ���)
	if (x!=1){
		gtx(0, x+4);
		printf("[%d]", x-1);
	}
	if (x!=y){
		gtx(0, x+6);
		printf("[%d]", x+1);
	}
}

void normalMenu(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);//���� ����!(Bin 1111 0000 �̹Ƿ� ������ ���, ���ڻ��� ������)
	printf("[1]");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);//���� ����!(Bin 0000 1111 �̹Ƿ� ������ ������, ���ڻ��� ���)
	printf(" ���ָ� ������\n");
	printf("[2] ���� ������\n");
	printf("[3] �ɷν� ������\n");
	printf("[4] �ڵ��� ������\n");
	printf("[5] �ڷ� ����\n\n\n\n\n");
}
