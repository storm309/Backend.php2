<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Leap Year Checker</title>
    <style>
        body{
            background-color:rgb(11, 197, 225);
            text-align: center;
        }

    </style>
</head>
<body>
<marquee behavior="scroll" direction="left">Welcome to the Leap Year Check Portal!</marquee>
    Enter any Year: 
    <form action="LeapYear.php" method="post">
    <input type="number" name="year" 
    placeholder="Enter any Year" required>
    <br>
    <button type="submit" name="checkleap" > CHECK FOR LEAP YEAR </button>
    <!-- // verify the server request method -->
    <?php
    if($_SERVER['REQUEST_METHOD'] == 'POST'){
        if(isset($_POST['checkleap'])){
            $year = $_POST['year'];
            
        // take the year as an input and pass it with post method
        $year = $_POST['year'];
            if(($year%400==0) || ($year%100!=0 && $year%4==0)){
                echo "<h1 style='color:green'> The year is a leap year </h1>";
            }else{
                echo "<h1 style='color:red'> The year is not a leap year </h1>";
        }
    }
}
        ?>
    </form>
</body>
</html>