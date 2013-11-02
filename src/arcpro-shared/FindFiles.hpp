/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation <http://arcpro.info/>
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

#ifndef ARCPRO_FINDFILES_HPP
#define ARCPRO_FINDFILES_HPP

#include "FindFilesResult.hpp"

namespace Arcpro{
	//////////////////////////////////////////////////////////////////////////////////
	//bool FindFiles( const char *where, const char *filename, FindFilesResult &r )
	//  Searches for files with the name of *filename*, and
	//  puts the result(s) into a FindFileResult object.
	//
	//Parameter(s)
	//  const char *where     -  directory to search
	//  const char *filename  -  filename/mask to search for
	//  FindFilesResult &r    -  reference to the result object
	//
	//Return Value
	//  Returns true if at least 1 file was found.
	//  Returns false if there were no files found.
	//
	//
	//////////////////////////////////////////////////////////////////////////////////
	bool FindFiles( const char *where, const char *filename, FindFilesResult &r );
}

#endif
