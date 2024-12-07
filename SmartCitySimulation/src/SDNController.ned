//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package smartcitysimulation;

simple SDNController {
    parameters:
        int numMECDevices;          // Number of MEC devices
        int numCoreServers;         // Number of core servers
        int coreServerCapacity;     // Capacity of each core server
        double epsilon = default(0.1);  // Exploration rate
        double alpha = default(0.1);    // Learning rate
        double gamma = default(0.9);    // Discount factor
    gates:
        input in[];         // Input gate vector for messages from MEC servers
        output out[];       // Output gate vector for messages to MEC servers
        input coreIn[];     // Input gate vector for messages from Core servers
        output coreOut[];   // Output gate vector for messages to Core servers
		input iotIn[];       // Input gate vector for messages from IoT devices
        output iotOut[];     // Output gate vector for messages to IoT devices
}