<?php

if($_SERVER["REQUEST_METHOD"] == "POST")
{
    if(isset($_POST["submitform"]))
    {
        $user = $_POST["uname"];
        $email = $_POST["email"];
        $mno = $_POST["mno"];
        $add = $_POST["add"];

        $nameerror = "";

        if(empty($user))
        {
            $nameerror = "User name cannot be left blank";
            echo "<h4 style = 'color:red'> $nameerror </h4><br>";
        }
        else
        {
            if(!preg_match('/^[A-Za-z0-9_]*$/',$user))
            {
                $nameerror = "Username is not vaild";
                echo "<h4 style = 'color:red'> $nameerror </h4><br>";
            }
            else
            {
                echo "<h4 style = 'color:green'>The Username is $user </h4><br>";
            }
        }


        if(empty($email))
        {
            $nameerror = "email feild cannot be left blank";
            echo "<h4 style = 'color:red'> $nameerror </h4><br>";
        }
        if(empty($mno))
        {
            $nameerror = "Mobile number cannot be left blank";
            echo "<h4 style = 'color:red'> $nameerror </h4><br>";
        }
        if(empty($add))
        {
            $nameerror = "Address field cannot be left blank";
            echo "<h4 style = 'color:red'> $nameerror </h4><br>";
        }
    }
}

?>