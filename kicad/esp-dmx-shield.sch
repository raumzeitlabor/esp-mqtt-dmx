EESchema Schematic File Version 4
LIBS:esp-dmx-shield-cache
EELAYER 26 0
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
L RF_Module:ESP-12E U1
U 1 1 5C4DAD3D
P 4950 2950
F 0 "U1" H 4950 3928 50  0000 C CNN
F 1 "ESP-12E" H 4950 3837 50  0000 C CNN
F 2 "RF_Module:ESP-12E" H 4950 2950 50  0001 C CNN
F 3 "http://wiki.ai-thinker.com/_media/esp8266/esp8266_series_modules_user_manual_v1.1.pdf" H 4600 3050 50  0001 C CNN
	1    4950 2950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5C4DAF4E
P 2300 4900
F 0 "#PWR0101" H 2300 4650 50  0001 C CNN
F 1 "GND" H 2305 4727 50  0000 C CNN
F 2 "" H 2300 4900 50  0001 C CNN
F 3 "" H 2300 4900 50  0001 C CNN
	1    2300 4900
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0102
U 1 1 5C4DB0AA
P 2300 1650
F 0 "#PWR0102" H 2300 1500 50  0001 C CNN
F 1 "+3.3V" H 2315 1823 50  0000 C CNN
F 2 "" H 2300 1650 50  0001 C CNN
F 3 "" H 2300 1650 50  0001 C CNN
	1    2300 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 4900 2300 4800
Wire Wire Line
	2300 4500 2900 4500
Wire Wire Line
	4950 4500 4950 3650
Connection ~ 4950 4500
$Comp
L Connector:Conn_01x03_Male J1
U 1 1 5C4DB517
P 8000 2150
F 0 "J1" H 7973 2080 50  0000 R CNN
F 1 "Conn_01x03_Male" H 7973 2171 50  0000 R CNN
F 2 "Jumper:SolderJumper-3_P1.3mm_Open_Pad1.0x1.5mm_NumberLabels" H 8000 2150 50  0001 C CNN
F 3 "~" H 8000 2150 50  0001 C CNN
	1    8000 2150
	-1   0    0    1   
$EndComp
Wire Wire Line
	7800 4500 7800 2250
Wire Wire Line
	5550 2450 7000 2450
Wire Wire Line
	7000 2450 7000 2050
Wire Wire Line
	7000 2050 7800 2050
Wire Wire Line
	5550 2650 7100 2650
Wire Wire Line
	7100 2650 7100 2150
Wire Wire Line
	7100 2150 7800 2150
Wire Wire Line
	4950 4500 5700 4500
$Comp
L Device:R R3
U 1 1 5C4DC610
P 5700 3650
F 0 "R3" H 5630 3604 50  0000 R CNN
F 1 "4k7" H 5630 3695 50  0000 R CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 5630 3650 50  0001 C CNN
F 3 "~" H 5700 3650 50  0001 C CNN
	1    5700 3650
	-1   0    0    1   
$EndComp
Wire Wire Line
	5700 3800 5700 4500
Connection ~ 5700 4500
Wire Wire Line
	5700 4500 6250 4500
Wire Wire Line
	5550 3250 5700 3250
Wire Wire Line
	5700 3250 5700 3500
$Comp
L Device:C C2
U 1 1 5C4DCDEE
P 2900 2850
F 0 "C2" H 3015 2896 50  0000 L CNN
F 1 "100nF" H 3015 2805 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 2938 2700 50  0001 C CNN
F 3 "~" H 2900 2850 50  0001 C CNN
	1    2900 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 2150 4950 1700
Wire Wire Line
	4950 1700 2900 1700
Wire Wire Line
	2900 2700 2900 2550
Connection ~ 2900 1700
Wire Wire Line
	2900 1700 2300 1700
$Comp
L Device:R R1
U 1 1 5C4DD5FD
P 3600 2550
F 0 "R1" V 3807 2550 50  0000 C CNN
F 1 "4k7" V 3716 2550 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 3530 2550 50  0001 C CNN
F 3 "~" H 3600 2550 50  0001 C CNN
	1    3600 2550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3450 2550 2900 2550
Connection ~ 2900 2550
Wire Wire Line
	2900 2550 2900 2350
Wire Wire Line
	3750 2550 4350 2550
Wire Wire Line
	2900 3000 2900 4500
Connection ~ 2900 4500
Wire Wire Line
	2900 4500 4950 4500
Connection ~ 4950 1700
Wire Wire Line
	5700 2550 5550 2550
$Comp
L Switch:SW_SPDT SW1
U 1 1 5C4DFB1D
P 6350 2100
F 0 "SW1" H 6350 2385 50  0000 C CNN
F 1 "SW_SPDT" H 6350 2294 50  0000 C CNN
F 2 "Jumper:SolderJumper-3_P1.3mm_Open_Pad1.0x1.5mm" H 6350 2100 50  0001 C CNN
F 3 "" H 6350 2100 50  0001 C CNN
	1    6350 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 2350 6150 2350
Wire Wire Line
	6150 2350 6150 2100
Wire Wire Line
	6550 2000 6550 1700
Wire Wire Line
	6550 2200 6550 4500
Connection ~ 6550 4500
Wire Wire Line
	6550 4500 7800 4500
$Comp
L power:+5V #PWR0103
U 1 1 5C4E3101
P 900 900
F 0 "#PWR0103" H 900 750 50  0001 C CNN
F 1 "+5V" H 915 1073 50  0000 C CNN
F 2 "" H 900 900 50  0001 C CNN
F 3 "" H 900 900 50  0001 C CNN
	1    900  900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	900  900  1000 900 
Wire Wire Line
	1500 900  1500 1050
Wire Wire Line
	2300 1700 2300 1650
Wire Wire Line
	2100 1700 2300 1700
Connection ~ 2300 1700
Wire Wire Line
	1800 4500 2300 4500
Connection ~ 2300 4500
$Comp
L Device:C C1
U 1 1 5C4EE3AC
P 1100 1600
F 0 "C1" H 1215 1646 50  0000 L CNN
F 1 "100nF" H 1215 1555 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 1138 1450 50  0001 C CNN
F 3 "~" H 1100 1600 50  0001 C CNN
	1    1100 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 900  1100 1450
Connection ~ 1100 900 
Wire Wire Line
	1100 1750 1800 1750
Connection ~ 1800 1750
Wire Wire Line
	1800 1750 1800 4500
$Comp
L Device:R R4
U 1 1 5C4DCDF9
P 3600 2350
F 0 "R4" V 3807 2350 50  0000 C CNN
F 1 "4k7" V 3716 2350 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 3530 2350 50  0001 C CNN
F 3 "~" H 3600 2350 50  0001 C CNN
	1    3600 2350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4350 2350 3750 2350
Wire Wire Line
	3450 2350 2900 2350
Connection ~ 2900 2350
Wire Wire Line
	2900 2350 2900 1700
$Comp
L Device:R R6
U 1 1 5C4DEC88
P 6200 1700
F 0 "R6" H 6270 1746 50  0000 L CNN
F 1 "4k7" H 6270 1655 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 6130 1700 50  0001 C CNN
F 3 "~" H 6200 1700 50  0001 C CNN
	1    6200 1700
	0    1    1    0   
$EndComp
Wire Wire Line
	6350 1700 6550 1700
$Comp
L Connector:Conn_01x01_Male J2
U 1 1 5C4EBE35
P 1000 700
F 0 "J2" V 1060 740 50  0000 L CNN
F 1 "Conn_01x01_Male" V 1151 740 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 1000 700 50  0001 C CNN
F 3 "~" H 1000 700 50  0001 C CNN
	1    1000 700 
	0    1    1    0   
$EndComp
Connection ~ 1000 900 
Wire Wire Line
	1000 900  1100 900 
$Comp
L Connector:Conn_01x01_Male J3
U 1 1 5C4EC3CB
P 2100 4800
F 0 "J3" H 2206 4978 50  0000 C CNN
F 1 "Conn_01x01_Male" H 2206 4887 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 2100 4800 50  0001 C CNN
F 3 "~" H 2100 4800 50  0001 C CNN
	1    2100 4800
	1    0    0    -1  
$EndComp
Connection ~ 2300 4800
Wire Wire Line
	2300 4800 2300 4500
Wire Wire Line
	4950 1700 6050 1700
$Comp
L Connector:Conn_01x01_Male J4
U 1 1 5C4F6D43
P 5900 2550
F 0 "J4" H 6006 2728 50  0000 C CNN
F 1 "Conn_01x01_Male" H 6006 2637 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 5900 2550 50  0001 C CNN
F 3 "~" H 5900 2550 50  0001 C CNN
	1    5900 2550
	-1   0    0    1   
$EndComp
Wire Wire Line
	1100 900  1500 900 
Wire Wire Line
	2100 1050 2100 1700
Wire Wire Line
	1800 1350 1800 1750
$Comp
L Device:LED D1
U 1 1 5C502D68
P 6250 3250
F 0 "D1" V 6288 3133 50  0000 R CNN
F 1 "LED" V 6197 3133 50  0000 R CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_Pad1.0x1.5mm" H 6250 3250 50  0001 C CNN
F 3 "~" H 6250 3250 50  0001 C CNN
	1    6250 3250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5550 2750 6250 2750
Wire Wire Line
	6250 2750 6250 3100
Wire Wire Line
	6250 3400 6250 4500
Connection ~ 6250 4500
Wire Wire Line
	6250 4500 6550 4500
$Comp
L Regulator_Linear:LD1117S33TR_SOT223 U2
U 1 1 5C51CDE9
P 1800 1050
F 0 "U2" H 1800 1292 50  0000 C CNN
F 1 "LD1117S33TR_SOT223" H 1800 1201 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 1800 1250 50  0001 C CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00000544.pdf" H 1900 800 50  0001 C CNN
	1    1800 1050
	1    0    0    -1  
$EndComp
$EndSCHEMATC
