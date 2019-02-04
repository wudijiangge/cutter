#pragma once

#include "Cutter.h"

class MainWindow;

class CutterSeekable : public QObject
{
    Q_OBJECT

public:
    explicit CutterSeekable(QObject *parent = nullptr);
    ~CutterSeekable();

    void seek(RVA addr) { updateSeek(addr, false); }
    void toggleSynchronization();
    RVA getOffset();
    bool isSynchronized();

public slots:
    void seekPrev();

private slots:
    void onCoreSeekChanged(RVA addr);

private:
    /**
     * @brief widgetOffset widget seek location.
     */
    RVA widgetOffset = RVA_INVALID;

    /**
     * @brief previousOffset last seek location.
     * @todo maybe use an actual history?
     */
    RVA previousOffset = RVA_INVALID;

    /**
     * @brief synchronized tells with the seekable's offset is
     * synchronized with core or not.
     */
    bool synchronized = true;

    /**
     * @brief internal method for changing the seek
     * @param localOnly whether the seek should be updated globally if synchronized
     */
    void updateSeek(RVA addr, bool localOnly);

signals:
    void seekableSeekChanged(RVA addr);

};
