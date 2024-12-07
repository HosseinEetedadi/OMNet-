package smartcitysimulation;

simple IoTDevice {
    parameters:
        double taskGenerationInterval @unit(s); // Task generation interval (seconds)
        double taskSize; // Task size or complexity
    gates:
        output out;  // Sends tasks to the SDN Controller or other devices
        input in;    // Receives responses from the SDN controller or processing units
}
