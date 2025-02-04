<?php
$num1=readline("Enetr the 1st number");
$num2=readline("Enetr the 2nd number");
$op = readline("Enter the Operations (+,-,*,/,**,%");
switch ($op) {
    //body
    case '+':
        $result=$num1+$num2;
        break;
        case '-':
            $result=$num1-$num2;
            break;
            case '*':
                $result=$num1*$num2;
                break;
                case '/':
                    $result=$num1/$num2;
                    break;
                    case '**':
                        $result=$num1**$num2;
                        break;
                        case '%':
                            $result=$num1%$num2;
                            break;

}
echo "The result is ".$result;
?>