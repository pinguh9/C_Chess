#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
enum name { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };
_Bool turn = 0;//0이면 백색 1이면 흑색의 턴

typedef struct piece
{
	_Bool isempty;//말이 있으면 0 없으면 1.
	enum name n;
	_Bool color;//1이면 흑 0이면 백
	int count;//이동한 횟수
	_Bool alive;//1이면 생존 0이면 사망
}Piece;

void  Initialize_map(Piece* (*p)[8]) {//맵 초기화

	for (int i = 0; i < 8; i++) {//폰 초기화
		  //흑색 폰 초기화
		p[1][i]->n = PAWN;
		p[1][i]->isempty = 0;
		p[1][i]->color = 1;
		p[1][i]->count = 0;
		p[1][i]->alive = 1;

		//백색 폰 초기화
		p[6][i]->n = PAWN;
		p[6][i]->isempty = 0;
		p[6][i]->color = 0;
		p[6][i]->count = 0;
		p[6][i]->alive = 1;

		//흑색 첫줄 초기화
		p[0][i]->isempty = 0;
		p[0][i]->color = 1;
		p[0][i]->count = 0;
		p[0][i]->alive = 1;

		//백색 두번째줄 초기화
		p[7][i]->isempty = 0;
		p[7][i]->color = 0;
		p[7][i]->count = 0;
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

void print_map(Piece* (*p)[8], int x, int y) {
	printf("　　a   b   c   d   e   f   g   h  \n");
	for (int i = 0; i < 8; i++) {
		printf(" %d ", i + 1);
		for (int j = 0; j < 8; j++) {
			if (p[i][j]->isempty)
			{
				if (x == -1 && y == -1) // 기물을 선택하지 않았을 때
					printf(" -- "); //빈자리
				else
				{
					switch (p[x][y]->n) {
					case 0: // 폰
						if (p[x][y]->color == 1) // 흑이면
						{
							if ((i == (x + 1)) && j == y)
								printf(" @@ ");
							else if (i == (x + 2) && j == y)
							{
								if (p[x][y]->count == 0)
									printf(" @@ "); // 한 번도 안 움직였으면 2칸 움직일 수 있음
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
									printf(" @@ "); // 한 번도 안 움직였으면 2칸 움직일 수 있음
								else
									printf(" -- ");
							}
							else
								printf(" -- ");
							break;
						}

					case 1:         // 나이트
						if (((abs(x - i) == 2) && abs(y - j) == 1) || ((abs(x - i) == 1) && abs(y - j) == 2))
							printf(" @@ ");
						else
							printf(" -- ");
						break;
					case 2: // 비숍
						if (abs(x - i) == abs(y - j))
							printf(" @@ ");
						else
							printf(" -- ");
						break;
					case 3: // 룩
						if ((x == i || y == j))
							printf(" @@ ");
						else
							printf(" -- ");
						break;
					case 4:         // 퀸
						if ((abs(x - i) == abs(y - j)) || x == i || y == j)
							printf(" @@ ");
						else
							printf(" -- ");
						break;
					case 5:         // 킹
						if (abs(x - i) <= 1 && abs(y - j) <= 1)
							printf(" @@ ");
						else
							printf(" -- ");
						break;
					}
				}
			}

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
						printf(" ▲ ");
						break;
					case 3:
						printf(" ■ ");
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
						printf(" △ ");
						break;
					case 3:
						printf(" □ ");
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

void Pawnlomotion(Piece* (*p)[8], int x, int y)      //폰 승급
{
	enum name nombre;

	printf("폰 승급 가능! 1:나이트 2:비숍 3:룩 4:퀸\n");
	while (1)
	{
		scanf("%d", &nombre);

		if (nombre < 1 || nombre > 4)
			printf("잘못된 값을 입력했습니다.\n");
		else
			break;
	}

	p[x][y]->n = nombre;
}

void pawn_move(Piece* (*p)[8], int x, int y) {
	int toX, toY;
	printf("이동할 칸 좌표:");
	scanf("%d %d", &toX, &toY);

	if (p[x][y]->color == 0) {         //선택한 폰이 백일때
		if ((x - (toX - 1)) <= 0) {      //뒤로 이동 불가
			printf("폰은 뒤로 이동할 수 없습니다.\n");
			return;
		}
	}
	else if (p[x][y]->color == 1) {      //선택한 폰이 흑일때
		if ((x - (toX - 1)) >= 0) {      //뒤로 이동 불가
			printf("폰은 뒤로 이동할 수 없습니다.\n");
			return;
		}
	}

	if (p[x][y]->color == p[toX - 1][toY - 1]->color) {      //같은 편 먹기 불가
		printf("같은 색의 위치로 이동할 수 없습니다.\n");
		return;
	}


	if (p[toX - 1][toY - 1]->isempty == 0) {      //가려는 곳에 말이 있을 때 @여기 if문 잘못돼서 폰 먹기에서 버그 발생하는듯?
		
		if (p[x][y]->count == 0)      //폰이 한번도 안 움직였을 때
			if (abs(x - (toX - 1)) <= 2 && abs(y - (toY - 1)) == 0) {      //2칸까지 이동 가능
				if (turn)turn = 0;
				else turn = 1;
				p[x][y]->isempty = 1;
				p[toX - 1][toY - 1]->isempty = 0;
				p[toX - 1][toY - 1]->n = p[x][y]->n;
				p[toX - 1][toY - 1]->color = p[x][y]->color;
				p[toX - 1][toY - 1]->alive = p[x][y]->alive;
				p[toX - 1][toY - 1]->count = p[x][y]->count + 1;
			}
			else printf("불가능한 이동입니다.\n");
		else {      //폰이 1번 이상 움직였을 때
			if (abs(x - (toX - 1)) <= 1 && abs(y - (toY - 1)) == 0) {      //2칸까지 이동 가능
				if (turn)turn = 0;
				else turn = 1;
				p[x][y]->isempty = 1;
				p[toX - 1][toY - 1]->isempty = 0;
				p[toX - 1][toY - 1]->n = p[x][y]->n;
				p[toX - 1][toY - 1]->color = p[x][y]->color;
				p[toX - 1][toY - 1]->alive = p[x][y]->alive;
				p[toX - 1][toY - 1]->count = p[x][y]->count + 1;
			}
			else printf("불가능한 이동입니다.\n");
		}
	}
	else { // 가려는 곳에 상대가 있을 때
		if (abs(x - (toX - 1)) == 1 && abs(y - (toY - 1)) == 1) {      //대각선으로 한 칸씩만 이동 가능
			if (turn)turn = 0;
			else turn = 1;
			p[x][y]->isempty = 1;
			p[toX - 1][toY - 1]->isempty = 0;
			p[toX - 1][toY - 1]->n = p[x][y]->n;
			p[toX - 1][toY - 1]->color = p[x][y]->color;
			p[toX - 1][toY - 1]->alive = p[x][y]->alive;
			p[toX - 1][toY - 1]->count = p[x][y]->count + 1;
		}
		else printf("불가능한 이동입니다.\n");
	}
	// 폰이 끝까지 가면 승급
	if (toX == 1 || toX == 8)
		if (p[toX - 1][toY - 1]->n == PAWN)
			Pawnlomotion(p, toX - 1, toY - 1);

}

void knight_move(Piece* (*p)[8], int x, int y) {
	int toX, toY;

	while (1)
	{
		printf("이동할 칸 좌표:");
		scanf("%d %d", &toX, &toY);

		if ((toX - 1) == x && (toY - 1) == y) printf("현재 위치입니다.\n");      //현재 위치 불가능
		else if (p[x][y]->color == p[toX - 1][toY - 1]->color) printf("불가능한 이동입니다.\n");      //같은 편 먹기 불가
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
			printf("불가능한 이동입니다.\n");
	}
}

void bishop_move(Piece* (*p)[8], int x, int y) {
	int toX, toY;

	while (1)
	{
		printf("이동할 칸 좌표:");
		scanf("%d %d", &toX, &toY);

		if ((toX - 1) == x && (toY - 1) == y) printf("현재 위치입니다.\n");
		else if (p[x][y]->color == p[toX - 1][toY - 1]->color) printf("불가능한 이동입니다.\n");
		else if (abs(x - (toX - 1)) != abs(y - (toY - 1))) printf("불가능한 이동입니다.\n");
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
		printf("이동할 칸 좌표:");
		scanf("%d %d", &toX, &toY);

		if ((toX - 1) == x && (toY - 1) == y) printf("현재 위치입니다.\n");
		else if (p[x][y]->color == p[toX - 1][toY - 1]->color) printf("불가능한 이동입니다.\n");
		else if ((abs(x - (toX - 1)) > 0 && abs(y - (toY - 1)) > 0)) printf("불가능한 이동입니다.\n");
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
		printf("이동할 칸 좌표:");
		scanf("%d %d", &toX, &toY);

		if ((toX - 1) == x && (toY - 1) == y) printf("현재 위치입니다.\n");
		else if (p[x][y]->color == p[toX - 1][toY - 1]->color) printf("불가능한 이동입니다.\n");
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
			printf("불가능한 이동입니다.\n");
	}
}
void king_move(Piece* (*p)[8], int x, int y) {
	int toX, toY;

	while (1)
	{
		printf("이동할 칸 좌표:");
		scanf("%d %d", &toX, &toY);

		if ((toX - 1) == x && (toY - 1) == y) printf("현재 위치입니다.\n");
		else if (p[x][y]->color == p[toX - 1][toY - 1]->color) printf("불가능한 이동입니다.\n");
		else if (abs(x - (toX - 1)) > 1 || abs(y - (toY - 1)) > 1) printf("불가능한 이동입니다.\n");
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
		if (turn) printf("흑색의 턴!\n");
		else printf("백색의 턴!\n");

		printf("이동할 기물 좌표:");
		scanf("%d %d", &fromX, &fromY);
		
		if (fromX < 1 || fromX>8 || fromY < 1 || fromY>8) printf("맵을 벗어난 좌표입니다.\n"); // 맵을 벗어나면
		else if (p[fromX - 1][fromY - 1]->color != turn) printf("자신의 턴이 아닙니다.\n"); //자신의 턴이 아니면
		else
		{
			if (p[fromX - 1][fromY - 1]->isempty == 1) printf("이동할 수 있는 기물이 없습니다..\n"); // 그 좌표에 말이 없으면 다시 입력받음
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

	for (int i = 0; i < 8; i++) { //맵 배열에 메모리 할당{
		for (int j = 0; j < 8; j++) {
			map[i][j] = (Piece*)malloc(sizeof(Piece));
			map[i][j]->isempty = 1;
		}
	}

	Initialize_map(map);

	while (1)
	{
		print_map(map, -1, -1); // 움직일 기물을 선택 안했을 때의 맵 출력
		move(map);
		printf("\n");
		system("cls");
	}

	for (int i = 0; i < 8; i++) { //맵 배열 메모리 할당 해제
		for (int j = 0; j < 8; j++) {
			free(map[i][j]);
		}
	}

	return 0;
}