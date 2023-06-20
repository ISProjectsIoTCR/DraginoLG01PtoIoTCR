
#define BAUDRATE 115200
#include <Console.h>
#include <SPI.h>
#include <RH_RF95.h>
#include <Process.h>
#include <FileIO.h>


RH_RF95 rf95;

static unsigned long newtime;
static uint8_t packet[64];
int led = A2;
float frequency = 915.0;


//_______________________________CONEXIONES_____________________________________
String dId = "dId_device";
String server = "broker";
String mqttuser = "";
String mqttpass = "";


//________________________________SET_UP____________________________
void setup()
{
  pinMode(led, OUTPUT);
  Bridge.begin(BAUDRATE);
  Console.begin();
  Console.println("Start Sketch");
  if (!rf95.init())
    Console.println("init failed");
  // Setup ISM frequency
  rf95.setFrequency(frequency);
  // Setup Power,dBm
  rf95.setTxPower(13);
  // Setup Spreading Factor (6 ~ 12)
  rf95.setSpreadingFactor(7);
  // Setup BandWidth, option: 7800,10400,15600,20800,31200,41700,62500,125000,250000,500000
  rf95.setSignalBandwidth(125000);
  // Setup Coding Rate:5(4/5),6(4/6),7(4/7),8(4/8)
  rf95.setCodingRate4(5);
  Console.print("Listening on frequency: ");
  Console.println(frequency);
}

//________________________________LOOP____________________________
void loop()
{
  if (rf95.available())
  {
    // Should be a message for us now
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rf95.recv(buf, &len))
    {
      digitalWrite(led, HIGH);
      RH_RF95::printBuffer("request: ", buf, len);

      Console.print("got request: ");
      char string_data[20]; // LENGTH = Whatever length is sufficient to hold all your data
      int i = 0;
      int index = 0;
      //NUMBER_OF_ITEMS_OF_DATA could be constant or another variable
      Process p;
      for (i = 0; i < 3; i++)
      {
        Console.println(buf[i]);

        p.begin("mosquitto_pub");
        p.addParameter("-h");
        p.addParameter(server);
        p.addParameter("-p");
        p.addParameter("1883");
        p.addParameter("-u");
        p.addParameter(mqttuser);
        p.addParameter("-P");
        p.addParameter(mqttpass);
        p.addParameter("-i");
        p.addParameter("dragino_23457");
        p.addParameter("-t");
        p.addParameter("LoRaIoTCR/" + dId + "/" + i + "/slora");  //topico por defecto, si lo cambias debes modificar la plataforma IoTCR
        p.addParameter("-m");
        p.addParameter(String(buf[i]));
        p.run();
        index += sprintf(&string_data[index], "%d,", buf[i]);
        delay(1000);
      }

      p(A.begin("mosquitto_pub");
      p.addParameter("-h");
      p.addParameter(server);
      p.addParameter("-p");
      p.addParameter("1883");
      p.addParameter("-u");
      p.addParameter(mqttuser);
      p.addParameter("-P");
      p.addParameter(mqttpass);
      p.addParameter("-i");
      p.addParameter("dragino_23457");
      p.addParameter("-t");
      p.addParameter("LoRaIoTCR/" + dId + "/RSSI/slora");
      p.addParameter("-m");
      p.addParameter(String(rf95.lastRssi(), DEC));
      p.run();

      Console.print("RSSI: ");
      Console.println(rf95.lastRssi(), DEC);

      // Send a reply
      uint8_t data[] = "And hello back to you";
      rf95.send(data, sizeof(data));
      rf95.waitPacketSent();
      Console.println("Sent a reply");
      digitalWrite(led, LOW);

    }
    else
    {
      Console.println("recv failed");
    }
  }
  else {
    Console.println("listening LoRa nodes...");
  }
  feeddog();
}

//PERRO_GUARDIAN
void feeddog()
{
  int i = 0;
  memset(packet, 0, sizeof(packet));

  Process p;    // Create a process
  p.begin("date");
  p.addParameter("+%s");
  p.run();
  while (p.available() > 0 && i < 32) {
    packet[i] = p.read();
    i++;
  }
  newtime = atol(packet);

  File dog = FileSystem.open("/var/iot/dog", FILE_WRITE);
  dog.println(newtime);
  dog.close();
}
