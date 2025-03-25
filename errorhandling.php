<?php
if (file_exists("errorhandling.php")) {
    include("errorhandling.php");

    $file = fopen("errorhandling.php", "r"); // Open the file for reading

    if ($file) {
        while (!feof($file)) { // Check if end of file is reached
            echo fgets($file) . "<br>"; // Read and display each line
        }
        fclose($file); // Close the file after reading
    } else {
        echo "Failed to open the file.";
    }
} else {
    echo "The file does not exist.";
}
?>
