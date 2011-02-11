#!/bin/sh

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$MICO_HOME/libs
$MICO_HOME/coss/naming/nsd -ORBIIOPAddr inet:localhost:5000 
