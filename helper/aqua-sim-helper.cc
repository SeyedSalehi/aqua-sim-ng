/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2016 University of Connecticut
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Robert Martin <robert.martin@engr.uconn.edu>
 */


#include "ns3/log.h"
#include "ns3/assert.h"
#include "ns3/double.h"

#include "ns3/aqua-sim-net-device.h"
#include "ns3/aqua-sim-propagation.h"
#include "ns3/aqua-sim-noise-generator.h"
#include "ns3/aqua-sim-address.h"
#include "ns3/application.h"

#include "aqua-sim-helper.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("AquaSimHelper");

AquaSimChannelHelper::AquaSimChannelHelper()
{
}

AquaSimChannelHelper
AquaSimChannelHelper::Default (void)
{
  AquaSimChannelHelper channelHelper;
  channelHelper.SetPropagation ("ns3::AquaSimSimplePropagation");
  channelHelper.SetNoiseGenerator("ns3::AquaSimConstNoiseGen");
  channelHelper.SetChannel("ns3::AquaSimChannel");
  return channelHelper;
}

void
AquaSimChannelHelper::SetPropagation (std::string type,
                                              std::string n0, const AttributeValue &v0,
                                              std::string n1, const AttributeValue &v1,
                                              std::string n2, const AttributeValue &v2,
                                              std::string n3, const AttributeValue &v3,
                                              std::string n4, const AttributeValue &v4,
                                              std::string n5, const AttributeValue &v5,
                                              std::string n6, const AttributeValue &v6,
                                              std::string n7, const AttributeValue &v7)
{
  ObjectFactory factory;
  factory.SetTypeId (type);
  factory.Set (n0,v0);
  factory.Set (n1,v1);
  factory.Set (n2,v2);
  factory.Set (n3,v3);
  factory.Set (n4,v4);
  factory.Set (n5,v5);
  factory.Set (n6,v6);
  factory.Set (n7,v7);
  m_propagation = factory;
}

void
AquaSimChannelHelper::SetNoiseGenerator (std::string type,
                                              std::string n0, const AttributeValue &v0,
                                              std::string n1, const AttributeValue &v1,
                                              std::string n2, const AttributeValue &v2,
                                              std::string n3, const AttributeValue &v3,
                                              std::string n4, const AttributeValue &v4,
                                              std::string n5, const AttributeValue &v5,
                                              std::string n6, const AttributeValue &v6,
                                              std::string n7, const AttributeValue &v7)
{
  ObjectFactory factory;
  factory.SetTypeId (type);
  factory.Set (n0,v0);
  factory.Set (n1,v1);
  factory.Set (n2,v2);
  factory.Set (n3,v3);
  factory.Set (n4,v4);
  factory.Set (n5,v5);
  factory.Set (n6,v6);
  factory.Set (n7,v7);
  m_noiseGen = factory;
}

void
AquaSimChannelHelper::SetChannel (std::string type,
                                              std::string n0, const AttributeValue &v0,
                                              std::string n1, const AttributeValue &v1,
                                              std::string n2, const AttributeValue &v2,
                                              std::string n3, const AttributeValue &v3,
                                              std::string n4, const AttributeValue &v4,
                                              std::string n5, const AttributeValue &v5,
                                              std::string n6, const AttributeValue &v6,
                                              std::string n7, const AttributeValue &v7)
{
  ObjectFactory factory;
  factory.SetTypeId (type);
  factory.Set (n0,v0);
  factory.Set (n1,v1);
  factory.Set (n2,v2);
  factory.Set (n3,v3);
  factory.Set (n4,v4);
  factory.Set (n5,v5);
  factory.Set (n6,v6);
  factory.Set (n7,v7);
  m_channel = factory;
}

Ptr<AquaSimChannel>
AquaSimChannelHelper::Create (void) const
{
  //Ptr<AquaSimChannel> channel = CreateObject<AquaSimChannel> ();
  Ptr<AquaSimChannel> channel = m_channel.Create<AquaSimChannel> ();
  Ptr<AquaSimPropagation> prop = m_propagation.Create<AquaSimPropagation>();
  Ptr<AquaSimNoiseGen> noise = m_noiseGen.Create<AquaSimNoiseGen>();
  channel->SetPropagation(prop);
  channel->SetNoiseGenerator(noise);
  return channel;
}

/*
int64_t
AquaSimChannelHelper::AssignStreams (Ptr<AquaSimChannel> c, int64_t stream)
{
  return c->AssignStreams (stream);	//this needs to be implemented or removed...
}
*/

AquaSimHelper::AquaSimHelper() :
    m_channel(0)
{
  /*
   * Protocol prefix setting
   */
  m_phy.SetTypeId("ns3::AquaSimPhyCmn");
  m_phy.Set("CPThresh", DoubleValue(10));
  m_phy.Set("CSThresh", DoubleValue(0));
  m_phy.Set("RXThresh", DoubleValue(0));
  m_phy.Set("PT", DoubleValue(0.2818));
  m_phy.Set("Frequency", DoubleValue(25));
  m_phy.Set("K", DoubleValue(2.0));
  m_mac.SetTypeId("ns3::AquaSimBroadcastMac");
  m_routing.SetTypeId("ns3::AquaSimStaticRouting");
  m_energyM.SetTypeId("ns3::AquaSimEnergyModel");
  m_sync.SetTypeId("ns3::AquaSimSync");
  m_localization.SetTypeId("ns3::AquaSimLocalization");
}

AquaSimHelper
AquaSimHelper::Default()
{
  AquaSimHelper asHelper;

  //populate the default case with child classes for mac/routing

  return asHelper;
}

void
AquaSimHelper::SetChannel(Ptr<AquaSimChannel> channel)
{
  m_channel = channel;
}

Ptr<AquaSimChannel>
AquaSimHelper::GetChannel()
{
  return m_channel;
}
void
AquaSimHelper::SetPhy (std::string type,
                       std::string n0, const AttributeValue &v0,
                       std::string n1, const AttributeValue &v1,
                       std::string n2, const AttributeValue &v2,
                       std::string n3, const AttributeValue &v3,
                       std::string n4, const AttributeValue &v4,
                       std::string n5, const AttributeValue &v5,
                       std::string n6, const AttributeValue &v6,
                       std::string n7, const AttributeValue &v7)
{
  ObjectFactory factory;
  factory.SetTypeId (type);
  factory.Set (n0,v0);
  factory.Set (n1,v1);
  factory.Set (n2,v2);
  factory.Set (n3,v3);
  factory.Set (n4,v4);
  factory.Set (n5,v5);
  factory.Set (n6,v6);
  factory.Set (n7,v7);
  m_phy = factory;
}

void
AquaSimHelper::SetMac (std::string type,
                                              std::string n0, const AttributeValue &v0,
                                              std::string n1, const AttributeValue &v1,
                                              std::string n2, const AttributeValue &v2,
                                              std::string n3, const AttributeValue &v3,
                                              std::string n4, const AttributeValue &v4,
                                              std::string n5, const AttributeValue &v5,
                                              std::string n6, const AttributeValue &v6,
                                              std::string n7, const AttributeValue &v7)
{
  ObjectFactory factory;
  factory.SetTypeId (type);
  factory.Set (n0,v0);
  factory.Set (n1,v1);
  factory.Set (n2,v2);
  factory.Set (n3,v3);
  factory.Set (n4,v4);
  factory.Set (n5,v5);
  factory.Set (n6,v6);
  factory.Set (n7,v7);
  m_mac = factory;
}

void
AquaSimHelper::SetRouting (std::string type,
                                              std::string n0, const AttributeValue &v0,
                                              std::string n1, const AttributeValue &v1,
                                              std::string n2, const AttributeValue &v2,
                                              std::string n3, const AttributeValue &v3,
                                              std::string n4, const AttributeValue &v4,
                                              std::string n5, const AttributeValue &v5,
                                              std::string n6, const AttributeValue &v6,
                                              std::string n7, const AttributeValue &v7)
{
  ObjectFactory factory;
  factory.SetTypeId (type);
  factory.Set (n0,v0);
  factory.Set (n1,v1);
  factory.Set (n2,v2);
  factory.Set (n3,v3);
  factory.Set (n4,v4);
  factory.Set (n5,v5);
  factory.Set (n6,v6);
  factory.Set (n7,v7);
  m_routing = factory;
}

void
AquaSimHelper::SetEnergyModel (std::string type,
                                              std::string n0, const AttributeValue &v0,
                                              std::string n1, const AttributeValue &v1,
                                              std::string n2, const AttributeValue &v2,
                                              std::string n3, const AttributeValue &v3,
                                              std::string n4, const AttributeValue &v4,
                                              std::string n5, const AttributeValue &v5,
                                              std::string n6, const AttributeValue &v6,
                                              std::string n7, const AttributeValue &v7)
{
  ObjectFactory factory;
  factory.SetTypeId (type);
  factory.Set (n0,v0);
  factory.Set (n1,v1);
  factory.Set (n2,v2);
  factory.Set (n3,v3);
  factory.Set (n4,v4);
  factory.Set (n5,v5);
  factory.Set (n6,v6);
  factory.Set (n7,v7);
  m_energyM = factory;
}

void
AquaSimHelper::SetSync (std::string type,
                                              std::string n0, const AttributeValue &v0,
                                              std::string n1, const AttributeValue &v1,
                                              std::string n2, const AttributeValue &v2,
                                              std::string n3, const AttributeValue &v3,
                                              std::string n4, const AttributeValue &v4,
                                              std::string n5, const AttributeValue &v5,
                                              std::string n6, const AttributeValue &v6,
                                              std::string n7, const AttributeValue &v7)
{
  ObjectFactory factory;
  factory.SetTypeId (type);
  factory.Set (n0,v0);
  factory.Set (n1,v1);
  factory.Set (n2,v2);
  factory.Set (n3,v3);
  factory.Set (n4,v4);
  factory.Set (n5,v5);
  factory.Set (n6,v6);
  factory.Set (n7,v7);
  m_sync = factory;
}

void
AquaSimHelper::SetLocalization (std::string type,
                                              std::string n0, const AttributeValue &v0,
                                              std::string n1, const AttributeValue &v1,
                                              std::string n2, const AttributeValue &v2,
                                              std::string n3, const AttributeValue &v3,
                                              std::string n4, const AttributeValue &v4,
                                              std::string n5, const AttributeValue &v5,
                                              std::string n6, const AttributeValue &v6,
                                              std::string n7, const AttributeValue &v7)
{
  ObjectFactory factory;
  factory.SetTypeId (type);
  factory.Set (n0,v0);
  factory.Set (n1,v1);
  factory.Set (n2,v2);
  factory.Set (n3,v3);
  factory.Set (n4,v4);
  factory.Set (n5,v5);
  factory.Set (n6,v6);
  factory.Set (n7,v7);
  m_localization = factory;
}

Ptr<AquaSimNetDevice>
AquaSimHelper::Create(Ptr<Node> node, Ptr<AquaSimNetDevice> device)
{
  Ptr<AquaSimPhy> phy = m_phy.Create<AquaSimPhy>();
  Ptr<AquaSimMac> mac = m_mac.Create<AquaSimMac>();
  Ptr<AquaSimRouting> routing = m_routing.Create<AquaSimRouting>();
  Ptr<AquaSimEnergyModel> energyM = m_energyM.Create<AquaSimEnergyModel>();
  //Ptr<AquaSimSync> sync = m_sync.Create<AquaSimSync>();
  //Ptr<AquaSimLocalization> loc = m_localization.Create<AquaSimLocalization>();

  device->SetPhy(phy);
  device->SetMac(mac);
  //device->SetMac(mac,sync,loc);
  device->SetRouting(routing);
  device->ConnectLayers();

  NS_ASSERT(m_channel);
  device->SetChannel(m_channel);

  device->SetEnergyModel(energyM);
  device->SetAddress(AquaSimAddress::Allocate());

  node->AddDevice(device);

  NS_LOG_DEBUG(this << "Create Dump. Phy:" << device->GetPhy() << " Mac:"
	       << device->GetMac() << " Routing:" << device->GetRouting()
	       << " Channel:" << device->GetChannel() << "\n");

  return device;
}


}  //namespace ns3
