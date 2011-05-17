#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
//#define NDEBUG
#include <assert.h>

#define P_TCP
#include "SendData.h"

int main( int argc, char **argv )
{
  // 待ち受けポート
  int port = 0;
  // ソケット
  int sockwait,sock;
  struct sockaddr_in addr,client;
  struct send_result res;

  int ret = 0;

  /* 引数チェック */
  if( argc > 1 ){
    // ポート指定
    port = atoi(argv[1]);
  }else{
    // use default 
    port = 56789;  
  }

  /* 接続 */
  // ソケット作り
  sockwait = socket( PF_INET, SOCK_STREAM, 0 );
  if( sockwait == -1 ){
    perror("socket");
    exit(EXIT_FAILURE);
  }
  // ソケットの設定
  addr.sin_family = PF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = INADDR_ANY;
  ret = bind(sockwait, (struct sockaddr *)&addr, sizeof(addr));
  if( ret == -1 ){
    perror("bind");
    exit(EXIT_FAILURE);
  }

  // 接続待つ
  ret = listen( sockwait, 1 );
  
  // 接続受ける
  len = sizeof(client);
  sock = accept( sockwait, (struct sockaddr *)&client, &len);

  /* データ送信 */
  res = SendData();

  /* 結果表示 */
  print_result(&res);
  
}

