#!/bin/sh

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$MICO_HOME/libs
./sof_remote_console  -ORBNamingAddr inet:localhost:5000 $1 $2
