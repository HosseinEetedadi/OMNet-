package sdnproject;
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.ethernet.Eth100M;
import inet.node.ethernet.Eth1G;
import inet.mobility.tracemobility.TractorMobility;
import inet.node.inet.Router;
import inet.node.openflow.OpenFlowSwitch;
import inet.node.inet.StandardHost;
import inet.node.inet.WirelessHost;
import inet.node.inet.BaseStation;
import inet.node.wireless.AccessPoint;
import inet.physicallayer.wireless.ieee80211.packetlevel.Ieee80211ScalarRadioMedium;
import inet.physicallayer.wireless.common.contract.packetlevel.IRadioMedium;
import inet.visualizer.contract.IIntegratedVisualizer;

network WiredAndWirelessHostsWithAP
{
    parameters:

        @display("bgb=3500,3500;bgg=100,1,grey95");

    submodules:
        visualizer: <default(firstAvailableOrEmpty("IntegratedCanvasVisualizer"))> like IIntegratedVisualizer if typename != "" {
            parameters:
                @display("p=69,303;is=s");
        }
        configurator: Ipv4NetworkConfigurator {
            parameters:
                assignDisjunctSubnetAddresses = false;
                @display("p=69,155;is=s");
        }
        radioMedium: Ieee80211ScalarRadioMedium {
            parameters:
                @display("p=68,224;is=s");
        }

        mobileServer1: WirelessHost {
            parameters:
                @display("p=2313,1542");
//                @display("i=device/cellphone2_vl");
				@display("i=device/pocketpc_s;r=,,#704050");

        }
        mobileServer2: WirelessHost {
            parameters:
                @display("p=967,1542");
//                @display("i=device/cellphone_vl");
				@display("i=device/pocketpc_s;r=,,#705070");

        }
        mobileServer3: WirelessHost {
            parameters:
                @display("p=2179,757");
                @display("i=device/pocketpc_s;r=,,#107010");

        }
        mobileServer4: WirelessHost {
            parameters:
                @display("p=1416,911");
//                @display("i=device/cellphone2_vl");
				  @display("i=device/pocketpc_s;r=,,#707070");

        }

        MECServer1: StandardHost {
            parameters:
                @display("p=1633,1542");
                @display("i=device/server");
        }
        MECServer2: StandardHost {
            parameters:
                @display("p=1633,1696");
                @display("i=device/server");
        }
        CoreServer1: StandardHost {
            parameters:
                @display("p=3343,2810");
                @display("i=device/server2");
        }

        CoreServer2: StandardHost {
            parameters:
                @display("p=3098,2810");
                @display("i=device/server2");
        }

        CoreServer3: StandardHost {
            parameters:
                @display("p=3098,2992");
                @display("i=device/server2");
        }

        CoreServer4: StandardHost {
            parameters:
                @display("p=3343,3034");
                @display("i=device/server2");
        }
        CoreServer5: StandardHost {
            parameters:
                @display("p=3098,3189");
                @display("i=device/server2");
        }
        CoreServer6: StandardHost {
   			 parameters:
          		@display("p=3098,3189");
           		@display("i=device/server2");  
		}

        router1: Router {
            parameters:
                @display("p=1486,2992");
        }

        router2: Router {
            parameters:
                @display("p=1913,2866");
        }
        router3: Router {
            parameters:
                @display("p=1913,3161");
        }
        router4: Router {
            parameters:
                @display("p=2313,2866");
        }
        router5: Router {
            parameters:
                @display("p=2313,3161");
        }
        router6: Router {
            parameters:
                @display("p=2607,2992");
        }
        bts: AccessPoint {
            parameters:
                @display("p=1486,1535");
                @display("i=device/antennatower_vl");
        }
    connections:
        bts.ethg++ <--> Eth100M <--> router1.ethg++;
        router1.ethg++ <--> Eth100M <--> router2.ethg++;
        router1.ethg++ <--> Eth100M <--> router3.ethg++;
        router3.ethg++ <--> Eth100M <--> router4.ethg++;
        router2.ethg++ <--> Eth100M <--> router5.ethg++;
        router5.ethg++ <--> Eth100M <--> router6.ethg++;
        router4.ethg++ <--> Eth100M <--> router6.ethg++;


        MECServer1.ethg++ <--> Eth100M <--> bts.ethg++;
        MECServer2.ethg++ <--> Eth100M <--> bts.ethg++;
        CoreServer1.ethg++ <--> Eth100M <--> router6.ethg++;
        CoreServer2.ethg++ <--> Eth100M <--> router6.ethg++;
        CoreServer3.ethg++ <--> Eth100M <--> router6.ethg++;
        CoreServer4.ethg++ <--> Eth100M <--> router6.ethg++;
        CoreServer5.ethg++ <--> Eth100M <--> router6.ethg++;
        CoreServer6.ethg++ <--> Eth100M <--> router6.ethg++;

}