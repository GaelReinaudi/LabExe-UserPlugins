/*!
 * \file    eventthread.cpp
 * \date    10.07.2009
 * \author  IDS Imaging Development Systems GmbH
 *
 * \brief   eventthread class (inherits QThread) implementation
 *          to wait on a uEye event and signal a connected slot
 *
 * \par Last modified
 *      on $Date:$ by $Author:$
 */

#include "eventthread.h"
#include <QDebug>

GUeyeCameraEventThread::GUeyeCameraEventThread ()
{
    m_hCam = 0;
    m_event = 0;
    m_bRunEventThread = false;
#ifndef __LINUX__
    m_hEvent = 0;
	// create event // Added by Gael from the uEyeEvent sample code
	m_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if(!m_hEvent) {
		qWarning() << "The Camera manager failed at Creating an event to monitor connection and disconnection of cameras.";
	}
#endif
}

GUeyeCameraEventThread::~GUeyeCameraEventThread ()
{

}

int GUeyeCameraEventThread::start (HIDS hCam,int event)
{
    int ret = 0;
    m_hCam = hCam;
    m_event = event;
#ifndef __LINUX__
    ret = is_InitEvent(m_hCam, m_hEvent, m_event);
#endif
    ret = is_EnableEvent (m_hCam, m_event);

    if (ret == 0)
    {
        //printf ("started event %d detection!\n", m_event);
        m_bRunEventThread = true;
        QThread::start (); // start the thread run function
    }

    return ret;
}

void GUeyeCameraEventThread::stop ()
{
    m_bRunEventThread = false;
}

void GUeyeCameraEventThread::run ()
{
    //printf ("start waiting on event %d\n", m_event);
    while (m_bRunEventThread)
    {
#ifdef __LINUX__
        if (is_WaitEvent (m_hCam, m_event, 1) == IS_SUCCESS)
#else
        if (WaitForSingleObject(m_hEvent, 1000) == WAIT_OBJECT_0)
#endif
        {
            //printf ("event %d detected\n", m_event);
            emit eventhappen (m_event);
        }
    }
    m_bRunEventThread = FALSE;
    is_DisableEvent (m_hCam, m_event);
#ifndef __LINUX__
    is_ExitEvent(m_hCam, m_event);
#endif
    //printf ("stop waiting on event %d\n", m_event);
}

