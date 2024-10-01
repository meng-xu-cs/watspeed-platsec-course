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
such as the [shellcode lab](https://seedsecuritylabs.org/Labs_20.04/Software/Shellcode/).