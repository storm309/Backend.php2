<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Password Validity Check</title>
</head>
<body>

    <form action="" method="POST">
        <label>Enter any number:</label>
        <input type="number" name="year" placeholder="Enter year here" required>
        <br>
        <button type="submit">Check Validity</button>
    </form>

    <?php
    if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST['year'])) {
        $year = $_POST['year'];

        if (is_numeric($year) && $year > 0) {
            echo "<p>The year $year is valid.</p>";
        } else {
            echo "<p>Please enter a valid year.</p>";
        }
    }
    ?>

</body>
</html>
