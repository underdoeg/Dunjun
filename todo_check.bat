@echo off

set Wildcard=*.hpp *.cpp

echo -------------------------------------------------------------------------------
echo TODOS FOUND:
echo -------------------------------------------------------------------------------
findstr -s -n -i -l "TODO" %Wildcard%
echo -------------------------------------------------------------------------------