# Lab 3 - Race Conditions

Race conditions occur when the timing of events affects a program’s correctness.
Time-of=check to time-of-use (TOCTOU) bugs are typical exmaples of race conditions.
In security, TOCTOU bugs arise when a program checks a resource (like a file) and
then uses it later without revalidating, leaving a window where an attacker can intervene.

In this lab, you will:
- Understand what a TOCTOU vulnerability is.
- Examine a simple vulnerable program.
- Exploit the vulnerability by forcing the program to use a modified file.

By the end of this lab, you should be able to
- Identify the race condition in a check-then-act sequence.
- Create an exploitation script that triggers the race condition.
- Reflect on and discuss mitigation strategies to prevent such vulnerabilities.

## Step 0: lab setup

Create the following files in your virtual machine (VM).

- `vuln_reader.c`: A simple C program with a TOCTOU vulnerability.

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc != 1) {
        fprintf(stderr, "Program %s does not take arguments\n", argv[0]);
        exit(1);
    }

    const char *filename = "target.txt";
    char target[256];

    // Find the target of the symbolic link
    ssize_t len = readlink(filename, target, sizeof(target));
    if (len == -1) {
        perror("readlink");
        exit(1);
    }
    target[len] = '\0';

    // Check if the target being accessed is "safe.txt"
    if (strcmp(target, "safe.txt") != 0) {
        fprintf(stderr, "Invalid symbolic link %s\n", target);
        exit(1);
    }

    // Introduce an artificial delay to widen the race window.
    usleep(100000);

    // Open and read the symbolic link
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("fopen");
        exit(1);
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }

    // Close the file
    fclose(fp);
    return 0;
}
```

- `safe.txt`: A benign file containing non-secret information

```bash
echo "Hello World" > safe.txt
```

- `secret.txt`: A file containing a "secret" (e.g., a password)

```bash
echo "A31DZyib6WeSx31VD2NxDls4WVwwbUPE" > secret.txt
```

- `target.txt`: A symbolic link initially pointing to `safe.txt`

```bash
ln -s safe.txt target.txt
```

## Step 1: understanding the vulnerable program

Take a closer look at the source code of the vulnerable program
`vuln_reader.c`. Briefly, this vulnerable program does the following:

- The program first checks the underlying path behind the symbolic link
  `target.txt` should be `safe.txt`.
- After a deliberate delay (`usleep`), it opens and reads the link and
  print out its content.
- **Vulnerability**: Between the `readlink()` check and the `fopen()`,
  an attacker can modify the link (for example, by swapping a symbolic link).

You can compile the vulnerable program with:
```bash
gcc -o vuln_reader vuln_reader.c
```

And subsequently execute `vuln_reader` by:
```bash
./vuln_reader
```

Notice what is printed out on the terminal. Without any attack, you
should expect "Hello World" being printed on the terminal, which is
the content of `safe.txt`.

## Step 2: create an exploitation script

Write a Shell (`.sh`) or Python (`.py`) script that exploits the
vulnerability in the compiled `vuln_reader` executable. Your script
needs to invoke this `vuln_reader` executable but when it is executed,
`vuln_reader` should print out the content in `secret.txt` instead.

## Step 3: mitigate the vulnerability

Prepare a `safe_reader.c` that does what `vuln_reader.c` intends to do:
i.e., print out the content of `target.txt` only after checking that
`target.txt` is a link to `safe.txt`, but is not vulnerable to TOCTOU.

To check whether `safe_reader.c` is really safe, test it with the script
you created for Step 2.

Hint: check the `freadlink` library call.

## Submission

A Dropbox has been created on LEARN for lab submission.
To complete this lab,
please submit the Shell (`.sh`) or Python (`.py`) script you prepared in step 2
as well as the `safe_reader.c` file you prepared in step 3.
You can also submit any scripts, screenshots, or documents
that you may deem necessary to show your understanding of the task.