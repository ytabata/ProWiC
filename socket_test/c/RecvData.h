#pragma once

struct recv_result {
  long long int sum;
};

struct recv_result RecvData(int sock);
void print_result(struct recv_result* res);

