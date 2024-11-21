#include "amdgpu_socket_utils.h"
#include "criu-log.h"
#include "common/scm.h"
#include "fdstore.h"
#include <time.h>
#include <semaphore.h>
#include <fcntl.h>
#include "util-pie.h"
#include "util.h"

int addr_len;
struct sockaddr_un sock_addr;
int sock_id = 0;

static void amdgpu_socket_name_gen(struct sockaddr_un *addr, int *len)
{
	addr->sun_family = AF_UNIX;
	snprintf(addr->sun_path, UNIX_PATH_MAX, "x/criu-amdgpu-parallel-%" PRIx64, criu_run_id);
	*len = SUN_LEN(addr);
	*addr->sun_path = '\0';
}

int install_parallel_sock()
{
	int ret = 0;
	int sock_fd;
	if ((sock_fd = socket(PF_UNIX, SOCK_DGRAM | SOCK_CLOEXEC, 0)) < 0) {
		pr_perror("socket creation failed");
		return -1;
	}
	amdgpu_socket_name_gen(&sock_addr, &addr_len);
	if ((ret = bind(sock_fd, (struct sockaddr *)&sock_addr, addr_len)) < 0) {
		pr_perror("bind failed");
		goto err;
	}
	if ((sock_id = fdstore_add(sock_fd)) < 0) {
		ret = -1;
		goto err;
	}
err:
	close(sock_fd);
	return ret;
}