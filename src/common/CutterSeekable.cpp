#include "MainWindow.h"
#include "CutterSeekable.h"

#include <QPlainTextEdit>


CutterSeekable::CutterSeekable(QObject *parent)
    :
    QObject(parent)
{
    connect(Core(), &CutterCore::seekChanged, this, &CutterSeekable::onCoreSeekChanged);
}

CutterSeekable::~CutterSeekable() {}

/*!
 * \brief Seek to a position, change current offset.
 *
 * If the seekable is synchronized with Core, then the Core offset will be
 * modified and then the CutterCore::seekChanged signal will be emitted.
 * In any case, CutterSeekable::seekableSeekChanged is emitted.
 */
void seek(RVA addr)
{
    updateSeek(addr, false);
}

/*!
 * \brief Signal received when the Core seek has changed.
 *
 * This is used when the CutterSeekable is synchronized with Core.
 */
void CutterSeekable::onCoreSeekChanged(RVA addr)
{
    if (synchronized && widgetOffset != addr) {
        updateSeek(addr, true);
    }
}

void CutterSeekable::updateSeek(RVA addr, bool localOnly)
{
    previousOffset = widgetOffset;
    widgetOffset = addr;
    if (synchronized && !localOnly) {
        Core()->seek(addr);
    }

    emit seekableSeekChanged(addr);
}

/*!
 * \brief Seek to last location.
 */
void CutterSeekable::seekPrev()
{
    if (synchronized) {
        Core()->seekPrev();
    } else {
        this->seek(previousOffset);
    }
}

/*!
 * \brief Retrieve the seekable offset.
 *
 * If the seekable is synchronized with Core, this function is similar to Core()->getOffset.
 * If it's not synchronized, it will return the seekable current seek.
 * Returns the seekable \c RVA offset.
 */
RVA CutterSeekable::getOffset()
{
    return (synchronized) ? Core()->getOffset() : widgetOffset;
}

/*!
 * \brief Toggle Core seek synchronization.
 */
void CutterSeekable::toggleSynchronization()
{
    synchronized = !synchronized;
    onCoreSeekChanged(Core()->getOffset());
}

/*!
 * \brief Tells whether the seekable is synchronized with Core or not.
 *
 * Returns \c true if the CutterSeekable is synchronized
 * with Core, \c false otherwise.
 */
bool CutterSeekable::isSynchronized()
{
    return synchronized;
}
