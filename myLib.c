#include "myLib.h"


/*
- 기능
: Gameboard 구조체에 있는 내용을 화면에 출력해주는 함수로 다음과 같은 기능을 한다.
1. 흰돌 검은돌 스코어 표시.
2. y축 숫자 표시.
3. x축 숫자 표시.
4. 가로와 세로 판을 그린다.
5. board.map에 입력되어 있는 값에 따라 돌의 모양 표시
*/
void ShowBoard(struct Gameboard *board)
{
   int i, j, k;

   // 게임 보드 상단에 스코어 표시
   printf("\t\t\t ● = %d, ○ = %d\n\t", board->score[1], board->score[2]);

   // Y축 번호 출력
   for (i = 0; i<MAPSIZE; i++)
      printf("    %d", i);
   printf("     Y축\n");

   // 가로 세로 출력
   for (i = 0; i<MAPSIZE; i++)
   {
      printf("\t  ");
      for (k = 0; k<MAPSIZE; k++)
         printf("*----");
      // X축 번호 출력
      printf("*\n\t%d |", i);
      // 구조체 map 배열의 값에 따라 다르게 출력 (0: 빈칸, 1: 흰돌, 2: 검은돌)
      for (j = 0; j<MAPSIZE; j++)
      {
         if (board->map[i][j] == 0)
            printf("    |");
         else if (board->map[i][j] == 1)
            printf(" ● |");
         else if (board->map[i][j] == 2)
            printf(" ○ |");
         else
            printf("    |");
      }
      printf("\n");
   }
   printf("\t  ");
   for (i = 0; i<MAPSIZE; i++)
      printf("*----");
   printf("*\n\tX축\n");
}

/*
- 기능
: 게임판의 크기에 맞게 Gameboard 구조체에 초기 값을 세팅
*/
void InitGame(struct Gameboard *board)
{
   // 맵의 크기에 따라 중앙 배치 기준점 설정
   int x = (MAPSIZE / 2) - 1;
   int y = MAPSIZE / 2;

   // 맵과 스코어를 초기화
   memset(board->map, 0, sizeof(board->map));
   memset(board->score, 0, sizeof(board->score));
   // 맵의 중앙에 흰돌과 검은돌을 대각선으로 배치
   board->map[x][x] = WHITE;
   board->map[y][x] = BLACK;
   board->map[x][y] = BLACK;
   board->map[y][y] = WHITE;
   // 스코어 값 설정
   board->score[1] += 2;
   board->score[2] += 2;
   board->score[0] = (MAPSIZE * MAPSIZE) - board->score[1] - board->score[2];
}

/*
- 기능
: turn 파라미터에 입력된 값에 따라 돌의 색갈을 선택하고 다음과 같은 동작을 한다.
1. 입력 값이 map의 범위를 넘지 않는지 확인.
2. 상, 하, 좌, 우, 대각선 8방향을 확인하여 주변에 돌의 유무를 확인.
3. 주변을 확인하여 ChangeStone() 함수에 적절한 파라미터 전달.

- 리턴 값
0: 입력 좌표에 돌을 놓을 수 있음
-1: 입력 좌표에 돌을 놓을 수 없음
*/
int PutStone(struct Gameboard *board, int x, int y, int turn)
{
   int i;
   int mx = 0;
   int my = 0;
   int color;
   int result = -1;
   
   // 돌 선택
	if (turn == 1)
      color = BLACK;
   	else
      color = WHITE;

   // 입력 값이 맵의 범위를 넘어가는지 확인
   	if ((x > MAPSIZE) || (y > MAPSIZE))
      return -1;

   // 상, 하, 좌, 우, 대각선 8방향을 확인하여 주변에 돌의 유무를 확인
   for (i = 0; i<8; i++)
   {
      // 확인할 좌표 설정
      mx = x + dx[i];
      my = y + dy[i];

      // -1< 좌표 값< 맵사이즈 의 범위를 넘었을 경우 처리
      if ((mx >= MAPSIZE) || (mx<0))
         continue;
      if ((my >= MAPSIZE) || (my < 0))
         continue;

      // 좌표에 돌이 있는지 또는 같은 색갈 돌이 있는지 확인
      if ((board->map[mx][my] == BLANK) || (board->map[mx][my] == color))
         continue;
      // 다른 색갈 돌이 있을 경우
      else
      {
         // ChangeStone() 함수가 에러 값을 리턴할 경우
         if ((ChangeStone(board, dx[i], dy[i], mx, my, color)) == -1)
            continue;
         // ChangeStone() 함수가 정상적으로 수행되었을 경우 좌표에 설정된 돌을 입력
         else
         {
            result += 1;
            board->map[x][y] = color;
         }
      }
   }
   // 반복문이 정상적으로 종료되면 주변에 돌이 없다는 의미이므로 오류값 -1 리턴
   return result;
}

/*
- 기능
: 입력된 좌표에 있는 돌의 색상과 입력된 방향을 검사하여 다음과 같은 동작을 한다.
1. 좌표에 있는 돌과 입력된 방향을 검사.
2. 입력된 방향 끝에 색갈이 다른 돌이 있는지 검사.
3. 다른 돌이 있으면 그 사이에 있는 돌의 색갈을 바꿈.
4. 다른 돌이 없으면 -1을 리턴

- 리턴 값
0: 정상적으로 돌을 바꿈
-1: 입력된 좌표와 입력된 방향 사이에 바꿀 수 있는 돌이 없음
*/
int ChangeStone(struct Gameboard *board, int dx, int dy, int x, int y, int color)
{
   int index = 0;
   int i = 0;

   // change_list 초기화
   memset(change_list, 0, sizeof(change_list));
   while (((x<MAPSIZE) && (x>-1)) || ((y<MAPSIZE) && (y>-1)))
   {

      {
         // 입력된 좌표와 다음칸의 돌 색갈이 같으면 좌표를 change_list 배열에 추가
         if (board->map[x][y] == board->map[x + dx][y + dy])
         {
            change_list[index][0] = x;
            change_list[index][1] = y;
            index++;
            // 좌표 값을 갱신하며 한칸씩 계속 검사
            x = x + dx;
            y = y + dy;
         }
         // 입력된 좌표와 다음칸의 돌 색갈이 다르면 입력된 좌표 돌 색갈만 바꿈
         else if (board->map[x + dx][y + dy] == color)
         {
            board->map[x][y] = color;
            break;
         }
         // 입력된 좌표 다음칸이 빈칸일 경우 에러 값 반환
         else if (board->map[x + dx][y + dy] == 0)
            return -1;
      }

   }

   // change_list 배열에 추가된 좌표의 돌 색갈을 전부 바꿔줌
   while (1)
   {
      // change_list 배열 값이 {0,0}이 아닐때까지 반복
      if ((change_list[i][0] == 0) && (change_list[i][1] == 0))
         break;
      else
      {
         board->map[change_list[i][0]][change_list[i][1]] = color;

      }
      i++;
   }

   return 0;
}

/*
- 기능
: 맵의 모든 칸을 확인하여 흰돌, 검은돌 그리고 빈칸의 갯 수를 카운트한다.
*/
void CntStone(struct Gameboard *board)
{
   int i, j;
   int w_cnt = 0;
   int b_cnt = 0;

   for (i = 0; i<MAPSIZE; i++)
   {
      for (j = 0; j<MAPSIZE; j++)
      {
         // 좌표의 값이 1이면 흰돌 갯수 +1
         if (board->map[i][j] == 1)
            w_cnt += 1;
         // 좌표의 값이 1이면 검은돌 갯수 +1
         else if (board->map[i][j] == 2)
            b_cnt += 1;
         else
            continue;

      }
   }
   // 카운트한 각 돌의 갯 수 값을 board 구조체에 입력
   board->score[WHITE] = w_cnt;
   board->score[BLACK] = b_cnt;
   board->score[BLANK] = board->score[BLANK] - w_cnt - b_cnt;
}
