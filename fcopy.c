#include<stdio.h>
#include<stdlib.h>

#define BUFSIZE 1024
int main(int argc,char **argv){

	int byteCount;
	FILE *in,*out;
	char buf[BUFSIZE];
	//파라미터의 개수 확인
	if(argc!=3){
		//write(2,"Usage : fcopy file1 file2\n",30); 동일
		fprintf(stderr,"Usage :fcopy file1 file2\n");
		return -1;
	}
	//파일오픈 , 예외처리
	//바이너리일 경우 rb
	if(in=fopen(argv[1],"r")==NULL){
		perror(argv[1]);
		return -1;
	}
	//파일오픈 , 예외처리
	//바이너리일 경우 wb? wt?
	if(out=fopen(argv[2],"w")==NULL){
		perror(argv[2]);
		return -1;
	}
	//bytecount 에 fread 에서 읽어온 수만큼 반환해준다.
	while(((bytecount = fread(buf,size(char),BUFSIZE,in))>0){
		fwrite(buf,sizeof(char),byteCount,out);
	}
	
	fclose(in);
	fclose(out);
	return 0;
}
