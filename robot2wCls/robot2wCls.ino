
#define   PIN_LED_LIVE          13 //LED blink
#define   BLINK_TIME            1000 //Mili second
/*
//-------For UNO
#define   PIN_BT_RX             2 //Bluetooth RX 
#define   PIN_BT_TX             3 //Bluetooth TX
#define   PIN_SPEED_MOT_KANAN   6 //Motor Speed Kanan PWM
#define   PIN_MOT_KANAN1        7 //Motor Kanan Positive
#define   PIN_MOT_KANAN2        8 //Motor Kanan Negative
#define   PIN_SPEED_MOT_KIRI    9 //Motor Speed Kiri PWM
#define   PIN_MOT_KIRI1         10 //Motor Kiri Positive
#define   PIN_MOT_KIRI2         11 //Motor Kiri Negative
*/
//-------For MEGA
//#define   PIN_BT_RX             2 //Bluetooth RX, Use Serial1 
//#define   PIN_BT_TX             3 //Bluetooth TX, Use Serial1
#define   PIN_SPEED_MOT_KANAN   44 //Motor Speed Kanan PWM
#define   PIN_MOT_KANAN1        50 //Motor Kanan Positive
#define   PIN_MOT_KANAN2        51 //Motor Kanan Negative
#define   PIN_SPEED_MOT_KIRI    45 //Motor Speed Kiri PWM
#define   PIN_MOT_KIRI1         52 //Motor Kiri Positive
#define   PIN_MOT_KIRI2         53 //Motor Kiri Negative
#define   PIN_SENSOR_GARIS_KIRI     A8 //Pin sensor cahaya kiri
#define   PIN_SENSOR_GARIS_KANAN    A9 //Pin sensor cahaya kanan
#define   PIN_SENSOR_JARAK          A10 //Pin sensor cahaya kanan
#define   PIN_SERVO                 46 //Pin Servo motor

#define   TURN_RATIO            10 //in percentage
#define   MAX_SPEED             0xFF //255
#define   MAX_GEAR              6 //Max Gear position
#define   MAX_TRACK             20 //Max tracking record
#define   MAX_IDL               25000 //Max Idle time milli second

#define   STOP_BT           '%' //Stop Bluetooth Command
#define   INV_CMD           '%' //Stop Bluetooth Command
#define   STOP_TRACK        'X' //Stop Track command
#define   STOP_RECORD       'X' //Stop Track command
#define   STOP_REMOTE       'X' //Stop Track command
#define   STOP_AUTO         'X' //Stop Track command
#define   BAUD_BT           57600 //Baud rate Bluetooth bps

#define   MAJU              'A' //Robot Maju
#define   MUNDUR            'B' //Robot Mundur
#define   BELOK_KIRI        'C' //Robot Belok Kiri
#define   BELOK_KANAN       'D' //Robot Belok Kanan
#define   MAJU_KIRI         'E' //Robot Maju Serong Kiri
#define   MAJU_KANAN        'F' //Robot Maju Serong Kanan
#define   MUNDUR_KIRI       'G' //Robot Mundur Serong Kiri
#define   MUNDUR_KANAN      'H' //Robot Mundur Serong Kanan
#define   BERHENTI          'I' //Stop Bluetooth Command

#define   MENU_UTAMA        'M' //Robot in Main menu 
#define   REMOTE            'L' //Robot Remote/Linnk by Remote Control
#define   SENAM             'S' //Robot Senam Mode
#define   RECORD            'R' //Robot Record Action
#define   TRACKING          'T' //Play on Tracking record
#define   AUTO_GARIS        'Q' //Play on Auto garis
#define   AUTO_JARAK        'J' //Play on Auto Jarak
#define   GEAR0             '0' //Gear position 0
#define   GEAR1             '1' //Gear position 1
#define   GEAR2             '2' //Gear position 2
#define   GEAR3             '3' //Gear position 3
#define   GEAR4             '4' //Gear position 4
#define   GEAR5             '5' //Gear position 5
#define   GEAR6             '6' //Gear position 6

//----------LCD TFT
#define   MINPRESSURE   200
#define   MAXPRESSURE   1000

#define   BLACK         0x0000
#define   NAVY          0x000F
#define   DARKGREEN     0x03E0
#define   DARKCYAN      0x03EF
#define   MAROON        0x7800
#define   PURPLE        0x780F
#define   OLIVE         0x7BE0
#define   LIGHTGREY     0xC618
#define   DARKGREY      0x7BEF
#define   BLUE          0x001F
#define   GREEN         0x07E0
#define   CYAN          0x07FF
#define   RED           0xF800
#define   MAGENTA       0xF81F
#define   YELLOW        0xFFE0
#define   WHITE         0xFFFF
#define   ORANGE        0xFD20
#define   GREENYELLOW   0xAFE5
#define   PINK          0xF81F

#define   MAX_CAHAYA    100 //Maximum nilai cahaya
#define   GELAP         80 //Batas gelap - terang
#define   ORT_KIRI      0 //Orientasi ukur jarak Kiri
#define   ORT_KANAN     180 //Orientasi ukur jarak Kanan
#define   ORT_LURUS     90 //Orientasi ukur jarak Lurus
#define   TRIGGER_PIN   47  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define   ECHO_PIN      48  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define   MAX_DISTANCE  200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define   JARAK_AMAN    20 // Maximum jarak aman cm 
#define   MILIS_RAND    1500 // lama gerakan random robot dalam milli detik
//-----------------
struct cmdRobot
{
  char cmd;//Command
  unsigned long miliS;//mili second
  struct cmdRobot *next; 
};

struct lcdMenu
{
  char title[15];//page menu title
  byte level;//level of deepness of menu
};

struct sensorRobot
{
  int Kiri;//Sensor kiri
  int Kanan;//Sensor kanan
  int JarakKiri;//Sensor jarak kiri
  int JarakLurus;//Sensor jarak Lurus
  int JarakKanan;//Sensor jarak kiri
};

struct freeRobot
{
  boolean Kiri;//Sensor kiri
  boolean Kanan;//Sensor kanan
  boolean JarakKiri;//Sensor jarak kiri
  boolean JarakLurus;//Sensor jarak Lurus
  boolean JarakKanan;//Sensor jarak kiri
};

struct modeRobot{
  boolean Utama;
  boolean Senam;
  boolean Remote;
  boolean Record;
  boolean Tracking;
  boolean AutoGaris;
  boolean AutoJarak;
};

enum 
{     
  // The first register starts at address 0
//Data perintah
  PAGE_UTAMA, //index 0    
  PAGE_REMOTE, //index 1    
  PAGE_SENAM, //index 2    
  PAGE_RECORD, //index 3    
  PAGE_TRACKING, //index 4    
  PAGE_AUTO_GARIS, //index 5    
  PAGE_AUTO_JARAK, //index 6
  MAX_MODE 
  // total number of registers
};
boolean printDiagOK = false;


volatile byte menuPage;
char* menuTitle[] = {"ROBOT CERDAS", "MODE REMOTE", "MODE SENAM",
                      "MODE RECORD", "MODE TRACKING", "MODE A.GARIS", "MODE A.JARAK"};

struct cmdRobot* frontCmdSenam = NULL;
struct cmdRobot* rearCmdSenam = NULL;
struct cmdRobot* frontCmdTrack = NULL;
struct cmdRobot* rearCmdTrack = NULL;
modeRobot ModeRobot;
volatile int iTrack = 0;
volatile int iSnm = 0;
volatile int iRcd = 0;
unsigned long prevRcdMs;

//this funtion is special treatment
boolean isRobotBusy(modeRobot modeVal){
  if (modeVal.Senam) return true;
  if (modeVal.Remote) return true;
  if (modeVal.Record) return true;
  if (modeVal.Tracking) return true;
  if (modeVal.AutoGaris) return true;
  if (modeVal.AutoJarak) return true;
  else return false;
}

                      
