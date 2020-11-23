#include "myLib.h"


/*
- ���
: Gameboard ����ü�� �ִ� ������ ȭ�鿡 ������ִ� �Լ��� ������ ���� ����� �Ѵ�.
1. �� ������ ���ھ� ǥ��.
2. y�� ���� ǥ��.
3. x�� ���� ǥ��.
4. ���ο� ���� ���� �׸���.
5. board.map�� �ԷµǾ� �ִ� ���� ���� ���� ��� ǥ��
*/
void ShowBoard(struct Gameboard *board)
{
   int i, j, k;

   // ���� ���� ��ܿ� ���ھ� ǥ��
   printf("\t\t\t �� = %d, �� = %d\n\t", board->score[1], board->score[2]);

   // Y�� ��ȣ ���
   for (i = 0; i<MAPSIZE; i++)
      printf("    %d", i);
   printf("     Y��\n");

   // ���� ���� ���
   for (i = 0; i<MAPSIZE; i++)
   {
      printf("\t  ");
      for (k = 0; k<MAPSIZE; k++)
         printf("*----");
      // X�� ��ȣ ���
      printf("*\n\t%d |", i);
      // ����ü map �迭�� ���� ���� �ٸ��� ��� (0: ��ĭ, 1: ��, 2: ������)
      for (j = 0; j<MAPSIZE; j++)
      {
         if (board->map[i][j] == 0)
            printf("    |");
         else if (board->map[i][j] == 1)
            printf(" �� |");
         else if (board->map[i][j] == 2)
            printf(" �� |");
         else
            printf("    |");
      }
      printf("\n");
   }
   printf("\t  ");
   for (i = 0; i<MAPSIZE; i++)
      printf("*----");
   printf("*\n\tX��\n");
}

/*
- ���
: �������� ũ�⿡ �°� Gameboard ����ü�� �ʱ� ���� ����
*/
void InitGame(struct Gameboard *board)
{
   // ���� ũ�⿡ ���� �߾� ��ġ ������ ����
   int x = (MAPSIZE / 2) - 1;
   int y = MAPSIZE / 2;

   // �ʰ� ���ھ �ʱ�ȭ
   memset(board->map, 0, sizeof(board->map));
   memset(board->score, 0, sizeof(board->score));
   // ���� �߾ӿ� �򵹰� �������� �밢������ ��ġ
   board->map[x][x] = WHITE;
   board->map[y][x] = BLACK;
   board->map[x][y] = BLACK;
   board->map[y][y] = WHITE;
   // ���ھ� �� ����
   board->score[1] += 2;
   board->score[2] += 2;
   board->score[0] = (MAPSIZE * MAPSIZE) - board->score[1] - board->score[2];
}

/*
- ���
: turn �Ķ���Ϳ� �Էµ� ���� ���� ���� ������ �����ϰ� ������ ���� ������ �Ѵ�.
1. �Է� ���� map�� ������ ���� �ʴ��� Ȯ��.
2. ��, ��, ��, ��, �밢�� 8������ Ȯ���Ͽ� �ֺ��� ���� ������ Ȯ��.
3. �ֺ��� Ȯ���Ͽ� ChangeStone() �Լ��� ������ �Ķ���� ����.

- ���� ��
0: �Է� ��ǥ�� ���� ���� �� ����
-1: �Է� ��ǥ�� ���� ���� �� ����
*/
int PutStone(struct Gameboard *board, int x, int y, int turn)
{
   int i;
   int mx = 0;
   int my = 0;
   int color;
   int result = -1;
   
   // �� ����
	if (turn == 1)
      color = BLACK;
   	else
      color = WHITE;

   // �Է� ���� ���� ������ �Ѿ���� Ȯ��
   	if ((x > MAPSIZE) || (y > MAPSIZE))
      return -1;

   // ��, ��, ��, ��, �밢�� 8������ Ȯ���Ͽ� �ֺ��� ���� ������ Ȯ��
   for (i = 0; i<8; i++)
   {
      // Ȯ���� ��ǥ ����
      mx = x + dx[i];
      my = y + dy[i];

      // -1< ��ǥ ��< �ʻ����� �� ������ �Ѿ��� ��� ó��
      if ((mx >= MAPSIZE) || (mx<0))
         continue;
      if ((my >= MAPSIZE) || (my < 0))
         continue;

      // ��ǥ�� ���� �ִ��� �Ǵ� ���� ���� ���� �ִ��� Ȯ��
      if ((board->map[mx][my] == BLANK) || (board->map[mx][my] == color))
         continue;
      // �ٸ� ���� ���� ���� ���
      else
      {
         // ChangeStone() �Լ��� ���� ���� ������ ���
         if ((ChangeStone(board, dx[i], dy[i], mx, my, color)) == -1)
            continue;
         // ChangeStone() �Լ��� ���������� ����Ǿ��� ��� ��ǥ�� ������ ���� �Է�
         else
         {
            result += 1;
            board->map[x][y] = color;
         }
      }
   }
   // �ݺ����� ���������� ����Ǹ� �ֺ��� ���� ���ٴ� �ǹ��̹Ƿ� ������ -1 ����
   return result;
}

/*
- ���
: �Էµ� ��ǥ�� �ִ� ���� ����� �Էµ� ������ �˻��Ͽ� ������ ���� ������ �Ѵ�.
1. ��ǥ�� �ִ� ���� �Էµ� ������ �˻�.
2. �Էµ� ���� ���� ������ �ٸ� ���� �ִ��� �˻�.
3. �ٸ� ���� ������ �� ���̿� �ִ� ���� ������ �ٲ�.
4. �ٸ� ���� ������ -1�� ����

- ���� ��
0: ���������� ���� �ٲ�
-1: �Էµ� ��ǥ�� �Էµ� ���� ���̿� �ٲ� �� �ִ� ���� ����
*/
int ChangeStone(struct Gameboard *board, int dx, int dy, int x, int y, int color)
{
   int index = 0;
   int i = 0;

   // change_list �ʱ�ȭ
   memset(change_list, 0, sizeof(change_list));
   while (((x<MAPSIZE) && (x>-1)) || ((y<MAPSIZE) && (y>-1)))
   {

      {
         // �Էµ� ��ǥ�� ����ĭ�� �� ������ ������ ��ǥ�� change_list �迭�� �߰�
         if (board->map[x][y] == board->map[x + dx][y + dy])
         {
            change_list[index][0] = x;
            change_list[index][1] = y;
            index++;
            // ��ǥ ���� �����ϸ� ��ĭ�� ��� �˻�
            x = x + dx;
            y = y + dy;
         }
         // �Էµ� ��ǥ�� ����ĭ�� �� ������ �ٸ��� �Էµ� ��ǥ �� ������ �ٲ�
         else if (board->map[x + dx][y + dy] == color)
         {
            board->map[x][y] = color;
            break;
         }
         // �Էµ� ��ǥ ����ĭ�� ��ĭ�� ��� ���� �� ��ȯ
         else if (board->map[x + dx][y + dy] == 0)
            return -1;
      }

   }

   // change_list �迭�� �߰��� ��ǥ�� �� ������ ���� �ٲ���
   while (1)
   {
      // change_list �迭 ���� {0,0}�� �ƴҶ����� �ݺ�
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
- ���
: ���� ��� ĭ�� Ȯ���Ͽ� ��, ������ �׸��� ��ĭ�� �� ���� ī��Ʈ�Ѵ�.
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
         // ��ǥ�� ���� 1�̸� �� ���� +1
         if (board->map[i][j] == 1)
            w_cnt += 1;
         // ��ǥ�� ���� 1�̸� ������ ���� +1
         else if (board->map[i][j] == 2)
            b_cnt += 1;
         else
            continue;

      }
   }
   // ī��Ʈ�� �� ���� �� �� ���� board ����ü�� �Է�
   board->score[WHITE] = w_cnt;
   board->score[BLACK] = b_cnt;
   board->score[BLANK] = board->score[BLANK] - w_cnt - b_cnt;
}
