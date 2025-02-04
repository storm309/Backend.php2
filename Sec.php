<?php
$s1=readline("Enter the marks in 1st subjects ");
$s2=readline("Enter the marks in 2nd subjects ");
$s3=readline("Enter the marks in 3rd subjects ");
$s4=readline("Enter the marks in 4th subjects ");
$s5=readline("Enter the marks in 5th subjects ");

$tot_marks=500;
$sum=$s1+$s2+$s3+$s4+$s5;
$per = ($sum/$tot_marks)*100;
echo "The per is ".number_format($per,1);

?>