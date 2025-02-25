<?php
// function change_name($nm){
//     echo "Inirially the name is $nm \n";
//     $nm = $nm."_new";
//     echo "This function changes the name to $nm \n";
// }
// $name = "John";
// echo "My name is $name \n";
// change_name($name);
// echo "My name is still $name \n";

//

// function say()
// {
//     echo "Hello world!.<br>";
// }
// $function_holder = "say";
// function_holder();

//
// function my_callback($item){
//     return strlen($item);
// }
// $strings = ["apple","orange","banana","coconut"];
// $lengths = array_map("my_callback",$strings);
// print_r($lengths);

//
// function multiply(...$numbers){
//     $result = 1;
//     foreach($numbers as $num){
//         $result *= $num;
//     }
//     return $result;
// }
// echo "nultiplication of 2,3,4 is ".multiply(2,3,4)."<br>";
// echo "nultiplication of 2,3,4,5 is ".multiply(2,3,4,5)."<br>";

//
$age = array("Peter"=>35, "Ben"=> 37, "Joe"=>25);
$var = json_encode($age);
echo $var . "<br>";
$jsonobj = '{"Raj":99, "Raushan":83, "Akash":57}';
var_dump(json_decode($var));
echo "<br>";
var_dump(json_decode($jsonobj));

?>
