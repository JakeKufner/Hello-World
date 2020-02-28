#!/bin/bash
echo username is:
read user
ssh bandit.labs.overthewire.org -p 2220 -l $user
