/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation <http://www.arcpro.info/>
 * Copyright (c) 2008-2013 ArcEmu Team <http://www.arcemu.org/>
 * Copyright (c) 2007-2010 Burlex <burlex@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "Network.h"
#ifdef CONFIG_USE_EPOLL

namespace SocketOps
{
	// Create file descriptor for socket i/o operations.
	SOCKET CreateTCPFileDescriptor()
	{
		// create a socket for use with overlapped i/o.
		return socket(AF_INET, SOCK_STREAM, 0);
	}

	// Disable blocking send/recv calls.
	bool Nonblocking(SOCKET fd)
	{
		uint32 arg = 1;
		return (::ioctl(fd, FIONBIO, &arg) == 0);
	}

	// Disable blocking send/recv calls.
	bool Blocking(SOCKET fd)
	{
		uint32 arg = 0;
		return (ioctl(fd, FIONBIO, &arg) == 0);
	}

	// Disable nagle buffering algorithm
	bool DisableBuffering(SOCKET fd)
	{
		uint32 arg = 1;
		return (setsockopt(fd, 0x6, 0x1, (const char*)&arg, sizeof(arg)) == 0);
	}

	// Enable nagle buffering algorithm
	bool EnableBuffering(SOCKET fd)
	{
		uint32 arg = 0;
		return (setsockopt(fd, 0x6, 0x1, (const char*)&arg, sizeof(arg)) == 0);
	}

	// Set internal buffer size to socket.
	bool SetSendBufferSize(SOCKET fd, uint32 size)
	{
		return (setsockopt(fd, SOL_SOCKET, SO_SNDBUF, (const char*)&size, sizeof(size)) == 0);
	}

	// Set internal buffer size to socket.
	bool SetRecvBufferSize(SOCKET fd, uint32 size)
	{
		return (setsockopt(fd, SOL_SOCKET, SO_RCVBUF, (const char*)&size, sizeof(size)) == 0);
	}

	// Set internal timeout.
	bool SetTimeout(SOCKET fd, uint32 timeout)
	{
		struct timeval to;
		to.tv_sec = timeout;
		to.tv_usec = 0;
		if(setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, (const char*)&to, (socklen_t)sizeof(to)) != 0) return false;
		return (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&to, (socklen_t)sizeof(to)) == 0);
	}

	// Closes a socket fully.
	void CloseSocket(SOCKET fd)
	{
		shutdown(fd, SHUT_RDWR);
		close(fd);
	}

	// Sets reuseaddr
	void ReuseAddr(SOCKET fd)
	{
		uint32 option = 1;
		setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (const char*)&option, 4);
	}
}

#endif
