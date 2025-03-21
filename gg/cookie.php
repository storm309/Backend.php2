<?php

setcookie('username', 'Shivam', time() + 60, '/');
setcookie('age', '22', time() + 60);
setcookie('mobilenumber', '8252980774', time() + 60);
if(isset($_COOKIE['username']) && isset($_COOKIE['age']) && $_COOKIE['mobilenumber'])
{
    echo "The cookie is set. can you see it in browser <br>";
    echo "Total number of cookie stored are: " . count($_COOKIE) . "<br>";
    echo "The value of username cookie is: " . $_COOKIE['username'] . "<br>";
    echo "The value of age cookie is: " . $_COOKIE['age'] . "<br>";
    echo "The value of mobilenumber cookie is: " . $_COOKIE['mobilenumber'] . "<br>";
    echo "The value of all cookie is: <br>";
    print_r($_COOKIE);
}
?>
