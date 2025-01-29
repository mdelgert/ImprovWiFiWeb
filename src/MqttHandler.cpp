#ifdef ENABLE_MQTT_HANDLER

#include "MqttHandler.h"
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <LittleFS.h>

// Create MQTT client; the actual client depends on the SSL flag
WiFiClient wiFiClient;
WiFiClientSecure wiFiClientSecure;
PubSubClient mqttClient;

// Optional: Use a NonBlockingTimer to avoid continuously retrying in busy loops
static NonBlockingTimer mqttTimer(60000);

void MqttHandler::init()
{
    // Use the appropriate client based on SSL settings
    if (settings.mqttSsl)
    {
        debugI("MqttHandler: Using secure WiFi client.");

        // Mount LittleFS (if not already mounted)
        if (!LittleFS.begin())
        {
            debugE("MqttHandler: Failed to initialize LittleFS.");
            return;
        }

        // Open the certificate file
        File certFile = LittleFS.open(EMQX_CERT_FILE, "r");
        if (!certFile)
        {
            debugE("MqttHandler: Failed to open certificate file: %s", EMQX_CERT_FILE);
            return;
        }

        // Read the certificate content
        String certContent = certFile.readString();
        certFile.close();

        wiFiClientSecure.setCACert(certContent.c_str());
        // wiFiClientSecure.setCACert(ca_cert);
        mqttClient.setClient(wiFiClientSecure);
    }
    else
    {
        debugI("MqttHandler: Using non-secure WiFi client.");
        mqttClient.setClient(wiFiClient);
    }

    // Point the MQTT client to the broker from settings
    mqttClient.setServer(settings.mqttServer.c_str(), settings.mqttPort);

    // Set the incoming message callback
    mqttClient.setCallback(MqttHandler::mqttCallback);

    // Attempt initial connection
    connectToMqtt();

    registerCommands();
}

void MqttHandler::loop()
{
    // If not connected, attempt to reconnect
    if (!mqttClient.connected())
    {
        if (mqttTimer.isReady())
        {
            debugW("MqttHandler: Not connected, attempting reconnect...");
            connectToMqtt();
        }
    }
    else
    {
        // Process the incoming MQTT traffic
        mqttClient.loop();
    }
}

void MqttHandler::publish(const char *topic, const char *message)
{
    // If not connected, attempt to reconnect
    if (!mqttClient.connected())
    {
        debugW("MqttHandler: Not connected, attempting reconnect before publish...");
        connectToMqtt();
    }

    debugI("MqttHandler: Publishing on [%s]: %s", topic, message);
    mqttClient.publish(topic, message);
}

void MqttHandler::connectToMqtt()
{
    debugI("MqttHandler: Attempting MQTT connection to %s:%d", settings.mqttServer.c_str(), settings.mqttPort);

    bool isConnected = false;

    // If username/password are not empty, use them
    if (!settings.mqttUsername.isEmpty() || !settings.mqttPassword.isEmpty())
    {
        debugI("MqttHandler: Trying MQTT connect with user/pass: [%s]/[****]", settings.mqttUsername.c_str());
        isConnected = mqttClient.connect(settings.deviceName.c_str(), settings.mqttUsername.c_str(), settings.mqttPassword.c_str());
    }
    else
    {
        debugI("MqttHandler: Trying MQTT connect WITHOUT credentials");
        isConnected = mqttClient.connect(settings.deviceName.c_str());
    }

    if (isConnected)
    {
        debugI("MqttHandler: Connected as client [%s]", settings.deviceName.c_str());

        // Subscribe to the topic from settings
        mqttClient.subscribe(settings.mqttSubTopic.c_str());
        debugI("MqttHandler: Subscribed to [%s]", settings.mqttSubTopic.c_str());

        // Optionally publish a "hello" message
        // publish(settings.mqttPubTopic.c_str(), "Hello from ESP32-S3!");

        String helloMessage = "Device: " + settings.deviceName + " connected.";
        publish(settings.mqttPubTopic.c_str(), helloMessage.c_str());
    }
    else
    {
        debugE("MqttHandler: Connection failed, state=%d. Will retry...", mqttClient.state());
    }
}

void MqttHandler::mqttCallback(char *topic, byte *payload, unsigned int length)
{
    String message;
    for (unsigned int i = 0; i < length; i++)
    {
        message += (char)payload[i];
    }

    debugI("MqttHandler: Received on [%s]: %s", topic, message.c_str());

    // If incoming message is on the subscribed topic, echo it out
    if (String(topic) == settings.mqttSubTopic)
    {
        debugD("MqttHandler: Echoing message to publish topic");
        publish(settings.mqttPubTopic.c_str(), message.c_str());
        // Debug.wsOnReceive(message.c_str());
        CommandHandler::handleCommand(message);
    }
}

void MqttHandler::registerCommands()
{
    CommandHandler::registerCommand("MQTT", [](const String &command)
                                    {
        String cmd, args;
        CommandHandler::parseCommand(command, cmd, args);

        if (CommandHandler::equalsIgnoreCase(cmd, "MSG")) {
            MqttHandler::publish(settings.mqttPubTopic.c_str(), args.c_str());
        }
        else if (CommandHandler::equalsIgnoreCase(cmd, "TOPIC")) {
            int delimiterPos = args.indexOf(' ');
            String topic = args.substring(0, delimiterPos);
            String message = args.substring(delimiterPos + 1);
            MqttHandler::publish(topic.c_str(), message.c_str());
        } 
        else {
            debugW("Unknown MQTT subcommand: %s", cmd.c_str());
        } }, "Handles MQTT commands. Usage: MQTT <subcommand> [args]\n"
                                         "  Subcommands:\n"
                                         "  msg <message> - Publishes a message to the MQTT broker default topic\n"
                                         "  topic <topic> <message> - Publishes a message to the specified topic");
}

#endif // ENABLE_MQTT_HANDLER

/*
debugI("settings.mqttServer: %s", settings.mqttServer.c_str());
debugI("settings.mqttPort: %d", settings.mqttPort);
debugI("settings.mqttUsername: %s", settings.mqttUsername.c_str());
debugI("settings.mqttPassword: %s", settings.mqttPassword.c_str());
*/