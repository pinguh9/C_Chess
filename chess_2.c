#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
enum name { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };
_Bool turn = 0;//0�̸� ��� 1�̸� ����� ��

typedef struct piece
{
	_Bool isempty;//���� ������ 0 ������ 1.
	enum name n;
	_Bool color;//1�̸� �� 0�̸� ��
	int count;//�̵��� Ƚ��
	_Bool alive;//1�̸� ���� 0�̸� ���
}Piece;

void  Initialize_map(Piece* (*p)[8]) {//�� �ʱ�ȭ

	for (int i = 0; i < 8; i++) {//�� �ʱ�ȭ
		  //��� �� �ʱ�ȭ
		p[1][i]->n = PAWN;
		p[1][i]->isempty = 0;
		p[1][i]->color = 1;
		p[1][i]->count = 0;
		p[1][i]->alive = 1;

		//��� �� �ʱ�ȭ
		p[6][i]->n = PAWN;
		p[6][i]->isempty = 0;
		p[6][i]->color = 0;
		p[6][i]->count = 0;
		p[6][i]->alive = 1;

		//��� ù�� �ʱ�ȭ
		p[0][i]->isempty = 0;
		p[0][i]->color = 1;
		p[0][i]->count = 0;
		p[0][i]->alive = 1;

		//��� �ι�°�� �ʱ�ȭ
		p[7][i]->isempty = 0;
		p[7][i]->color = 0;
		p[7][i]->count = 0;
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

void print_map(Piece* (*p)[8], int x, int y) {
	printf("����a   b   c   d   e   f   g   h  \n");
	for (int i = 0; i < 8; i++) {
		printf(" %d ", i + 1);
		for (int j = 0; j < 8; j++) {
			if (p[i][j]->isempty)
			{
				if (x == -1 && y == -1) // �⹰�� �������� �ʾ��� ��
					printf(" -- "); //���ڸ�
				else
				{
					switch (p[x][y]->n) {
					case 0: // ��
						if (p[x][y]->color == 1) // ���̸�
						{
							if ((i == (x + 1)) && j == y)
								printf(" @@ ");
							else if (i == (x + 2) && j == y)
							{
								if (p[x][y]->count == 0)
									printf(" @@ "); // �� ���� �� ���������� 2ĭ ������ �� ����
								else
									printf(" -- ");
							}
							else
								printf(" -- ");
							break;
						}
						else
						{
							if ((i == (x - 1)) && j == y)
								printf(" @@ ");
							else if (i == (x - 2) && j == y)
							{
								if (p[x][y]->count == 0)
									printf(" @@ "); // �� ���� �� ���������� 2ĭ ������ �� ����
								else
									printf(" -- ");
							}
							else
								printf(" -- ");
							break;
						}

					case 1:         // ����Ʈ
						if (((abs(x - i) == 2) && abs(y - j) == 1) || ((abs(x - i) == 1) && abs(y - j) == 2))
							printf(" @@ ");
						else
							printf(" -- ");
						break;
					case 2: // ���
						if (abs(x - i) == abs(y - j))
							printf(" @@ ");
						else
							printf(" -- ");
						break;
					case 3: // ��
						if ((x == i || y == j))
							printf(" @@ ");
						else
							printf(" -- ");
						break;
					case 4:         // ��
						if ((abs(x - i) == abs(y - j)) || x == i || y == j)
							printf(" @@ ");
						else
							printf(" -- ");
						break;
					case 5:         // ŷ
						if (abs(x - i) <= 1 && abs(y - j) <= 1)
							printf(" @@ ");
						else
							printf(" -- ");
						break;
					}
				}
			}

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

void Pawnlomotion(Piece* (*p)[8], int x, int y)      //�� �±�
{
	enum name nombre;

	printf("�� �±� ����! 1:����Ʈ 2:��� 3:�� 4:��\n");
	while (1)
	{
		scanf("%d", &nombre);

		if (nombre < 1 || nombre > 4)
			printf("�߸��� ���� �Է��߽��ϴ�.\n");
		else
			break;
	}

	p[x][y]->n = nombre;
}

void pawn_move(Piece* (*p)[8], int x, int y) {
	int toX, toY;
	printf("�̵��� ĭ ��ǥ:");
	scanf("%d %d", &toX, &toY);

	if (p[x][y]->color == 0) {         //������ ���� ���϶�
		if ((x - (toX - 1)) <= 0) {      //�ڷ� �̵� �Ұ�
			printf("���� �ڷ� �̵��� �� �����ϴ�.\n");
			return;
		}
	}
	else if (p[x][y]->color == 1) {      //������ ���� ���϶�
		if ((x - (toX - 1)) >= 0) {      //�ڷ� �̵� �Ұ�
			printf("���� �ڷ� �̵��� �� �����ϴ�.\n");
			return;
		}
	}

	if (p[x][y]->color == p[toX - 1][toY - 1]->color) {      //���� �� �Ա� �Ұ�
		printf("���� ���� ��ġ�� �̵��� �� �����ϴ�.\n");
		return;
	}


	if (p[toX - 1][toY - 1]->isempty == 0) {      //������ ���� ���� ���� �� @���� if�� �߸��ż� �� �Ա⿡�� ���� �߻��ϴµ�?
		
		if (p[x][y]->count == 0)      //���� �ѹ��� �� �������� ��
			if (abs(x - (toX - 1)) <= 2 && abs(y - (toY - 1)) == 0) {      //2ĭ���� �̵� ����
				if (turn)turn = 0;
				else turn = 1;
				p[x][y]->isempty = 1;
				p[toX - 1][toY - 1]->isempty = 0;
				p[toX - 1][toY - 1]->n = p[x][y]->n;
				p[toX - 1][toY - 1]->color = p[x][y]->color;
				p[toX - 1][toY - 1]->alive = p[x][y]->alive;
				p[toX - 1][toY - 1]->count = p[x][y]->count + 1;
			}
			else printf("�Ұ����� �̵��Դϴ�.\n");
		else {      //���� 1�� �̻� �������� ��
			if (abs(x - (toX - 1)) <= 1 && abs(y - (toY - 1)) == 0) {      //2ĭ���� �̵� ����
				if (turn)turn = 0;
				else turn = 1;
				p[x][y]->isempty = 1;
				p[toX - 1][toY - 1]->isempty = 0;
				p[toX - 1][toY - 1]->n = p[x][y]->n;
				p[toX - 1][toY - 1]->color = p[x][y]->color;
				p[toX - 1][toY - 1]->alive = p[x][y]->alive;
				p[toX - 1][toY - 1]->count = p[x][y]->count + 1;
			}
			else printf("�Ұ����� �̵��Դϴ�.\n");
		}
	}
	else { // ������ ���� ��밡 ���� ��
		if (abs(x - (toX - 1)) == 1 && abs(y - (toY - 1)) == 1) {      //�밢������ �� ĭ���� �̵� ����
			if (turn)turn = 0;
			else turn = 1;
			p[x][y]->isempty = 1;
			p[toX - 1][toY - 1]->isempty = 0;
			p[toX - 1][toY - 1]->n = p[x][y]->n;
			p[toX - 1][toY - 1]->color = p[x][y]->color;
			p[toX - 1][toY - 1]->alive = p[x][y]->alive;
			p[toX - 1][toY - 1]->count = p[x][y]->count + 1;
		}
		else printf("�Ұ����� �̵��Դϴ�.\n");
	}
	// ���� ������ ���� �±�
	if (toX == 1 || toX == 8)
		if (p[toX - 1][toY - 1]->n == PAWN)
			Pawnlomotion(p, toX - 1, toY - 1);

}

void knight_move(Piece* (*p)[8], int x, int y) {
	int toX, toY;

	while (1)
	{
		printf("�̵��� ĭ ��ǥ:");
		scanf("%d %d", &toX, &toY);

		if ((toX - 1) == x && (toY - 1) == y) printf("���� ��ġ�Դϴ�.\n");      //���� ��ġ �Ұ���
		else if (p[x][y]->color == p[toX - 1][toY - 1]->color) printf("�Ұ����� �̵��Դϴ�.\n");      //���� �� �Ա� �Ұ�
		else if (((abs(x - (toX - 1)) == 1) && (abs(y - (toY - 1)) == 2)) || ((abs(x - (toX - 1)) == 2) && (abs(y - (toY - 1)) == 1))) {
			if (turn)turn = 0;
			else turn = 1;
			p[x][y]->isempty = 1;
			p[toX - 1][toY - 1]->isempty = 0;
			p[toX - 1][toY - 1]->n = p[x][y]->n;
			p[toX - 1][toY - 1]->color = p[x][y]->color;
			p[toX - 1][toY - 1]->alive = p[x][y]->alive;
			p[toX - 1][toY - 1]->count = p[x][y]->count + 1;
			break;
		}
		else
			printf("�Ұ����� �̵��Դϴ�.\n");
	}
}

void bishop_move(Piece* (*p)[8], int x, int y) {
	int toX, toY;

	while (1)
	{
		printf("�̵��� ĭ ��ǥ:");
		scanf("%d %d", &toX, &toY);

		if ((toX - 1) == x && (toY - 1) == y) printf("���� ��ġ�Դϴ�.\n");
		else if (p[x][y]->color == p[toX - 1][toY - 1]->color) printf("�Ұ����� �̵��Դϴ�.\n");
		else if (abs(x - (toX - 1)) != abs(y - (toY - 1))) printf("�Ұ����� �̵��Դϴ�.\n");
		else
			break;
	}

	if (turn)turn = 0;
	else turn = 1;
	p[x][y]->isempty = 1;
	p[toX - 1][toY - 1]->isempty = 0;
	p[toX - 1][toY - 1]->n = p[x][y]->n;
	p[toX - 1][toY - 1]->color = p[x][y]->color;
	p[toX - 1][toY - 1]->alive = p[x][y]->alive;
	p[toX - 1][toY - 1]->count = p[x][y]->count + 1;
}

void rook_move(Piece* (*p)[8], int x, int y) {
	int toX, toY;

	while (1)
	{
		printf("�̵��� ĭ ��ǥ:");
		scanf("%d %d", &toX, &toY);

		if ((toX - 1) == x && (toY - 1) == y) printf("���� ��ġ�Դϴ�.\n");
		else if (p[x][y]->color == p[toX - 1][toY - 1]->color) printf("�Ұ����� �̵��Դϴ�.\n");
		else if ((abs(x - (toX - 1)) > 0 && abs(y - (toY - 1)) > 0)) printf("�Ұ����� �̵��Դϴ�.\n");
		else
			break;
	}

	if (turn)turn = 0;
	else turn = 1;
	p[x][y]->isempty = 1;
	p[toX - 1][toY - 1]->isempty = 0;
	p[toX - 1][toY - 1]->n = p[x][y]->n;
	p[toX - 1][toY - 1]->color = p[x][y]->color;
	p[toX - 1][toY - 1]->alive = p[x][y]->alive;
	p[toX - 1][toY - 1]->count = p[x][y]->count + 1;
}
void queen_move(Piece* (*p)[8], int x, int y) {
	int toX, toY;
	while (1)
	{
		printf("�̵��� ĭ ��ǥ:");
		scanf("%d %d", &toX, &toY);

		if ((toX - 1) == x && (toY - 1) == y) printf("���� ��ġ�Դϴ�.\n");
		else if (p[x][y]->color == p[toX - 1][toY - 1]->color) printf("�Ұ����� �̵��Դϴ�.\n");
		else if ((abs(x - (toX - 1)) == abs(y - (toY - 1))) || (abs(x - (toX - 1)) > 0 && abs(y - (toY - 1)) == 0) || (abs(x - (toX - 1)) == 0 && abs(y - (toY - 1)) > 0)) {
			if (turn)turn = 0;
			else turn = 1;
			p[x][y]->isempty = 1;
			p[toX - 1][toY - 1]->isempty = 0;
			p[toX - 1][toY - 1]->n = p[x][y]->n;
			p[toX - 1][toY - 1]->color = p[x][y]->color;
			p[toX - 1][toY - 1]->alive = p[x][y]->alive;
			p[toX - 1][toY - 1]->count = p[x][y]->count + 1;
			break;
		}
		else
			printf("�Ұ����� �̵��Դϴ�.\n");
	}
}
void king_move(Piece* (*p)[8], int x, int y) {
	int toX, toY;

	while (1)
	{
		printf("�̵��� ĭ ��ǥ:");
		scanf("%d %d", &toX, &toY);

		if ((toX - 1) == x && (toY - 1) == y) printf("���� ��ġ�Դϴ�.\n");
		else if (p[x][y]->color == p[toX - 1][toY - 1]->color) printf("�Ұ����� �̵��Դϴ�.\n");
		else if (abs(x - (toX - 1)) > 1 || abs(y - (toY - 1)) > 1) printf("�Ұ����� �̵��Դϴ�.\n");
		else
			break;
	}

	if (turn)turn = 0;
	else turn = 1;
	p[x][y]->isempty = 1;
	p[toX - 1][toY - 1]->isempty = 0;
	p[toX - 1][toY - 1]->n = p[x][y]->n;
	p[toX - 1][toY - 1]->color = p[x][y]->color;
	p[toX - 1][toY - 1]->alive = p[x][y]->alive;
	p[toX - 1][toY - 1]->count = p[x][y]->count + 1;
}

void move(Piece* (*p)[8]) {
	int fromX, fromY;

	while (1)
	{
		if (turn) printf("����� ��!\n");
		else printf("����� ��!\n");

		printf("�̵��� �⹰ ��ǥ:");
		scanf("%d %d", &fromX, &fromY);
		
		if (fromX < 1 || fromX>8 || fromY < 1 || fromY>8) printf("���� ��� ��ǥ�Դϴ�.\n"); // ���� �����
		else if (p[fromX - 1][fromY - 1]->color != turn) printf("�ڽ��� ���� �ƴմϴ�.\n"); //�ڽ��� ���� �ƴϸ�
		else
		{
			if (p[fromX - 1][fromY - 1]->isempty == 1) printf("�̵��� �� �ִ� �⹰�� �����ϴ�..\n"); // �� ��ǥ�� ���� ������ �ٽ� �Է¹���
			else
				break;
		}
	}

	system("cls");
	print_map(p, fromX - 1, fromY - 1);

	switch (p[fromX - 1][fromY - 1]->n) {
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

	for (int i = 0; i < 8; i++) { //�� �迭�� �޸� �Ҵ�{
		for (int j = 0; j < 8; j++) {
			map[i][j] = (Piece*)malloc(sizeof(Piece));
			map[i][j]->isempty = 1;
		}
	}

	Initialize_map(map);

	while (1)
	{
		print_map(map, -1, -1); // ������ �⹰�� ���� ������ ���� �� ���
		move(map);
		printf("\n");
		system("cls");
	}

	for (int i = 0; i < 8; i++) { //�� �迭 �޸� �Ҵ� ����
		for (int j = 0; j < 8; j++) {
			free(map[i][j]);
		}
	}

	return 0;
}