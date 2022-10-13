#ifndef PROGRESSEVENT_H
#define PROGRESSEVENT_H

#include <QEvent>

class ProgressEvent : public QEvent
{
public:
    enum {EventID = QEvent::User + 1};
    ProgressEvent(int progress);

    int progress() const;

private:
    int m_progress;
};

#endif // PROGRESSEVENT_H
