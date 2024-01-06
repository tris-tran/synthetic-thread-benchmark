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

echo "+++++++++++++++++++++"
cat /proc/$pid/status
echo "+++++++++++++++++++++"

echo "+++++++++++++++++++++"
ps -p "$pid" -o %cpu,%mem,cmd
echo "+++++++++++++++++++++"
ps -T -p "$pid"
echo "+++++++++++++++++++++"

read -p "Finish messurements"

echo "END" >&"${COPROC[1]}"
echo "End sended"

wait "$COPROC_PID"
