#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
enum name { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, NONE };
int turn = 0;

typedef struct piece
{
   _Bool isempty;//���� ������ 0, ������ 1.
   enum name n;
   int color;//���̸� 0, ���̸� 1, ������ 2
   int count;//�̵��� Ƚ��
   _Bool alive;//����̸� 0, �����̸� 1
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
	 //�� ���� �ʱ�ȭ
	 for(int i = 2; i < 6; i++)
	 	for(int j = 0; j < 8; j++){
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

               case 1: // ����Ʈ
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
               case 4: // ��
                  if ((abs(x - i) == abs(y - j)) || x == i || y == j)
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
void statuemove(Piece* (*p)[8], int x, int y, int toX, int toY){
	p[toX - 1][toY - 1]->isempty = 0;
	p[toX - 1][toY - 1]->n = p[x][y]->n;
	p[toX - 1][toY - 1]->color = p[x][y]->color;
	p[toX - 1][toY - 1]->alive = p[x][y]->alive;
	p[toX - 1][toY - 1]->count = p[x][y]->count + 1;
	p[x][y]->isempty = 1;
	p[x][y]->n = NONE;
	p[x][y]->color = 3;
	p[x][y]->alive = 0;
	p[x][y]->count = 0;
  turn++;
}

//�� �̵� �Լ�
void pawn_move(Piece* (*p)[8], int x, int y) {
   int toX, toY;
   printf("�̵��� ĭ ��ǥ:");
   scanf("%d %d", &toX, &toY);

   if (p[x][y]->color == p[toX - 1][toY - 1]->color) { //���� �� �Ա� �Ұ�
   printf("�Ұ����� �̵��Դϴ�.\n");
   return ;
}

 if (p[x][y]->color == 0) {	//������ ���� ���϶�
   if (p[toX - 1][toY - 1]->isempty == 1) { //������ ���� ���� ���� ��
      if (p[x][y]->count == 0) //���� �ѹ��� �� �������� ��
         if ((x - (toX - 1) == 2 && (y - (toY - 1)) == 0) || (x - (toX - 1) == 1 && (y - (toY - 1)) == 0)) { //���η� 2ĭ���� �̵� ����
					  statuemove(p,x,y,toX,toY);
         }
         else printf("�Ұ����� �̵��Դϴ�.\n");
      else { //���� 1�� �̻� �������� ��
				if ((x - (toX - 1) == 1 && (y - (toY - 1)) == 0) ) { //1ĭ���� �̵� ����
					 statuemove(p,x,y,toX,toY);
				}
				else printf("�Ұ����� �̵��Դϴ�.\n");
			}
    }
   else { //������ ���� ��밡 ���� ��
      if ((x - (toX - 1)) == 1 && abs(y - (toY - 1)) == 1) { //�밢������ �� ĭ���� �̵� ����
         statuemove(p,x,y,toX,toY);
      }
      else printf("�Ұ����� �̵��Դϴ�.\n");
   }
 }
 else{ //������ ���� ���϶�
	 if (p[toX - 1][toY - 1]->isempty == 1) { //������ ���� ���� ���� ��
			if (p[x][y]->count == 0) //���� �ѹ��� �� �������� ��
				 if ((x - (toX - 1) == -2 && (y - (toY - 1)) == 0) || (x - (toX - 1) == -1 && (y - (toY - 1)) == 0) ) { //���η� 2ĭ���� �̵� ����
						statuemove(p,x,y,toX,toY);
				 }
				 else printf("�Ұ����� �̵��Դϴ�.\n");
			else { //���� 1�� �̻� �������� ��
				if ((x - (toX - 1) == -1 && (y - (toY - 1)) == 0) ) { //1ĭ���� �̵� ����
					 statuemove(p,x,y,toX,toY);
				}
				else printf("�Ұ����� �̵��Դϴ�.\n");
						}
		}
	 else { // ������ ���� ��밡 ���� ��
			if ((x - (toX - 1)) == -1 && abs(y - (toY - 1)) == 1) {      //�밢������ �� ĭ���� �̵� ����
				 statuemove(p,x,y,toX,toY);
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
   printf("�̵��� ĭ ��ǥ:");
   scanf("%d %d", &toX, &toY);

   if ((toX - 1) == x && (toY - 1) == y) printf("���� ��ġ�Դϴ�.\n");      //���� ��ġ �Ұ���
   else if (p[x][y]->color == p[toX - 1][toY - 1]->color) printf("�Ұ����� �̵��Դϴ�.\n");      //���� �� �Ա� �Ұ�
   else if (((abs(x - (toX - 1)) == 1) && (abs(y - (toY - 1)) == 2)) || ((abs(x - (toX - 1)) == 2) && (abs(y - (toY - 1)) == 1))) {
    statuemove(p,x,y,toX,toY);
    }
    else
      printf("�Ұ����� �̵��Դϴ�.\n");
}



void bishop_move(Piece* (*p)[8], int x, int y) {
   int toX, toY,blockDR_X = 7, blockDR_Y = 7, blockUL_X = 0, blockUL_Y = 0, blockDL_X = 7, blockDL_Y = 7, blockUR_X = 0, blockUR_Y = 7;

      printf("�̵��� ĭ ��ǥ:");
      scanf("%d %d", &toX, &toY);

			//��� ��ֹ� ã��
			for(int i = x+1, j = y+1; i <= 7 && j <= 7; i++, j++) //�Ʒ� ������ ��ֹ�
				if(p[i][j]->isempty == 0){
					blockDR_X = i;
					blockDR_Y = j;
					break;
					}
			for(int i = x-1, j = y-1; i >= 0 && j >= 0; i--, j--) //�� ���� ��ֹ�
				if(p[i][j]->isempty == 0){
					blockUL_X = i;
					blockUL_Y = j;
					break;
					}
			for(int i = x+1, j = y-1; i <= 7 && j >= 0; i++, j--) //�Ʒ� ���� ��ֹ�
				if(p[i][j]->isempty == 0){
					blockDL_X = i;
					blockDL_Y = j;//���� �Ʒ��� ��ֹ�
					break;
					}
			for(int i = x-1, j = y+1; i >= 0 && j <= 7; i--, j++) //�� ������ ��ֹ�
				if(p[i][j]->isempty == 0){
					blockUR_X = i;
					blockUR_Y = j;
					break;
					}

      if ((toX - 1) == x && (toY - 1) == y) printf("���� ��ġ�Դϴ�.\n");
      else if (p[x][y]->color == p[toX - 1][toY - 1]->color) printf("�Ұ����� �̵��Դϴ�.\n");
      else if (abs(x - (toX - 1)) != abs(y - (toY - 1))) printf("�Ұ����� �̵��Դϴ�.\n");
			else if ((toX-1 > blockDR_X && toY-1 > blockDR_Y) || (toX-1 < blockUL_X && toY-1 < blockUL_Y) || (toX-1 > blockDL_X && toY-1 < blockDL_Y) || (toX-1 < blockUR_X && toY-1 > blockUR_Y)) printf("�Ұ����� �̵��Դϴ�.\n");
      else
         statuemove(p,x,y,toX,toY);
   }


void rook_move(Piece* (*p)[8], int x, int y) {
   int toX, toY,blockD = 7,blockU = 0,blockR = 7,blockL = 0;

      printf("�̵��� ĭ ��ǥ:");
      scanf("%d %d", &toX, &toY);

			for(int i = x+1; i <= 7; i++) // �Ʒ��� ��ֹ�
				if(p[i][y]->isempty == 0){
					blockD = i;
					break;
				}
			for(int i = x-1; i >= 0; i--) // ���� ��ֹ�
				if(p[i][y]->isempty == 0){
					blockU = i;
					break;
				}
			for(int i = y+1; i <= 7; i++) // ������ ��ֹ�
				if(p[x][i]->isempty == 0){
					blockR = i;
					break;
				}
			for(int i = y-1; i >= 0; i--) // ���� ��ֹ�
				if(p[x][i]->isempty == 0){
					blockL = i;
					break;
				}

      if ((toX - 1) == x && (toY - 1) == y) printf("���� ��ġ�Դϴ�.\n");
      else if (p[x][y]->color == p[toX - 1][toY - 1]->color) printf("�Ұ����� �̵��Դϴ�.\n");
      else if ((abs(x - (toX - 1)) > 0 && abs(y - (toY - 1)) > 0)) printf("�Ұ����� �̵��Դϴ�.\n");
			else if (toX-1 > blockD || toX-1 < blockU || toY-1 > blockR || toY-1 < blockL) printf("�Ұ����� �̵��Դϴ�.\n");
      else
        statuemove(p,x,y,toX,toY);
   }


void queen_move(Piece* (*p)[8], int x, int y) {
   int toX, toY, blockDR_X = 7, blockDR_Y = 7, blockUL_X = 0, blockUL_Y = 0, blockDL_X = 7, blockDL_Y = 7, blockUR_X = 0, blockUR_Y = 7, blockD = 7, blockU = 0, blockR = 7, blockL = 0;

      printf("�̵��� ĭ ��ǥ:");
      scanf("%d %d", &toX, &toY);
			//�� ��ֹ� ã��(������ ���� ��� ����)
			for(int i = x+1, j = y+1; i <= 7 && j <= 7; i++, j++) //�Ʒ� ������ ��ֹ�
				if(p[i][j]->isempty == 0){
					blockDR_X = i;
					blockDR_Y = j;
					break;
					}
			for(int i = x-1, j = y-1; i >= 0 && j >= 0; i--, j--) //�� ���� ��ֹ�
				if(p[i][j]->isempty == 0){
					blockUL_X = i;
					blockUL_Y = j;
					break;
					}
			for(int i = x+1, j = y-1; i <= 7 && j >= 0; i++, j--) //�Ʒ� ���� ��ֹ�
				if(p[i][j]->isempty == 0){
					blockDL_X = i;
					blockDL_Y = j;
					break;
					}
			for(int i = x-1, j = y+1; i >= 0 && j <= 7; i--, j++) //�� ������ ��ֹ�
				if(p[i][j]->isempty == 0){
					blockUR_X = i;
					blockUR_Y = j;
					break;
					}

			for(int i = x+1; i <= 7; i++) // �Ʒ��� ��ֹ�
				if(p[i][y]->isempty == 0){
					blockD = i;
					break;
				}
			for(int i = x-1; i >= 0; i--) // ���� ��ֹ�
				if(p[i][y]->isempty == 0){
					blockU = i;
					break;
				}
			for(int i = y+1; i <= 7; i++) // ������ ��ֹ�
				if(p[x][i]->isempty == 0){
					blockR = i;
					break;
				}
			for(int i = y-1; i >= 0; i--) // ���� ��ֹ�
				if(p[x][i]->isempty == 0){
					blockL = i;
					break;
				}


      if ((toX - 1) == x && (toY - 1) == y) printf("���� ��ġ�Դϴ�.\n");
      else if (p[x][y]->color == p[toX - 1][toY - 1]->color) printf("�Ұ����� �̵��Դϴ�.\n");
			else if ((toX-1 > blockDR_X && toY-1 > blockDR_Y) || (toX-1 < blockUL_X && toY-1 < blockUL_Y) || (toX-1 > blockDL_X && toY-1 < blockDL_Y) || (toX-1 < blockUR_X && toY-1 > blockUR_Y)) printf("�Ұ����� �̵��Դϴ�.");
			else if (((toX-1 > blockD) && (toY-1 == y))|| ((toX-1 < blockU) && (toY-1 == y))|| ((toY-1 > blockR) && (toX-1 == x))|| ((toY-1 < blockL) && (toX-1 == x))) printf("�Ұ����� �̵��Դϴ�.\n");
      else if ((abs(x - (toX - 1)) == abs(y - (toY - 1))) || (abs(x - (toX - 1)) > 0 && abs(y - (toY - 1)) == 0) || (abs(x - (toX - 1)) == 0 && abs(y - (toY - 1)) > 0))
         statuemove(p,x,y,toX,toY);
      else
         printf("�Ұ����� �̵��Դϴ�.\n");
   }


void king_move(Piece* (*p)[8], int x, int y) {
   int toX, toY;

      printf("�̵��� ĭ ��ǥ:");
      scanf("%d %d", &toX, &toY);

      if ((toX - 1) == x && (toY - 1) == y) printf("���� ��ġ�Դϴ�.\n");
      else if (p[x][y]->color == p[toX - 1][toY - 1]->color) printf("�Ұ����� �̵��Դϴ�.\n");
      else if (abs(x - (toX - 1)) > 1 || abs(y - (toY - 1)) > 1) printf("�Ұ����� �̵��Դϴ�.\n");
      else
        statuemove(p,x,y,toX,toY);
   }

//üũ���� Ȯ���ϴ� �Լ�
int check(Piece* (*p)[8]){
	int King_x, King_y, Knight_num = 0 ,Knight1_x, Knight1_y, Knight2_x, Knight2_y;
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			if(p[i][j]-> n == KING && p[i][j]->color == turn%2){ //ŷ�� ��ġ Ȯ��
				King_x = i;
				King_y = j;
			}
      else if(p[i][j]-> n == KNIGHT && p[i][j]->color == (turn+1)%2){ //����Ʈ�� ��ġ Ȯ��
        Knight_num++;
        Knight1_x = i;
        Knight1_y = j;
      }
  if(Knight_num == 2) //����Ʈ�� 2���� ��� �ι�° ����Ʈ ��ġ Ȯ��
    for(int i = Knight1_x-1; i >= 0; i--)
  	 for(int j = Knight1_y-1; j >= 0; j--)
      if(p[i][j]-> n == KNIGHT && p[i][j]->color == (turn+1)%2){
        Knight2_x = i;
        Knight2_y = j;
      }

			for(int i = King_x+1, j = King_y+1; i <= 7 && j <= 7; i++, j++)
				if(p[i][j]->isempty == 0){ //�Ʒ� ������ ��ֹ��� ��� �� Ȥ�� ��� Ȯ��
					if((p[i][j]->color == (turn+1)%2) && ((p[i][j]->n == QUEEN) || (p[i][j]->n == BISHOP))){
						return 1;
					}
					else
						break;
					}
			for(int i = King_x-1, j = King_y-1; i >= 0 && j >= 0; i--, j--) //�� ���� ��ֹ��� ��� �� Ȥ�� ��� Ȯ��
				if(p[i][j]->isempty == 0){
					if((p[i][j]->color == (turn+1)%2) && ((p[i][j]->n == QUEEN) || (p[i][j]->n == BISHOP))){
						return 1;
					}
					else
						break;
					}
			for(int i = King_x+1, j = King_y-1; i <= 7 && j >= 0; i++, j--) //�Ʒ� ���� ��ֹ��� ��� �� Ȥ�� ��� Ȯ��
				if(p[i][j]->isempty == 0){
					if((p[i][j]->color == (turn+1)%2) && ((p[i][j]->n == QUEEN) || (p[i][j]->n == BISHOP))){
						return 1;
					}
					else
						break;
					}
			for(int i = King_x-1, j = King_y+1; i >= 0 && j <= 7; i--, j++) //�� ������ ��ֹ��� ��� �� Ȥ�� ��� Ȯ��
				if(p[i][j]->isempty == 0){
					if((p[i][j]->color == (turn+1)%2) && ((p[i][j]->n == QUEEN) || (p[i][j]->n == BISHOP))){
						return 1;
					}
					else
						break;
					}
			for(int i = King_x+1; i <= 7; i++) // �Ʒ��� ��ֹ��� ��� �� Ȥ�� �� Ȯ��
				if(p[i][King_y]->isempty == 0){
					if((p[i][King_y]->color == (turn+1)%2) && ((p[i][King_y]->n == QUEEN) || (p[i][King_y]->n == ROOK))){
						return 1;
					}
					else
						break;
					}
			for(int i = King_x-1; i >= 0; i--) // ���� ��ֹ��� ��� �� Ȥ�� �� Ȯ��
				if(p[i][King_y]->isempty == 0){
					if((p[i][King_y]->color == (turn+1)%2) && ((p[i][King_y]->n == QUEEN) || (p[i][King_y]->n == ROOK))){
						return 1;
					}
					else
						break;
					}
			for(int i = King_y+1; i <= 7; i++) // ������ ��ֹ��� ��� �� Ȥ�� �� Ȯ��
				if(p[King_x][i]->isempty == 0){
					if((p[King_x][i]->color == (turn+1)%2) && ((p[King_x][i]->n == QUEEN) || (p[King_x][i]->n == ROOK))){
						return 1;
					}
					else
						break;
					}
			for(int i = King_y-1; i >= 0; i--) // ���� ��ֹ��� ��� �� Ȥ�� �� Ȯ��
				if(p[King_x][i]->isempty == 0){
					if((p[King_x][i]->color == (turn+1)%2) && ((p[King_x][i]->n == QUEEN) || (p[King_x][i]->n == ROOK))){
						return 1;
					}
					else
						break;
					}
      if(Knight_num == 2){ //��� ����Ʈ�� 2���϶� ��ġ Ȯ�� �� üũ
        if(((abs(King_x - Knight1_x) == 1) && (abs(King_y - Knight1_y) == 2)) || ((abs(King_x - Knight1_x) == 2) && (abs(King_y - Knight1_y) == 1)) || ((abs(King_x - Knight2_x) == 1) && (abs(King_y - Knight2_y) == 2)) || ((abs(King_x - Knight2_x) == 2) && (abs(King_y - Knight2_y) == 1))){
          return 1;
          }
        }
      else if(Knight_num == 1){ //��� ����Ʈ�� 1���϶� ��ġ Ȯ�� �� üũ
        if(((abs(King_x - Knight1_x) == 1) && (abs(King_y - Knight1_y) == 2)) || ((abs(King_x - Knight1_x) == 2) && (abs(King_y - Knight1_y) == 1)))
        return 1;
      }

        if(turn%2 == 0){ //����� ���϶� ŷ�� �� ��ġ �� �� üũ
          if((King_x > 0) && (King_y > 0) && (King_y < 7))
            if(((p[King_x-1][King_y-1]->n == PAWN) && (p[King_x-1][King_y-1]->color == 1)) || ((p[King_x-1][King_y+1]->n == PAWN) && (p[King_x-1][King_y+1]->color == 1)))
              return 1;
            else if(King_x > 0 && King_y == 0)
              if((p[King_x-1][King_y+1]->n == PAWN) && (p[King_x-1][King_y+1]->color == 1))
                return 1;
            else if(King_x > 0 && King_y == 7)
              if((p[King_x-1][King_y-1]->n == PAWN) && (p[King_x-1][King_y-1]->color == 1))
                return 1;
        }
        else if((turn+1)%2 == 0){ ////����� ���϶� ŷ�� �� ��ġ �� �� üũ
          if((King_x < 7) && (King_y > 0) && (King_y < 7))
            if(((p[King_x+1][King_y-1]->n == PAWN) && (p[King_x+1][King_y-1]->color == 0)) || ((p[King_x+1][King_y+1]->n == PAWN) && (p[King_x+1][King_y+1]->color == 0)))
              return 1;
            else if(King_x < 7 && King_y == 0)
              if((p[King_x+1][King_y+1]->n == PAWN) && (p[King_x+1][King_y+1]->color == 0))
                return 1;
            else if(King_x < 7 && King_y == 7)
              if((p[King_x+1][King_y-1]->n == PAWN) && (p[King_x+1][King_y-1]->color == 0))
                return 1;
        }

        else return 0;
        return 0;
}


void move(Piece* (*p)[8]) {
   int fromX, fromY;

   while (1)
   {
      printf("�̵��� �⹰ ��ǥ:");
      scanf("%d %d", &fromX, &fromY);

      if (fromX < 1 || fromX>8 || fromY < 1 || fromY>8) printf("���� ��� ��ǥ�Դϴ�.\n"); // ���� �����
      else
      {
         if (p[fromX - 1][fromY - 1]->isempty == 1) printf("�̵��� �� �ִ� �⹰�� �����ϴ�..\n"); // �� ��ǥ�� ���� ������ �ٽ� �Է¹���
         else if(turn%2 == 0 && p[fromX-1][fromY-1]->color == 1) printf("����� ���Դϴ�.\n");
         else if(turn%2 == 1 && p[fromX-1][fromY-1]->color == 0) printf("����� ���Դϴ�.\n");
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
			if(check(map) == 1)
				printf("üũ\n");
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
