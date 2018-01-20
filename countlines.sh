#!/bin/bash
#loops ovr files
for file in $(git ls-files); do

    git blame --line-porcelain $file | grep  "^author " | sort | uniq -c | sort -nr >>temp1  
#for each file gets git to print each line with the author of that line, sums up values by author into file temp1
done

sed "s/^ *//" <temp1 >temp2 #formatting (removes spaces)
echo "Gavin:"
awk '$3=="Gavin"{s+=$1}END{print s}' temp2 #adds all the lines together where author=gavin

echo "David:"
awk '$3=="David"{s+=$1}END{print s}' temp2 #same but for david
rm temp1 temp2