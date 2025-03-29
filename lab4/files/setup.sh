#!/bin/bash

#echo "[*] Downloading Lab 4 binaries..."

#BASE_URL="https://raw.githubusercontent.com/meng-xu-cs/watspeed-platsec-course/main/lab4/files"
#FILES=(sandbox1 sandbox2 sandbox3 sandbox4 flag)

#for file in "${FILES[@]}"; do
#    echo "Downloading $file..."
#    wget -q "$BASE_URL/$file" -O "$file"
#    chmod +x "$file"
#done

#echo "[+] All files downloaded and ready!"
#**********************************
#!/bin/bash

echo "[*] Setting up Lab 4 environment..."

BASE_URL="https://raw.githubusercontent.com/meng-xu-cs/watspeed-platsec-course/main/lab4/src"
FILES=(sandbox1.c sandbox2.c sandbox3.c sandbox4.c flag)

# Download source and flag
for file in "${FILES[@]}"; do
    echo "Downloading $file..."
    wget -q "$BASE_URL/$file" -O "$file"
done

# Compile each sandbox
for i in {1..4}; do
    echo "Compiling sandbox$i..."
    gcc -o sandbox$i sandbox$i.c -lseccomp
    chmod +x sandbox$i
done

chmod +x flag

echo "[+] All sandboxes compiled successfully."

