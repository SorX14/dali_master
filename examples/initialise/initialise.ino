// This #include statement was automatically added by the Particle IDE.
#include <dali_master.h>
Dali_master dali;

void setup() {
    delay(5000);
    Serial.begin();
    Serial.println("Start...");
    dali.begin(0x23); // Default address
    Serial.println("setup done");
}

void loop() {
    Serial.println("Loop start");
    scanShortAddresses();
    Serial.println("scanShortAddress done");
    initialise();
    Serial.println("initialise done");
    scanShortAddresses();
    Serial.println("scanShortAddress done");
    
    while (true) {
        delay(1000);
    }
}

void initialise()
{
    Serial.println("Initialising connected devices...");
    dali.transmitCommand(TERMINATE_C, BLANK_C); // Stop any existing initialisation
    
    dali.transmitCommand(RESET_C, BLANK_C); // Reset
    delay(10);
    dali.transmitCommand(RESET_C, BLANK_C); // (send twice within 100ms)
    
    dali.transmitCommand(BROADCAST_C, OFF_C); // Turn all devices off
    dali.transmitCommand(INITIALISE_C, BLANK_C); // Start initisation process 
    delay(10);
    dali.transmitCommand(INITIALISE_C, BLANK_C); // (send twice within 100ms)
    delay(10);
    dali.transmitCommand(RANDOMISE_C, BLANK_C); // Tell devices to create a random 24 bit address
    delay(10);
    dali.transmitCommand(RANDOMISE_C, BLANK_C); // (send twice within 100ms)
    
    uint8_t highbyte;
    uint8_t middlebyte;
    uint8_t lowbyte;
    
    long low_longadd = 0x000000;
    long high_longadd = 0xFFFFFF;
    long longadd = (long)(low_longadd + high_longadd) / 2;
    uint8_t short_add = 0;
    for (uint8_t y = 0; y <= 100; y++) {
        short_add = random(0, 60);
    }
    Serial.print("Device ID from: ");
    Serial.print(short_add);
    Serial.println();
    
    while (longadd <= 0xFFFFFF - 2 && short_add <= 64) {
        while ((high_longadd - low_longadd) > 1) {
            Serial.print("Searching for: ");
            Serial.print(longadd);
            
            dali.splitAdd(longadd, highbyte, middlebyte, lowbyte);
            dali.transmitCommand(SEARCHADDRH_C, highbyte);
            dali.transmitCommand(SEARCHADDRM_C, middlebyte);
            dali.transmitCommand(SEARCHADDRL_C, lowbyte);
            
            bool reply;
            byte cmd1;
            byte cmd2;
            
            byte a = dali.transmitCommand(COMPARE_C, BLANK_C, reply, cmd1, cmd2);
            Serial.print(" ");
            dali.explainStatus(a);
            
            if (reply) {
                while (cmd1 != 0xFF && reply) {
                    dali.transmitCommand(COMPARE_C, BLANK_C, reply, cmd1, cmd2);
                    Serial.print("RETRY [");
                    Serial.print(cmd1);
                    Serial.println("]");
                }
                
                Serial.print(" \\/");
                high_longadd = longadd;
            } else {
                Serial.print(" /\\");
                low_longadd = longadd;
            }

            Serial.println();
            
            longadd = (low_longadd + high_longadd) / 2;
        }
        
        if (high_longadd != 0xFFFFFF) {
            Serial.print("Found luminaire!! ");
            Serial.print("Enter device ID: ");
            uint8_t choosenId = serialInput();
            Serial.println();
            Serial.print("Setting ID to ");
            Serial.println(choosenId);
            
            dali.splitAdd(longadd + 1, highbyte, middlebyte, lowbyte);
            dali.transmitCommand(SEARCHADDRH_C, highbyte);
            dali.transmitCommand(SEARCHADDRM_C, middlebyte);
            dali.transmitCommand(SEARCHADDRL_C, lowbyte);
            delay(100);
            dali.transmitCommand(PROGRAMSHORT_C, 1 + (choosenId << 1)); // Program short address
            delay(100);
            dali.transmitCommand(WITHDRAW_C, BLANK_C); // Withdraw from search
            
            delay(100);
            
            dali.flashDevice(choosenId);
            short_add++;
            short_add++;
            
            high_longadd = 0xFFFFFF;
            longadd = (low_longadd + high_longadd) / 2;
        }
    }
    
    dali.transmitCommand(TERMINATE_C, BLANK_C); // Finish initialisation
    dali.transmitCommand(BROADCAST_C, ON_C);
    delay(1000);
    dali.transmitCommand(BROADCAST_C, OFF_C);
    
    Serial.println("DONE!");
}

void scanShortAddresses()
{
    uint8_t deviceId;
    uint8_t deviceAddress;
    
    Serial.println("Scanning for addressable devices...");
    
    dali.transmitCommand(BROADCAST_C, OFF_C);
    
    for (deviceId = 0; deviceId <= 64; deviceId++)
    {
        Serial.print("Scanning for device ");
        Serial.print(deviceId);
        Serial.print("...");
        
        deviceAddress = 1 + (deviceId << 1);
        byte cmd1, cmd2;
        bool reply;
        
        dali.transmitCommand(deviceAddress, QUERY_MAX_LEVEL_C, reply, cmd1, cmd2);
        if (reply && cmd1 == 0xFE) {
            Serial.println(" VALID :)");
        } else {
            Serial.println(" NOT FOUND :(");
        }
    }   
    
    Serial.println("DONE!");
}

uint8_t serialInput()
{
    const int bufferSize = 128;
    int bufferPointer = 0;
    char inputBuffer[128];
    while (true) {
        delay(10);
        char inByte;

        if (Serial.available()) {
            inByte = Serial.read();

            if (inByte == '\n') {
                // 'newline' character
                inputBuffer[bufferPointer++] = '\0';
                return constrain(atoi(inputBuffer), 0, 62);
            } else {
                Serial.print(inByte);
                // not a 'newline' character
                if (bufferPointer < bufferSize - 1)  {// Leave room for a null terminator
                    inputBuffer[bufferPointer++] = inByte;                
                } else {
                    bufferPointer = 0;
                }
            }
        }
    }
    
}