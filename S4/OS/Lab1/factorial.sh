echo "Enter a number: "
read n
fact=1
if [ $n -eq 1 -o $n -eq 0 ]
then
echo "The factorial is 1"
else
for (( i=$n;i>0;i-- )) 
do
fact=$((fact * i))
done
echo "The value of factorial is: $fact"
fi

