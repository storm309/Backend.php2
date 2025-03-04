<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
    <form action="#" method="POST">
        <label for="url">Enter URL of the Video</label> <br>
        <input type="url" name="url" placeholder="Enter the URL"> <br>
         <textarea name="des" placeholder="Enter the description"></textarea> <br>
        <button type="submit" name="sub">Submit</button>
    </form>

    <?php
    if($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $url = $_POST["url"];
        $url = filter_var($url, FILTER_SANITIZE_URL);
        $des = $_POST["des"];
        $des = filter_var($des, FILTER_SANITIZE_STRING);
        if(isset($_POST["sub"]))
        {
            if(filter_var($url, FILTER_VALIDATE_URL))
            {
                if(strlen($des) > 20)
                {
                    echo "<h3> The video description must be less than 20 charecters. </h3>";
                }
                else
                {
                    echo "<h3> Your URL is successfully submitted. </h3>";
                }
            }
            else
            {
                echo "<h3> The video URL is not valid. </h3>";   
            }
        }
    }
    ?>
</body>
</html>