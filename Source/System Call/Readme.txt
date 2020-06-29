//// PNAMETOID và PIDTONAME

- Chạy Userspace test:
make all

-> pnametoid: Nhập name vào sẽ trả về id
-> pidtoname: Nhập id sẽ trả về name
---> Kết quả trả về được in thẳng vào Userspace

- Vào dmesg để kiểm tra kết quả: Nếu trong dmesg có in ra tên của tiến trình thì syscall chạy thành công