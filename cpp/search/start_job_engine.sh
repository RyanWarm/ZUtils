#!/bin/bash

PID_BASE=21000
BASE_DIR=/usr/local/job_search_engine/
SEARCH_BIN=$BASE_DIR/job_search_engine_prod

pushd $BASE_DIR
pid_list=""
for i in `seq 0 0`;
do
    port=$(($PID_BASE+$i))
    $SEARCH_BIN --port $port --index-dir /ram/job_index/ --server-type job --company-score-file conf/company_score &
    pid_list="$pid_list $!"
done 
echo "All partition started"

while [ 1 ]
do
    for pid in $pid_list
    do
        kill -URG $pid
        if [ $? -ne 0 ]
        then
            for pid in $pid_list
            do
                kill $pid
            done
            echo "Some partitions are down. For all exit."
            exit
        else
            continue
        fi
    done
    sleep 1
done


