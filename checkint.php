<?php
// $a=10;
// $b=29.5;
// if(is_int($a)){
//     echo "The num is int ";
// }

// else{
//     echo "The num is not int ";
// }
// if(is_float($b)){
//     echo "The num is float ";
// }
// else{
//     echo "The num is not float ";
// }
// ECHO (PI());
echo(number_format(pi(),2));
echo(min(0,150,30,-8,-29) ."<br>");
echo(max(0,150,30,-8,-29) ."<br>");
echo(abs(-6.7)."\n");
echo(sqrt(0)."\n");
echo(sqrt(1));

$name = "Shivam is a good boy ";
echo $name;
echo "<br>";
echo "The length of " . "my string is " . strlen($name);
echo "<br>";
echo strrev($name); // reverse the string
echo "<br>";
echo strpos($name,"Shivam");
?>