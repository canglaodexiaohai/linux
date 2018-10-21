#!/bin/bash

read -p "请输入数字：" N

sum=0
for ((i=1; i<=$N; i=i+1))
do
	sum=$(($sum +$i))
done
echo "1-$N的和为：$sum"
