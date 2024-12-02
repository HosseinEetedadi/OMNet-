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

#include <omnetpp.h>

using namespace omnetpp;

class IoTDevice : public cSimpleModule {
protected:
    virtual void initialize() override {
        // Schedule the first task generation
        scheduleAt(simTime() + uniform(1, 5), new cMessage("generateTask"));
    }

    virtual void handleMessage(cMessage *msg) override {
        if (strcmp(msg->getName(), "generateTask") == 0) {
            // Generate a new task and send it out
            cMessage *task = new cMessage("task");
            send(task, "out");

            // Schedule the next task
            scheduleAt(simTime() + uniform(1, 5), msg);
        }
    }
};

Define_Module(IoTDevice);
