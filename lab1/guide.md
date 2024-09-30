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

## Step 0: Establish an SSH connection to the cloud machine

You should see a terminal display alongside this lab guide.
However, should you prefer to connect to the cloud machine in alternative ways,
Please refer to the [CloudLabs documentation](https://docs.cloudlabs.ai/Learner/ConnectToTheVM)
for the instructions to connect to the cloud machine assigned to you.

Note that you will need
*VM DNS name*, *VM Admin Username*, and *VM Admin Password*
to make the connection,
which can be found in the `Environment` tab on the lab manual page.

## Step 1: update the installed packages

Once you established a connection to the cloud machine,
run the following commands in the terminal:

```bash
sudo apt-get update && sudo apt-get upgrade -y
```

The purpose of these commands is to bring the base Ubuntu operating system
up to date.

`apt` is the command for the [package manager](https://ubuntu.com/server/docs/package-management)
on Ubuntu, which we will use a lot through this course.

## Step 2: install VM-related packages

As we will be learning attacks and defenses in this course,
it is not a bad idea to run the experiments in an isolated environment.
In this step, we will setup our first level of isolation ---
a virtual machine (VM).

More specifically, we will be using
- [VirtualBox](https://www.virtualbox.org/) as the backend
  for actually running the VMs, and
- [`vagrant`](https://www.vagrantup.com/) as the frontend
  for easy deployment and management of VMs.

Fortunately, both tools are already indexed by the `apt` package manager,
so we can simply install them via

```bash
sudo apt-get install virtualbox vagrant -y
```

## Step 3: launching up your first VM

```bash
vagrant up
```

## Step 4: install Docker inside the VM

```bash
vagrant ssh
```

1. Set up Docker's `apt` repository.
```bash
sudo apt-get update
sudo apt-get install ca-certificates curl
sudo install -m 0755 -d /etc/apt/keyrings
sudo curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc
sudo chmod a+r /etc/apt/keyrings/docker.asc
```

2. Install the Docker packages.
```bash
sudo apt-get install -y \
    docker-ce docker-ce-cli containerd.io \
    docker-buildx-plugin docker-compose-plugin
```

3. Verify that the Docker Engine installation is successful
   by running the `hello-world` image.
```bash
sudo docker run hello-world
```

This command downloads a test image and runs it in a container.
When the container runs, it prints a confirmation message and exits.
If you see the confirmation message,
you have now successfully installed and started Docker Engine.