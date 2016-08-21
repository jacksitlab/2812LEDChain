import smbus
import time

class WS2812ChainItem(object):

    COMMAND_TESTRUN=0x01
    COMMAND_OFFSET=0x02
    COMMAND_SETSENDINGMODE=0x03
    COMMAND_DEMO_KITT=0x04
    COMMAND_RINGBUFFER=0x05

    def __init__(self,adr,bus):
        self._address=adr
        self._bus=bus
        self._length=6

    def Write(self,adr,colorData):
        buffer=[]
        buffer.append(0xff&adr)
        for color in colorData:
            buffer.append(0xff&(color>>16))
            buffer.append(0xff&(color>>8))
            buffer.append(0xff&(color))
        self._bus.write_i2c_block_data(self._address, 0xff&(adr>>8), buffer)

    def Clear(self):
        buffer=[]
        i=0
        while i < self._length:
            buffer.append(0x000000)
            i+=1
        self.Write(0,buffer)

    def sendCommand(self,command,params):
        buffer=[]
        adr=0xff00|command
        buffer.append(0xff&adr)
        for param in params:
            buffer.append(0xff&param)
        self._bus.write_i2c_block_data(self._address, 0xff&(adr>>8), buffer)

    def Offset(self,difvalue):
        difvalue = 0xff&difvalue
        self.sendCommand(self.COMMAND_OFFSET,[difvalue])
    # speed: 16bit in ms
    # direction: 0=forward,1=backward
    def RingBuffer(self,speed,direction):
        self.sendCommand(self.COMMAND_RINGBUFFER,[0xff&(speed>>8),0xff&speed,direction])

    def Test(self):
        ledcolors=[0xff0000,0x00ff00,0x0000ff,0xffff00,0xff00ff,0x00ffff]
        ledcolors2=[0x00ff00,0xff0000,0xff0000,0xff0000,0xffFFff,0x0000ff]
        self.Write(0,ledcolors)
        time.sleep(2)
        self.Write(0,ledcolors2)
        time.sleep(2)
        self.Clear()

    def Test2(self):
        ledcolors=[0xff0000,0x00ff00,0x0000ff,0xffff00,0xff00ff,0x00ffff]
        ledcolors2=[0xff0000,0x800000,0x400000,0x300000,0x200000,0x100000]
        self.Write(0,ledcolors)
        time.sleep(2)
        self.Write(0,ledcolors2)
#        time.sleep(2)
        

class WS2812Chain(object):
    def __init__(self,busno):
        self._bus=smbus.SMBus(busno)
        self._items=[]
    def Add(self,adr):
        item=WS2812ChainItem(adr,self._bus)
        self._items.append(item)
        return item




#========usage=======
#chain=WS2812Chain(1)
#leds=chain.Add(0x44)
#leds.Test()
#leds.RingBuffer(100,0)
#time.sleep(5)
#leds.RingBuffer(100,1)
