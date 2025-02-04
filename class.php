<?php

class Car {
    public $color;
    public function setcolor($color){
        $this->color=$color;
    }
    public function getcolor(): mixed{
        return $this->color;
    }
}

$myCar = new Car();
$myfriendCar = new Car();
// obj name is variable $myCar = new // new obj car

//set color of the car 
$myCar->setcolor("Red");
$myfriendCar->setcolor("White");

//get and  display color of the car
echo "The color of my car is: ".$myCar->getcolor();
echo "\n";
echo "The color of my friend car is: ".$myfriendCar->getcolor();
?>