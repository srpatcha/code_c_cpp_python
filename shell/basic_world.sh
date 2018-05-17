#!/bin/bash -xv 
#this is shell_script.sh  shell script to run linux mutiple linux commands

#helps to Exit immediately if a command exits 
set -e

#helps to print all commands
set -o xtrace  

read word 
echo ""Hello" world \$word"
word="shell script"
echo "hello world \$word"

echo "hell world text file " > "${word}_hellowrd.txt"
echo * 


for i in 9 2 3 4 5 6
do
   # -e prints like  new line wild  charecter
   echo  "a quote is already getting up to move ahead";
done



for i in hello 1*2 goodbye
  do
    echo "hello ranga is is set to $i"
  done

#helps to print commands-x and +x will reset
set -x  
#export globle environment  . ./shell_script.sh 
# $unset HERO
export HERO="SRIKANTH"
echo "hero is ${HERO}"

#new Line print ways 
printf "hello\nworld\n"
echo  $'hello\nworld\n'
echo -e "Hello \nworld\n";

set +x

echo "Home folder location:/home/$(whoami)"
# echo "Listing home fodler files : $(ls ~/)"
