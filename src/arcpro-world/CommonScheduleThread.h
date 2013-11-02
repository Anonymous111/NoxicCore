/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation <http://arcpro.info/>
 * Copyright (c) 2008-2013 ArcEmu Team <http://www.arcemu.org/>
 * Copyright (c) 2005-2007 Ascent Team <http://www.ascentemu.com/>
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

#ifndef _COMMONSCHEDULETHREAD_
#define _COMMONSCHEDULETHREAD_

class CommonScheduleThread : public CThread
{
		bool m_running;
		bool m_busy;
		std::multimap<uint32, uint32>::iterator itOrderMSGEntry;

		uint32 BCTimerCount;

		Arcpro::Threading::ConditionVariable cond;

	public:
		CommonScheduleThread();
		~CommonScheduleThread();

		bool run();
		void terminate();

		void BroadCastExec();
};

#endif
