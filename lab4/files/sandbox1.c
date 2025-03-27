//sandbox1.c

#include <unistd.h>
#include <seccomp.h>
#include <linux/seccomp.h>
#include <syscall.h>
#include <stdlib.h>

int main() {
	scmp_filter_ctx ctx;
	ctx = seccomp_init(SCMP_ACT_ALLOW);
	seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(write), 0);
	seccomp_load(ctx);

	char *args[] = {"./sploit1", NULL};
	execve(args[0], args, NULL);
}
