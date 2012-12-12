/*
 * unittest.h
 *
 * Copyright 2011-2012 Thomas L Dunnick
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
#ifndef __UNITTEST__
#define __UNITTEST__

/*
 * some shared globals usually in main.c
 */
char Software[] = "Phineas UNIT TEST";
char LogName[] = "tmp/phineas.log";

#define __LOG_C__		/* suppress log.h		*/
				/* and replace with...		*/
int Errors = 0;

#define _DEBUG_(fmt...) printf("DEBUG %s %d-",__FILE__,__LINE__),printf(fmt)
#ifndef error
#define error(fmt...) printf("ERROR %s %d-",__FILE__,__LINE__),printf(fmt),Errors++
#endif
#ifndef info
#define info(fmt...) printf("INFO %s %d-",__FILE__,__LINE__),printf(fmt)
#endif
#ifndef warn
#define warn(fmt...) printf("WARNING %s %d-",__FILE__,__LINE__),printf(fmt)
#endif
#ifndef fatal
#define fatal(fmt...) printf("FATAL %s %d-",__FILE__,__LINE__),printf(fmt),exit(++Errors)
#endif

void strdiff (char *file, int line, char *msg, char *p, char *expected)
{
  int n = 0;

retry:
  while (*p == *expected)
  {
    if (*p == 0) return;
    n++;
    p++;
    expected++;
  }
  if ((*p == '\r') && (*expected == '\n'))
  {
    p++;
    goto retry;
  }
  printf ("ERROR: %s %d-%s at %d expected:%d %.10s.. found:%d %.10s...\n", 
    file, line, msg, n, *expected, expected, *p, p);
  Errors++;
}

/*
 * configurations used for testing purposes
 */
char PhineasConfig[] =
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
"<Phineas>\n"
"  <!-- install directory -->\n"
"  <InstallDirectory>c:/usr/src/phineas/</InstallDirectory>\n"
"  <!-- our EbXML party ID -->\n"
"  <PartyId>test_party_id</PartyId>\n"
"  <!-- our organization name -->\n"
"  <Organization>test_organization</Organization>\n"
"  <!-- EbXML template for the SOAP component of a message -->\n"
"  <SoapTemplate>templates/soap.xml</SoapTemplate>\n"
"  <!-- ebXML template for SOAP acknowledgment -->\n"
"  <AckTemplate>templates/ack.xml</AckTemplate>\n"
"  <!-- ebXML template for SOAP response -->\n"
"  <ResponseTemplate>templates/response.xml</ResponseTemplate>\n"
"  <!-- EbXML template for encrypted payload component of a message -->\n"
"  <EncryptionTemplate>templates/encryption.xml</EncryptionTemplate>\n"
"  <!-- CPA template -->\n"
"  <CpaTemplate>templates/cpa.xml</CpaTemplate>\n"
"  <!-- CPA folder -->\n"
"  <CpaDirectory>cpa/</CpaDirectory>\n"
"  <!--a directory to temporarily stash files -->\n"
"  <TempDirectory>tmp/</TempDirectory>\n"
"  <!-- logging -->\n"
"  <LogFile></LogFile>\n"
"  <LogLevel>debug</LogLevel>\n"
"  <!-- stand-alone service related -->\n"
"  <Server>\n"
"    <Port>80</Port>\n"
"    <SSL>\n"
"      <Port>443</Port>\n"
"      <CertFile>security/Phineas.pfx</CertFile>\n"
"      <KeyFile>security/Phineas.pfx</KeyFile>\n"
"      <Password>changeit</Password>\n"
"      <AuthFile></AuthFile>\n"
"    </SSL>\n"
"  </Server>\n"
"  <!-- console features -->\n"
"  <Console>\n"
"    <Url>/phineas/console</Url>\n"
"    <Root>console</Root>\n"
"    <Config>config.xml</Config>\n"
"  </Console>\n"
"<!-- The sender's configuration -->\n"
"<Sender>\n"
"  <!-- second between map, queue, or other polling -->\n"
"  <PollInterval>1</PollInterval>\n"
"  <!-- maximum number of sender threads -->\n"
"  <MaxThreads>3</MaxThreads>\n"
"  <!-- certificate authority -->\n"
"  <CertificateAuthority></CertificateAuthority>\n"
"  <!-- maximum number of reties -->\n"
"  <MaxRetry>2</MaxRetry>\n"
"  <!-- retry delay -->\n"
"  <DelayRetry>2</DelayRetry>\n"
"  <!-- \n"
"    Routes indicated EbXML end points for the sender\n"
"   -->\n"
"  <RouteInfo>\n"
"    <Route>\n"
"      <Name>test_route</Name>\n"
"      <PartyId>test_route_id</PartyId>\n"
"      <Cpa>test_route_cpa</Cpa>\n"
"      <Host>localhost</Host>\n"
"      <Path>/receiver/receivefile</Path>\n"
"      <Port>8443</Port>\n"
"      <Protocol>https</Protocol>\n"
"      <Timeout>2</Timeout>\n"
"      <Retry>2</Retry>\n"
"      <Authentication>\n"
"        <Type>clientcert</Type>\n"
"        <Id></Id>\n"
"        <Password></Password>\n"
"        <Unc>security/shrek.pem</Unc>\n"
"      </Authentication>\n"
"      <Packager></Packager>\n"
"    </Route>\n"
"  </RouteInfo>\n"
"  <!-- \n"
"    Maps direct processing of sender files.  Each map can have it's own\n"
"    processor.  The archtype is for EbXML payload queueing, but \n"
"    anything can be done as long as candidate files from Folder are\n"
"    consumed.\n"
"   -->\n"
"  <MapInfo>\n"
"    <Map>\n"
"      <Name>test_map</Name>\n"
"      <Folder>data/ebxml/outgoing/</Folder>\n"
"      <Processor>ebxml</Processor>\n"
"      <!-- the rest is processor specific, for EbXmlMapProcessor... -->\n"
"      <Processed>data/ebxml/processed/</Processed>\n"
"      <Acknowledged>data/ebxml/ack/</Acknowledged>\n"
"      <Filter>\n"
"        <Class></Class>\n"
"        <Config></Config>\n"
"      </Filter>\n"
"      <Route>test_route</Route>\n"
"      <Service>defaultservice</Service>\n"
"      <Action>defaultaction</Action>\n"
"      <Arguments></Arguments>\n"
"      <Recipient></Recipient>\n"
"      <Encryption>\n"
"        <Type>x509</Type>\n"
"        <Id></Id>\n"
"        <Password></Password>\n"
"        <Unc>security/phineas.pem</Unc>\n"
"      </Encryption>\n"
"      <Queue>MemSendQ</Queue>\n"
"    </Map>\n"
"  </MapInfo>\n"
"</Sender>\n"
"<Receiver>\n"
"  <Url>/phineas/receiver/receivefile</Url>\n"
"  <MapInfo>\n"
"    <Map>\n"
"      <Name>request2</Name>\n"
"      <Directory>data/tmp/</Directory>\n"
"      <Filter></Filter>\n"
"      <Route>loopback</Route>\n"
"      <Service>defaultservice</Service>\n"
"      <Action>defaultaction</Action>\n"
"      <Arguments></Arguments>\n"
"      <Encryption>\n"
"        <Type>clientcert</Type>\n"
"        <Id>EMAILADDRESS=tdunnick@wisc.edu, OU=Phineas Project, "
         "ST=Wisconsin, L=Madison, C=US, O=Phineas Health, "
	 "CN=Phineas App lication</Id>\n"
"        <Password>changeit</Password>\n"
"        <Unc>security/phineas.pfx</Unc>\n"
"      </Encryption>\n"
"      <Queue>MemReceiveQ</Queue>\n"
"    </Map>\n"
"  </MapInfo>\n"
"</Receiver>\n"
"<!-- \n"
"  Phineas Queues are shared by all apps.  Each one minimally has\n"
"  an int record ID as it's first field, followed by one or more VARCHAR\n"
"  fields which are identified in the queue Type.\n"
"  \n"
"  The Type identifies the fields expected in the record, and those names\n"
"  should correspond to those in the queue (database)\n"
"-->\n"
"<QueueInfo>\n"
"  <!-- frequency that queues should be polled in seconds -->"
"  <PollInterval>2</PollInterval>"
"  <!-- \n"
"    for queue types, the field id is used internally, and the field\n"
"    value should match the field label in the data row\n"
"   -->\n"
"  <Type>\n"
"    <Name>EbXmlSndQ</Name>\n"
"    <Field id=\"RECORDID\">RECORDID</Field>\n"
"    <Field id=\"MESSAGEID\">MESSAGEID</Field>\n"
"    <Field id=\"PAYLOADFILE\">PAYLOADFILE</Field>\n"
"    <Field id=\"DESTINATIONFILENAME\">DESTINATIONFILENAME</Field>\n"
"    <Field id=\"ROUTEINFO\">ROUTEINFO</Field>\n"
"    <Field id=\"SERVICE\">SERVICE</Field>\n"
"    <Field id=\"ACTION\">ACTION</Field>\n"
"    <Field id=\"ARGUMENTS\">ARGUMENTS</Field>\n"
"    <Field id=\"MESSAGERECIPIENT\">MESSAGERECIPIENT</Field>\n"
"    <Field id=\"MESSAGECREATIONTIME\">MESSAGECREATIONTIME</Field>\n"
"    <Field id=\"ENCRYPTION\">ENCRYPTION</Field>\n"
"    <Field id=\"SIGNATURE\">SIGNATURE</Field>\n"
"    <Field id=\"PUBLICKEYLDAPADDRESS\">PUBLICKEYLDAPADDRESS</Field>\n"
"    <Field id=\"PUBLICKEYLDAPBASEDN\">PUBLICKEYLDAPBASEDN</Field>\n"
"    <Field id=\"PUBLICKEYLDAPDN\">PUBLICKEYLDAPDN</Field>\n"
"    <Field id=\"CERTIFICATEURL\">CERTIFICATEURL</Field>\n"
"    <Field id=\"PROCESSINGSTATUS\">PROCESSINGSTATUS</Field>\n"
"    <Field id=\"TRANSPORTSTATUS\">TRANSPORTSTATUS</Field>\n"
"    <Field id=\"TRANSPORTERRORCODE\">TRANSPORTERRORCODE</Field>\n"
"    <Field id=\"APPLICATIONSTATUS\">APPLICATIONSTATUS</Field>\n"
"    <Field id=\"APPLICATIONERRORCODE\">APPLICATIONERRORCODE</Field>\n"
"    <Field id=\"APPLICATIONRESPONSE\">APPLICATIONRESPONSE</Field>\n"
"    <Field id=\"MESSAGESENTTIME\">MESSAGESENTTIME</Field>\n"
"    <Field id=\"MESSAGERECEIVEDTIME\">MESSAGERECEIVEDTIME</Field>\n"
"    <Field id=\"RESPONSEMESSAGEID\">RESPONSEMESSAGEID</Field>\n"
"    <Field id=\"RESPONSEARGUMENTS\">RESPONSEARGUMENTS</Field>\n"
"    <Field id=\"RESPONSELOCALFILE\">RESPONSELOCALFILE</Field>\n"
"    <Field id=\"RESPONSEFILENAME\">RESPONSEFILENAME</Field>\n"
"    <Field id=\"RESPONSEMESSAGEORIGIN\">RESPONSEMESSAGEORIGIN</Field>\n"
"    <Field id=\"RESPONSEMESSAGESIGNATURE\">RESPONSEMESSAGESIGNATURE</Field>\n"
"    <Field id=\"PRIORITY\">PRIORITY</Field>\n"
"  </Type>\n"
"  <Type>\n"
"    <Name>EbXmlRcvQ</Name>\n"
"    <Field id=\"RECORDID\">RECORDID</Field>\n"
"    <Field id=\"MESSAGEID\">MESSAGEID</Field>\n"
"    <Field id=\"PAYLOADNAME\">PAYLOADNAME</Field>\n"
"    <Field id=\"LOCALFILENAME\">LOCALFILENAME</Field>\n"
"    <Field id=\"SERVICE\">SERVICE</Field>\n"
"    <Field id=\"ACTION\">ACTION</Field>\n"
"    <Field id=\"ARGUMENTS\">ARGUMENTS</Field>\n"
"    <Field id=\"FROMPARTYID\">FROMPARTYID</Field>\n"
"    <Field id=\"MESSAGERECIPIENT\">MESSAGERECIPIENT</Field>\n"
"    <Field id=\"ERRORCODE\">ERRORCODE</Field>\n"
"    <Field id=\"ERRORMESSAGE\">ERRORMESSAGE</Field>\n"
"    <Field id=\"PROCESSINGSTATUS\">PROCESSINGSTATUS</Field>\n"
"    <Field id=\"APPLICATIONSTATUS\">APPLICATIONSTATUS</Field>\n"
"    <Field id=\"ENCRYPTION\">ENCRYPTION</Field>\n"
"    <Field id=\"RECEIVEDTIME\">RECEIVEDTIME</Field>\n"
"    <Field id=\"LASTUPDATETIME\">LASTUPDATETIME</Field>\n"
"    <Field id=\"PROCESSID\">PROCESSID</Field>\n"
"  </Type>\n"
"  <Connection>\n"
"    <Name>FileQueue</Name>\n"
"    <Type>file</Type>\n"
"    <Id></Id>\n"
"    <Password></Password>\n"
"    <Unc>queues/</Unc>\n"
"    <Driver></Driver>\n"
"  </Connection>\n"
"  <Connection>\n"
"    <Name>AccessQueue</Name>\n"
"    <Type>odbc</Type>\n"
"    <Id></Id>\n"
"    <Password></Password>\n"
/*
"    <Unc>PhinmsgAccessDSN270</Unc>\n"
*/
"    <Unc>tmp\\phineas.dsn</Unc>\n"
"    <Driver></Driver>\n"
"  </Connection>\n"
"  <Queue>\n"
"    <Name>MemSendQ</Name>\n"
"    <Type>EbXmlSndQ</Type>\n"
"    <Class></Class>\n"
"    <Connection>FileQueue</Connection>\n"
"    <Table>TransportQ</Table>\n"
"  </Queue>\n"
"  <Queue>\n"
"    <Name>MemReceiveQ</Name>\n"
"    <Type>EbXmlRcvQ</Type>\n"
"    <Class></Class>\n"
"    <Connection>FileQueue</Connection>\n"
"    <Table>ReceiveQ</Table>\n"
"  </Queue>  \n"
"  <Queue>\n"
"    <Name>AccessSendQ</Name>\n"
"    <Type>EbXmlSndQ</Type>\n"
"    <Class></Class>\n"
"    <Connection>AccessQueue</Connection>\n"
"    <Table>TransportQ</Table>\n"
"  </Queue>\n"
"  <Queue>\n"
"    <Name>AccessReceiveQ</Name>\n"
"    <Type>EbXmlRcvQ</Type>\n"
"    <Class></Class>\n"
"    <Connection>AccessQueue</Connection>\n"
"    <Table>ReceiveQ</Table>\n"
"  </Queue>  \n"
"</QueueInfo>\n"
"</Phineas>\n";

#endif /* __UNITTEST__ */
