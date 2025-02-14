<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Inventory Form</title>
</head>
<body>
    <h1>Inventory Management</h1>
    
    <form method="POST">
        <h4>Adding Item</h4>
        <input type="hidden" name="action" value="add">
        <input type="text" name="Item" placeholder="Item Name">
        <input type="number" name="Quan" placeholder="Item Quantity">
        <input type="number" name="Price" placeholder="Item Price">
        <input type="submit" name="addItem" value="Add Item">
    </form>

    <form method="POST">
        <h4>Updating Item</h4>
        <input type="hidden" name="action" value="update">
        <input type="text" name="Item" placeholder="Item Name">
        <input type="number" name="Quan" placeholder="Item Quantity">
        <input type="number" name="Price" placeholder="Item Price">
        <input type="submit" name="updateItem" value="Update Item">
    </form>
    
    <form action="POST">
        <h4>Deleting Item</h4>
        <input type="hidden" name="action" value="update">
        <input type="text" name="Item" placeholder="Item Name">
        <input type="number" name="Quan" placeholder="Item Quantity">
        <input type="number" name="Price" placeholder="Item Price">
        <input type="submit" name="updateItem" value="Delete Item">
    </form>

    <?php
//     $Inventory=["zen"=>['quantity'=>10,'price'=>20000],
//     'maruti'=>['quantity'=>8,'price'=>10000],
//     'flat'=>['quantity'=>7,'price'=>8000],
// ];
// print_r($Inventory);
// foreach($Inventory as $ItemName=>$details){
//     echo $details['quantity'];
//     echo "<br>"
//     echo "Price details"
// }

$Inventory = [
    "zen" => ["quantity" => 10, "price" => 20000],
    "maruti" => ["quantity" => 8, "price" => 10000],
    "flat" => ["quantity" => 7, "price" => 8000],
];

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $action = $_POST["action"] ?? "";
    $itemName = strtolower(trim($_POST["Item"] ?? ""));
    $quantity = intval($_POST["Quan"] ?? 0);
    $price = intval($_POST["Price"] ?? 0);

    if ($itemName !== "") {
        if ($action == "add") {
            if (isset($Inventory[$itemName])) {
                $Inventory[$itemName]["quantity"] += $quantity;
                $Inventory[$itemName]["price"] = $price;
            } else {
                $Inventory[$itemName] = ["quantity" => $quantity, "price" => $price];
            }
        } elseif ($action == "update") {
            if (isset($Inventory[$itemName])) {
                $Inventory[$itemName]["quantity"] = $quantity;
                $Inventory[$itemName]["price"] = $price;
            } else {
                echo "<p>Item not found in inventory.</p>";
            }
        } elseif ($action == "delete") {
            if (isset($Inventory[$itemName])) {
                unset($Inventory[$itemName]);
            } else {
                echo "<p>Item not found in inventory.</p>";
            }
        }
    } else {
        echo "<p>Please enter an item name.</p>";
    }
}

// Display the inventory
echo "<h2>Current Inventory</h2>";
echo "<table border='1'><tr><th>Item</th><th>Quantity</th><th>Price</th></tr>";
foreach ($Inventory as $itemName => $details) {
    echo "<tr><td>" . ucfirst($itemName) . "</td><td>" . $details['quantity'] . "</td><td>" . $details['price'] . "</td></tr>";
}
echo "</table>";




    ?>


</body>
</html>

