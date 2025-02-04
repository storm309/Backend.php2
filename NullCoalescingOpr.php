<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Null Coallescing Operator</title>
</head>
<body>
    <?php
    // Null Coalescing Operator
    $a;
    $b;
    $c=20;
    $d=30;
    $result = $a ?? $b ?? $c ?? $d;
    echo $result;
    ?>
</body>
</html>