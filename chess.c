#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#define _CRT_SECURE_NO_WARNINGS
enum name { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, NONE };
int turn = 0;
int isEnpassantTurn[2][8]; // �� �ε����� ���Ļ��� �� �� �ִ� ��, �� �ε����� ���Ļ��� ������ �̵��ϴ� ��
typedef struct piece
{
        _Bool isempty;//���� ������ 0, ������ 1.
        enum name n;
        int color;//���̸� 0, ���̸� 1, ������ 2
        int count;//�̵��� Ƚ��
        _Bool alive;//����̸� 0, �����̸� 1
        _Bool isMove;//�� �� ������ 1, ������ 0
}Piece;
Piece enemy;
int enemy_x;
int enemy_y;
int check(Piece* (*p)[8]);

void initialize_Move(Piece* (*p)[8], int x, int y) // ��ֹ��� Ȯ���ϰ� �� �� ������ isMove�� 1��, �� �� ������ 0���� �ٲ۴�.
{
        int i, j, blockDR_X = 7, blockDR_Y = 7, blockUL_X = 0, blockUL_Y = 0, blockDL_X = 7, blockDL_Y = 7, blockUR_X = 0, blockUR_Y = 7, blockD = 7, blockU = 0, blockR = 7, blockL = 0;

        if (x == -1 && y == -1)
                return;

        else
        {
                switch (p[x][y]->n) // �ڡ١ڡ� x-1, y-1�� �����ؾ� �Ҽ���
                {
                case 0: // PAWN
                        for(i=0; i<8; i++)
                                for(j=0; j<8; j++) {
                                        if (p[x][y]->color == 1) // ���̸�
                                        {
                                                if ((i == (x + 1)) && j == y && p[i][j]->color != 1)
                                                        p[i][j]->isMove = 1;
                                                else if (i == (x + 2) && j == y && p[x][y]->count == 0 && p[i][j]->color != 1)
                                                        p[i][j]->isMove = 1;

                                                else if (isEnpassantTurn[1][j] == turn-1 && turn>1 && i == x+1 && p[i][j]->color != 1) // ���Ļ� ������ ���̸�
                                                        p[i][j]->isMove = 1;
                                                else
                                                        p[i][j]->isMove = 0;
                                                break;
                                        }
                                        else
                                        {
                                                if ((i == (x - 1)) && j == y && p[i][j]->color != 0)
                                                        p[i][j]->isMove = 1;
                                                else if (i == (x - 2) && j == y && p[x][y]->count == 0 && p[i][j]->color != 0)
                                                        p[i][j]->isMove = 1;
                                                else if (isEnpassantTurn[0][j] == turn-1 && turn>1 && i == x-1 && p[i][j]->color != 0) // ���Ļ� ������ ���̸�
                                                        p[i][j]->isMove = 1;
                                                else
                                                        p[i][j]->isMove = 0;
                                                break;
                                        }
                                }
                case 1: // KNIGHT
                        for(i=0; i<8; i++)
                                for(j=0; j<8; j++)
                                        if(((abs(x - i) == 2) && abs(y - j) == 1) || ((abs(x - i) == 1) && abs(y - j) == 2) && (p[i][j]->color != p[x][y]->color))
                                                p[i][j]->isMove = 1;
                                        else
                                                p[i][j]->isMove = 0;
                        break;
                case 2: // BISHOP
                        for (i = x + 1, j = y + 1; i <= 7 && j <= 7; i++, j++) //�Ʒ� ������ ��ֹ�
                                if (p[i][j]->isempty == 0) {
                                        blockDR_X = i;
                                        blockDR_Y = j;
                                        break;
                                }
                        for (i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--) //�� ���� ��ֹ�
                                if (p[i][j]->isempty == 0) {
                                        blockUL_X = i;
                                        blockUL_Y = j;
                                        break;
                                }
                        for (i = x + 1, j = y - 1; i <= 7 && j >= 0; i++, j--) //�Ʒ� ���� ��ֹ�
                                if (p[i][j]->isempty == 0) {
                                        blockDL_X = i;
                                        blockDL_Y = j;
                                        break;
                                }
                        for (i = x - 1, j = y + 1; i >= 0 && j <= 7; i--, j++) //�� ������ ��ֹ�
                                if (p[i][j]->isempty == 0) {
                                        blockUR_X = i;
                                        blockUR_Y = j;
                                        break;
                                }

                        for (i = 0; i < 8; i++)
                        {
                                for (j = 0; j < 8; j++)
                                {
                                        if (i < blockUL_X && j < blockUL_Y) // �� ���� ��ֹ�
                                                p[i][j]->isMove = 0;
                                        else if (i<blockUR_X && j>blockUR_Y) // �� ������ ��ֹ�
                                                p[i][j]->isMove = 0;
                                        else if (i > blockDL_X&& j < blockDL_Y) // �Ʒ� ���� ��ֹ�
                                                p[i][j]->isMove = 0;
                                        else if (i > blockDR_X&& j > blockDR_Y) // �Ʒ� ������ ��ֹ�
                                                p[i][j]->isMove = 0;
                                        else
                                                p[i][j]->isMove = 1;
                                }
                        }

                        break;
                case 3: // ROOK
                        for (i = x + 1; i <= 7; i++) // �Ʒ��� ��ֹ�
                                if (p[i][y]->isempty == 0) {
                                        blockD = i;
                                        break;
                                }
                        for (i = x - 1; i >= 0; i--) // ���� ��ֹ�
                                if (p[i][y]->isempty == 0) {
                                        blockU = i;
                                        break;
                                }
                        for (i = y + 1; i <= 7; i++) // ������ ��ֹ�
                                if (p[x][i]->isempty == 0) {
                                        blockR = i;
                                        break;
                                }
                        for (i = y - 1; i >= 0; i--) // ���� ��ֹ�
                                if (p[x][i]->isempty == 0) {
                                        blockL = i;
                                        break;
                                }

                        for (i = 0; i < 8; i++)
                        {
                                for (j = 0; j < 8; j++)
                                {
                                        if (j == y && ((i < blockU) || (i > blockD))) // ���� �Ʒ� ��ֹ��� ���� ��
                                                p[i][j]->isMove = 0;
                                        else if (i == x && ((j < blockL) || (j > blockR))) // ���ʰ� ������ ��ֹ��� ���� ��
                                                p[i][j]->isMove = 0;
                                        else
                                                p[i][j]->isMove = 1;
                                }
                        }

                        break;
                case 4: // QUEEN
                        for (i = x + 1, j = y + 1; i <= 7 && j <= 7; i++, j++) //�Ʒ� ������ ��ֹ�
                                if (p[i][j]->isempty == 0) {
                                        blockDR_X = i;
                                        blockDR_Y = j;
                                        break;
                                }
                        for (i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--) //�� ���� ��ֹ�
                                if (p[i][j]->isempty == 0) {
                                        blockUL_X = i;
                                        blockUL_Y = j;
                                        break;
                                }
                        for (i = x + 1, j = y - 1; i <= 7 && j >= 0; i++, j--) //�Ʒ� ���� ��ֹ�
                                if (p[i][j]->isempty == 0) {
                                        blockDL_X = i;
                                        blockDL_Y = j;
                                        break;
                                }
                        for (i = x - 1, j = y + 1; i >= 0 && j <= 7; i--, j++) //�� ������ ��ֹ�
                                if (p[i][j]->isempty == 0) {
                                        blockUR_X = i;
                                        blockUR_Y = j;
                                        break;
                                }

                        for (i = x + 1; i <= 7; i++) // �Ʒ��� ��ֹ�
                                if (p[i][y]->isempty == 0) {
                                        blockD = i;
                                        break;
                                }
                        for (i = x - 1; i >= 0; i--) // ���� ��ֹ�
                                if (p[i][y]->isempty == 0) {
                                        blockU = i;
                                        break;
                                }
                        for (i = y + 1; i <= 7; i++) // ������ ��ֹ�
                                if (p[x][i]->isempty == 0) {
                                        blockR = i;
                                        break;
                                }
                        for (i = y - 1; i >= 0; i--) // ���� ��ֹ�
                                if (p[x][i]->isempty == 0) {
                                        blockL = i;
                                        break;
                                }

                        for (i = 0; i < 8; i++)
                        {
                                for (j = 0; j < 8; j++)
                                {
                                        if (j == y && ((i < blockU) || (i > blockD))) // ���� �Ʒ� ��ֹ��� ���� ��
                                                p[i][j]->isMove = 0;
                                        else if (i == x && ((j < blockL) || (j > blockR))) // ���ʰ� ������ ��ֹ��� ���� ��
                                                p[i][j]->isMove = 0;
                                        else if (i < blockUL_X && j < blockUL_Y) // �� ���� ��ֹ�
                                                p[i][j]->isMove = 0;
                                        else if (i<blockUR_X && j>blockUR_Y) // �� ������ ��ֹ�
                                                p[i][j]->isMove = 0;
                                        else if (i > blockDL_X&& j < blockDL_Y) // �Ʒ� ���� ��ֹ�
                                                p[i][j]->isMove = 0;
                                        else if (i > blockDR_X && j > blockDR_Y) // �Ʒ� ������ ��ֹ�
                                                p[i][j]->isMove = 0;
                                        else
                                                p[i][j]->isMove = 1;
                                }
                        }
                        break;
                case 5: // KING
                        break;
                case 6: // empty
                        break;
                }
        }
}

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
                p[7][i]->alive = 1;
        }
        //�� ���� �ʱ�ȭ
        for (int i = 2; i < 6; i++)
                for (int j = 0; j < 8; j++) {
                        p[i][j]->isempty = 1;
                        p[i][j]->color = 3;
                        p[i][j]->count = 0;
                        p[i][j]->alive = 0;
                        p[i][j]->n = NONE;
                }

        //�� �ʱ�ȭ
        p[0][0]->n = ROOK;
        p[0][7]->n = ROOK;
        p[7][0]->n = ROOK;
        p[7][7]->n = ROOK;
        //����Ʈ �ʱ�ȭ
        p[0][1]->n = KNIGHT;
        p[0][6]->n = KNIGHT;
        p[7][1]->n = KNIGHT;
        p[7][6]->n = KNIGHT;
        //��� �ʱ�ȭ
        p[0][2]->n = BISHOP;
        p[0][5]->n = BISHOP;
        p[7][2]->n = BISHOP;
        p[7][5]->n = BISHOP;
        //�� �ʱ�ȭ
        p[0][3]->n = QUEEN;
        p[7][3]->n = QUEEN;
        //ŷ �ʱ�ȭ
        p[0][4]->n = KING;
        p[7][4]->n = KING;
}

void print_map(Piece* (*p)[8], int x, int y) {

        initialize_Move(p, x, y);
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
                                                        else if (isEnpassantTurn[1][j] == turn-1 && x == 4 && turn>1 && i == x+1)  // ���Ļ� ������ ���̸�
                                                        {
                                                                printf(" @@ ");
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
                                                        else if (isEnpassantTurn[0][j] == turn-1 && x == 3 && turn>1 && i == x-1) // ���Ļ� ������ ���̸�
                                                        {
                                                                printf(" @@ ");
                                                        }
                                                        else
                                                                printf(" -- ");
                                                        break;
                                                }

                                        case 1: // ����Ʈ
                                                if (((abs(x - i) == 2) && abs(y - j) == 1) || ((abs(x - i) == 1) && abs(y - j) == 2))
                                                        printf(" @@ ");
                                                else
                                                        printf(" -- ");
                                                break;
                                        case 2: // ���
                                                if ((abs(x - i) == abs(y - j)) && p[i][j]->isMove == 1)
                                                        printf(" @@ ");
                                                else
                                                        printf(" -- ");
                                                break;
                                        case 3: // ��
                                                if ((x == i || y == j) && p[i][j]->isMove == 1)
                                                        printf(" @@ ");
                                                else
                                                        printf(" -- ");
                                                break;
                                        case 4: // ��
                                                if (((abs(x - i) == abs(y - j)) || x == i || y == j) && p[i][j]->isMove == 1)
                                                        printf(" @@ ");
                                                else
                                                        printf(" -- ");
                                                break;
                                        case 5: // ŷ
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

//�� �±� �Լ�
void Pawnlomotion(Piece* (*p)[8], int x, int y)
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

//�̵��� �� ���� ���� �Լ�
void statuemove(Piece* (*p)[8], int x, int y, int toX, int toY) {
        p[toX - 1][toY - 1]->isempty = 0;
        p[toX - 1][toY - 1]->n = p[x][y]->n;
        p[toX - 1][toY - 1]->color = p[x][y]->color;
        p[toX - 1][toY - 1]->alive = p[x][y]->alive;
        p[toX - 1][toY - 1]->count = p[x][y]->count + 1;
        p[x][y]->isempty = 1;
        p[x][y]->n = NONE;
        p[x][y]->color = 2;
        p[x][y]->alive = 0;
        p[x][y]->count = 0;
        turn++;
}


//�� �̵� �Լ�
void pawn_move(Piece* (*p)[8], int x, int y) {
        Piece temp;
        int toX, toY;
        char tmp;

        printf("�̵��� ĭ ��ǥ:");
        scanf(" %c %d", &tmp, &toX);

        toY = (int)(tmp - 'a' + 1);

        if (p[x][y]->color == p[toX - 1][toY - 1]->color) { //���� �� �Ա� �Ұ�
                printf("�Ұ����� �̵��Դϴ�.\n");
                return;
        }

        temp = *p[toX - 1][toY - 1]; //�̵��� ŷ�� üũ �� ��� �̵� �Ұ�
        statuemove(p, x, y, toX, toY);
        p[toX - 1][toY - 1]->count--;
        turn--;
        if (check(p) == 0) {
                statuemove(p, toX - 1, toY - 1, x + 1, y + 1);
                p[x][y]->count--;
                turn--;
                *p[toX - 1][toY - 1] = temp;
        }
        else {
                statuemove(p, toX - 1, toY - 1, x + 1, y + 1);
                p[x][y]->count--;
                turn--;
                *p[toX - 1][toY - 1] = temp;
                printf("�Ұ����� �̵��Դϴ�.\n");
                return;
        }


        if (p[x][y]->color == 0) { //������ ���� ���϶�
                if (p[toX - 1][toY - 1]->isempty == 1) { //������ ���� ���� ���� ��
                        //���Ļ�
                        if (isEnpassantTurn[0][toY - 1] == turn-1) // �ٷ� ���� ������ ������ ���� ���� 2ĭ �������� ��
                        {
                                if (x == 3 && p[toX][toY-1]->n == 0) // ���� ���� ��
                                {
                                        {
                                                p[toX][toY-1]->isempty = 1;
                                                p[toX][toY-1]->n = NONE;
                                                p[toX][toY-1]->color = 2;
                                                p[toX][toY-1]->alive = 0;
                                                p[toX][toY-1]->count = 0;
                                                statuemove(p, x, y, toX, toY);
                                                return;
                                        }

                                }
                        }

                        if (p[x][y]->count == 0)         //���� �ѹ��� �� �������� ��
                                if ((x - (toX - 1) == 2 && (y - (toY - 1)) == 0) || (x - (toX - 1) == 1 && (y - (toY - 1)) == 0)) {         //���η� 2ĭ���� �̵� ����
                                        if((x - (toX - 1) == 2 && (y - (toY - 1)) == 0))         // ���� 2ĭ ���������� �ٷ� ���� �Ͽ� ���Ļ��� ����
                                                isEnpassantTurn[1][y] = turn;         // ���� y��ǥ�� ���Ļ��� ����

                                        statuemove(p, x, y, toX, toY);
                                }
                                else printf("�Ұ����� �̵��Դϴ�.\n");
                        else {         //���� 1�� �̻� �������� ��
                                if ((x - (toX - 1) == 1 && (y - (toY - 1)) == 0)) {         //1ĭ���� �̵� ����
                                        statuemove(p, x, y, toX, toY);
                                }
                                else printf("�Ұ����� �̵��Դϴ�.\n");
                        }
                }
                else { //������ ���� ��밡 ���� ��
                        if ((x - (toX - 1)) == 1 && abs(y - (toY - 1)) == 1) { //�밢������ �� ĭ���� �̵� ����
                                statuemove(p, x, y, toX, toY);
                        }
                        else printf("�Ұ����� �̵��Դϴ�.\n");
                }
        }
        else { //������ ���� ���϶�
                if (p[toX - 1][toY - 1]->isempty == 1) { //������ ���� ���� ���� ��
                        //���Ļ�
                        if (isEnpassantTurn[1][toY - 1] == turn-1) // �ٷ� ���� ������ ������ ���� ���� 2ĭ �������� ��
                        {
                                if (x==4 && p[toX-2][toY-1]->n == 0) // ���� ���� ��
                                {
                                        {
                                                p[toX-2][toY-1]->isempty = 1;
                                                p[toX-2][toY-1]->n = NONE;
                                                p[toX-2][toY-1]->color = 2;
                                                p[toX-2][toY-1]->alive = 0;
                                                p[toX-2][toY-1]->count = 0;
                                                statuemove(p, x, y, toX, toY);
                                                return;
                                        }
                                }
                        }
                        if (p[x][y]->count == 0) //���� �ѹ��� �� �������� ��
                                if ((x - (toX - 1) == -2 && (y - (toY - 1)) == 0) || (x - (toX - 1) == -1 && (y - (toY - 1)) == 0)) { //���η� 2ĭ���� �̵� ����
                                        if((x - (toX - 1) == -2 && (y - (toY - 1)) == 0)) // ���� 2ĭ ���������� �ٷ� ���� �Ͽ� ���Ļ��� ����
                                                isEnpassantTurn[0][y] = turn; // ���� y��ǥ�� ���Ļ��� ����

                                        statuemove(p, x, y, toX, toY);
                                }
                                else printf("�Ұ����� �̵��Դϴ�.\n");
                        else { //���� 1�� �̻� �������� ��
                                if ((x - (toX - 1) == -1 && (y - (toY - 1)) == 0)) { //1ĭ���� �̵� ����
                                        statuemove(p, x, y, toX, toY);
                                }
                                else printf("�Ұ����� �̵��Դϴ�.\n");
                        }
                }
                else { // ������ ���� ��밡 ���� ��
                        if ((x - (toX - 1)) == -1 && abs(y - (toY - 1)) == 1) { //�밢������ �� ĭ���� �̵� ����
                                statuemove(p, x, y, toX, toY);
                        }
                        else printf("�Ұ����� �̵��Դϴ�.\n");
                }
        }

        // ���� ������ ���� �±�
        if (toX == 1 || toX == 8)
                if (p[toX - 1][toY - 1]->n == PAWN)
                        Pawnlomotion(p, toX - 1, toY - 1);
}


void knight_move(Piece* (*p)[8], int x, int y) {
        int toX, toY;
        char tmp;
        Piece temp;
        printf("�̵��� ĭ ��ǥ:");
        scanf(" %c %d", &tmp, &toX);

        toY = (int)(tmp - 'a' + 1);

        temp = *p[toX - 1][toY - 1]; //�̵��� ŷ�� üũ �� ��� �̵� �Ұ�
        statuemove(p, x, y, toX, toY);
        p[toX - 1][toY - 1]->count--;
        turn--;
        if (check(p) == 0) {
                statuemove(p, toX - 1, toY - 1, x + 1, y + 1);
                p[x][y]->count--;
                turn--;
                *p[toX - 1][toY - 1] = temp;
        }
        else {
                statuemove(p, toX - 1, toY - 1, x + 1, y + 1);
                p[x][y]->count--;
                turn--;
                *p[toX - 1][toY - 1] = temp;
                printf("�Ұ����� �̵��Դϴ�.\n");
                return;
        }

        if ((toX - 1) == x && (toY - 1) == y) printf("���� ��ġ�Դϴ�.\n"); //���� ��ġ �Ұ���
        else if (p[x][y]->color == p[toX - 1][toY - 1]->color) printf("�Ұ����� �̵��Դϴ�.\n"); //���� �� �Ա� �Ұ�
        else if (((abs(x - (toX - 1)) == 1) && (abs(y - (toY - 1)) == 2)) || ((abs(x - (toX - 1)) == 2) && (abs(y - (toY - 1)) == 1))) {
                statuemove(p, x, y, toX, toY);
        }
        else
                printf("�Ұ����� �̵��Դϴ�.\n");
}



void bishop_move(Piece* (*p)[8], int x, int y) {
        int toX, toY, blockDR_X = 7, blockDR_Y = 7, blockUL_X = 0, blockUL_Y = 0, blockDL_X = 7, blockDL_Y = 7, blockUR_X = 0, blockUR_Y = 7;
        char tmp;
        Piece temp;
        printf("�̵��� ĭ ��ǥ:");
        scanf(" %c %d", &tmp, &toX);

        toY = (int)(tmp - 'a' + 1);

        //��� ��ֹ� ã��
        for (int i = x + 1, j = y + 1; i <= 7 && j <= 7; i++, j++) //�Ʒ� ������ ��ֹ�
                if (p[i][j]->isempty == 0) {
                        blockDR_X = i;
                        blockDR_Y = j;
                        break;
                }
        for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--) //�� ���� ��ֹ�
                if (p[i][j]->isempty == 0) {
                        blockUL_X = i;
                        blockUL_Y = j;
                        break;
                }
        for (int i = x + 1, j = y - 1; i <= 7 && j >= 0; i++, j--) //�Ʒ� ���� ��ֹ�
                if (p[i][j]->isempty == 0) {
                        blockDL_X = i;
                        blockDL_Y = j;//���� �Ʒ��� ��ֹ�
                        break;
                }
        for (int i = x - 1, j = y + 1; i >= 0 && j <= 7; i--, j++) //�� ������ ��ֹ�
                if (p[i][j]->isempty == 0) {
                        blockUR_X = i;
                        blockUR_Y = j;
                        break;
                }

        temp = *p[toX - 1][toY - 1]; //�̵��� ŷ�� üũ �� ��� �̵� �Ұ�
        statuemove(p, x, y, toX, toY);
        p[toX - 1][toY - 1]->count--;
        turn--;
        if (check(p) == 0) {
                statuemove(p, toX - 1, toY - 1, x + 1, y + 1);
                p[x][y]->count--;
                turn--;
                *p[toX - 1][toY - 1] = temp;
        }
        else {
                statuemove(p, toX - 1, toY - 1, x + 1, y + 1);
                p[x][y]->count--;
                turn--;
                *p[toX - 1][toY - 1] = temp;
                printf("�Ұ����� �̵��Դϴ�.\n");
                return;
        }

        if ((toX - 1) == x && (toY - 1) == y) printf("���� ��ġ�Դϴ�.\n");
        else if (p[x][y]->color == p[toX - 1][toY - 1]->color) printf("�Ұ����� �̵��Դϴ�.\n");
        else if (abs(x - (toX - 1)) != abs(y - (toY - 1))) printf("�Ұ����� �̵��Դϴ�.\n");
        else if (p[toX - 1][toY - 1]->isMove == 0) printf("�Ұ����� �̵��Դϴ�.\n");
        else
                statuemove(p, x, y, toX, toY);
}


void rook_move(Piece* (*p)[8], int x, int y) {
        int toX, toY, blockD = 7, blockU = 0, blockR = 7, blockL = 0;
        char tmp;
        Piece temp;

        printf("�̵��� ĭ ��ǥ:");
        scanf(" %c %d", &tmp, &toX);

        toY = (int)(tmp - 'a' + 1);

        for (int i = x + 1; i <= 7; i++) // �Ʒ��� ��ֹ�
                if (p[i][y]->isempty == 0) {
                        blockD = i;
                        break;
                }
        for (int i = x - 1; i >= 0; i--) // ���� ��ֹ�
                if (p[i][y]->isempty == 0) {
                        blockU = i;
                        break;
                }
        for (int i = y + 1; i <= 7; i++) // ������ ��ֹ�
                if (p[x][i]->isempty == 0) {
                        blockR = i;
                        break;
                }
        for (int i = y - 1; i >= 0; i--) // ���� ��ֹ�
                if (p[x][i]->isempty == 0) {
                        blockL = i;
                        break;
                }

        temp = *p[toX - 1][toY - 1]; //�̵��� ŷ�� üũ �� ��� �̵� �Ұ�
        statuemove(p, x, y, toX, toY);
        p[toX - 1][toY - 1]->count--;
        turn--;
        if (check(p) == 0) {
                statuemove(p, toX - 1, toY - 1, x + 1, y + 1);
                p[x][y]->count--;
                turn--;
                *p[toX - 1][toY - 1] = temp;
        }
        else {
                statuemove(p, toX - 1, toY - 1, x + 1, y + 1);
                p[x][y]->count--;
                turn--;
                *p[toX - 1][toY - 1] = temp;
                printf("�Ұ����� �̵��Դϴ�.\n");
                return;
        }

        if ((toX - 1) == x && (toY - 1) == y) printf("���� ��ġ�Դϴ�.\n");
        else if (p[x][y]->color == p[toX - 1][toY - 1]->color) printf("�Ұ����� �̵��Դϴ�.\n");
        else if ((abs(x - (toX - 1)) > 0 && abs(y - (toY - 1)) > 0)) printf("�Ұ����� �̵��Դϴ�.\n");
        else if (p[toX - 1][toY - 1]->isMove == 0) printf("�Ұ����� �̵��Դϴ�.\n");
        else
                statuemove(p, x, y, toX, toY);
}


void queen_move(Piece* (*p)[8], int x, int y) {
        int toX, toY, blockDR_X = 7, blockDR_Y = 7, blockUL_X = 0, blockUL_Y = 0, blockDL_X = 7, blockDL_Y = 7, blockUR_X = 0, blockUR_Y = 7, blockD = 7, blockU = 0, blockR = 7, blockL = 0;
        char tmp;
        Piece temp;

        printf("�̵��� ĭ ��ǥ:");
        scanf(" %c %d", &tmp, &toX);

        toY = (int)(tmp - 'a' + 1);

        //�� ��ֹ� ã��(������ ���� ��� ����)
        for (int i = x + 1, j = y + 1; i <= 7 && j <= 7; i++, j++) //�Ʒ� ������ ��ֹ�
                if (p[i][j]->isempty == 0) {
                        blockDR_X = i;
                        blockDR_Y = j;
                        break;
                }
        for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--) //�� ���� ��ֹ�
                if (p[i][j]->isempty == 0) {
                        blockUL_X = i;
                        blockUL_Y = j;
                        break;
                }
        for (int i = x + 1, j = y - 1; i <= 7 && j >= 0; i++, j--) //�Ʒ� ���� ��ֹ�
                if (p[i][j]->isempty == 0) {
                        blockDL_X = i;
                        blockDL_Y = j;
                        break;
                }
        for (int i = x - 1, j = y + 1; i >= 0 && j <= 7; i--, j++) //�� ������ ��ֹ�
                if (p[i][j]->isempty == 0) {
                        blockUR_X = i;
                        blockUR_Y = j;
                        break;
                }

        for (int i = x + 1; i <= 7; i++) // �Ʒ��� ��ֹ�
                if (p[i][y]->isempty == 0) {
                        blockD = i;
                        break;
                }
        for (int i = x - 1; i >= 0; i--) // ���� ��ֹ�
                if (p[i][y]->isempty == 0) {
                        blockU = i;
                        break;
                }
        for (int i = y + 1; i <= 7; i++) // ������ ��ֹ�
                if (p[x][i]->isempty == 0) {
                        blockR = i;
                        break;
                }
        for (int i = y - 1; i >= 0; i--) // ���� ��ֹ�
                if (p[x][i]->isempty == 0) {
                        blockL = i;
                        break;
                }

        temp = *p[toX - 1][toY - 1]; //�̵��� ŷ�� üũ �� ��� �̵� �Ұ�
        statuemove(p, x, y, toX, toY);
        p[toX - 1][toY - 1]->count--;
        turn--;
        if (check(p) == 0) {
                statuemove(p, toX - 1, toY - 1, x + 1, y + 1);
                p[x][y]->count--;
                turn--;
                *p[toX - 1][toY - 1] = temp;
        }
        else {
                statuemove(p, toX - 1, toY - 1, x + 1, y + 1);
                p[x][y]->count--;
                turn--;
                *p[toX - 1][toY - 1] = temp;
                printf("�Ұ����� �̵��Դϴ�.\n");
                return;
        }

        if ((toX - 1) == x && (toY - 1) == y) printf("���� ��ġ�Դϴ�.\n");
        else if (p[x][y]->color == p[toX - 1][toY - 1]->color) printf("�Ұ����� �̵��Դϴ�.\n");
        else if (p[toX - 1][toY - 1]->isMove == 0) printf("�Ұ����� �̵��Դϴ�.");
        else if ((abs(x - (toX - 1)) == abs(y - (toY - 1))) || (abs(x - (toX - 1)) > 0 && abs(y - (toY - 1)) == 0) || (abs(x - (toX - 1)) == 0 && abs(y - (toY - 1)) > 0))
                statuemove(p, x, y, toX, toY);
        else
                printf("�Ұ����� �̵��Դϴ�.\n");
}


void king_move(Piece* (*p)[8], int x, int y) {
        int toX, toY;
        char tmp;
        Piece temp;

        printf("�̵��� ĭ ��ǥ:");
        scanf(" %c %d", &tmp, &toX);

        toY = (int)(tmp - 'a' + 1);

        temp = *p[toX - 1][toY - 1];
        statuemove(p, x, y, toX, toY);
        p[toX - 1][toY - 1]->count--;
        turn--;
        if (check(p) == 0) {
                statuemove(p, toX - 1, toY - 1, x + 1, y + 1);
                p[x][y]->count--;
                turn--;
                *p[toX - 1][toY - 1] = temp;
        }
        else {
                statuemove(p, toX - 1, toY - 1, x + 1, y + 1);
                p[x][y]->count--;
                turn--;
                *p[toX - 1][toY - 1] = temp;
                printf("�Ұ����� �̵��Դϴ�.\n");
                return;
        }

        if ((toX - 1) == x && (toY - 1) == y) printf("���� ��ġ�Դϴ�.\n");
        else if (p[x][y]->color == p[toX - 1][toY - 1]->color) printf("�Ұ����� �̵��Դϴ�.\n");
        else if (abs(x - (toX - 1)) > 1 || abs(y - (toY - 1)) > 1) printf("�Ұ����� �̵��Դϴ�.\n");
        else
                statuemove(p, x, y, toX, toY);
}

//üũ���� Ȯ���ϴ� �Լ�
int check(Piece* (*p)[8]) {
        int King_x, King_y, Knight_num = 0, Knight1_x, Knight1_y, Knight2_x = 0, Knight2_y = 0;
        for (int i = 0; i < 8; i++)
                for (int j = 0; j < 8; j++)
                        if (p[i][j]->n == KING && p[i][j]->color == turn % 2) { //ŷ�� ��ġ Ȯ��
                                King_x = i;
                                King_y = j;
                        }

                        else if (p[i][j]->n == KNIGHT && p[i][j]->color == (turn + 1) % 2) { //����Ʈ�� ��ġ Ȯ��
                                Knight_num++;
                                Knight1_x = i;
                                Knight1_y = j;
                        }
        printf("King_x = %d, King_y = %d\n", King_x, King_y);

        if (Knight_num == 2) //����Ʈ�� 2���� ��� �ι�° ����Ʈ ��ġ Ȯ��
                for (int i = Knight1_x - 1; i >= 0; i--)
                        for (int j = Knight1_y - 1; j >= 0; j--)
                                if (p[i][j]->n == KNIGHT && p[i][j]->color == (turn + 1) % 2) {
                                        Knight2_x = i;
                                        Knight2_y = j;
                                }

        for (int i = King_x + 1, j = King_y + 1; i <= 7 && j <= 7; i++, j++)
                if (p[i][j]->isempty == 0) { //�Ʒ� ������ ��ֹ��� ��� �� Ȥ�� ��� Ȯ��
                        if ((p[i][j]->color == (turn + 1) % 2) && ((p[i][j]->n == QUEEN) || (p[i][j]->n == BISHOP))) {
                                enemy = *p[i][j];
                                enemy_x = i;
                                enemy_y = j;
                                return 1;
                        }
                        else
                                break;
                }
        for (int i = King_x - 1, j = King_y - 1; i >= 0 && j >= 0; i--, j--) //�� ���� ��ֹ��� ��� �� Ȥ�� ��� Ȯ��
                if (p[i][j]->isempty == 0) {
                        if ((p[i][j]->color == (turn + 1) % 2) && ((p[i][j]->n == QUEEN) || (p[i][j]->n == BISHOP))) {
                                enemy = *p[i][j];
                                enemy_x = i;
                                enemy_y = j;
                                return 1;
                        }
                        else
                                break;
                }
        for (int i = King_x + 1, j = King_y - 1; i <= 7 && j >= 0; i++, j--) //�Ʒ� ���� ��ֹ��� ��� �� Ȥ�� ��� Ȯ��
                if (p[i][j]->isempty == 0) {
                        if ((p[i][j]->color == (turn + 1) % 2) && ((p[i][j]->n == QUEEN) || (p[i][j]->n == BISHOP))) {
                                enemy = *p[i][j];
                                enemy_x = i;
                                enemy_y = j;
                                return 1;
                        }
                        else
                                break;
                }
        for (int i = King_x - 1, j = King_y + 1; i >= 0 && j <= 7; i--, j++) //�� ������ ��ֹ��� ��� �� Ȥ�� ��� Ȯ��
                if (p[i][j]->isempty == 0) {
                        if ((p[i][j]->color == (turn + 1) % 2) && ((p[i][j]->n == QUEEN) || (p[i][j]->n == BISHOP))) {
                                enemy = *p[i][j];
                                enemy_x = i;
                                enemy_y = j;
                                return 1;
                        }
                        else
                                break;
                }
        for (int i = King_x + 1; i <= 7; i++) // �Ʒ��� ��ֹ��� ��� �� Ȥ�� �� Ȯ��
                if (p[i][King_y]->isempty == 0) {
                        if ((p[i][King_y]->color == (turn + 1) % 2) && ((p[i][King_y]->n == QUEEN) || (p[i][King_y]->n == ROOK))) {
                                enemy = *p[i][King_y];
                                enemy_x = i;
                                enemy_y = King_y;
                                return 1;
                        }
                        else
                                break;
                }
        for (int i = King_x - 1; i >= 0; i--) // ���� ��ֹ��� ��� �� Ȥ�� �� Ȯ��
                if (p[i][King_y]->isempty == 0) {
                        if ((p[i][King_y]->color == (turn + 1) % 2) && ((p[i][King_y]->n == QUEEN) || (p[i][King_y]->n == ROOK))) {
                                enemy = *p[i][King_y];
                                enemy_x = i;
                                enemy_y = King_y;
                                return 1;
                        }
                        else
                                break;
                }
        for (int i = King_y + 1; i <= 7; i++) // ������ ��ֹ��� ��� �� Ȥ�� �� Ȯ��
                if (p[King_x][i]->isempty == 0) {
                        if ((p[King_x][i]->color == (turn + 1) % 2) && ((p[King_x][i]->n == QUEEN) || (p[King_x][i]->n == ROOK))) {
                                enemy = *p[King_x][i];
                                enemy_x = i;
                                enemy_y = King_y;
                                return 1;
                        }
                        else
                                break;
                }
        for (int i = King_y - 1; i >= 0; i--) // ���� ��ֹ��� ��� �� Ȥ�� �� Ȯ��
                if (p[King_x][i]->isempty == 0) {
                        if ((p[King_x][i]->color == (turn + 1) % 2) && ((p[King_x][i]->n == QUEEN) || (p[King_x][i]->n == ROOK))) {
                                enemy = *p[King_x][i];
                                enemy_x = King_x;
                                enemy_y = i;
                                return 1;
                        }
                        else
                                break;
                }
        if (Knight_num == 2) { //��� ����Ʈ�� 2���϶� ��ġ Ȯ�� �� üũ
                if (((abs(King_x - Knight1_x) == 1) && (abs(King_y - Knight1_y) == 2)) || ((abs(King_x - Knight1_x) == 2) && (abs(King_y - Knight1_y) == 1))) {
                        enemy = *p[Knight1_x][Knight1_y];
                        enemy_x = Knight1_x;
                        enemy_y = Knight1_y;
                        return 1;
                }
                else if(((abs(King_x - Knight2_x) == 1) && (abs(King_y - Knight2_y) == 2)) || ((abs(King_x - Knight2_x) == 2) && (abs(King_y - Knight2_y) == 1))) {
                        enemy = *p[Knight2_x][Knight2_y];
                        enemy_x = Knight2_x;
                        enemy_y = Knight2_y;
                        return 1;
                }
        }
        else if (Knight_num == 1) { //��� ����Ʈ�� 1���϶� ��ġ Ȯ�� �� üũ
                if (((abs(King_x - Knight1_x) == 1) && (abs(King_y - Knight1_y) == 2)) || ((abs(King_x - Knight1_x) == 2) && (abs(King_y - Knight1_y) == 1))) {
                        enemy = *p[Knight1_x][Knight1_y];
                        enemy_x = Knight1_x;
                        enemy_y = Knight1_y;
                        return 1;
                }
        }

        if (turn % 2 == 0) { //����� ���϶� ŷ�� �� ��ġ �� �� üũ
                if ((King_x > 0) && (King_y > 0) && (King_y < 7)) {
                        if ((p[King_x - 1][King_y - 1]->n == PAWN) && (p[King_x - 1][King_y - 1]->color == 1)) {
                                enemy = *p[King_x - 1][King_y - 1];
                                enemy_x = King_x - 1;
                                enemy_y = King_y - 1;
                                return 1;
                        }
                        else if ((p[King_x - 1][King_y + 1]->n == PAWN) && (p[King_x - 1][King_y + 1]->color == 1)) {
                                enemy = *p[King_x - 1][King_y + 1];
                                enemy_x = King_x - 1;
                                enemy_y = King_y + 1;
                                return 1;
                        }
                }
                else if (King_x > 0 && King_y == 0) {
                        if ((p[King_x - 1][King_y + 1]->n == PAWN) && (p[King_x - 1][King_y + 1]->color == 1)) {
                                enemy = *p[King_x - 1][King_y + 1];
                                enemy_x = King_x - 1;
                                enemy_y = King_y + 1;
                                return 1;
                        }
                }
                else if (King_x > 0 && King_y == 7)
                        if ((p[King_x - 1][King_y - 1]->n == PAWN) && (p[King_x - 1][King_y - 1]->color == 1)) {
                                enemy = *p[King_x - 1][King_y - 1];
                                enemy_x = King_x - 1;
                                enemy_y = King_y - 1;
                                return 1;
                        }
        }
        else if ((turn + 1) % 2 == 0) { ////����� ���϶� ŷ�� �� ��ġ �� �� üũ
                if ((King_x < 7) && (King_y > 0) && (King_y < 7)) {
                        if ((p[King_x + 1][King_y - 1]->n == PAWN) && (p[King_x + 1][King_y - 1]->color == 0)) {
                                enemy = *p[King_x + 1][King_y - 1];
                                enemy_x = King_x + 1;
                                enemy_y = King_y - 1;
                                return 1;
                        }
                        else if((p[King_x + 1][King_y + 1]->n == PAWN) && (p[King_x + 1][King_y + 1]->color == 0)) {
                                enemy = *p[King_x + 1][King_y + 1];
                                enemy_x = King_x + 1;
                                enemy_y = King_y + 1;
                                return 1;
                        }
                }
                else if (King_x < 7 && King_y == 0) {
                        if ((p[King_x + 1][King_y + 1]->n == PAWN) && (p[King_x + 1][King_y + 1]->color == 0)) {
                                enemy = *p[King_x + 1][King_y + 1];
                                enemy_x = King_x + 1;
                                enemy_y = King_y + 1;
                                return 1;
                        }
                }
                else if (King_x < 7 && King_y == 7)
                        if ((p[King_x + 1][King_y - 1]->n == PAWN) && (p[King_x + 1][King_y - 1]->color == 0)) {
                                enemy = *p[King_x + 1][King_y - 1];
                                enemy_x = King_x + 1;
                                enemy_y = King_y - 1;
                                return 1;
                        }
        }

        return 0;
}

int checkmate(Piece* (*p)[8]) {
        int King_x, King_y;
        Piece temp;
        printf("enemy.n = %d, x = %d, y = %d\n", enemy.n, enemy_x, enemy_y);
        for (int i = 0; i < 8; i++)
                for (int j = 0; j < 8; j++)
                        if (p[i][j]->n == KING && p[i][j]->color == turn % 2) { //ŷ�� ��ġ Ȯ��
                                King_x = i;
                                King_y = j;
                        }

        if (King_x > 0 && King_x < 7 && King_y > 0 && King_y < 7) {
                for (int i = King_x - 1; i <= King_x + 1; i++)
                        for (int j = King_y - 1; j <= King_y + 1; j++) {
                                if ((p[King_x][King_y]->color != p[i][j]->color) && (i != King_x || j != King_y)) {
                                        temp = *p[i][j];
                                        statuemove(p, King_x, King_y, i + 1, j + 1);
                                        turn--;
                                        if (check(p) == 0) {
                                                statuemove(p, i, j, King_x + 1, King_y + 1);
                                                turn--;
                                                *p[i][j] = temp;
                                                return 0;
                                        }
                                        else {
                                                statuemove(p, i, j, King_x + 1, King_y + 1);
                                                turn--;
                                                *p[i][j] = temp;
                                        }
                                }
                        }
        }

        else if (King_x == 0 && King_y > 0 && King_y < 7) {
                for (int i = King_x; i <= King_x + 1; i++)
                        for (int j = King_y - 1; j <= King_y + 1; j++) {
                                if ((p[King_x][King_y]->color != p[i][j]->color) && (i != King_x || j != King_y)) {
                                        temp = *p[i][j];
                                        statuemove(p, King_x, King_y, i + 1, j + 1);
                                        turn--;
                                        if (check(p) == 0) {
                                                statuemove(p, i, j, King_x + 1, King_y + 1);
                                                turn--;
                                                *p[i][j] = temp;
                                                return 0;
                                        }
                                        else {
                                                statuemove(p, i, j, King_x + 1, King_y + 1);
                                                turn--;
                                                *p[i][j] = temp;
                                        }
                                }
                        }
        }

        else if (King_x == 7 && King_y > 0 && King_y < 7) {
                for (int i = King_x; i >= King_x - 1; i--)
                        for (int j = King_y - 1; j <= King_y + 1; j++) {
                                if ((p[King_x][King_y]->color != p[i][j]->color) && (i != King_x || j != King_y)) {
                                        temp = *p[i][j];
                                        statuemove(p, King_x, King_y, i + 1, j + 1);
                                        turn--;
                                        if (check(p) == 0) {
                                                statuemove(p, i, j, King_x + 1, King_y + 1);
                                                turn--;
                                                *p[i][j] = temp;
                                                return 0;
                                        }
                                        else {
                                                statuemove(p, i, j, King_x + 1, King_y + 1);
                                                turn--;
                                                *p[i][j] = temp;
                                        }
                                }
                        }
        }

        else if (King_x > 0 && King_x < 7 && King_y == 0) {
                for (int i = King_x - 1; i <= King_x + 1; i++)
                        for (int j = King_y; j <= King_y + 1; j++) {
                                if ((p[King_x][King_y]->color != p[i][j]->color) && (i != King_x || j != King_y)) {
                                        temp = *p[i][j];
                                        statuemove(p, King_x, King_y, i + 1, j + 1);
                                        turn--;
                                        if (check(p) == 0) {
                                                statuemove(p, i, j, King_x + 1, King_y + 1);
                                                turn--;
                                                *p[i][j] = temp;
                                                return 0;
                                        }
                                        else {
                                                statuemove(p, i, j, King_x + 1, King_y + 1);
                                                turn--;
                                                *p[i][j] = temp;
                                        }
                                }
                        }
        }

        else if (King_x > 0 && King_x < 7 && King_y == 7) {
                for (int i = King_x - 1; i <= King_x + 1; i++)
                        for (int j = King_y; j >= King_y - 1; j--) {
                                if ((p[King_x][King_y]->color != p[i][j]->color) && (i != King_x || j != King_y)) {
                                        temp = *p[i][j];
                                        statuemove(p, King_x, King_y, i + 1, j + 1);
                                        turn--;
                                        if (check(p) == 0) {
                                                statuemove(p, i, j, King_x + 1, King_y + 1);
                                                turn--;
                                                *p[i][j] = temp;
                                                return 0;
                                        }
                                        else {
                                                statuemove(p, i, j, King_x + 1, King_y + 1);
                                                turn--;
                                                *p[i][j] = temp;
                                        }
                                }
                        }
        }

        else if (King_x == 0 && King_y == 0) {
                for (int i = King_x; i <= King_x + 1; i++)
                        for (int j = King_y; j <= King_y + 1; j++) {
                                if ((p[King_x][King_y]->color != p[i][j]->color) && (i != King_x || j != King_y)) {
                                        temp = *p[i][j];
                                        statuemove(p, King_x, King_y, i + 1, j + 1);
                                        turn--;
                                        if (check(p) == 0) {
                                                statuemove(p, i, j, King_x + 1, King_y + 1);
                                                turn--;
                                                *p[i][j] = temp;
                                                return 0;
                                        }
                                        else {
                                                statuemove(p, i, j, King_x + 1, King_y + 1);
                                                turn--;
                                                *p[i][j] = temp;
                                        }
                                }
                        }
        }

        else if (King_x == 7 && King_y == 7) {
                for (int i = King_x; i >= King_x - 1; i--)
                        for (int j = King_y; j >= King_y - 1; j--) {
                                if ((p[King_x][King_y]->color != p[i][j]->color) && (i != King_x || j != King_y)) {
                                        temp = *p[i][j];
                                        statuemove(p, King_x, King_y, i + 1, j + 1);
                                        turn--;
                                        if (check(p) == 0) {
                                                statuemove(p, i, j, King_x + 1, King_y + 1);
                                                turn--;
                                                *p[i][j] = temp;
                                                return 0;
                                        }
                                        else {
                                                statuemove(p, i, j, King_x + 1, King_y + 1);
                                                turn--;
                                                *p[i][j] = temp;
                                        }
                                }
                        }
        }

        else if (King_x == 0 && King_y == 7) {
                for (int i = King_x; i <= King_x + 1; i++)
                        for (int j = King_y; j >= King_y - 1; j--) {
                                if ((p[King_x][King_y]->color != p[i][j]->color) && (i != King_x || j != King_y)) {
                                        temp = *p[i][j];
                                        statuemove(p, King_x, King_y, i + 1, j + 1);
                                        turn--;
                                        if (check(p) == 0) {
                                                statuemove(p, i, j, King_x + 1, King_y + 1);
                                                turn--;
                                                *p[i][j] = temp;
                                                return 0;
                                        }
                                        else {
                                                statuemove(p, i, j, King_x + 1, King_y + 1);
                                                turn--;
                                                *p[i][j] = temp;
                                        }
                                }
                        }
        }

        else if (King_x == 7 && King_y == 0) {
                for (int i = King_x; i >= King_x - 1; i--)
                        for (int j = King_y; j <= King_y + 1; j++) {
                                if ((p[King_x][King_y]->color != p[i][j]->color) && (i != King_x || j != King_y)) {
                                        temp = *p[i][j];
                                        statuemove(p, King_x, King_y, i + 1, j + 1);
                                        turn--;
                                        if (check(p) == 0) {
                                                statuemove(p, i, j, King_x + 1, King_y + 1);
                                                turn--;
                                                *p[i][j] = temp;
                                                return 0;
                                        }
                                        else {
                                                statuemove(p, i, j, King_x + 1, King_y + 1);
                                                turn--;
                                                *p[i][j] = temp;
                                        }
                                }
                        }
        }

        switch (enemy.n) {
        case 0:
                for(int i=0; i<8; i++)
                        for(int j=0; j<8; j++) {
                                if(p[i][j]->color == turn % 2) {
                                        initialize_Move(p, i, j);
                                        if(p[enemy_x][enemy_y]->isMove == 1) {
                                                temp = *p[enemy_x][enemy_y];
                                                statuemove(p, i, j, enemy_x + 1, enemy_y + 1);
                                                turn--;
                                                if (check(p) == 0) {
                                                        statuemove(p, enemy_x, enemy_y, i + 1, j + 1);
                                                        turn--;
                                                        *p[enemy_x][enemy_y] = temp;
                                                        return 0;
                                                }
                                                else {
                                                        statuemove(p, enemy_x, enemy_y, i + 1, j + 1);
                                                        turn--;
                                                        *p[enemy_x][enemy_y] = temp;
                                                        return 1;
                                                }
                                        }

                                }
                        }
                return 1;
        case 1:
                for(int i=0; i<8; i++)
                        for(int j=0; j<8; j++) {
                                if(p[i][j]->color == turn % 2) {
                                        initialize_Move(p, i, j);
                                        if(p[enemy_x][enemy_y]->isMove == 1) {
                                                temp = *p[enemy_x][enemy_y];
                                                statuemove(p, i, j, enemy_x + 1, enemy_y + 1);
                                                turn--;
                                                if (check(p) == 0) {
                                                        statuemove(p, enemy_x, enemy_y, i + 1, j + 1);
                                                        turn--;
                                                        *p[enemy_x][enemy_y] = temp;
                                                        return 0;
                                                }
                                                else {
                                                        statuemove(p, enemy_x, enemy_y, i + 1, j + 1);
                                                        turn--;
                                                        *p[enemy_x][enemy_y] = temp;
                                                        return 1;
                                                }
                                        }

                                }
                        }
                return 1;
        case 2:
                for(int i=0; i<8; i++)
                        for(int j=0; j<8; j++)
                                if(p[i][j]->color == turn % 2) {
                                        initialize_Move(p, i, j);
                                        if(King_x > enemy_x && King_y > enemy_y) {
                                                for(int k = 0; k<abs(King_x - enemy_x); k++) {
                                                        if(p[enemy_x+k][enemy_y+k]->isMove == 1) {
                                                                temp = *p[enemy_x+k][enemy_y+k];
                                                                statuemove(p, i, j, enemy_x + k + 1, enemy_y + k + 1);
                                                                turn--;
                                                                if (check(p) == 0) {
                                                                        statuemove(p, enemy_x+ k, enemy_y+ k, i  + 1, j  + 1);
                                                                        turn--;
                                                                        *p[enemy_x+k][enemy_y+k] = temp;
                                                                        return 0;
                                                                }
                                                                else {
                                                                        statuemove(p, enemy_x + k, enemy_y + k, i + 1, j + 1);
                                                                        turn--;
                                                                        *p[enemy_x+k][enemy_y+k] = temp;
                                                                        return 1;
                                                                }
                                                        }
                                                }
                                        }
                                        else if(King_x > enemy_x && King_y < enemy_y) {
                                                for(int k = 0; k<abs(King_x - enemy_x); k++) {
                                                        if(p[enemy_x+k][enemy_y-k]->isMove == 1) {
                                                                temp = *p[enemy_x+k][enemy_y-k];
                                                                statuemove(p, i, j, enemy_x + k + 1, enemy_y - k + 1);
                                                                turn--;
                                                                if (check(p) == 0) {
                                                                        statuemove(p, enemy_x+ k, enemy_y-k, i  + 1, j  + 1);
                                                                        turn--;
                                                                        *p[enemy_x+k][enemy_y-k] = temp;
                                                                        return 0;
                                                                }
                                                                else {
                                                                        statuemove(p, enemy_x + k, enemy_y -k, i + 1, j + 1);
                                                                        turn--;
                                                                        *p[enemy_x+k][enemy_y-k] = temp;
                                                                        return 1;
                                                                }
                                                        }
                                                }
                                        }
                                        else if(King_x < enemy_x && King_y > enemy_y) {
                                                for(int k = 0; k<abs(King_x - enemy_x); k++) {
                                                        if(p[enemy_x-k][enemy_y+k]->isMove == 1) {
                                                                temp = *p[enemy_x-k][enemy_y+k];
                                                                statuemove(p, i, j, enemy_x -k + 1, enemy_y + k + 1);
                                                                turn--;
                                                                if (check(p) == 0) {
                                                                        statuemove(p, enemy_x-k, enemy_y+ k, i  + 1, j  + 1);
                                                                        turn--;
                                                                        *p[enemy_x-k][enemy_y+k] = temp;
                                                                        return 0;
                                                                }
                                                                else {
                                                                        statuemove(p, enemy_x -k, enemy_y + k, i + 1, j + 1);
                                                                        turn--;
                                                                        *p[enemy_x-k][enemy_y+k] = temp;
                                                                        return 1;
                                                                }
                                                        }
                                                }
                                        }
                                        else if(King_x < enemy_x && King_y < enemy_y) {
                                                for(int k = 0; k<abs(King_x - enemy_x); k++) {
                                                        if(p[enemy_x-k][enemy_y-k]->isMove == 1) {
                                                                temp = *p[enemy_x-k][enemy_y-k];
                                                                statuemove(p, i, j, enemy_x -k + 1, enemy_y -k + 1);
                                                                turn--;
                                                                if (check(p) == 0) {
                                                                        statuemove(p, enemy_x-k, enemy_y-k, i  + 1, j  + 1);
                                                                        turn--;
                                                                        *p[enemy_x-k][enemy_y-k] = temp;
                                                                        return 0;
                                                                }
                                                                else {
                                                                        statuemove(p, enemy_x -k, enemy_y -k, i + 1, j + 1);
                                                                        turn--;
                                                                        *p[enemy_x-k][enemy_y-k] = temp;
                                                                        return 1;
                                                                }
                                                        }
                                                }
                                        }
                                }
        case 3:
                for(int i=0; i<8; i++)
                        for(int j=0; j<8; j++)
                                if(p[i][j]->color == turn % 2) {
                                        initialize_Move(p, i, j);
                                        if(King_x > enemy_x && King_y == enemy_y) {
                                                for(int k = 0; k<abs(King_x - enemy_x); k++) {
                                                        if(p[enemy_x+k][enemy_y]->isMove == 1) {
                                                                temp = *p[enemy_x+k][enemy_y];
                                                                statuemove(p, i, j, enemy_x + k + 1, enemy_y + 1);
                                                                turn--;
                                                                if (check(p) == 0) {
                                                                        statuemove(p, enemy_x+ k, enemy_y, i  + 1, j  + 1);
                                                                        turn--;
                                                                        *p[enemy_x+k][enemy_y] = temp;
                                                                        return 0;
                                                                }
                                                                else {
                                                                        statuemove(p, enemy_x + k, enemy_y, i + 1, j + 1);
                                                                        turn--;
                                                                        *p[enemy_x+k][enemy_y] = temp;
                                                                        return 1;
                                                                }
                                                        }
                                                }

                                        }

                                        else if(King_x < enemy_x && King_y == enemy_y) {
                                                for(int k = 0; k<abs(King_x - enemy_x); k++) {
                                                        if(p[enemy_x-k][enemy_y]->isMove == 1) {
                                                                temp = *p[enemy_x-k][enemy_y];
                                                                statuemove(p, i, j, enemy_x - k + 1, enemy_y + 1);
                                                                turn--;
                                                                if (check(p) == 0) {
                                                                        statuemove(p, enemy_x- k, enemy_y, i  + 1, j  + 1);
                                                                        turn--;
                                                                        *p[enemy_x-k][enemy_y] = temp;
                                                                        return 0;
                                                                }
                                                                else {
                                                                        statuemove(p, enemy_x- k, enemy_y, i + 1, j + 1);
                                                                        turn--;
                                                                        *p[enemy_x-k][enemy_y] = temp;
                                                                        return 1;
                                                                }
                                                        }
                                                }

                                        }
                                        else if(King_x == enemy_x && King_y > enemy_y) {
                                                for(int k = 0; k<abs(King_x - enemy_x); k++) {
                                                        if(p[enemy_x][enemy_y+k]->isMove == 1) {
                                                                temp = *p[enemy_x][enemy_y+k];
                                                                statuemove(p, i, j, enemy_x  + 1, enemy_y+ k + 1);
                                                                turn--;
                                                                if (check(p) == 0) {
                                                                        statuemove(p, enemy_x, enemy_y+ k, i  + 1, j  + 1);
                                                                        turn--;
                                                                        *p[enemy_x][enemy_y+k] = temp;
                                                                        return 0;
                                                                }
                                                                else {
                                                                        statuemove(p, enemy_x, enemy_y+ k, i + 1, j + 1);
                                                                        turn--;
                                                                        *p[enemy_x][enemy_y+k] = temp;
                                                                        return 1;
                                                                }
                                                        }
                                                }

                                        }
                                        else if(King_x == enemy_x && King_y < enemy_y) {
                                                for(int k = 0; k<abs(King_x - enemy_x); k++) {
                                                        if(p[enemy_x][enemy_y-k]->isMove == 1) {
                                                                temp = *p[enemy_x][enemy_y-k];
                                                                statuemove(p, i, j, enemy_x + 1, enemy_y -k+ 1);
                                                                turn--;
                                                                if (check(p) == 0) {
                                                                        statuemove(p, enemy_x, enemy_y-k, i  + 1, j  + 1);
                                                                        turn--;
                                                                        *p[enemy_x][enemy_y-k] = temp;
                                                                        return 0;
                                                                }
                                                                else {
                                                                        statuemove(p, enemy_x, enemy_y-k, i + 1, j + 1);
                                                                        turn--;
                                                                        *p[enemy_x][enemy_y-k] = temp;
                                                                        return 1;
                                                                }
                                                        }
                                                }

                                        }
                                }
                return 1;
        case 4:
                for(int i=0; i<8; i++)
                        for(int j=0; j<8; j++)
                                if(p[i][j]->color == turn % 2) {
                                        initialize_Move(p, i, j);
                                        if(King_x > enemy_x && King_y > enemy_y) {
                                                for(int k = 0; k<abs(King_x - enemy_x); k++) {
                                                        if(p[enemy_x+k][enemy_y+k]->isMove == 1) {
                                                                temp = *p[enemy_x+k][enemy_y+k];
                                                                statuemove(p, i, j, enemy_x + k + 1, enemy_y + k + 1);
                                                                turn--;
                                                                if (check(p) == 0) {
                                                                        statuemove(p, enemy_x+ k, enemy_y+ k, i  + 1, j  + 1);
                                                                        turn--;
                                                                        *p[enemy_x+k][enemy_y+k] = temp;
                                                                        return 0;
                                                                }
                                                                else {
                                                                        statuemove(p, enemy_x + k, enemy_y + k, i + 1, j + 1);
                                                                        turn--;
                                                                        *p[enemy_x+k][enemy_y+k] = temp;
                                                                        return 1;
                                                                }
                                                        }
                                                }
                                        }
                                        else if(King_x > enemy_x && King_y < enemy_y) {
                                                for(int k = 0; k<abs(King_x - enemy_x); k++) {
                                                        if(p[enemy_x+k][enemy_y-k]->isMove == 1) {
                                                                temp = *p[enemy_x+k][enemy_y-k];
                                                                statuemove(p, i, j, enemy_x + k + 1, enemy_y - k + 1);
                                                                turn--;
                                                                if (check(p) == 0) {
                                                                        statuemove(p, enemy_x+ k, enemy_y-k, i  + 1, j  + 1);
                                                                        turn--;
                                                                        *p[enemy_x+k][enemy_y-k] = temp;
                                                                        return 0;
                                                                }
                                                                else {
                                                                        statuemove(p, enemy_x + k, enemy_y -k, i + 1, j + 1);
                                                                        turn--;
                                                                        *p[enemy_x+k][enemy_y-k] = temp;
                                                                        return 1;
                                                                }
                                                        }
                                                }
                                        }
                                        else if(King_x < enemy_x && King_y > enemy_y) {
                                                for(int k = 0; k<abs(King_x - enemy_x); k++) {
                                                        if(p[enemy_x-k][enemy_y+k]->isMove == 1) {
                                                                temp = *p[enemy_x-k][enemy_y+k];
                                                                statuemove(p, i, j, enemy_x -k + 1, enemy_y + k + 1);
                                                                turn--;
                                                                if (check(p) == 0) {
                                                                        statuemove(p, enemy_x-k, enemy_y+ k, i  + 1, j  + 1);
                                                                        turn--;
                                                                        *p[enemy_x-k][enemy_y+k] = temp;
                                                                        return 0;
                                                                }
                                                                else {
                                                                        statuemove(p, enemy_x -k, enemy_y + k, i + 1, j + 1);
                                                                        turn--;
                                                                        *p[enemy_x-k][enemy_y+k] = temp;
                                                                        return 1;
                                                                }
                                                        }
                                                }
                                        }
                                        else if(King_x < enemy_x && King_y < enemy_y) {
                                                for(int k = 0; k<abs(King_x - enemy_x); k++) {
                                                        if(p[enemy_x-k][enemy_y-k]->isMove == 1) {
                                                                temp = *p[enemy_x-k][enemy_y-k];
                                                                statuemove(p, i, j, enemy_x -k + 1, enemy_y -k + 1);
                                                                turn--;
                                                                if (check(p) == 0) {
                                                                        statuemove(p, enemy_x-k, enemy_y-k, i  + 1, j  + 1);
                                                                        turn--;
                                                                        *p[enemy_x-k][enemy_y-k] = temp;
                                                                        return 0;
                                                                }
                                                                else {
                                                                        statuemove(p, enemy_x -k, enemy_y -k, i + 1, j + 1);
                                                                        turn--;
                                                                        *p[enemy_x-k][enemy_y-k] = temp;
                                                                        return 1;
                                                                }
                                                        }

                                                        else if(King_x > enemy_x && King_y == enemy_y) {
                                                                for(int k = 0; k<abs(King_x - enemy_x); k++) {
                                                                        if(p[enemy_x+k][enemy_y]->isMove == 1) {
                                                                                temp = *p[enemy_x+k][enemy_y];
                                                                                statuemove(p, i, j, enemy_x + k + 1, enemy_y + 1);
                                                                                turn--;
                                                                                if (check(p) == 0) {
                                                                                        statuemove(p, enemy_x+ k, enemy_y, i  + 1, j  + 1);
                                                                                        turn--;
                                                                                        *p[enemy_x+k][enemy_y] = temp;
                                                                                        return 0;
                                                                                }
                                                                                else {
                                                                                        statuemove(p, enemy_x + k, enemy_y, i + 1, j + 1);
                                                                                        turn--;
                                                                                        *p[enemy_x+k][enemy_y] = temp;
                                                                                        return 1;
                                                                                }
                                                                        }
                                                                }

                                                        }

                                                        else if(King_x < enemy_x && King_y == enemy_y) {
                                                                for(int k = 0; k<abs(King_x - enemy_x); k++) {
                                                                        if(p[enemy_x-k][enemy_y]->isMove == 1) {
                                                                                temp = *p[enemy_x-k][enemy_y];
                                                                                statuemove(p, i, j, enemy_x - k + 1, enemy_y + 1);
                                                                                turn--;
                                                                                if (check(p) == 0) {
                                                                                        statuemove(p, enemy_x- k, enemy_y, i  + 1, j  + 1);
                                                                                        turn--;
                                                                                        *p[enemy_x-k][enemy_y] = temp;
                                                                                        return 0;
                                                                                }
                                                                                else {
                                                                                        statuemove(p, enemy_x- k, enemy_y, i + 1, j + 1);
                                                                                        turn--;
                                                                                        *p[enemy_x-k][enemy_y] = temp;
                                                                                        return 1;
                                                                                }
                                                                        }
                                                                }

                                                        }
                                                        else if(King_x == enemy_x && King_y > enemy_y) {
                                                                for(int k = 0; k<abs(King_x - enemy_x); k++) {
                                                                        if(p[enemy_x][enemy_y+k]->isMove == 1) {
                                                                                temp = *p[enemy_x][enemy_y+k];
                                                                                statuemove(p, i, j, enemy_x  + 1, enemy_y+ k + 1);
                                                                                turn--;
                                                                                if (check(p) == 0) {
                                                                                        statuemove(p, enemy_x, enemy_y+ k, i  + 1, j  + 1);
                                                                                        turn--;
                                                                                        *p[enemy_x][enemy_y+k] = temp;
                                                                                        return 0;
                                                                                }
                                                                                else {
                                                                                        statuemove(p, enemy_x, enemy_y+ k, i + 1, j + 1);
                                                                                        turn--;
                                                                                        *p[enemy_x][enemy_y+k] = temp;
                                                                                        return 1;
                                                                                }
                                                                        }
                                                                }

                                                        }
                                                        else if(King_x == enemy_x && King_y < enemy_y) {
                                                                for(int k = 0; k<abs(King_x - enemy_x); k++) {
                                                                        if(p[enemy_x][enemy_y-k]->isMove == 1) {
                                                                                temp = *p[enemy_x][enemy_y-k];
                                                                                statuemove(p, i, j, enemy_x + 1, enemy_y -k+ 1);
                                                                                turn--;
                                                                                if (check(p) == 0) {
                                                                                        statuemove(p, enemy_x, enemy_y-k, i  + 1, j  + 1);
                                                                                        turn--;
                                                                                        *p[enemy_x][enemy_y-k] = temp;
                                                                                        return 0;
                                                                                }
                                                                                else {
                                                                                        statuemove(p, enemy_x, enemy_y-k, i + 1, j + 1);
                                                                                        turn--;
                                                                                        *p[enemy_x][enemy_y-k] = temp;
                                                                                        return 1;
                                                                                }
                                                                        }
                                                                }
                                                        }

                                                }
                                        }
                                }
        }
}

void saveGame(Piece* (*p)[8]) {//���� ����

        FILE* fp;
        char path[20];

        printf("�̸��� �Է��ϼ���: ");
        scanf("%s", path);
        strcat(path, ".bin");

        fp = fopen(path, "wb");
        if (fp == NULL) {
                printf("������ �� �� �����ϴ�.\n");
                return;
        }

        for (int i = 0; i < 8; i++)
                for (int j = 0; j < 8; j++)
                        fwrite(p[i][j], sizeof(*p[i][j]), 1, fp);
        fclose(fp);

        printf("������ �Ϸ�Ǿ����ϴ�.\n");

}

void LoadGame(Piece* (*p)[8]) {//���� �ҷ�����

        FILE* fp;
        int lineNum = 0, bytes;
        char path[20], buffer[35];

        printf("�̸��� �Է��ϼ���: ");
        scanf("%s", path);
        strcat(path, ".bin");

        fp = fopen(path, "rb");
        if (fp == NULL) {
                printf("����� ������ �����ϴ�.���ο� ������ �����մϴ�.\n");
                Sleep(3000);
                return;
        }

        for (int i = 0; i < 8; i++)
                for (int j = 0; j < 8; j++) fread(p[i][j], sizeof(*p[i][j]), 1, fp);
}

void clearBuffer(void) {//�Է� ���� ����
        while (getchar() != '\n');
}

void castling(Piece* (*p)[8]) {
        int King_x, King_y, Rook1_x, Rook1_y, Rook2_x, Rook2_y,Rooknum = 0, num;
        Piece temp;

        for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                        if (p[i][j]->n == KING && p[i][j]->color == turn % 2) { //ŷ�� ��ġ Ȯ��
                                King_x = i;
                                King_y = j;
                        }

                        if (p[i][j]->n == ROOK && p[i][j]->color == turn % 2) { //ŷ�� ��ġ Ȯ��
                                if (Rooknum == 0) {
                                        Rook1_x = i;
                                        Rook1_y = j;
                                        Rooknum++;
                                }
                                else {
                                        Rook2_x = i;
                                        Rook2_y = j;
                                }
                        }
                }
        }

        if (p[King_x][King_y]->count != 0) {
                printf("ĳ���� �Ұ�\n");
                return;
        }

        else {

                printf("1.ŷ ���̵� ĳ���� 2. �� ���̵� ĳ����");
                scanf("%d", &num);


                if (num == 1) {

                        if (p[Rook2_x][Rook2_y]->count != 0) {
                                printf("�� �̵���. ĳ���� �Ұ�\n");
                                return;
                        }

                        else {
                                for (int i = King_y + 1; i < Rook2_y; i++) {
                                        if (p[King_x][i]->isempty == 0) {
                                                printf("��ֹ�. ĳ���� �Ұ�\n");
                                                return;
                                        }
                                }

                                temp = *p[King_x][King_y+2]; //�̵��� ŷ�� üũ �� ��� �̵� �Ұ�
                                statuemove(p, King_x, King_y, King_x+1, King_y+3);
                                p[King_x][King_y+2]->count--;
                                turn--;
                                if (check(p) == 0) {
                                        statuemove(p, Rook2_x, Rook2_y, King_x + 1, King_y + 2);
                                        p[King_x][King_y+2]->count++;
                                        *p[King_x][King_y] = temp;
                                }
                                else {
                                        statuemove(p, King_x, King_y+2, King_x+1, King_y+1);
                                        p[King_x][King_y]->count--;
                                        turn--;
                                        *p[King_x][King_y+2] = temp;
                                        printf("�̵��� üũ. ĳ���� �Ұ�\n");
                                        return;
                                }


                        }
                }

                if (num == 2) {
                        if (p[Rook1_x][Rook1_y]->count != 0) {
                                printf("ĳ���� �Ұ�\n");
                                return;
                        }
                        else {

                                for (int i = Rook1_y + 1; i < King_y; i++) {
                                        if (p[King_x][i]->isempty == 0) {
                                                printf("��ֹ�. ĳ���� �Ұ�\n");
                                                return;
                                        }
                                }

                                temp = *p[King_x][King_y - 2]; //�̵��� ŷ�� üũ �� ��� �̵� �Ұ�
                                statuemove(p, King_x, King_y, King_x + 1, King_y - 1);
                                p[King_x][King_y - 2]->count--;
                                turn--;
                                if (check(p) == 0) {
                                        statuemove(p, Rook1_x, Rook1_y, King_x + 1, King_y);
                                        p[King_x][King_y - 2]->count++;
                                        *p[King_x][King_y] = temp;
                                }
                                else {
                                        statuemove(p, King_x, King_y - 2, King_x + 1, King_y + 1);
                                        p[King_x][King_y]->count--;
                                        turn--;
                                        *p[King_x][King_y - 2] = temp;
                                        printf("�̵��� üũ. ĳ���� �Ұ�\n");
                                        return;
                                }

                        }
                }

        }

        system("cls");
        print_map(p, -1, -1);

}


void move(Piece* (*p)[8]) {
        int fromX, fromY, save;
        char tmp;

        while (1) {
                printf("1.�̵�  2.���� ���� 3.ĳ���� 4.���� ");
                if (scanf("%d", &save) != 1) clearBuffer();
                if (save == 1) break;
                if (save == 2) saveGame(p);
                if (save == 3) castling(p);
                if (save == 4) exit(0);
        }

        while (1)
        {
                printf("�̵��� �⹰ ��ǥ(�Է� ��� : a 1) : ");
                scanf(" %c %d", &tmp, &fromX);

                fromY = (int)(tmp - 'a' + 1);

                if (fromX < 1 || fromX>8 || fromY < 1 || fromY>8) printf("���� ��� ��ǥ�Դϴ�.\n"); // ���� �����
                else
                {
                        if (p[fromX - 1][fromY - 1]->isempty == 1) printf("�̵��� �� �ִ� �⹰�� �����ϴ�..\n"); // �� ��ǥ�� ���� ������ �ٽ� �Է¹���
                        else if (turn % 2 == 0 && p[fromX - 1][fromY - 1]->color == 1) printf("����� ���Դϴ�.\n");
                        else if (turn % 2 == 1 && p[fromX - 1][fromY - 1]->color == 0) printf("����� ���Դϴ�.\n");
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


void startGame(Piece* (*p)[8]) {//���� ���� �޴�
        int menuNum;
        while (1) {
                printf("1. �� ����  2. �̾��ϱ� 3. ����\n");
                if (!scanf("%d", &menuNum)) clearBuffer();
                if (menuNum == 1) break;
                else if (menuNum == 2) {
                        LoadGame(p);
                        break;
                }
                else if (menuNum == 3) exit(0);
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
        startGame(map);
        system("cls");

        while (1)
        {
                print_map(map, -1, -1); // ������ �⹰�� ���� ������ ���� �� ���
                if (check(map) == 1) {
                        if (checkmate(map) == 1) {
                                printf("üũ����Ʈ\n");
                                exit(0);
                        }
                        else
                                printf("üũ\n");
                }

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
