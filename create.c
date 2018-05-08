/*
	stdin  = fd=>0
	stdout = fd=>1
	stderr = fd=>2
	open fd = 3
	blocking
	non-blocking
	
	ch 1 < 궁금한사람만
	ch 2 정적 라이브러리(.so) 공유 라이브러리(.a) 아직 안함 읽어보기.
	ch 3 퀴즈가 자주....ㅠㅠㅠ
	
	 
	
*/
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

#define BUFSIZE 50
int main(void){
	int fd;
	char temp[50],rbuf[50],rbuf2[50],tempr[100];
	int wcount,rcount;
	//파일 오픈. 속성 내용 참조필요.
	fd= open("./test.txt",O_RDWR|O_CREAT|O_TRUNC,\
			  S_IRWXU|S_IWGRP|S_IRUSR|S_IRGRP|S_IROTH);

	if(fd==-1){
		printf("file open error!!\n");
		return -1;
	}
	
	//sprintf(temp,"beakhyuntest\n");//string에서 변수 넣는것처럼 하는 함수
	sprintf(temp,"Do not count the before they hatch\n");
	//write(1,temp,strlen(temp));//1=stdout

	//write
	wcount=write(fd,temp,strlen(temp));//오픈으로 fd변수에 저장한곳에 씀,비트수 반환
	printf("fd=%d\n wcnt=%d\n",fd,wcount);
	
	//close(fd);	
	//fd=open("./test.txt",O_RDONLY);
	//rcount=lseek(fd,0,SEEK_SET);// 위 두줄 주석 대신 사용. 
	rcount=lseek(fd,0,SEEK_SET);// 위 두줄 주석 대신 사용. 

	//lseek(fd,offset,SEEK_END);//코드 끝으로
	//lseek(fd,offset,SEEK_CUR);//10바이트 앞으로

	//read
	//rcount=read(fd,rbuf,BUFSIZE);//반환값 비트수
	rcount=read(fd,rbuf,16);//반환값 비트수
	rbuf[rcount]='\0';
	strcat(rbuf," eggs");
	strcpy(tempr,rbuf);
	strcpy(rbuf,rbuf2);
	//printf("%s",tempr);
	rcount=lseek(fd,16,SEEK_SET);
	rcount=read(fd,rbuf2,BUFSIZE);
	//memset(0,' ',BUFSIZE);
	strcat(tempr,rbuf2);
	printf("rcount=%d\n",rcount);
	printf("%s\n",tempr);
	
	
	//file close
	close(fd);
	/*
	fd = creat("./test2.txt",0764);

	if(fd==-1){
		printf("file creat error!!\n");
		return -1;
	}
	*/
	return 0;
}

