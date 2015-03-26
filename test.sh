make >> log.txt
sudo insmod ./calc_proc.ko

echo "testing 12 + 12:"
echo 12 > /proc/calc_proc_first
echo 12 > /proc/calc_proc_second
echo '+' > /proc/calc_proc_operation
cat /proc/calc_proc_result

echo "testing 24 - 12:"
echo 24 > /proc/calc_proc_first
echo 12 > /proc/calc_proc_second
echo '-' > /proc/calc_proc_operation
cat /proc/calc_proc_result

echo "testing 12 * 12:"
echo 12 > /proc/calc_proc_first
echo 12 > /proc/calc_proc_second
echo '*' > /proc/calc_proc_operation
cat /proc/calc_proc_result

echo "testing 24 / 12:"
echo 24 > /proc/calc_proc_first
echo 12 > /proc/calc_proc_second
echo '/' > /proc/calc_proc_operation
cat /proc/calc_proc_result

echo "testing 24 / 0:"
echo 24 > /proc/calc_proc_first
echo 0 > /proc/calc_proc_second
echo '/' > /proc/calc_proc_operation
cat /proc/calc_proc_result
dmesg | tail -n 1

sudo rmmod calc_proc
make clean >> log.txt

