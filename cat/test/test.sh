#!/bin/bash

BRIGHT_RED='\033[1;31m'
BRIGHT_GREEN='\033[1;32m'
BRIGHT_BLUE='\033[1;34m'
RESET='\e[0m'

COUNTER_SUCCES=0
COUNTER_FAIL=0
REZ_DIFF=""

S21_CAT="../s21_cat"
FILE1="test1.txt"
FILE2="test2.txt"
FILE3="test3.txt"
FILE4="test4.txt"

>log_cat.txt

echo -e "${BRIGHT_BLUE}ЗАПУСКАЕМ ТЕСТИРОВАНИЕ${RESET}"

#Flags -b
TEST_B="-b $FILE1 $FILE2 $FILE3 $FILE4"
$S21_CAT $TEST_B > s21.txt 2>&1
cat $TEST_B > cat.txt 2>&1
REZ_DIFF="$(diff -b s21.txt cat.txt)"
if [ "$REZ_DIFF" == "" ];
then
    ((COUNTER_SUCCES++))
    echo -e "${BRIGHT_GREEN} -b flag = SUCCES${RESET}"

else 
    ((COUNTER_FAIL++))
    echo -e "${BRIGHT_RED} -b flag = FAIL${RESET}"
    diff -b -C 2 cat.txt s21.txt >> log_cat.txt

    

fi
rm s21.txt cat.txt


#Flags -n 
TEST_B="-n $FILE1 $FILE2 $FILE3 $FILE4"
$S21_CAT $TEST_B > s21.txt 2>&1
cat $TEST_B > cat.txt 2>&1
REZ_DIFF="$(diff -b s21.txt cat.txt)"
if [ "$REZ_DIFF" == "" ];
then
        ((COUNTER_SUCCES++))
          echo -e "${BRIGHT_GREEN} -n flag = SUCCES${RESET}"

else 
        ((COUNTER_FAIL++))
         echo -e "${BRIGHT_RED} -n flag = FAIL${RESET}"
         diff -b -C 2 cat.txt s21.txt >> log_cat.txt

fi
rm s21.txt cat.txt

#Flags -s 
TEST_B="-s $FILE1 $FILE2 $FILE3 $FILE4"
$S21_CAT $TEST_B > s21.txt 2>&1
cat $TEST_B > cat.txt 2>&1
REZ_DIFF="$(diff -b s21.txt cat.txt)"
if [ "$REZ_DIFF" == "" ];
then
        ((COUNTER_SUCCES++))
          echo -e "${BRIGHT_GREEN} -s flag = SUCCES${RESET}"

else 
        ((COUNTER_FAIL++))
         echo -e "${BRIGHT_RED} -s flag = FAIL${RESET}"
         diff -b -C 2 cat.txt s21.txt >> log_cat.txt

fi
rm s21.txt cat.txt


#Flags -v 
TEST_B="-v $FILE1 $FILE2 $FILE3 $FILE4"
$S21_CAT $TEST_B > s21.txt 2>&1
cat $TEST_B > cat.txt 2>&1
REZ_DIFF="$(diff -b s21.txt cat.txt)"
if [ "$REZ_DIFF" == "" ];
then
        ((COUNTER_SUCCES++))
          echo -e "${BRIGHT_GREEN} -v flag = SUCCES${RESET}"

else 
        ((COUNTER_FAIL++))
         echo -e "${BRIGHT_RED} -v flag = FAIL${RESET}"
         diff -b -C 2 cat.txt s21.txt >> log_cat.txt

fi
rm s21.txt cat.txt


#Flags -t
TEST_B="-n $FILE1 $FILE2 $FILE3 $FILE4"
$S21_CAT $TEST_B > s21.txt 2>&1
cat $TEST_B > cat.txt 2>&1
REZ_DIFF="$(diff -b s21.txt cat.txt)"
if [ "$REZ_DIFF" == "" ];
then
        ((COUNTER_SUCCES++))
          echo -e "${BRIGHT_GREEN} -t flag = SUCCES${RESET}"

else 
        ((COUNTER_FAIL++))
         echo -e "${BRIGHT_RED} -t flag = FAIL${RESET}"
         diff -b -C 2 cat.txt s21.txt >> log_cat.txt

fi
rm s21.txt cat.txt


#Flags -e 
TEST_B="-e $FILE1 $FILE2 $FILE3 $FILE4"
$S21_CAT $TEST_B > s21.txt 2>&1
cat $TEST_B > cat.txt 2>&1
REZ_DIFF="$(diff -b s21.txt cat.txt)"
if [ "$REZ_DIFF" == "" ];
then
        ((COUNTER_SUCCES++))
          echo -e "${BRIGHT_GREEN} -e flag = SUCCES${RESET}"

else 
        ((COUNTER_FAIL++))
         echo -e "${BRIGHT_RED} -e flag = FAIL${RESET}"
         diff -b -C 2 cat.txt s21.txt >> log_cat.txt

fi
rm s21.txt cat.txt



