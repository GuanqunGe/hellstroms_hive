#! /bin/bash

echo "Finish!!!!!!!!!!!" >> ./record.txt 2>&1
now=$(date +"%T")
echo "Current time : $now"
echo "-------------------------------------------------------------------------------------------" >> ./record.txt 2>&1
echo "Now runs app -var:" | tee -a ./record.txt 
./eLEE -x box_copy.xml -o var #>> ./record.txt 2>&1


echo "Finish!!!!!!!!!!!" >> ./record.txt 2>&1
now=$(date +"%T")

echo "-------------------------------------------------------------------------------------------" >> ./record.txt 2>&1
echo "Now runs -r -o datamc :" | tee -a ./record.txt 
./eLEE -x box_copy.xml -r -o datamc >> ./record.txt 2>&1

echo "Finish!!!!!!!!!!!" >> ./record.txt 2>&1
now=$(date +"%T")
echo "Current time : $now"
echo "-------------------------------------------------------------------------------------------" >> ./record.txt 2>&1
echo "Now runs -o sig:" | tee -a ./record.txt 
./eLEE -x box_copy.xml -o sig  >> ./record.txt 2>&1

echo "Finish!!!!!!!!!!!" >> ./record.txt 2>&1
now=$(date +"%T")
echo "Current time : $now"


echo "-------------------------------------------------------------------------------------------" >> ./record.txt 2>&1
echo "Now runs -o stack :" | tee -a ./record.txt 
./eLEE -x box_copy.xml -o stack -n '0'>> ./record.txt 2>&1

echo "Finish!!!!!!!!!" >> ./record.txt 2>&1
now=$(date +"%T")
echo "Current time : $now"
echo "-------------------------------------------------------------------------------------------" >> ./record.txt 2>&1
echo "Now runs -o datamc --number :" >> ./record.txt 2>&1
./eLEE -x box_copy.xml -o datamc -n '0' >> ./record.txt 2>&1

echo "Finish!!!!!!!!!!!" >> ./record.txt 2>&1
now=$(date +"%T")
echo "Current time : $now"
echo "-------------------------------------------------------------------------------------------" >> ./record.txt 2>&1
echo "Now runs -o response :" >> ./record.txt 2>&1
./eLEE -x box_copy.xml -o response >> ./record.txt 2>&1

echo "Finish!!!!!!!!!!!" >> ./record.txt 2>&1
now=$(date +"%T")
echo "Current time : $now"
echo "-------------------------------------------------------------------------------------------" >> ./record.txt 2>&1
echo "Now runs -o recomc :" >> ./record.txt 2>&1
./eLEE -x box_copy.xml -o recomc -n '2'>> ./record.txt 2>&1
echo "Finish!!!!!!!!!!!" >> ./record.txt 2>&1
now=$(date +"%T")
echo "Current time : $now"
echo "-------------------------------------------------------------------------------------------" >> ./record.txt 2>&1
echo "Now runs -o eff:" >> ./record.txt 2>&1
./eLEE -x box_copy.xml -o eff>> ./record.txt 2>&1

