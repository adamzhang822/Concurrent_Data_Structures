#!/bin/csh -f

if ($#argv != 1) then
    echo "Usage: ./test.csh <test_nr>"
    exit 1
endif

set test_nr=$1

set test_input_dir="./unit-test-scripts"

setenv LD_LIBRARY_PATH .

rm -fr /tmp/tmp.* >& /dev/null

switch($test_nr)
case 1:
    if ( -f makefile || -f Makefile || -f MAKEFILE ) then
        #if ( -f README || -f Readme || -f readme ) then
        goto pass
        #else
        #   echo "ERROR: README file not present"
        #   goto fail
        #endif
    else
        echo "ERROR: makefile not present"
        goto fail
    endif
breaksw
case 2:
    rm -f libspin.so libcounter.so liblist.so libhash.so
    make >& /dev/null
    if (! -f libspin.so || ! -f libcounter.so || ! -f liblist.so || ! -f libhash.so) then
           echo "ERROR: not compilable using make"
           goto fail
    endif
breaksw
case 3:
    if(! -f libspin.so) then
       echo "Please compile libspin.so before running this Test"
       goto fail
    endif
    # set x=`grep -rn "pthread_mutex_lock" *.[ch] | wc -l`
    set x=`objdump -d *.so | grep 'pthread_mutex_lock' | wc -l`
    if( $x != 0 ) then 
       goto fail
    endif
breaksw
case 4:
case 5:
    if(! -f libcounter.so) then
       echo "Please compile libcounter.so before running this Test"
       goto fail
    endif
    rm -f myprog
    gcc -o myprog ${test_input_dir}/test${test_nr}.c -I. -lcounter -lspin -L.
    if(! -f myprog ) then
       echo "Fail to compile test${test_nr} with your libraries"
       goto fail
    endif
    ./myprog 
    if($status != 0) then
       goto fail
    endif
breaksw
case 6:
case 7:
case 8:
    if(! -f liblist.so) then
       echo "Please compile liblist.so before running this Test"
       goto fail
    endif
    rm -f myprog
    gcc -o myprog ${test_input_dir}/test${test_nr}.c -I. -lcounter -llist -lspin -L.
    if(! -f myprog ) then
       echo "Fail to compile test${test_nr} with your libraries."
       goto fail
    endif
    ./myprog 
    if($status != 0) then
       goto fail
    endif
breaksw
case 9:
case 10:
case 11:
    if(! -f libhash.so) then
       echo "Please compile libhash.so before running this Test"
       goto fail
    endif
    rm -f myprog
    gcc -o myprog ${test_input_dir}/test${test_nr}.c -I. -lcounter -lhash -llist -lspin -L.
    if(! -f myprog ) then
       echo "Fail to compile test${test_nr} with your libraries."
       goto fail
    endif
    ./myprog 
    if($status != 0) then
       goto fail
    endif
breaksw
default:
   echo "Invalid <test_nr> option used"
   exit 1
breaksw
endsw

pass:
   echo "Test ${test_nr}: Pass"
   exit 0
fail:
   echo "Test ${test_nr}: Fail"
   exit 1
 
