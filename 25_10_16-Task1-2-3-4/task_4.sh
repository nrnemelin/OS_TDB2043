echo -n "Enter two numbers (with a space): "
read a b
temp=$a
a=$b
b=$temp
echo "after swapping: " $a $b

