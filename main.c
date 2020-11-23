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
      // ȭ���� ���� �� ǥ��
      system("cls");
      ShowBoard(&board);
	  memset(change_list, 0, sizeof(change_list));
	  
      // turn ���� 1�̸� �������� ��ġ�� ��ǥ�� ����
      if (turn == 1)
      {
        printf("BLACK �� (x,y): ");
        scanf("%d,%d", &x_data, &y_data);
        while(getchar() != '\n');
      }
      // turn ���� -1�̸� ���� ��ġ�� ��ǥ�� ����
      else if (turn == -1)
      {
        printf("WHITE �� (x,y): ");
        scanf("%d,%d", &x_data, &y_data);
        while(getchar() != '\n');
      }
      // �Էµ� ��ǥ�� ���� ���� �� �ִ��� �˻� �� ���� �� ������ ���� �ٲ�
      if ((PutStone(&board, x_data, y_data, turn)) != -1)
        turn *= -1;
      else
      {
        printf("Can't put the stone there\n");
        while(getchar() != '\n');
      }

      // �� ���� �� �� ī��Ʈ
      CntStone(&board);

      // ��� ĭ�� ä������ ��� ������ �������� ���
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



