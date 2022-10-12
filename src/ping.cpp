#include <stdio.h>
#include "ping.h"

Ping::Ping(IP * ip) {
    printf("Pinging: %s", ip->ADDR);
}