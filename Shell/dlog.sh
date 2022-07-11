#!/bin/bash
# filename flog

LOG="/home/ts/Kenny/Shell/log"

if [ ! -f $LOG ]
then
	touch $LOG
fi

echo -e "dlog:`date`" >> $LOG
exit 0
