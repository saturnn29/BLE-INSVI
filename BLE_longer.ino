#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVICE_UUID        "b249f895-9a3a-4a0b-9c60-f7ec71380af2"
#define CHARACTERISTIC_UUID "dfc4e66f-c04a-4f7f-9dfa-38868b3e8eed"

BLEServer *pServer = NULL;
BLECharacteristic *pCharacteristic = NULL;
BLEAdvertising *pAdvertising;

void setup() {
    Serial.begin(115200);
    BLEDevice::init("ESP32_BLE_3");

    pServer = BLEDevice::createServer();
    BLEService *pService = pServer->createService(SERVICE_UUID);

    pCharacteristic = pService->createCharacteristic(
                        CHARACTERISTIC_UUID,
                        BLECharacteristic::PROPERTY_READ |
                        BLECharacteristic::PROPERTY_NOTIFY
                      );

    pCharacteristic->setValue("Location Data");
    pService->start();

    pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06); 
    pAdvertising->setMinPreferred(0x12);
    pAdvertising->start();

    Serial.println("BLE Advertising Started...");
}

void loop() {
    delay(3000);  // Ensure BLE continues advertising
    pAdvertising->start();  // Restart advertising if stopped
}
