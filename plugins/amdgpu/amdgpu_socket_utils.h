#ifndef __KFD_PLUGIN_AMDGPU_SOCKET_UTILS_H__
#define __KFD_PLUGIN_AMDGPU_SOCKET_UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>

typedef struct {
	int id;
	int fd_write_num;
	int entry_num;
} parallel_restore_cmd_head;

typedef struct {
	int gpu_id;
	int minor;
	int write_id;
	uint64_t read_offset;
	uint64_t write_offset;
	uint64_t size;
} parallel_restore_entry;

typedef struct {
	parallel_restore_cmd_head cmd_head;
	int *fds_write;
	parallel_restore_entry *entries;
} parallel_restore_cmd;

extern parallel_restore_cmd restore_cmd;

void init_parallel_restore_cmd(int num, int id);

void free_parallel_restore_cmd();

int install_parallel_sock();

int send_parallel_restore_cmd(void);

int recv_parallel_restore_cmd(void);

void parallel_restore_bo_add(int dmabuf_fd, int gpu_id, uint64_t size, uint64_t offset, int minor);
#endif
