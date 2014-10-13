make gen
make B_pai
make B_re
$i
while [ true ]
do
	echo $((i=i+1))
	./gen > B.in
	./B_pai < B.in > B_pai.out
	./B_re < B.in > B_re.out
	if ! diff B_pai.out B_re.out
	then
		echo Wrong
		break
	fi
done
