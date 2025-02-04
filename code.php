// write a php script to check whether a number is integer or not. if it is an integer , print if it is +ve, -ve or 0

<?php
$number = 123; 

if (is_int($number)) {
    if ($number > 0) {
        echo "$number is a positive integer.";
    } elseif ($number < 0) {
        echo "$number is a negative integer.";
    } else {
        echo "$number is zero.";
    }
} else {
    echo "$number is not an integer.";
}

?>