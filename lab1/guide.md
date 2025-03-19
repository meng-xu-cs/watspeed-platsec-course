# Lab 1 - Container Inside Virtual Machine

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
sudo apt-get update
```
```bash
sudo DEBIAN_FRONTEND=noninteractive NEEDRESTART_MODE=a apt-get upgrade -y
```

The purpose of these commands is to bring the base Ubuntu operating system
up to date.

`apt` is the command for the [package manager](https://ubuntu.com/server/docs/package-management)
on Ubuntu, which we will use a lot throughout this course.

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

One way of installing them is to download the installer from their
official websites and follow the instructions to run the installer.
But on most Linux-based distributions (including Ubuntu),
there are simpler solutions --- install via the `apt` package manager.

### Installing `virtualbox`

```bash
wget -O - https://www.virtualbox.org/download/oracle_vbox_2016.asc | sudo gpg --dearmor -o /etc/apt/trusted.gpg.d/virtualbox.gpg
```
```bash
echo "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/trusted.gpg.d/virtualbox.gpg] http://download.virtualbox.org/virtualbox/debian $(lsb_release -cs) contrib" | sudo tee /etc/apt/sources.list.d/virtualbox.list
```
```bash
sudo apt update
```
```bash
sudo DEBIAN_FRONTEND=noninteractive NEEDRESTART_MODE=a apt install -y virtualbox-7.1
```

### Installing `vagrant`

```bash
wget -O - https://apt.releases.hashicorp.com/gpg | sudo gpg --dearmor -o /usr/share/keyrings/hashicorp-archive-keyring.gpg
```
```bash
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/hashicorp-archive-keyring.gpg] https://apt.releases.hashicorp.com $(lsb_release -cs) main" | sudo tee /etc/apt/sources.list.d/hashicorp.list
```
```bash
sudo apt update
```
```bash
sudo DEBIAN_FRONTEND=noninteractive NEEDRESTART_MODE=a apt install -y vagrant
```

## Step 3: launch your first VM

In order for `vagrant` to manage a VM,
you need to provide a `Vagrantfile`.

Save the following text to a file named `Vagrantfile`
under your home directory.
```rb
Vagrant.configure("2") do |config|
  config.vm.box = "ubuntu/jammy64"
  config.vm.network "forwarded_port", guest: 80, host: 8080
  config.vm.provider "virtualbox" do |v|
    v.cpus = 2
    v.memory = 4096
  end
end
```

Tips: you can use any terminal-oriented text-editing tool
to create this file. Common choices include `vim` and `nano`
(both are available in the VM already).

In the directory of the `Vagrantfile` (which was just created), run

```bash
vagrant up
```

This will launch and provision the VM.
It may take a couple of minutes before the VM is ready to use.

## Step 4: install Docker inside the VM

To get inside the VM, use the following command:

```bash
vagrant ssh
```

This will spawn a shell environment inside the VM you just launched.
You will be greeted by the welcome message by the Ubuntu operating system
and note that your username inside the VM is `vagrant`,
not the username you use to access the cloud machine.

Once you are in the shell of the VM,
follow the following steps to setup a Docker environment:

1. Upgrade packages inside the the VM.

```bash
sudo apt-get update && sudo apt-get upgrade -y
```
```bash
sudo apt-get install -y ca-certificates curl
```
```bash
sudo install -m 0755 -d /etc/apt/keyrings
```

2. Install the Docker packages.

```bash
sudo curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc
```
```bash
sudo chmod a+r /etc/apt/keyrings/docker.asc
```
```bash
echo "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list
```
```bash
sudo apt-get update && sudo apt-get install -y docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
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

## Step 5: run the Apache Docker image as a sandboxed webserver

The official Apache image on Docker Hub is `httpd`.
Download the image to your VM with the `docker pull` command:

```bash
sudo docker pull httpd
```

After pulling,
use the `docker run` command to create and start a Docker container
based on the `httpd` image:

```bash
sudo docker run -d --name apache -p 80:80 httpd
```

## Validation

At this step, you have successfully setted up a web server
in a Dockerized environment inside a VM. To test it out,
inside the VM on the console, try this command:
```bash
curl localhost:80
```

You are expected to see the following in the console output:
```html
<html><body><h1>It works!</h1></body></html>
```
If this is not the output, you might have missed a step above.

## Task to Complete

The validation step above only checks that you can access the web server
inside the VM. In fact, your web server can also be accessed
from outside publicly. This is something you need to explore
in the rest of the assignment.

Essentially, find a URL such that if you input the URL in your web browser
(not the web browser inside the VM), the URL will lead you to a webpage
that simply shows: "It works!".

Hint: this URL consists of a host name and an optional port number.

## Submission

A Dropbox has been created on LEARN for lab submission.
To complete this lab, submit the URL you have found in the Dropbox,
and optionally, you can include a screenshot of the webpage behind this URL.