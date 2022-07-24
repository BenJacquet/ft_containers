#/bin/bash

if [ -s $1 ]
	then
		echo "\033[31mOof! something's wrong, check the logs in ./logs.\033[0m"
	else
		echo "\033[32mAll good\033[0m"
fi