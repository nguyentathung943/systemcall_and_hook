Link tải UBUNTU: http://old-releases.ubuntu.com/releases/14.04.0/ubuntu-14.04-desktop-amd64.iso
---> Ubuntu phiên bản 14.04

Bước 1: Cài cái gói tin mở rộng: 
- Trong Terminal
sudo apt-get install libncurses5-dev libncursesw5-dev
sudo apt-get install libssl-dev
sudo apt-get install libelf-dev
sudo apt-get install bison
sudo apt-get install flex
sudo apt-get install bc
sudo apt-get install perl
sudo apt-get install gcc
sudo apt-get install build-essential
sudo apt-get update
sudo apt-get upgrade
----> Phải chắc chắn là cài thành công các gói tin trên 

Bước 2: Download gói Kernel về -> Tải theo cùng phiên bản Kernel -> Vì phiên bản hiện tại đang là 3.13 nên tải kernel
bản 13.13
- Trong Terminal, gõ:
	wget https://mirrors.edge.kernel.org/pub/linux/kernel/v3.x/linux-3.13.11.tar.xz

Bước 3: Giải nén gói tin vào thư mục usr
- Trong Terminak, gõ:
	sudo tar -xvf linux-3.13.11.tar.xz -C /usr/src/

Bước 4:
- Cài đặt code -> Trong báo cáo

Bước 5: Tạo Menuconfig
- Trong Terminal, gõ:
	sudo make menuconfig -> save -> exit

Bước 6: Build kernel 
- Trong Terminal, gõ:
	sudo make -j 8 && sudo make modules_install -j 8 && sudo make install -j 8

Bước 7:
Build xong restart lại máy, trong Ubuntu boot menu chọn Advance option ubuntu chọn bản 3.13.11
