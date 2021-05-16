# SmartCarParking
When a user enters or exits the system, the microcontroller will
update the real-time database (firebase real-time database), which will update the counter on
the website. It will also trigger the servo motors at the entry and exit gates to open. An
ultrasonic sensor is used to detect the presence of a car in the parking space. If a car is
detected by the ultrasonic sensor, the website is updated to indicate that the space is occupied and also turn on
the LED of the particular parking space. If there is no space available in the parking lot when
the user tries to enter, the servo motor(gate) will not be triggered to let the user into the
parking lot.
