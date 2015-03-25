make
sudo insmod ./calc_proc.ko
echo 1234 > /proc/calc_proc_first
cat /proc/calc_proc_result
sudo rmmod calc_proc
make clean
