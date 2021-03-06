/*
 *  This file is part of seq24/sequencer64.
 *
 *  seq24 is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General)mm Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  seq24 is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with seq24; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/**
 * \file          perfroll_input.cpp
 *
 *  This module declares/defines the base class for the Performance window
 *  mouse input.
 *
 * \library       sequencer64 application
 * \author        Seq24 team; modifications by Chris Ahlstrom
 * \date          2015-07-24
 * \updates       2016-11-06
 * \license       GNU GPLv2 or above
 *
 */

#include <gtkmm/button.h>
#include <gdkmm/cursor.h>

#include "click.hpp"                    /* SEQ64_CLICK_LEFT(), etc.    */
#include "gui_key_tests.hpp"            /* seq64::is_super_key()       */
#include "perform.hpp"
#include "perfroll_input.hpp"
#include "perfroll.hpp"
#include "sequence.hpp"
#include "settings.hpp"                 /* seq64::rc() or seq64::usr()  */

/**
 *  Duplicates what is at the top of the perfroll.cpp module.  FIX LATER.
 */

static int s_perfroll_size_box_click_w = 4; /* s_perfroll_size_box_w + 1 */

/*
 * Do not document the namespace; it breaks Doxygen.
 */

namespace seq64
{

/**
 *  A popup menu (which one?) calls this.  What does it mean?
 */

void
Seq24PerfInput::activate_adding (bool adding, perfroll & roll)
{
    if (adding)
        roll.get_window()->set_cursor(Gdk::Cursor(Gdk::PENCIL));
    else
        roll.get_window()->set_cursor(Gdk::Cursor(Gdk::LEFT_PTR));

    set_adding(adding);
}

/**
 *  Handles the normal variety of button-press event.  Is there any easy way
 *  to use ctrl-left-click as the middle button here?
 *
 * Stazed:
 *
 *      roll.m_drop_y will be adjusted by perfroll::change_vert() for any scroll
 *      after it was originally selected. The call here to draw_drawable_row()
 *      [now folded into draw_all()] will have the wrong y location and
 *      un-select will not occur (or the wrong sequence will be unselected) if
 *      the user scrolls the track up or down to a new y location, if not
 *      adjusted.
 *
 * \return
 *      Returns true if a modification occurred.
 */

bool
Seq24PerfInput::on_button_press_event (GdkEventButton * ev, perfroll & roll)
{
    bool result = false;
    perform & p = roll.perf();
    int & dropseq = roll.m_drop_sequence;
    sequence * seq = p.get_sequence(dropseq);
    bool dropseq_active = p.is_active(dropseq);
    roll.grab_focus();
    if (dropseq_active)
    {
        seq->unselect_triggers();
        roll.draw_all();
    }
    roll.m_drop_x = int(ev->x);
    roll.m_drop_y = int(ev->y);
    roll.convert_drop_xy();                             /* affects dropseq  */
    seq = p.get_sequence(dropseq);
    dropseq_active = p.is_active(dropseq);
    if (! dropseq_active)
        return false;

    /*
     * EXPERIMENTAL.
     *  Let's make better use of the Ctrl key here.  First, let Ctrl-Left be
     *  handled exactly like the Middle click, then bug out.
     *
     *  Note that this middle-click code ought to be folded into a function.
     */

    if (is_ctrl_key(ev))
    {
        if (SEQ64_CLICK_LEFT(ev->button))
        {
            bool state = seq->get_trigger_state(roll.m_drop_tick);
            if (state)
            {
                roll.split_trigger(dropseq, roll.m_drop_tick);
            }
            else
            {
                p.push_trigger_undo(dropseq);
                seq->paste_trigger(roll.m_drop_tick);
            }
        }
        return true;
    }

    if (SEQ64_CLICK_LEFT(ev->button))
    {
        midipulse droptick = roll.m_drop_tick;
        if (is_adding())                /* add new note if nothing selected */
        {
            set_adding_pressed(true);
            midipulse seqlength = seq->get_length();
            bool state = seq->get_trigger_state(droptick);
            if (state)
            {
                p.push_trigger_undo(dropseq);           /* stazed fix   */
                seq->del_trigger(droptick);
            }
            else
            {
                droptick -= (droptick % seqlength);     /* snap         */
                p.push_trigger_undo(dropseq);           /* stazed fix   */
                seq->add_trigger(droptick, seqlength);
                roll.draw_all();
            }
            result = true;
        }
        else
        {
            /*
             * Set this flag to tell on_motion_notify() to call
             * p.push_trigger_undo().
             */

            roll.m_have_button_press = seq->select_trigger(droptick);

            midipulse tick0 = seq->selected_trigger_start();
            midipulse tick1 = seq->selected_trigger_end();
            int wscalex = s_perfroll_size_box_click_w * c_perf_scale_x;
            int ydrop = roll.m_drop_y % c_names_y;
            if
            (
                droptick >= tick0 && droptick <= (tick0 + wscalex) &&
                ydrop <= s_perfroll_size_box_click_w + 1
            )
            {
                roll.m_growing = true;
                roll.m_grow_direction = true;
                roll.m_drop_tick_trigger_offset = droptick -
                     seq->selected_trigger_start();
            }
            else if
            (
                droptick >= (tick1 - wscalex) && droptick <= tick1 &&
                ydrop >= c_names_y - s_perfroll_size_box_click_w - 1
            )
            {
                roll.m_growing = true;
                roll.m_grow_direction = false;
                roll.m_drop_tick_trigger_offset = droptick -
                    seq->selected_trigger_end();
            }
            else
            {
                roll.m_moving = true;
                roll.m_drop_tick_trigger_offset = droptick -
                     seq->selected_trigger_start();
            }
            roll.draw_all();
        }
    }
    else if (SEQ64_CLICK_RIGHT(ev->button))
    {
        activate_adding(true, roll);
        // Should we add this?
        // result = true;
    }
    else if (SEQ64_CLICK_MIDDLE(ev->button))                   /* split    */
    {
        /*
         * The middle click in seq24 interaction mode is either for splitting
         * the triggers or for setting the paste location of copy/paste.
         */

        bool state = seq->get_trigger_state(roll.m_drop_tick);
        if (state)
        {
            roll.split_trigger(dropseq, roll.m_drop_tick);
            result = true;
        }
        else
        {
            p.push_trigger_undo(dropseq);
            seq->paste_trigger(roll.m_drop_tick);
            // Should we add this?
            // result = true;
        }
    }
    return result;
}

/**
 *  Handles various button-release events.
 *  Any use for the middle-button or ctrl-left-click we can add?
 *
 * \return
 *      Returns true if any modification occurred.
 */

bool
Seq24PerfInput::on_button_release_event (GdkEventButton * ev, perfroll & roll)
{
    bool result = false;
    if (SEQ64_CLICK_LEFT(ev->button))
    {
        if (is_adding())
            set_adding_pressed(false);
    }
    else if (SEQ64_CLICK_RIGHT(ev->button))
    {
        /*
         * Minor new feature.  If the Super (Mod4, Windows) key is
         * pressed when release, keep the adding-state in force.  One
         * can then use the unadorned left-click key to add material.  Right
         * click to reset the adding mode.  This feature is enabled only
         * if allowed by Options / Mouse  (but is true by default).
         * See the same code in seq24seqroll.cpp.
         */

        bool addmode_exit = ! rc().allow_mod4_mode();
        if (! addmode_exit)
            addmode_exit = ! is_super_key(ev);              /* Mod4 held? */

        if (addmode_exit)
        {
            set_adding_pressed(false);
            activate_adding(false, roll);
        }
    }

    perform & p = roll.perf();
    roll.m_moving = roll.m_growing = false;
    set_adding_pressed(false);
    m_effective_tick = 0;
    if (p.is_active(roll.m_drop_sequence))
    {
        roll.draw_all();
    }
    return result;
}

/**
 *  Handles the normal motion-notify event.
 *
 * \return
 *      Returns true if a modification occurs.  This function used to always
 *      return true.
 */

bool
Seq24PerfInput::on_motion_notify_event (GdkEventMotion * ev, perfroll & roll)
{
    bool result = false;
    int x = int(ev->x);
    perform & p = roll.perf();
    int dropseq = roll.m_drop_sequence;
    sequence * seq = p.get_sequence(dropseq);
    if (! p.is_active(dropseq))
    {
        return false;
    }
    if (is_adding() && is_adding_pressed())
    {
        midipulse seqlength = seq->get_length();
        midipulse tick;
        roll.convert_x(x, tick);
        tick -= (tick % seqlength);

        midipulse length = seqlength;
        seq->grow_trigger(roll.m_drop_tick, tick, length);
        roll.draw_all();
        result = true;
    }
    else if (roll.m_moving || roll.m_growing)
    {
        /*
         * This code is necessary to insure that there is no push unless
         * we have a motion notification.
         */

        if (roll.m_have_button_press)
        {
            p.push_trigger_undo(dropseq);
            roll.m_have_button_press = false;
        }

        midipulse tick;
        roll.convert_x(x, tick);
        tick -= roll.m_drop_tick_trigger_offset;
        tick -= tick % roll.m_snap;
        if (roll.m_moving)
        {
            seq->move_selected_triggers_to(tick, true);
            result = true;
        }
        if (roll.m_growing)
        {
            if (roll.m_grow_direction)
            {
                seq->move_selected_triggers_to
                (
                    tick, false, triggers::GROW_START
                );
            }
            else
            {
                seq->move_selected_triggers_to
                (
                    tick - 1, false, triggers::GROW_END);
            }
            result = true;
        }
        roll.draw_all();
    }
    return result;
}

/**
 *  Handles the keystroke motion-notify event for moving a pattern back and
 *  forth in the performance.
 *
 *  What happens when the mouse is used to drag the pattern is that, first,
 *  roll.m_drop_tick is set by left-clicking into the pattern to select it.
 *  As the pattern is dragged, the drop-tick value does not change, but the
 *  tick (converted from the moving x value) does.
 *
 *  Then the button-handler sets roll.m_moving = true, and calculates
 *  roll.m_drop_tick_trigger_offset = roll.m_drop_tick -
 *  p.get_sequence(dropseq)->selected_trigger_start();
 *
 *  The motion handler sees that roll.m_moving is true, gets the new tick
 *  value from the new x value, offsets it, and calls
 *  p.get_sequence(dropseq)->move_selected_triggers_to(tick, true).
 *
 *  When the user releases the left button, then roll.m_growing is turned of
 *  and the roll draw_all()'s.
 *
 * \param is_left
 *      False denotes the right arrow key, and true denotes the left arrow
 *      key.
 *
 * \param roll
 *      Provides a reference to the parent roll, which keeps track of most of
 *      the information about the status of the window.
 *
 * \return
 *      Returns true if there was some action able to happen that would
 *      necessitate a window update.  We've updated triggers::move_selected()
 *      [called indirectly near the end of this routine] to return false if no
 *      more movement could be made.  This prevents this routine from moving
 *      way ahead after movement of the selected (in the user-interface)
 *      trigger stops.
 */

bool
Seq24PerfInput::handle_motion_key (bool is_left, perfroll & roll)
{
    bool result = false;
    bool ok = roll.m_drop_sequence >= 0;        /* need ">=" here!  */
    if (ok)
    {
        perform & p = roll.perf();
        int dropseq = roll.m_drop_sequence;
        midipulse droptick = roll.m_drop_tick;
        if (m_effective_tick == 0)
            m_effective_tick = droptick;

        if (is_left)
        {
            /*
             * This needlessly prevents a selection from moving leftward
             * from its original position.  We'll just put up with the
             * annoyance of absorbed decrements and document it in
             * sequencer64-doc.
             *
             * if (m_effective_tick < droptick)
             *     m_effective_tick = droptick;
             */

            midipulse tick = m_effective_tick;
            m_effective_tick -= roll.m_snap;
            if (m_effective_tick <= 0)
                m_effective_tick += roll.m_snap;    /* retrench */

            if (m_effective_tick != tick)
                result = true;
        }
        else
        {
            m_effective_tick += roll.m_snap;
            result = true;

            /*
             * What is the upper boundary here?
             */
        }

        midipulse tick = m_effective_tick - roll.m_drop_tick_trigger_offset;
        tick -= tick % roll.m_snap;

        /*
         * Hmmmm, this overrides any result setting above.  Due to issues with
         * triggers::move_selected(), this always returns true.  Let's ignore
         * the return value for now.
         */

        (void) p.get_sequence(dropseq)->move_selected_triggers_to(tick, true);
    }
    return result;
}

}           // namespace seq64

/*
 * perfroll_input.cpp
 *
 * vim: sw=4 ts=4 wm=4 et ft=cpp
 */

