<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Quiz App</title>
</head>
<body>
    <?php
   $questions = [
    'question' => 'What is the capital of France?',
    'options' => ['Paris', 'London', 'Berlin', 'Madrid'],
    'answer' => 'Paris'

    'question' => 'What is 2 + 2?',
    'options' => ['3', '4', '5', '6'],
    'answer' => '4'

    'question' => 'What is the largest planet in our solar system?',
    'options' => ['Earth', 'Mars', 'Jupiter', 'Saturn'],
    'answer' => 'Jupiter'
   ];
    $score = 0;
    $total_questions = count($questions);
    if($_SERVER["REQUEST_METHOD"] == "POST")
    {
        for($i = 0; $i < $total_questions; $i++)
        {
            if(isset($_POST["q$i"]))
            {
                if($_POST["q$i"] == $questions[$i]['answer'])
                {
                    $score++;
                }
            }
        }
        echo "<h1>Your score is $score out of $total_questions</h1>";
    }
    else
    {
        echo "<form action='' method='post'>";
        for($i = 0; $i < $total_questions; $i++)
        {
            echo "<h3>" . $questions[$i]['question'] . "</h3>";
            foreach($questions[$i]['options'] as $option)
            {
                echo "<input type='radio' name='q$i' value='$option'> $option <br>";
            }
        }
        echo "<input type='submit' name='sub' value='Submit'>";
        echo "</form>";
    }
    ?>
</body>
</html>