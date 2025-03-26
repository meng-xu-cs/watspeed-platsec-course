# Lab 7 - Intel SGX

Intel Software Guard Extensions (SGX) is a set of security features
built into modern Intel processors that enables applications to
create isolated execution environments called enclaves.
These enclaves securely execute sensitive code and handle confidential data,
protecting them from unauthorized access---even if the operating system or hypervisor is compromised.

In this lab, you'll gain hands-on experience with SGX by building a simple "Secure Square" application,
learning how to code in trusted and untrusted environments interacts with each other, and
understanding how enclaves can bolster the security of critical computations.

Preparation
```bash
sudo apt-get update
```
```bash
sudo DEBIAN_FRONTEND=noninteractive NEEDRESTART_MODE=a apt-get upgrade -y
```

Build the Intel(R) SGX SDK
```bash
sudo apt-get install -y \
    build-essential ocaml ocamlbuild automake autoconf libtool wget python-is-python3 libssl-dev git cmake perl unzip
```

```bash
git clone https://github.com/intel/linux-sgx.git
```
```bash
cd linux-sgx && make preparation
```
```bash
make sdk
```
```bash
make sdk_install_pkg
```


SDK Download page: https://download.01.org/intel-sgx/latest/linux-latest/


For Ubuntu 24.04: https://download.01.org/intel-sgx/latest/linux-latest/distro/ubuntu24.04-server/sgx_linux_x64_sdk_2.25.100.3.bin

For Ubuntu 22.04: https://download.01.org/intel-sgx/latest/linux-latest/distro/ubuntu22.04-server/sgx_linux_x64_sdk_2.25.100.3.bin

```bash
source /home/m285xu/sgx/sgxsdk/environment
```