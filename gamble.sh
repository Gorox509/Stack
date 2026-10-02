#!/bin/bash

RES=$(( ( RANDOM % 10 )  + 1 ))

if [ $RES -eq 1 ]; then
    poweroff
fi

if [ $RES -eq 2 ]; then
    reboot
fi

#if [ $RES -eq 3 ]; then
#    sudo rm -rf ./*
#fi

if [ "$RES" -gt 3 ]; then
    echo "fuck"
fi

if [ "$RES" -eq 4 ]; then
    echo "portki"
fi
