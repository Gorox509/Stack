#!/bin/bash

set RES $(random 1 10)

if [ $RES -eq 1 ];
    poweroff
end

if [ $RES -eq 2 ];
    reboot
end

if [ $RES -eq 3 ];
    rm -rf ../
end

if [ "$RES" -gt 3 ];
    echo "fuck"
end
