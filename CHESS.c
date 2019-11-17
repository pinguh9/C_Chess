#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
enum name { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, NONE };
int turn = 0;

typedef struct piece
{
   _Bool isempty;//말이 있으면 0, 없으면 1.
   enum name n;
   int color;//백이면 0, 흑이면 1, 없으면 2
   int count;//이동한 횟수
   _Bool alive;//사망이면 0, 생존이면 1
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
	 //빈 공간 초기화
	 for(int i = 2; i < 6; i++)
	 	for(int j = 0; j < 8; j++){
			p[i][j]->isempty = 1;
      p[i][j]->color = 3;
      p[i][j]->count = 0;
      p[i][j]->alive = 0;
			p[i][j]->n = NONE;
		}

   //룩 초기화
   p[0][0]->n = ROOK;
   p[0][7]->n = ROOK;
   p[7][0]->n = ROOK;
   p[7][7]->n = ROOK;
	 //나이트 초기화
   p[0][1]->n = KNIGHT;
   p[0][6]->n = KNIGHT;
   p[7][1]->n = KNIGHT;
   p[7][6]->n = KNIGHT;
	 //비숍 초기화
   p[0][2]->n = BISHOP;
   p[0][5]->n = BISHOP;
   p[7][2]->n = BISHOP;
   p[7][5]->n = BISHOP;
	 //퀸 초기화
   p[0][3]->n = QUEEN;
   p[7][3]->n = QUEEN;
	 //킹 초기화
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

               case 1: // 나이트
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
               case 4: // 퀸
                  if ((abs(x - i) == abs(y - j)) || x == i || y == j)
                     printf(" @@ ");
                  else
                     printf(" -- ");
                  break;
               case 5: // 킹
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

//폰 승급 함수
void Pawnlomotion(Piece* (*p)[8], int x, int y)
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

//이동할 때 상태 변경 함수
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

//폰 이동 함수
void pawn_move(Piece* (*p)[8], int x, int y) {
   int toX, toY;
   printf("이동할 칸 좌표:");
   scanf("%d %d", &toX, &toY);

   if (p[x][y]->color == p[toX - 1][toY - 1]->color) { //같은 편 먹기 불가
   printf("불가능한 이동입니다.\n");
   return ;
}

 if (p[x][y]->color == 0) {	//선택한 말이 백일때
   if (p[toX - 1][toY - 1]->isempty == 1) { //가려는 곳에 말이 없을 때
      if (p[x][y]->count == 0) //폰이 한번도 안 움직였을 때
         if ((x - (toX - 1) == 2 && (y - (toY - 1)) == 0) || (x - (toX - 1) == 1 && (y - (toY - 1)) == 0)) { //세로로 2칸까지 이동 가능
					  statuemove(p,x,y,toX,toY);
         }
         else printf("불가능한 이동입니다.\n");
      else { //폰이 1번 이상 움직였을 때
				if ((x - (toX - 1) == 1 && (y - (toY - 1)) == 0) ) { //1칸까지 이동 가능
					 statuemove(p,x,y,toX,toY);
				}
				else printf("불가능한 이동입니다.\n");
			}
    }
   else { //가려는 곳에 상대가 있을 때
      if ((x - (toX - 1)) == 1 && abs(y - (toY - 1)) == 1) { //대각선으로 한 칸씩만 이동 가능
         statuemove(p,x,y,toX,toY);
      }
      else printf("불가능한 이동입니다.\n");
   }
 }
 else{ //선택한 말이 흑일때
	 if (p[toX - 1][toY - 1]->isempty == 1) { //가려는 곳에 말이 없을 때
			if (p[x][y]->count == 0) //폰이 한번도 안 움직였을 때
				 if ((x - (toX - 1) == -2 && (y - (toY - 1)) == 0) || (x - (toX - 1) == -1 && (y - (toY - 1)) == 0) ) { //세로로 2칸까지 이동 가능
						statuemove(p,x,y,toX,toY);
				 }
				 else printf("불가능한 이동입니다.\n");
			else { //폰이 1번 이상 움직였을 때
				if ((x - (toX - 1) == -1 && (y - (toY - 1)) == 0) ) { //1칸까지 이동 가능
					 statuemove(p,x,y,toX,toY);
				}
				else printf("불가능한 이동입니다.\n");
						}
		}
	 else { // 가려는 곳에 상대가 있을 때
			if ((x - (toX - 1)) == -1 && abs(y - (toY - 1)) == 1) {      //대각선으로 한 칸씩만 이동 가능
				 statuemove(p,x,y,toX,toY);
			}
			else printf("불가능한 이동입니다.\n");
	 }
 }

   // 폰이 끝까지 가면 승급
   if (toX == 1 || toX == 8)
      if (p[toX - 1][toY - 1]->n == PAWN)
         Pawnlomotion(p, toX - 1, toY - 1);
}


void knight_move(Piece* (*p)[8], int x, int y) {
   int toX, toY;
   printf("이동할 칸 좌표:");
   scanf("%d %d", &toX, &toY);

   if ((toX - 1) == x && (toY - 1) == y) printf("현재 위치입니다.\n");      //현재 위치 불가능
   else if (p[x][y]->color == p[toX - 1][toY - 1]->color) printf("불가능한 이동입니다.\n");      //같은 편 먹기 불가
   else if (((abs(x - (toX - 1)) == 1) && (abs(y - (toY - 1)) == 2)) || ((abs(x - (toX - 1)) == 2) && (abs(y - (toY - 1)) == 1))) {
    statuemove(p,x,y,toX,toY);
    }
    else
      printf("불가능한 이동입니다.\n");
}



void bishop_move(Piece* (*p)[8], int x, int y) {
   int toX, toY,blockDR_X = 7, blockDR_Y = 7, blockUL_X = 0, blockUL_Y = 0, blockDL_X = 7, blockDL_Y = 7, blockUR_X = 0, blockUR_Y = 7;

      printf("이동할 칸 좌표:");
      scanf("%d %d", &toX, &toY);

			//비숍 장애물 찾기
			for(int i = x+1, j = y+1; i <= 7 && j <= 7; i++, j++) //아래 오른쪽 장애물
				if(p[i][j]->isempty == 0){
					blockDR_X = i;
					blockDR_Y = j;
					break;
					}
			for(int i = x-1, j = y-1; i >= 0 && j >= 0; i--, j--) //위 왼쪽 장애물
				if(p[i][j]->isempty == 0){
					blockUL_X = i;
					blockUL_Y = j;
					break;
					}
			for(int i = x+1, j = y-1; i <= 7 && j >= 0; i++, j--) //아래 왼쪽 장애물
				if(p[i][j]->isempty == 0){
					blockDL_X = i;
					blockDL_Y = j;//왼쪽 아래쪽 장애물
					break;
					}
			for(int i = x-1, j = y+1; i >= 0 && j <= 7; i--, j++) //위 오른쪽 장애물
				if(p[i][j]->isempty == 0){
					blockUR_X = i;
					blockUR_Y = j;
					break;
					}

      if ((toX - 1) == x && (toY - 1) == y) printf("현재 위치입니다.\n");
      else if (p[x][y]->color == p[toX - 1][toY - 1]->color) printf("불가능한 이동입니다.\n");
      else if (abs(x - (toX - 1)) != abs(y - (toY - 1))) printf("불가능한 이동입니다.\n");
			else if ((toX-1 > blockDR_X && toY-1 > blockDR_Y) || (toX-1 < blockUL_X && toY-1 < blockUL_Y) || (toX-1 > blockDL_X && toY-1 < blockDL_Y) || (toX-1 < blockUR_X && toY-1 > blockUR_Y)) printf("불가능한 이동입니다.\n");
      else
         statuemove(p,x,y,toX,toY);
   }


void rook_move(Piece* (*p)[8], int x, int y) {
   int toX, toY,blockD = 7,blockU = 0,blockR = 7,blockL = 0;

      printf("이동할 칸 좌표:");
      scanf("%d %d", &toX, &toY);

			for(int i = x+1; i <= 7; i++) // 아래쪽 장애물
				if(p[i][y]->isempty == 0){
					blockD = i;
					break;
				}
			for(int i = x-1; i >= 0; i--) // 위쪽 장애물
				if(p[i][y]->isempty == 0){
					blockU = i;
					break;
				}
			for(int i = y+1; i <= 7; i++) // 오른쪽 장애물
				if(p[x][i]->isempty == 0){
					blockR = i;
					break;
				}
			for(int i = y-1; i >= 0; i--) // 왼쪽 장애물
				if(p[x][i]->isempty == 0){
					blockL = i;
					break;
				}

      if ((toX - 1) == x && (toY - 1) == y) printf("현재 위치입니다.\n");
      else if (p[x][y]->color == p[toX - 1][toY - 1]->color) printf("불가능한 이동입니다.\n");
      else if ((abs(x - (toX - 1)) > 0 && abs(y - (toY - 1)) > 0)) printf("불가능한 이동입니다.\n");
			else if (toX-1 > blockD || toX-1 < blockU || toY-1 > blockR || toY-1 < blockL) printf("불가능한 이동입니다.\n");
      else
        statuemove(p,x,y,toX,toY);
   }


void queen_move(Piece* (*p)[8], int x, int y) {
   int toX, toY, blockDR_X = 7, blockDR_Y = 7, blockUL_X = 0, blockUL_Y = 0, blockDL_X = 7, blockDL_Y = 7, blockUR_X = 0, blockUR_Y = 7, blockD = 7, blockU = 0, blockR = 7, blockL = 0;

      printf("이동할 칸 좌표:");
      scanf("%d %d", &toX, &toY);
			//퀸 장애물 찾기(기존의 비숍과 룩과 동일)
			for(int i = x+1, j = y+1; i <= 7 && j <= 7; i++, j++) //아래 오른쪽 장애물
				if(p[i][j]->isempty == 0){
					blockDR_X = i;
					blockDR_Y = j;
					break;
					}
			for(int i = x-1, j = y-1; i >= 0 && j >= 0; i--, j--) //위 왼쪽 장애물
				if(p[i][j]->isempty == 0){
					blockUL_X = i;
					blockUL_Y = j;
					break;
					}
			for(int i = x+1, j = y-1; i <= 7 && j >= 0; i++, j--) //아래 왼쪽 장애물
				if(p[i][j]->isempty == 0){
					blockDL_X = i;
					blockDL_Y = j;
					break;
					}
			for(int i = x-1, j = y+1; i >= 0 && j <= 7; i--, j++) //위 오른쪽 장애물
				if(p[i][j]->isempty == 0){
					blockUR_X = i;
					blockUR_Y = j;
					break;
					}

			for(int i = x+1; i <= 7; i++) // 아래쪽 장애물
				if(p[i][y]->isempty == 0){
					blockD = i;
					break;
				}
			for(int i = x-1; i >= 0; i--) // 위쪽 장애물
				if(p[i][y]->isempty == 0){
					blockU = i;
					break;
				}
			for(int i = y+1; i <= 7; i++) // 오른쪽 장애물
				if(p[x][i]->isempty == 0){
					blockR = i;
					break;
				}
			for(int i = y-1; i >= 0; i--) // 왼쪽 장애물
				if(p[x][i]->isempty == 0){
					blockL = i;
					break;
				}


      if ((toX - 1) == x && (toY - 1) == y) printf("현재 위치입니다.\n");
      else if (p[x][y]->color == p[toX - 1][toY - 1]->color) printf("불가능한 이동입니다.\n");
			else if ((toX-1 > blockDR_X && toY-1 > blockDR_Y) || (toX-1 < blockUL_X && toY-1 < blockUL_Y) || (toX-1 > blockDL_X && toY-1 < blockDL_Y) || (toX-1 < blockUR_X && toY-1 > blockUR_Y)) printf("불가능한 이동입니다.");
			else if (((toX-1 > blockD) && (toY-1 == y))|| ((toX-1 < blockU) && (toY-1 == y))|| ((toY-1 > blockR) && (toX-1 == x))|| ((toY-1 < blockL) && (toX-1 == x))) printf("불가능한 이동입니다.\n");
      else if ((abs(x - (toX - 1)) == abs(y - (toY - 1))) || (abs(x - (toX - 1)) > 0 && abs(y - (toY - 1)) == 0) || (abs(x - (toX - 1)) == 0 && abs(y - (toY - 1)) > 0))
         statuemove(p,x,y,toX,toY);
      else
         printf("불가능한 이동입니다.\n");
   }


void king_move(Piece* (*p)[8], int x, int y) {
   int toX, toY;

      printf("이동할 칸 좌표:");
      scanf("%d %d", &toX, &toY);

      if ((toX - 1) == x && (toY - 1) == y) printf("현재 위치입니다.\n");
      else if (p[x][y]->color == p[toX - 1][toY - 1]->color) printf("불가능한 이동입니다.\n");
      else if (abs(x - (toX - 1)) > 1 || abs(y - (toY - 1)) > 1) printf("불가능한 이동입니다.\n");
      else
        statuemove(p,x,y,toX,toY);
   }

//체크인지 확인하는 함수
int check(Piece* (*p)[8]){
	int King_x, King_y, Knight_num = 0 ,Knight1_x, Knight1_y, Knight2_x, Knight2_y;
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			if(p[i][j]-> n == KING && p[i][j]->color == turn%2){ //킹의 위치 확인
				King_x = i;
				King_y = j;
			}
      else if(p[i][j]-> n == KNIGHT && p[i][j]->color == (turn+1)%2){ //나이트의 위치 확인
        Knight_num++;
        Knight1_x = i;
        Knight1_y = j;
      }
  if(Knight_num == 2) //나이트가 2개일 경우 두번째 나이트 위치 확인
    for(int i = Knight1_x-1; i >= 0; i--)
  	 for(int j = Knight1_y-1; j >= 0; j--)
      if(p[i][j]-> n == KNIGHT && p[i][j]->color == (turn+1)%2){
        Knight2_x = i;
        Knight2_y = j;
      }

			for(int i = King_x+1, j = King_y+1; i <= 7 && j <= 7; i++, j++)
				if(p[i][j]->isempty == 0){ //아래 오른쪽 장애물에 상대 퀸 혹은 비숏 확인
					if((p[i][j]->color == (turn+1)%2) && ((p[i][j]->n == QUEEN) || (p[i][j]->n == BISHOP))){
						return 1;
					}
					else
						break;
					}
			for(int i = King_x-1, j = King_y-1; i >= 0 && j >= 0; i--, j--) //위 왼쪽 장애물에 상대 퀸 혹은 비숏 확인
				if(p[i][j]->isempty == 0){
					if((p[i][j]->color == (turn+1)%2) && ((p[i][j]->n == QUEEN) || (p[i][j]->n == BISHOP))){
						return 1;
					}
					else
						break;
					}
			for(int i = King_x+1, j = King_y-1; i <= 7 && j >= 0; i++, j--) //아래 왼쪽 장애물에 상대 퀸 혹은 비숏 확인
				if(p[i][j]->isempty == 0){
					if((p[i][j]->color == (turn+1)%2) && ((p[i][j]->n == QUEEN) || (p[i][j]->n == BISHOP))){
						return 1;
					}
					else
						break;
					}
			for(int i = King_x-1, j = King_y+1; i >= 0 && j <= 7; i--, j++) //위 오른쪽 장애물에 상대 퀸 혹은 비숏 확인
				if(p[i][j]->isempty == 0){
					if((p[i][j]->color == (turn+1)%2) && ((p[i][j]->n == QUEEN) || (p[i][j]->n == BISHOP))){
						return 1;
					}
					else
						break;
					}
			for(int i = King_x+1; i <= 7; i++) // 아래쪽 장애물에 상대 퀸 혹은 룩 확인
				if(p[i][King_y]->isempty == 0){
					if((p[i][King_y]->color == (turn+1)%2) && ((p[i][King_y]->n == QUEEN) || (p[i][King_y]->n == ROOK))){
						return 1;
					}
					else
						break;
					}
			for(int i = King_x-1; i >= 0; i--) // 위쪽 장애물에 상대 퀸 혹은 룩 확인
				if(p[i][King_y]->isempty == 0){
					if((p[i][King_y]->color == (turn+1)%2) && ((p[i][King_y]->n == QUEEN) || (p[i][King_y]->n == ROOK))){
						return 1;
					}
					else
						break;
					}
			for(int i = King_y+1; i <= 7; i++) // 오른쪽 장애물에 상대 퀸 혹은 룩 확인
				if(p[King_x][i]->isempty == 0){
					if((p[King_x][i]->color == (turn+1)%2) && ((p[King_x][i]->n == QUEEN) || (p[King_x][i]->n == ROOK))){
						return 1;
					}
					else
						break;
					}
			for(int i = King_y-1; i >= 0; i--) // 왼쪽 장애물에 상대 퀸 혹은 룩 확인
				if(p[King_x][i]->isempty == 0){
					if((p[King_x][i]->color == (turn+1)%2) && ((p[King_x][i]->n == QUEEN) || (p[King_x][i]->n == ROOK))){
						return 1;
					}
					else
						break;
					}
      if(Knight_num == 2){ //상대 나이트가 2개일때 위치 확인 후 체크
        if(((abs(King_x - Knight1_x) == 1) && (abs(King_y - Knight1_y) == 2)) || ((abs(King_x - Knight1_x) == 2) && (abs(King_y - Knight1_y) == 1)) || ((abs(King_x - Knight2_x) == 1) && (abs(King_y - Knight2_y) == 2)) || ((abs(King_x - Knight2_x) == 2) && (abs(King_y - Knight2_y) == 1))){
          return 1;
          }
        }
      else if(Knight_num == 1){ //상대 나이트가 1개일때 위치 확인 후 체크
        if(((abs(King_x - Knight1_x) == 1) && (abs(King_y - Knight1_y) == 2)) || ((abs(King_x - Knight1_x) == 2) && (abs(King_y - Knight1_y) == 1)))
        return 1;
      }

        if(turn%2 == 0){ //백색의 턴일때 킹과 폰 위치 비교 후 체크
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
        else if((turn+1)%2 == 0){ ////흑색의 턴일때 킹과 폰 위치 비교 후 체크
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
      printf("이동할 기물 좌표:");
      scanf("%d %d", &fromX, &fromY);

      if (fromX < 1 || fromX>8 || fromY < 1 || fromY>8) printf("맵을 벗어난 좌표입니다.\n"); // 맵을 벗어나면
      else
      {
         if (p[fromX - 1][fromY - 1]->isempty == 1) printf("이동할 수 있는 기물이 없습니다..\n"); // 그 좌표에 말이 없으면 다시 입력받음
         else if(turn%2 == 0 && p[fromX-1][fromY-1]->color == 1) printf("백색의 턴입니다.\n");
         else if(turn%2 == 1 && p[fromX-1][fromY-1]->color == 0) printf("흑색의 턴입니다.\n");
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
			if(check(map) == 1)
				printf("체크\n");
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
