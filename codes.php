<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Check INT</title>
</head>
<body>
    <form action="" method="POST">
        Enter the Integer: <input type="number"
        placeholder="Enter any value" name = "num">
        <br>
        <br>
        <button type="submit" name="checkInt"> CHECK IF 
            IT IS INTEGER</button>
    </form>
    <?php
    // verify the server request method
    if($_SERVER['REQUEST_METHOD'] == 'POST'){
    if(isset($_POST['checkInt'])){
        $num=(int) $_POST['num'];
        if(filter_var($num, FILTER_VALIDATE_INT)!== false){
            if($num==0){
                echo " <h1 style= 'color:blue'>The value is zero </h1>";
            }elseif($num>0){
                echo " <h1 style= 'color:green'>The value is positive </h1>";
    }
}
    }
    }
    ?>
</body>
</html>