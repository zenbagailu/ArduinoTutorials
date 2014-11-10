#ArduinoTutorials.

These are a series of arduino tutorials for using the ethernet shield and the Arduino ethernet library, together with the [arduino websockets library](https://github.com/ejeklint/ArduinoWebsocketServer) developed by [Per Ejeklint](https://github.com/ejeklint). The most basic tutorial example illustrates how to control a servo motor through javascript and websockets.

###1.
Download and set-up Arduino from here: [arduino.cc](arduino.cc). When installing Arduino, it will create a directory/folder for your sketches (usually something like: /Users/username/Arduino/).This is your Sketchbook location. You can see and change this location in the Arduino application, through Preferences.

###2.
Download and install the web socket server library by Per Ejeklint:
[https://github.com/ejeklint/ArduinoWebsocketServer](https://github.com/ejeklint/ArduinoWebsocketServer).
If you download it as a zip file and unzip it, the resulting folder  will be called WebsocketServer-master. Remove the -master bit (so it is called only WebsocketServer) and copy it into the “library” folder in your Sketchbook location (explained in 1.). Restart the Arduino application if it is open, so it can find the library.

###3.
Download the “WebsocketServo” Arduino example from here (you can also download all files in the repository as a zip file). Copy the example into your sketchbook location.

You can optionally download and test the other examples, “WebsocketLED” and “WebsocketServoComplex”, which is an advanced version of the “WebsocketServo” example.

###4.
You should at this point set up the hardware bit… first mount the Ethernet shield on the Arduino, and connect a servo motor, like this: 

- Connect Ground (brown or black cable) to Arduino’s ground (GND).
- Connect the Control cable (white or yellow) to pin 7.
- Connect the Power cable (red)to +5V.

For a tutorial on how to connect servo motors to the Arduino, look here:[http://playground.arduino.cc/Learning/SingleServoExample](http://playground.arduino.cc/Learning/SingleServoExample). Connect the Arduino to your computer through the USB cable.

In any real use of servos, it is also recommended to use an external power supply rather than the power provided through the USB. Servos and motors in general may use more current than the one provided through a USB port (usually about 500mA). For testing the code this is not necessary.

###5.
In the Arduino application, open the “WebsocketServo” project (it should be visible in the `file->Sketchbook` menu, if you have copied it into the right location) Compile and upload the project into the Arduino (with the Ethernet Shield), which should be connected through the USB to your computer, by clicking  the arrow on top of the screen (it says Upload…). You may have to set the right serial port in the Arduino app, in `Tools->Serial Port`.

###6.
Open the serial port monitor `Tools->Serial Monitor` (set the baudrate to 57600) and listen to get the correct IP address from the Arduino. If you are connecting many Arduinos to the same network, you should give them different mac addresses in the code. You will see this in the first lines of the WebsocketServo project, where it says something like:` byte mac[] = { 0x52, 0x4F, 0x43, 0x4B, 0x45, 0x54 };` Ethernet shields have usually a unique mac Address on a sticker attached to them, it is quite a good idea to use that one.

###7.
Open the `control.html` file (it is in the same folder as the WebsocketServo project, but you can copy and place it anywhere) and input the IP you have got from the serial..
(Hopefully) Control the servo!


