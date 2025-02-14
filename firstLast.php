<?php
// Sample array
$array = [1, 2, 3, 4, 5];

// Check if the array is not empty
if (!empty($array)) {
    // Get the first element
    $firstElement = $array[0];
    
    // Get the last element
    $lastElement = $array[count($array) - 1];
    
    // Output the results
    echo "First element: " . $firstElement . "\n";
    echo "Last element: " . $lastElement . "\n";
} else {
    echo "The array is empty.";
}
?>