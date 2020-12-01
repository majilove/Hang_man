#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>

#define clear system("clear")
#define COLOR_RED "\x1b[31m"
#define COLOR_RESET "\x1b[0m"

#define UP 65
#define DOWN 66
#define ENTER 10

int getkey(int is_echo, int timeout);   //키 입력함수
int getch(void);    //키 입력함수
// void ClearReadBuffer(void); //\n을 만날 때까지 문자를 읽어 들이는 함수 

int Intro(void);                                                    //초기화면
void Lean(void);                                                    //인트로 2
void Voca_List(char (*word)[15]);                                   //단어 목록
void Draw_Man(int *pchance);                                                    //행맨 그리기
int Fill_Word(char (*word)[15]);                                    //단어 맞추기(게임)
/////////////////////////////////////////////////
int main(void)
{
    int pick;       //메인메뉴에서 고르기
    char word[10][15]={"clean", "destory", "bottle", "cheese", "future", "honey", "shelf", "refrigerator", "computer", "homework"};
    int result=3;     //게임오버, 클리어 저장 (조건 범위 밖의 임시값)

    while(1)
    {
        pick=Intro();
        if(pick==0) 
        {
            result= Fill_Word(word);    //게임시작
        }
        else if(pick==1) Voca_List(word);   //단어목록
        else if(pick==2) break; //종료
        
        if(result==0) 
        {
            printf("\n\n::GAME CLEAR::\n");
            result=3;
        }
        else if(result ==1)
        {
            printf("\n\n::GAME OVER::\n");
            result=3;
        }
        getchar();
    }
   
    return 0;
}
////////////////////////////////////////////////
int getch(void){
   int num1=0, num2=0, num3=0;
   int result=0;

   num1=getkey(0, 0);
   if(num1==27){
      num2=getkey(0, 1);
      num3=getkey(0, 1);
   }

   if(num1==27&&num2==-1){
      result=27;
   }else if(num2==91){
      return num3;
   }else{
      result=num1;
   }

   return result;
}

int getkey(int is_echo, int timeout){
   int ch;
   struct termios old;
   struct termios current;

   tcgetattr(0 , &old);
   current = old;
   current.c_lflag &= ~ICANON;

   if(is_echo){
      current.c_lflag |= ECHO;
   }else{
      current.c_lflag &= ~ECHO;
   }
   current.c_cc[VMIN]=(!timeout);
   current.c_cc[VTIME]=1;

   tcsetattr(0 , TCSANOW, &current);
   ch = getchar();
   tcsetattr(0 , TCSANOW, &old);

   return ch;
}

/* void ClearReadBuffer(void)  //\n을 만날 때까지 문자를 읽어 들이는 함수 
{
  while (getchar() != '\n');
} */

int Intro(void)                                                    //초기화면
{
    int move;   //방향키 받기
    int pick=0; 

    while(1)
    {
        clear;
        Lean();
        printf("                               ┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
        switch(pick)
        {
            case 0:
                printf("                                      ▼ GAME START ▼\n");
                printf("                                        VOCA  LIST\n");
                printf("                                           EXIT\n");
                break;
            case 1:
                printf("                                        GAME START\n");
                printf("                                      ▼ VOCA  LIST ▼\n");
                printf("                                           EXIT\n");
                break;
            case 2:
                printf("                                        GAME START\n");
                printf("                                        VOCA  LIST\n");
                printf("                                      ▼    EXIT    ▼\n");
                break;
        }
        printf("                               ┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
        printf("                                   방향키로 커서 이동\n");

        move=getch();

        switch(move)
        {
            case UP:
                if(pick>0) pick--;
                break;
            case DOWN:
                if(pick<2) pick++;
                break;
            case ENTER:
                if(pick==0) return 0;
                else if(pick==1) return 1;
                else return 2;
        }
    }//while
}

void Lean(void)                                                    //인트로 2
{
    printf("\n\n\n");
    printf("##     ##     #####     ###    ##      #######          ##      ##      #####      ###    ##\n");
    printf("##     ##    ##   ##    ####   ##     ##                ####  ####     ##   ##     ####   ##\n");
    printf("#########   ##     ##   ## ##  ##    ###                ##  ##  ##    ##     ##    ## ##  ##\n");
    printf("#########   #########   ##  ## ##    ###  ####          ##  ##  ##    #########    ##  ## ##\n");
    printf("##     ##   ##     ##   ##   ####     ##   ##           ##      ##    ##     ##    ##   ####\n");
    printf("##     ##   ##     ##   ##    ###      ######           ##      ##    ##     ##    ##    ###\n\n");
}

void Voca_List(char (*word)[15])                                      //단어 목록
{   
    printf("▼Voca List▼\n\n");
    for(int i=0; i<10; i++)
    {
        printf("%s \n\n", word[i]);
    }
}
void Draw_Man(int *pchance)                                                    //행맨 그리기
{
    int hang[15][20]={
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    
    switch(*pchance)
    {
        case 15:
            break;
        case 14:
            hang[12][14]=2, hang[12][15]=2, hang[12][16]=2;
            break;
        case 13:
            hang[12][14]=2, hang[12][15]=2, hang[12][16]=2;
            hang[11][15]=3, hang[10][15]=3, hang[9][15]=3;
            break;
        case 12:
            hang[12][14]=2, hang[12][15]=2, hang[12][16]=2;
            hang[11][15]=3, hang[10][15]=3, hang[9][15]=3;
            hang[8][15]=3, hang[7][15]=3, hang[6][15]=3;
            break;
        case 11:
            hang[12][14]=2, hang[12][15]=2, hang[12][16]=2;
            hang[11][15]=3, hang[10][15]=3, hang[9][15]=3;
            hang[8][15]=3, hang[7][15]=3, hang[6][15]=3;
            hang[5][15]=3, hang[4][15]=3, hang[3][15]=3;
            break;
        case 10:
            hang[12][14]=2, hang[12][15]=2, hang[12][16]=2;
            hang[11][15]=3, hang[10][15]=3, hang[9][15]=3;
            hang[8][15]=3, hang[7][15]=3, hang[6][15]=3;
            hang[5][15]=3, hang[4][15]=3, hang[3][15]=3;
            hang[2][15]=2, hang[2][14]=2, hang[2][13]=2;
            break;
        case 9:
            hang[12][14]=2, hang[12][15]=2, hang[12][16]=2;
            hang[11][15]=3, hang[10][15]=3, hang[9][15]=3;
            hang[8][15]=3, hang[7][15]=3, hang[6][15]=3;
            hang[5][15]=3, hang[4][15]=3, hang[3][15]=3;
            hang[2][15]=2, hang[2][14]=2, hang[2][13]=2;
            hang[2][12]=2, hang[2][11]=2, hang[2][10]=2;
            break;
        case 8:
            hang[12][14]=2, hang[12][15]=2, hang[12][16]=2;
            hang[11][15]=3, hang[10][15]=3, hang[9][15]=3;
            hang[8][15]=3, hang[7][15]=3, hang[6][15]=3;
            hang[5][15]=3, hang[4][15]=3, hang[3][15]=3;
            hang[2][15]=2, hang[2][14]=2, hang[2][13]=2;
            hang[2][12]=2, hang[2][11]=2, hang[2][10]=2;
            hang[3][10]=4;
            break;
        case 7:
            hang[12][14]=2, hang[12][15]=2, hang[12][16]=2;
            hang[11][15]=3, hang[10][15]=3, hang[9][15]=3;
            hang[8][15]=3, hang[7][15]=3, hang[6][15]=3;
            hang[5][15]=3, hang[4][15]=3, hang[3][15]=3;       
            hang[2][15]=2, hang[2][14]=2, hang[2][13]=2;
            hang[2][12]=2, hang[2][11]=2, hang[2][10]=2;
            hang[3][10]=4;
            hang[4][10]=5, hang[5][9]=5;
            break;
        case 6:
            hang[12][14]=2, hang[12][15]=2, hang[12][16]=2;
            hang[11][15]=3, hang[10][15]=3, hang[9][15]=3;
            hang[8][15]=3, hang[7][15]=3, hang[6][15]=3;
            hang[5][15]=3, hang[4][15]=3, hang[3][15]=3;
            hang[2][15]=2, hang[2][14]=2, hang[2][13]=2;
            hang[2][12]=2, hang[2][11]=2, hang[2][10]=2;
            hang[3][10]=4;
            hang[4][10]=5, hang[5][9]=5;
            hang[5][11]=5, hang[6][10]=5;
            break;
        case 5:
            hang[12][14]=2, hang[12][15]=2, hang[12][16]=2;
            hang[11][15]=3, hang[10][15]=3, hang[9][15]=3;
            hang[8][15]=3, hang[7][15]=3, hang[6][15]=3;
            hang[5][15]=3, hang[4][15]=3, hang[3][15]=3;
            hang[2][15]=2, hang[2][14]=2, hang[2][13]=2;
            hang[2][12]=2, hang[2][11]=2, hang[2][10]=2;
            hang[3][10]=4;
            hang[4][10]=5, hang[5][9]=5;
            hang[5][11]=5, hang[6][10]=5;
            hang[7][10]=5, hang[8][10]=5;
            break;
        case 4:
            hang[12][14]=2, hang[12][15]=2, hang[12][16]=2;
            hang[11][15]=3, hang[10][15]=3, hang[9][15]=3;
            hang[8][15]=3, hang[7][15]=3, hang[6][15]=3;
            hang[5][15]=3, hang[4][15]=3, hang[3][15]=3;
            hang[2][15]=2, hang[2][14]=2, hang[2][13]=2;
            hang[2][12]=2, hang[2][11]=2, hang[2][10]=2;
            hang[3][10]=4;
            hang[4][10]=5, hang[5][9]=5;
            hang[5][11]=5, hang[6][10]=5;
            hang[7][10]=5, hang[8][10]=5;
            hang[8][9]=5;
            break;
        case 3:
            hang[12][14]=2, hang[12][15]=2, hang[12][16]=2;
            hang[11][15]=3, hang[10][15]=3, hang[9][15]=3;
            hang[8][15]=3, hang[7][15]=3, hang[6][15]=3;
            hang[5][15]=3, hang[4][15]=3, hang[3][15]=3;
            hang[2][15]=2, hang[2][14]=2, hang[2][13]=2;
            hang[2][12]=2, hang[2][11]=2, hang[2][10]=2;
            hang[3][10]=4;
            hang[4][10]=5, hang[5][9]=5;
            hang[5][11]=5, hang[6][10]=5;
            hang[7][10]=5, hang[8][10]=5;
            hang[8][9]=5;
            hang[8][11]=5;
            break;
        case 2:
            hang[12][14]=2, hang[12][15]=2, hang[12][16]=2;
            hang[11][15]=3, hang[10][15]=3, hang[9][15]=3;
            hang[8][15]=3, hang[7][15]=3, hang[6][15]=3;
            hang[5][15]=3, hang[4][15]=3, hang[3][15]=3;
            hang[2][15]=2, hang[2][14]=2, hang[2][13]=2;
            hang[2][12]=2, hang[2][11]=2, hang[2][10]=2;
            hang[3][10]=4;
            hang[4][10]=5, hang[5][9]=5;
            hang[5][11]=5, hang[6][10]=5;
            hang[7][10]=5, hang[8][10]=5;
            hang[8][9]=5;
            hang[8][11]=5;
            hang[9][10]=5, hang[10][10]=5;

            break;
        case 1:
            hang[12][14]=2, hang[12][15]=2, hang[12][16]=2;
            hang[11][15]=3, hang[10][15]=3, hang[9][15]=3;
            hang[8][15]=3, hang[7][15]=3, hang[6][15]=3;
            hang[5][15]=3, hang[4][15]=3, hang[3][15]=3;
            hang[2][15]=2, hang[2][14]=2, hang[2][13]=2;
            hang[2][12]=2, hang[2][11]=2, hang[2][10]=2;
            hang[3][10]=4;
            hang[4][10]=5, hang[5][9]=5;
            hang[5][11]=5, hang[6][10]=5;
            hang[7][10]=5, hang[8][10]=5;
            hang[8][9]=5;
            hang[8][11]=5;
            hang[9][10]=5, hang[10][10]=5;
            hang[11][9]=5, hang[12][9]=5;
            break;
        case 0:
            hang[12][14]=2, hang[12][15]=2, hang[12][16]=2;
            hang[11][15]=3, hang[10][15]=3, hang[9][15]=3;
            hang[8][15]=3, hang[7][15]=3, hang[6][15]=3;
            hang[5][15]=3, hang[4][15]=3, hang[3][15]=3;
            hang[2][15]=2, hang[2][14]=2, hang[2][13]=2;
            hang[2][12]=2, hang[2][11]=2, hang[2][10]=2;
            hang[3][10]=4;
            hang[4][10]=5, hang[5][9]=5;
            hang[5][11]=5, hang[6][10]=5;
            hang[7][10]=5, hang[8][10]=5;
            hang[8][9]=5;
            hang[8][11]=5;
            hang[9][10]=5, hang[10][10]=5;
            hang[11][9]=5, hang[12][9]=5;
            hang[11][11]=5, hang[12][11]=5;
            break;
    }

    for(int i=0; i<15; i++)
    {
        for(int j=0; j<20; j++)
        {
            if(hang[i][j]==1) printf("▣");
            else if(hang[i][j]==0) printf(" ");
            else if(hang[i][j]==2) printf("─");
            else if(hang[i][j]==3) printf("│");
            else if(hang[i][j]==4) printf("§");
            else if(hang[i][j]==5) printf("●");
        }
        printf("\n");
    }
}

int Fill_Word(char(*word)[15])                                                   //단어 맞추기(게임)
{
    srand(time(NULL));  //정답 단어 선정

    int pick;                               //단어장에서 pick번째 배열의 단어 선정
    int len;                                //정답 단어 길이 재기
    char input;                              //알파벳 입력받기
    char input2[3];
    char answer[15];                        //정답 하나 랜덤으로 받을 공간
    char temp[15]={"______________"};       //빈 칸 14개 (언더바로 채우기, 마지막은 \0) 출력할 때 ("%c ", temp[i])
    char wrong[15]={" "};                         //기회만큼.
    int chance=15;                           //기회 15회
    int check;                              //틀렸는지 체크
    int i=0, j=0;                           //반복제어변수

    pick= rand()%10;                        //정답 단어 선정(0~9)
    strcpy(answer, word[pick]);             //정답 단어 선정
    len= strlen(answer);                    //정답 단어의 문자 길이 측정 및 저장
    temp[len]= '\0';                        //정답 단어 문자 길이에 맞춰서 '널' 문자 삽입

    while(chance>=0)
    {   
        clear;
        check=0;                            //틀렸는지 여부 확인하는 변수 초기화.
        Draw_Man(&chance);

        for(int i=0; i<len; i++)
        {
            printf("%c ", temp[i]);             //빈 칸( 스펠링 갯수) 출력
        }
        printf("\n\n");
        if( strcmp(temp, answer) ==0) return 0;        //정답 맞췄으면 탈출

        printf("현재 남은 기회: ");
        printf(COLOR_RED"%d \n\n"COLOR_RESET, chance);

        printf("틀린 문자: ");
        printf(COLOR_RED"%s "COLOR_RESET, wrong);

        printf("\n▶ ");
        if( scanf("%c", &input) !=1) continue;                    //문자 입력

        for(i=0; i<len; i++)                //문자 비교(문자열이 아니라 문자이므로 string.h 함수 안 쓴다!)
        {
            if(input== answer[i])               //입력한 하나의 알파벳과, 정답단어의 문자열전체 같은 게 있는지 검사
            {
                temp[i]= answer[i];             //있으면 temp 빈 칸에 채워넣기
                check=1;                        //정답 맞추면 체크 변수 증가
            }
        }
        if(check==0)                            //체크변수 변화 x(입력한 알파벳이 정답 단어 내에 존재하지 않았음)
            {
                wrong[j]= temp[i];             //틀린 문자 옮겨닮기
                chance--;                      //기회 감소
                j++;

                input2[0]=input;
                //input2[1]=' ';
                strcat(wrong, input2);
            }
        getchar();
    }//while
    return 1;   //게임오버
}