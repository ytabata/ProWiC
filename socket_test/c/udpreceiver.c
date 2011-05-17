#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
//#define NDEBUG
#include <assert.h>

#define P_UDP
#include "RecvData.h"

int main( int argc, char **argv )
{
  // 接続先 IP address & Port
  char *ipstr = NULL;
  int port = 0;
  // ソケット
  int sock;
  struct sockaddr_in addr;
  
  int ret = 0;
  
  struct recv_result res;
  
  /* 引数チェック */
  if( argc < 2 ){
    fprintf(stderr,"Usage: %s addr port\n",argv[0]);
    exit(EXIT_FAILURE);
  }
  ipstr = argv[1];
  if( argc > 2 ){
    port = atoi(argv[2]);
  }else{
    port = 56789; // use default
  }


  /* 接続 */
  // ソケットつくる
  sock = socket( PF_INET, SOCK_DGRAM, 0 );
  if( sock == -1 ){
    perror("socket");
    exit(EXIT_FAILURE);
  }

  // IPアドレスをバイナリに変換
  addr.sin_family = AF_INET;
  if( !inet_aton( ipstr, &(addr.sin_addr) )){
    perror("inet_aton");
    exit(EXIT_FAILURE);
  }
  // ポート番号を変換
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = INADDR_ANY;

  bind(sock, (struct sockaddr *)&addr, sizeof(addr));

  /* 受信 */
  res = RecvData(sock);

  /* 結果表示 */
  print_result(&res);

}

