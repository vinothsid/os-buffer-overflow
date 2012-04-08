
#i=0;
#for s in 49 c7 c6 d4 0e 60 00 49 c7 c7 42 00 00 00 4d 89 3e
#do
#		
#	echo "attackB[$i] = 0x$s;"
#	#echo "dump[$i] = 0x$s;"
#	i=$(expr $i '+' 1);
#done

i=6
for s in c6 04 25 a4 0d 60 00 42 e9 41 fa df ff ff
do

        #echo "attackB[$i] = 0x$s;"
        echo "attackB[$i] = 0x$s;"
        #echo "dump[$i] = 0x$s;"
        i=$(expr $i '+' 1);
done

