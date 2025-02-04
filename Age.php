<!DOCTYPE html>

<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
<form action="" method="POST">
        Enter the Age: <input type="number"
        placeholder="Enter any Age" name = "num">
        <br>
        <br>
        <button type="submit" name="checkInt"> CHECK IF 
            IT IS NUMBER</button>
<?php

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    if (isset($_POST['checkInt'])) {
        $num = (int) $_POST['num'];
        if (filter_var($num, FILTER_VALIDATE_INT) !== false) {
            if ($num >= 18) {
                echo "<h1 style='color:blue'>You are eligible for Voting</h1>";
            } else if ($num < 18){
                echo "<h1 style='color:green'>You are not eligible for Voting</h1>";
            } else if ($num > 100) {
                echo "<h1 style='color:red'>You are in RED ZONE</h1>";
        }
    }
}
}
?>
 </form>
</body>
</html>