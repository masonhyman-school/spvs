#include <iostream>
#include "ping.h"

using namespace std;

int main(int argc, char ** argv) {
    IP * target = new IP(argv[1]);
    printf("%s", target->ADDR);
    Ping ping(target);
}