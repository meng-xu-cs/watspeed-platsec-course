# Lab 7 - Intel SGX

Intel Software Guard Extensions (SGX) is a set of security features
built into modern Intel processors that enables applications to
create isolated execution environments called enclaves.
These enclaves securely execute sensitive code and handle confidential data,
protecting them from unauthorized access---even if
the operating system or hypervisor is compromised.

In this lab,
you'll gain hands-on experience with SGX by
building a simple "Secure Square" application,
learning how code in trusted and untrusted environments interacts with each other, and
understanding how enclaves can bolster the security of critical computations.

## Step 1: Install Intel SGX SDK

```bash
sudo apt-get update
```
```bash
sudo DEBIAN_FRONTEND=noninteractive NEEDRESTART_MODE=a apt-get upgrade -y
```
```bash
sudo apt-get install -y build-essential automake autoconf libtool wget libssl-dev unzip
```
```bash
wget https://download.01.org/intel-sgx/latest/linux-latest/distro/ubuntu22.04-server/sgx_linux_x64_sdk_2.25.100.3.bin -O sgx_sdk.bin
```
```bash
chmod +x sgx_sdk.bin
```
```bash
./sgx_sdk.bin
```

You will be greated by a prompt:
> 
> Do you want to install in current directory? [yes/no] :
>
Type `yes` in the command line and hit enter.

If installation is successful, the screen should show
>
> Installation is successful! The SDK package can be found in "your-current-path"/sgxsdk
>

Follow the prompt and set the environment variables with the suggested command or using
```bash
source sgxsdk/environment
```

## Step 2: Download and understand the SGX application skeleton

We provide a minimal skeleton of SGX application for you to get familiar with
SGX application development. To get the skeleton, use
```bash
wget https://github.com/meng-xu-cs/watspeed-platsec-course/raw/refs/heads/main/lab7/sgx-skeleton.zip
```
```bash
unzip sgx-skeleton.zip
```
```bash
cd sgx-skeleton
```

Now you are in the directory of this skeleton SGX application.

There are three items in the directory:
- `Makefile`: pre-defined rules to build the SGX application.
   You don't need to modify this file
- `Enclave/` directory: all information about code in the enclave
   * `Enclave.config.xml`: configuration files for the SGX toolchain.
     You don't need to modify this file
   * `Enclave.edl`: **IMPORTANT**: this file defines
      + the trusted function provided by the enclave as well as
      + the untrusted functions that are going to be used by the enclave.
   * `Enclave.cpp`: **IMPORTANT**: source code of the enclave lives in
   * `Enclave.lds`: linker scripts for the SGX toolchain.
     You don't need to modify this file
- `App/` directory: all information about code running in the host (potentially untrusted) environment
   * `App.cpp`: **IMPORTANT**: source code for the host application which will invoke the SGX enclave.

Take a look at the file content that are marked with **IMPORTANT**,
examine their code closely, and try to understand
how the `Enclave` (in SGX) and the `App` (in host environment) might interact with each other.

You can also build the application and run it. To do this,
make sure you are in the `sgx-skeleton` directory (where you see a `Makefile`), then:
```bash
make
```

If compilation is successful, you should see the following in the output:
>
> The project has been built in debug simulation mode.
>

Run the host application via:
```bash
./app
```

And you will be promoted to enter an integer,
and after that either a `Goodbye!` or `Aborting...` message,
depending on whether you entered a valid 64-bit integer.

## Step 3: Implement the TODO items

The skeleton SGX application does not do anything useful in the enclave.
In this step, you need to extend the skeleton code so that the enclave
computes a simple sensitive operation --- calculating the square root of an input.

To be specific, the enclave function `ecall_secure_square` should:
- Receives an integer from the host (this is passed in as argument `input`)
- Print the integer received using an OCALL (to be implemented)
- Computes the square inside the enclave (to be implemented)
- Returns the result (to be implemented)

The host app should:
- Receives an integer from user input (done)
- Invoke the enclave `ecall_secure_square` using ECALL (to be implemented)
- Display (i.e., print) the result returned by the enclave (to be implemented)

All items marked as (*to be implemented*) can be found as TODO items in two files:
`Enclave/Enclave.cpp` and `App/App.cpp`. You only need to modify these files.

## Step 4: Validate your program

Once you are done with the implementation in Step 3,
first compile your program with the `make` command.

If `make` is successful, i.e., you see the following in the output:
>
> The project has been built in debug simulation mode.
>
You can test your program
with some concrete numbers and verify that the program is responding correctly.

For example, if the input integer is 10, the output from SGX Enclave should be 100,
hence if you run program with
```bash
./app
```

And when promoted:
>
> Please enter an integer:
>
Enter `10`

You should expect the following output:
>
> [SGX] Got input: 10 \
> [App] Got result: 100 \
> Goodbye!
>

If you get other output on the console,
it is very like that the program you develop has some issues.

## Submission

A Dropbox has been created on LEARN for lab submission.
To complete this lab,
please submit the modified version of `Enclave/Enclave.cpp` and `App/App.cpp` ONLY
which contains your implementation of the TODO items,
as well as any scripts, screenshots, or documents
that you may deem necessary to show your understanding of the task.
