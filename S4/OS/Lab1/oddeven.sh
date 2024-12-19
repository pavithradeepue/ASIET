echo "Enter a number to check whether odd or even: "
read n
if [ $(($n%2)) -eq 0 ]
then
echo "The number is even"
else
echo "The number is odd"
fi
