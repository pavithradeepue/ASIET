echo "Enter the number for Palindrome check: "
read num
number=$num
rev=0
while [ $number -gt 0 ]
do
n=$(($number%10))
rev=$(($rev*10+$n))
number=$(($number/10))
done
if [ $num -eq $rev ]
then 
echo "Number is palindrome"
else
echo "Number is Not palindrome"
fi
