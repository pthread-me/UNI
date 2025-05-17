#!/bin/bash

for i in $(seq 1 40); do
	addr6 -A 2001::/16 -f >> addr.txt
done
