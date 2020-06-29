///HOOK

- Trước khi insmod ráp module hook vào kernel, clear dmesg:
dmesg -C
 
- Theo dõi dmesg theo thời gian thực: 
dmesg -wH

- Tạo module: 
make all

- Ráp module vào Kernel
sudo insmod hook.ko

- Build file test trong Userspace
gcc test.c -o test

- Chạy file test hook, trong thư mục Test hook
sudo ./test

- Remove module
sudo rmmod hook

----> Xong các bước thì gõ dmesg trong Terminal để xem kết quả
