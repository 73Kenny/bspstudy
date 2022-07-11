#!/bin/bash

# filename score

echo -e "Please input a score:"

read SCORE

echo -d "You input Score: $SCORE"

if [ $SCORE -lt 60 ]
then
	echo -e "Sorry! You fail the examination."
else
	echo -e "Congratulation! You pass the examination."
fi

echo -e "Press any key to continue"

read $GOOUT
