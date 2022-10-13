#include "progressevent.h"

ProgressEvent::ProgressEvent(int progress) : QEvent(static_cast<Type>(EventID)), m_progress(progress)
{

}

int ProgressEvent::progress() const
{
    return m_progress;
}
