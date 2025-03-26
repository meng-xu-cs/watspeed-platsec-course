# Lab 5: Linux Access Control

In this lab,
you will build on your foundational knowledge of the Linux command line to explore
how access control mechanisms contribute to system security.
You will delve into how Linux implements security through file permissions,
Access Control Lists (ACLs), and special permission bits such as
`setuid` and `setgid`, and the sticky bit.

The goal of this lab is to provide you with hands‑on experience
in configuring and verifying these security features,
enabling you to understand their role in protecting system resources and managing multi‑user environments.
By the end of the exercise,
you should be able to interpret and modify access controls effectively,
appreciate the significance of secure permission settings, and
recognize potential security implications in real‑world scenarios.

## Step 1: Basic file permissions

In this step,
you will get familiar with basic file permissions on most
Linux file systems.

To start with, create a file for testing:
```bash
touch testfile.txt
```

Now, check its permission:
```bash
ls -l testfile.txt
```

**Q1**: What does each segment of the permission string represent?

Now we modify the file permission with the following commands:
```bash
chmod o-w testfile.txt
```
```bash
chmod u+x testfile.txt
```

And check the file permission again:
```bash
ls -l testfile.txt
```

**Q2**: How do the changes you made (i.e., the two `chmod` commands)
        affect which users can read, write, or execute the file?

## Step 2: Advanced access control with ACLs

In this step,
you will learn some advanced access control tooling
availble on the Linux system, the `acl` (short for Access Control List).

To start with, create a directory for testing:
```bash
mkdir shared_dir
```

Observe the default permissions set on the directory
```bash
ls -ld shared_dir
```

Now create two users, `alice` and `bob` on the system.
```bash
adduser --disabled-password --gecos "" alice
```
```bash
adduser --disabled-password --gecos "" bob
```

Grant `alice` full access and `bob` read-only access using ACLs:
```bash
sudo setfacl -m u:alice:rwx shared_dir
```
```bash
sudo setfacl -m u:bob:r-- shared_dir
```

Now, observe the ACL permission on this shared directory
```bash
getfacl shared_dir
```

**Q3**: How does the ACL output complement or override the standard permission settings?

**Q4**: What happens if a user is not explicitly mentioned in the ACL?

## Step 3: Special permission bits

In this step,
you will learn some of the special permission bits
availble on the Linux system, namely,
the `setuid`, `setgid`, and the sticky bit.

To start with, compile the following C program to an executable.
```c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
    uid_t effective_uid = geteuid();
    gid_t effective_gid = getegid();

    printf("Effective UID: %d\n", effective_uid);
    printf("Effective GID: %d\n", effective_gid);

    return 0;
}
```

You can save this C program as `show_id.c` and use the following command
to compile the `show_id` executable.
```bash
gcc -o show_id show_id.c
```

Execute `./show_id` and observe its output.

Now, changes the special permission bits on this executable:
```bash
sudo chown root:root show_id
```
```bash
sudo chmod u+s show_id
```

Execute `./show_id` again, and observe its output.

**Q5**: What differences do you notice in the output? What are the security implications of them?

Another feature on Linux filesystem is the sticky bit.
The sticky bit restricts who can delete files in a directory.
Specifically, when the sticky bit is set, only
1) the user that owns the file, or
2) the user that owns the directory, or
3) the root user can delete a file within the directory.

To test this out, first create a public directory where anyone can read and write.
```bash
mkdir public_dir
```
```bash
chmod o+w public_dir
```

Examnine the permission of this directory with
```bash
ls -ld public_dir
```

And create two files inside the newly created directory
```bash
touch public_dir/file1 public_dir/file2
```

Now, login on behalf of user `alice` (creaetd in Step 2 above):
```bash
sudo su alice
```

As user `alice`, try to remove `file1`
```bash
rm public_dir/file1
```

Observe the result.

Now exit user `alice` with
```bash
exit
```

And subsequently set the sticky bit for the directory
```bash
chmod +t public_dir
```

Now, login on behalf of user `alice` again
```bash
sudo su alice
```

And try to remove `file2`
```bash
rm public_dir/file2
```

Observe the result.

**Q6**: What differences do you notice in the two removal operations?
        How does the sticky bit enhance the security of shared directories?

## Submission

A Dropbox has been created on LEARN for lab submission.
To complete this lab,
please submit a `.txt` or `.pdf` file
which contains your responses to the six questions (Q1 to Q6) above
as well as any scripts, screenshots, or documents
that you may deem necessary to show your understanding of the task.
