//  Copyright 2020 by Saurabh Gandhi

#include "udp_receiver.h"

#include "esp_system.h"
#include "esp_log.h"

#include <string.h>

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"

static const char *TAG = "UDP RCVR";

int udp_rec_fd;
static struct sockaddr_in serveraddr;
static char buf[UDP_RECEIVING_MAX_PAYLOAD_LEN];

void udp_receiver_free(void) {
	int err = 0;
    if( (err = shutdown(udp_rec_fd, 2)) == 0 ){
		ESP_LOGE(TAG, "\nUDP socket shutdown!");
	} else {
		ESP_LOGE(TAG, "\nShutting-down UDP socket failed: %d!\n", err);
	}

    if( (err = close( udp_rec_fd )) == 0 ) {
		ESP_LOGE(TAG, "\nUDP socket closed!");
	} else {
		ESP_LOGE(TAG, "\n Closing UDP socket failed: %d!\n", err);
	}
    udp_rec_fd = 0;
}

int udp_receiver_receive(void) {
    sendto(udp_rec_fd, "Init", 4, 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    socklen_t socklen = sizeof(serveraddr);
    int len = recvfrom(udp_rec_fd, buf, sizeof(buf) - 1, 0, (struct sockaddr *)&serveraddr, &socklen);

    // Error occurred during receiving
    if (len < 0) {
        ESP_LOGE(TAG, "recvfrom failed: errno %d", errno);
    }
    // Data received
    else {
        buf[len] = 0; // Null-terminate whatever we received and treat like a string
        ESP_LOGI(TAG, "Received %d bytes", len);
        ESP_LOGI(TAG, "%s", buf);
        if (strncmp(buf, "OK: ", 4) == 0) {
            ESP_LOGI(TAG, "Received flash initiation message.");
        }
    }
    return len;
}

int udp_receiver_init(const char *ipaddr, unsigned long port) {
	struct timeval send_timeout = {1,0};
	udp_rec_fd = 0;
	ESP_LOGI(TAG, "initializing udp logging...");
    if( (udp_rec_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
       ESP_LOGE(TAG, "Cannot open socket!");
       return -1;
    }

    uint32_t ip_addr_bytes;
    inet_aton(ipaddr, &ip_addr_bytes);
    ESP_LOGI(TAG, "Receiving from 0x%x", ip_addr_bytes);

    memset( &serveraddr, 0, sizeof(serveraddr) );
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons( port );
    serveraddr.sin_addr.s_addr = ip_addr_bytes;

    int err = setsockopt(udp_rec_fd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&send_timeout, sizeof(send_timeout));
	if (err < 0) {
	   ESP_LOGE(TAG, "Failed to set <option>. Error %d", err);
	}

    err = sendto(udp_rec_fd, "Init", 4, 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
	if (err < 0) {
	   ESP_LOGE(TAG, "Failed to send initialization packet");
	}

    return 0;
}
