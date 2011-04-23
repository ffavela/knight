#! /bin/bash
for i in $(seq 1 5)
	do
		for j in $(seq 1 5)
			do
				./knight $i $j | tee  knight.$i.$j.txt
				echo ""
			done
	done
