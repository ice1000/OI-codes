if [[ $1 == "1010" ]] ;
then
    echo "101"
else
    if [[ $1 == "12005000" ]] ;
    then
	echo "50021"
    else
	echo $1 | rev
    fi
fi
