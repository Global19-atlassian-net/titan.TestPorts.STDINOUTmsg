/******************************************************************************
* Copyright (c) 2009, 2015  Ericsson AB
* All rights reserved. This program and the accompanying materials
* are made available under the terms of the Eclipse Public License v1.0
* which accompanies this distribution, and is available at
* http://www.eclipse.org/legal/epl-v10.html
*
* Contributors:
* Balazs Andor Zalanyi
* Endre Kulcsar
* Gabor Szalai
* Janos Kovesdi
******************************************************************************/
//
//  File:               STDINOUTmsg_PT.cc
//  Description:        The source file for STDINOUT testport
//  Rev:                R3A
//  Prodnr:             CNL 113 642
///////////////////////////////////////////////

#include "STDINOUTmsg_PT.hh"
#include "STDINOUTmsg_PortType.hh"

#include "memory.h"
namespace STDINOUTmsg__PortType {

bool STDINOUTmsg__PT_PROVIDER::port_connected = false;

STDINOUTmsg__PT_PROVIDER::STDINOUTmsg__PT_PROVIDER(const char *par_port_name)
	: PORT(par_port_name)
{}

STDINOUTmsg__PT_PROVIDER::~STDINOUTmsg__PT_PROVIDER()
{}

void STDINOUTmsg__PT_PROVIDER::Handle_Fd_Event_Readable(int fd) {
  size_t buf_len = 0, buf_size = 32;
  int c;
  char *buf = (char*)Malloc(buf_size);
  while (true)
  { 
    c = getc(stdin);
    if (c == EOF)
    {
      if (buf_len > 0)
        incoming_message(CHARSTRING(buf_len, buf));
      //Uninstall_Handler();
      Handler_Remove_Fd_Read(fd);
      break;
    } 
    else if (c == '\n')
    {
      incoming_message(CHARSTRING(buf_len, buf));
      break;
    }
    else
    {
      if (buf_len >= buf_size)
      {
        buf_size *= 2;
        buf = (char*)Realloc(buf, buf_size);
      }
      buf[buf_len++] = c;
    }
  }
  Free(buf);
}

void STDINOUTmsg__PT_PROVIDER::user_map(const char *system_port)
{
  if(port_connected)
    TTCN_error("Only one STDINOUT Test Port entity can be mapped"
               " on the same time");
  port_connected = true;
  Handler_Add_Fd_Read(fileno(stdin));
}

void STDINOUTmsg__PT_PROVIDER::user_unmap(const char *system_port)
{
  port_connected = false;
  Uninstall_Handler();
}

void STDINOUTmsg__PT_PROVIDER::outgoing_send(const CHARSTRING& send_par)
{
  puts((const char*)send_par);
  fflush(stdout);
}

} /* end of namespace */

