//sandbox3.c

#include <unistd.h>
#include <seccomp.h>
#include <linux/seccomp.h>
#include <syscall.h>

int main() {
	scmp_filter_ctx ctx;
	ctx = seccomp_init(SCMP_ACT_ALLOW);

	seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(write), 0);
	seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(open), 0);
    seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(writev), 0);
    // seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(writev2), 0);
    seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(sendfile), 0);
    seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(sendfile64), 0);
    seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(ptrace), 0);
    seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(prctl), 0);
    seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(splice), 0);
    seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(tee), 0);
    seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(vmsplice), 0);
    // seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(pwrite), 0);
    seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(pwritev), 0);
    seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(pwritev2), 0);
    seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(pwrite64), 0);
    seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(open_by_handle_at), 0);
    seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(copy_file_range), 0);
    seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(pwritev2), 0);
    seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(ioctl), 0);
    seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(send), 0);
    seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(sendto), 0);
    seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(sendmsg), 0);
    seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(sendmmsg), 0);
    seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(msgsnd), 0);
    
    seccomp_arch_add(ctx, SCMP_ARCH_X86);
	seccomp_load(ctx);

	char *args[] = {"./sploit3", NULL};
	execve(args[0], args, NULL);
}
