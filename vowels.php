<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Check Vowels</title>
</head>
<body>
    <form action="" method="post">
        <label for="Str">Enter the String</label> 
        <input type="text" name="Str" id="Str" placeholder="Enter the String" required>
        <button type="submit">Check for Vowels</button> 
        <button type="reset">Reset</button> 
        <br> <br>
    </form>

<?php
if($_SERVER["REQUEST_METHOD"] == "POST")
{
    $string = $_POST["Str"];
    $count = 0;
    $string = strtolower($string);
    
    for($i = 0; $i < strlen($string); $i++)
    {
        if(in_array($string[$i], ['a', 'e', 'i', 'o', 'u']))
        {
            $count++;
        }
    }
    echo "The String: $string <br>";
    echo "The total number of vowels in the string: $count"; 
}
?>
</body>
</html>


