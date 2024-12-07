package smartcitysimulation;

network SmartCity {
    submodules:
        controller: SDNController {
            gates:
                in[5];          // Input gates for messages from MEC servers
                out[5];         // Output gates for messages to MEC servers
                coreIn[3];      // Input gates for messages from Core servers
                coreOut[3];     // Output gates for messages to Core servers
                iotIn[10];      // Input gates for messages from IoT devices
                iotOut[10];     // Output gates for messages to IoT devices
        }
        mec[5]: MECServer {     // Array of 5 MEC servers
            parameters:
                processingCapacity = 10; // MEC server capacity
        }
        coreServer[3]: CoreServer { // Array of 3 Core servers
            parameters:
                processingCapacity = 50; // Core server capacity
        }
        iot[10]: IoTDevice {    // Array of 10 IoT devices
            parameters:
                taskGenerationInterval = 1s; // Task generation interval
                taskSize = 1;                // Task size or complexity
        }
    connections allowunconnected:
        // Bidirectional connection between MEC servers and SDN Controller
        for i = 0..sizeof(mec) - 1 {
            controller.out[i] --> mec[i].in;
            mec[i].out --> controller.in[i];
        }

        // Bidirectional connection between Core servers and SDN Controller
        for i = 0..sizeof(coreServer) - 1 {
            controller.coreOut[i] --> coreServer[i].in;
            coreServer[i].out --> controller.coreIn[i];
        }

        // Bidirectional connection between IoT devices and SDN Controller
        for i = 0..sizeof(iot) - 1 {
            iot[i].out --> controller.iotIn[i];
            controller.iotOut[i] --> iot[i].in;
        }
}
