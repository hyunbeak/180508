/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2017.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Listing 4-3 */
/*

beakhyun 주석입니다.
long getLong(const char *arg, int flags, const char *name);
(getLong의 인자)

void errMsg(const char *format, ...){
va_list argList;
int savedErrno;

savedErrno = errno;       // In case we change it here

va_start(argList, format);
outputError(TRUE, errno, TRUE, format, argList);
va_end(argList);

errno = savedErrno;
}

void errExit(const char *format, ...){
va_list argList;//스텍에 저장됨
va_start(argList, format);//가변인수 
outputError(TRUE, errno, TRUE, format, argList);//스텍에 있는 내용이 전부 출력되도록
va_end(argList);//종료
terminate(TRUE);
}
void err_exit(const char *format, ...){
va_list argList;
va_start(argList, format);
outputError(TRUE, errno, FALSE, format, argList);
va_end(argList);

terminate(FALSE);
}
void cmdLineErr(const char *format, ...){

va_list argList;
fflush(stdout);           // Flush any pending stdout

fprintf(stderr, "Command-line usage error: ");
va_start(argList, format);
vfprintf(stderr, format, argList);
va_end(argList);
fflush(stderr);           // In case stderr is not line-buffered
exit(EXIT_FAILURE);
}

long getLong(const char *arg, int flags, const char *name){
return getNum("getLong", arg, flags, name);
}
static long getNum(const char *fname, const char *arg,
int flags, const char *name){
long res;
char *endptr;
int base;

if (arg == NULL || *arg == '\0')
gnFail(fname, "null or empty string", arg, name);
//진수 구분
base = (flags & GN_ANY_BASE) ? 0 : (flags & GN_BASE_8) ? 8 :
(flags & GN_BASE_16) ? 16 : 10;

errno = 0;//함수 호출중 에러 발생시 0이됨. 함수 에러가 발생하지 않고 완료될 경우 0이 반환되지 않고 다른 값이 반환됨
//진수로 변환해서 계산후 10진수로 변환됨.
res = strtol(arg, &endptr, base);//포인터 처음부터 끝까지 길이 반환
if (errno != 0)
gnFail(fname, "strtol() failed", arg, name);

if (*endptr != '\0')//숫자가 아닐경우
gnFail(fname, "nonnumeric characters", arg, name);
//GN_NONNEG 01
if ((flags & GN_NONNEG) && res < 0)//음수일경우
gnFail(fname, "negative value not allowed", arg, name);

if ((flags & GN_GT_0) && res <= 0)//0보다 작은경우
gnFail(fname, "value must be > 0", arg, name);

return res;
}

static void gnFail(const char *fname, const char *msg,
const char *arg, const char *name){
fprintf(stderr, "%s error", fname);
if (name != NULL)
fprintf(stderr, " (in %s)", name);
fprintf(stderr, ": %s\n", msg);
if (arg != NULL && *arg != '\0')
fprintf(stderr, "        offending text: %s\n", arg);

exit(EXIT_FAILURE);
}
void
usageErr(const char *format, ...)
{
va_list argList;

fflush(stdout);           // Flush any pending stdout 

fprintf(stderr, "Usage: ");
va_start(argList, format);
vfprintf(stderr, format, argList);
va_end(argList);

fflush(stderr);           // In case stderr is not line-buffered 
exit(EXIT_FAILURE);
}
static void
terminate(Boolean useExit3){
char *s;

// Dump core if EF_DUMPCORE environment variable is defined and
//is a nonempty string; otherwise call exit(3) or _exit(2),
//depending on the value of 'useExit3'. 

s = getenv("EF_DUMPCORE");//환경 변수 목록 중에 원하는 변수값을 구합니다.

if (s != NULL && *s != '\0')
abort();
else if (useExit3)
exit(EXIT_FAILURE);
else
_exit(EXIT_FAILURE);
}
*/
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
    size_t len;
    off_t offset;//32 bit longlong iint 64bit long int
    int fd, ap, j;
    char *buf;
    ssize_t numRead, numWritten;
	//argc가 3개이하거나 1번이 --help인경우 
    if (argc < 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s file {r<length>|R<length>|w<string>|s<offset>}...\n",
                 argv[0]);

    fd = open(argv[1], O_RDWR | O_CREAT,
                S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH);                     /* rw-rw-rw- */
    if (fd == -1)
        errExit("open");

    for (ap = 2; ap < argc; ap++) {
	//argv의 인자의 첫글자만 받아오기 위해서.
        switch (argv[ap][0]) {
        case 'r':   /* Display bytes at current offset, as text */
        case 'R':   /* Display bytes at current offset, in hex */
	
			//GN_ANY_BASE = 0100 권환으로 생각됨.(숫자 8?? 예상됨)
			
           len = getLong(&argv[ap][1], GN_ANY_BASE, argv[ap]);//길이를 반환함, if문으로 예외처리 getLong

            buf = malloc(len);//동적할당
            if (buf == NULL)//버퍼에 아무것도 없을경우 멜록선언 0
                errExit("malloc");

            numRead = read(fd, buf, len);
            if (numRead == -1)//읽을 수 없는 경우
                errExit("read");

            if (numRead == 0) {//파일의 끝인경우(공백인 경우)
                printf("%s: end-of-file\n", argv[ap]);
            } else {
                printf("%s: ", argv[ap]);
                for (j = 0; j < numRead; j++) {
                    if (argv[ap][0] == 'r')//첫글자가 r인경우
                        printf("%c", isprint((unsigned char) buf[j]) ? buf[j] : '?');//isprint:인수로 받은 문자가 인쇄 가능 문자인지를 판별합니다. isgraph()와의 차이점은 공백문자도 인쇄 가능 문자로 판별합니다.
                    else
                        printf("%02x ", (unsigned int) buf[j]);//숫자 출력
                }
                printf("\n");
            }

            free(buf);
            break;

        case 'w':   /* Write string at current offset */
            numWritten = write(fd, &argv[ap][1], strlen(&argv[ap][1]));//파일을 복사 1글자의 파일명만큼??
            if (numWritten == -1)
                errExit("write");//write라는 애러를 출력
            printf("%s: wrote %ld bytes\n", argv[ap], (long) numWritten);//파일에 쓴 길이만큼 보여줌
            break;

        case 's':   /* Change file offset */
            offset = getLong(&argv[ap][1], GN_ANY_BASE, argv[ap]);//길이반환
            if (lseek(fd, offset, SEEK_SET) == -1)//파일포인터?가 처음위치를 찾을 수 없는 경우?? 설정이 잘못되엇다., 알수없는 위치일 경우에
                errExit("lseek");
            printf("%s: seek succeeded\n", argv[ap]);//파일포인터 위치 변환 성공
            break;

        default:
            cmdLineErr("Argument must start with [rRws]: %s\n", argv[ap]);//마지막 에러를 출력
        }
    }

    if (close(fd) == -1)//종료,파일이 닫혀있다?(예외처리)
        errExit("close");

    exit(EXIT_SUCCESS);//종료
}
