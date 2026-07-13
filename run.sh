
date > results_release.txt
date +%T >> results_release.txt

echo "about 15 minutes, please wait ..."

./Sorts >> results_release.txt

date +%T
date +%T >> results_release.txt

read -p "Press any key to continue..." -n1