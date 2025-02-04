<?php
// Verify the server request method
if($_SERVER["REQUEST_METHOD"]=="POST"){ // super global server
    $num1=$_POST["num1"];
    $num2=$_POST["num2"];
    if(isset($_POST["ADD"])){
        $result=$num1+$num2;
        echo "<h1> The result is $result </h1>";
    }
    else if(isset($_POST["SUB"])){
        $result=$num1-$num2;
        echo "<h1> The result is $result </h1>";
   }
   else if(isset($_POST["MUL"])){
    $result=$num1*$num2;
    echo "<h1> The result is $result </h1>";
   }
   else if(isset($_POST["DIV"])){
    $result=$num1/$num2;
    echo "<h1> The result is $result </h1>";
   }
   else if(isset($_POST["MOD"])){
    $result=$num1%$num2;
    echo "<h1> The result is $result </h1>";
   }
   else if(isset($_POST["EXP"])){
    $result=$num1**$num2;
    echo "<h1> The result is $result </h1>";
   }
}
?>