#phase 1 iterations. 1/3 of the iterations necessary to reach 
#objective function "stability"
counter=0
# remove old files
rm -f output*

for prob in ft53 ft70 ftv33 ftv35 ftv38 ftv44 ftv47 ftv55 ftv64 ftv70 ftv170 kro124p p43 rbg323 rbg358 rbg403 rbg443 ry48p
do
	fname=output_${prob}.txt
        for i in {1..100}
        do
                ./betATSP ../dsc/tsplib/${prob}.atsp 500 >> ${fname}
        done
done
