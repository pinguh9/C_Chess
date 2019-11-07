#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
enum name { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };

typedef struct piece
{
	_Bool isempty;//���� ������ 0 ������ 1.
	enum name n;
	_Bool color;//1�̸� �� 0�̸� ��
	_Bool alive;//1�̸� ���� 0�̸� ���
}Piece;

void  Initialize_map(Piece* (*p)[8]) {//�� �ʱ�ȭ
	
	for (int i = 0; i < 8; i++) {//�� �ʱ�ȭ
		//��� �� �ʱ�ȭ
		p[1][i]->n = PAWN;
	    p[1][i]->isempty = 0;
		p[1][i]->color = 1;
		p[1][i]->alive = 1;

		//��� �� �ʱ�ȭ
		p[6][i]->n = PAWN;
		p[6][i]->isempty = 0;
		p[6][i]->color = 0;
		p[6][i]->alive = 1;

		//��� ù�� �ʱ�ȭ
		p[0][i]->isempty = 0;
		p[0][i]->color = 1;
		p[0][i]->alive = 1;

		//��� �ι�°�� �ʱ�ȭ
		p[7][i]->isempty = 0;
		p[7][i]->color = 0;
		p[7][i]->alive = 0;
	}
	
	//�� �ʱ�ȭ
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
			
			if (p[i][j]->isempty) printf(" �� ");//���ڸ��ϰ��
			
			else {
				if (p[i][j]->color) {//���
					switch (p[i][j]->n) {
					case 0:
						printf(" �� ");
						break;
					case 1:
						printf(" �� ");
						break;
					case 2:
						printf(" �� ");
						break;
					case 3:
						printf(" �� ");
						break;
					case 4:
						printf(" �� ");
						break;
					case 5:
						printf(" �� ");
						break;
					}
				 }

				else {//���
					switch (p[i][j]->n) {
					case 0:
						printf(" �� ");
						break;
					case 1:
						printf(" �� ");
						break;
					case 2:
						printf(" �� ");
						break;
					case 3:
						printf(" �� ");
						break;
					case 4:
						printf(" �� ");
						break;
					case 5:
						printf(" �� ");
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
	printf("�̵��� ĭ ��ǥ:");
	scanf("%d %d", &toX, &toY);

	if (abs(x - (toX - 1)) > 1 || abs(y - (toY - 1)) > 1) printf("�Ұ����� �̵��Դϴ�.\n");
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
	
	printf("�̵��� �� ��ǥ:");
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
	
	for (int i = 0; i < 8; i++){   //�� �迭�� �޸� �Ҵ�{
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

	for (int i = 0; i < 8; i++) {   //�� �迭�� �޸� �Ҵ�{
		for (int j = 0; j < 8; j++) {
			free(map[i][j]);
		}
	}

	return 0;


}