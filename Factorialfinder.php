<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Factorial Finder</title>
</head>
<body>
    <form action="" method="post">
        <label for="no">Enter the number</label>
        <input type="number" name="no" placeholder="Enter the Number"> <br>
        <input type="submit" name="sub" value="Click to find the Factorial">
    </form>

    <?php

    if($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if(isset($_POST["sub"]))
        {
            $n = intval($_POST["no"]);

            function factorial($n)
            {
                if($n == 0 || $n == 1)
                {
                    return 1;
                }
                else
                {
                    return $n * factorial($n - 1);
                }
            }

            echo "<h1>The Factorial of $n is " . factorial($n) . "</h1><br>";
            
        }
    }

    ?>
    
</body>
</html> 
