/*
 * InstrumentView.cpp - base-class for views of all Instruments
 *
 * Copyright (c) 2008-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
 *
 * This file is part of LMMS - https://lmms.io
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 */

#include <QIcon>

#include "InstrumentView.h"
#include "embed.h"
#include "InstrumentTrack.h"
#include "InstrumentTrackWindow.h"

namespace lmms::gui
{

/**
 * Constructs an InstrumentView object with the given Instrument and parent widget.
 *
 * @param _Instrument A pointer to the Instrument object.
 * @param _parent A pointer to the parent widget.
 *
 * @throws None
 */
InstrumentView::InstrumentView( Instrument * _Instrument, QWidget * _parent ) :
	PluginView( _Instrument, _parent )
{
	setModel( _Instrument );
	setAttribute( Qt::WA_DeleteOnClose, true );
}



/**
 * Destructor for the InstrumentView class.
 *
 * This function releases the memory allocated for the instrumentTrackWindow
 * object by setting the m_instrumentView pointer to nullptr.
 *
 * @throws None
 */
InstrumentView::~InstrumentView()
{
	if( instrumentTrackWindow() )
	{
		instrumentTrackWindow()->m_instrumentView = nullptr;
	}
}



/**
 * Sets the model for the InstrumentView.
 *
 * @param _model The model to be set.
 * @param unused A boolean parameter that is not used in the function.
 *
 * @return None
 *
 * @throws None
 */
void InstrumentView::setModel( Model * _model, bool )
{
	if( dynamic_cast<Instrument *>( _model ) != nullptr )
	{
		ModelView::setModel( _model );
		instrumentTrackWindow()->setWindowIcon( model()->logo()->pixmap() );
		connect( model(), SIGNAL(destroyed(QObject*)), this, SLOT(close()));
	}
}



/**
 * Returns a pointer to the InstrumentTrackWindow object that is the parent of the
 * parent widget of this InstrumentView object.
 *
 * @return A pointer to the InstrumentTrackWindow object.
 */
InstrumentTrackWindow * InstrumentView::instrumentTrackWindow()
{
	return( dynamic_cast<InstrumentTrackWindow *>(
					parentWidget()->parentWidget() ) );
}





} // namespace lmms::gui