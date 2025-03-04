<?php

// $str = "<h1> This is a String </h1>";
// echo filter_var($str, FILTER_SANITIZE_STRING) . "<br>";

$email = "@Rajemail.com";
if(filter_var($email, FILTER_VALIDATE_EMAIL))
{
    echo "email $email is valid <br>";
}
else
{
    echo "email $email is not valid <br>";
}

echo "<br><br>";

$ip = "275.255.255.255";
if(filter_var($ip, FILTER_VALIDATE_IP))
{
    echo "ip $ip is valid <br>";
}
else
{
    echo "ip $ip is not valid <br>";
}

echo "<br><br>";

$url = "https://www.invalidwebsite..com";
if(filter_var($url, FILTER_VALIDATE_URL))
{
    echo "url $url is valid <br>";
}
else
{
    echo "url $url is not valid <br>";
}

?>