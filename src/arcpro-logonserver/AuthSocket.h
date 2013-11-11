/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation <http://www.arcpro.info/>
 * Copyright (c) 2008-2013 ArcEmu Team <http://www.arcemu.org/>
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

#ifndef AUTHSOCKET_H
#define AUTHSOCKET_H

#include "AccountCache.h"
#include "AuthStructs.h"

class LogonCommServerSocket;
struct Patch;
class PatchJob;

class AuthSocket : public Socket
{
		friend class LogonCommServerSocket;
	public:

		///////////////////////////////////////////////////
		// Netcore shit
		//////////////////////////
		AuthSocket(SOCKET fd);
		~AuthSocket();

		void OnRead();

		///////////////////////////////////////////////////
		// Client Packet Handlers
		//////////////////////////

		void HandleChallenge();
		void HandleProof();
		void HandleRealmlist();
		void HandleReconnectChallenge();
		void HandleReconnectProof();
		void HandleTransferAccept();
		void HandleTransferResume();
		void HandleTransferCancel();

		///////////////////////////////////////////////////
		// Server Packet Builders
		//////////////////////////

		void SendChallengeError(uint8 Error);
		void SendProofError(uint8 Error, uint8* M2);
		ARCPRO_INLINE sAuthLogonChallenge_C* GetChallenge() { return &m_challenge; }
		ARCPRO_INLINE void SendPacket(const uint8* data, const uint16 len) { Send(data, len); }
		void OnDisconnect();
		ARCPRO_INLINE time_t GetLastRecv() { return last_recv; }
		bool removedFromSet;
		ARCPRO_INLINE uint32 GetAccountID() { return m_account ? m_account->AccountId : 0; }

	protected:

		sAuthLogonChallenge_C m_challenge;
		Account* m_account;
		bool m_authenticated;

		// BigNumbers for the SRP6 implementation
		BigNumber N; // Safe prime
		BigNumber g; // Generator
		BigNumber s; // Salt
		BigNumber v; // Verifier
		BigNumber b; // server private value
		BigNumber B; // server public value
		BigNumber rs;

		//////////////////////////////////////////////////
		// Session Key
		/////////////////////////

		BigNumber m_sessionkey;
		time_t last_recv;

		//////////////////////////////////////////////////////////////////////////
		// Patching stuff
		//////////////////////////////////////////////////////////////////////////
	public:
		Patch* m_patch;
		PatchJob* m_patchJob;
};

#endif
