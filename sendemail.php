<?php
$to = "rajranjan707077@gmail.com";
$from = "shivamkumarp447@gmail.com";
$subject = "Checking PHP mail";
$message = "PHP mail works just fine";
if(mail($to,$subject,$message,"From: $from\n")){
    echo "Email sent successfully";
} else {
    echo "Email sending failed";
}
?>
