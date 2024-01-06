#!/bin/sh

threads=$1

exec cargo r $threads
