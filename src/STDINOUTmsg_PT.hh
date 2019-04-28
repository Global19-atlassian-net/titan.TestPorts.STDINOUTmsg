/******************************************************************************
* Copyright (c) 2000-2019 Ericsson Telecom AB
* All rights reserved. This program and the accompanying materials
* are made available under the terms of the Eclipse Public License v2.0
* which accompanies this distribution, and is available at
* https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html
*
* Contributors:
* Balazs Andor Zalanyi
* Endre Kulcsar
* Gabor Szalai
* Janos Kovesdi
******************************************************************************/
//
//  File:               STDINOUTmsg_PT.hh
//  Description:        The header file for STDINOUT testport
//  Rev:                R3A
//  Prodnr:             CNL 113 642
///////////////////////////////////////////////

#ifndef STDINOUTmsg__PT_HH
#define STDINOUTmsg__PT_HH

#include <TTCN3.hh>

// Note: Header file STDINOUTmsg_PortType.hh must not be included into this file!
// Please add the declarations of message types manually.

namespace STDINOUTmsg__PortType {

class STDINOUTmsg__PT_PROVIDER : public PORT {
public:
	STDINOUTmsg__PT_PROVIDER(const char *par_port_name);
	~STDINOUTmsg__PT_PROVIDER();

	void set_parameter(const char *parameter_name,
		const char *parameter_value){};

        void Handle_Fd_Event_Readable(int fd);
	void Handle_Timeout(double time_since_last_call) {}
  static bool port_connected;

protected:
	void user_map(const char *system_port);
	void user_unmap(const char *system_port);

	void user_start(){};
	void user_stop(){};

	void outgoing_send(const CHARSTRING& send_par);
	virtual void incoming_message(const CHARSTRING& incoming_par) = 0;
};

} /* end of namespace */

#endif
