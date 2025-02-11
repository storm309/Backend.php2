<?php

// $age = [22, 56, 48, 20, 78, 66, 45, 95, 71, 23, 65];
// $evenage = array_filter($age, function($num){
//     return $num % 2 == 0;
// });

// print_r($evenage);
// echo "<br>";
// echo "Total Number of even ages are: ". count($evenage);
// echo "<br>";

// $oddage = array_filter($age, function($num){
//     return $num % 2 != 0;
// });

// print_r($oddage);
// echo "<br>";
// echo "Total Number of odd ages are: ". count($oddage);
// echo "<br>";

// $primeage = array_filter($age, function($num){
//     $count = 0;
//     for($i=2;$i<$num;$i++)
//     {
//         if($num % $i == 0)
//         {
//             $count++;
//         }
//     }
//     if($count == 0)
//     {
//         return $num;
//     }
// });

// print_r($primeage);
// echo "<br>";
// echo "Total Number of prime ages are: ". count($primeage);
// echo "<br>";



// array_push($age, 31, 7, 11, 59);
// print_r($age);
// echo "<br>";

// $name = array("Raj", "Raushan", "Akash", "Ankit", "Rohit");
// $marks = array(99, 88, 77, 66, 55);
// echo "<br>";

// $c = array_combine($name, $marks);
// print_r($c);
// echo "<br>";

// print_r(array_chunk($c, 1));
// echo "<br>";

// $a1 = array("a" => "Red", "b" => "Green", "c" => "Pink", "d" => "White", "e" => "Blue");
// $a2 = array("a" => "Red", "b" => "Black", "c" => "Aqua", "d" => "Purple");
// $a3 = array("a" => "Red", "b" => "Magenta", "c" => "Lavender");

// print_r(array_intersect($a1, $a2, $a3));
// echo "<br>";

$str = "This is some sample text";
print_r(explode(" ", $str));
echo "<br>";

$arr = array("Course", "code", "is", "INT220");
print_r(implode(" ", $arr));
echo "<br>";
?>