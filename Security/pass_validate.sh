#!/bin/bash
#created by Michael Rogers


echo 'Please enter the password: '
read pass;

if [[ ${#pass} -lt 8 ]]; then
	echo 'Password is less than 8 characters.'
elif [[ ! $pass =~ [0-9] ]]; then
	echo 'Password does not contain a number.'
elif [[ ! $pass =~ [@#$%'&'+-=] ]]; then
	echo 'Password does not contain a non-alphabetic character.'
else
	echo 'Password contains a minimum of 8 characters, at least one number, and
	at least one non-alphabetic character. All tests passed.'
fi
