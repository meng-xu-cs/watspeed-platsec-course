# Lab 4: Seccomp-sandboxes and Evasion Lab 
## Escaping `seccomp`-based Sandboxes

### Overview

### 1. Lab Tasks

In this lab, we have provided four binary executable files: sandbox1, sandbox2, sandbox3, and sandbox4. Each of these programs implements a `seccomp`-based sandbox and employs some distinct filtering rules. The programs are designed to execute external programs `sploit1`, `sploit2`, `sploit3`, and `sploit4` respectively.

   - `sandbox1.c` file

```
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
```

   - `sandbox2.c` file

```
//sandbox2.c

#include <unistd.h>
#include <seccomp.h>
#include <linux/seccomp.h>
#include <syscall.h>
#include <stdlib.h>

int main() {
	scmp_filter_ctx ctx;
	ctx = seccomp_init(SCMP_ACT_KILL);
	seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(open), 0);
	seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(read), 0);
	seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(write), 0);

    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(arch_prctl), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(mmap), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(access), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(newfstatat), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(close), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(mprotect), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(pread64), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(set_tid_address), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(set_robust_list), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(rseq), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(prlimit64), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(munmap), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(brk), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(execve), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit_group), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(fstat), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(getrandom), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(uname), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(readlink), 0);
	seccomp_load(ctx);

	char *args[] = {"./sploit2", NULL};
	execve(args[0], args, NULL);
}

```

   - `sandbox3.c` file

```
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
```

   - `sandbox4.c` file

```
//sandbox4.c

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
    
    seccomp_arch_add(ctx, SCMP_ARCH_X32);
	seccomp_load(ctx);

	char *args[] = {"./sploit4", NULL};
	execve(args[0], args, NULL);
}
```

Additionally, we have provided a `flag` file that stores a flag you required to get:

```
s3ccoMp_$@nd80x_fla6
```

Your task is to write four exploit programs in C language, namely `sploit1.c`, `sploit2.c`, `sploit3.c`, and `sploit4.c`, and compile them into four binary executable files sploit1, sploit2, sploit3, and sploit4, respectively, in such a way that when running the sandbox programs, the contents of the flag file are written into standard output. You are expected to submit the four source code files of your exploit programs with a `Makefile`, such that we can get your compiled binary executable files by simply typing `make` in the terminal

Below is an example demonstrating how to test your code and run the sandbox programs:

```
// compile your exploit programs
// (should produces sploit[1-4])
$ make

// run the sandbox programs
// (your exploit programs should be in the same folder as the sandbox programs)
$ ./sandbox1
the flag should be written to standard output and displayed here

$ ./sandbox2
the flag should be written to standard output and displayed here

$ ./sandbox3
the flag should be written to standard output and displayed here

$ ./sandbox4
the flag should be written to standard output and displayed here
```

NOTE: When evaluating your work, we will replace the contents of the flag file. Therefore, you should NOT hardcode the contents of the flag file in your program.

Tips: 
   - [`strace`](https://man7.org/linux/man-pages/man1/strace.1.html) is a handy utility which will tell you the system calls invoked by a process.
   - While reading the assembly can be a way to extract the seccomp-bpf rules enforced in each sandbox, it is not recommended. There are other ways of extracting the rules enforced.



### You have successfully completed the lab


