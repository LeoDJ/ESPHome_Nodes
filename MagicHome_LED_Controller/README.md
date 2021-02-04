# MagicHome LED Controller

![](https://user-images.githubusercontent.com/29731130/31029721-23312a68-a553-11e7-9bd9-0a45f38d3375.jpg)

This node includes my `virtualAddressableLight` to use all the addressable LED effects on a simple 12V RGB strip. It simulates a single addressable LED and controls the whole "dumb" LED strip with that. It's quite hacked together, but should work.

You need to place the `virtualAddressableLight.h` file into the esphome folder.

This node mainly adds WLED support to simple RGB strips, which wouldn't be possible without the virtualization layer.

## Magic Home Controller Connections
To flash the MagicHome controller the first time, you need to open it and solder some wires to it. After that you can upload any future updates via OTA. The [Tasmota Documentation](https://tasmota.github.io/docs/devices/MagicHome-LED-strip-controller/) has a nice connection diagram and uploading instructions.
![](https://user-images.githubusercontent.com/29731130/31029735-2f99db9c-a553-11e7-896c-2f71c3d04551.jpg)