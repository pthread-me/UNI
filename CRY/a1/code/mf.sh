#!/bin/bash
letters=('a' 'b' 'c' 'd' "e" "f" "g" "h" "i" "j" "k" "l" "m" "n" "o" "p" "q" "r" "s" "t" "u" "v" "w" "x" "y" "z")

for i in ${letters[@]}; do
	grep -i "^.$i$i$" words.txt | tee -a possible.txt 
done
