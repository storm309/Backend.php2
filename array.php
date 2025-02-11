<?php
// check whether an item is present in the cart
$cart = ["bread","jam","peanut","butter"];
echo "Total items".count($cart);
echo "<br>";

foreach($cart as $item){
    echo "$item";
    echo "<br>";
}
if(in_array("egg",$cart)){
    echo "Egg is present";
}
else{
    echo "Egg is not present";
}
// add Egg
array_push($cart, "egg");
print_r($cart);
echo "Total items".count($cart);
$item_name=array_keys($cart);
print_r($item_name);
?>