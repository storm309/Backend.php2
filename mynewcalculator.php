<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>My Calculator</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <form  method="POST" action=""> 
        <label for="num1">Enter 1st Num: </label>
        <input type="number"
        placeholder="Enter the num"
        name="num1" required>
        <br>
        <label for="num2">Enter 2nd Num: </label>
        <input type="number"
        placeholder="Enter the num"
        name="num2" required>
        <br>
        <input type="Submit" name="ADD" value="+">
        <input type="Submit" name="SUB" value="-">
        <input type="Submit" name="MUL" value="*">
        <input type="Submit" name="DIV" value="/">
        <input type="Submit" name="MOD" value="%">
        <input type="Submit" name="EXP" value="**">
    </form>
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
</body>
</html>