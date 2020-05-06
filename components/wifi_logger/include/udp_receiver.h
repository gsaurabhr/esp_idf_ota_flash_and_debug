//  Copyright 2020 by Saurabh Gandhi

#ifndef UDP_RECEIVING_MAX_PAYLOAD_LEN
#define UDP_RECEIVING_MAX_PAYLOAD_LEN 4096
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_system.h"
#include "esp_log.h"

#include <string.h>
extern int udp_rec_fd;
// perhaps the receiver registers a callback function in init?
int udp_receiver_init(const char *ipaddr, unsigned long port);
int udp_receiver_receive(void);
void udp_receiver_free(void);

#ifdef __cplusplus
}
#endif
