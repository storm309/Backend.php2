<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Set Preferred Language</title>
</head>
<body>
    <h2>Choose your preferred language:</h2>
    <form action="#" method="POST">
        <select name="language">
        <option value="en">English</option>
        <option value="hi">Hindi</option>
        <option value="bho">Bhojpuri</option>
        <option value="gr">German</option>
        <option value="it">Italian</option>
        <option value="fr">French</option>
        <option value="es">Spanish</option>
        <option value="ru">Russian</option>
            
        </select>
        <button type="submit">Set Language</button>
        <button type="submit">Save Preferences</button>
    </form>

    <?php
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        $language = $_POST["language"];
        setcookie("user_language", $language, time() + 60 * 60 * 24 * 7); 

        echo "<h3 style='color:green;'>Language set to: " . ucfirst($language) . "</h3>";
    }
    ?>
</body>
</html>