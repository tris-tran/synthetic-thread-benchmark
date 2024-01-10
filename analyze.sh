#!/bin/zsh

language=$1
threads=$2

cd $language
pwd

coproc (./run.sh $threads)

echo "waiting to read"

read o <&"${COPROC[0]}"
echo "READED: $o"

echo "PID: ${COPROC_PID}"
pid="${COPROC_PID}"

echo "Commands to take mesurements ensure all threads are running"

echo "ps -p \"$pid\" -o %cpu,%mem,cmd"
echo "ps -T -p \"$pid\""
echo "cat /proc/$pid/status"

read -p "Finish messurements"

echo "END" >&"${COPROC[1]}"
echo "END" >&"${COPROC[1]}"
echo "End sended"

time wait "$COPROC_PID"
