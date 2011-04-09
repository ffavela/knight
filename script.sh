#! /bin/bash
for i in $(seq 1 8)
	do
		for j in $(seq 1 8)
			do
				./knight $i $j
				echo ""
			done
	done
