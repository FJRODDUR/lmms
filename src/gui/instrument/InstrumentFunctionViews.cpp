/*
 * InstrumentFunctionViews.cpp - view for instrument-functions-tab
 *
 * Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
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

#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>

#include "InstrumentFunctions.h"
#include "InstrumentFunctionViews.h"
#include "ComboBox.h"
#include "GroupBox.h"
#include "gui_templates.h"
#include "Knob.h"
#include "TempoSyncKnob.h"


namespace lmms::gui
{

/**
 * Constructs an InstrumentFunctionNoteStackingView object with the given
 * InstrumentFunctionNoteStacking pointer and parent widget.
 *
 * @param cc Pointer to an InstrumentFunctionNoteStacking object.
 * @param parent Pointer to the parent widget.
 *
 * @throws None.
 */
InstrumentFunctionNoteStackingView::InstrumentFunctionNoteStackingView( InstrumentFunctionNoteStacking* cc, QWidget* parent ) :
	QWidget( parent ),
	ModelView( nullptr, this ),
	m_cc( cc ),
	m_chordsGroupBox( new GroupBox( tr( "STACKING" ) ) ),
	m_chordsComboBox( new ComboBox() ),
	m_chordRangeKnob( new Knob( KnobType::Bright26 ) )
{
	auto topLayout = new QHBoxLayout(this);
	topLayout->setContentsMargins(0, 0, 0, 0);
	topLayout->addWidget( m_chordsGroupBox );

	auto mainLayout = new QGridLayout(m_chordsGroupBox);
	mainLayout->setContentsMargins( 8, 18, 8, 8 );
	mainLayout->setColumnStretch( 0, 1 );
	mainLayout->setHorizontalSpacing( 20 );
	mainLayout->setVerticalSpacing( 1 );

	auto chordLabel = new QLabel(tr("Chord:"));
	chordLabel->setFont(adjustedToPixelSize(chordLabel->font(), 10));

	m_chordRangeKnob->setLabel( tr( "RANGE" ) );
	m_chordRangeKnob->setHintText( tr( "Chord range:" ), " " + tr( "octave(s)" ) );

	mainLayout->addWidget( chordLabel, 0, 0 );
	mainLayout->addWidget( m_chordsComboBox, 1, 0 );
	mainLayout->addWidget( m_chordRangeKnob, 0, 1, 2, 1, Qt::AlignHCenter );
}



/**
 * Destructor for the InstrumentFunctionNoteStackingView class.
 *
 * This function is responsible for deallocating the memory allocated for the
 * m_chordsGroupBox member variable. It is called when an instance of the
 * InstrumentFunctionNoteStackingView class is destroyed.
 *
 * @throws None.
 */
InstrumentFunctionNoteStackingView::~InstrumentFunctionNoteStackingView()
{
	delete m_chordsGroupBox;
}



/**
 * Updates the view's models when the underlying data model changes.
 *
 * This function is called when the data model associated with this view is modified.
 * It updates the models for the chords group box, chords combo box, and chord range knob.
 *
 * @return None
 *
 * @throws None
 */
void InstrumentFunctionNoteStackingView::modelChanged()
{
	m_cc = castModel<InstrumentFunctionNoteStacking>();
	m_chordsGroupBox->setModel( &m_cc->m_chordsEnabledModel );
	m_chordsComboBox->setModel( &m_cc->m_chordsModel );
	m_chordRangeKnob->setModel( &m_cc->m_chordRangeModel );
}






/**
 * Constructs an InstrumentFunctionArpeggioView object with the given arpeggio and parent widget.
 *
 * @param arp A pointer to an InstrumentFunctionArpeggio object.
 * @param parent A pointer to a QWidget object.
 *
 * @return None.
 *
 * @throws None.
 */
InstrumentFunctionArpeggioView::InstrumentFunctionArpeggioView( InstrumentFunctionArpeggio* arp, QWidget* parent ) :
	QWidget( parent ),
	ModelView( nullptr, this ),
	m_a( arp ),
	m_arpGroupBox( new GroupBox( tr( "ARPEGGIO" ) ) ),
	m_arpComboBox( new ComboBox() ),
	m_arpRangeKnob( new Knob( KnobType::Bright26 ) ),
	m_arpRepeatsKnob( new Knob( KnobType::Bright26 ) ),
	m_arpCycleKnob( new Knob( KnobType::Bright26 ) ),
	m_arpSkipKnob( new Knob( KnobType::Bright26 ) ),
	m_arpMissKnob( new Knob( KnobType::Bright26 ) ),
	m_arpTimeKnob( new TempoSyncKnob( KnobType::Bright26 ) ),
	m_arpGateKnob( new Knob( KnobType::Bright26 ) ),
	m_arpDirectionComboBox( new ComboBox() ),
	m_arpModeComboBox( new ComboBox() )
{
	auto topLayout = new QHBoxLayout(this);
	topLayout->setContentsMargins(0, 0, 0, 0);
	topLayout->addWidget( m_arpGroupBox );

	auto mainLayout = new QGridLayout(m_arpGroupBox);
	mainLayout->setContentsMargins( 8, 18, 8, 8 );
	mainLayout->setColumnStretch( 0, 1 );
	mainLayout->setHorizontalSpacing( 20 );
	mainLayout->setVerticalSpacing( 1 );

	m_arpRangeKnob->setLabel( tr( "RANGE" ) );
	m_arpRangeKnob->setHintText( tr( "Arpeggio range:" ), " " + tr( "octave(s)" ) );


	m_arpRepeatsKnob->setLabel( tr( "REP" ) );
	m_arpRepeatsKnob->setHintText( tr( "Note repeats:" ) + " ", " " + tr( "time(s)" ) );


	m_arpCycleKnob->setLabel( tr( "CYCLE" ) );
	m_arpCycleKnob->setHintText( tr( "Cycle notes:" ) + " ", " " + tr( "note(s)" ) );


	m_arpSkipKnob->setLabel( tr( "SKIP" ) );
	m_arpSkipKnob->setHintText( tr( "Skip rate:" ), tr( "%" ) );


	m_arpMissKnob->setLabel( tr( "MISS" ) );
	m_arpMissKnob->setHintText( tr( "Miss rate:" ), tr( "%" ) );


	m_arpTimeKnob->setLabel( tr( "TIME" ) );
	m_arpTimeKnob->setHintText( tr( "Arpeggio time:" ), " " + tr( "ms" ) );


	m_arpGateKnob->setLabel( tr( "GATE" ) );
	m_arpGateKnob->setHintText( tr( "Arpeggio gate:" ), tr( "%" ) );

	constexpr int labelFontSize = 10;
	auto arpChordLabel = new QLabel(tr("Chord:"));
	arpChordLabel->setFont(adjustedToPixelSize(arpChordLabel->font(), labelFontSize));

	auto arpDirectionLabel = new QLabel(tr("Direction:"));
	arpDirectionLabel->setFont(adjustedToPixelSize(arpDirectionLabel->font(), labelFontSize));

	auto arpModeLabel = new QLabel(tr("Mode:"));
	arpModeLabel->setFont(adjustedToPixelSize(arpModeLabel->font(), labelFontSize));

	mainLayout->addWidget( arpChordLabel, 0, 0 );
	mainLayout->addWidget( m_arpComboBox, 1, 0 );
	mainLayout->addWidget( arpDirectionLabel, 3, 0 );
	mainLayout->addWidget( m_arpDirectionComboBox, 4, 0 );
	mainLayout->addWidget( arpModeLabel, 6, 0 );
	mainLayout->addWidget( m_arpModeComboBox, 7, 0 );

	mainLayout->addWidget( m_arpRangeKnob, 0, 1, 2, 1, Qt::AlignHCenter );
	mainLayout->addWidget( m_arpRepeatsKnob, 0, 2, 2, 1, Qt::AlignHCenter );
	mainLayout->addWidget( m_arpCycleKnob, 0, 3, 2, 1, Qt::AlignHCenter );
	mainLayout->addWidget( m_arpSkipKnob, 3, 2, 2, 1, Qt::AlignHCenter );
	mainLayout->addWidget( m_arpMissKnob, 3, 3, 2, 1, Qt::AlignHCenter );
	mainLayout->addWidget( m_arpGateKnob, 6, 2, 2, 1, Qt::AlignHCenter );
	mainLayout->addWidget( m_arpTimeKnob, 6, 3, 2, 1, Qt::AlignHCenter );

	mainLayout->setRowMinimumHeight( 2, 10 );
	mainLayout->setRowMinimumHeight( 5, 10 );
}



/**
 * Destructor for the InstrumentFunctionArpeggioView class.
 *
 * This destructor is responsible for deallocating the memory allocated for the m_arpGroupBox member variable.
 *
 * @throws None.
 */
InstrumentFunctionArpeggioView::~InstrumentFunctionArpeggioView()
{
	delete m_arpGroupBox;
}



/**
 * Updates the models of the various UI elements in the InstrumentFunctionArpeggioView
 * class with the corresponding models from the InstrumentFunctionArpeggio model.
 */
void InstrumentFunctionArpeggioView::modelChanged()
{
	m_a = castModel<InstrumentFunctionArpeggio>();
	m_arpGroupBox->setModel( &m_a->m_arpEnabledModel );
	m_arpComboBox->setModel( &m_a->m_arpModel );
	m_arpRangeKnob->setModel( &m_a->m_arpRangeModel );
	m_arpRepeatsKnob->setModel( &m_a->m_arpRepeatsModel );
	m_arpCycleKnob->setModel( &m_a->m_arpCycleModel );
	m_arpSkipKnob->setModel( &m_a->m_arpSkipModel );
	m_arpMissKnob->setModel( &m_a->m_arpMissModel );
	m_arpTimeKnob->setModel( &m_a->m_arpTimeModel );
	m_arpGateKnob->setModel( &m_a->m_arpGateModel );
	m_arpDirectionComboBox->setModel( &m_a->m_arpDirectionModel );
	m_arpModeComboBox->setModel( &m_a->m_arpModeModel );
}




} // namespace lmms::gui
