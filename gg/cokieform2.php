<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Greeting Page</title>
</head>
<body>
    <h2>Greeting based on your selected language:</h2>

    <?php
    if (isset($_COOKIE["user_language"])) {
        $language = $_COOKIE["user_language"];
        
        switch ($language) {
            case "en":
                echo "<h3>Hello, welcome!</h3>";
                break;
            case "hi":
                echo "<h3>नमस्ते, स्वागत है!</h3>";
                break;
            case "gr":
                echo "<h3>Hallo, willkommen!</h3>";
                break;
            case "it":
                echo "<h3>Ciao, benvenuto!</h3>";
                break;
            case "fr":
                echo "<h3>Bonjour, bienvenue!</h3>";
                break;
            case "es":
                echo "<h3>Hola, bienvenido!</h3>";
                break;
            case "ru":
                echo "<h3>Привет, добро пожаловать!</h3>";
                break;
            case "jp":
                echo "<h3>こんにちは、ようこそ!</h3>";
                break;
            case "zh":
                echo "<h3>你好，欢迎!</h3>";
                break;
            case "ar":
                echo "<h3>مرحبا، أهلا وسهلا!</h3>";
                break;
            case "bho":
                echo "<h3>नमस्ते, का हाल बा!</h3>";
                break;
            default:
                echo "<h3>Language not recognized. Defaulting to English.</h3>";
        }
    } else {
        echo "<h3>You have not set a preferred language yet.</h3>";
    }
    ?>

</body>
</html>
