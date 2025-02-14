<?php
// $array1 = array("apple", "banana", "cherry");
// $array2 = array("date", "elderberry", "fig");
$array2 = [2,3,4,6,8];
$array3 = [4,7,9,4,3,5];
// $mergedArray = array_merge($array1, $array2);
$mergedArray = array_merge($array2, $array3);
echo "Combined array:\n";
print_r($mergedArray);
$commonEle=array_intersect($array2,$array3);
echo "Common element is ";
print_r($commonEle);
?>