#include "graphics.h"
#include "myDifinitons.h"
#include <iostream>		 
#include <fstream>
#include "myQueue.h"
#include <ctime>
#include <stdio.h>
using namespace std;

typedef struct toado{
	int x, y;
}TOADO;

typedef struct Graph{
	int G[MAXSIZE][MAXSIZE];
	TOADO tdDinh[MAXSIZE];
	int soDinh;
}GRAPH;


char kiTu[26][2];
void initKiTu(char kiTu[][2]);																 		
void initGraph(GRAPH &g);																			
void initMenu();																					
void initCheck(bool check[], int n);
void textWrite(int &, int &, char[]);
void textWriteln(int &, int &, char[]);
void textWriteRemove(int &, int &, char[]);
void textReadNumber(int &, int &, char[]);
void textReadString(int &, int &, char[]);
void drawArrow(int dauX, int dauY, int cuoiX, int cuoiY, int color);									
double lenghLine(int x1, int y1, int x2, int y2);														
LUACHON checkClick(int, int);																			

// Các hàm chức năng chính
void drawVertexSelected(GRAPH &g);																		
void drawEdgeSelected(GRAPH &g);																		
void drawAdjMatrixSelected(GRAPH &g);	
void deleteVertexSelected(GRAPH &g);
void loadFileSelected(GRAPH &g, char fileName[]);
void saveFileSelected(GRAPH &g, char fileName[]);
void cleanGraphSelected(GRAPH &g);
void BFSSelected(GRAPH &g);
void DFSSelected(GRAPH &g);
void findPathTwoVertexSelected(GRAPH &g);
void findEulerCycleSelected(int u, GRAPH &g);
void findHamiltonCycleSelected(GRAPH &g);
void findSCCSelected(GRAPH &g);
void dijkstraAlgorithmSelected(GRAPH &g);
void timTruSelected(GRAPH &g);
void timCanhCauSelected(GRAPH &g);
void moveVertexSelected(GRAPH &g);

// Các hàm vẽ Button cho giao diện
void drawButton(int, int, int, int, int);
void drawButtonVertex(int color);
void drawButtonEdge(int color);
void drawButtonDeleteVertex(int color);
void drawButtonMove(int color);
void drawButtonSave(int color);
void drawButtonLoad(int color);
void drawButtonClean(int color);
void drawButtonBFS(int color);
void drawButtonDFS(int color);
void drawButtonTimTCDDi(int color);
void drawButtonFindSCC(int color);
void drawButtonDijkstra(int color);
void drawButtonTimTru(int color);
void drawButtonTimCCau(int color);
void drawButtonEuler(int color);
void drawButtonHamilton(int color);

// Các hàm hỗ trợ
void veCungHaiDinh(GRAPH &g, int dinhDau, int dinhCuoi, int color, int xcolor = 15);
void xoaCungHaiDinh(GRAPH &g, int dinhDau, int dinhCuoi, int color);
void drawGraph(GRAPH &g);
bool kiemTraDinhGanNhau(GRAPH &g, int x, int y);
void DFS(GRAPH &g, int v, bool check[], int &textX, int &textY);
void DFSAlgorithm(int G[][MAXSIZE], int soDinh, int u, bool check[]);
void findSCCDFS(int **G, TOADO tdDinh[], int soDinh, int v, bool check[], int &textX, int &textY, char kt[][2]);
void BFS(GRAPH &g, int v, bool check[], QUEUE &q, int &textX, int &textY);
void inDuongDiXY(int duongDi[], int dinh, GRAPH &g, int &dem);
void timDuongDi(int dinh, int dinhY, GRAPH &g, int duongDi[], bool check[], int &dem);
void SCC(int u, int &count, int &conponentCount, GRAPH &g, STACK L[], STACK &st, int low[], int numbering[]);
void SCC(int u, int &count, int &conponentCount, int **G, int n, STACK &st, int low[], int numbering[], bool check[]);
bool ktLTYeu(GRAPH &g);
bool ktEuler(GRAPH &g);
bool isHamiltonCycle(GRAPH &g);
void hamiltonAlgorithm(int pos,  GRAPH &g, int duongDi[], bool check[], bool &timDuocCT);
void veDinhTheoToaDo(int V, GRAPH &g, int color, int bgColor, int textColor);
int kiemtraClickDinh(GRAPH &g, int x, int y);
bool kiemTraMouseTrongKhungVe(int x, int y);
void help();

int main()
{
	initwindow(MAXX, MAXY, "GRAPH THEORY PROGRAM VER 1.1", 100, 0);
	initMenu();
	initKiTu(kiTu);
	LUACHON luaChon;
	char fileName[50];
	GRAPH g;
	initGraph(g);

	int clickLBDownX, clickLBDownY;
	while (1){
		if (ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, clickLBDownX, clickLBDownY);
			luaChon = checkClick(clickLBDownX, clickLBDownY);
			if (luaChon == VE_DINH){
				drawButtonVertex(LIGHTCYAN);
				drawVertexSelected(g);
				drawAdjMatrixSelected(g);
				drawButtonVertex(LIGHTBLUE);
			}
			else if (luaChon == VE_CANH){
				drawButtonEdge(LIGHTCYAN);
				drawEdgeSelected(g);
				drawAdjMatrixSelected(g);
				drawButtonEdge(LIGHTBLUE);
			}
			else if (luaChon == XOA_DINH){
				drawButtonDeleteVertex(LIGHTCYAN);
				deleteVertexSelected(g);
				drawAdjMatrixSelected(g);
				drawButtonDeleteVertex(LIGHTBLUE);
			}	
			else if (luaChon == DI_CHUYEN){
				drawButtonMove(LIGHTCYAN);
				moveVertexSelected(g);
				drawButtonMove(LIGHTBLUE);
			}
			else if (luaChon == LOAD_FILE){
				drawButtonLoad(LIGHTCYAN);
				loadFileSelected(g, fileName);
				setfillstyle(SOLID_FILL, DARKGRAY);
				bar(KHUNGVE_LEFT + 53, KHUNGVE_TOP + 1, KHUNGVE_RIGHT, KHUNGVE_BOTTOM - 1);
				drawAdjMatrixSelected(g);
				drawGraph(g);
				drawButtonLoad(LIGHTBLUE);
			}
			else if (luaChon == CLEAN){
				drawButtonClean(LIGHTCYAN);
				cleanGraphSelected(g);
				drawButtonClean(LIGHTBLUE);
			}
			else if (luaChon == SAVE_FILE){
				drawButtonSave(LIGHTCYAN);
				saveFileSelected(g, fileName);
				drawButtonSave(LIGHTBLUE);
			}
			else if (luaChon == DUYET_BFS){
				drawButtonBFS(LIGHTCYAN);
				BFSSelected(g);
				drawButtonBFS(LIGHTBLUE);
			}
			else if (luaChon == DUYET_DFS){
				drawButtonDFS(LIGHTCYAN);
				DFSSelected(g);
				drawButtonDFS(LIGHTBLUE);
			}
			else if (luaChon == ALL_PATH){
				drawButtonTimTCDDi(LIGHTCYAN);
				findPathTwoVertexSelected(g);
				drawButtonTimTCDDi(LIGHTBLUE);

			}
			else if (luaChon == FIND_SCC){
				drawButtonFindSCC(LIGHTCYAN);
				findSCCSelected(g);
				drawButtonFindSCC(LIGHTBLUE);
			}
			else if (luaChon == DIJKSTRA_ALG){
				drawButtonDijkstra(LIGHTCYAN);
				dijkstraAlgorithmSelected(g);
				drawButtonDijkstra(LIGHTBLUE);
			}
			else if (luaChon == TIM_TRU){
				drawButtonTimTru(LIGHTCYAN);
				timTruSelected(g);
				drawButtonTimTru(LIGHTBLUE);
			}
			else if (luaChon == TIM_CCAU){
				drawButtonTimCCau(LIGHTCYAN);
				timCanhCauSelected(g);
				drawButtonTimCCau(LIGHTBLUE);
			}
			else if (luaChon == EULER){
				srand(time(NULL));
				drawButtonEuler(LIGHTCYAN);
				int x = 1;
				if (g.soDinh > 0) x = rand() % g.soDinh + 1; 
				findEulerCycleSelected(x, g);
				drawButtonEuler(LIGHTBLUE);
			}
			else if (luaChon == HAMILTON){
				srand(time(NULL));
				drawButtonHamilton(LIGHTCYAN);
				findHamiltonCycleSelected(g);
				drawButtonHamilton(LIGHTBLUE);
			}
		}
	}
	return 0;
}

void initGraph(GRAPH &g){
	g.soDinh = 0;
	for (int i = 1; i <= MAXSIZE; i++){
		for (int j = 1; j <= MAXSIZE; j++){
			g.G[i][j] = 0;
		}
	}
}

void initMenu(){
	setbkcolor(LIGHTGRAY);
	cleardevice();

	setfillstyle(SOLID_FILL, DARKGRAY);
	setcolor(BLACK);

	// Khung vẽ đồ thị
	bar(KHUNGVE_LEFT, KHUNGVE_TOP, KHUNGVE_RIGHT, KHUNGVE_BOTTOM );
	rectangle(KHUNGVE_LEFT, KHUNGVE_TOP, KHUNGVE_RIGHT, KHUNGVE_BOTTOM );
	line(KHUNGVE_LEFT + 52, KHUNGVE_TOP, KHUNGVE_LEFT + 52, KHUNGVE_BOTTOM);
	
	// Khung Menu
	rectangle(0, KHUNGVE_TOP, KHUNGVE_LEFT - 20, BTN_DIJKSTRA_BOTTOM + 10 );
	outtextxy(10, KHUNGVE_TOP - 10, "MENU");
	
	//Khung ma tran ke
	rectangle(0, BTN_DIJKSTRA_BOTTOM + 30, KHUNGVE_LEFT - 20, KHUNGVE_BOTTOM);
	outtextxy(10, BTN_DIJKSTRA_BOTTOM + 20, "ADJACENCY MATRIX");

	// Khung LOG					  
	rectangle(LOG_LEFT, LOG_TOP, LOG_RIGHT , LOG_BOTTOM);
	outtextxy(LOG_LEFT + 10, LOG_TOP - 10, "LOG");

	// Khung help
	rectangle(HELP_LEFT, HELP_TOP, HELP_RIGHT, HELP_BOTTOM);
	outtextxy(HELP_LEFT + 380, HELP_TOP + 10, "DESIGN & DEVELOPMENT BY TUAN ANH LE");
	
	// Vẽ button "Vẽ đồ thị "
	drawButtonVertex(LIGHTBLUE);
	//Vẽ button "Vẽ cạnh và trong số"
	drawButtonEdge(LIGHTBLUE);
	//Vẽ button Xóa đỉnh
	drawButtonDeleteVertex(LIGHTBLUE);
	//Ve Button di chuyen dinh
	drawButtonMove(LIGHTBLUE);
	//Ve Button Save File
	drawButtonSave(LIGHTBLUE);
	//Ve Button Load File
	drawButtonLoad(LIGHTBLUE);
	drawButtonClean(LIGHTBLUE);
	
	//Menu Button
	drawButtonBFS(LIGHTBLUE);
	drawButtonDFS(LIGHTBLUE);
	drawButtonTimTCDDi(LIGHTBLUE);
	drawButtonFindSCC(LIGHTBLUE);
	drawButtonDijkstra(LIGHTBLUE);
	drawButtonTimTru(LIGHTBLUE);
	drawButtonTimCCau(LIGHTBLUE);
	drawButtonEuler(LIGHTBLUE);
	drawButtonHamilton(LIGHTBLUE);

}


void drawAdjMatrixSelected(GRAPH &g){
	setcolor(BLACK);
	setbkcolor(LIGHTGRAY);
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	bar(10, BTN_DIJKSTRA_BOTTOM + 35, KHUNGVE_LEFT - 21, KHUNGVE_BOTTOM - 2);

	int n = g.soDinh;
	if (n == 0)	 return;
	rectangle(MTK_LEFT, MTK_TOP, MTK_RIGHT, MTK_BOTTOM);
	int xNgang1 = MTK_LEFT, xNgang2 = MTK_RIGHT, yNgang = MTK_BOTTOM;
	int doRong = (MTK_RIGHT - MTK_LEFT) / n;
	int nuaDoRong = doRong / 2;
	int yDoc1 = MTK_TOP, yDoc2 = MTK_BOTTOM + (20 * n);
	int xDoc = MTK_LEFT;
	line(xDoc, yDoc1, xDoc, yDoc2);
	char trongSo[5];
	int xText;

	for (int i = 1; i <= n; i++){
		// In các đường ngang
		xText = MTK_LEFT + nuaDoRong;
		for (int j = 1; j <= n; j++){
			if (g.G[i][j] != 0){
				_itoa(g.G[i][j], trongSo, 10);
				outtextxy(xText, yNgang + 3, trongSo);
			}
			xText += doRong;
		}
		yNgang += 20;
		line(xNgang1, yNgang, xNgang2, yNgang);
		// In các đường dọc
		xDoc += doRong;
		outtextxy(xDoc - nuaDoRong, yDoc1 + 3, kiTu[i]);
		if (i != n){
			line(xDoc, yDoc1, xDoc, yDoc2);
		}
	}
	line(MTK_RIGHT, MTK_BOTTOM, MTK_RIGHT, yDoc2);
}

void textWrite(int &x, int &y, char s[]){
	outtextxy(x, y, s);
	x += textwidth(s);
}
void textWriteRemove(int &x, int &y, char s[]){
	setcolor(LIGHTGRAY);
	x -= textwidth(s);
	outtextxy(x, y, s);
}
void textWriteln(int &x, int &y, char s[]){
	outtextxy(x, y, s);
	x = 5;
	y += textheight("A");
}
void textReadNumber(int &x, int &y, char s[]){
	char ch[2];
	char temp;
	ch[1] = 0;
	int i = 0;
	while (1){
		fflush(stdin);
		setcolor(RED);
		temp = getch();
		if (temp >= '0' && temp <= '9'){
			ch[0] = temp;
			textWrite(x, y, ch);
			s[i++] = ch[0];
		}
		else if (temp == 8 && i > 0){
			textWriteRemove(x, y, ch);
			i--;
		}
		else if (temp == 13) break;
	}
	s[i] = 0;
}

void textReadString(int &x, int &y, char s[]){
	char ch[2];
	char temp;
	ch[1] = 0;
	int i = 0;
	while (1){
		fflush(stdin);
		setcolor(RED);
		temp = getch();
		if (temp == 8 && i > 0){
			textWriteRemove(x, y, ch);
			i--;
		}	 
		else if (temp == 13) break;
		else{
			ch[0] = temp;
			textWrite(x, y, ch);
			s[i++] = ch[0];
		}
	}
	s[i] = 0;
}
/*Hàm vẽ mũi tên*/
void drawArrow(int dauX, int dauY, int cuoiX, int cuoiY, int color){
	double x1, x2, y1, y2, x3, y3;
	double arrowLenght = 30, arrowDegrees = 0.3;
	double angle = atan2(cuoiY - dauY, cuoiX - dauX) + M_PI;

	// Xác định 3 đỉnh của tam giác - mũi tên
	x1 = cuoiX + arrowLenght * cos(angle - arrowDegrees);
	y1 = cuoiY + arrowLenght * sin(angle - arrowDegrees);
	x2 = cuoiX + arrowLenght * cos(angle + arrowDegrees);
	y2 = cuoiY + arrowLenght * sin(angle + arrowDegrees);

	// Đỉnh mũi tên sẽ lùi têm 20 pixel do đỉnh cuối là tâm của hình tròn
	x3 = cuoiX + 20 * cos(angle);		 
	y3 = cuoiY + 20 * sin(angle);

	int x4 = (x1 + x2 + x3) / 3;
	int y4 = (y1 + y2 + y3) / 3;
	int arr[] = { x1, y1, x2, y2, x3, y3, x1, y1 };	

	/*Tô lại màu trắng	*/
	setcolor(color);
	setfillstyle(SOLID_FILL, color);
	fillpoly(4, arr);
}

double lenghLine(int x1, int y1, int x2, int y2){
	return sqrt(double(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

void veCungHaiDinh(GRAPH &g, int dinhDau, int dinhCuoi, int color, int xcolor ){
	int x1 = g.tdDinh[dinhDau].x, y1 = g.tdDinh[dinhDau].y;
	int x2 = g.tdDinh[dinhCuoi].x, y2 = g.tdDinh[dinhCuoi].y;

	if (g.G[dinhCuoi][dinhDau] == 0){
		char trongSo[4];
		setcolor(color);
		line(x1, y1, x2, y2);
		drawArrow(x1, y1, x2, y2, color);

		setfillstyle(SOLID_FILL, GREEN);
		/*Tô lại màu cho 2 đỉnh để che đi đường thẳng bên trong*/
		//Đỉnh 1
		setcolor(BLACK);
		circle(x1, y1, R);
		floodfill(x1, y1, BLACK);

		setcolor(GREEN);
		circle(x1, y1, R);
		floodfill(x1, y1, GREEN);
		setcolor(RED);
		setbkcolor(GREEN);
		outtextxy(x1 - 5, y1 - 5, kiTu[dinhDau]);

		// Đỉnh 2
		setcolor(BLACK);
		circle(x2, y2, R);
		floodfill(x2, y2, BLACK);

		setcolor(GREEN);
		circle(x2, y2, R);
		floodfill(x2, y2, GREEN);
		setcolor(RED);
		setbkcolor(GREEN);
		outtextxy(x2 - 5, y2 - 5, kiTu[dinhCuoi]);
		//
		setbkcolor(DARKGRAY);
		setcolor(DARKGRAY);
		outtextxy((x1 + x2) / 2 + 15, (y1 + y2) / 2 + 5, "AA");

		/*In trọng số*/
		setcolor(color);
		_itoa(g.G[dinhDau][dinhCuoi], trongSo, 10);
		outtextxy((x1 + x2) / 2 + 15, (y1 + y2) / 2 + 5, trongSo);
	}
	else{

		char trongSo[4];
		setbkcolor(DARKGRAY);
		setcolor(DARKGRAY);
		line(x2, y2, x1, y1);
		drawArrow(x2, y2, x1, y1,DARKGRAY);
		_itoa(g.G[dinhCuoi][dinhDau], trongSo, 10);
		outtextxy((x1 + x2) / 2 + 15, (y1 + y2) / 2 + 5, trongSo);

		double arrow_lenght_(8), arrow_degrees_(M_PI / 2);
		double angle = atan2(y2 - y1, x2 - x1) + M_PI;
		int xtemp1 = x1 + arrow_lenght_ * cos(angle - arrow_degrees_);
		int ytemp1 = y1 + arrow_lenght_ * sin(angle - arrow_degrees_);
		int xtemp2 = x2 + arrow_lenght_ * cos(angle - arrow_degrees_);
		int ytemp2 = y2 + arrow_lenght_ * sin(angle - arrow_degrees_);

		// Vẽ lại đường thẳng nối từ Cuoi -> dau
		setcolor(xcolor);
		line(xtemp2, ytemp2, xtemp1, ytemp1);
		drawArrow(xtemp2, ytemp2, xtemp1, ytemp1, xcolor);
		_itoa(g.G[dinhCuoi][dinhDau], trongSo, 10);
		outtextxy((xtemp1 + xtemp2) / 2, (ytemp1 + ytemp2) / 2, trongSo);

		// Vẽ lại đường thẳng nối từ Dau -> cuoi
		xtemp1 = x1 + arrow_lenght_ * cos(angle + arrow_degrees_);
		ytemp1 = y1 + arrow_lenght_ * sin(angle + arrow_degrees_);
		xtemp2 = x2 + arrow_lenght_ * cos(angle + arrow_degrees_);
		ytemp2 = y2 + arrow_lenght_ * sin(angle + arrow_degrees_);

		setcolor(color);
		line(xtemp1, ytemp1, xtemp2, ytemp2);
		drawArrow(xtemp1, ytemp1, xtemp2, ytemp2, color);
		_itoa(g.G[dinhDau][dinhCuoi], trongSo, 10);
		outtextxy((xtemp1 + xtemp2) / 2, (ytemp1 + ytemp2) / 2, trongSo);

		/*Tô lại màu cho 2 đỉnh để che đi đường thẳng bên trong*/
		setfillstyle(SOLID_FILL, GREEN);
		//Đỉnh 1
		setcolor(YELLOW);
		circle(x1, y1, R);
		floodfill(x1, y1, YELLOW);
		setcolor(GREEN);
		circle(x1, y1, R);
		floodfill(x1, y1, GREEN);
		setcolor(RED);
		setbkcolor(GREEN);
		outtextxy(x1 - 5, y1 - 5, kiTu[dinhDau]);

		// Đỉnh 2
		setcolor(YELLOW);
		circle(x2, y2, R);
		floodfill(x2, y2, YELLOW);
		setcolor(GREEN);
		circle(x2, y2, R);
		floodfill(x2, y2, GREEN);
		setcolor(RED);
		setbkcolor(GREEN);
		outtextxy(x2 - 5, y2 - 5, kiTu[dinhCuoi]);
	}

}

void initKiTu(char kiTu[][2]){
	for (int i = 1, j = 65; i < 26; i++, j++){
		kiTu[i][0] = j;
		kiTu[i][1] = 0;
	}
}

LUACHON checkClick(int clickLBDownX, int clickLBDownY){
	if (clickLBDownX >= BTN_VEDINH_LEFT && clickLBDownX <= BTN_VEDINH_RIGHT &&
		clickLBDownY >= BTN_VEDINH_TOP && clickLBDownY <= BTN_VEDINH_BOTTOM){
		return VE_DINH;
	}
	if (clickLBDownX >= BTN_VECANH_LEFT && clickLBDownX <= BTN_VECANH_RIGHT &&
		clickLBDownY >= BTN_VECANH_TOP && clickLBDownY <= BTN_VECANH_BOTTOM){
		return VE_CANH;
	}
	if (clickLBDownX >= BTN_XOADINH_LEFT && clickLBDownX <= BTN_XOADINH_RIGHT &&
		clickLBDownY >= BTN_XOADINH_TOP && clickLBDownY <= BTN_XOADINH_BOTTOM){
		return XOA_DINH;
	}
	if (clickLBDownX >= BTN_DICHUYEN_LEFT && clickLBDownX <= BTN_DICHUYEN_RIGHT &&
		clickLBDownY >= BTN_DICHUYEN_TOP && clickLBDownY <= BTN_DICHUYEN_BOTTOM){
		return DI_CHUYEN;
	}
	if (clickLBDownX >= BTN_SAVEFILE_LEFT && clickLBDownX <= BTN_SAVEFILE_RIGHT &&
		clickLBDownY >= BTN_SAVEFILE_TOP && clickLBDownY <= BTN_SAVEFILE_BOTTOM){
		return SAVE_FILE;
	}
	if (clickLBDownX >= BTN_LOADFILE_LEFT && clickLBDownX <= BTN_LOADFILE_RIGHT &&
		clickLBDownY >= BTN_LOADFILE_TOP && clickLBDownY <= BTN_LOADFILE_BOTTOM){
		return LOAD_FILE;
	}
	if (clickLBDownX >= BTN_CLEANALL_LEFT && clickLBDownX <= BTN_CLEANALL_RIGHT &&
		clickLBDownY >= BTN_CLEANALL_TOP && clickLBDownY <= BTN_CLEANALL_BOTTOM){
		return CLEAN;
	}
	if (clickLBDownX >= BTN_BFS_LEFT && clickLBDownX <= BTN_BFS_RIGHT &&
		clickLBDownY >= BTN_BFS_TOP && clickLBDownY <= BTN_BFS_BOTTOM){
		return DUYET_BFS;
	}
	if (clickLBDownX >= BTN_DFS_LEFT && clickLBDownX <= BTN_DFS_RIGHT &&
		clickLBDownY >= BTN_DFS_TOP && clickLBDownY <= BTN_DFS_BOTTOM){
		return DUYET_DFS;
	}
	if (clickLBDownX >= BTN_TIMTCDDI_LEFT && clickLBDownX <= BTN_TIMTCDDI_RIGHT &&
		clickLBDownY >= BTN_TIMTCDDI_TOP &&	clickLBDownY <= BTN_TIMTCDDI_BOTTOM){
		return ALL_PATH;
	}
	if (clickLBDownX >= BTN_SCC_LEFT && clickLBDownX <= BTN_SCC_RIGHT &&
		clickLBDownY >= BTN_SCC_TOP &&	clickLBDownY <= BTN_SCC_BOTTOM){
		return FIND_SCC;
	}
	if (clickLBDownX >= BTN_DIJKSTRA_LEFT && clickLBDownX <= BTN_DIJKSTRA_RIGHT &&
		clickLBDownY >= BTN_DIJKSTRA_TOP &&	clickLBDownY <= BTN_DIJKSTRA_BOTTOM)   {
		return DIJKSTRA_ALG;
	}
	if (clickLBDownX >= BTN_TIMTRU_LEFT && clickLBDownX <= BTN_TIMTRU_RIGHT &&
		clickLBDownY >= BTN_TIMTRU_TOP &&	clickLBDownY <= BTN_TIMTRU_BOTTOM)   {
		return TIM_TRU;
	}
	if (clickLBDownX >= BTN_CANHCAU_LEFT && clickLBDownX <= BTN_CANHCAU_RIGHT &&
		clickLBDownY >= BTN_CANHCAU_TOP &&	clickLBDownY <= BTN_CANHCAU_BOTTOM)   {
		return TIM_CCAU;
	}
	if (clickLBDownX >= BTN_EULER_LEFT && clickLBDownX <= BTN_EULER_RIGHT &&
		clickLBDownY >= BTN_EULER_TOP &&	clickLBDownY <= BTN_EULER_BOTTOM)   {
		return EULER;
	}
	if (clickLBDownX >= BTN_HAMILTON_LEFT && clickLBDownX <= BTN_HAMILTON_RIGHT &&
		clickLBDownY >= BTN_HAMILTON_TOP &&	clickLBDownY <= BTN_HAMILTON_BOTTOM)   {
		return HAMILTON;
	}
	return NON;
}

void drawButton(int x1, int y1, int x2, int y2, int color){
	setcolor(BLACK);
	setfillstyle(SOLID_FILL, color);
	bar(x1, y1, x2, y2);
	rectangle(x1 - 1, y1 - 1, x2 + 1, y2 + 1);
}

void drawVertexSelected(GRAPH &g){
	setbkcolor(GREEN);
	setfillstyle(SOLID_FILL, GREEN);
	int tempX, tempY;
	while (g.soDinh < 10){
		while (kbhit()){
			if (char a = getch() == 13) return;
		}
		if (ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, tempX, tempY);
			if (checkClick(tempX, tempY) == VE_DINH) return;

			//Kiểm tra điểm nằm trong khung vẽ
			else if (tempX >= (KHUNGVE_LEFT + 55 + R) && tempX <= KHUNGVE_RIGHT - R &&
					tempY >= KHUNGVE_TOP + R && tempY <= KHUNGVE_BOTTOM - R){
					if (kiemTraDinhGanNhau(g, tempX, tempY) == false){
						g.soDinh++;
						g.tdDinh[g.soDinh].x = tempX, g.tdDinh[g.soDinh].y = tempY;
						//Vẽ đỉnh tại điểm chọn
						setcolor(GREEN);
						circle(g.tdDinh[g.soDinh].x, g.tdDinh[g.soDinh].y, R);
						floodfill(g.tdDinh[g.soDinh].x, g.tdDinh[g.soDinh].y, GREEN);
						setcolor(RED);
						outtextxy(g.tdDinh[g.soDinh].x - 5, g.tdDinh[g.soDinh].y - 5, kiTu[g.soDinh]);
					}
			}
		}
	}
}

void drawEdgeSelected(GRAPH &g){
	int kiemTraClickLeft = 0;
	int textX = 5, textY = KHUNGVE_BOTTOM + 30;
	int dinhDau = 0, dinhCuoi = 0;
	char s[10];
	int xtemp, ytemp;
	int soLanVe = 0;
	TOADO tdHaiDiemChon[3];
	if (g.soDinh == 0){
		setcolor(RED);
		setbkcolor(LIGHTGRAY);
		outtextxy(textX, textY, "CHUA TON TAI DINH!!!");
		textX = 5, textY = KHUNGVE_BOTTOM + 30;
		delay(700);
		setcolor(LIGHTGRAY);
		outtextxy(textX, textY, "CHUA TON TAI DINH!!!");
		return;
	}
	while (1){
		while (kbhit()){
			if (char a = getch() == 13 && kiemTraClickLeft != 1){
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(LOG_LEFT + 2, LOG_TOP + 10, LOG_RIGHT, LOG_BOTTOM);
				textX = 5, textY = KHUNGVE_BOTTOM + 30;
				return;
			}
		}
		// Vẽ cung khi chọn được 2 điểm
		if (kiemTraClickLeft == 2){
			soLanVe++;
			int tempTextX = textX;
			int tempTextY = textY;
			setbkcolor(LIGHTGRAY);
			setcolor(RED);
			textWrite(textX, textY, "NHAP VAO TRONG SO ");
			char *a = new char[6];
			strcpy(a, "");
			strcat(a, &kiTu[dinhDau][0]);
			strcat(a, "->");
			strcat(a, &kiTu[dinhCuoi][0]);
			strcat(a, ":");
			textWrite(textX, textY, a);

			/*Nhập vào trọng số*/
			textReadNumber(textX, textY, s);
			textWriteln(textX, textY, "");

			// Set ki tu thanh mau den
			setcolor(BLACK);
			textWrite(tempTextX, tempTextY, "NHAP VAO TRONG SO ");
			textWrite(tempTextX, tempTextY, a);
			textWrite(tempTextX, tempTextY, s);
			
			g.G[dinhDau][dinhCuoi] = atoi(s);

			/*Vẽ cung*/
			if (g.G[dinhDau][dinhCuoi] != 0)
				veCungHaiDinh(g, dinhDau, dinhCuoi, WHITE);
			else  {
				xoaCungHaiDinh(g, dinhDau, dinhCuoi, WHITE);
				g.G[dinhDau][dinhCuoi] = 0;
			}

			/*Đưa kiemTraClick về 0*/
			kiemTraClickLeft = 0;
			dinhDau = 0, dinhCuoi = 0;

			if (soLanVe == 9){
				textX = 5;
				textY = KHUNGVE_BOTTOM + 30;
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(LOG_LEFT + 2, LOG_TOP + 10, LOG_RIGHT, LOG_BOTTOM);
				soLanVe = 0;
			}
		}

		if (ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, xtemp, ytemp);
			if (checkClick(xtemp, ytemp) == VE_CANH){
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(LOG_LEFT + 2, LOG_TOP + 10, LOG_RIGHT, LOG_BOTTOM);
				textX = 5, textY = KHUNGVE_BOTTOM + 30;
				return;
			}
			else {
				for (int i = 1; i <= g.soDinh; i++){
					if (lenghLine(g.tdDinh[i].x, g.tdDinh[i].y, xtemp, ytemp) <= R){
						kiemTraClickLeft++;
						tdHaiDiemChon[kiemTraClickLeft].x = g.tdDinh[i].x;
						tdHaiDiemChon[kiemTraClickLeft].y = g.tdDinh[i].y;
						if (dinhDau == 0) {
							dinhDau = i;
							setfillstyle(SOLID_FILL, LIGHTGREEN);
							setcolor(LIGHTGREEN);
							circle(g.tdDinh[dinhDau].x, g.tdDinh[dinhDau].y, R);
							floodfill(g.tdDinh[dinhDau].x, g.tdDinh[dinhDau].y, LIGHTGREEN);
							setcolor(RED);
							setbkcolor(LIGHTGREEN);
							outtextxy(g.tdDinh[dinhDau].x - 5, g.tdDinh[dinhDau].y - 5, kiTu[dinhDau]);	
						}
						else if (i != dinhDau){ 
							dinhCuoi = i; 
							setfillstyle(SOLID_FILL, LIGHTGREEN);
							setcolor(LIGHTGREEN);
							circle(g.tdDinh[dinhCuoi].x, g.tdDinh[dinhCuoi].y, R);
							floodfill(g.tdDinh[dinhCuoi].x, g.tdDinh[dinhCuoi].y, LIGHTGREEN);
							setcolor(RED);
							setbkcolor(LIGHTGREEN);
							outtextxy(g.tdDinh[dinhCuoi].x - 5, g.tdDinh[dinhCuoi].y - 5, kiTu[dinhCuoi]);
						}
						else if (dinhDau == i) kiemTraClickLeft--;
					}
				}
			}
		}
	}
}
void deleteVertexSelected(GRAPH &g){
	int x, y;
	int vitriXoa = -1;
	while (1){
		while (kbhit()){
			if (char a = getch() == 13) return;
		}
		if (ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if (checkClick(x, y) == XOA_DINH) return;
			for (int i = 1; i <= g.soDinh; i++){
				if (lenghLine(g.tdDinh[i].x, g.tdDinh[i].y, x, y) <= R){
					vitriXoa = i;
					break;
				}
			}
			if (vitriXoa != -1){
				//Xóa khung vẽ 
				setfillstyle(SOLID_FILL, DARKGRAY);
				bar(KHUNGVE_LEFT + 53, KHUNGVE_TOP + 1, KHUNGVE_RIGHT, KHUNGVE_BOTTOM - 1);

				//Thay đổi ma trận kề Và tọa độ đỉnh
				for (int i = 1; i <= g.soDinh; i++){
					for (int j = vitriXoa; j < g.soDinh; j++){
						g.G[i][j] = g.G[i][j + 1];
					}
					g.G[i][g.soDinh] = 0;
				}
				for (int i = vitriXoa; i < g.soDinh; i++){
					for (int j = 1; j < g.soDinh; j++){
						g.G[i][j] = g.G[i + 1][j];
					}
					g.tdDinh[i].x = g.tdDinh[i + 1].x;
					g.tdDinh[i].y = g.tdDinh[i + 1].y;
				}
				for (int j = 1; j < g.soDinh; j++){
					g.G[g.soDinh][j] = 0;
				}
				
				g.tdDinh[g.soDinh].x = 0;
				g.tdDinh[g.soDinh].y = 0;
				g.soDinh--;

				bool check = false;
				for (int i = 1; i <= g.soDinh; i++){
					for (int j = 1; j <= g.soDinh; j++){
						if (g.G[i][j] != 0) {
							check = true;
							break;
						}
					}
				}
				
				if (check){
					//Vẽ lại Đồ thị mới
					drawGraph(g);
				}
				else if (g.soDinh > 0){
					setfillstyle(SOLID_FILL, GREEN);
					for (int i = 1; i <= g.soDinh; i++){
						setcolor(GREEN);
						circle(g.tdDinh[i].x, g.tdDinh[i].y, R);
						floodfill(g.tdDinh[i].x, g.tdDinh[i].y, GREEN);
						setcolor(RED);
						setbkcolor(GREEN);
						outtextxy(g.tdDinh[i].x - 5, g.tdDinh[i].y - 5, kiTu[i]);
					}
				}

			}
		}
	}
}
void drawButtonVertex(int color){
	drawButton(BTN_VEDINH_LEFT, BTN_VEDINH_TOP, BTN_VEDINH_RIGHT, BTN_VEDINH_BOTTOM, color);
	setcolor(BLACK);
	setbkcolor(color);
	circle(BTN_VEDINH_LEFT + 25, BTN_VEDINH_TOP + 25, 20);
	outtextxy(BTN_VEDINH_LEFT + 20, BTN_VEDINH_TOP + 20, "A");
}
void drawButtonEdge(int color){
	drawButton(BTN_VECANH_LEFT, BTN_VECANH_TOP, BTN_VECANH_RIGHT, BTN_VECANH_BOTTOM, color);
	drawArrow(BTN_VECANH_LEFT, BTN_VECANH_BOTTOM , BTN_VECANH_RIGHT , BTN_VECANH_TOP , BLACK);
	line(BTN_VECANH_LEFT + 5, BTN_VECANH_BOTTOM - 5, BTN_VECANH_RIGHT - 15, BTN_VECANH_TOP + 15);
}

void xoaCungHaiDinh(GRAPH &g, int dinhDau, int dinhCuoi, int color){
	int x1 = g.tdDinh[dinhDau].x, y1 = g.tdDinh[dinhDau].y;
	int x2 = g.tdDinh[dinhCuoi].x, y2 = g.tdDinh[dinhCuoi].y;
	int colorBG = DARKGRAY;

	if (g.G[dinhCuoi][dinhDau] == 0){
		setcolor(colorBG);
		line(x1, y1, x2, y2);
		drawArrow(x1, y1, x2, y2, colorBG);
		/*In trọng số*/
		setbkcolor(colorBG);
		setcolor(colorBG);
		char trongSo[4] = "000";
		outtextxy((x1 + x2) / 2 + 15, (y1 + y2) / 2 + 5, trongSo);

		setfillstyle(SOLID_FILL, GREEN);
		/*Tô lại màu cho 2 đỉnh để che đi đường thẳng bên trong*/
		//Đỉnh 1
		setcolor(BLACK);
		circle(x1, y1, R);
		floodfill(x1, y1, BLACK);

		setcolor(GREEN);
		circle(x1, y1, R);
		floodfill(x1, y1, GREEN);
		setcolor(RED);
		setbkcolor(GREEN);
		outtextxy(x1 - 5, y1 - 5, kiTu[dinhDau]);

		// Đỉnh 2
		setcolor(BLACK);
		circle(x2, y2, R);
		floodfill(x2, y2, BLACK);

		setcolor(GREEN);
		circle(x2, y2, R);
		floodfill(x2, y2, GREEN);
		setcolor(RED);
		setbkcolor(GREEN);
		outtextxy(x2 - 5, y2 - 5, kiTu[dinhCuoi]);

	}
	else{
		char trongSo[4] = "000";
		setcolor(colorBG);
		
		setbkcolor(colorBG);
		double arrow_lenght_(8), arrow_degrees_(M_PI / 2);
		double angle = atan2(y2 - y1, x2 - x1) + M_PI;
		int xtemp1 = x1 + arrow_lenght_ * cos(angle - arrow_degrees_);
		int ytemp1 = y1 + arrow_lenght_ * sin(angle - arrow_degrees_);
		int xtemp2 = x2 + arrow_lenght_ * cos(angle - arrow_degrees_);
		int ytemp2 = y2 + arrow_lenght_ * sin(angle - arrow_degrees_);

		// Vẽ lại đường thẳng nối từ Cuoi -> dau
		line(xtemp2, ytemp2, xtemp1, ytemp1);
		drawArrow(xtemp2, ytemp2, xtemp1, ytemp1, colorBG);
		outtextxy((xtemp1 + xtemp2) / 2, (ytemp1 + ytemp2) / 2, trongSo);

		// Vẽ lại đường thẳng nối từ Dau -> cuoi
		setcolor(colorBG);
		xtemp1 = x1 + arrow_lenght_ * cos(angle + arrow_degrees_);
		ytemp1 = y1 + arrow_lenght_ * sin(angle + arrow_degrees_);
		xtemp2 = x2 + arrow_lenght_ * cos(angle + arrow_degrees_);
		ytemp2 = y2 + arrow_lenght_ * sin(angle + arrow_degrees_);
		line(xtemp1, ytemp1, xtemp2, ytemp2);
		drawArrow(xtemp1, ytemp1, xtemp2, ytemp2, colorBG);
		outtextxy((xtemp1 + xtemp2) / 2, (ytemp1 + ytemp2) / 2, trongSo);

		//Ve lai 1 cung con lai
		setbkcolor(colorBG);
		setcolor(color);
		line(x2, y2, x1, y1);
		drawArrow(x2, y2, x1, y1, color);
		_itoa(g.G[dinhCuoi][dinhDau], trongSo, 10);
		outtextxy((x1 + x2) / 2 + 15, (y1 + y2) / 2 + 5, trongSo);

		/*Tô lại màu cho 2 đỉnh để che đi đường thẳng bên trong*/
		setfillstyle(SOLID_FILL, GREEN);
		//Đỉnh 1
		setcolor(YELLOW);
		circle(x1, y1, R);
		floodfill(x1, y1, YELLOW);
		setcolor(GREEN);
		circle(x1, y1, R);
		floodfill(x1, y1, GREEN);
		setcolor(RED);
		setbkcolor(GREEN);
		outtextxy(x1 - 5, y1 - 5, kiTu[dinhDau]);

		// Đỉnh 2
		setcolor(YELLOW);
		circle(x2, y2, R);
		floodfill(x2, y2, YELLOW);
		setcolor(GREEN);
		circle(x2, y2, R);
		floodfill(x2, y2, GREEN);
		setcolor(RED);
		setbkcolor(GREEN);
		outtextxy(x2 - 5, y2 - 5, kiTu[dinhCuoi]);
	}

}

bool kiemTraDinhGanNhau(GRAPH &g, int x, int y){
	for (int i = 1; i <= g.soDinh; i++){
		if (lenghLine(x, y, g.tdDinh[i].x, g.tdDinh[i].y) <= (2 * R + 20))
			return true;
	}
	return false;
}

void drawGraph(GRAPH &g){
	setbkcolor(DARKGRAY);
	setcolor(GREEN);
	bool *check = new bool[g.soDinh + 1];
	for (int i = 1; i <= g.soDinh; i++){
		check[i] = false;
	}
	for (int i = 1; i <= g.soDinh; i++){
		for (int j = 1; j <= g.soDinh; j++){
			if (g.G[i][j] != 0){
				veCungHaiDinh(g, i, j, WHITE);
				check[i] = true;
				check[j] = true;
			}
		}
	}
	setfillstyle(SOLID_FILL, GREEN);
	for (int i = 1; i <= g.soDinh; i++){
		if (check[i] == false){
			setcolor(GREEN);
			circle(g.tdDinh[i].x, g.tdDinh[i].y, R);
			floodfill(g.tdDinh[i].x, g.tdDinh[i].y, GREEN);
			setcolor(RED);
			setbkcolor(GREEN);
			outtextxy(g.tdDinh[i].x - 5, g.tdDinh[i].y - 5, kiTu[i]);
		}
	}
}

void drawButtonDeleteVertex(int color){
	drawButton(BTN_XOADINH_LEFT, BTN_XOADINH_TOP, BTN_XOADINH_RIGHT, BTN_XOADINH_BOTTOM, color);
	setcolor(BLACK);
	setbkcolor(color);
	circle(BTN_XOADINH_LEFT + 25, BTN_XOADINH_TOP + 25, 20);
	outtextxy(BTN_XOADINH_LEFT + 20, BTN_XOADINH_TOP + 20, "A");

	line(BTN_XOADINH_LEFT + 5, BTN_XOADINH_TOP + 5, BTN_VEDINH_RIGHT - 5, BTN_XOADINH_BOTTOM - 5);
	line(BTN_VEDINH_RIGHT - 5, BTN_XOADINH_TOP + 5, BTN_XOADINH_LEFT + 5, BTN_XOADINH_BOTTOM - 5);
}
void drawButtonMove(int color){
	drawButton(BTN_DICHUYEN_LEFT, BTN_DICHUYEN_TOP, BTN_DICHUYEN_RIGHT, BTN_DICHUYEN_BOTTOM, color);
	setcolor(BLACK);
	circle(BTN_DICHUYEN_LEFT + 15, BTN_DICHUYEN_TOP + 15, 10);
	circle(BTN_DICHUYEN_RIGHT - 15, BTN_DICHUYEN_BOTTOM - 15, 10);
}
void drawButtonSave(int color){
	drawButton(BTN_SAVEFILE_LEFT, BTN_SAVEFILE_TOP, BTN_SAVEFILE_RIGHT, BTN_SAVEFILE_BOTTOM, color);
	setbkcolor(color);
	setcolor(BLACK);
	outtextxy(BTN_SAVEFILE_LEFT + 5, BTN_SAVEFILE_TOP + 20, "SAVE");
}
void drawButtonLoad(int color){
	drawButton(BTN_LOADFILE_LEFT, BTN_LOADFILE_TOP, BTN_LOADFILE_RIGHT, BTN_LOADFILE_BOTTOM, color);
	setbkcolor(color);
	setcolor(BLACK);
	outtextxy(BTN_LOADFILE_LEFT + 5, BTN_LOADFILE_TOP + 20, "LOAD");
}
void drawButtonClean(int color){
	drawButton(BTN_CLEANALL_LEFT, BTN_CLEANALL_TOP, BTN_CLEANALL_RIGHT, BTN_CLEANALL_BOTTOM, color);
	setbkcolor(color);
	setcolor(BLACK);
	outtextxy(BTN_CLEANALL_LEFT + 2, BTN_CLEANALL_TOP + 20, "CLEAN");
}
void drawButtonBFS(int color){
	drawButton(BTN_BFS_LEFT, BTN_BFS_TOP, BTN_BFS_RIGHT, BTN_BFS_BOTTOM, color);
	setbkcolor(color);
	setcolor(BLACK);
	outtextxy(BTN_BFS_LEFT + 25, BTN_BFS_TOP + 10, "B F S");
}
void drawButtonDFS(int color){
	drawButton(BTN_DFS_LEFT, BTN_DFS_TOP, BTN_DFS_RIGHT, BTN_DFS_BOTTOM, color);
	setbkcolor(color);
	setcolor(BLACK);
	outtextxy(BTN_DFS_LEFT + 25, BTN_DFS_TOP + 10, "D F S");
}
void drawButtonTimTCDDi(int color){
	drawButton(BTN_TIMTCDDI_LEFT, BTN_TIMTCDDI_TOP, BTN_TIMTCDDI_RIGHT, BTN_TIMTCDDI_BOTTOM, color);
	setbkcolor(color);
	setcolor(BLACK);
	outtextxy(BTN_TIMTCDDI_LEFT + 15, BTN_TIMTCDDI_TOP + 10, " PATH ");
}
void drawButtonFindSCC(int color){
	drawButton(BTN_SCC_LEFT, BTN_SCC_TOP, BTN_SCC_RIGHT, BTN_SCC_BOTTOM, color);
	setbkcolor(color);
	setcolor(BLACK);
	outtextxy(BTN_SCC_LEFT + 25, BTN_SCC_TOP + 10, "SCC");
}
void drawButtonDijkstra(int color){
	drawButton(BTN_DIJKSTRA_LEFT, BTN_DIJKSTRA_TOP, BTN_DIJKSTRA_RIGHT, BTN_DIJKSTRA_BOTTOM, color);
	setbkcolor(color);
	setcolor(BLACK);
	outtextxy(BTN_DIJKSTRA_LEFT + 10, BTN_DIJKSTRA_TOP + 10, "DIJKSTRA");
}
void drawButtonTimTru(int color){
	drawButton(BTN_TIMTRU_LEFT, BTN_TIMTRU_TOP, BTN_TIMTRU_RIGHT, BTN_TIMTRU_BOTTOM, color);
	setbkcolor(color);
	setcolor(BLACK);
	outtextxy(BTN_TIMTRU_LEFT + 25, BTN_TIMTRU_TOP + 10, "TRU");
}
void drawButtonTimCCau(int color){
	drawButton(BTN_CANHCAU_LEFT, BTN_CANHCAU_TOP, BTN_CANHCAU_RIGHT, BTN_CANHCAU_BOTTOM, color);
	setbkcolor(color);
	setcolor(BLACK);
	outtextxy(BTN_CANHCAU_LEFT + 20, BTN_CANHCAU_TOP + 10, "CCAU");
}
void drawButtonEuler(int color){
	drawButton(BTN_EULER_LEFT, BTN_EULER_TOP, BTN_EULER_RIGHT, BTN_EULER_BOTTOM, color);
	setbkcolor(color);
	setcolor(BLACK);
	outtextxy(BTN_EULER_LEFT + 20, BTN_EULER_TOP + 10, "EULER");
}
void drawButtonHamilton(int color){
	drawButton(BTN_HAMILTON_LEFT, BTN_HAMILTON_TOP, BTN_HAMILTON_RIGHT, BTN_HAMILTON_BOTTOM, color);
	setbkcolor(color);
	setcolor(BLACK);
	outtextxy(BTN_HAMILTON_LEFT + 5, BTN_HAMILTON_TOP + 10, "HAMILTON");
}
void loadFileSelected(GRAPH &g, char fileName[]){
	int textX = 5, textY = KHUNGVE_BOTTOM + 30;
	setbkcolor(LIGHTGRAY);
	setcolor(RED);
	char s[10];
	bool check = false;
	fstream dataFile;

	if (g.soDinh > 0){
		textWrite(textX, textY, "DO THI DANG TON TAI. BAN CO MUON LOAD FILE KHONG? (Y/N): ");
		textReadString(textX, textY, s);
		//Xoa ki tu vua in
		textX = 5;
		textY = KHUNGVE_BOTTOM + 30;
		setcolor(LIGHTGRAY);
		textWrite(textX, textY, "DO THI DANG TON TAI. BAN CO MUON LOAD FILE KHONG? (Y/N): ");
		textWriteln(textX, textY, s);

		if (s[0] == 'y' || s[0] == 'Y')
			check = true;
		else return;
	}

	textX = 5;
	textY = KHUNGVE_BOTTOM + 30;
	setcolor(RED);
	textWrite(textX, textY, "NHAP VAO TEN FILE: ");
	fflush(stdin);
	textReadString(textX, textY, fileName);
	textWriteln(textX, textY, "");

	dataFile.open(fileName, ios::in);
	if (dataFile.fail()){
		textWrite(textX, textY, "KHONG TIM THAY FILE, VUI LONG KIEM TRA LAI!");
		Sleep(700);
		setfillstyle(SOLID_FILL, LIGHTGRAY);
		bar(LOG_LEFT + 2, LOG_TOP + 10, LOG_RIGHT, LOG_BOTTOM);
		return;
	}
	// Reset cac gia tri ve 0
	check = true;
	if (check){
		for (int i = 1; i <= g.soDinh; i++){
			for (int j = 1; j <= g.soDinh; j++){
				g.G[i][j] = 0;
			}
			g.tdDinh[i].x = g.tdDinh[i].y = 0;
		}
		g.soDinh = 0;

		int t = 1;
		while (!dataFile.eof())	{
			dataFile >> g.soDinh;
			while (t <= g.soDinh){
				dataFile >> g.tdDinh[t].x >> g.tdDinh[t].y;
				dataFile.seekg(3, ios::cur);
				t++;
			}
			for (int i = 1; i <= g.soDinh; i++){
				for (int j = 1; j <= g.soDinh; j++){
					dataFile >> g.G[i][j];
				}
			}
		}
	}
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	bar(LOG_LEFT + 2, LOG_TOP + 10, LOG_RIGHT, LOG_BOTTOM);
	dataFile.close();
}

void saveFileSelected(GRAPH &g, char fileName[]){
	int textX = 5, textY = KHUNGVE_BOTTOM + 30;
	setbkcolor(LIGHTGRAY);
	setcolor(RED);
	fstream dataFile;

	textWrite(textX, textY, "NHAP VAO TEN FILE CAN LUU: ");
	textReadString(textX, textY, fileName);
	textWrite(textX, textY, "");

	//Set lai mau chu den
	setcolor(LIGHTGRAY);
	textX = 5;
	textY = KHUNGVE_BOTTOM + 30;
	textWrite(textX, textY, "NHAP VAO TEN FILE CAN LUU: ");
	textWriteln(textX, textY, fileName);

	dataFile.open(fileName, ios::out);
	// Kiểm tra mở file
	if (dataFile.fail()){
		setcolor(RED);
		textX = 5;
		textY = KHUNGVE_BOTTOM + 30;
		textWriteln(textX, textY, "LUU KHONG THANH CONG. VUI LONG KIEM TRA LAI TEN FILE!");
		Sleep(700);
		setfillstyle(SOLID_FILL, LIGHTGRAY);
		bar(LOG_LEFT + 2, LOG_TOP + 10, LOG_RIGHT, LOG_BOTTOM);
		return;
	}
	
	//Lưu file ở đây
	dataFile << g.soDinh << "\n";
	for (int i = 1; i <= g.soDinh; i++){
		dataFile << g.tdDinh[i].x << "  " << g.tdDinh[i].y << " - ";
	}
	dataFile << "\n";
	for (int i = 1; i <= g.soDinh; i++){
		for (int j = 1; j <= g.soDinh; j++){
			dataFile << g.G[i][j] << "  ";
		}
		dataFile << "\n";
	}

	setcolor(RED);
	textX = 5;
	textY = KHUNGVE_BOTTOM + 30;
	textWriteln(textX, textY, "LUU FILE THANH CONG!!");
	Sleep(1000);
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	bar(LOG_LEFT + 2, LOG_TOP + 10, LOG_RIGHT, LOG_BOTTOM);
}

void DFS(GRAPH &g, int v, bool check[], int &textX, int &textY){
	setbkcolor(LIGHTGRAY);
	setcolor(BLACK);
	// Xử lý
	textWrite(textX, textY, kiTu[v]);

	setfillstyle(SOLID_FILL, CYAN);
	setbkcolor(CYAN);
	setcolor(CYAN);
	circle(g.tdDinh[v].x, g.tdDinh[v].y, R);
	floodfill(g.tdDinh[v].x, g.tdDinh[v].y, CYAN);
	setcolor(RED);
	outtextxy(g.tdDinh[v].x - 5, g.tdDinh[v].y - 5, kiTu[v]);
	Sleep(1000);

	//
	check[v] = false;
	for (int u = 1; u <= g.soDinh; u++){
		if (g.G[v][u] && check[u]) {
			setcolor(BLACK);
			setbkcolor(LIGHTGRAY);
			textWrite(textX, textY, " --> ");
			//Vẽ đường thẳng nối giữa 2 đỉnh
			if (g.G[u][v] != 0){
				double arrow_lenght_(8), arrow_degrees_(M_PI / 2);
				double angle = atan2(g.tdDinh[u].y - g.tdDinh[v].y, g.tdDinh[u].x - g.tdDinh[v].x) + M_PI;
				int xtemp1 = g.tdDinh[v].x + arrow_lenght_ * cos(angle + arrow_degrees_);
				int ytemp1 = g.tdDinh[v].y + arrow_lenght_ * sin(angle + arrow_degrees_);
				int xtemp2 = g.tdDinh[u].x + arrow_lenght_ * cos(angle + arrow_degrees_);
				int ytemp2 = g.tdDinh[u].y + arrow_lenght_ * sin(angle + arrow_degrees_);

				setcolor(RED);
				line(xtemp1, ytemp1, xtemp2, ytemp2);
				drawArrow(xtemp1, ytemp1, xtemp2, ytemp2, RED);
			}
			else{
				setcolor(RED);
				line(g.tdDinh[v].x, g.tdDinh[v].y, g.tdDinh[u].x, g.tdDinh[u].y);
				drawArrow(g.tdDinh[v].x, g.tdDinh[v].y, g.tdDinh[u].x, g.tdDinh[u].y, RED);
			}
			setfillstyle(SOLID_FILL, CYAN);
			//Vẽ lại 2 đỉnh 
			setcolor(BLACK);
			circle(g.tdDinh[v].x, g.tdDinh[v].y, R);
			floodfill(g.tdDinh[v].x, g.tdDinh[v].y, BLACK);

			setcolor(CYAN);
			circle(g.tdDinh[v].x, g.tdDinh[v].y, R);
			floodfill(g.tdDinh[v].x, g.tdDinh[v].y, CYAN);
			setcolor(RED);
			setbkcolor(CYAN);
			outtextxy(g.tdDinh[v].x - 5, g.tdDinh[v].y - 5, kiTu[v]);

			// Đỉnh 2
			setcolor(BLACK);
			circle(g.tdDinh[u].x, g.tdDinh[u].y, R);
			floodfill(g.tdDinh[u].x, g.tdDinh[u].y, BLACK);

			setfillstyle(SOLID_FILL, GREEN);
			setbkcolor(GREEN);
			setcolor(GREEN);
			circle(g.tdDinh[u].x, g.tdDinh[u].y, R);
			floodfill(g.tdDinh[u].x, g.tdDinh[u].y, GREEN);
			setcolor(RED);
			outtextxy(g.tdDinh[u].x - 5, g.tdDinh[u].y - 5, kiTu[u]);
			Sleep(1000);

			DFS(g, u, check, textX, textY);
		}
	}

}

void DFSAlgorithm(int G[][MAXSIZE], int soDinh, int u, bool check[]){
	check[u] = false;
	for (int v = 1; v <= soDinh; v++){
		if (G[u][v] && check[v])
			DFSAlgorithm(G, soDinh, v, check);
	}
}
void BFS(GRAPH &g, int v, bool check[], QUEUE &q, int &textX, int &textY){
	setbkcolor(LIGHTGRAY);
	setcolor(BLACK);
	int u;
	q.front = NULL;
	pushQueue(q, v);
	check[v] = false;
	while (q.front != NULL){
		u = popQueue(q);
		// Xử lý
		setcolor(BLACK);
		setbkcolor(LIGHTGRAY);
		textWrite(textX, textY, kiTu[u]);

		setfillstyle(SOLID_FILL, CYAN);
		setbkcolor(CYAN);
		setcolor(CYAN);
		circle(g.tdDinh[u].x, g.tdDinh[u].y, R);
		floodfill(g.tdDinh[u].x, g.tdDinh[u].y, CYAN);
		setcolor(RED);
		outtextxy(g.tdDinh[u].x - 5, g.tdDinh[u].y - 5, kiTu[u]);
		Sleep(1000);

		for (int j = 1; j <= g.soDinh; j++){
			if (g.G[u][j] && check[j]){
				pushQueue(q, j);
				check[j] = false;

				//Vẽ đường thẳng khi duyệt tới
				if (g.G[j][u] != 0){
					double arrow_lenght_(8), arrow_degrees_(M_PI / 2);
					double angle = atan2(g.tdDinh[j].y - g.tdDinh[u].y, g.tdDinh[j].x - g.tdDinh[u].x) + M_PI;
					int xtemp1 = g.tdDinh[u].x + arrow_lenght_ * cos(angle + arrow_degrees_);
					int ytemp1 = g.tdDinh[u].y + arrow_lenght_ * sin(angle + arrow_degrees_);
					int xtemp2 = g.tdDinh[j].x + arrow_lenght_ * cos(angle + arrow_degrees_);
					int ytemp2 = g.tdDinh[j].y + arrow_lenght_ * sin(angle + arrow_degrees_);

					setcolor(RED);
					line(xtemp1, ytemp1, xtemp2, ytemp2);
					drawArrow(xtemp1, ytemp1, xtemp2, ytemp2, RED);
				}
				else{
					setcolor(RED);
					line(g.tdDinh[u].x, g.tdDinh[u].y, g.tdDinh[j].x, g.tdDinh[j].y);
					drawArrow(g.tdDinh[u].x, g.tdDinh[u].y, g.tdDinh[j].x, g.tdDinh[j].y, RED);
				}
				setfillstyle(SOLID_FILL, CYAN);
				//Vẽ lại 2 đỉnh 
				setcolor(BLACK);
				circle(g.tdDinh[u].x, g.tdDinh[u].y, R);
				floodfill(g.tdDinh[u].x, g.tdDinh[u].y, BLACK);

				setcolor(CYAN);
				circle(g.tdDinh[u].x, g.tdDinh[u].y, R);
				floodfill(g.tdDinh[u].x, g.tdDinh[u].y, CYAN);
				setcolor(RED);
				setbkcolor(CYAN);
				outtextxy(g.tdDinh[u].x - 5, g.tdDinh[u].y - 5, kiTu[u]);

				// Đỉnh 2
				setcolor(BLACK);
				circle(g.tdDinh[j].x, g.tdDinh[j].y, R);
				floodfill(g.tdDinh[j].x, g.tdDinh[j].y, BLACK);

				setfillstyle(SOLID_FILL, GREEN);
				setbkcolor(GREEN);
				setcolor(GREEN);
				circle(g.tdDinh[j].x, g.tdDinh[j].y, R);
				floodfill(g.tdDinh[j].x, g.tdDinh[j].y,GREEN);
				setcolor(RED);
				outtextxy(g.tdDinh[j].x - 5, g.tdDinh[j].y - 5, kiTu[j]);
				Sleep(1000);

			}
		}
		if (q.front != NULL){
			setbkcolor(LIGHTGRAY);
			setcolor(BLACK);
			textWrite(textX, textY, " --> ");
		}
	}
}

void BFSSelected(GRAPH &g){
	int textX = 5, textY = KHUNGVE_BOTTOM + 30;
	setbkcolor(LIGHTGRAY);
	setcolor(RED);
	bool checkEdge = false;
	for (int i = 1; i <= g.soDinh; i++){
		for (int j = 1; j <= g.soDinh; j++){
			if (g.G[i][j] != 0){
				checkEdge = true;
				break;
			}
		}
	}
	if (g.soDinh == 0){
		outtextxy(textX, textY, "DO THI CHUA TON TAI. VUI LONG KIEM TRA LAI!!");
		setcolor(LIGHTGRAY);
		Sleep(1000);
		outtextxy(textX, textY, "DO THI CHUA TON TAI. VUI LONG KIEM TRA LAI!!");
		return;
	}
	else if (g.soDinh == 1){
		outtextxy(textX, textY, "TON TAI CHI 1 DINH. KHONG THUC HIEN DUYET!!");
		setcolor(LIGHTGRAY);
		Sleep(1000);
		outtextxy(textX, textY, "TON TAI CHI 1 DINH. KHONG THUC HIEN DUYET!!");
		return;
	}
	else if (checkEdge == false){
		outtextxy(textX, textY, "CHUA THIET LAP TRONG SO. VUI LONG KIEM TRA LAI!!");
		setcolor(LIGHTGRAY);
		Sleep(1000);
		outtextxy(textX, textY, "CHUA THIET LAP TRONG SO. VUI LONG KIEM TRA LAI!!");
		return;
	}

	textWriteln(textX, textY, "VUI LONG CHON DINH BAT DAU DUYET!");
	int tempX, tempY;
	QUEUE q;
	bool   *chuaXet = new bool[g.soDinh + 1];
	for (int i = 0; i <= g.soDinh; i++){
		chuaXet[i] = true;
	}
	int viTriDuyet = -1;
	while (1){
		while (kbhit()){
			if (char a = getch() == 13) {
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(LOG_LEFT + 2, LOG_TOP + 10, LOG_RIGHT, LOG_BOTTOM);
				//Xóa khung vẽ 
				setfillstyle(SOLID_FILL, DARKGRAY);
				bar(KHUNGVE_LEFT + 53, KHUNGVE_TOP + 1, KHUNGVE_RIGHT, KHUNGVE_BOTTOM - 1);

				drawGraph(g);
				delete chuaXet;
				return;
			}
		}
		if (ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, tempX, tempY);
			if (checkClick(tempX, tempY) == DUYET_BFS){
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(LOG_LEFT + 2, LOG_TOP + 10, LOG_RIGHT, LOG_BOTTOM);
				delete chuaXet;
				return;
			}
			for (int i = 1; i <= g.soDinh; i++){
				if (lenghLine(g.tdDinh[i].x, g.tdDinh[i].y, tempX, tempY) <= R){
					textX = 5, textY = KHUNGVE_BOTTOM + 30;
					setcolor(LIGHTGRAY);
					textWriteln(textX, textY, "VUI LONG CHON DINH BAT DAU DUYET!");
					viTriDuyet = i;
					break;
				}
			}
			if (viTriDuyet != -1){
				textX = 5, textY = KHUNGVE_BOTTOM + 30;
				BFS(g, viTriDuyet, chuaXet, q, textX, textY);

				//Duyệt các thành phần còn lại nếu chưa quyệt hết
				for (int i = 1; i <= g.soDinh; i++){
					if (chuaXet[i]){
						textWriteln(textX, textY, "");
						BFS(g, i, chuaXet, q, textX, textY);
					}
				}
				textWriteln(textX, textY, "");
				setbkcolor(LIGHTGRAY);
				setcolor(RED);
				outtextxy(textX, textY, "DA DUYET XONG. VUI LONG NHAN ENTER DE TIEP TUC CHUONG TRINH!");
			}
		}
	}
}			

void DFSSelected(GRAPH &g){
	int textX = 5, textY = KHUNGVE_BOTTOM + 30;
	setbkcolor(LIGHTGRAY);
	setcolor(RED);
	bool check = false;
	for (int i = 1; i <= g.soDinh; i++){
		for (int j = 1; j <= g.soDinh; j++){
			if (g.G[i][j] != 0){
				check = true;
				break;
			}
		}
	}
	if (g.soDinh == 0){
		outtextxy(textX, textY, "DO THI CHUA TON TAI. VUI LONG KIEM TRA LAI!!");
		setcolor(LIGHTGRAY);
		Sleep(1000);
		outtextxy(textX, textY, "DO THI CHUA TON TAI. VUI LONG KIEM TRA LAI!!");
		return;
	}
	else if (g.soDinh == 1){
		outtextxy(textX, textY, "TON TAI CHI 1 DINH. KHONG THUC HIEN DUYET!!");
		setcolor(LIGHTGRAY);
		Sleep(1000);
		outtextxy(textX, textY, "TON TAI CHI 1 DINH. KHONG THUC HIEN DUYET!!");
		return;
	}
	else if (check == false){
		outtextxy(textX, textY, "CHUA THIET LAP TRONG SO. VUI LONG KIEM TRA LAI!!");
		setcolor(LIGHTGRAY);
		Sleep(1000);
		outtextxy(textX, textY, "CHUA THIET LAP TRONG SO. VUI LONG KIEM TRA LAI!!");
		return;
	}

	textWriteln(textX, textY, "VUI LONG CHON DINH BAT DAU DUYET!");
	int tempX, tempY;
	bool   *chuaXet = new bool[g.soDinh + 1];
	for (int i = 0; i <= g.soDinh; i++){
		chuaXet[i] = true;
	}
	int viTriDuyet = -1;
	while (1){
		while (kbhit()){
			if (char a = getch() == 13){
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(LOG_LEFT + 2, LOG_TOP + 10, LOG_RIGHT, LOG_BOTTOM);
				//Xóa khung vẽ 
				setfillstyle(SOLID_FILL, DARKGRAY);
				bar(KHUNGVE_LEFT + 53, KHUNGVE_TOP + 1, KHUNGVE_RIGHT, KHUNGVE_BOTTOM - 1);

				drawGraph(g);
				delete chuaXet;
				return;
			}
		}
		if (ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, tempX, tempY);
			if (checkClick(tempX, tempY) == DUYET_DFS){
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(LOG_LEFT + 2, LOG_TOP + 10, LOG_RIGHT, LOG_BOTTOM);
				delete chuaXet;
				return;
			}
			for (int i = 1; i <= g.soDinh; i++){
				if (lenghLine(g.tdDinh[i].x, g.tdDinh[i].y, tempX, tempY) <= R){
					textX = 5, textY = KHUNGVE_BOTTOM + 30;
					setcolor(LIGHTGRAY);
					textWriteln(textX, textY, "VUI LONG CHON DINH BAT DAU DUYET!");
					viTriDuyet = i;
					break;
				}
			}
			if (viTriDuyet != -1){
				textX = 5, textY = KHUNGVE_BOTTOM + 30;
				DFS(g, viTriDuyet, chuaXet, textX, textY);

				//Duyệt các thành phần còn lại nếu chưa quyệt hết
				for (int i = 1; i <= g.soDinh; i++){
					if (chuaXet[i]){
						textWriteln(textX, textY, "");
						DFS(g, i, chuaXet, textX, textY);
					}
				}
				textWriteln(textX, textY, "");
				setbkcolor(LIGHTGRAY);
				setcolor(RED);
				outtextxy(textX, textY, "DA DUYET XONG. VUI LONG NHAN ENTER DE TIEP TUC CHUONG TRINH!");
			}
		}
	}
}

void findPathTwoVertexSelected(GRAPH &g){
	int textX = 5, textY = KHUNGVE_BOTTOM + 30;
	setbkcolor(LIGHTGRAY);
	setcolor(RED);
	bool check = false;
	for (int i = 1; i <= g.soDinh; i++){
		for (int j = 1; j <= g.soDinh; j++){
			if (g.G[i][j] != 0){
				check = true;
				break;
			}
		}
	}
	if (g.soDinh == 0){
		outtextxy(textX, textY, "DO THI CHUA TON TAI. VUI LONG KIEM TRA LAI!!");
		setcolor(LIGHTGRAY);
		Sleep(1000);
		outtextxy(textX, textY, "DO THI CHUA TON TAI. VUI LONG KIEM TRA LAI!!");
		return;
	}
	else if (g.soDinh == 1){
		outtextxy(textX, textY, "TON TAI CHI 1 DINH. KHONG THUC HIEN TIM DUONG!!");
		setcolor(LIGHTGRAY);
		Sleep(1000);
		outtextxy(textX, textY, "TON TAI CHI 1 DINH. KHONG THUC HIEN TIM DUONG!!");
		return;
	}
	else if (check == false){
		outtextxy(textX, textY, "CHUA THIET LAP TRONG SO. VUI LONG KIEM TRA LAI!!");
		setcolor(LIGHTGRAY);
		Sleep(1000);
		outtextxy(textX, textY, "CHUA THIET LAP TRONG SO. VUI LONG KIEM TRA LAI!!");
		return;
	}

	textWriteln(textX, textY, "VUI LONG CHON 2 DINH X, Y CAN TIM !!");

	int x, y;
	int dinhX = 0, dinhY = 0;
	int dem = 0;
	bool *chuaXet = new bool[g.soDinh + 1];
	int *duongDi = new int[g.soDinh + 1];
	for (int i = 1; i <= g.soDinh; i++){
		chuaXet[i] = true;
		duongDi[i] = 0;
	}

	while (1){
		if (ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, x, y);
			
			//Kiểm tra điểm click có thuộc đỉnh nào
			for (int i = 1; i <= g.soDinh; i++){
				if (lenghLine(x, y, g.tdDinh[i].x, g.tdDinh[i].y) <= R){
					if (dinhX == 0) dinhX = i;
					else dinhY = i;

					//	Tô lại màu cho đỉnh vừa chọn
					setfillstyle(SOLID_FILL, LIGHTGREEN);
					setcolor(LIGHTGREEN);
					circle(g.tdDinh[i].x, g.tdDinh[i].y, R);
					floodfill(g.tdDinh[i].x, g.tdDinh[i].y, LIGHTGREEN);
					setcolor(RED);
					setbkcolor(LIGHTGREEN);
					outtextxy(g.tdDinh[i].x - 5, g.tdDinh[i].y - 5, kiTu[i]);
				}
			}
		}
		if (dinhX != 0 && dinhY != 0){
			duongDi[1] = dinhX;			// Đưa đỉnh X vào mảng vị trí thứ 1
			chuaXet[dinhX] = false;
			break;
		}
	}
	textX = 5, textY = KHUNGVE_BOTTOM + 30;
	setcolor(LIGHTGRAY);
	setbkcolor(LIGHTGRAY);
	textWriteln(textX, textY, "VUITLONGTCHONT2TDINHTX,TYTCANTTIM !!");
	textX = 5, textY = KHUNGVE_BOTTOM + 30;
	setcolor(RED);
	textWrite(textX, textY, "DANG TIM .....");

	Sleep(500);

	//Thuật toán tìm tất cả các đường đi
	timDuongDi(2, dinhY, g, duongDi, chuaXet, dem);


	setcolor(LIGHTGRAY);
	setbkcolor(LIGHTGRAY);
	textWriteln(textX, textY, "VUITLONGTCHONT2TDINHTX,TYTCANTTIM !!");
	textX = 5, textY = KHUNGVE_BOTTOM + 30;
	setcolor(RED);
	setbkcolor(LIGHTGRAY);
	if (dem == 0){
		textWrite(textX, textY, "KHONG CO DUONG DI NAO!!");
	}
	else textWrite(textX, textY, "DA TIM XONG TAT CA CAC DUONG DI, ENTER TIEP TUC!!");

	while (1){
		if (ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if (checkClick(x, y) == ALL_PATH){
				setfillstyle(SOLID_FILL, DARKGRAY);
				bar(KHUNGVE_LEFT + 53, KHUNGVE_TOP + 1, KHUNGVE_RIGHT, KHUNGVE_BOTTOM - 1);
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(LOG_LEFT + 2, LOG_TOP + 10, LOG_RIGHT, LOG_BOTTOM);
				drawGraph(g);
				delete chuaXet, duongDi;
				return;
			}
		}
		while (kbhit()){
			if (char a = getch() == 13){
				setfillstyle(SOLID_FILL, DARKGRAY);
				bar(KHUNGVE_LEFT + 53, KHUNGVE_TOP + 1, KHUNGVE_RIGHT, KHUNGVE_BOTTOM - 1);
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(LOG_LEFT + 2, LOG_TOP + 10, LOG_RIGHT, LOG_BOTTOM);
				drawGraph(g);
				delete chuaXet, duongDi;
				return;
			}
		}
	}
}

void timDuongDi(int dinh, int dinhY, GRAPH &g, int duongDi[], bool check[], int &dem){
	if (duongDi[dinh - 1] == dinhY) {     //Xuất nếu đỉnh tìm từ lần tìm kiếm trước bằng C
		setfillstyle(SOLID_FILL, DARKGRAY);
		bar(KHUNGVE_LEFT + 53, KHUNGVE_TOP + 1, KHUNGVE_RIGHT, KHUNGVE_BOTTOM - 1);
		drawGraph(g);
		if (dem == 16){
			setcolor(RED);
			setbkcolor(LIGHTGRAY);
			int textX = MAXX / 2, textY = KHUNGVE_BOTTOM + 30 + (6 * 20);
			outtextxy(textX, textY, "ENTER DE TIEP TUC DUYET...");
			int x, y;
			while (1){
				if (char a = getch() == 13){
					dem = 0;
					setfillstyle(SOLID_FILL, LIGHTGRAY);
					bar(LOG_LEFT + 2, LOG_TOP + 10, LOG_RIGHT, LOG_BOTTOM);
					textX = 5, textY = KHUNGVE_BOTTOM + 30;
					outtextxy(textX, textY, "DANG TIM ....");

					break;
				}
			}
		}
		inDuongDiXY(duongDi, dinh, g, dem);
		Sleep(1200);
	}
	else {
		for (int i = 1; i <= g.soDinh; i++)
			if (g.G[duongDi[dinh - 1]][i] && check[i] ){
				duongDi[dinh] = i;										//Lưu lại đỉnh đi qua
				check[i] = false;										//Đánh dấu đỉnh đi qua
				timDuongDi(dinh + 1,dinhY, g, duongDi, check, dem);		//Tìm kiếm đỉnh tiếp theo
				duongDi[dinh] = 0;
				check[i] = true;										//Phục hồi đỉnh đỉnh đã đi qua
			}
	}
}

void inDuongDiXY(int duongDi[],int dinh,GRAPH &g, int &dem){
	dem++;
	int textX = 5, textY = KHUNGVE_BOTTOM + 30;
	if (dem < 9){
		for (int i = 0; i < dem; i++)  {
			textWriteln(textX, textY, "");
		}
	}
	else{
		textX = MAXX / 2;
		textY = KHUNGVE_BOTTOM + 30;
		for (int i = 9; i < dem; i++){
			textX = MAXX / 2;
			textY += 20;
		}
	}

	//demo
	setbkcolor(GREEN);
	setfillstyle(SOLID_FILL, GREEN);
	setcolor(BLACK);
	circle(g.tdDinh[duongDi[1]].x, g.tdDinh[duongDi[1]].y, R);
	floodfill(g.tdDinh[duongDi[1]].x, g.tdDinh[duongDi[1]].y, BLACK);

	
	setcolor(GREEN);
	circle(g.tdDinh[duongDi[1]].x, g.tdDinh[duongDi[1]].y, R);
	floodfill(g.tdDinh[duongDi[1]].x, g.tdDinh[duongDi[1]].y, GREEN);
	setcolor(RED);
	outtextxy(g.tdDinh[duongDi[1]].x - 5, g.tdDinh[duongDi[1]].y - 5, kiTu[duongDi[1]]);
	
	setcolor(BLACK);
	setbkcolor(LIGHTGRAY);
	textWrite(textX, textY, kiTu[duongDi[1]]);
	Sleep(1000);

	for (int i = 2; i < dinh; i++){
		char trongSo[4];
		if (g.G[duongDi[i]][duongDi[i - 1]] != 0){
			double arrow_lenght_(8), arrow_degrees_(M_PI / 2);
			double angle = atan2(g.tdDinh[duongDi[i - 1]].y - g.tdDinh[duongDi[i]].y, g.tdDinh[duongDi[i - 1]].x - g.tdDinh[duongDi[i]].x) + M_PI;
			int xtemp1 = g.tdDinh[duongDi[i - 1]].x + arrow_lenght_ * cos(angle - arrow_degrees_);
			int ytemp1 = g.tdDinh[duongDi[i - 1]].y + arrow_lenght_ * sin(angle - arrow_degrees_);
			int xtemp2 = g.tdDinh[duongDi[i]].x + arrow_lenght_ * cos(angle - arrow_degrees_);
			int ytemp2 = g.tdDinh[duongDi[i]].y + arrow_lenght_ * sin(angle - arrow_degrees_);

			setcolor(RED);
			line(xtemp1, ytemp1, xtemp2, ytemp2);
			drawArrow(xtemp1, ytemp1, xtemp2, ytemp2, RED);
			/*In trọng số*/
			setbkcolor(DARKGRAY);
			setcolor(RED);
			_itoa(g.G[duongDi[i - 1]][duongDi[i]], trongSo, 10);
			outtextxy((xtemp1 + xtemp2) / 2, (ytemp1 + ytemp2) / 2, trongSo);
		}
		else{
			setcolor(RED);
			line(g.tdDinh[duongDi[i - 1]].x, g.tdDinh[duongDi[i - 1]].y, g.tdDinh[duongDi[i]].x, g.tdDinh[duongDi[i]].y);
			drawArrow(g.tdDinh[duongDi[i - 1]].x, g.tdDinh[duongDi[i - 1]].y, g.tdDinh[duongDi[i]].x, g.tdDinh[duongDi[i]].y, RED);
			/*In trọng số*/
			setbkcolor(DARKGRAY);
			setcolor(RED);
			_itoa(g.G[duongDi[i - 1]][duongDi[i]], trongSo, 10);
			outtextxy((g.tdDinh[duongDi[i - 1]].x + g.tdDinh[duongDi[i]].x) / 2 + 15, (g.tdDinh[duongDi[i - 1]].y + g.tdDinh[duongDi[i]].y) / 2 + 5, trongSo);

		}

		/*Tô lại màu cho 2 đỉnh để che đi đường thẳng bên trong*/
		//Đỉnh 1
		setfillstyle(SOLID_FILL, CYAN);
		setcolor(BLACK);
		circle(g.tdDinh[duongDi[i - 1]].x, g.tdDinh[duongDi[i - 1]].y, R);
		floodfill(g.tdDinh[duongDi[i - 1]].x, g.tdDinh[duongDi[i - 1]].y, BLACK);

		setcolor(CYAN);
		circle(g.tdDinh[duongDi[i - 1]].x, g.tdDinh[duongDi[i - 1]].y, R);
		floodfill(g.tdDinh[duongDi[i - 1]].x, g.tdDinh[duongDi[i - 1]].y, CYAN);
		setcolor(RED);
		setbkcolor(CYAN);
		outtextxy(g.tdDinh[duongDi[i - 1]].x - 5, g.tdDinh[duongDi[i - 1]].y - 5, kiTu[duongDi[i - 1]]);

		// Đỉnh 2
		setcolor(CYAN);
		circle(g.tdDinh[duongDi[i]].x, g.tdDinh[duongDi[i]].y, R);
		floodfill(g.tdDinh[duongDi[i]].x, g.tdDinh[duongDi[i]].y, CYAN);
		setcolor(RED);
		setbkcolor(CYAN);
		outtextxy(g.tdDinh[duongDi[i]].x - 5, g.tdDinh[duongDi[i]].y - 5, kiTu[duongDi[i]]);

		setcolor(BLACK);
		setbkcolor(LIGHTGRAY);
		textWrite(textX, textY, " --> ");
		textWrite(textX, textY, kiTu[duongDi[i]]);

		Sleep(1000);
	}
}

void SCC(int u, int &count, int &conponentCount, GRAPH &g, STACK L[], STACK &st, int low[], int numbering[]){
	low[u] = numbering[u] = ++count;
	pushStack(st, u);

	for (int v = 1; v <= g.soDinh; v++){
		if (g.G[u][v] != 0){
			if (numbering[v] != 0){					  // Nếu đỉnh v đã thăm 
				low[u] = min(low[u], numbering[v]);
			}
			else{									  // Nếu đỉnh V chưa thăm
				SCC(v, count, conponentCount, g, L, st, low, numbering);
				low[u] = min(low[u], low[v]);
			}
		}
	}

	if (numbering[u] == low[u]){
		int v;
		conponentCount++;
		do{
			popStack(st, v);
			//Bỏ đỉnh v vào Stack cho từng thành phần liên thông. 
			pushStack(L[conponentCount], v);
			numbering[v] = low[v] = oo;
		} while (v != u);
	}
}

void SCC(int u, int &count, int &conponentCount, int **G, int n, STACK &st, int low[], int numbering[], bool check[])	{
	low[u] = numbering[u] = ++count;
	pushStack(st, u);

	for (int v = 1; v <= n; v++){
		if (G[u][v] != 0 && check[v] == true){
			if (numbering[v] != 0){
				low[u] = min(low[u], numbering[v]);
			}
			else{
				SCC(v, count, conponentCount, G, n, st, low, numbering, check);
				low[u] = min(low[u], low[v]);
			}
		}
	}

	if (numbering[u] == low[u]){
		int v;
		conponentCount++;
		do{
			popStack(st, v);
			numbering[v] = low[v] = oo;
		} while (v != u);
	}
}
void findSCCSelected(GRAPH &g){
	setbkcolor(LIGHTGRAY);
	setcolor(RED);
	int textX = 5, textY = KHUNGVE_BOTTOM + 30;

	// Kiểm tra đồ thị đã tồn tại hay chưa?
	if (g.soDinh == 0){
		outtextxy(textX, textY, "DO THI CHUA TON TAI. VUI LONG KIEM TRA LAI!!");
		setcolor(LIGHTGRAY);
		Sleep(1000);
		outtextxy(textX, textY, "DO THI CHUA TON TAI. VUI LONG KIEM TRA LAI!!");
		return;
	}

	int *low = new int[g.soDinh + 1];					 // Giá trị numbering nhỏ nhất có thể đến được đỉnh u
	int *numbering = new int[g.soDinh + 1];				 // Thứ tự được duyệt của đỉnh u
	STACK st;
	STACK *L = new STACK[g.soDinh + 1];					// Lưu các thành phần liên thông mạnh
	int count = 0;
	int conponentCount = 0;
	//Khởi tạo thông số mặc định
	st.sp = -1;
	for (int i = 0; i <= g.soDinh; i++){
		low[i] = numbering[i] = 0;
		L[i].sp = -1;
	}
	
	//Gọi hàm SCC tìm thành phần liên thông
	for (int i = 1; i <= g.soDinh; i++){
		if (!numbering[i]){
			SCC(i, count, conponentCount,g, L, st, low, numbering);
		}
	}
	
	char countSCC[5];
	_itoa(conponentCount, countSCC, 10);
	textWrite(textX, textY, "SO THANH PHAN LIEN THONG MANH CUA DO THI: ");
	textWriteln(textX, textY, countSCC);

	//Hiển thị trên màn hình dựa vào conponentStack[] đã tìm được
	setbkcolor(LIGHTGRAY);
	setcolor(RED);
	int *A = new int[g.soDinh + 1];
	int n;
	char kt[26][2];
	for (int i = 1; i < 26; i++){
		kt[i][1] = 0;
	}

	bool inBenPhai = false;
	for (int i = 1; i <= conponentCount; i++){
		int n = L[i].sp + 1;
		int j = 0;
		while (!empty(L[i])){
			popStack(L[i], A[j++]);
		}

		// Tạo ma trận kề của thành phần liên thuộc
		int **G = new int *[n + 1];
		TOADO *td = new TOADO	[n + 1];
		bool   *chuaXet = new bool[n + 1];
		for (int i = 0; i <= n; i++){
			G[i] = new int[n + 1];
			chuaXet[i] = true;
		}

		for (int u = 0; u < n; u++){
			for (int v = 0; v < n; v++){
				G[u + 1][v + 1] = g.G[A[u]][A[v]];
			}
			td[u + 1] = g.tdDinh[A[u]];
			kt[u + 1][0] = kiTu[A[u]][0];
		}
		
		if (i > 8 && inBenPhai == false){
			textX = MAXX / 2;
			textY = KHUNGVE_BOTTOM + 30;
			inBenPhai = true;
		}
		else if (i > 8)  {
			textX = MAXX / 2;
		}
		findSCCDFS(G, td, n, 1, chuaXet, textX, textY, kt);
		textWriteln(textX, textY, "");
		Sleep(1000);

		// Giải phóng vùng nhớ cho ma trận kề
		for (int i = 0; i < n; i++){
			delete[] G[i];
		}
		delete[] G;
		delete[] td;
		delete[] chuaXet;
	}

	//Nhấn  enter hoặc click vào button để thoát
	setbkcolor(LIGHTGRAY);
	setcolor(RED);
	if (conponentCount > 8) textX = MAXX / 2;
	textWriteln(textX, textY, "VUI LONG ENTER DE TIEP TUC CHUONG TRINH!!");
	int x, y;
	while (1){
		if (ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if (checkClick(x, y) == FIND_SCC){
				setfillstyle(SOLID_FILL, DARKGRAY);
				bar(KHUNGVE_LEFT + 53, KHUNGVE_TOP + 1, KHUNGVE_RIGHT, KHUNGVE_BOTTOM - 1);
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(LOG_LEFT + 2, LOG_TOP + 10, LOG_RIGHT, LOG_BOTTOM);
				drawGraph(g);
				return;
			}
		}
		while (kbhit()){
			if (char a = getch() == 13){
				setfillstyle(SOLID_FILL, DARKGRAY);
				bar(KHUNGVE_LEFT + 53, KHUNGVE_TOP + 1, KHUNGVE_RIGHT, KHUNGVE_BOTTOM - 1);
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(LOG_LEFT + 2, LOG_TOP + 10, LOG_RIGHT, LOG_BOTTOM);
				drawGraph(g);
				return;
			}
		}
	}
	//Giải phóng vùng nhớ đã cấp phát
	delete low;
	delete numbering;
	delete L, A;
}



void findSCCDFS(int **G, TOADO tdDinh[], int soDinh, int v, bool check[], int &textX, int &textY, char kt[][2]){
	setbkcolor(LIGHTGRAY);
	setcolor(BLACK);
	// Xử lý
	textWrite(textX, textY, kt[v]);

	setfillstyle(SOLID_FILL, CYAN);
	setbkcolor(CYAN);
	setcolor(CYAN);
	circle(tdDinh[v].x, tdDinh[v].y, R);
	floodfill(tdDinh[v].x, tdDinh[v].y, CYAN);
	setcolor(RED);
	outtextxy(tdDinh[v].x - 5, tdDinh[v].y - 5, kt[v]);
	Sleep(700);

	//
	check[v] = false;
	for (int u = 1; u <= soDinh; u++){
		if (G[v][u] != 0&& check[u] == false){
			if (G[u][v] != 0){
				double arrow_lenght_(8), arrow_degrees_(M_PI / 2);
				double angle = atan2(tdDinh[u].y - tdDinh[v].y, tdDinh[u].x - tdDinh[v].x) + M_PI;
				int xtemp1 = tdDinh[v].x + arrow_lenght_ * cos(angle + arrow_degrees_);
				int ytemp1 = tdDinh[v].y + arrow_lenght_ * sin(angle + arrow_degrees_);
				int xtemp2 = tdDinh[u].x + arrow_lenght_ * cos(angle + arrow_degrees_);
				int ytemp2 = tdDinh[u].y + arrow_lenght_ * sin(angle + arrow_degrees_);

				setcolor(RED);
				line(xtemp1, ytemp1, xtemp2, ytemp2);
				drawArrow(xtemp1, ytemp1, xtemp2, ytemp2, RED);
			}
			else{
				setcolor(RED);
				line(tdDinh[v].x, tdDinh[v].y, tdDinh[u].x, tdDinh[u].y);
				drawArrow(tdDinh[v].x, tdDinh[v].y, tdDinh[u].x, tdDinh[u].y, RED);
			}
			setfillstyle(SOLID_FILL, CYAN);
			//Vẽ lại 2 đỉnh 
			setcolor(BLACK);
			circle(tdDinh[v].x, tdDinh[v].y, R);
			floodfill(tdDinh[v].x, tdDinh[v].y, BLACK);

			setcolor(CYAN);
			circle(tdDinh[v].x, tdDinh[v].y, R);
			floodfill(tdDinh[v].x, tdDinh[v].y, CYAN);
			setcolor(RED);
			setbkcolor(CYAN);
			outtextxy(tdDinh[v].x - 5, tdDinh[v].y - 5, kt[v]);

			// Đỉnh 2
			setcolor(BLACK);
			circle(tdDinh[u].x, tdDinh[u].y, R);
			floodfill(tdDinh[u].x, tdDinh[u].y, BLACK);

			setfillstyle(SOLID_FILL, CYAN);
			setbkcolor(CYAN);
			setcolor(CYAN);
			circle(tdDinh[u].x, tdDinh[u].y, R);
			floodfill(tdDinh[u].x, tdDinh[u].y, CYAN);
			setcolor(RED);
			outtextxy(tdDinh[u].x - 5, tdDinh[u].y - 5, kt[u]);
			Sleep(500);
		}
		if (G[v][u] && check[u]) {
			setcolor(BLACK);
			setbkcolor(LIGHTGRAY);
			textWrite(textX, textY, " --> ");
			//Vẽ đường thẳng nối giữa 2 đỉnh
			if (G[u][v] != 0){
				double arrow_lenght_(8), arrow_degrees_(M_PI / 2);
				double angle = atan2(tdDinh[u].y - tdDinh[v].y, tdDinh[u].x - tdDinh[v].x) + M_PI;
				int xtemp1 = tdDinh[v].x + arrow_lenght_ * cos(angle + arrow_degrees_);
				int ytemp1 = tdDinh[v].y + arrow_lenght_ * sin(angle + arrow_degrees_);
				int xtemp2 = tdDinh[u].x + arrow_lenght_ * cos(angle + arrow_degrees_);
				int ytemp2 = tdDinh[u].y + arrow_lenght_ * sin(angle + arrow_degrees_);

				setcolor(RED);
				line(xtemp1, ytemp1, xtemp2, ytemp2);
				drawArrow(xtemp1, ytemp1, xtemp2, ytemp2, RED);
			}
			else{
				setcolor(RED);
				line(tdDinh[v].x, tdDinh[v].y, tdDinh[u].x, tdDinh[u].y);
				drawArrow(tdDinh[v].x, tdDinh[v].y, tdDinh[u].x, tdDinh[u].y, RED);
			}
			setfillstyle(SOLID_FILL, CYAN);
			//Vẽ lại 2 đỉnh 
			setcolor(BLACK);
			circle(tdDinh[v].x, tdDinh[v].y, R);
			floodfill(tdDinh[v].x, tdDinh[v].y, BLACK);

			setcolor(CYAN);
			circle(tdDinh[v].x, tdDinh[v].y, R);
			floodfill(tdDinh[v].x, tdDinh[v].y, CYAN);
			setcolor(RED);
			setbkcolor(CYAN);
			outtextxy(tdDinh[v].x - 5, tdDinh[v].y - 5, kt[v]);

			// Đỉnh 2
			setcolor(BLACK);
			circle(tdDinh[u].x, tdDinh[u].y, R);
			floodfill(tdDinh[u].x, tdDinh[u].y, BLACK);

			setfillstyle(SOLID_FILL, GREEN);
			setbkcolor(GREEN);
			setcolor(GREEN);
			circle(tdDinh[u].x, tdDinh[u].y, R);
			floodfill(tdDinh[u].x, tdDinh[u].y, GREEN);
			setcolor(RED);
			outtextxy(tdDinh[u].x - 5, tdDinh[u].y - 5, kt[u]);
			Sleep(700);

			findSCCDFS(G, tdDinh, soDinh, u, check, textX, textY, kt);
		}
	}
}

void dijkstraAlgorithmSelected(GRAPH &g){
	int textX = 5, textY = KHUNGVE_BOTTOM + 30;
	setbkcolor(LIGHTGRAY);
	setcolor(RED);

	//Kiểm tra điều kiện tồn tại đồ thị
	bool check = false;
	for (int i = 1; i <= g.soDinh; i++){
		for (int j = 1; j <= g.soDinh; j++){
			if (g.G[i][j] != 0){
				check = true;
				break;
			}
		}
	}
	if (g.soDinh == 0){
		outtextxy(textX, textY, "DO THI CHUA TON TAI. VUI LONG KIEM TRA LAI!!");
		setcolor(LIGHTGRAY);
		Sleep(1000);
		outtextxy(textX, textY, "DO THI CHUA TON TAI. VUI LONG KIEM TRA LAI!!");
		return;
	}
	else if (g.soDinh == 1){
		outtextxy(textX, textY, "TON TAI CHI 1 DINH. KHONG THUC HIEN TIM DUONG!!");
		setcolor(LIGHTGRAY);
		Sleep(1000);
		outtextxy(textX, textY, "TON TAI CHI 1 DINH. KHONG THUC HIEN TIM DUONG!!");
		return;
	}
	else if (check == false){
		outtextxy(textX, textY, "CHUA THIET LAP TRONG SO. VUI LONG KIEM TRA LAI!!");
		setcolor(LIGHTGRAY);
		Sleep(1000);
		outtextxy(textX, textY, "CHUA THIET LAP TRONG SO. VUI LONG KIEM TRA LAI!!");
		return;
	}
	textWriteln(textX, textY, "VUI LONG CHON 2 DINH X, Y CAN TIM !!");

	//Chọn 2 đỉnh để tìm đường đi ngắn nhất
	int x, y;
	int dinhDau = 0, dinhCuoi = 0;
	int solanChon = 0;
	while (1){
		if (solanChon == 2) break;
		if (ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, x, y);

			//Kiểm tra điểm click có thuộc đỉnh nào
			for (int i = 1; i <= g.soDinh; i++){
				if (lenghLine(x, y, g.tdDinh[i].x, g.tdDinh[i].y) <= R){
					if (solanChon == 0){
						solanChon++;
						dinhDau = i;
					}
					else if (solanChon == 1 && dinhDau != i){
						dinhCuoi = i;
						solanChon++;
					}

					//	Tô lại màu cho đỉnh vừa chọn
					if (solanChon <= 2){
						setfillstyle(SOLID_FILL, LIGHTGREEN);
						setcolor(LIGHTGREEN);
						circle(g.tdDinh[i].x, g.tdDinh[i].y, R);
						floodfill(g.tdDinh[i].x, g.tdDinh[i].y, LIGHTGREEN);
						setcolor(RED);
						setbkcolor(LIGHTGREEN);
						outtextxy(g.tdDinh[i].x - 5, g.tdDinh[i].y - 5, kiTu[i]);
					}
				}
			}
		}
	}

	// Khởi tạo 
	int *L = new int[g.soDinh + 1];			// Tập L chứa độ dài từ đỉnh đầu đến đỉnh L[u]
	bool *T = new bool[g.soDinh + 1];		// Tập T dánh dấu đỉnh đã xét hay chưa
	int *prev = new int[g.soDinh + 1];		// prev chứa đỉnh liền kề đi trước nó
	STACK st;								// Chứa tập hợp đường đi
	bool coDuongDi = true;

	st.sp = -1;
	for (int i = 0; i <= g.soDinh; i++){
		T[i] = true;
		L[i] = oo;
		prev[i] = -1;
	}

	L[dinhDau] = 0;	   // độ dài tính từ đỉnh bắt đầu là 0

	// Vòng lặp đến khi đỉnh Cuối được xét 
	while (T[dinhCuoi]){

		// Tìm đỉnh có độ dài nhỏ nhất còn nằm trong T
		int min = oo;
		int v = -1;
		for (int i = 1; i <= g.soDinh; i++){
			if (T[i] == true && min > L[i]){
				min = L[i];
				v = i;
			}
		}

		// Nếu không tìm thấy thì kết thúc	vòng lặp
		if (v == -1){
			coDuongDi = false;
			break;
		}

		// Loại V ra khỏi tập T
		T[v] = false;

		// Duyệt các đỉnh nổi từ v 
		for (int i = 1; i <= g.soDinh; i++){
			// Tồn tại cạch liền kề và đỉnh đó chưa xét
			if (g.G[v][i] != 0 && T[i] == true){
				if (L[i] > (L[v] + g.G[v][i])){			  // Nếu độ dài L[i] lớn hơn độ dài của V + độ dài từ V -> i
					L[i] = L[v] + g.G[v][i];			  // Cập nhật độ dài L[i] và prev
					prev[i] = v;
				}
			}
		}
	}

	// Kiểm tra đỉnh cuối đã được xét hay chưa
	if (!T[dinhCuoi])  {
		int i = dinhCuoi;
		pushStack(st, dinhCuoi);
		do{
			i = prev[i];
			pushStack(st, i);
		} while (i != dinhDau);
	}
	// Trường hợp không tìm được đường đi nào
	else{
		textX = 5, textY = KHUNGVE_BOTTOM + 30;
		setcolor(LIGHTGRAY);
		setbkcolor(LIGHTGRAY);
		textWriteln(textX, textY, "VUITLONGTCHONT2TDINHTX,TYTCANTTIM !!");
		textX = 5, textY = KHUNGVE_BOTTOM + 30;
		setcolor(RED);
		textWriteln(textX, textY, "KHONG TIM DUOC DUONG DI!!");

		Sleep(1500);
		setfillstyle(SOLID_FILL, DARKGRAY);
		bar(KHUNGVE_LEFT + 53, KHUNGVE_TOP + 1, KHUNGVE_RIGHT, KHUNGVE_BOTTOM - 1);
		setfillstyle(SOLID_FILL, LIGHTGRAY);
		bar(LOG_LEFT + 2, LOG_TOP + 10, LOG_RIGHT, LOG_BOTTOM);
		drawGraph(g);
		return;
	}
	/* DEMO đường đi trên màn hình	*/
	textX = 5, textY = KHUNGVE_BOTTOM + 30;
	setcolor(LIGHTGRAY);
	setbkcolor(LIGHTGRAY);
	textWriteln(textX, textY, "VUITLONGTCHONT2TDINHTX,TYTCANTTIM !!");
	textX = 5, textY = KHUNGVE_BOTTOM + 30;
	setcolor(RED);
	textWriteln(textX, textY, "DANG TIM .....");

	int U, V = 0;
	int dem = 1;
	char trongSo[10];
	popStack(st, U);

	Sleep(1000);
	while (!empty(st)){
		if (dem != 1){
			U = V;
		}
		popStack(st, V);
		dem++;

		//Vẽ đỉnh U
		setbkcolor(LIGHTGRAY);
		setcolor(BLACK);
		textWrite(textX, textY, kiTu[U]);
		textWrite(textX, textY, " --> ");
		setfillstyle(SOLID_FILL, CYAN);
		setbkcolor(CYAN);
		setcolor(CYAN);
		circle(g.tdDinh[U].x, g.tdDinh[U].y, R);
		floodfill(g.tdDinh[U].x, g.tdDinh[U].y, CYAN);
		setcolor(RED);
		outtextxy(g.tdDinh[U].x - 5, g.tdDinh[U].y - 5, kiTu[U]);
		Sleep(1000);

		// Vẽ line(U, V)
		if (g.G[V][U] != 0){
			double arrow_lenght_(8), arrow_degrees_(M_PI / 2);
			double angle = atan2(g.tdDinh[V].y - g.tdDinh[U].y, g.tdDinh[V].x - g.tdDinh[U].x) + M_PI;
			int xtemp1 = g.tdDinh[U].x + arrow_lenght_ * cos(angle + arrow_degrees_);
			int ytemp1 = g.tdDinh[U].y + arrow_lenght_ * sin(angle + arrow_degrees_);
			int xtemp2 = g.tdDinh[V].x + arrow_lenght_ * cos(angle + arrow_degrees_);
			int ytemp2 = g.tdDinh[V].y + arrow_lenght_ * sin(angle + arrow_degrees_);

			setcolor(RED);
			line(xtemp1, ytemp1, xtemp2, ytemp2);
			drawArrow(xtemp1, ytemp1, xtemp2, ytemp2, RED);
			setcolor(RED);
			setbkcolor(DARKGRAY);
			_itoa(g.G[U][V], trongSo, 10);
			outtextxy((xtemp1 + xtemp2) / 2, (ytemp1 + ytemp2) / 2, trongSo);
		}
		else{
			setcolor(RED);
			line(g.tdDinh[U].x, g.tdDinh[U].y, g.tdDinh[V].x, g.tdDinh[V].y);
			drawArrow(g.tdDinh[U].x, g.tdDinh[U].y, g.tdDinh[V].x, g.tdDinh[V].y, RED);
			setcolor(RED);
			setbkcolor(DARKGRAY);
			_itoa(g.G[U][V], trongSo, 10);
			outtextxy((g.tdDinh[U].x + g.tdDinh[V].x) / 2 + 15, (g.tdDinh[U].y + g.tdDinh[V].y) / 2 + 5, trongSo);
		}
		//Vẽ lại 2 đỉnh 
		setfillstyle(SOLID_FILL, BLACK);
		setcolor(BLACK);
		circle(g.tdDinh[U].x, g.tdDinh[U].y, R);
		floodfill(g.tdDinh[U].x, g.tdDinh[U].y, BLACK);

		setcolor(CYAN);
		setfillstyle(SOLID_FILL, CYAN);
		circle(g.tdDinh[U].x, g.tdDinh[U].y, R);
		floodfill(g.tdDinh[U].x, g.tdDinh[U].y, CYAN);
		setcolor(RED);
		setbkcolor(CYAN);
		outtextxy(g.tdDinh[U].x - 5, g.tdDinh[U].y - 5, kiTu[U]);

		// Đỉnh 2
		setfillstyle(SOLID_FILL, BLACK);
		setcolor(BLACK);
		circle(g.tdDinh[V].x, g.tdDinh[V].y, R);
		floodfill(g.tdDinh[V].x, g.tdDinh[V].y, BLACK);

		setfillstyle(SOLID_FILL, GREEN);
		setbkcolor(GREEN);
		setcolor(GREEN);
		circle(g.tdDinh[V].x, g.tdDinh[V].y, R);
		floodfill(g.tdDinh[V].x, g.tdDinh[V].y, GREEN);
		setcolor(RED);
		outtextxy(g.tdDinh[V].x - 5, g.tdDinh[V].y - 5, kiTu[V]);
		Sleep(1000);
	}

	//Vẽ lại đỉnh cuối
	setfillstyle(SOLID_FILL, BLACK);
	setcolor(BLACK);
	circle(g.tdDinh[V].x, g.tdDinh[V].y, R);
	floodfill(g.tdDinh[V].x, g.tdDinh[V].y, BLACK);

	setcolor(CYAN);
	setfillstyle(SOLID_FILL, CYAN);
	circle(g.tdDinh[V].x, g.tdDinh[V].y, R);
	floodfill(g.tdDinh[V].x, g.tdDinh[V].y, CYAN);
	setcolor(RED);
	setbkcolor(CYAN);
	outtextxy(g.tdDinh[V].x - 5, g.tdDinh[V].y - 5, kiTu[V]);
	setbkcolor(LIGHTGRAY);
	setcolor(BLACK);
	textWrite(textX, textY, kiTu[V]);

	//In độ dài nhỏ nhất
	char s[10];
	setcolor(BLACK);
	textWriteln(textX, textY, "");
	textWrite(textX, textY, "DUONG DI NGAN NHAT LA: ");
	_itoa(L[dinhCuoi], s, 10);
	textWrite(textX, textY, s);


	//Bật tính năng thoát
	textX = 5, textY = KHUNGVE_BOTTOM + 30;
	setcolor(LIGHTGRAY);
	setbkcolor(LIGHTGRAY);
	textWriteln(textX, textY, "VUITLONGTCHONT2TDINHTX,TYTCANTTIM !!");
	textX = 5, textY = KHUNGVE_BOTTOM + 30;
	setcolor(RED);
	textWriteln(textX, textY, "TIM KIEM HOAN THANH. ENTER DE TIEP TUC CHUONG TRINH !!");

	delete prev, T, L;
	while (1){
		if (ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if (checkClick(x, y) == DIJKSTRA_ALG){
				setfillstyle(SOLID_FILL, DARKGRAY);
				bar(KHUNGVE_LEFT + 53, KHUNGVE_TOP + 1, KHUNGVE_RIGHT, KHUNGVE_BOTTOM - 1);
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(LOG_LEFT + 2, LOG_TOP + 10, LOG_RIGHT, LOG_BOTTOM);
				drawGraph(g);
				return;
			}
		}
		while (kbhit()){
			if (char a = getch() == 13){
				setfillstyle(SOLID_FILL, DARKGRAY);
				bar(KHUNGVE_LEFT + 53, KHUNGVE_TOP + 1, KHUNGVE_RIGHT, KHUNGVE_BOTTOM - 1);
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(LOG_LEFT + 2, LOG_TOP + 10, LOG_RIGHT, LOG_BOTTOM);
				drawGraph(g);
				return;
			}
		}
	}
}

void initCheck(bool check[], int n){
	for (int i = 0; i <= n; i++){
		check[i] = true;
	}
}

bool kiemTraLienThong(bool check[], int n){
	for (int i = 1; i <= n; i++){
		if (check[i]) return true;		 // Nếu tồn tại đỉnh chưa xét => đỉnh trụ => trả về true
	}
	return false;
}
void timTruSelected(GRAPH &g){
	int textX = 5, textY = KHUNGVE_BOTTOM + 30;
	setbkcolor(LIGHTGRAY);
	setcolor(RED);
	// Kiểm tra đồ thị đã tồn tại hay chưa?
	if (g.soDinh == 0){
		outtextxy(textX, textY, "DO THI CHUA TON TAI. VUI LONG KIEM TRA LAI!!");
		setcolor(LIGHTGRAY);
		Sleep(1000);
		outtextxy(textX, textY, "DO THI CHUA TON TAI. VUI LONG KIEM TRA LAI!!");
		return;
	}

	textWriteln(textX, textY, "DANG TIM .....");

	int *low = new int[g.soDinh + 1];
	int *numbering = new int[g.soDinh + 1];
	STACK st;
	STACK *L = new STACK[g.soDinh + 1];
	int count = 0;
	int conponentCount = 0;
	//Khởi tạo thông số mặc định
	st.sp = -1;
	for (int i = 0; i <= g.soDinh; i++){
		low[i] = numbering[i] = 0;
		L[i].sp = -1;
	}

	//Gọi hàm SCC tìm thành phần liên thông
	for (int i = 1; i <= g.soDinh; i++){
		if (!numbering[i]){
			SCC(i, count, conponentCount, g, L, st, low, numbering);
		}
	}

	delete[]  numbering, low;
	//
	int *A = new int[g.soDinh + 1];
	int soDinhTru = 0;
	int n;
	char kt[26][2];
	for (int i = 1; i < 26; i++){
		kt[i][1] = 0;
	}

	for (int i = 1; i <= conponentCount; i++){
		n = L[i].sp + 1;
		int j = 0;
		if (n == 1)	 continue;
		while (!empty(L[i])){
			popStack(L[i], A[j++]);
		}

		// Tạo ma trận kề của thành phần liên thuộc
		int **G = new int *[n + 1];
		TOADO *td = new TOADO[n + 1];
		bool   *chuaXet = new bool[n + 1];
		for (int i = 0; i <= n; i++){
			G[i] = new int[n + 1];
			chuaXet[i] = true;
		}

		for (int u = 0; u < n; u++){
			for (int v = 0; v < n; v++){
				G[u + 1][v + 1] = g.G[A[u]][A[v]];
			}
			td[u + 1] = g.tdDinh[A[u]];
			kt[u + 1][0] = kiTu[A[u]][0];
		}
		// Thực hiện duyệt DFS trên từng thành phần liên thông
		bool *check = new bool[n + 1];
		initCheck(check, n);

		for (int q = 1; q <= n; q++){
			initCheck(check, n);
			int *lowTemp = new int[n + 1];
			int *numTemp = new int[n + 1];
			STACK stTemp;
			stTemp.sp = -1;
			int countTemp = 0;
			int conponentTemp = 0;
			for (int p = 0; p <= n; p++){
				lowTemp[p] = numTemp[p] = 0;
			}
			check[q] = false;
			for (int x = 1; x <= n; x++){
				if (!numTemp[x] && check[x] == true){
					SCC(x, countTemp, conponentTemp, G, n, stTemp, lowTemp, numTemp, check);
				}
			}

			if (conponentTemp > 1){
				soDinhTru++;
				// Xử lý đỉnh trụ này ở đây
				setcolor(BLACK);
				setbkcolor(LIGHTGRAY);
				textWrite(textX, textY, kt[q]);
				textWrite(textX, textY, "  ");
				//
				setfillstyle(SOLID_FILL, CYAN);
				setcolor(CYAN);
				circle(td[q].x, td[q].y, R);
				floodfill(td[q].x, td[q].y, CYAN);
				setcolor(RED);
				setbkcolor(CYAN);
				outtextxy(td[q].x - 5, td[q].y - 5, kt[q]);
				Sleep(700);
			}
			delete[] lowTemp, numTemp;
		}

		// Giải phóng vùng nhớ cho ma trận kề
		for (int q = 0; q < n; q++){
			delete[] G[q];
		}
		delete[] G, td, chuaXet, check;
	}

	// Chức năng thoát
	textX = 5, textY = KHUNGVE_BOTTOM + 30;
	setbkcolor(LIGHTGRAY);
	setcolor(RED);
	if (soDinhTru == 0){
		textWriteln(textX, textY, "KHONG CO DINH TRU. ENTER DE TIEP TUC CHUONG TRINH!!");
	}
	else{
		textWriteln(textX, textY, "HOAN TAT TIM KIEM. ENTER DE TIEP TUC CHUONG TRINH!!");
	}
	int x, y;
	while (1){
		if (ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if (checkClick(x, y) == TIM_TRU){
				setfillstyle(SOLID_FILL, DARKGRAY);
				bar(KHUNGVE_LEFT + 53, KHUNGVE_TOP + 1, KHUNGVE_RIGHT, KHUNGVE_BOTTOM - 1);
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(LOG_LEFT + 2, LOG_TOP + 10, LOG_RIGHT, LOG_BOTTOM);
				drawGraph(g);
				return;
			}
		}
		while (kbhit()){
			if (char a = getch() == 13){
				setfillstyle(SOLID_FILL, DARKGRAY);
				bar(KHUNGVE_LEFT + 53, KHUNGVE_TOP + 1, KHUNGVE_RIGHT, KHUNGVE_BOTTOM - 1);
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(LOG_LEFT + 2, LOG_TOP + 10, LOG_RIGHT, LOG_BOTTOM);
				drawGraph(g);
				return;
			}
		}
	}
}

void timCanhCauSelected(GRAPH &g){
	int textX = 5, textY = KHUNGVE_BOTTOM + 30;
	setbkcolor(LIGHTGRAY);
	setcolor(RED);
	// Kiểm tra đồ thị đã tồn tại hay chưa?
	if (g.soDinh == 0){
		outtextxy(textX, textY, "DO THI CHUA TON TAI. VUI LONG KIEM TRA LAI!!");
		setcolor(LIGHTGRAY);
		Sleep(1000);
		outtextxy(textX, textY, "DO THI CHUA TON TAI. VUI LONG KIEM TRA LAI!!");
		return;
	}

	textWriteln(textX, textY, "DANG TIM .....");

	int *low = new int[g.soDinh + 1];
	int *numbering = new int[g.soDinh + 1];
	STACK st;
	STACK *L = new STACK[g.soDinh + 1];
	int count = 0;
	int conponentCount = 0;
	//Khởi tạo thông số mặc định
	st.sp = -1;
	for (int i = 0; i <= g.soDinh; i++){
		low[i] = numbering[i] = 0;
		L[i].sp = -1;
	}

	//Gọi hàm SCC tìm thành phần liên thông
	for (int i = 1; i <= g.soDinh; i++){
		if (!numbering[i]){
			SCC(i, count, conponentCount, g, L, st, low, numbering);
		}
	}
	// Tạo mảng kiểm tra các cạnh cầu
	bool checkCC[MAXSIZE][MAXSIZE];
	for (int i = 1; i <= g.soDinh; i++){
		for (int j = 1; j <= g.soDinh; j++){
			checkCC[i][j] = true;
		}
	}
	//
	int *A = new int[g.soDinh + 1];
	int n;							// 	Số đỉnh của mỗi thành phần liên thông
	char kt[26][2];
	for (int i = 1; i < 26; i++){
		kt[i][1] = 0;
	}

	int demCanhCau = 0;
	for (int i = 1; i <= conponentCount; i++){
		n = L[i].sp + 1;
		int j = 0;
		if (n == 1)	 continue;
		while (!empty(L[i])){
			popStack(L[i], A[j++]);
		}

		// Tạo ma trận kề của thành phần liên thuộc
		int **G = new int *[n + 1];
		TOADO *td = new TOADO[n + 1];
		bool   *chuaXet = new bool[n + 1];
		for (int i = 0; i <= n; i++){
			G[i] = new int[n + 1];
			chuaXet[i] = true;
		}

		for (int u = 0; u < n; u++){
			for (int v = 0; v < n; v++){
				G[u + 1][v + 1] = g.G[A[u]][A[v]];
			}
			td[u + 1] = g.tdDinh[A[u]];
			kt[u + 1][0] = kiTu[A[u]][0];
		}
		// Thực hiện duyệt DFS trên từng thành phần liên thông
		bool *check = new bool[n + 1];
		initCheck(check, n);

		for (int q = 1; q <= n; q++){
			for (int w = 1; w <= n; w++) {
				if (G[q][w] != 0){
					int trongSo = G[q][w];
					G[q][w] = 0;

					int *lowTemp = new int[n + 1];
					int *numTemp = new int[n + 1];
					STACK stTemp;
					stTemp.sp = -1;
					int countTemp = 0;
					int conponentTemp = 0;
					for (int p = 0; p <= n; p++){
						lowTemp[p] = numTemp[p] = 0;
					}
					for (int x = 1; x <= n; x++){
						if (!numTemp[x]){
							SCC(x, countTemp, conponentTemp, G, n, stTemp, lowTemp, numTemp, check);
						}
					}

					if (conponentTemp > 1){
						checkCC[A[q - 1]][A[w - 1]] = false;
						if (checkCC[A[w - 1]][A[q - 1]] == false){			  //   Nếu cung ngược lại cũng là cạnh cầu 
							veCungHaiDinh(g, A[q - 1], A[w - 1], RED, RED);
						}
						else{
							veCungHaiDinh(g, A[q - 1], A[w - 1], RED);
						}
						Sleep(700);
						demCanhCau++;
					}

					G[q][w] = trongSo;
					delete[] lowTemp, numTemp;
				}
			}
		}

		// Giải phóng vùng nhớ cho ma trận kề
		for (int q = 0; q < n; q++){
			delete[] G[q];
		}
		delete[] G;
		delete[] td;
		delete[] chuaXet;
	}
	
	char temp[10];
	setbkcolor(LIGHTGRAY);
	setcolor(BLACK);
	if (demCanhCau == 0){
		textWrite(textX, textY, "KHONG CO CANH CAU NAO!!");
	}else{
		_itoa(demCanhCau, temp, 10);
		textWrite(textX, textY, "SO CANH CAU : ");
		textWrite(textX, textY, temp);
	}
	// Chức năng thoát
	textX = 5, textY = KHUNGVE_BOTTOM + 30;
	setbkcolor(LIGHTGRAY);
	setcolor(RED);
	textWriteln(textX, textY, "HOAN TAT TIM KIEM. ENTER DE TIEP TUC CHUONG TRINH!!");
	int x, y;
	while (1){
		if (ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if (checkClick(x, y) == TIM_CCAU){
				setfillstyle(SOLID_FILL, DARKGRAY);
				bar(KHUNGVE_LEFT + 53, KHUNGVE_TOP + 1, KHUNGVE_RIGHT, KHUNGVE_BOTTOM - 1);
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(LOG_LEFT + 2, LOG_TOP + 10, LOG_RIGHT, LOG_BOTTOM);
				drawGraph(g);
				return;
			}
		}
		while (kbhit()){
			if (char a = getch() == 13){
				setfillstyle(SOLID_FILL, DARKGRAY);
				bar(KHUNGVE_LEFT + 53, KHUNGVE_TOP + 1, KHUNGVE_RIGHT, KHUNGVE_BOTTOM - 1);
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(LOG_LEFT + 2, LOG_TOP + 10, LOG_RIGHT, LOG_BOTTOM);
				drawGraph(g);
				return;
			}
		}
	}
}

bool ktLTYeu(GRAPH &g){
	bool *check = new bool[g.soDinh + 1];
	bool kt = false;
	initCheck(check, g.soDinh);

	int temp = 0;
	for (int i = 1; i <= g.soDinh; i++){
		DFSAlgorithm(g.G, g.soDinh,i, check);

		for (int j = 1; j <= g.soDinh; j++){
			if (check[j] == false)
				temp++;
		}
		if (temp == g.soDinh){
			kt = true;
			break;
		}else{
			initCheck(check, g.soDinh);
		}
	}

	return kt;
}

bool ktEuler(GRAPH &g){
	if (ktLTYeu(g) == false) return false;
	int bacRa = 0, bacVao = 0;
	for (int i = 1; i <= g.soDinh; i++){
		bacRa = 0, bacVao = 0;
		//Kiểm tra bán bậc ra
		for (int u = 1; u <= g.soDinh; u++){
			if (g.G[i][u] != 0)
				bacRa++;
		}
		//Kiểm tra bán bậc vào
		for (int v = 1; v <= g.soDinh; v++){
			if (g.G[v][i] != 0)
				bacVao++;
		}
		if (bacRa != bacVao || bacVao == 0)	{
			return false;
		}
	}
	return true;
}

void findEulerCycleSelected(int u, GRAPH &g){
	int textX = 5, textY = KHUNGVE_BOTTOM + 30;
	setbkcolor(LIGHTGRAY);
	setcolor(RED);
	// Kiểm tra đồ thị đã tồn tại hay chưa?
	if (g.soDinh == 0){
		outtextxy(textX, textY, "DO THI CHUA TON TAI. VUI LONG KIEM TRA LAI!!");
		setcolor(LIGHTGRAY);
		Sleep(1000);
		outtextxy(textX, textY, "DO THI CHUA TON TAI. VUI LONG KIEM TRA LAI!!");
		return;
	}

	//Kiểm tra có tồn tại chu trình Euler hay không
	if (ktEuler(g) == false){
		outtextxy(textX, textY, "DO THI KHONG CO CHU TRINH EULER!!");
		setcolor(LIGHTGRAY);
		Sleep(1000);
		outtextxy(textX, textY, "DO THI KHONG CO CHU TRINH EULER!!");
		return ;
	}
	
	//Tồn tại chu trình euler
	setcolor(RED);
	textWriteln(textX, textY, "DANG DUYET...");

	bool **G = new bool* [g.soDinh + 1];
	for (int i = 0; i <= g.soDinh; i++){
		G[i] = new bool[g.soDinh + 1];
	}
	
	for (int i = 1; i <= g.soDinh; i++){
		for (int j = 1; j <= g.soDinh; j++){
			if(g.G[i][j] > 0) G[i][j] = true;
			else   G[i][j] = false;
		}
	}

	//Khởi tạo 
	STACK stack;
	STACK CE;
	stack.sp = -1;
	CE.sp = -1;
	pushStack(stack, u);

	// Bước lặp
	do{
		int s = getStack(stack);
		int x = 1;
		//Xác định vị trí kề với s: x 
		while (x <= g.soDinh && G[s][x] == false) {
			x++;
		}
		if (x > g.soDinh){  // Không tồn tại đỉnh ke nao
			popStack(stack, s);
			pushStack(CE, s);
		}
		else{
			pushStack(stack, x);
			G[s][x] = false;
		}
	} while (!empty(stack));

	// Thực hiện in chu trình
	int xcolor;
	bool *dinhChuaIn = new bool[g.soDinh + 1];
	initCheck(dinhChuaIn, g.soDinh);
	int U, V = 0;
	int dem = 1;
	char trongSo[10];
	popStack(CE, U);

	Sleep(1000);
	while (!empty(CE)){
		if (dem != 1){
			U = V;
		}
		dinhChuaIn[U] = false;
		popStack(CE, V);
		dem++;

		//Vẽ đỉnh U
		setbkcolor(LIGHTGRAY);
		setcolor(BLACK);
		textWrite(textX, textY, kiTu[U]);
		textWrite(textX, textY, " --> ");
		setfillstyle(SOLID_FILL, CYAN);
		setbkcolor(CYAN);
		setcolor(CYAN);
		circle(g.tdDinh[U].x, g.tdDinh[U].y, R);
		floodfill(g.tdDinh[U].x, g.tdDinh[U].y, CYAN);
		setcolor(RED);
		outtextxy(g.tdDinh[U].x - 5, g.tdDinh[U].y - 5, kiTu[U]);
		Sleep(1000);

		// Vẽ line(U, V)
		if (g.G[V][U] != 0){
			double arrow_lenght_(8), arrow_degrees_(M_PI / 2);
			double angle = atan2(g.tdDinh[V].y - g.tdDinh[U].y, g.tdDinh[V].x - g.tdDinh[U].x) + M_PI;
			int xtemp1 = g.tdDinh[U].x + arrow_lenght_ * cos(angle + arrow_degrees_);
			int ytemp1 = g.tdDinh[U].y + arrow_lenght_ * sin(angle + arrow_degrees_);
			int xtemp2 = g.tdDinh[V].x + arrow_lenght_ * cos(angle + arrow_degrees_);
			int ytemp2 = g.tdDinh[V].y + arrow_lenght_ * sin(angle + arrow_degrees_);

			setcolor(RED);
			line(xtemp1, ytemp1, xtemp2, ytemp2);
			drawArrow(xtemp1, ytemp1, xtemp2, ytemp2, RED);
			setcolor(RED);
			setbkcolor(DARKGRAY);
			_itoa(g.G[U][V], trongSo, 10);
			outtextxy((xtemp1 + xtemp2) / 2, (ytemp1 + ytemp2) / 2, trongSo);
		}
		else{
			setcolor(RED);
			line(g.tdDinh[U].x, g.tdDinh[U].y, g.tdDinh[V].x, g.tdDinh[V].y);
			drawArrow(g.tdDinh[U].x, g.tdDinh[U].y, g.tdDinh[V].x, g.tdDinh[V].y, RED);
			setcolor(RED);
			setbkcolor(DARKGRAY);
			_itoa(g.G[U][V], trongSo, 10);
			outtextxy((g.tdDinh[U].x + g.tdDinh[V].x) / 2 + 15, (g.tdDinh[U].y + g.tdDinh[V].y) / 2 + 5, trongSo);
		}
		//Vẽ lại 2 đỉnh 
		setfillstyle(SOLID_FILL, BLACK);
		setcolor(BLACK);
		circle(g.tdDinh[U].x, g.tdDinh[U].y, R);
		floodfill(g.tdDinh[U].x, g.tdDinh[U].y, BLACK);

		setcolor(CYAN);
		setfillstyle(SOLID_FILL, CYAN);
		circle(g.tdDinh[U].x, g.tdDinh[U].y, R);
		floodfill(g.tdDinh[U].x, g.tdDinh[U].y, CYAN);
		setcolor(RED);
		setbkcolor(CYAN);
		outtextxy(g.tdDinh[U].x - 5, g.tdDinh[U].y - 5, kiTu[U]);

		// Đỉnh 2
		setfillstyle(SOLID_FILL, BLACK);
		setcolor(BLACK);
		circle(g.tdDinh[V].x, g.tdDinh[V].y, R);
		floodfill(g.tdDinh[V].x, g.tdDinh[V].y, BLACK);

		if (dinhChuaIn[V])
			xcolor = GREEN;
		else xcolor = CYAN;
		setfillstyle(SOLID_FILL, xcolor);
		setbkcolor(xcolor);
		setcolor(xcolor);
		circle(g.tdDinh[V].x, g.tdDinh[V].y, R);
		floodfill(g.tdDinh[V].x, g.tdDinh[V].y, xcolor);
		setcolor(RED);
		outtextxy(g.tdDinh[V].x - 5, g.tdDinh[V].y - 5, kiTu[V]);
		Sleep(1000);
	}
	setbkcolor(LIGHTGRAY);
	setcolor(BLACK);
	textWrite(textX, textY, kiTu[V]);

	//Bật tính năng thoát
	textX = 5, textY = KHUNGVE_BOTTOM + 30;
	setcolor(LIGHTGRAY);
	setbkcolor(LIGHTGRAY);
	textWriteln(textX, textY, "VUITLONGTCHONT2TDINHTX,TYTCANTTIM !!");
	textX = 5, textY = KHUNGVE_BOTTOM + 30;
	setcolor(RED);
	textWriteln(textX, textY, "TIM KIEM HOAN THANH. ENTER DE TIEP TUC CHUONG TRINH !!");
   
	int x, y;
	while (1){
		if (ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if (checkClick(x, y) == EULER){
				setfillstyle(SOLID_FILL, DARKGRAY);
				bar(KHUNGVE_LEFT + 53, KHUNGVE_TOP + 1, KHUNGVE_RIGHT, KHUNGVE_BOTTOM - 1);
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(LOG_LEFT + 2, LOG_TOP + 10, LOG_RIGHT, LOG_BOTTOM);
				drawGraph(g);
				return;
			}
		}
		while (kbhit()){
			if (char a = getch() == 13){
				setfillstyle(SOLID_FILL, DARKGRAY);
				bar(KHUNGVE_LEFT + 53, KHUNGVE_TOP + 1, KHUNGVE_RIGHT, KHUNGVE_BOTTOM - 1);
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(LOG_LEFT + 2, LOG_TOP + 10, LOG_RIGHT, LOG_BOTTOM);
				drawGraph(g);
				return;
			}
		}
	}

	//Giải phóng bộ nhớ 
	delete[] dinhChuaIn;
	for (int i = 0; i <= g.soDinh; i++){
		delete[] G[i];
	}
	delete[] G;
}

bool isHamiltonCycle(GRAPH &g){
	int *low = new int[g.soDinh + 1];
	int *numbering = new int[g.soDinh + 1];
	STACK st;
	STACK *L = new STACK[g.soDinh + 1];
	int count = 0;
	int conponentCount = 0;
	//Khởi tạo thông số mặc định
	st.sp = -1;
	for (int i = 0; i <= g.soDinh; i++){
		low[i] = numbering[i] = 0;
		L[i].sp = -1;
	}

	//Gọi hàm SCC tìm thành phần liên thông
	for (int i = 1; i <= g.soDinh; i++){
		if (!numbering[i]){
			SCC(i, count, conponentCount, g, L, st, low, numbering);
		}
	}
	delete[] low, numbering, L;
	if (conponentCount != 1) return false;

	for (int i = 1; i <= g.soDinh; i++){
		int dauRa = 0, dauVao = 0;
		for (int j = 1; j <= g.soDinh; j++){
			if (g.G[i][j] != 0)	dauRa++;
			if (g.G[j][i] != 0) dauVao++;
		}
		if (dauRa < g.soDinh / 2 || dauVao < g.soDinh / 2)
			return false;
	}
	return true;
}

void findHamiltonCycleSelected(GRAPH &g){
	int textX = 5, textY = KHUNGVE_BOTTOM + 30;
	setbkcolor(LIGHTGRAY);
	setcolor(RED);
	bool timDuocCT = false;

	// Kiểm tra đồ thị đã tồn tại hay chưa?
	if (g.soDinh == 0){
		outtextxy(textX, textY, "DO THI CHUA TON TAI. VUI LONG KIEM TRA LAI!!");
		setcolor(LIGHTGRAY);
		Sleep(1000);
		outtextxy(textX, textY, "DO THI CHUA TON TAI. VUI LONG KIEM TRA LAI!!");
		return;
	}

	//Kiểm tra có tồn tại chu trình Euler hay không
	if (isHamiltonCycle(g) == false){
		outtextxy(textX, textY, "DO THI KHONG CO CHU TRINH HAMILTON!!");
		setcolor(LIGHTGRAY);
		Sleep(1000);
		outtextxy(textX, textY, "DO THI KHONG CO CHU TRINH HAMILTON!!");
		return;
	}

	// Có chu trình hamilton 
	bool *check = new bool[g.soDinh + 1];
	initCheck(check, g.soDinh);
	int *duongDi = new int[g.soDinh + 1];
	for (int i = 0; i <= g.soDinh; i++){
		duongDi[i] = 0;
	}

	int V = rand() % g.soDinh + 1;
	duongDi[1] = V;
	check[V] = false;

	setbkcolor(LIGHTGRAY);
	setcolor(RED);
	textWriteln(textX, textY, "DANG TIM...");

	// Hàm đệ quy tìm chu trình hamilton
	hamiltonAlgorithm(2, g, duongDi, check, timDuocCT);

	textX = 5, textY = KHUNGVE_BOTTOM + 30;
	setbkcolor(LIGHTGRAY);
	setcolor(LIGHTGRAY);
	textWriteln(textX, textY, "DANG TIM...");
	textX = 5, textY = KHUNGVE_BOTTOM + 30;
	setbkcolor(LIGHTGRAY);
	setcolor(RED);
	textWriteln(textX, textY, "DA TIM XONG! EMTER DE TIEP TUC!!");

	//Giải phóng bộ nhớ 
	delete[] check, duongDi;

	// Bạt tính năng thoát
	int x, y;
	while (1){
		if (ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if (checkClick(x, y) == HAMILTON){
				setfillstyle(SOLID_FILL, DARKGRAY);
				bar(KHUNGVE_LEFT + 53, KHUNGVE_TOP + 1, KHUNGVE_RIGHT, KHUNGVE_BOTTOM - 1);
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(LOG_LEFT + 2, LOG_TOP + 10, LOG_RIGHT, LOG_BOTTOM);
				drawGraph(g);
				return;
			}
		}
		while (kbhit()){
			if (char a = getch() == 13){
				setfillstyle(SOLID_FILL, DARKGRAY);
				bar(KHUNGVE_LEFT + 53, KHUNGVE_TOP + 1, KHUNGVE_RIGHT, KHUNGVE_BOTTOM - 1);
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(LOG_LEFT + 2, LOG_TOP + 10, LOG_RIGHT, LOG_BOTTOM);
				drawGraph(g);
				return;
			}
		}
	}
}

void hamiltonAlgorithm(int pos, GRAPH &g, int duongDi[], bool check[], bool &timDuocCT){
	if (pos == g.soDinh + 1){
		if (g.G[duongDi[pos - 1]][duongDi[1]] != 0){
			timDuocCT = true;
			int temp = 0;
			duongDi[pos] = duongDi[1];
			pos++;
			inDuongDiXY(duongDi, pos, g, temp);

			// Ve lai dinh V
			int V = duongDi[1];
			setcolor(BLACK);
			circle(g.tdDinh[V].x, g.tdDinh[V].y, R);
			floodfill(g.tdDinh[V].x, g.tdDinh[V].y, BLACK);

			setcolor(CYAN);
			circle(g.tdDinh[V].x, g.tdDinh[V].y, R);
			floodfill(g.tdDinh[V].x, g.tdDinh[V].y, CYAN);
			setcolor(RED);
			setbkcolor(CYAN);
			outtextxy(g.tdDinh[V].x - 5, g.tdDinh[V].y - 5, kiTu[V]);
			return;
		}
	}

	// Tìm đỉnh kề tiếp theo
	for (int i = 1; i <= g.soDinh; i++){
		if (g.G[duongDi[pos - 1]][i] != 0 && check[i] == true && timDuocCT == false){
			check[i] = false;
			duongDi[pos] = i;
			hamiltonAlgorithm(pos + 1, g, duongDi, check, timDuocCT);
			check[i] = true;
			duongDi[pos] = 0;
		}
	}
}

void moveVertexSelected(GRAPH &g){
	int textX = 5, textY = KHUNGVE_BOTTOM + 30;
	if (g.soDinh == 0){
		setcolor(RED);
		setbkcolor(LIGHTGRAY);
		outtextxy(textX, textY, "CHUA TON TAI DINH!!!");
		textX = 5, textY = KHUNGVE_BOTTOM + 30;
		delay(700);
		setcolor(LIGHTGRAY);
		outtextxy(textX, textY, "CHUA TON TAI DINH!!!");
		return;
	}

	int x, y;
	setmousequeuestatus(WM_MOUSEMOVE);
	while (1){
		if (ismouseclick(WM_LBUTTONDOWN) && !ismouseclick(WM_LBUTTONUP)){
			x = mousex();
			y = mousey();
			clearmouseclick(WM_LBUTTONDOWN);
			// Nếu nhấn vào button DiChuyen thì thoát
			if (checkClick(x, y) == DI_CHUYEN){
				setfillstyle(SOLID_FILL, DARKGRAY);
				bar(KHUNGVE_LEFT + 53, KHUNGVE_TOP + 1, KHUNGVE_RIGHT, KHUNGVE_BOTTOM - 1);
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(LOG_LEFT + 2, LOG_TOP + 10, LOG_RIGHT, LOG_BOTTOM);
				drawGraph(g);
				return;
			}

			//Kiểm tra có chọn đỉnh hay không
			int V = kiemtraClickDinh(g, x, y);
			int moveX = 0, moveY = 0;
			if (V != -1){
				while (!ismouseclick(WM_LBUTTONUP)){
					if (ismouseclick(WM_MOUSEMOVE)){
						moveX = mousex();
						moveY = mousey();
						clearmouseclick(WM_MOUSEMOVE);
						//Thực hiện ẩn đỉnh cũ và vẽ đỉnh mới
						if (kiemTraMouseTrongKhungVe(moveX, moveY)){
							veDinhTheoToaDo(V, g, DARKGRAY, DARKGRAY, DARKGRAY);
							g.tdDinh[V].x = moveX;
							g.tdDinh[V].y = moveY;
							veDinhTheoToaDo(V, g, WHITE, GREEN, RED);
						}
						else break;
					}
				}
			}
		}
		else if (ismouseclick(WM_LBUTTONUP)){
			clearmouseclick(WM_LBUTTONUP);		
		}

		// Tính năng thoát khi nhấn Enter
		while (kbhit()){
			if (char a = getch() == 13){
				setfillstyle(SOLID_FILL, DARKGRAY);
				bar(KHUNGVE_LEFT + 53, KHUNGVE_TOP + 1, KHUNGVE_RIGHT, KHUNGVE_BOTTOM - 1);
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(LOG_LEFT + 2, LOG_TOP + 10, LOG_RIGHT, LOG_BOTTOM);
				drawGraph(g);
				return;
			}
		}
	}

}

void veDinhTheoToaDo(int V, GRAPH &g, int color, int bgColor, int textColor){
	int n = g.soDinh;
	for (int i = 1; i <= n; i++){
		if (g.G[V][i] != 0){
			veCungHaiDinh(g, V, i, color, color);
			setfillstyle(SOLID_FILL, bgColor);
			setcolor(bgColor);
			circle(g.tdDinh[i].x, g.tdDinh[i].y, R);
			floodfill(g.tdDinh[i].x, g.tdDinh[i].y, bgColor);
			setbkcolor(bgColor);
			setcolor(textColor);
			outtextxy(g.tdDinh[i].x - 5, g.tdDinh[i].y - 5, kiTu[i]);
		}
		if (g.G[i][V] != 0 && g.G[V][i] == 0){
			veCungHaiDinh(g, i, V, color, color);
			setfillstyle(SOLID_FILL, bgColor);
			setcolor(bgColor);
			circle(g.tdDinh[i].x, g.tdDinh[i].y, R);
			floodfill(g.tdDinh[i].x, g.tdDinh[i].y, bgColor);
			setbkcolor(bgColor);
			setcolor(textColor);
			outtextxy(g.tdDinh[i].x - 5, g.tdDinh[i].y - 5, kiTu[i]);
		}
	}
	setfillstyle(SOLID_FILL, bgColor);
	setcolor(bgColor);
	circle(g.tdDinh[V].x, g.tdDinh[V].y, R);
	floodfill(g.tdDinh[V].x, g.tdDinh[V].y, bgColor);
	setbkcolor(bgColor);
	setcolor(textColor);
	outtextxy(g.tdDinh[V].x - 5, g.tdDinh[V].y - 5, kiTu[V]);
}

int kiemtraClickDinh(GRAPH &g, int x, int y){
	for (int i = 1; i <= g.soDinh; i++){
		if (lenghLine(x, y, g.tdDinh[i].x, g.tdDinh[i].y) <= R)
			return i;
	}
	return -1;
}

bool kiemTraMouseTrongKhungVe(int x, int y){
	if (x < (KHUNGVE_LEFT + 55 + R)) return false;
	if (x > (KHUNGVE_RIGHT - R)	)	return false;
	if (y < (KHUNGVE_TOP + R)	)	return false;
	if (y > (KHUNGVE_BOTTOM - R))	return false;
	return true;
}

void cleanGraphSelected(GRAPH &g){
	int textX = 5, textY = KHUNGVE_BOTTOM + 30;
	setbkcolor(LIGHTGRAY);
	setcolor(RED);
	char s[10];
	bool check = false;

	if (g.soDinh > 0){
		textWrite(textX, textY, "BAN CO CHAC CHAN XOA DO THI NAY HAY KHONG? (Y/N): ");
		textReadString(textX, textY, s);
		//Xoa ki tu vua in
		textX = 5;
		textY = KHUNGVE_BOTTOM + 30;
		setcolor(LIGHTGRAY);
		textWrite(textX, textY, "BAN CO CHAC CHAN XOA DO THI NAY HAY KHONG? (Y/N): ");
		textWriteln(textX, textY, s);

		if (s[0] == 'y' || s[0] == 'Y')
			check = true;
		else return;
	}

	// Xóa đồ thị
	for (int i = 1; i <= g.soDinh; i++){
		for (int j = 1; j <= g.soDinh; j++){
			g.G[i][j] = 0;
		}
	}		
	g.soDinh = 0;
	setfillstyle(SOLID_FILL, DARKGRAY);
	bar(KHUNGVE_LEFT + 53, KHUNGVE_TOP + 1, KHUNGVE_RIGHT, KHUNGVE_BOTTOM - 1);
	drawAdjMatrixSelected(g);
	drawGraph(g);
}
