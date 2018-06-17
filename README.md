## 2812LEDChain

This Project is based on a little piece of Hardware I build for accessing 2812LEDs via I2C-Bus(aka TWI). In my special case I use a Raspberry PI to control them.
The Clou: It is possible to wire them from board to board and control them seperately. So you can wire the seperated LEDChains from one to another.
The Controller works like a simple 32bit adressable I2C-EEPROM where you can write the RGB-Values.

## Why the extra board? There is already a lib for the raspi that can control 2812LEDs.

Yeah, thats right. But this lib is using the PWM-output Pin and many of my Projects are using this as it should be. That's why I want to put it on a place where I can control them with a seperate address.
 
## Folders

* pcb: all KiCAD files (Schematics and Layout files)
* firmware: all microcontroller files for CodeComposerStudio(from Texas Instruments)
* raspberry: all files to remote control the LEDChain from a Raspberry PI with python


## Installation / Usage

### Firmware installation

* File > Import > Code Composer Studio > CCS Projects
* Select Directory and Finish
* Debug with a programmer (a launchpad also works) with connected TEST and RESET Pin. Don't forget GND.


### For Raspberry PI with Python

* copy ws2812ledchain.py to your python project folder
* use it from a seperate file like this below.

```
	
	from ws2812ledchain import *

	chain=WS2812Chain(1)  //1 =>bus number(i2c-1 on raspi 2 and 3, i2c-0 on raspi 1)
	leds=chain.Add(0x44,256)  //0x44 => 7bit address of the chain element. 0x44 is the default. can be modified in firmware, 256 leds to handle
	leds.Test()
	leds.RingBuffer(500,0)  //shift forward every LED every 500ms 
	time.sleep(5)
	leds.RingBuffer(100,1)  //shift backward every LED every 100ms

```

### For Raspberry PI with Web-API


* install apache webserver

```

	pi@raspberrypi ~ $ sudo apt-get install apache2

```

* copy ws2812ledchain.py and api.py to /usr/lib/cgi-bin/
* change userrights for those files

```

	pi@raspberrypi ~ $ sudo chmod 0755 /usr/lib/cgi-bin/*.py

```


* add cgi support in your apache config file

```

	<Directory "/usr/lib/cgi-bin">
		AllowOverride None
		Options +ExecCGI -MultiViews +SymLinksIfOwnerMatch
		Order allow,deny
		Allow from all
	</Directory>


```

* maybe you have to enable cgi mod for apache

```

	sudo a2enmod cgi
	sudo /etc/init.d/apache2 restart
```

* make a simple get request with javascript from your page (here with jQuery)

```

	$.ajax({
		url:'cgi-bin/api.py?task='+task,
		success: function(r){
			console.log(r);
		}
    });

```

## TODO

* Set RGBChain Length via Command
* Change I2C-Address via Command
* Add more functions ...

## License

Beerware License.