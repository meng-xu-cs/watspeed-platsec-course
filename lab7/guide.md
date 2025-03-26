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

## Step 2: Understand the SGX application skeleton



## Step 3: Implement the TODO items

## Step 4: Validate your program

Test your program with some concrete numbers and verify that the program is responding correctly.

For example, if the input integer is 10, the output from SGX Enclave should be 100,
hence if you run program with
```bash
./app
```

And when promoted:
> Please enter an integer: \
Enter `10`

You should expect the following output:
> [SGX] Got input: 10 \
> [App] Got result: 100 \
> Goodbye!

If you get other output on the console, it is very like that the program you develop
has some issues.