/*
20180503 beakhyun code
*/




/*
header
stdio.h 			표준입출력 헤더
sys/stat.h,sys/types.h,unistd.h 파일 입출력 위한 헤더.
unstd.h				fcntl(),open()을 위한 자료형, 상수 그리고 함수 정의
string.h			문자열 헤더
stdlib.h			malloc 사용 헤더,문자열 변환, 의사 난수 생성
*/

#include<stdio.h>
#include<sys/stat.h>		
#include<sys/types.h>				
#include<unistd.h>		
#include<fcntl.h>
#include<stdlib.h>
//#include<string.h>

/*
define

HUNDRED_MB			100MB
BUFSIZE				512B 
LOG 1				LOG 값 출력 위한 정의. 1일때만 출력이 가능
*/
#define HUNDRED_MB 104857600	
#define BUFSIZE 512		
#define LOG 1			

/*
main

argc				실행시 cmd 창에서 받는 인자의 갯수
argv[]				실행시 cmd 창에서 받는 인자의 문자열
mal 				heap 메모리에 설정하여, 동적으로 값을 저장

*/
int main(int argc,char *argv[]){

        int fp,rfp,fpbit,rfpbit,bit;
	char buf[BUFSIZE]={'\0',};
        char *mal;
		//argv[0]=실행하는 파일(cpy)  argv[1]=카피 txt      argv[2]=카피저장 txt
		//내가 원하는 인자는 3개임으로 그것이 아닐 경우에, 비정상으로 판단 종료.
		if(argc!=3){
		#if LOG == 1
                printf("HLOG0 arg가 다릅니다.");
		#endif
	return -1;	
	}

/*
open 함수에 사용되는 인자들
O_RDONLY readonly
O_WRONLY writeonly
O_RDWR read and write 

O_CREAT		해당파일이 없으면 생성합니다, 파일을 생성하게 된다면 파일의 접근 권한을 지정하기 위해 접근 권한 값을 추가해야 합니다.ex)0644
O_EXCL 		O_CREAT 를 사용했을 때, 파일이 이미 있어도, 열기가 가능하여 쓰기를 하면 이전 내용이 사라집니다.
O_TRUNC		기존 내용을 모두 삭제합니다.
O_APPEND	파일을 추가하여 쓰기가 되도록 open 후에 쓰기 포인터가 파일의 끝에 위치하게 됩니다.
O_NOCITTY	열기 대상이 터미널일 경우, 이 터미널이 플로그램의 제어 터미널로 할당하지 않습니다.
O_NONBLOCK	읽을 내용이 없을 때에는 읽을 내용이 있을 때까지 기다리지 않고 바로 복귀합니다.
O_SYNC		쓰기를 할 때, 실제 쓰기가 완료될 때 까지 기다립니다. 즉, 물리적으로 쓰기가 완료되어야 복귀하게 됩니다.
*/
      
	//파일 오픈
	//0644 = O_CREAT 로 파일이 생성되었을 경우, 권한문제를 해결하기 위해 권한 부여 위함.
	fp=open(argv[1],O_RDONLY);
	rfp= open(argv[2],O_RDWR|O_CREAT|O_APPEND|O_SYNC|\
                          S_IRWXU|S_IWGRP|S_IRUSR|S_IRGRP|S_IROTH,0644);
	#if LOG ==1
	//??...생성된 파일이 이미 있는경우 -1반환됨...이유를 모르겠습니다.. 오픈 설정문제 예상중...
	printf("HLOG1 fp=%d	rfp=%d\n",fp,rfp);
	#endif
	//복사할 파일의 길이를 구함, 100MB 를 넘어갈 경우 실행하지 않고, printf를 남김. (log x)
	bit=lseek(fp,0,SEEK_END);
	lseek(fp,0,SEEK_SET);
	if(bit>=HUNDRED_MB){
		printf("ERROR:용량이 너무 큽니다.");
	}
	else{
	//mal 변수에 동적 초기화후 그 크기만큼 파일에서 읽고 씀.
	mal=((char*)malloc(sizeof(mal)*bit));
	fpbit=read(fp,mal,bit);
	rfpbit=write(rfp,mal,bit);
	
	#if LOG == 1
	printf("HLOG2 mal=%s\n",mal);
	printf("HLOG3 fpbit=%d	,	rfbbit=%d\n",fpbit,rfpbit);
	printf("HLOG4 bit=%d\n",bit);
	#endif
	}

	//메모리 반환 및 파일 입출력 종료
	free(mal);
	close(fp);
	close(rfp);

        return 0;
}


