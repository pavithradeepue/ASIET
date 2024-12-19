x=1
while [ $x -eq 1 ]
do
echo "Enter two numbers: "
read a
read b
echo "1.Addition"
echo "2.Substraction"
echo "3.Multiplication"
echo "4.Division"
echo "Enter choise"
read op 
case $op in
1) sum=$(($a+$b))
echo "The sum is $sum";;
2) diff=$(($a-$b))
echo "The difference is $diff";;
3) mul=$(( $a * $b ))
echo "The product is $mul";;
4) div=$(( $a / $b ))
echo "The answer of division is $div";;
5)x=0;;
*) echo "Invalid option";;
esac
done
