#!/bin/bash
xcode_path=/Users/noprom/Documents/Dev/C++/Complier/java_complier/java_complier
vs_path=/Users/noprom/Downloads/VBShare/Complier/java_complier_vs2/java_complier/java_complier

if [[ $# -ne 1 ]];
then
    echo "`basename ${0}`:usage: [1: xcode to vs] | [2: vs to xcode]"
	exit 1
fi
option=$1
if [ ${option} == '1' ];
    then
    	cp ${xcode_path}/App.java ${vs_path}
    	cp ${xcode_path}/globals.h ${vs_path}
		cp ${xcode_path}/util.h ${vs_path}
		cp ${xcode_path}/util.cpp ${vs_path}
		cp ${xcode_path}/lexer.h ${vs_path}
		cp ${xcode_path}/lexer.cpp ${vs_path}
		cp ${xcode_path}/main.cpp ${vs_path}
elif [ ${option} == '2' ]
	then
		cp ${vs_path}/App.java ${xcode_path}
		cp ${vs_path}/globals.h ${xcode_path}
		cp ${vs_path}/util.h ${xcode_path}
		cp ${vs_path}/util.cpp ${xcode_path}
		cp ${vs_path}/lexer.h ${xcode_path}
		cp ${vs_path}/lexer.cpp ${xcode_path}
		cp ${vs_path}/main.cpp ${xcode_path}
fi