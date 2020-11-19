#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 
#define BLACK 2
#define WHITE 1
#define BLANK 0
#define MAPSIZE 8

static int dx[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
static int dy[8] = {0, 0, -1, 1, -1, 1, -1, 1};
static int change_list[8][2];


struct Gameboard 
{ 
    int map[MAPSIZE][MAPSIZE]; 
    int score[3];                     // 0: empty, 1: white, 2: black 
};

void ShowBoard(struct Gameboard *board);
void InitGame(struct Gameboard *board);
void CalcStone(struct Gameboard *board, int x, int y, int turn);
void CntStone(struct Gameboard *board);
int PutStone(struct Gameboard *board, int xq, int y, int turn);
int ChangeStone(struct Gameboard *board, int dx, int dy, int x, int y, int color);



int main(void)
{
    struct Gameboard board;

    int i;
    int x_data;
    int y_data;
    int turn = -1;                               // 1: BLACK, -1:WHITE

    InitGame(&board);

    while(1)
    {
        system("cls");
        ShowBoard(&board);
        if(turn == 1)
        {
            printf("BLACK �� (x,y): ");
            scanf("%d,%d",&x_data, &y_data);
            getchar();
        }
        else if(turn == -1)
        {
            printf("WHITE �� (x,y): ");
            scanf("%d,%d",&x_data, &y_data);
            getchar();
        }
        
        if ((PutStone(&board, x_data, y_data, turn)) != -1)
        {
            printf("continue\n");
            getchar();
            turn *= -1;
        }
        else
        {
            printf("Can't put the stone there\n");
            getchar();
        }

        CntStone(&board);
        
        if(board.score[BLANK] == 0)
        {
            system("clear");
            printf("\n\n\t=========== No more space ===========\n\n\n");
            printf("\t              GAME OVER               \n\n\n");
            printf("\t         PLEASE PRESS ANY KEY         \n\n\n");
            printf("==========================================================");
            getchar();
        }
    }
}


// Gameboard ����ü�� �ִ� ������ ȭ�鿡 ������ִ� �Լ�
void ShowBoard(struct Gameboard *board) 
{
    int i, j, k;

    // ���� ���� ��ܿ� ���ھ� ǥ��
    printf("\t\t\t �� = %d, �� = %d\n\t", board->score[1], board->score[2]); 

    for(i=0; i<MAPSIZE; i++)
        printf("    %d",i);
    printf("     Y��\n");
    for(i=0; i<MAPSIZE; i++) 
    {   
        printf("\t  ");
        for(k=0; k<MAPSIZE; k++)
            printf("*----");
        printf("*\n\t%d |",i);
        for(j=0; j<MAPSIZE; j++)
        {
            if(board->map[i][j] == 0)
                printf("    |");
            else if(board->map[i][j] == 1)
                printf(" �� |");
            else if(board->map[i][j] == 2)
                printf(" �� |");
            else
                printf("    |");
        }
        printf("\n");
    } 
    printf("\t  ");
    for(i=0; i<MAPSIZE; i++)
        printf("*----");
    printf("*\n\tX��\n");
}

// �������� ũ�⿡ �°� Gameboard ����ü�� �ʱ� ���� ����
void InitGame(struct Gameboard *board)
{
    int x = (MAPSIZE / 2) - 1;
    int y = MAPSIZE / 2;

    memset(board->map, 0, sizeof(board->map));
    memset(board->score, 0, sizeof(board->score));
    board->map[x][x]=WHITE;
    board->map[y][x]=BLACK;
    board->map[x][y]=BLACK;
    board->map[y][y]=WHITE;
    board->score[1] += 2;
    board->score[2] += 2;
    board->score[0] = (MAPSIZE * MAPSIZE) - board->score[1] - board->score[2];
}

// 0: �Է� ��ǥ�� ���� ���� �� ����
// -1: �Է� ��ǥ�� ���� ���� �� ����
int PutStone(struct Gameboard *board, int x, int y, int turn)
{   
    int i;
    int mx = 0;
    int my = 0;
    int color;
    int result = -1;

    // �� ����
    if(turn == 1)
        color = BLACK;
    else
        color = WHITE;

    // �Է� ���� ���� ������ �Ѿ���� Ȯ��
    if((x > MAPSIZE) || (y > MAPSIZE))          
        return -1;

    // ��, ��, ��, ��, �밢�� 8������ Ȯ���Ͽ� �ֺ��� ���� ������ Ȯ��
    for (i=0; i<8; i++)
    {
        // Ȯ���� ��ǥ ����
        mx = x + dx[i];
        my = y + dy[i];

        // -1< ��ǥ ��< �ʻ����� �� ������ �Ѿ��� ��� ó��
        if ((mx>=MAPSIZE) || (mx<0))
            continue;
        if ((my>=MAPSIZE) || (my < 0))
            continue;

        // ��ǥ�� ���� �ִ��� �Ǵ� ���� ���� ���� �ִ��� Ȯ��
        if((board->map[mx][my] == BLANK) || (board->map[mx][my] == color))
            continue;
        else
        {   
            if((ChangeStone(board, dx[i], dy[i], mx, my, color)) == -1)
                continue;
            else
            {
                result +=1;
                board->map[x][y] = color;
            }               // 8���� �� �� ������ ���� ������ ���� 0�� ����
        }
    }
    // �ݺ����� ���������� ����Ǹ� �ֺ��� ���� ���ٴ� �ǹ��̹Ƿ� ������ -1 ����
    return result;
}

int ChangeStone(struct Gameboard *board, int dx, int dy, int x, int y, int color)
{
    int index = 0;
    int i=0;

    memset(change_list, 0, sizeof(change_list));
    while(((x<MAPSIZE) && (x>-1)) || ((y<MAPSIZE) && (y>-1)))
    {   
        
        {
            if (board->map[x][y] == board->map[x+dx][y+dy])
            {
                change_list[index][0] = x;
                change_list[index][1] = y;
                index++;
                x = x+dx;
                y = y+dy;
            }
            else if(board->map[x+dx][y+dy] == color)
            {
                board->map[x][y] = color;
                break;
            }
            else if(board->map[x+dx][y+dy] == 0)
                return -1;
        }
        
    }

    while(1)
    {   
        if( (change_list[i][0]==0) && (change_list[i][1]==0) )
            break;
        else
            {
                board->map[change_list[i][0]][change_list[i][1]] = color;

            }
        i++;
    }

    return 0;
}

void CntStone(struct Gameboard *board)
{
    int i,j;
    int w_cnt = 0;
    int b_cnt = 0;

    for (i=0; i<MAPSIZE; i++)
        {
            for (j=0; j<MAPSIZE; j++)
                {
                    if(board->map[i][j] == 1)
                        w_cnt += 1;
                    else if(board->map[i][j] == 2)
                        b_cnt += 1;
                    else
                        continue;
                    
                }
        }
    board->score[WHITE] = w_cnt;
    board->score[BLACK] = b_cnt;
    board->score[BLANK] = board->score[BLANK] - w_cnt - b_cnt;
}
