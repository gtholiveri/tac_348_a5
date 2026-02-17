## COMPILE
`particle compile p2 . --saveTo bin/NAME.bin --target 6.3.4`
* the dot gives pwd
* --target lets you specify device version
* --saveTo self-explanatory
* always use a .bin file

## FLASH
`particle flash --local --target 6.3.4 bin/NAME.bin`
* --local makes it use usb and also automatically puts it in DFU mode if needed
* --usb you use to flash new firmware version

## UTILS
`particle serial identify`
* very useful for checking connection, getting device id, and getting firmware version
`particle serial monitor`
* general serial monitor viewing (println etc)
* use --follow tag for logger output