#include <cstdio>
#include <iostream>
#include "ip.h"

IP::IP(char input_addr[]) {
    sscanf(input_addr, "%hhu.%hhu.%hhu.%hhu", ADDR[0], ADDR[1], ADDR[2], ADDR[3]);
}