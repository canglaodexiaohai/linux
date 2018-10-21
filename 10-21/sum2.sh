#!/bin/bash

read -p "请输入数字：" n

sum=0
i=0
while (($i<=$n))
do
	sum=$(($sum +$i))
	i=$(($i +1))
done
echo "1-$n的和为：$sum"
