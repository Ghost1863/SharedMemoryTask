#!/bin/bash

gcc -o write_shared src/write_shared.c
if [ $? -ne 0 ]; then
    echo "Failed to compile write_shared.c"
    exit 1
fi

gcc -o read_shared src/read_shared.c
if [ $? -ne 0 ]; then
    echo "Failed to compile read_shared.c"
    exit 1
fi

./write_shared | ./read_shared
if [ $? -ne 0 ]; then
    echo "Failed to run programs"
    exit 1
fi

rm -f write_shared read_shared