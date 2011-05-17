#pragma once
#include <sys/types.h>
#include <sys/socket.h>

struct send_result {
  long long int sum; // 送信したデータ量[byte]
  float time;        // 送信にかかった時間[sec]
};
  
struct send_result SendData(int sock, struct sockaddr* paddr, size_t len);
void print_result(struct send_result* res);
