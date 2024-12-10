#ifndef __KFD_PLUGIN_AMDGPU_SOCKET_UTILS_H__
#define __KFD_PLUGIN_AMDGPU_SOCKET_UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>

int install_parallel_sock(void);

#endif
