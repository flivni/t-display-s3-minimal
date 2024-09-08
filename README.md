This is a minimal example of using the LilyGO T-Display-S3. I started with the `tft` example from the [T-Display-S3 repo](https://github.com/Xinyuan-LilyGO/T-Display-S3) and then started removing code.

Still to do:

1. Figure out what's different between their local "blessed" version of the TFT_eSPI library. They only state in the example code that you need to use their copy of the library. It would be great to be able to use the official library.

2. Look into the scattered delays in the initialization code. These come from the example. Are they needed?

3. ~~I have to do a full hardware reset (hold boot and hit reset) on the device every time before I upload. Would like to fix.~~

4. ~~I have to do a simple reset on the device (hit reset button) after successfully uploading code so that it will properly start running the code. I would like to fix this as well.~~

    ~~> Both of the above appear to related to an issue with the current version of platformio's esptool.py and if I use the one I installed with pip it works. I added a custom upload_command in platform.ini to address.~~
Added a platformio.ini directive to pull a newer version of esptool.py that seems to work as per the above workaround, without altering system-wide Python libs.

