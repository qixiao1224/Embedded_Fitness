# Embedded_Fitness
Code is written by Arduino
Chip: Adafruit Circuit Playground(ATmega32u4)

My chip will work like this:  
a.	When we push the left button, the chip will reset its condition and start working  
This work can be done by GPIO.  
b.	It will detect your first motion automatically and tell what that is.  
  Set up four functions to indicate four different exercises. The color of LEDs will show what you are doing right now. Red represents Sit-ups, Green represents push-ups, Blue represents jumping jacks and violet represents squats. The color can be changed by different parameters we use in the Neopixel function.  
c.	And then it will start counting until you finish 15 repetitions. The number of shining LED will indicate how many times you left.   
I’m working on it if the counter can count successfully when I am doing mixed exercises at the same time. This means I need four variables to be the counter and they can count together. But this may lead to error if I cannot separate four motions clearly.  
d.	The LED will blink four times with different colors when we finish all the four exercises.  
  This can be implemented easily by using the LED function.
  
## Basic function description                        
*Left button is used to convert between random & fixed mode  
*Right button is used to go to next exercise in fixed mode   
*Right button is not used in random mode   
  
## Lights  
*Red   LED represents Sit-up                                 
*Green LED represents Push-up                                
*Blue  LED represnets Jumping jack                           
*Violet LED represents Squat                                 
*Single color shining means this exercise is done            
*Rainbow blinking means it's finished                       
  
*The times you want to do in an exercise can be changed      
  by changing value of variable "total"      *             

