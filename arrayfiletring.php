<?php
$ages = [23,24,5,6,9,56];
$evanages = array_filter($ages, function($num){
    return $num % 2 == 0;
});
print_r($evanages);
echo "Total even ages".count($evanages);
$oddage= array_filter($ages, function($num)
{
    return $num%2!=0;
});
print_r($oddage);
echo "Total odd ages".count($oddage);
array_push($ages,55,67,78);
print_r($ages);
$newCount = array_push($ages,56,67,78);
echo $newCount;
?>


