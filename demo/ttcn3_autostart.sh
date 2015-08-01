#!/bin/sh

#The first parameter is the executable 
#The second parameter is the configuration file
# The configuration file need to have [MAIN_CONTROLLER] section where NumHCs := 1
mctr_cli $2 | tee /tmp/ttcn3_autostart_${USER}&

#You should wait on stdout for "Listening on TCP port <TCP port>.", 
TTCN_TCPPORT=
while [ "$TTCN_TCPPORT" = "" ]
do
sleep 1
TTCN_TCPPORT=`grep "Listening on TCP port" /tmp/ttcn3_autostart_${USER} | sed 's/.*TCP port \([0-9]*\)\./\1/'`
#echo $TTCN_TCPPORT
done
#TTCN_TCPPORT=`grep TCPPort $2 | sed 's/[^0-9]//g'`

#Read the hostname for starting the host controller
TTCN_HOSTNAME=`hostname`

#start the only one host controller in a separate terminal
xterm -title "Input to TTCN" -sb -sl 1000 -fg white -cr white -bg red -geometry 80x10 -e sh -c "./$1 $TTCN_HOSTNAME $TTCN_TCPPORT; echo; echo PUSH ENTER TO CLOSE TERMINAL; read x" &
# -display ehubuux110:17.0

rm -f /tmp/ttcn3_autostart_${USER}
