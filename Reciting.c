/*
"But his delight is in the law of the LORD; and in his law doth he meditate day and night." Psalm 1:2

The purpose of the program is to help Christians to recite the Scripture well.

*/
#define Max 500
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void reciting();
void initialpage();
int firstpage();
void create();
void delete();
void update();
void each();
void ranVerse();
void hint(char str[] , char tf []) ; 

int main() {
    int in;
    initialpage();
	while(1){
        in = firstpage();

        if(in == 1)
            reciting();
        else if(in == 2)
            create();
        else if(in == 3)
            delete();
        else if(in == 4)
            update();
        else if(in == 5)
            each();
	    else if(in == 6)
	        ranVerse(); 
        else if(in == 7)
            break;
        
        else
            printf("잘못된 입력입니다. 다시 입력하세요 \n\n");
        
    }
	return 0;
}

void initialpage(){
    printf("-----------------------------------------------------------\n\n");
    printf("         복 있는 사람은 악인들의 꾀를 따르지 아니하며          \n");
    printf("                죄인들의 길에 서지 아니하며                \n");
    printf("             오만한 자들의 자리에 앉지 아니하고              \n");
    printf("              오직 여호와의 율법을 즐거워하여                \n");
    printf("              그의 율법을 주야로 묵상하는도다                \n\n");
    printf("                     시편 1편 1절                       \n");
    printf("-----------------------------------------------------------\n\n");
    printf("말씀 암송 프로그램입니다.\n\n");

}
int firstpage(){//처음 페이지로 메뉴 고르고 그 값을 반환까지 함. 
    int in;

    printf("1. 암송 프로그램\n");
    printf("2. 암송 텍스트 만들기\n");
    printf("3. 암송 텍스트 삭제\n");
    printf("4. 암송 텍스트 업데이트\n");
    printf("5. 오늘의 말씀\n\n");
    //printf("6. 말씀 뽑기\n");
    printf("7. 종료\n\n원하는 번호를 입력하세요. >>");

    scanf("%d", &in);
    return in;
}



void reciting(){
    ///책선택
    FILE *book;
    book = fopen("booklist.txt", "r");
    int bi=0;
    char books[66][20], thebook[20];
	printf("책 선택: \n");
    while(!feof(book)){
        fscanf(book, "%s", books[bi]);
        printf("%d. %s\n", bi+1, books[bi]);
        bi++;
    }
    fclose(book);
    scanf("%d", &bi);
    strcpy(thebook, books[bi-1]);
    strcat(thebook, ".txt");

    //printf("%s", thebook);

	//\

    int chap, vers, mode;
	printf("장 선택:");
	scanf("%d", &chap);
	printf("절 선택:");
	scanf("%d", &vers);
	
	printf("\n\n1. 따라쓰기\n2. 암송\n");
	scanf("%d", &mode);
	printf("도움말이 필요하면 ?를 입력하세요\n");
	getchar();
	printf("\n\n\n");
	

	char* a, * t, * t1;
	a = (char*)malloc(Max);
	t = (char*)malloc(Max);
	t1 = (char*)malloc(Max);
	int v, i;
	sprintf(a, "%d", chap);
	strcat(a, "장\n");
	printf("%s", a);
	FILE* f;
	f = fopen(thebook, "r");


	//searching wanted position
	while (!feof(f)) {//searching chapter
		fgets(t, Max, f);
		if (strlen(t) < 30)//pass if it is contents of verse
			if (strncmp(t, a, 4) == 0)
				break;
        //printf("%s", t);
	}
	//printf("%s", t);
	while (!feof(f)) {
		fscanf(f, "%d. ", &v);
        //printf("%d %d\n", v, vers);
		fgets(a, Max, f);
        //printf("%s", a);
		if (v == vers)
			break;
        
	}
	
	if (vers != v && strcmp(t, "\n") != 0 && vers != -1) {//if file ends without wanted result, finish the pg with error message
		printf("해당 구절을 찾을 수 없습니다. \n\n");
		return;
	}//end searching
    
	goto b2;

	while (!feof(f)) {
		fgets(t, Max, f);
		if (strcmp(t, "\n") == 0) {//단락 구분인 경우
			printf("\n");
			continue;
		}
		else if (strlen(t) < 30 && strstr(t, "장")) {//장이 넘어가는 경우
			v = 1;
			printf("\n\n%s\n", t);
			continue;
		}
		sscanf(t, "%d. %s", &v, t1);
		for (; t[0] != ' '; t++);//removing verse tag from t
		strcpy(a, ++t);
	b2:
		i = 0;
		printf("%d. ", v);
		if (mode == 1)
			printf("%s%d. ", a, v);//따라쓰기 틀
	b3://when * is input
		fgets(t, Max, stdin);
		if (strstr(t, "*")) {
			i -= 10;
			if (strstr(t, " *"))
				strcpy(strstr(t, " *"), " ");//기존 * 자리
			else
				strcpy(strstr(t, "*"), " ");

			if (i == -10)
				strcpy(t1, t);
			else
				strcat(t1, t);
			goto b3;
		}
		if (i < 0) {
			strcat(t1, t);
			strcpy(t, t1);
		}
		if (strcmp(t, "/\n") == 0) //jump to next verse
			continue;
		else if (strcmp(t, "+\n") == 0) {//show the contents of verse
			printf("%d. %s", v, a);
			goto b2;
		}
		else if (strcmp(t, ">\n") == 0) {//show the contents of verse
			hint(a, thebook);
			goto b2;
		}
		else if (strcmp(t, "?\n") == 0) {//jump to next verse
			printf("\n* 이어서 입력\n> 힌트\n+ 정답공개\n/ 다음 절로 이동\n] 다음 단락으로 이동\n? 도움말\n- 종료\n\n");
			
		}
		else if (strcmp(t, "]\n") == 0) //jump to next paragraph
			while (!feof(f)) {
				fgets(t, Max, f);
				if (strcmp(t, "\n") == 0)
					break;
			}
		if (strcmp(t, "-\n") == 0) //jump to next verse
			break; //변환됨.
		else if (strcmp(t, a) != 0)//t is input value, and a is net contents of verse
			goto b2;
	}
	fclose(f);
}


void create(){
	
	char ct[60] ; 
	printf("새롭게 만들고 싶은 책을 알려주세요. ");
	scanf("%s",ct);
	FILE* fp ; 
	fp = fopen("booklist.txt","a");
	fprintf(fp,"\n%s",ct);
	fclose(fp) ; 
	FILE* nc ; 
	strcat(ct,".txt");
	nc = fopen(ct,"w");
	char vs[Max] ; 
	printf("책의 내용을 장과 절 별로 입력해주세요.\n양식은 기존의 파일의 양식에 맞춰서 써 주세요.\n내용을 다 입력하셨다면 0번 을 눌러서 종료해주세요.\n종료: 0 \n");
	scanf(" %[^\n]",vs);
	
	while(!(strcmp(vs,"0")==0)){
		fprintf(nc,"%s",vs);
		fprintf(nc,"\n");
		while(getchar() != '\n');
		scanf(" %[^\n]",vs);
	}
	fclose(nc);
	printf("생성되었습니다.\n\n");
}

void delete(){
	FILE* fp, *f ; 
    int i=0, k=0, nu;
	char chap[66][128] ; 

	char ucd[50];
	char cd[50] ; 
	fp=fopen("booklist.txt","r");
    printf("현재 저장되어 있는 책들: \n");
	while (!feof(fp) ) {
		fgets( chap[i] , 128, fp);
		if(strcmp(chap[i], "\n")==0)
			continue;
		printf("%d. %s",i+1, chap[i]);
        i++;
	}
    fclose(fp);
	printf("\n\n삭제하고싶은 책의 번호를 입력해주세요. 취소하고자 한다면 범위 밖의 값을 입력하세요\n");
	scanf("%d", &nu);		

	f = fopen("booklist.txt", "w");
    while(k<i){
        if(k!=nu-1)
            fprintf(f, "%s", chap[k]);
        k++;
    }
    fclose(f);
    printf("삭제 완료\n\n");
	
}

void update(){

	FILE* chl ;
	char ch[60] ; 
	chl=fopen("booklist.txt","r");
	while (!feof(chl) ) {
		fgets( ch , 128, chl);
		if(strcmp(ch, "\n")!=0)
			printf("%s",ch);
	}
	fclose(chl) ; 
	char uch [60] ;
	printf("\n\n수정하고싶은 책을 말해주세요. ");
	scanf("%s",uch) ; 
	strcat(uch,".txt");

	FILE* ucf ; 
	ucf = fopen(uch,"w");
	char ubv[128] ; 

	printf("수정하고자 하는 책의 내용을 장과 절 별로 입력해주세요.\n양식은 기존의 파일의 양식에 맞춰서 써 주세요.\n내용을 다 입력하셨다면 0번 을 눌러서 종료해주세요.\n종료: 0 \n");
	scanf(" %[^\n]",ubv);
	while(!(strcmp(ubv,"0")==0)){
		fprintf(ucf,"%s",ubv);
		fprintf(ucf,"\n");
		while(getchar() != '\n');
		scanf(" %[^\n]",ubv);
	}

	fclose(ucf);
	printf("수정되었습니다.\n");
}


void hint(char str[] /* 구절 */ , char tf [] /*텍스트 파일 이름*/){
	int hn ; //원하는 힌트 번호
	if(strcmp(tf,"dayBibleVerse.txt")==0){
        printf("어떤 힌트를 원하시나요?\n1. 첫글자 힌트\n2. 글자 수 힌트\n3. 챕터 힌트\n0. 취소\n ");
	    scanf("%d",&hn);
		if( hn == 1 ){
			printf("%c",str[3]);
		}
		if( hn == 2 ){
			printf("%lu글자입니다. \n\n",strlen(str));
		}
		if( hn == 3 ){
			while(1){ // str의 글자 하나씩 검사
				int n = 0 ;
				if(str[n] != '('){ // '('가 아니라면 continue 
					continue ; 
				}
				if(str[n] == ')'){ // '('가 나오면 
					while(str[n] != ')'){ // ')'가 나오기 전까지 프린트
						printf("%c",str[n]);
					}
				}
				break ; 
			}
		}
	}
	else if(strcmp(tf,"dayBibleVerse.txt")!=0){
		printf("첫 글자: %c%c%c\n",str[0], str[1], str[2]);
	}
}


void ranVerse(){
	
	FILE* ch ;
	ch = fopen("booklist.txt","r");
	char cp[66][30] ; 
	int l1 =0; 
    
	while (!feof(ch)) {
        fgets(cp[l1], 30, ch);
        if(cp[l1][strlen(cp[l1])-1] == '\n')
            cp[l1][strlen(cp[l1])-1] ='\0';
        if(strlen(cp[l1]) <= 1)
            continue;
        l1++;
    }
    l1--;
	srand(time(0)); 
	int rcp = rand()%l1;

	char rcap[35] ; 
	strcpy(rcap,cp[rcp]);
	strcat(rcap,".txt");
	fclose(ch);

    FILE* fp ; 

	int line=0;
	char v[Max];

	fp=fopen(rcap,"r");
    
    if (fp == NULL) {
        printf("Failed to open the file %s.\n", rcap);
        return; // or handle the error appropriately
    }
    
	while (!feof(fp)) {
        fgets(v, Max, fp);
        line++;
    }

	srand(time(0)); 
	int rn = rand()%line; 

	int t ;
    char  dv[Max] ; 
	
	while(!feof(fp)){
		fscanf(fp,"%d. ",&t); 
        fgets(dv, Max, fp);
		
		if( t== rn){
			break ; 
		}
	}
	fclose(fp);
	printf("%s\n",dv);
}


void each() {
    FILE* fp;
    fp = fopen("dayBibleVerse.txt", "r"); // Open the file in "r" mode for reading

    time_t x1;
    struct tm* p;
    x1 = time(NULL);
    p = localtime(&x1); // Get the current time

    int* t = malloc(sizeof(int)); // Allocate memory for t
    char dv[Max];

    while (!feof(fp)) {
        fscanf(fp, "%d. ", t); // Read an integer from the file into t
        fgets(dv, Max, fp);
        if (*t == p->tm_mday) { // Compare the read value with the current day
            break;
        }
    }
    free(t); // Free the allocated memory
    fclose(fp); // Close the file
    printf("%s\n\n", dv); // Print the verse
}
