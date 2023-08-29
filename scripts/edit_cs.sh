
TMP_DIR=/usr2

#set -v

echo Reading CS...

ssh 10.76.247.21 "cd /ccshare/linux/c_spec && tar -cf - kha_*_cr$1_configspec.txt 2>/dev/null" | tar -C $TMP_DIR -xf -

cd $TMP_DIR

[ -f kha_*_cr$1_configspec.txt ] || (echo "CS $1 not found" && exit)

vim kha_*_cr$1_configspec.txt

echo Writing CS...

tar -cf - kha_*_cr$1_configspec.txt | ssh 10.76.247.21 "tar -C /ccshare/linux/c_spec -xf -"

rm kha_*_cr$1_configspec.*
