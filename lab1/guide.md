# Lab 1 - Docker Container Inside Virtual Machine

This introductory lab intends to familiarize you with
the Ubuntu operating system (a Linux distribution) and
its command-line interface (i.e., shell).

We achieve this with an exercise on
setting-up a secure practice environment for the rest of this course.
In this lab, we will touch base on concepts and technologies including:

- Virtual machines (VM): backed by Vagrant and VirtualBox
- Container technologies: backed by Docker on Linux

Upon successful completion of the lab,
you should be able to deploy a simple webserver
running inside the container of your VM.

## Step 1: Update the installed packages

```bash
sudo apt-get update
sudo apt-get upgrade -y
```