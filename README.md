#  Enhanced ESP8266 Color Weather Station w/ Touchscreen -- (Version v15) (based on original by Daniel Eichorn (squix78) )

This project is a series of enhancements made to the original color weather station for the ESP8266 created by Daniel Eichorn, with contributions by several others.  Though the original display layout came from squix78, I've made substantial changes to add additional information.

This version of the project was written specifically for the WeMos Mini D1 with the 2.8" or 3.2" color LCD display based on the ILI9341 and XPT2046 touchscreen controller that squix78 used.  These can be had very inexpensively from sources such as AliExpress (<$10, shipped to the US, or slightly more for the 3.2" version).  You may also want to pick up a cheap stylus for the screen if it doesn't come with one.

This edition (v15) has been in development for almost a year now and I have been running this code for several months now; it seems to be pretty stable despite the large number of changes.

Note that the wiring for this version is somewhat different from prior releases in order to support the touchscreen functions.  I have also attempted to deal with some instability issues that occurred with the prior releases.  First, I added a short delay following the TFT initialization, which seemed to eliminate some issues with periodic "white screen" displays at power-up.  Second, I added a 1000uF capacitor between the VCC and GND pins on the WeMos mini, in order to avoid sags in the voltage during WiFi operations.  Third, I soldered jumper J1 on the TFT board to bypass the on-board regulator since the board is being powered directly from the WeMos 3.3V supply.  (The additional regulator in-line was causing the voltage to drop below specifications for the TFT display.)  All of these changes seem to have resulted in a much more stable station.



##  Overview of Changes from v11d

This release contains significant changes over prior releases, including support for touchscreen functions.  (You may want to review the README files for v8 and v11d in my other repositories, as this version builds on those enhancements.)  **(Note:  As a result of prior changes to the Weather Underground client library to support corrections to the weather icons, I've submitted a pull request to merge these changes into the original master.  This is still pending, so I've included a copy of the changed library in the "/Weather Underground Client Library" folder.  Replace your copy in your libraries folder for the IDE with this copy (both the .cpp and .h files). Note that this library version does not include squix78's most recent updates he made for the MiniGrafx library, including improvements in memory used.)**

Some of the touchscreen functions added:
* a touch in the upper-rightmost corner (next to the date display) will toggle the WiFi strength indicator on/off
* a touch to the current conditions (weather icon / temperature) region will bring up the day / night forecast for today
* a touch to any of the forecast icons for the 9-day forecast will bring up the day / night forecast for that date
* a long touch (>4-5 secs) to the time display region will enter configuration mode (previously triggered via a double-reset of the ESP)
* a long touch (>4-5 secs) to the current conditions region (weather icon / temperature) will initiate the screen calibration routine again
* a long touch (>4-5 secs) to the bottom panel region will bring up a detailed ESP status screen, showing heap, WiFi connection info, last reset error condition, etc. (adapted from Daniel Eichorn...thanks Dani!)

All of these touch displays return to the normal "rotating" screens by touching the screen again.

A few of the other changes / enhancements:
* reversed the high / low temperatures on the forecast panel, a more logical display indicating the daytime high / nighttime low
* added a brief (500ms) delay following the TFT initialization and prior to any other display calls to avoid an occasional "white-screen" display state on startup
* added configuration items to set the display delay times for the mid- and bottom-panels.  These default to 6 seconds for the forecast (mid-panel) and 10 seconds for the bottom panel as previously used.
* added configuration item to allow setting an auto-restart frequency in seconds; this is in an attempt to periodically clear fragmented heap that I suspect causes occasional hangs in the station (usually manifested during a call to update WU information), and after the station is running for a week or so.  The default is set to 604,800 seconds, or 7 days of runtime.  (I suspect some of the remaining stalls that occasionally manifest themselves after 7-10 days of running are due to heap fragmentation due to extensive use of Strings in the code, and this is a crude workaround.)
* added configuration item to allow setting the hour / minute for the auto-restart described previously (say, to trigger the restart at 2:00 every 7 days)
* added code to check available free-heap space and trigger a restart if it falls below the specified threshhold (currently hard-coded at 5KB)
* added code to disconnect the WiFi prior to resetting the ESP prior to a configuration save; previously, if the WiFi was connected, changes to the SSID/password would not be saved, and the WiFiManager skips connecting and storing these parameters if the WiFi is connected
* much code refactoring for better organization, code re-use, and efficiencies

## Wiring

(*** Added 04/06/18 ***)

| ILI9341   | NodeMCU | WeMos D1 Mini | ESP8266 Pin
| --------- |:---------:|:---------------:|:-------------:
| T_IRQ     | D4    | D4  | GPIO2
| T_DO      | D6    | D6  | GPIO12
| T_DIN     | D7    | D7  | GPIO13
| T_CS      | D3    | D3  | GPIO0
| T_CLK     | D5    | D5  | GPIO14
| SDO/MISO  | D6    | D6  | GPIO12
| LED       | D8    | D8  | GPIO15
| SCK       | D5    | D5  | GPIO14
| SDI/MOSI  | D7    | D7  | GPIO13
| DC/RS     | D2    | D2  | GPIO4
| RESET     | RST   | RST | RST
| CS        | D1    | D1  | GPIO5
| GND       | GND   | GND | GND
| VCC       | 3V3   | 3V3 | 3V3

**Note that I have not tested the NodeMCU pin references, but from what I understand these are the same as for the WeMos D1 mini.  Verify and test these at your own risk!**  Also, note that some of these require more than one connection to the same pin.  Though this can be accomplished a number of ways, I highly recommend get some of the WeMos prototyping boards (if you are using this ESP variant) and soldering the connections directly to this board, then slipping it over the pin headers on the WeMos itself.  This also allows a good location for soldering the capacitor if you elect to use it.


##  Contributed Libraries (and links)

(*** As noted from the v8 README, with the removal of the double-reset detector library, no longer used in this version ***)

After several requests, I have added a summary of the contributed libraries with links below to make it easier to find and include these.  Most all of these come from the original examples on squix's site, but I admit that the list has become somewhat long and it took me some time to find all of these originally.

Library Referenced | Description | Link
------------------ | ----------- | ----
**<FS.h>** | Part of ESP8266 core, SPIFFS filesystem support | 
**<Adafruit_GFX.h>** | Adafruit's core graphics library | <https://github.com/adafruit/Adafruit-GFX-Library>
**<Adafruit_ILI9341.h>** | Adafruit's ILI9341 LCD hardware-specific library | <https://github.com/adafruit/Adafruit_ILI9341>
**<XPT2046_Touchscreen.h>** | XPT2046 library for touch-screen controller by Paul Stoffregen | <https://github.com/PaulStoffregen/XPT2046_Touchscreen>
**<WiFiManager.h>** | WiFi Manager library by Tzapu | <https://github.com/tzapu/WiFiManager>
**<ArduinoJson.h>** | JSON library by Bblanchon | <https://github.com/bblanchon/ArduinoJson>
**<JsonListener.h>** | JSON streaming parser by Squix78 | <https://github.com/squix78/json-streaming-parser>
**<WundergroundClient.h>** | Weather Underground client library by Squix78 **(Note (1) )** | <https://github.com/squix78/esp8266-weather-station>
**<simpleDSTadjust.h>**	| Simple daylight-savings time adjustment by Neptune | <https://github.com/neptune2/simpleDSTadjust>
**"TimeZone.h"** | Time zone conversion library by JChristensen | <https://github.com/JChristensen/Timezone>
**"DHT.h"** | Adafruit's DHT sensor library | <https://github.com/adafruit/DHT-sensor-library>
**<Adafruit_Sensor.h>** | Adafruit's Unified Sensor library | <https://github.com/adafruit/Adafruit_Sensor>

(Note that though I included the SPIFFS library in the list above, I elected not to document all of the other core libraries.)  Also note that though I do not use the DHT sensor in my setup (nor Thinkspeak as in the original code), I've maintained the bulk of this code in order to make it easier for those that elect to use it.  As a result, the Adafruit libraries for the DHT sensors and their Unified Sensor library are required for compilation.

**Note 1:**  Until my customizations are merged, replace the library contents with my changes located in the **Weather Underground Client Library** folder

##  Quick Start

(*** Added 04/06/18 ***)
1.  Install the libraries that are required as noted above.
1.  Wire the WeMos (or equivalent) as noted.  For best stability, add a 1000uF capacitor between VCC and GND near the WeMos pins, and solder the J1 jumper on the TFT board to bypass the regulator if powering the display from the WeMos.
1.  Install the ESP8266 Sketch Data Upload tool from here:  https://github.com/esp8266/arduino-esp8266fs-plugin
1.  Download and unzip this repository to your system.
1.  Copy/replace the two updated Weather Underground client library files in the folder "/Weather Underground Client Library" into the IDE libraries/ESP8266_Weather_Station folder (temporary fix until my pending changes are merged to the master library).
1.  Ensure your board is set correctly with the appropriate flash size (4M, 3M SPIFFS) in the IDE.
1.  Compile, download, and run the SPIFFS format tool located in the "/ESP SPIFFS Format" folder.  This will give you a clean SPIFFS file system area.  Be patient...it takes a few minutes to format the filesystem.  (Note that if you have used a prior version of my code and DON'T format the SPIFFS, you'll need to delete the config.json file, as the format of the file has changed.)
1.  Compile and download the Weather Station v15 code to the WeMos.
1.  Run the ESP8266 Data Upload tool located in the Tools menu of the IDE.  You should receive information in the IDE indicating the copying of the icon folders located in the "/data" folder to the ESP8266.
1.  On first run, the station will run a display calibration routine to map the touchscreen coordinates to the display coordinates.  Follow the on-screen instructions by touching the screen targets as indicated in the upper-left and lower-right corners of the screen.  The last step in the calibration allows you to see how closely the coordinates are mapped by displaying the screen coordinates as you touch various locations on the screen.  This will time out and continue startup if the screen is not touched for 5 seconds.
1.  The initial configuration is done via a configuration portal or webpage. The first time you bring up the app, if it cannot find previously stored settings, it will bring up an access point and configuration portal. Look for an access point that begins with "ESP..." and connect to it. The access point is password protected, with a default password as "portal-pass".  It is a captive portal, and in most cases a browser will open automatically connecting to the portal after connection. If it doesn't, then type the address "192.168.4.1" in a browser to bring it up once connected to the AP. It should be fairly self-explanatory at that point; enter your WiFi AP/password credentials, WeatherUnderground API key, WU weather station, timezone city from the list, etc., and click "Save". The ESP should restart and try to connect using the new configuration. There's other features of the configuration portal, such as scanning for all available access points and allowing you to just select one, but again, it's pretty self-explanatory once you see the configuration page.  (If you've done this before with a prior release, you'll need to reconfigure and save the settings, as the SPIFFS format will erase the configuration file stored previously.  Note that there are a number of new configuration parameters here from prior versions to allow tweaking the timing of the mid- and bottom-panels to your liking, and to control automatic restarting of the station to clear fragmented heap.
1.  If it doesn't connect, then you can at any time bring up the configuration portal again manually by touching the time-display region of the screen and holding for 4-5 seconds. You should also see information on the LCD display when it comes up in config mode.
1.  The initial defaults for the configuration portal are located on the "Settings.h" tab as well. If you look through this, you'll find parameters for the WU API key, the timezone city, weather station, etc. These are currently set for my location and preferences, but you can change them here if you want also.

