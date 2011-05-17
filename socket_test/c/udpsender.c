#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
//#define NDEBUG
#include <assert.h>

#define P_UDP
#include "SendData.h"

int main( int argc, char **argv )
{
  // ポート
  int port = 0;
  // 送信先ip
  char *ip = NULL;
  // ソケット
  int sock;
  struct sockaddr_in addr;
  struct send_result res;

  int ret = 0;

  /* 引数チェック */
  if( argc > 2 ){
    // ポート指定
    port = atoi(argv[2]);
  }else if( argc > 1){
    ip = argv[1];
    // use default 
    port = 56789;  
  }else{
    fprintf("Usage: %s ip port\n",argv[0]);
    exit(EXIT_FAILURE);
  }

  /* 接続 */
  // ソケット作り
  sock = socket( PF_INET, SOCK_DGRAM, 0 );
  if( sock == -1 ){
    perror("socket");
    exit(EXIT_FAILURE);
  }
  // ソケットの設定
  addr.sin_family = PF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = inet_addr(ip);
  if( addr.sin_addr.s_addr == INADDR_NONE ){
    fprintf("Invalid address: %s\n",ip);
    exit(EXIT_FAILURE);
  }

  /* データ送信 */
  res = SendData(sock,(struct sockaddr*)&addr,sizeof(addr));
  /* 結果表示 */
  print_result(&res);
  
}

