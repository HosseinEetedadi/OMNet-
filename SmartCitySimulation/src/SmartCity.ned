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

import smartcitysimulation.IoTDevice;
import smartcitysimulation.MECServer;
import smartcitysimulation.SDNController;

network SmartCity
{
    submodules:
        iot[10]: IoTDevice {
            @display("p=100,200");
        }
        mec[5]: MECServer {
            serverType = "Fixed";
            @display("p=300,200");
        }
        drones[3]: MECServer {
            serverType = "Drone";
            @display("p=400,300");
        }
        controller: SDNController {
            @display("p=500,200");
        }
    connections:
        for i=0..9 {
            iot[i].out --> controller.in++;
            controller.out++ --> iot[i].in;
        }
        for i=0..4 {
            mec[i].out --> controller.in++;
            controller.out++ --> mec[i].in;
        }
        for i=0..2 {
            drones[i].out --> controller.in++;
            controller.out++ --> drones[i].in;
        }
}
