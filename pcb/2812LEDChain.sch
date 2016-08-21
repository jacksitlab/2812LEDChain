EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:st
LIBS:msp430
LIBS:2812LEDChain-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CONN_01X03 P3
U 1 1 56F656FC
P 9850 1250
F 0 "P3" H 9850 1450 50  0000 C CNN
F 1 "CONN_01X03" V 9950 1250 50  0000 C CNN
F 2 "Pin_Headers:PINHEAD1-3_SMD" H 9850 1250 60  0000 C CNN
F 3 "" H 9850 1250 60  0000 C CNN
	1    9850 1250
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR01
U 1 1 56F65CA0
P 2550 850
F 0 "#PWR01" H 2550 700 50  0001 C CNN
F 1 "+5V" H 2550 990 50  0000 C CNN
F 2 "" H 2550 850 60  0000 C CNN
F 3 "" H 2550 850 60  0000 C CNN
	1    2550 850 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 56F65CB7
P 2450 1725
F 0 "#PWR02" H 2450 1475 50  0001 C CNN
F 1 "GND" H 2450 1575 50  0000 C CNN
F 2 "" H 2450 1725 60  0000 C CNN
F 3 "" H 2450 1725 60  0000 C CNN
	1    2450 1725
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 1425 3725 1425
Wire Wire Line
	2450 1425 2450 1725
Wire Wire Line
	2550 1325 1800 1325
Wire Wire Line
	2550 850  2550 1325
Wire Wire Line
	2550 1150 9650 1150
Connection ~ 2550 1150
Wire Wire Line
	3725 1350 9650 1350
Wire Wire Line
	3725 1425 3725 1350
Connection ~ 2450 1425
Wire Wire Line
	8275 1250 9650 1250
Wire Wire Line
	2250 1125 2250 4750
Wire Wire Line
	1800 1125 2250 1125
Wire Wire Line
	1800 1225 2150 1225
Wire Wire Line
	2150 1225 2150 4625
Connection ~ 7450 1350
$Comp
L CONN_01X02 P1
U 1 1 56F66097
P 1250 3700
F 0 "P1" H 1250 3850 50  0000 C CNN
F 1 "CONN_01X02" V 1350 3700 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 1250 3700 60  0001 C CNN
F 3 "" H 1250 3700 60  0000 C CNN
	1    1250 3700
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1450 3625 3175 3625
Wire Wire Line
	1450 3625 1450 3650
Wire Wire Line
	1450 3750 3175 3750
$Comp
L LD59015 U1
U 1 1 56F654BD
P 4200 2275
F 0 "U1" H 3875 2575 60  0000 C CNN
F 1 "LD59015" H 4450 2575 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-5" H 4200 2175 60  0000 C CNN
F 3 "" H 4200 2175 60  0000 C CNN
	1    4200 2275
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 4625 3175 4625
Wire Wire Line
	2250 4750 3175 4750
Wire Wire Line
	2875 2275 3600 2275
Wire Wire Line
	2875 2275 2875 1425
Connection ~ 2875 1425
Wire Wire Line
	4850 2125 5325 2125
Wire Wire Line
	5325 2125 5325 1975
NoConn ~ 4850 2425
$Comp
L +3.3V #PWR03
U 1 1 56F65CB4
P 5325 1975
F 0 "#PWR03" H 5325 1825 50  0001 C CNN
F 1 "+3.3V" H 5325 2115 50  0000 C CNN
F 2 "" H 5325 1975 60  0000 C CNN
F 3 "" H 5325 1975 60  0000 C CNN
	1    5325 1975
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 56F6625D
P 1775 3350
F 0 "R1" V 1855 3350 50  0000 C CNN
F 1 "47k" V 1775 3350 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 1705 3350 30  0000 C CNN
F 3 "" H 1775 3350 30  0000 C CNN
	1    1775 3350
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 56F66378
P 1775 4050
F 0 "C1" H 1800 4150 50  0000 L CNN
F 1 "1n" H 1800 3950 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 1813 3900 30  0001 C CNN
F 3 "" H 1775 4050 60  0000 C CNN
	1    1775 4050
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR04
U 1 1 56F663E0
P 1775 3000
F 0 "#PWR04" H 1775 2850 50  0001 C CNN
F 1 "+3.3V" H 1775 3140 50  0000 C CNN
F 2 "" H 1775 3000 60  0000 C CNN
F 3 "" H 1775 3000 60  0000 C CNN
	1    1775 3000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 56F663FB
P 1775 4450
F 0 "#PWR05" H 1775 4200 50  0001 C CNN
F 1 "GND" H 1775 4300 50  0000 C CNN
F 2 "" H 1775 4450 60  0000 C CNN
F 3 "" H 1775 4450 60  0000 C CNN
	1    1775 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1775 3000 1775 3200
Wire Wire Line
	1775 3500 1775 3900
Wire Wire Line
	1775 4200 1775 4450
Text Label 2700 4625 0    60   ~ 0
SDA
Text Label 2700 4750 0    60   ~ 0
SCL
Text Label 2675 3750 0    60   ~ 0
TEST
Text Label 8650 1250 0    60   ~ 0
DO
Text Label 8650 1150 0    60   ~ 0
VCC_5V
Text Label 8650 1350 0    60   ~ 0
GND
Text Label 4925 2125 0    60   ~ 0
VCC_3_3V
$Comp
L R R2
U 1 1 56F6739F
P 2650 4200
F 0 "R2" V 2730 4200 50  0000 C CNN
F 1 "10k" V 2650 4200 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 2580 4200 30  0000 C CNN
F 3 "" H 2650 4200 30  0000 C CNN
	1    2650 4200
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 56F67BD2
P 2950 4200
F 0 "R3" V 3030 4200 50  0000 C CNN
F 1 "10k" V 2950 4200 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 2880 4200 30  0000 C CNN
F 3 "" H 2950 4200 30  0000 C CNN
	1    2950 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 4350 2650 4625
Connection ~ 2650 4625
Wire Wire Line
	2950 4350 2950 4750
Connection ~ 2950 4750
Wire Wire Line
	1775 3100 2950 3100
Wire Wire Line
	2650 3100 2650 4050
Connection ~ 1775 3100
Wire Wire Line
	2950 3100 2950 4050
Connection ~ 2650 3100
Wire Notes Line
	2425 3900 3275 3900
Wire Notes Line
	3275 3900 3275 4500
Wire Notes Line
	3275 4500 2425 4500
Wire Notes Line
	2425 4500 2425 3900
Text Notes 2425 3900 0    60   ~ 0
optional PullUps
$Comp
L C C2
U 1 1 56F683BA
P 2975 2625
F 0 "C2" H 3000 2725 50  0000 L CNN
F 1 "1u" H 3000 2525 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 3013 2475 30  0001 C CNN
F 3 "" H 2975 2625 60  0000 C CNN
	1    2975 2625
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 56F68421
P 5175 2550
F 0 "C3" H 5200 2650 50  0000 L CNN
F 1 "1u" H 5200 2450 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 5213 2400 30  0001 C CNN
F 3 "" H 5175 2550 60  0000 C CNN
	1    5175 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2975 2125 3600 2125
Wire Wire Line
	2975 1150 2975 2475
Connection ~ 2975 1150
Connection ~ 2975 2125
Wire Wire Line
	3600 2425 3425 2425
Wire Wire Line
	3425 2425 3425 2125
Connection ~ 3425 2125
Wire Wire Line
	2450 1600 2700 1600
Wire Wire Line
	2700 1600 2700 2875
Wire Wire Line
	2700 2875 5175 2875
Wire Wire Line
	2975 2875 2975 2775
Connection ~ 2450 1600
Wire Wire Line
	5175 2875 5175 2700
Connection ~ 2975 2875
Wire Wire Line
	5175 2400 5175 2125
Connection ~ 5175 2125
Connection ~ 1775 3625
$Comp
L CONN_02X04 P2
U 1 1 56FF8E13
P 1550 1275
F 0 "P2" H 1550 1525 50  0000 C CNN
F 1 "CONN_02X04" H 1550 1025 50  0000 C CNN
F 2 "Pin_Headers:PINHEAD1-8_SMD" H 1550 75  50  0000 C CNN
F 3 "" H 1550 75  50  0000 C CNN
	1    1550 1275
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 1125 1225 1125
Wire Wire Line
	1225 1125 1225 975 
Wire Wire Line
	1225 975  1850 975 
Wire Wire Line
	1850 975  1850 1125
Connection ~ 1850 1125
Wire Wire Line
	1300 1225 1175 1225
Wire Wire Line
	1175 1225 1175 925 
Wire Wire Line
	1175 925  1900 925 
Wire Wire Line
	1900 925  1900 1225
Connection ~ 1900 1225
Wire Wire Line
	1300 1425 1225 1425
Wire Wire Line
	1225 1425 1225 1625
Wire Wire Line
	1225 1625 1850 1625
Wire Wire Line
	1850 1625 1850 1425
Connection ~ 1850 1425
Wire Wire Line
	1300 1325 1175 1325
Wire Wire Line
	1175 1325 1175 1675
Wire Wire Line
	1175 1675 1900 1675
Wire Wire Line
	1900 1675 1900 1325
Connection ~ 1900 1325
Text Label 2700 3625 0    60   ~ 0
RST
$Comp
L MSP430F5739 U2
U 1 1 5784CEA6
P 7775 4075
F 0 "U2" H 6275 5975 60  0000 C CNN
F 1 "MSP430F5739" H 7750 4075 60  0000 C CNN
F 2 "Housings_DFN_QFN:QFN-40-1EP_6x6mm_Pitch0.5mm" H 7775 4075 60  0001 C CNN
F 3 "" H 7775 4075 60  0000 C CNN
	1    7775 4075
	1    0    0    -1  
$EndComp
Connection ~ 7300 1350
Wire Wire Line
	7400 2025 7400 1350
Connection ~ 7400 1350
Wire Wire Line
	8250 2025 8250 1350
Connection ~ 8250 1350
Wire Wire Line
	8150 2025 8150 1700
Wire Wire Line
	8150 1700 7125 1700
Wire Wire Line
	7125 1700 7125 1650
Wire Wire Line
	7300 2025 7300 1700
Connection ~ 7300 1700
$Comp
L +3V3 #PWR06
U 1 1 5784D524
P 7125 1650
F 0 "#PWR06" H 7125 1500 50  0001 C CNN
F 1 "+3V3" H 7125 1790 50  0000 C CNN
F 2 "" H 7125 1650 50  0000 C CNN
F 3 "" H 7125 1650 50  0000 C CNN
	1    7125 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7725 2025 7725 1350
Connection ~ 7725 1350
Wire Wire Line
	8275 6275 8275 6300
Wire Wire Line
	8275 6300 8550 6300
Wire Wire Line
	8175 6275 8175 6400
Wire Wire Line
	8175 6400 8550 6400
Wire Wire Line
	7950 6275 7950 6450
Wire Wire Line
	7950 6450 7625 6450
Wire Wire Line
	9850 3825 10300 3825
Wire Wire Line
	9850 3725 10300 3725
Text Label 7700 6450 0    60   ~ 0
DO
Text Label 8400 6300 0    60   ~ 0
RST
Text Label 8325 6400 0    60   ~ 0
TEST
Text Label 10025 3825 0    60   ~ 0
SDA
Text Label 10025 3725 0    60   ~ 0
SCL
$EndSCHEMATC
