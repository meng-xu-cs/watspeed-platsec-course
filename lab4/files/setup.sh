#!/bin/bash

echo "[*] Downloading Lab 4 binaries..."

BASE_URL="https://raw.githubusercontent.com/meng-xu-cs/watspeed-platsec-course/main/lab4/files"
FILES=(sandbox1 sandbox2 sandbox3 sandbox4 flag)

for file in "${FILES[@]}"; do
    echo "Downloading $file..."
    wget -q "$BASE_URL/$file" -O "$file"
    chmod +x "$file"
done

echo "[+] Lab 4 environment ready!"
