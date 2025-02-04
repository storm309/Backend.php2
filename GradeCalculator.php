<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Result</title>
    <style>
        body{
            background-color:rgb(11, 197, 225);
            text-align: center;
        }
    </style>
</head>
<marquee behavior="scroll" direction="left">Welcome to the Student Grade Calculator!</marquee>
    <h1 >STUDENT GRADE CALCULATOR</h1>
    <form action="GradeCalculator.php" method="post">
    <div>
        <label for="english">Enter the marks in English:</label>
        <input type="number" id="english" name="english" required>
    </div>
    <div>
        <label for="maths">Enter the marks in Maths:</label>
        <input type="number" id="maths" name="maths" required>
    </div>
    <div>
        <label for="socialScience">Enter the marks in Social Science:</label>
        <input type="number" id="socialScience" name="socialScience" required>
    </div>
    <div>
        <label for="hindi">Enter the marks in Hindi:</label>
        <input type="number" id="hindi" name="hindi" required>
    </div>
    <div>
        <label for="science">Enter the marks in Science:</label>
        <input type="number" id="science" name="science" required>
    </div>
    <div>
        <button type="submit">Submit</button>
    </div>
    
</form>
    
<body>
<h1> Result </h1>
<?php

// VERIFY THE SERVER REQUEST METHOD
if($_SERVER['REQUEST_METHOD'] == 'POST') {
    if(isset($_POST['CalGrade'])){
$s1=$_POST['english'];    
$s2=$_POST['maths'];
$s3=$_POST['socialscience'];
$s4=$_POST['hindi'];
$s5=$_POST['science'];
$sum=$s1+$s2+$s3+$s4+$s5;
$tot_marks=500;
$per=($sum/$tot_marks)*100;
echo "<h1> The Percentage is: $per </h1";
echo "<br>";
if($per>=90  && $per<=100)
{
    echo "Grade O";
}
else if($per>=80 && $per<90)
{
    echo "Grade A";
}
else if($per>=70 && $per<80)
{
    echo "Grade B";
}
else if($per>=60 && $per<70)
{
    echo "Grade C";
}
else if($per>=40 && $per<60)
{
    echo "Grade D";
}
else
{
    echo "Grade F";
}
    
    }
} 

// $s1=readline("Enter the marks in English:-");
// $s2=readline("Enter the marks in Maths:-");
// $s3=readline("Enter the marks in Social Science:-");
// $s4=readline("Enter the marks in Hindi:-");
// $s5=readline("Enter the marks in Science:-");

$s1=$_POST['english'];
$s2=$_POST['maths'];
$s3=$_POST['socialScience'];
$s4=$_POST['hindi'];
$s5=$_POST['science'];

$sum=$s1+$s2+$s3+$s4+$s5;
$tot_marks=500;
$per=($sum/$tot_marks)*100;
echo "The Percentage is: ".number_format($per,2)."<br>";
echo "\n";
if($per>=90  && $per<=100)
{
    echo "Grade O";
}
else if($per>=80 && $per<90)
{
    echo "Grade A";
}
else if($per>=70 && $per<80)
{
    echo "Grade B";
}
else if($per>=60 && $per<70)
{
    echo "Grade C";
}
else if($per>=40 && $per<60)
{
    echo "Grade D";
}
else
{
    echo "Grade F";
}
?>
</body>
</html>