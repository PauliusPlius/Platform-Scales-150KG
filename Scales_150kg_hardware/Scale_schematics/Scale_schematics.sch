EESchema Schematic File Version 4
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Scales_150kg"
Date "2019-02-11"
Rev "v02"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 "designed by MACROlab"
$EndDescr
$Comp
L MCU_Module:Arduino_Nano_v3.x A?
U 1 1 5C60A98B
P 4600 4600
F 0 "A?" H 4600 3514 50  0000 C CNN
F 1 "Arduino_Nano_v3.x" H 4600 3423 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 4750 3650 50  0001 L CNN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 4600 3600 50  0001 C CNN
	1    4600 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 5600 4600 5900
Wire Wire Line
	4700 5600 4700 5900
Wire Wire Line
	4700 5900 4600 5900
Connection ~ 4600 5900
$Comp
L power:GND #PWR?
U 1 1 5C60BA42
P 7100 5550
F 0 "#PWR?" H 7100 5300 50  0001 C CNN
F 1 "GND" H 7105 5377 50  0000 C CNN
F 2 "" H 7100 5550 50  0001 C CNN
F 3 "" H 7100 5550 50  0001 C CNN
	1    7100 5550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C60BA6F
P 4600 6250
F 0 "#PWR?" H 4600 6000 50  0001 C CNN
F 1 "GND" H 4605 6077 50  0000 C CNN
F 2 "" H 4600 6250 50  0001 C CNN
F 3 "" H 4600 6250 50  0001 C CNN
	1    4600 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 5900 4600 6250
$Comp
L power:+5V #PWR?
U 1 1 5C60BD00
P 4800 3450
F 0 "#PWR?" H 4800 3300 50  0001 C CNN
F 1 "+5V" H 4815 3623 50  0000 C CNN
F 2 "" H 4800 3450 50  0001 C CNN
F 3 "" H 4800 3450 50  0001 C CNN
	1    4800 3450
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5C60BD2A
P 7100 3350
F 0 "#PWR?" H 7100 3200 50  0001 C CNN
F 1 "+5V" H 7115 3523 50  0000 C CNN
F 2 "" H 7100 3350 50  0001 C CNN
F 3 "" H 7100 3350 50  0001 C CNN
	1    7100 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 3450 4800 3600
$Comp
L Scales_Library:LCD_20x2 J?
U 1 1 5C60D353
P 7100 4400
F 0 "J?" H 7100 5328 50  0000 C CNN
F 1 "LCD_20x2" H 7100 5237 50  0000 C CNN
F 2 "" H 7150 4750 50  0001 C CNN
F 3 "" H 7150 4750 50  0001 C CNN
	1    7100 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 3650 7100 3350
Wire Wire Line
	7100 5200 7100 5550
$Comp
L Device:R_POT RV?
U 1 1 5C60D478
P 7950 3850
F 0 "RV?" H 7880 3804 50  0000 R CNN
F 1 "10K" H 7880 3895 50  0000 R CNN
F 2 "" H 7950 3850 50  0001 C CNN
F 3 "~" H 7950 3850 50  0001 C CNN
	1    7950 3850
	-1   0    0    1   
$EndComp
$EndSCHEMATC
