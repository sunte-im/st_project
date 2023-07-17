#ifndef CONFIG_H
#define CONFIG_H

#define IP "127.0.0.1"
#define PORT1 50003
#define PORT2 50004

#define ERROR_CODE_77 "fail open file"
#define ERROR_CODE_110 "does not send header info"
#define ERROR_CODE_111 "does not request file transfer"

//#define ERROR_CODE_77 "파일 열기 실패"
//#define ERROR_CODE_110 "파일 헤더 정보를 보내지 못했습니다."
//#define ERROR_CODE_111 "파일 다운로드 요청을 보내지 못했습니다."

#define FILE_CODE 77
#define FILE_HEAD_REC_CODE 78
#define FILE_REC_CODE 79
#define UNZIP_CODE 80
#define COMPILE_CODE 81

#define FILE_DOWN_LOAD 90
#endif // CONFIG_H
