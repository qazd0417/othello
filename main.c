#include "myLib.h"

int main(void)
{
   struct Gameboard board;

   int i;
   int x_data;
   int y_data;
   int turn = -1;                               // 1: BLACK, -1:WHITE

   InitGame(&board);

   while (1)
   {
      // 화면을 비우고 맵 표시
      system("cls");
      ShowBoard(&board);
	  memset(change_list, 0, sizeof(change_list));
	  
      // turn 값이 1이면 검은돌이 위치할 좌표를 받음
      if (turn == 1)
      {
        printf("BLACK ○ (x,y): ");
        scanf("%d,%d", &x_data, &y_data);
        while(getchar() != '\n');
      }
      // turn 값이 -1이면 흰돌이 위치할 좌표를 받음
      else if (turn == -1)
      {
        printf("WHITE ● (x,y): ");
        scanf("%d,%d", &x_data, &y_data);
        while(getchar() != '\n');
      }
      // 입력된 좌표에 돌을 놓을 수 있는지 검사 후 놓을 수 있으면 턴을 바꿈
      if ((PutStone(&board, x_data, y_data, turn)) != -1)
        turn *= -1;
      else
      {
        printf("Can't put the stone there\n");
        while(getchar() != '\n');
      }

      // 각 돌의 갯 수 카운트
      CntStone(&board);

      // 모든 칸이 채워졌을 경우 게임이 끝났음을 출력
      if (board.score[BLANK] == 0)
      {
        system("cls");
        printf("\n\n\t=========== No more space ===========\n\n\n");
        printf("\t              GAME OVER               \n\n\n");
        printf("\t         PLEASE PRESS ANY KEY         \n\n\n");
        printf("==========================================================\n\n\n");
        if(board.score[1] > board.score[2])
        	printf("\t    ******   WHITE WIN   ******\n");
        else if(board.score[1] == board.score[2])
        	printf("\t    ******     DROW   ******\n");
        else
    		printf("\t    ******   BLACK WIN   ******\n");
        getchar();
      }
   }
}



