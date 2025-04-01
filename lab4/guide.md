# Lab 4: Seccomp-sandboxes and Evasion Lab 
## Escaping `seccomp`-based Sandboxes

## Overview

In this lab, we have provided four binary executable files: sandbox1, sandbox2, sandbox3, and sandbox4. Each of these programs implements a `seccomp`-based sandbox and employs some distinct filtering rules. The programs are designed to execute external programs `sploit1`, `sploit2`, `sploit3`, and `sploit4` respectively.

#### Hint: You can use `seccomp-tools` [(https://github.com/david942j/seccomp-tools)](https://github.com/david942j/seccomp-tools) to get the detailed seccomp rules.

## Environment Setup

You should use a **CloudLab VM** for this assignment.

First, install required packages:

```bash
sudo apt update
sudo apt install gcc make strace -y
```

Then, download and set up the lab files:

```bash
wget https://raw.githubusercontent.com/meng-xu-cs/watspeed-platsec-course/main/lab4/files/setup.sh
chmod +x setup.sh
./setup.sh
```

The script will download sandbox1 to sandbox4

Additionally, we have provided a `flag` file that stores a flag you required to get:

```
s3ccoMp_$@nd80x_fla6
```

## 1. Lab Tasks

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


## Submission

A Dropbox has been created on LEARN for lab submission.
To complete this lab,
please submit the four `.c` source code files of your exploit programs with a `Makefile`.
You can also submit any scripts, screenshots, or documents
that you may deem necessary to show your understanding of the task.
