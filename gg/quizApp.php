<?php
$quiz = [
    "question1" => [
        "question" => "What does PHP stand for?",
        "options" => ["Personal Home Page", "Preprocessor Hypertext", "Hypertext Preprocessor", "Private Hypertext Processor"],
        "correct_answer" => "Hypertext Preprocessor"
    ],
    "question2" => [
        "question" => "Which of the following is an inbuilt PHP function to get the length of a string?",
        "options" => ["strlen()", "count()", "length()", "sizeof()"],
        "correct_answer" => "strlen()"
    ],
    "question3" => [
        "question" => "What will the function array_push(\$arr, \$val) do?",
        "options" => ["Pushes a value to the array", "Pops a value from the array", "Creates an associative array", "Checks if an array is empty"],
        "correct_answer" => "Pushes a value to the array"
    ],
    "question4" => [
        "question" => "How do you start a PHP session?",
        "options" => ["session_start()", "start_session()", "begin_session()", "php_session()"],
        "correct_answer" => "session_start()"
    ],
    "question5" => [
        "question" => "Which of the following is not a valid way to declare a variable in PHP?",
        "options" => ["\$var", "\$variable", "var$", "\$_var"],
        "correct_answer" => "var$"
    ]
];

$score = 0;

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    foreach ($quiz as $key => $value) {
        if (isset($_POST[$key]) && $_POST[$key] == $value["correct_answer"]) {
            $score++;
        }
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>PHP Quiz</title>
    <style>
        .quiz-container {
            width: 50%;
            margin: 0 auto;
            padding: 20px;
            border: 1px solid #ccc;
            border-radius: 5px;
        }
        .question {
            font-weight: bold;
            margin-top: 10px;
        }
        .options {
            margin-top: 5px;
        }
        .result {
            margin-top: 20px;
            font-size: 1.2em;
            color: green;
        }
    </style>
</head>
<body>

<div class="quiz-container">
    <h2>PHP Quiz</h2>

    <?php if ($_SERVER["REQUEST_METHOD"] == "POST"): ?>
        <div class="result">
            Your score is: <?php echo $score; ?> out of 5
        </div>
    <?php endif; ?>

    <form method="POST">
        <?php foreach ($quiz as $key => $value): ?>
            <div class="question">
                <?php echo $value["question"]; ?>
            </div>
            <div class="options">
                <?php foreach ($value["options"] as $option): ?>
                    <input type="radio" name="<?php echo $key; ?>" value="<?php echo $option; ?>" 
                        <?php if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST[$key]) && $_POST[$key] == $option) echo "checked"; ?>> 
                    <?php echo $option; ?><br>
                <?php endforeach; ?>
            </div>
        <?php endforeach; ?>
        
        <button type="submit">Submit</button>
    </form>
</div>

</body>
</html>
