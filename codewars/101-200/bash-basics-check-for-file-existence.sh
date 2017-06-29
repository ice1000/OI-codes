#!/bin/bash

if [[ $1 == "" ]]
then
		echo Nothing to find
else if [[ ! -f $1 ]] ;
		 then
				 echo "Can't find $1"
		 else
				 echo "Found $1"
		 fi
fi
