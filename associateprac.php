<?php
$products = ['Laptop'=>2000, 'Tablet'=>600,
'Smartphone'=>900, 'Desktop'=>900];
print_r($products);
krsort($products);
print_r($products);
echo "The prizes in Asc order";
asort($products);
print_r($products);
echo "The max prize is " . max($products) . "\n";
$max_value = max($products);
$max_product = array_search($max_value, $products);
$min_value = min($products);
$min_product = array_search($min_value, $products);
echo "The max product is " . $max_product . " with prize " . $max_value . "\n";
echo "The min product is " . $min_product . " with prize " . $min_value . "\n";
?>