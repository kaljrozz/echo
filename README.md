# Echo for the STM32F407G-DISC1
>This program recieves and echoes back characters from a host computer running a serial terminal program. You will need a ftdi serial to usb converter, and a serial terminal program installed. I personally like picocom, but any serial terminal program should work.

## Required Tools
* [GNU Make](https://www.gnu.org/software/make/)
* [GNU ARM Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)
* [St-Link Flash Utility](https://github.com/texane/stlink)
* [STM32F407G-DISC1 Development Board](https://www.st.com/en/evaluation-tools/stm32f4discovery.html)
* [FTDI serial to usb converter](https://www.adafruit.com/product/284)
* picocom

## Compiling Instructions
>Make sure your discovery board is plugged into your computer, and that you have the required tools installed. Then use your shell to clone the git repository and compile/flash your board.
```
git clone https://github.com/mkrolbass/echo.git
cd echo
make flash
picocom -b 9600 -l -r path/to/ftdi
```
