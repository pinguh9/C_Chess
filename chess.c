#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
enum name { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };

typedef struct piece
{
	_Bool isempty;//말이 있으면 0 없으면 1.
	enum name n;
	_Bool color;//1이면 흑 0이면 백
	_Bool alive;//1이면 생존 0이면 사망
}Piece;

void  Initialize_map(Piece* (*p)[8]) {//맵 초기화
	
	for (int i = 0; i < 8; i++) {//폰 초기화
		//흑색 폰 초기화
		p[1][i]->n = PAWN;
	    p[1][i]->isempty = 0;
		p[1][i]->color = 1;
		p[1][i]->alive = 1;

		//백색 폰 초기화
		p[6][i]->n = PAWN;
		p[6][i]->isempty = 0;
		p[6][i]->color = 0;
		p[6][i]->alive = 1;

		//흑색 첫줄 초기화
		p[0][i]->isempty = 0;
		p[0][i]->color = 1;
		p[0][i]->alive = 1;

		//백색 두번째줄 초기화
		p[7][i]->isempty = 0;
		p[7][i]->color = 0;
		p[7][i]->alive = 0;
	}
	
	//룩 초기화
	p[0][0]->n = ROOK;
	p[0][7]->n = ROOK;
	p[7][0]->n = ROOK;
	p[7][7]->n = ROOK;

	p[0][1]->n = KNIGHT;
	p[0][6]->n = KNIGHT;
	p[7][1]->n = KNIGHT;
	p[7][6]->n = KNIGHT;

	p[0][2]->n = BISHOP;
	p[0][5]->n = BISHOP;
	p[7][2]->n = BISHOP;
	p[7][5]->n = BISHOP;

	p[0][3]->n = QUEEN;
	p[7][3]->n = QUEEN;

	p[0][4]->n = KING;
	p[7][4]->n = KING;
}

void print_map(Piece* (*p)[8]) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			
			if (p[i][j]->isempty) printf(" 빔 ");//빈자리일경우
			
			else {
				if (p[i][j]->color) {//흑색
					switch (p[i][j]->n) {
					case 0:
						printf(" ● ");
						break;
					case 1:
						printf(" ◆ ");
						break;
					case 2:
						printf(" ■ ");
						break;
					case 3:
						printf(" ▲ ");
						break;
					case 4:
						printf(" ▼ ");
						break;
					case 5:
						printf(" ★ ");
						break;
					}
				 }

				else {//백색
					switch (p[i][j]->n) {
					case 0:
						printf(" ○ ");
						break;
					case 1:
						printf(" ◇ ");
						break;
					case 2:
						printf(" □ ");
						break;
					case 3:
						printf(" △ ");
						break;
					case 4:
						printf(" ▽ ");
						break;
					case 5:
						printf(" ☆ ");
						break;

					}
				}
		
			}
		}
		printf("\n");
	}
}

void pawn_move(Piece* (*p)[8], int x, int y) {
	int toX, toY;
	printf("이동할 칸 좌표:");
	scanf("%d %d", &toX, &toY);

	if (abs(x - (toX - 1)) > 1 || abs(y - (toY - 1)) > 1) printf("불가능한 이동입니다.\n");
	else {
		p[x][y]->isempty = 1;
		p[toX - 1][toY - 1]->isempty = 0;
		p[toX - 1][toY - 1]->n = p[x][y]->n;
		p[toX - 1][toY - 1]->color = p[x][y]->color;
		p[toX - 1][toY - 1]->alive = p[x][y]->alive;
	}
	
}

void knight_move(Piece* (*p)[8], int x, int y) {}
void bishop_move(Piece* (*p)[8], int x, int y) {}
void rook_move(Piece* (*p)[8], int x, int y) {}
void queen_move(Piece* (*p)[8], int x, int y) {}
void king_move(Piece* (*p)[8], int x, int y) {}

void move(Piece* (*p)[8]) {
	int	fromX, fromY;
	
	printf("이동할 말 좌표:");
	scanf("%d %d", &fromX, &fromY);
	
	switch (p[fromX-1][fromY-1]->n) {
	case 0:
		pawn_move(p, fromX - 1, fromY - 1);
		break;
	case 1:
		knight_move(p, fromX - 1, fromY - 1);
		break;
	case 2:
		bishop_move(p, fromX - 1, fromY - 1);
		break;
	case 3:
		rook_move(p, fromX - 1, fromY - 1);
		break;
	case 4:
		queen_move(p, fromX - 1, fromY - 1);
		break;
	case 5:
		king_move(p, fromX - 1, fromY - 1);
		break;
	}


}

int main() {

	Piece* map[8][8];
	
	for (int i = 0; i < 8; i++){   //맵 배열에 메모리 할당{
		for (int j = 0; j < 8; j++) {
			map[i][j] = (Piece *)malloc(sizeof(Piece));
			map[i][j]->isempty = 1;
		}
	}

	Initialize_map(map);
	print_map(map);
	move(map);
	printf("\n");
	print_map(map);

	for (int i = 0; i < 8; i++) {   //맵 배열에 메모리 할당{
		for (int j = 0; j < 8; j++) {
			free(map[i][j]);
		}
	}

	return 0;


}