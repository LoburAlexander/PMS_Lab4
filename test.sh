make >> log.txt
sudo insmod ./calc_proc.ko
echo 12 > /proc/calc_proc_first
echo 32 > /proc/calc_proc_second
cat /proc/calc_proc_result
sudo rmmod calc_proc
make clean >> log.txt
