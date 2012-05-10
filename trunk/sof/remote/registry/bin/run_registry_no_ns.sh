#!/bin/sh

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$MICO_HOME/libs
./registry -ORBIIOPAddr inet:localhost:5000 
