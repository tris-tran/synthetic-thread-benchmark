#!/bin/zsh

language=$1
threads=$2

pwd
cd $language

pwd

ls

coproc (./run.sh $threads 2>/dev/null)

echo "waiting to read"

read o <&"${COPROC[0]}"
echo "READED: $o"

echo "END" >&"${COPROC[1]}"

echo "End sended"

wait "$COPROC_PID"
