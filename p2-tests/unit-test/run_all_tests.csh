#!/bin/csh -f

set i=1
set max_test_nr=11
set total=0
set max_total=0
set grade_file=test_output.txt
set score=(1 1 1 1 1 1 1 1 1 1 1)

if (-e ${grade_file}) then
    rm -f ${grade_file}
endif
echo "" > ${grade_file}
echo "**************" >> ${grade_file}
echo " Test results " >> ${grade_file}
echo "**************" >> ${grade_file}
echo "" >> ${grade_file}
echo "" >> ${grade_file}


setenv LD_LIBRARY_PATH .

#while (${i} <= `expr ${max_test_nr} - 3` )
while (${i} <= `expr ${max_test_nr}` )
    ./test.csh $i
    if ($status != 0) then
       echo "Test ${i}: 0 / $score[$i]" >> ${grade_file}
    else
       echo "Test ${i}: $score[$i] / $score[$i]" >> ${grade_file}
       set total=`expr ${total} + $score[$i]`
    endif
    set max_total=`expr ${max_total} + $score[$i]`
    set i=`expr ${i} + 1`
end


echo "" >> ${grade_file}
echo "" >> ${grade_file}
echo "------------------" >> ${grade_file}
echo "Total  : ${total} / ${max_total} " >> ${grade_file}
echo "------------------" >> ${grade_file}
rm -fr /tmp/tmp.* >& /dev/null

