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

#if !defined(FIELD_H)
#define FIELD_H

class Field
{
	public:

		ARCPRO_INLINE void SetValue(char* value) { mValue = value; }

		ARCPRO_INLINE const char* GetString() { return mValue; }
		ARCPRO_INLINE float GetFloat() { return mValue ? static_cast<float>(atof(mValue)) : 0; }
		ARCPRO_INLINE bool GetBool() { return mValue ? atoi(mValue) > 0 : false; }
		ARCPRO_INLINE uint8 GetUInt8() { return mValue ? static_cast<uint8>(atol(mValue)) : 0; }
		ARCPRO_INLINE int8 GetInt8() { return mValue ? static_cast<int8>(atol(mValue)) : 0; }
		ARCPRO_INLINE uint16 GetUInt16() { return mValue ? static_cast<uint16>(atol(mValue)) : 0; }
		ARCPRO_INLINE int16 GetInt16() { return mValue ? static_cast<int16>(atol(mValue)) : 0; }
		ARCPRO_INLINE uint32 GetUInt32() { return mValue ? static_cast<uint32>(atol(mValue)) : 0; }
		ARCPRO_INLINE int32 GetInt32() { return mValue ? static_cast<int32>(atol(mValue)) : 0; }
		uint64 GetUInt64()
		{
			if(mValue)
			{
				uint64 value;
#ifndef WIN32	// Make GCC happy.
				sscanf(mValue, I64FMTD, (long long unsigned int*)&value);
#else
				sscanf(mValue, I64FMTD, &value);
#endif
				return value;
			}
			else
				return 0;
		}

	private:
		char* mValue;
};

#endif
