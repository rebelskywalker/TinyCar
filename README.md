# TinyCar

This code was designed to drive a car made from a [TI-RSLK Maze Edition](https://university.ti.com/en/faculty/ti-robotics-system-learning-kit/ti-robotics-system-learning-kit). The car drives down a track made from a black line about 1 cm wide, until it encounters a perpendicular finish line. The bump switches included in the kit were not used.

## Prerequisites

Get the kit linked above, and follow the [assembly guide](http://www.ti.com/lit/ml/swrp249/swrp249.pdf) (other than the part with the bump switches).

Download and install [Energia](http://energia.nu/download/), an Arduino IDE variant for the TI platform. Energia must be installed in a path without spaces.

Once Energia is installed, launch it and to install board files for the MSP432 Board as follows:
1. Go to Tools > Board > Boards Manager
2. Click Energia MSP432 EMT RED Boards and select Install
3. Install the MSP-EXP432P401R drivers (choose your operating system at [this link](http://energia.nu/guide/))
4. Restart Energia
5. You should be able to now select RED Launchpad under Tools > Board

## Loading the code to your car

To use this code as is:
1. Download the TinyCar.ino sketch along with the TinyCar folder to your Energia sketchbook location (in Energia, this is set under File->Preferences->Settings: Sketchbook Location)
2. Open the sketch in Energia
3. Connect your car to your computer, using the USB port on the car
4. Select the appropriate port in Energia under Tools->Port. If only one port option is available, it's probably that one. If there is more than one, unplug the car to see which port option disappears. If you're using Windows, you can also open Device Manager and expand Universal Serial Bus Controllers. Devices which are plugged in to USB ports may be clearly labeled here, or may have generic labels. You can right click on a particular USB item listed here and select "Properties" to get the port information.
5. Compile, and upload to your car. If the code compiles correctly but does not upload, something may be wrong with your Energia installation. Make sure you have followed all of the instructions in the Prerequisites section, and check the Energia help files. With TI software it is sometimes necessary to just completely uninstall and reinstall. If the code does not compile correctly, make sure there is only one .ino file in the folder containing your sketch, and that the folder has the same name as the .ino file.

## Built With

* [Energia](http://energia.nu/)

## Authors

* Zefyr Scott ([combobulate](https://github.com/combobulate))
* Chris Baker ([rebelskywalker](https://github.com/rebelskywalker))

## Acknowledgements

* Professor Mike Briggs, who assigned this project in the EC ENGR 3 experimental lab section for Fall '18 quarter at UCLA
* PurpleBooth for the [README.md template](https://gist.github.com/PurpleBooth/109311bb0361f32d87a2)
